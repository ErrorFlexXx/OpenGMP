#include "frmMain.h"
#include "ui_frmMain.h"
//#include "inject.h"
#include "frmMainSettings.h"
#include <Shared/Utils/file.hpp>
#include <Launcher/Objects/jsonFile.hpp>
#include <Launcher/Objects/lserver.hpp>
#include <Launcher/Systems/serverStorage.hpp>
#include <Shared/Types/constants.hpp>
#include <Shared/Utils/logger.hpp>
#include <Shared/Utils/fileDownload.hpp>
#include "Systems/clientStore.hpp"
#include <qfiledialog.h>
#include <QMessageBox>
#include <QDateTime>
#include <QProgressBar>
#include <map>
#include <string>

using namespace std;
using namespace OpenGMP;

FrmMain::FrmMain(QWidget *parent)
    : QMainWindow(parent)
    , config("Settings.json")
    , ui(new Ui::FrmMain)
    , serverListName("Serverlist.json")
    , frmLogConsole(parent)
    , progressBar(nullptr)
    , progressText(nullptr)
    , contextSelectedItem(nullptr)
{
    ui->setupUi(this); //Setup the ui.

    if(!config.Load())          //Load the config
        CreateDefaultConfig();  //or create the default one.

    serverList.clear();
    ServerStorage::LoadCachedServerlist(serverListName, serverList); //Load locally stored servers
    //And update with the web list:
    if(ServerStorage::LoadWebServerlist("raw.githubusercontent.com", "/ErrorFlexXx/OpenGMP/master/ServerList/serverList.json", serverList))
        ServerStorage::StoreCachedServerList(serverListName, serverList); //Save to local cache.
    UpdateFrmServerList(); //Insert treeView items to form.

    SetupServerCommunicator();  //Start the updater thread.

    SetupClientStore();         //Start the clientStore thread (for ui decoupled tasks).

    SetupTreeViewActions();     //Setup of context / double click actions for the serverlist.

}

FrmMain::~FrmMain()
{
    serverCommunicatorTask->Stop();
    delete ui;
}

OpenGMP::LServer &FrmMain::GetServerFromTreeItem(QTreeWidgetItem *item)
{
    for(OpenGMP::LServer &server : serverList)
    {
        if(item && item == server.treeItem)
            return server;
    }
    //Should never happen:
    LogError() << "Can't find server with given tree item!";
    QMessageBox::critical(nullptr, "Critical error", "Internal application error. Please restart the application!");
    exit(0);
}

void FrmMain::UpdateFrmServerList()
{
    ui->treeServerList->clear();
    for(OpenGMP::LServer &server : serverList)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(LServer::ServernameCol, server.servername.c_str());
        item->setText(LServer::HostnameCol, server.hostname.c_str());
        item->setText(LServer::PortCol, QString::number(server.webPort));
        item->setText(LServer::VersionCol, VersionSystem::GetVersionString(server.version.version).c_str());
        item->setText(LServer::PingCol, QString("Contacting"));
        server.treeItem = item;
        ui->treeServerList->addTopLevelItem(item);
        for(int i = 0; i < LServer::UiListColumns::Max; i++)
            ui->treeServerList->resizeColumnToContents(i);
    }
}

void FrmMain::CreateDefaultConfig()
{
    config.Clear();

    config.WriteBool("SearchForUpdatesOnStart", true);
    config.Save();
}

/******************************************
 * Server Communicator update slots:
 ******************************************/
void FrmMain::UpdateServerEntry(const OpenGMP::LServer &server)
{
    if(server.treeItem)
    {
        server.treeItem->setText(OpenGMP::LServer::PlayerCol, server.playerInfo);
        server.treeItem->setText(OpenGMP::LServer::PingCol, server.pingInfo);
    }
}

void FrmMain::UpdateServerEntryNowOnline(const OpenGMP::LServer &server)
{
    UpdateServerEntry(server); //Enter normal informations
    if(server.treeItem)
    {
        //Enter online informations.
        server.treeItem->setText(OpenGMP::LServer::ServernameCol, server.servernameInfo);
        server.treeItem->setText(OpenGMP::LServer::VersionCol, server.versionInfo);
        for(int i = 0; i < LServer::UiListColumns::Max; i++) //Adjust column widths
            ui->treeServerList->resizeColumnToContents(i);
        //Update local store
        for(LServer &storeServer : serverList)
        {
            if(server == storeServer)
            {
                storeServer.isOnline = true;
                storeServer.servername = server.servername;
                storeServer.version = server.version;
                break;
            }
        }
        ServerStorage::StoreCachedServerList(serverListName, serverList);
    }
}

void FrmMain::UpdateServerEntryNowOffline(const OpenGMP::LServer &server)
{
    UpdateServerEntry(server); //Enter normal informations

    for(int i = 0; i < LServer::UiListColumns::Max; i++) //Adjust column widths
        ui->treeServerList->resizeColumnToContents(i);

    //Update store server online flag.
    for(LServer &storeServer : serverList)
    {
        if(server == storeServer)
        {
            storeServer.isOnline = false;
        }
    }
}

/******************************************
 * Client store progress status bar slots:
 ******************************************/
void FrmMain::ProgressBegin(const QString &text)
{
    if(!progressText)
    {   //Creation:
        progressText = new QLabel();
        ui->statusBar->insertPermanentWidget(0, progressText);
    }
    progressText->setText(text); //Setup

    if(!progressBar)
    {   //Creation:
        progressBar = new QProgressBar();
        ui->statusBar->insertPermanentWidget(1, progressBar, 1);
    }
    progressBar->setMaximum(100); //Setup
    progressBar->setValue(0);

    ui->statusBar->show();
}

void FrmMain::ProgressUpdate(int progress, const QString &text)
{
    if(progressBar)
    {
        progressBar->setValue(progress);
    }
    if(progressText)
    {
        progressText->setText(text);
    }
}

void FrmMain::ProgressUpdate(int progress)
{
    if(progressBar)
        progressBar->setValue(progress);
}

void FrmMain::ProgressFinished()
{
    ui->statusBar->hide();
}

/*****************
 * Menu bar slots:
 *****************/
void FrmMain::on_actionExit_triggered()
{
    this->close();
}

void FrmMain::on_actionMainSettings_triggered()
{
    FrmMainSettings frmSettings(this);
    frmSettings.exec(); //Open modal.
}

void FrmMain::on_actionLog_Console_triggered()
{
    frmLogConsole.open();
}

void FrmMain::on_btnTest_clicked()
{
//    static Inject injTest;
//    QString newPath = QFileDialog::getExistingDirectory(this, tr("Bitte wählen Sie den Gothic Pfad aus"),
//                                                        "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
//    experimental::filesystem::path path;
//    path.assign(newPath.toStdString()); //Normalizes the path.
//    if(0 < newPath.size())
//    {
//        string gothic = newPath.toStdString();
//        experimental::filesystem::path gmpPath;
//        gmpPath.assign(QApplication::applicationDirPath().append("/gmp").toStdString());
//        experimental::filesystem::path localePath;
//        localePath.assign(QApplication::applicationDirPath().append("/locale").toStdString());
//        string dll = gmpPath.string();
//        dll.append("\\OpenGMP.dll");
//        gothic.append("/Gothic2.exe");
//        injTest.SetStartProgram(gothic.c_str(), "");
//        injTest.SetInjectProgram(dll.c_str());
//        injTest.AddEnvironmentVariable(make_pair<string, string>(hostnameEnvVarName, "192.168.1.201"));
//        injTest.AddEnvironmentVariable(make_pair<string, string>(webStatusPortVarName, "1761"));
//        injTest.AddEnvironmentVariable(make_pair<string, string>(localeEnvVarName, localePath.string()));
//        injTest.AppendEnvironmentVariable(make_pair<string, string>("PATH", path.string())); //PATH=Gothic/System
//        injTest.AppendEnvironmentVariable(make_pair<string, string>("PATH", gmpPath.string())); //PATH=gmp
//        injTest.Start(false);
//        }
//    std::vector<OpenGMP::Server> serverlist;

//    for(int i = 0; i < 4; i++)
//    {
//        OpenGMP::Server test;
//        test.hostname = to_string(i);
//        test.gamePort = i;
//        test.webPort = i + 1;
//        test.servername = "testname";
//        test.servername += to_string(i);
//        serverlist.push_back(test);
//    }
//    ServerStorage::LoadCachedServerlist("serverlist.json", serverlist);
//    ServerStorage::StoreCachedServerList("serverlist.json", serverlist);
//    emit StartClient(*serverList.begin());
}

void FrmMain::StartSelectedClient()
{
    if(contextSelectedItem)
    {
        LServer &server = GetServerFromTreeItem(contextSelectedItem);
        emit StartClient(server);
    }
}

void FrmMain::CustomMenuRequested(QPoint pos)
{
    contextSelectedItem = ui->treeServerList->itemAt(pos);
    if(contextSelectedItem)
    {
        QMenu *menu = new QMenu(this);
        menu->addAction(new QAction(tr("Connect"), this));
        //menu->addAction(new QAction(tr("Remove"), this));
        connect(menu->actions()[0], SIGNAL(triggered()), this, SLOT(StartSelectedClient()));
        //connect(menu->actions()[1], SIGNAL(triggered()), this, SLOT(contextGasbankDisconnect_triggered()));
        menu->popup(ui->treeServerList->viewport()->mapToGlobal(pos));
    }
}

void FrmMain::TreeWidgetItemDoubleClicked(QTreeWidgetItem *item, int column)
{
    contextSelectedItem = item;
    (void) &column; //Unused - Do not warn.
    StartSelectedClient();
}

void FrmMain::SetupServerCommunicator()
{
    //Create Updater Thread:
    serverCommunicator = new QThread();
    if(!serverCommunicator)
    {
        LogError() << "Out of memory!";
        return;
    }
    serverCommunicatorTask = new ServerCommunicator();
    if(!serverCommunicatorTask)
    {
        LogError() << "Out of memory!";
        return;
    }
    serverCommunicatorTask->SetServerList(serverList);
    serverCommunicatorTask->moveToThread(serverCommunicator);
    //Connect Signals (Serverlist update):
    connect(serverCommunicatorTask, SIGNAL(UpdateServerEntry(const OpenGMP::LServer)),
            this, SLOT(UpdateServerEntry(const OpenGMP::LServer)));
    connect(serverCommunicatorTask, SIGNAL(UpdateServerEntryNowOnline(const OpenGMP::LServer)),
            this, SLOT(UpdateServerEntryNowOnline(const OpenGMP::LServer)));
    connect(serverCommunicatorTask, SIGNAL(UpdateServerEntryNowOffline(const OpenGMP::LServer)),
            this, SLOT(UpdateServerEntryNowOffline(const OpenGMP::LServer)));
    connect(serverCommunicator, SIGNAL(started()),
            serverCommunicatorTask, SLOT(UpdateServerLoop()) );  //Start the update server loop on thread start.
    connect(serverCommunicatorTask, SIGNAL(finished()),
            serverCommunicator, SLOT(quit()));              //If the task ends, the thread quits.
    connect(serverCommunicatorTask, SIGNAL(finished()),
            serverCommunicatorTask, SLOT(deleteLater()));   //Let Qt free the Task
    connect(serverCommunicator, SIGNAL(finished()),
            serverCommunicator, SLOT(deleteLater())); //Let Qt free the Thread
    connect(this, SIGNAL(UpdatedServerList(const std::list<OpenGMP::LServer>&)),
            serverCommunicatorTask, SLOT(SetServerList(const std::list<OpenGMP::LServer>&)));
    serverCommunicator->start();
    LogInfo() << "Server list updater started.";
}

void FrmMain::SetupClientStore()
{
    clientStoreThread = new QThread();
    if(!clientStoreThread)
    {
        LogError() << "Out of memory!";
        return;
    }
    connect(&clientStore, SIGNAL(ProgressBegin(QString)), this, SLOT(ProgressBegin(QString)));
    connect(&clientStore, SIGNAL(ProgressUpdate(int, QString)), this, SLOT(ProgressUpdate(int, QString)));
    connect(&clientStore, SIGNAL(ProgressUpdate(int)), this, SLOT(ProgressUpdate(int)));
    connect(&clientStore, SIGNAL(ProgressFinished()), this, SLOT(ProgressFinished()));
    connect(this, SIGNAL(StartClient(OpenGMP::LServer)), &clientStore, SLOT(Start(OpenGMP::LServer)));
    connect(clientStoreThread, SIGNAL(finished()),
            clientStoreThread, SLOT(deleteLater())); //Let Qt free the Thread
    clientStore.moveToThread(clientStoreThread);
    clientStoreThread->start();
    LogInfo() << "ClientStore started.";
}

void FrmMain::SetupTreeViewActions()
{
    //Tree Context Menu
    ui->treeServerList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeServerList, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(CustomMenuRequested(QPoint)));
    connect(ui->treeServerList, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
            this, SLOT(TreeWidgetItemDoubleClicked(QTreeWidgetItem*,int)));
}

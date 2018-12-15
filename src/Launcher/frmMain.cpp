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
{
    ui->setupUi(this);
    if(!config.Load())
        CreateDefaultConfig();
    serverList.clear();
    ServerStorage::LoadCachedServerlist(serverListName, serverList);
    if(ServerStorage::LoadWebServerlist("raw.githubusercontent.com", "/ErrorFlexXx/OpenGMP/master/ServerList/serverList.json", serverList))
        ServerStorage::StoreCachedServerList(serverListName, serverList); //Save to local cache.
    UpdateFrmServerList(); //Insert treeView items to form.
    //Create Updater Thread:
    serverCommunicator      = new QThread();
    serverCommunicatorTask  = new ServerCommunicator(parent);
    serverCommunicatorTask->SetServerList(serverList);
    serverCommunicatorTask->moveToThread(serverCommunicator);
    //Connect Signals:
    connect(serverCommunicatorTask, SIGNAL(UpdateServerEntry(const OpenGMP::LServer)), this, SLOT(UpdateServerEntry(const OpenGMP::LServer)));
    connect(serverCommunicatorTask, SIGNAL(UpdateServerEntryNowOnline(const OpenGMP::LServer)), this, SLOT(UpdateServerEntryNowOnline(const OpenGMP::LServer)));
    connect(serverCommunicatorTask, SIGNAL(UpdateServerEntryNowOffline(const OpenGMP::LServer)), this, SLOT(UpdateServerEntryNowOffline(const OpenGMP::LServer)));
    connect(serverCommunicator, SIGNAL(started()), serverCommunicatorTask, SLOT(UpdateServerLoop()) );  //Start the update server loop on thread start.
    connect(serverCommunicatorTask, SIGNAL(finished()), serverCommunicator, SLOT(quit()));              //If the task ends, the thread quits.
    connect(serverCommunicatorTask, SIGNAL(finished()), serverCommunicatorTask, SLOT(deleteLater()));   //Let Qt free the Task
    connect(serverCommunicator, SIGNAL(finished()), serverCommunicator, SLOT(deleteLater()));           //Let Qt free the Thread
    connect(this, SIGNAL(UpdatedServerList(const std::list<OpenGMP::LServer>&)), serverCommunicatorTask, SLOT(SetServerList(const std::list<OpenGMP::LServer>&)));
    serverCommunicator->start();
}

FrmMain::~FrmMain()
{
    serverCommunicatorTask->Stop();
    delete ui;
}

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
    ClientStore testStore;
    testStore.Download(serverList.front().version);
}

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

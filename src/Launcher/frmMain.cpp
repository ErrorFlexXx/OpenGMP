#include "frmMain.h"
#include "ui_frmMain.h"
#include "inject.h"
#include "frmMainSettings.h"
#include <Launcher/Systems/JsonFile.hpp>
#include <Shared/Types/constants.hpp>
#include <ZenLib/utils/logger.h>
#include <qfiledialog.h>
#include <map>
#include <string>

using namespace std;
using namespace httplib;
using namespace OpenGMP;

FrmMain::FrmMain(QWidget *parent)
    : QMainWindow(parent)
    , config("Settings.json")
    , ui(new Ui::FrmMain)
{
    ui->setupUi(this);
    if(!config.Load())
        CreateDefaultConfig();
}

FrmMain::~FrmMain()
{
    delete ui;
}

void FrmMain::CreateDefaultConfig()
{
    config.Clear();

    config.WriteBool("SearchForUpdatesOnStart", true);
    config.Save();
}

void FrmMain::GetServerlist()
{
    SSLClient client("raw.githubusercontent.com", 443);
    auto res = client.Get("/ErrorFlexXx/OpenGMP/master/ServerList/serverList.json");
    if (res) //&& res->status == 200)
    {
        LogInfo() << res->status;
        LogInfo() << res->body;
    }
}

void FrmMain::on_btnTest_clicked()
{
    static Inject injTest;
    QString newPath = QFileDialog::getExistingDirectory(this, tr("Bitte wählen Sie den Gothic Pfad aus"),
                                                        "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    experimental::filesystem::path path;
    path.assign(newPath.toStdString()); //Normalizes the path.
    if(0 < newPath.size())
    {
        string gothic = newPath.toStdString();
        experimental::filesystem::path gmpPath;
        gmpPath.assign(QApplication::applicationDirPath().append("/gmp").toStdString());
        experimental::filesystem::path localePath;
        localePath.assign(QApplication::applicationDirPath().append("/locale").toStdString());
        string dll = gmpPath.string();
        dll.append("\\OpenGMP.dll");
        gothic.append("/Gothic2.exe");
        injTest.SetStartProgram(gothic.c_str(), "");
        injTest.SetInjectProgram(dll.c_str());
        injTest.AddEnvironmentVariable(make_pair<string, string>(hostnameEnvVarName, "192.168.1.201"));
        injTest.AddEnvironmentVariable(make_pair<string, string>(webStatusPortVarName, "1761"));
        injTest.AddEnvironmentVariable(make_pair<string, string>(localeEnvVarName, localePath.string()));
        injTest.AppendEnvironmentVariable(make_pair<string, string>("PATH", path.string())); //PATH=Gothic/System
        injTest.AppendEnvironmentVariable(make_pair<string, string>("PATH", gmpPath.string())); //PATH=gmp
        injTest.Start(false);
        }
    GetServerlist();
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

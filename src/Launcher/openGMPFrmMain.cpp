#include "openGMPFrmMain.h"
#include "ui_openGMPFrmMain.h"
#include "inject.h"
#include <map>
#include <string>
#include <Shared/Types/constants.hpp>
#include <qfiledialog.h>

using namespace std;
using namespace OpenGMP;

OpenGMPFrmMain::OpenGMPFrmMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpenGMPFrmMain)
{
    ui->setupUi(this);
}

OpenGMPFrmMain::~OpenGMPFrmMain()
{
    delete ui;
}

void OpenGMPFrmMain::on_btnTest_clicked()
{
    static Inject injTest;
    QString newPath = QFileDialog::getExistingDirectory(this, tr("Bitte wählen Sie den Gothic Pfad aus"),
                                                            "",
                                                                QFileDialog::ShowDirsOnly
                                                                | QFileDialog::DontResolveSymlinks);
    experimental::filesystem::path path;
    path.assign(newPath.toStdString()); //Normalizes the path.
    if(0 < newPath.size())
    {
        string gothic = newPath.toStdString();
        string dll = newPath.toStdString();
        gothic.append("/Gothic2.exe");
        dll.append("/OpenGMP.dll");
        injTest.SetStartProgram(gothic.c_str(), "");
        injTest.SetInjectProgram(dll.c_str());
        injTest.AddEnvironmentVariable(make_pair<string, string>(hostnameEnvVarName, "192.168.1.201"));
        injTest.AddEnvironmentVariable(make_pair<string, string>(portEnvVarName, "1760"));
        injTest.AppendEnvironmentVariable(make_pair<string, string>("PATH", path.string()));
        injTest.Start(false);
    }
}

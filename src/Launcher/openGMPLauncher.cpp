#include "openGMPLauncher.h"
#include "ui_openGMPLauncher.h"

OpenGMPLauncher::OpenGMPLauncher(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpenGMPLauncher)
{
    ui->setupUi(this);
}

OpenGMPLauncher::~OpenGMPLauncher()
{
    delete ui;
}

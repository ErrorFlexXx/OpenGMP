#include "openGMP.h"
#include "ui_openGMP.h"

OpenGMP::OpenGMP(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpenGMP)
{
    ui->setupUi(this);
}

OpenGMP::~OpenGMP()
{
    delete ui;
}

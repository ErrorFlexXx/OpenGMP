#include "frmMainSettings.h"
#include "ui_frmMainSettings.h"
#include <frmMain.h>
#include <QMessageBox>

FrmMainSettings::FrmMainSettings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FrmMainSettings)
{
    ui->setupUi(this);
    frmMain = dynamic_cast<FrmMain*>(parent);
    if(!frmMain)
        this->close();
    bool searchForUpdatesOnStart;
    if(frmMain->config.ReadBool("SearchForUpdatesOnStart", searchForUpdatesOnStart))
        ui->cbxSearchForUpdatesOnStart->setChecked(searchForUpdatesOnStart);
}

FrmMainSettings::~FrmMainSettings()
{
    delete ui;
}

void FrmMainSettings::on_btnSave_clicked()
{
    frmMain->config.WriteBool("SearchForUpdatesOnStart", ui->cbxSearchForUpdatesOnStart->isChecked());

    if(!frmMain->config.Save())
    {
        QMessageBox::critical(this, tr("Save failed!"), tr("Cannot write config file: ").append(frmMain->config.configDir.absoluteFilePath(
                                                                                                    frmMain->config.filename)));
    }
    this->close();
}

void FrmMainSettings::on_btnCancel_clicked()
{
    this->close();
}

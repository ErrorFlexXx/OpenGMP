#pragma once

#include <QDialog>

namespace Ui {
class FrmMainSettings;
}

class FrmMain;

class FrmMainSettings : public QDialog
{
    Q_OBJECT

public:
    explicit FrmMainSettings(QWidget *parent = nullptr);
    ~FrmMainSettings();

private slots:
    void on_btnSave_clicked();
    void on_btnCancel_clicked();

private:
    Ui::FrmMainSettings *ui;
    FrmMain *frmMain;
};

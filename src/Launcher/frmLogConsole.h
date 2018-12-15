#ifndef FRMLOGCONSOLE_H
#define FRMLOGCONSOLE_H

#include <QDialog>

namespace Ui {
    class FrmLogConsole;
}

class FrmLogConsole : public QDialog
{
    Q_OBJECT

public:
    explicit FrmLogConsole(QWidget *parent = 0);
    ~FrmLogConsole();

private slots:
    void on_cbxLogLevel_currentIndexChanged(int index);

private:
    Ui::FrmLogConsole *ui;
};

#endif // FRMLOGCONSOLE_H

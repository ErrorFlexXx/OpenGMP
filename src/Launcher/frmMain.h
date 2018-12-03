#pragma once

#include <Launcher/Systems/JsonFile.hpp>
#include <Shared/Objects/server.hpp>
#include <QMainWindow>
#include <cpp-httplib/httplib.h>
#include <vector>

namespace Ui {
    class FrmMain;
}

class FrmMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit FrmMain(QWidget *parent = nullptr);
    ~FrmMain();

    void CreateDefaultConfig();
    void GetServerlist();
    std::vector<OpenGMP::Server> serverList;//!< List of known servers.
    OpenGMP::JsonFile config;               //!< Json parser object for configurations.

private slots:
    void on_btnTest_clicked();
    void on_actionExit_triggered();
    void on_actionMainSettings_triggered();

private:
    Ui::FrmMain *ui;
};

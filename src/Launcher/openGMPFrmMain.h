#pragma once

#include <Shared/Objects/server.hpp>
#include <QMainWindow>
#include <vector>
#include <cpp-httplib/httplib.h>

namespace Ui {
    class OpenGMPFrmMain;
}

class OpenGMPFrmMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit OpenGMPFrmMain(QWidget *parent = nullptr);
    ~OpenGMPFrmMain();

    std::vector<OpenGMP::Server> serverList; //!< List of known servers.

private slots:
    void on_btnTest_clicked();

private:
    Ui::OpenGMPFrmMain *ui;
};

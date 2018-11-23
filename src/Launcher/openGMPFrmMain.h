#pragma once

#include <QMainWindow>

namespace Ui {
    class OpenGMPFrmMain;
}

class OpenGMPFrmMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit OpenGMPFrmMain(QWidget *parent = nullptr);
    ~OpenGMPFrmMain();

private slots:
    void on_btnTest_clicked();

private:
    Ui::OpenGMPFrmMain *ui;
};

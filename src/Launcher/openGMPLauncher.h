#ifndef OPENGMPLAUNCHER_H
#define OPENGMPLAUNCHER_H

#include <QMainWindow>

namespace Ui {
    class OpenGMPLauncher;
}

class OpenGMPLauncher : public QMainWindow
{
    Q_OBJECT

public:
    explicit OpenGMPLauncher(QWidget *parent = 0);
    ~OpenGMPLauncher();

private:
    Ui::OpenGMPLauncher *ui;
};

#endif // OPENGMPLAUNCHER_H

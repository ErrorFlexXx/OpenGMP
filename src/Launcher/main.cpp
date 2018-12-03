#include "frmMain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FrmMain w;
    w.show();

    return a.exec();
}

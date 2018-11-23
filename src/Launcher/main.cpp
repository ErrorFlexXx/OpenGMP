#include "openGMPFrmMain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpenGMPFrmMain w;
    w.show();

    return a.exec();
}

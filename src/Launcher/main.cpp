#include "frmMain.h"
#include <Shared/Utils/logger.hpp>
#include <QApplication>

int main(int argc, char *argv[])
{
    Log() << OpenGMP::Logger::Debug; //Set debug log level.
    QApplication a(argc, argv);
    FrmMain w;
    w.show();

    return a.exec();
}

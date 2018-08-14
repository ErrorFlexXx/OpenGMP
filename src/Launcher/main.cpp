#include "openGMP.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpenGMP w;
    w.show();

    return a.exec();
}

#include "clientInstallation.hpp"
#include <ZenLib/utils/logger.h>
#include <QStandardPaths>

using namespace OpenGMP;

ClientInstallation::ClientInstallation(Version &version)
    : version(version)
{
    //LogInfo() << "Will install clients here: " << QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).toStdString();
}

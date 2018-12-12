#include "clientStore.hpp"
#include <Shared/Utils/logger.hpp>
#include <QStandardPaths>

using namespace std;
using namespace OpenGMP;

ClientStore::ClientStore()
    : ClientStore(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).toStdString())
{}

ClientStore::ClientStore(const string &installationDir)
    : installationDir(installationDir)
{
    LogInfo() << "ClientStore created with install dir: " << installationDir;
}



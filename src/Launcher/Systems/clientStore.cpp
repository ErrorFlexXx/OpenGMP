#include "clientStore.hpp"
#include <Shared/Utils/logger.hpp>
#include <Shared/Components/version.hpp>
#include <QStandardPaths>

using namespace std;
using namespace OpenGMP;

ClientStore::ClientStore()
    : ClientStore(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).toStdString(),
                  QStandardPaths::writableLocation(QStandardPaths::TempLocation).toStdString())
{}

ClientStore::ClientStore(const string &installationDir, const std::string &downloadDir)
    : installationDir(installationDir)
    , downloadDir(downloadDir)
{}

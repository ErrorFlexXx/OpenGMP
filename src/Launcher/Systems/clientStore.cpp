#include "clientStore.hpp"
#include <Shared/Utils/logger.hpp>
#include <Shared/Utils/fileDownload.hpp>
#include <Shared/Utils/zipFile.hpp>
#include <Shared/Components/version.hpp>
#include <Shared/Systems/versionSystem.hpp>
#include <experimental/filesystem>
#include <fstream>
#include <QStandardPaths>

using namespace std;
using namespace std::experimental;
using namespace OpenGMP;

ClientStore::ClientStore(QObject *parent)
    : QObject(parent)
    , installationDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).toStdString().append("/Clients"))
    , downloadDir(QStandardPaths::writableLocation(QStandardPaths::TempLocation).toStdString())
    , storeUrl("https://github.com/ErrorFlexXx/OpenGMP/releases/download/")
{
    CreateStore(); //Take care, store directory is created.
}

bool ClientStore::IsInstalled(const Version &version) const
{
    filesystem::path test(installationDir);
    test = test / VersionSystem::GetVersionString(version.version);
    error_code error;
    bool exists = filesystem::exists(test, error);
    if(error)
    {
        LogError() << error.message();
        return false;
    }
    return exists;
}

void ClientStore::Download(const Version &version)
{
    FileDownload download(downloadDir, "Client.zip");
    std::string downloadUrl = storeUrl;
    downloadUrl.append(VersionSystem::GetVersionString(version.version));
    downloadUrl.append("/Client.zip");
    LogInfo() << "ClientStore start download to: " << download.Fullpath() << " from " << downloadUrl;
    download.Download(downloadUrl, true);
    ZipFile zip = download;
    if(zip.Extract(installationDir))
    {
        LogInfo() << "Successfully installed Client version " << VersionSystem::GetVersionString(version.version);
        download.Delete();
    }
}

bool ClientStore::CreateStore() const
{
    if(!filesystem::exists(installationDir))
    {
        LogInfo() << "Client storage directory not found. Creating directory: " << installationDir << "...";
        error_code error;
        filesystem::create_directories(installationDir, error);
        if(error)
        {
            LogError() << "Can't create dir: " << installationDir << ". " << error.message();
            return false;
        }
    }
    return true;
}

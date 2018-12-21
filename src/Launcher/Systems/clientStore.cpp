#include "clientStore.hpp"
#include <Launcher/Objects/qFileDownload.hpp>
#include <Launcher/Objects/qZipFile.hpp>
#include <Shared/Utils/logger.hpp>
#include <Shared/Components/version.hpp>
#include <Shared/Systems/versionSystem.hpp>
#include <experimental/filesystem>
#include <fstream>
#include <QStandardPaths>
#include <QThread>

using namespace std;
using namespace std::experimental;
using namespace OpenGMP;

ClientStore::ClientStore(QObject *parent)
    : QObject(parent)
    , parent(parent)
    , installationDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation).toStdString().append("/Clients"))
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

void ClientStore::SetGothicPath(const std::string &path)
{
    gothicDir = path;
}

void ClientStore::Download(const Version &version)
{
    FileDownload download(downloadDir, "Client.zip");
    std::string downloadUrl = GetDownloadUrl(version);
    LogInfo() << "ClientStore start download to: " << download.Fullpath() << " from " << downloadUrl;
    download.Download(downloadUrl, true);
    ZipFile zip = download;
    if(zip.Extract(installationDir))
    {
        LogInfo() << "Successfully installed Client version " << VersionSystem::GetVersionString(version.version);
        download.Delete();
    }
}

void ClientStore::Start(const LServer &server)
{
    std::string startText = "Starting ";
    startText.append(VersionSystem::GetVersionString(server.version.version));
    emit ProgressBegin(startText.c_str());

    QThread::sleep(1);

    if(!IsInstalled(server.version)) //Client isn't installed yet, download it.
    {
        emit ProgressUpdate(1, "Downloading...");
        maxSubstepProgress = 50; //50 % progress after download.
        std::string downloadUrl = GetDownloadUrl(server.version);
        QFileDownload download(this, downloadDir, "Client.zip");
        download.connect(&download, SIGNAL(Progress(uint64_t,uint64_t)), this, SLOT(DownloadProgress(uint64_t,uint64_t)));
        download.StartDownload(downloadUrl);
        if(download.DownloadFinished() && !download.DownloadResult())
        {
            emit ProgressUpdate(100, QString("Client download failed! File: ").append(downloadUrl.c_str()));
            return;
        }
        QZipFile zip = download;
        emit ProgressUpdate(75, "Installing...");
        if(!zip.Extract(installationDir))
        {
            emit ProgressUpdate(100, QString("Installation failed! Destination was: ").append(installationDir.c_str()));
            return;
        }
        emit ProgressUpdate(95, "Starting...");
        QThread::sleep(1);
    }
    else
    {
        emit ProgressUpdate(95, "Client installed. Now starting...");
        QThread::sleep(1);
    }
    emit ProgressFinished();
}

void ClientStore::Subprogress(int percentage)
{
    emit ProgressUpdate(percentage / 100.f * (float) maxSubstepProgress);
}

void ClientStore::DownloadProgress(uint64_t len, uint64_t total)
{
    emit Subprogress((int)((float) len / (float) total * 100.f));
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

std::string ClientStore::GetDownloadUrl(const OpenGMP::Version &version) const
{
    std::string downloadUrl = storeUrl;
    downloadUrl.append(VersionSystem::GetVersionString(version.version));
    downloadUrl.append("/Client.zip");
    return downloadUrl;
}

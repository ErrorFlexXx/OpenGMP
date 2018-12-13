#include "clientStore.hpp"
#include <Shared/Utils/logger.hpp>
#include <Shared/Components/version.hpp>
#include <Shared/Systems/versionSystem.hpp>
#include <cpp-httplib/httplib.h>
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
    , storeHost("github.com")
    , storeUrl("/ErrorFlexXx/OpenGMP/releases/download/")
{}

bool ClientStore::IsInstalled(const Version &version) const
{
    CreateStore();
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

bool GetRedirectTarget(const std::string &location, std::string &outHost, std::string &outUrl)
{
    string tmp = location;
    string workTmp;

    if(tmp.find("https://") != string::npos)
        workTmp = tmp.substr(8); //Cut out https://
    else
        workTmp = tmp;
    if(workTmp.find("/") == string::npos) //Search / to cut out the host
        return false; //No / found -> No target!
    outHost = workTmp.substr(0, workTmp.find("/")); //Cut out host
    outUrl = workTmp.substr(workTmp.find("/")); //Cut out url
    return true; //Got all data
}

void ClientStore::Download(const Version &version)
{
    httplib::SSLClient client(storeHost.c_str(), 443);
    std::string requestFile = storeUrl;
    requestFile.append(VersionSystem::GetVersionString(version.version)).append("/Client.zip");
    auto res = client.Get(requestFile.c_str());
    if(res)
    {
        if(res->status == 302)
        {
            string redirect = res->get_header_value("Location");
            string newHost;
            string newUrl;
            if(GetRedirectTarget(redirect, newHost, newUrl))
            {
                httplib::SSLClient client(newHost.c_str(), 443);
                res = client.Get(newUrl.c_str());
            }
            else
            {
                LogError() << "FIXME - Can't extract redirect address from: " << redirect;
                return;
            }
        }
        if(res && res->status == 200) //Got file
        {
            ofstream write; //Write to disk
            std::string outPath = string(downloadDir).append("/Client.zip");
            write.open(outPath, std::ios::out | std::ios::trunc | std::ios::binary);
            if(write.is_open())
            {
                write.write(res->body.c_str(), res->body.length());
                write.close();
            }
            else
                LogError() << "Can't write file to: " << outPath;
        }
        else
        {
            if(res)
                LogError() << "Request failed. Status: " << res->status;
            else
                LogError() << "Request failed. No result given!";
        }
    }
}

bool ClientStore::CreateStore() const
{
    error_code error;
    filesystem::create_directory(installationDir, error);
    if(error)
    {
        LogError() << "Can't create dir: " << installationDir << ". " << error.message();
        return false;
    }
    return true;
}

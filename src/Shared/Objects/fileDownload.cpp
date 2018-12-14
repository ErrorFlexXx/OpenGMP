#include "fileDownload.hpp"
#include <Shared/Utils/url.hpp>
#include <cpp-httplib/httplib.h>

using namespace std;
using namespace OpenGMP;

FileDownload::FileDownload(const std::string &filename)
    : File(filename)
{}

FileDownload::FileDownload(const std::string &directory, const std::string &filename)
    : File(directory, filename)
    , redirectCount(0)
{}

bool FileDownload::Download(const std::string &url)
{
    Url downloadUrl(url);
    if(downloadUrl.port == 80)
        return DownloadHttp(url);
    return DownloadHttps(url); //Default https
}

bool FileDownload::DownloadHttp(const std::string &url)
{
    Url downloadUrl(url);

    httplib::Client client(downloadUrl.host.c_str(), downloadUrl.port);
    return DownloadBase(client, downloadUrl);
}

bool FileDownload::DownloadHttps(const std::string &url)
{
    Url downloadUrl(url);

    httplib::SSLClient client(downloadUrl.host.c_str(), downloadUrl.port);
    return DownloadBase(client, downloadUrl);
}

bool FileDownload::DownloadBase(httplib::Client &client, const Url &url)
{
    auto response = client.Get(url.path.c_str());
    if(response)
    {
        if(response->status == 302) //Redirect ?
        {
            redirectCount++;
            if(redirectCount > REDIRECT_LIMIT)
            {
                LogError() << "Detected infinite redirection! Canceled after " << redirectCount << " tries!";
                return false;
            }
            return Download(response->get_header_value("Location"));
        }
        else if(response->status == 200) //Ok ?
        {
            ofstream write; //Write to disk
            write.open(Fullpath(), std::ios::out | std::ios::trunc | std::ios::binary);
            if(write.is_open())
            {
                write.write(response->body.c_str(), response->body.length());
                write.close();
                return true;
            }
            else
            {
                LogError() << "Can't write file to: " << Fullpath();
                return false;
            }
        }
    }
    LogError() << "Didn't get a response from host: " << url.host;
    return false;
}

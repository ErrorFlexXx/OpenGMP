#include "fileDownload.hpp"
#include <Shared/Utils/url.hpp>
#include <cpp-httplib/httplib.h>
#include <thread>
#include <chrono>

using namespace std;
using namespace OpenGMP;

FileDownload::FileDownload(const std::string &filename)
    : File(filename)
{}

FileDownload::FileDownload(const std::string &directory, const std::string &filename)
    : File(directory, filename)
    , worker(nullptr)
    , downloadPending(false)
    , downloadResult(false)
    , redirectCount(0)
{}

FileDownload::~FileDownload()
{
    //Wait for thread finish - deleting this object forbidden while
    //thread is running.
    while(worker && lock.try_lock() == false) //Thread exists, and lock is locked.
        std::this_thread::sleep_for(1ms); //Wait for thread finish.
    delete worker;      //Delete the worker thread.
    worker = nullptr;   //Mark as deleted.
}

bool FileDownload::DownloadFinished()
{
    bool locked = lock.try_lock();
    if(!locked)
        return false;
    lock.unlock();
    return !downloadPending;
}

bool FileDownload::DownloadResult()
{
    bool locked = lock.try_lock();
    if(!locked)
        return false;
    bool result = downloadResult;
    if(worker)
    {
        delete worker;
        worker = nullptr;
    }
    lock.unlock();
    return result;
}

bool FileDownload::Download(const std::string &url, bool blocking)
{
    if(!blocking)
    {
        if(worker == nullptr)
        {
            worker = new std::thread([=]{
                LogInfo() << "Thread started!";
                lock_guard<mutex> guard(lock);
                LogInfo() << "Thread locked!";
                downloadResult = Download(url, true);
                downloadPending = false;
                LogInfo() << "Thread finished!";
            });
            worker->detach();
            while(lock.try_lock() == true) //Wait for thread start.
            {
                lock.unlock();
                std::this_thread::sleep_for(1ms); //Wait for thread finish.
            }
            return true; //Async download started successfully.
        }
        else
        {
            LogError() << "Do not start a non blocking download twice!";
            return false;
        }
    }
    //Blocking:
    Url downloadUrl(url);
    downloadPending = true;
    if(downloadUrl.protocol.find("http://") != string::npos ||
       downloadUrl.port == 80) //Http
        return DownloadHttp(url);
    else //Https
        return DownloadHttps(url);
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
    auto response = client.Get(url.path.c_str(), [=] (uint64_t len, uint64_t total) {
        ProgressUpdate(len, total);
        return true;
    });
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
            return Download(response->get_header_value("Location"), true);
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
        else //Unexpected result
        {
            LogError() << "Download failed! Status: " << response->status << " Message: " << response->body;
            return false;
        }
    }
    LogError() << "Didn't get a response from host: " << url.host << ":" << url.port;
    return false;
}

void FileDownload::ProgressUpdate(uint64_t len, uint64_t total)
{
    LogInfo() << len << "/" << total;
}

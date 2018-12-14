#include "qFileDownload.hpp"

using namespace std;
using namespace OpenGMP;

QFileDownload::QFileDownload(QObject *parent,
                             const string &directory,
                             const string &filename)
    : QObject(parent)
    , FileDownload(directory, filename)
{}

void QFileDownload::ProgressUpdate(uint64_t len, uint64_t total)
{
    emit Progress(len, total);
}

void QFileDownload::StartDownload(const std::string &url)
{
    bool success = Download(url, true);
    emit Finished(success);
}

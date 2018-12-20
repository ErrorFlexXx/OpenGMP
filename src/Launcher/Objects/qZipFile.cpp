#include "qZipFile.hpp"

using namespace OpenGMP;

QZipFile::QZipFile(QObject *parent,
                   const std::string &directory,
                   const std::string &filename)
    : QObject(parent)
    , ZipFile(directory, filename)
{}

QZipFile::QZipFile(const File &copy)
    : QObject(nullptr)
    , ZipFile(copy)
{}

QZipFile::QZipFile(const QZipFile &copy)
    : QObject(nullptr)
    , ZipFile(copy)
{}

void QZipFile::StartExtract(const std::string &to)
{
    bool success = Extract(to);
    emit finished(success);
}

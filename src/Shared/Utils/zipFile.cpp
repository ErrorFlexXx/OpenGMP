#include "zipFile.hpp"

using namespace OpenGMP;

ZipFile::ZipFile(const std::string &filename)
    : File(filename)
{}

ZipFile::ZipFile(const std::string &filename, const std::string &directory)
    : File(filename, directory)
{}

bool ZipFile::Extract(const std::string &to)
{
    return false;
}

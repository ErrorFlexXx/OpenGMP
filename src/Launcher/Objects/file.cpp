#include "file.hpp"
#include <Shared/Utils/logger.hpp>
#include <Shared/Utils/format.hpp>
#include <experimental/filesystem>
#include <fstream>
#include <ios>

using namespace std;
using namespace std::experimental;
using namespace OpenGMP;

size_t File::bufferSize = 10 * MEGA; //Byte

File::File(const string &filename)
    : directory(filesystem::current_path().string())
    , filename(filename)
{}

File::File(const string &directory, const string &filename)
    : directory(directory)
    , filename(filename)
{}

bool File::Exists() const
{
    string fullpath = Fullpath();
    ifstream test(fullpath.c_str());
    return test.good();
}

std::string File::Fullpath() const
{
    filesystem::path fullpath;
    fullpath.assign(directory);
    fullpath = fullpath / filename;
    return fullpath.string();
}

uintmax_t File::Size() const
{
    std::error_code err;
    uintmax_t size = filesystem::file_size(Fullpath(), err);
    if(err)
    {
        LogError() << err.message();
    }
    return size;
}

bool File::Copy(const string &to) const
{
    std::error_code error;
    filesystem::copy_file(Fullpath(), to, error);
    if(error)
    {
        LogError() << error.message();
        return false;
    }
    return true;
}

bool File::Move(const string &to) const
{
    if(!Copy(to))
        return false;

    std::error_code error;
    filesystem::remove(Fullpath(), error);
    if(error)
    {
        LogError() << error.message();
        return false;
    }

    return true;
}

bool File::Delete() const
{
    std::error_code error;
    filesystem::remove(Fullpath(), error);
    if(error)
    {
        LogError() << error.message();
        return false;
    }
    return true;
}

string File::MD5(const string &delim) const
{
    unsigned char digest[MD5_DIGEST_LENGTH];
    char *buffer = new char[File::bufferSize];
    MD5_CTX mdContext;

    ifstream file;
    file.open(Fullpath(), std::ios::in | std::ios::binary);
    if(!file.is_open())
    {
        LogError() << "Can't open file: " << Fullpath();
        return "";
    }
    if(!buffer)
    {
        LogError() << "Out of memory!";
        return "";
    }

    MD5_Init (&mdContext);

    streamsize i;
    do
    {
        file.read(buffer, File::bufferSize);
        i = file.gcount();
        MD5_Update(&mdContext, buffer, i);
    } while(i != 0);

    MD5_Final(digest, &mdContext);

    //Cleanup
    file.close();
    delete[] buffer;

    return Bin2HexString(digest, MD5_DIGEST_LENGTH, delim);
}

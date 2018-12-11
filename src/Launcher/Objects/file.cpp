#include "file.hpp"
#include <experimental/filesystem>
#include <fstream>
#include <ios>

using namespace std;
using namespace std::experimental;
using namespace OpenGMP;

File::File(const string &filename)
    : directory(filesystem::current_path())
    , filename(filename)
{}

File::File(const string &directory, const string &filename)
    : directory(directory)
    , filename(filename)
{}

bool File::Exists() const
{
    std::string fullpath = Fullpath();
    std::ifstream test(fullpath.c_str());
    return test.good();
}

std::string File::Fullpath() const
{
    filesystem::path fullpath;
    fullpath.assign(string(directory).append("/").append(filename));
    return fullpath.string();
}

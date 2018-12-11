#pragma once

#include <string>

namespace OpenGMP
{
    class File
    {
    public:
        File(const std::string &filename);
        File(const std::string &directory,
             const std::string &filename);

        bool Exists() const;

        std::string Fullpath() const;

    private:
        std::string filename;
        std::string directory;
    };
}

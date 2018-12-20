#pragma once

#include "file.hpp"
#include <string>

#define PHYSFS_GETERROR() PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode())

namespace OpenGMP
{
    class ZipFile : public File
    {
    public:
        ZipFile(const std::string &filename);

        ZipFile(const std::string &directory,
                const std::string &filename);

        ZipFile(const File &copy);

        /**
         * @brief Extract extracts the zip file to a directory.
         * @param to the directory to extract into.
         * @return true if the file was successfully extracted, false otherwise.
         */
        bool Extract(const std::string &to);
    };
}

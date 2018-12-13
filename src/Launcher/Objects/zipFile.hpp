#pragma once

#include <Shared/Objects/file.hpp>
#include <string>

namespace OpenGMP
{
    class ZipFile : public File
    {
    public:
        ZipFile(const std::string &filename);

        ZipFile(const std::string &filename,
                const std::string &directory);

        /**
         * @brief Extract extracts the zip file to a directory.
         * @param to the directory to extract into.
         * @return true if the file was successfully extracted, false otherwise.
         */
        bool Extract(const std::string &to);

    private:
    };
}

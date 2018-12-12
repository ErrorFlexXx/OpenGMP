#pragma once

#include <string>
#include <stdint.h>
#include <openssl/md5.h>

#define MEGA (1024 * 1024)

namespace OpenGMP
{    
    /**
     * @brief The File class contains basic file operations.
     */
    class File
    {
    public:
        File(const std::string &filename);
        File(const std::string &directory,
             const std::string &filename);

        /**
         * @brief Exists checks if this file exists on the filesystem, or not.
         * @return true if this file exists, false otherwise.
         */
        bool Exists() const;

        /**
         * @brief Fullpath returns a full path to this file.
         * @return the full path.
         */
        std::string Fullpath() const;

        /**
         * @brief Size returns the size of this file in bytes.
         * @return the size in bytes.
         */
        uintmax_t Size() const;

        /**
         * @brief Copy copies this file to another location.
         * @param to directory to copy this file to.
         * @return true if successfully copied, false otherwise.
         */
        bool Copy(const std::string &to) const;

        /**
         * @brief Move moves this file to another location.
         * @param to directory to move this file to.
         * @return true if moved successfull, false otherwise.
         */
        bool Move(const std::string &to) const;

        /**
         * @brief Delete deletes this file from the filesystem.
         * @return true if successfully deleted, false otherwise.
         */
        bool Delete() const;

        /**
         * @brief MD5 calculates the md5 checksum of this file.
         * @return MD5 checksum in Hex represenatation.
         */
        std::string MD5(const std::string &delim = "", bool upper = false) const;

        /**
         * @brief Touch creates an empty file.
         * @param overwrite set to true to overwrite the file, if it exists.
         * @return true if the empty file has been created, false otherwise.
         */
        bool Touch(bool overwrite = false) const;

    private:
        std::string directory;  //!< Directory this file lives in.
        std::string filename;   //!< filename of this file.
        static size_t bufferSize;    //!< Size of buffer for file operations.
    };
}

#pragma once

#include "file.hpp"

#define REDIRECT_LIMIT 3 //Allow three times redirection before canceling out.

namespace httplib
{
    class Client;
}

namespace OpenGMP
{
    class Url;

    class FileDownload : public File
    {
    public:
        FileDownload(const std::string &filename);
        FileDownload(const std::string &directory,
                     const std::string &filename);

        /**
         * @brief Download downloads a file from given url.
         * @param url to download the file from.
         * @return true if downloaded successfully.
         */
        bool Download(const std::string &url);

        /**
         * @brief DownloadHttp downloads a file with http protocol.
         * @param url to download the file from.
         * @return true if downloaded successfully.
         */
        bool DownloadHttp(const std::string &url);

        /**
         * @brief DownloadHttps downloads a file with https protocol.
         * @param url to download the file from.
         * @return true if downloaded sucessfully.
         */
        bool DownloadHttps(const std::string &url);

    protected:
        bool DownloadBase(httplib::Client &client, const Url &url);

    private:
        size_t redirectCount;   //!< Protection against infinite redirections
    };
}

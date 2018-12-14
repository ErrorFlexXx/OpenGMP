#pragma once

#include "file.hpp"
#include <mutex>

#define REDIRECT_LIMIT 3 //Allow three times redirection before canceling out.

//Forward declarations:
namespace std
{
    class thread;
}

namespace httplib
{
    class Client;
}

namespace OpenGMP
{
    class Url;

    /**
     * @brief The FileDownload class implements a blocking and non blocking way of a
     *   file download.
     */
    class FileDownload : public File
    {
    public:
        FileDownload(const std::string &filename);
        FileDownload(const std::string &directory,
                     const std::string &filename);

        /**
         * @brief ~FileDownload destroys this object. Waits for non blocking thread
         *   to finish, if any is running.
         */
        ~FileDownload();

        /**
         * @brief Download downloads a file from given url.
         * @param url to download the file from.
         * @return true if downloaded successfully.
         */
        bool Download(const std::string &url, bool blocking = false);

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

        /**
         * @brief DownloadFinished ask non blocking download, if it has finished.
         * @return true if finished, false otherwise.
         */
        bool DownloadFinished();

        /**
         * @brief DownloadResult ask non blocking download, if it has finished successfully.
         * @return true if finished and successfull, false otherwise.
         */
        bool DownloadResult();

    protected:
        bool DownloadBase(httplib::Client &client, const Url &url);

        /**
         * @brief ProgressUpdate called from download thread on progress update.
         * @param len currently downloaded bytes.
         * @param total total bytes of the download.
         */
        virtual void ProgressUpdate(uint64_t len, uint64_t total);

    private:
        std::thread *worker;    //!< Worker, if any.
        std::mutex lock;        //!< Lock for threaded cases.
        bool downloadPending;   //!< Pending flag of the download.
        bool downloadResult;    //!< Result of the download.
        size_t redirectCount;   //!< Protection against infinite redirections
    };
}

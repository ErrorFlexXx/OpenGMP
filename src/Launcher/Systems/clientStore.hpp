#pragma once

#include <string>
#include <list>
#include <QObject>
#include <mutex>
#include <Launcher/Objects/lserver.hpp>

namespace OpenGMP
{
    class Version;

    /**
     * @brief The ClientStore class manages installed client versions
     *   and can download new ones.
     */
    class ClientStore : public QObject
    {
        Q_OBJECT
    public:
        /**
         * @brief ClientStore creates a client Store with default installation dir.
         */
        ClientStore(QObject *parent = nullptr);

        bool IsInstalled(const Version &version) const;

    signals:
        /**
         * @brief ProgressBegin emitted if a progress action starts.
         * @param text to show initially.
         */
        void ProgressBegin(const QString &text);

        /**
         * @brief ProgressUpdate emitted if some progress is made.
         * @param progress percentual progress (0-100%)
         * @param text describing the current action.
         */
        void ProgressUpdate(int progress, const QString &text);

        /**
         * @brief ProgressUpdate emitted if some progress is made, without updating the text.
         * @param progress percentage of progress.
         */
        void ProgressUpdate(int progress);

        /**
         * @brief ProgressFinished emitted, if all actions are finished.
         */
        void ProgressFinished();

    public slots:
        /**
         * @brief Download starts a download of a client.
         * @param version that shall be downloaded.
         */
        void Download(const Version &version);

        /**
         * @brief Start does start a client instance with specified server.
         * @param server to connect to.
         */
        void Start(const OpenGMP::LServer &server);

        /**
         * @brief Subprogress slot to be called from clientStore slots.
         * @param percentage of current subprogress.
         */
        void Subprogress(int percentage);

        /**
         * @brief DownloadProgress updates a download progress.
         * @param len the current downloaded bytes.
         * @param total the total amount of download bytes.
         */
        void DownloadProgress(uint64_t len, uint64_t total);

    private:
        QObject *parent;
        std::string installationDir;    //!< Directory for installed clients.
        std::string downloadDir;        //!< Directory for new downloads.
        std::string storeUrl;           //!< Url to release directory
        int maxSubstepProgress;         //!< Progress percentage after current substep finished.

        bool CreateStore() const;

        std::string GetDownloadUrl(const OpenGMP::Version &version) const;
    };
}

#pragma once

#include <Shared/Utils/fileDownload.hpp>
#include <QObject>
#include <string>

namespace OpenGMP
{
    /**
     * @brief The QFileDownload class delivers the qt signal/slot interface for
     *   an instance of a FileDownload object.
     */
    class QFileDownload : public QObject, public FileDownload
    {
        Q_OBJECT
    public:
        explicit QFileDownload(QObject *parent = nullptr,
                               const std::string &directory = "",
                               const std::string &filename = "");

    signals:
        /**
         * @brief Progress signals the progress of this download.
         * @param len of currently downloaded bytes.
         * @param total bytes of the download file.
         */
        void Progress(uint64_t len, uint64_t total);

        /**
         * @brief Finished signals that the download has finished.
         * @param success true if it was successfull, false otherwise.
         */
        void Finished(bool success);

    public slots:
        /**
         * @brief StartDownload slot to start a download e.g. in a QThread.
         * @param url the file that shall be downloaded.
         */
        void StartDownload(const std::string &url);

    protected:
        /**
         * @brief ProgressUpdate override of default progress function from FileDownload.
         * @param len of currently downloaded bytes.
         * @param total bytes of the download file.
         */
        virtual void ProgressUpdate(uint64_t len, uint64_t total) override;

    };
}

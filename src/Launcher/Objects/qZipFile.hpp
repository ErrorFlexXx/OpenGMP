#pragma once

#include <Shared/Utils/zipFile.hpp>
#include <QObject>
#include <string>

namespace OpenGMP
{
    class QZipFile : public QObject, public ZipFile
    {
        Q_OBJECT

    public:
        explicit QZipFile(QObject *parent = nullptr,
                          const std::string &directory = "",
                          const std::string &filename = "");

        QZipFile(const File &copy);

        QZipFile(const QZipFile &copy);

    signals:
        /**
         * @brief finished signal emitted if the extraction finished.
         * @param success true if successfull, false otherwise.
         */
        void finished(bool success);

    public slots:
        /**
         * @brief StartExtract starts the extraction of the archive
         * @param to directory to extract the archive to.
         */
        void StartExtract(const std::string &to);
    };
}

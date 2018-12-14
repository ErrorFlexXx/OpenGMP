#pragma once

#include <string>
#include <list>
#include <QObject>

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

    public slots:
        void Download(const Version &version);

    private:
        std::string installationDir;    //!< Directory for installed clients.
        std::string downloadDir;        //!< Directory for new downloads.
        std::string storeUrl;           //!< Url to release directory

        bool CreateStore() const;
    };
}

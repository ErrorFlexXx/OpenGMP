#pragma once

#include <string>
#include <list>

namespace OpenGMP
{
    class Version;

    /**
     * @brief The ClientStore class manages installed client versions
     *   and can download new ones.
     */
    class ClientStore
    {
    public:
        /**
         * @brief ClientStore creates a client Store with default installation dir.
         */
        ClientStore();

        /**
         * @brief ClientStore creates a client Store with custom installation dir.
         * @param installationDir to store new and look for existing installations.
         * @param downloadDir to download new files to.
         */
        ClientStore(const std::string &installationDir,
                    const std::string &downloadDir);



    private:
        std::string installationDir;    //!< Directory for installed clients.
        std::string downloadDir;        //!< Directory for new downloads.
    };
}

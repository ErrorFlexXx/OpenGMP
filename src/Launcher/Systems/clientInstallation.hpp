#pragma once

#include <Shared/Components/version.hpp>
#include <string>

namespace OpenGMP
{
    /**
     * @brief The ClientInstallation class manages installations.
     *   Intended to check installations, get new versions, etc.
     */
    class ClientInstallation
    {
    public:
        ClientInstallation(Version &version);

        std::string installationDirectory;
        Version version;
    };
}

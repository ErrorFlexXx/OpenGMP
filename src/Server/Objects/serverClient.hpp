#pragma once

#include <Shared/Objects/client.hpp>

namespace OpenGMP
{
    /**
     * @defgroup scriptObject
     * @brief ScriptObjects Elements exposed to scripts
     */

    /**
     * @brief The ServerClient object
     * @ingroup scriptObject
     */
    class ServerClient : public Client
    {
    public:
        ServerClient();
        ~ServerClient();
    };
}

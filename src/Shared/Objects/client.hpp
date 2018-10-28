#pragma once

#include <string>
#include <BitStream.h>
#include "netIdObject.hpp"
#include "../Components/version.hpp"
#include "../Components/authData.hpp"
#include "../Components/id.hpp"
#include "../Components/netId.hpp"

namespace OpenGMP
{
    /**
     * @defgroup scriptObject
     * @brief ScriptObjects Elements exposed to scripts
     */

    /**
     * @brief The Client object
     * @ingroup scriptObject
     */
    class Client : public NetIdObject
    {
    public:
        Version version;    //!< (available script attribute) version of a client
        AuthData authData;  //!< (available script attribute) auth data of a client
    };
}

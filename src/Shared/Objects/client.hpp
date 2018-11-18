#pragma once

#include <string>
#include <BitStream.h>
#include "netIdObject.hpp"
#include "world.hpp"
#include "../Components/version.hpp"
#include "../Components/authData.hpp"
#include "../Components/loginData.hpp"
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
        Client()
            : NetIdObject() {}
        World world;        //!< world the client has loaded (as player or spectator)
        Version version;    //!< (available script attribute) version of a client
        AuthData authData;  //!< (available script attribute) auth data of a client
        LoginData loginData;//!< (available script attribute) login data of a client
    };
}

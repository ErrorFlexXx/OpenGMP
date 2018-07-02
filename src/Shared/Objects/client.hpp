#pragma once

#include <string>
#include <BitStream.h>
#include "netIdObject.hpp"
#include "../Components/version.hpp"
#include "../Components/authData.hpp"
#include "../Components/id.hpp"

namespace OpenGMP
{
    namespace Objects
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
            Components::Version version;   //!< (available script attribute) version of a client
            Components::AuthData authData; //!< (available script attribute) auth data of a client
        };
    }
}

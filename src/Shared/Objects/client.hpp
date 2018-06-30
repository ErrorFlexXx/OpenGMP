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
         * @describe The Client class
         *   This class covers a network client.
         */
        class Client : public NetIdObject
        {
        public:
            Components::Version version;   //!< Client version
            Components::AuthData authData; //!< Auth data of the client.
        };
    }
}

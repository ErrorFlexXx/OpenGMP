#pragma once

#include <MessageIdentifiers.h>

#define DBG_NETWORK

namespace OpenGMP
{
    namespace Types
    {
        enum NetworkSystemOrderingChannels : char
        {
            LoginSystemOrderingChannel = 1
        };

        enum NetworkSystemMessages : unsigned char
        {
            ClientPing = ID_USER_PACKET_ENUM,
            LoginSystem,
            MenuSystem
        };
    }
}

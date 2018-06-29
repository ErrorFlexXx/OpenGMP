#pragma once

#include <MessageIdentifiers.h>

namespace OpenGMP
{
    namespace Types
    {
        enum NetworkSystemMessages : unsigned char
        {
            ClientPing = ID_USER_PACKET_ENUM,
            LoginSystem
        };
    }
}

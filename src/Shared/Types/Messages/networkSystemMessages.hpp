#pragma once

#include <MessageIdentifiers.h>

#define DBG_NETWORK

typedef unsigned char NetMessage;

namespace OpenGMP
{
    enum NetworkSystemOrderingChannels : char
    {
        LoginSystemOrderingChannel = 1,
        MenuSystemOrderingChannel,
        WorldSystemOrderingChannel
    };

    enum NetworkSystemMessages : unsigned char
    {
        Ping = ID_USER_PACKET_ENUM,
        LoginSystem,
        MenuSystem,
        WorldSystem
    };
}

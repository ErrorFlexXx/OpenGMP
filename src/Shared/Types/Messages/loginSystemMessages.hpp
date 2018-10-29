#pragma once

#include "networkSystemMessages.hpp"

namespace OpenGMP
{
    enum LoginSystemMessages : unsigned char
    {
        BANNED,
        SERVERFULL,
        AUTH,
        AUTH_ACCEPTED,
        VERSION_INCOMPATIBLE,
        REGISTER
    };
}

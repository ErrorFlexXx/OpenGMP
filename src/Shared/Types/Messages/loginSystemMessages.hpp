#pragma once

#include "networkSystemMessages.hpp" //For the Debug Network definition

namespace OpenGMP
{
    namespace Types
    {        
        enum LoginSystemMessages : unsigned char
        {
            BANNED,
            SERVERFULL,
            AUTH,
            REGISTER
        };
    }
}

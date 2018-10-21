#pragma once

#include "networkSystemMessages.hpp" //For the Debug Network definition

namespace OpenGMP
{
    namespace Types
    {
        enum MenuSystemMessages : unsigned char
        {
            SHOW_NOTIFICATION,
            SHOW_TIMED_NOTIFICATION,
            HIDE_NOTIFICATION
        };
    }
}

#pragma once

#include <Shared/Objects/iStreamObject.hpp>
#include "color.hpp"
#include <string>
#include <stdint.h>

namespace OpenGMP
{
    class NotificationText
    {
    public:
        NotificationText();

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);

        std::string text;
        uint32_t posY;
        Color color;
        uint32_t duration;
    };
}

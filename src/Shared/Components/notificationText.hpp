#pragma once

#include <Shared/Objects/iStreamObject.hpp>
#include <Shared/Types/string.hpp>
#include "color.hpp"
#include <stdint.h>

namespace OpenGMP
{
    class NotificationText
    {
    public:
        NotificationText();
        NotificationText(const std::string &text, uint32_t posY, const Color &color, uint32_t duration);

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);

        String text;
        uint32_t posY;
        Color color;
        uint32_t duration;
    };
}

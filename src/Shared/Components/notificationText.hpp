#pragma once

#include <Shared/Objects/IStreamObject.hpp>
#include "color.hpp"
#include <string>
#include <stdint.h>

namespace OpenGMP
{
    namespace Components
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
}
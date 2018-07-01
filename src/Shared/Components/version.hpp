#pragma once

#include "../Objects/iStreamObject.hpp"
#include <stdint.h>

namespace OpenGMP
{
    namespace Components
    {
        class Version : public IStreamObject
        {
        public:
            Version();
            Version(uint32_t version);
            Version(const uint8_t &major, const uint16_t &minor, const uint16_t &patch);

            uint32_t version;

            void WriteStream(RakNet::BitStream &stream) const;
            bool ReadStream(RakNet::BitStream &stream);
        };
    }
}

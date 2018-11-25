#pragma once

#include <stdint.h>

namespace RakNet
{
    class BitStream;
}

namespace OpenGMP
{
    class Version
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

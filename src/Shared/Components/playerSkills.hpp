#pragma once

#include <stdint.h>

namespace RakNet
{
    class BitStream;
}

namespace OpenGMP
{
    class PlayerSkills
    {
    public:
        PlayerSkills();

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);

        int32_t skill_1h;
        int32_t skill_2h;
        int32_t skill_bow;
        int32_t skill_cbow;
    };
}

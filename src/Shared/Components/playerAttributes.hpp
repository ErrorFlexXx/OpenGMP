#pragma once

#include <stdint.h>

namespace RakNet
{
    class BitStream;
}

namespace OpenGMP
{
    class PlayerAttributes
    {
    public:
        int32_t level;
        int32_t learn_points;
        int32_t experience;
        int32_t experience_next_level;
        int32_t magic_level;
        int32_t health;
        int32_t max_health;
        int32_t mana;
        int32_t max_mana;
        int32_t strength;
        int32_t dexterity;

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);
    };
}

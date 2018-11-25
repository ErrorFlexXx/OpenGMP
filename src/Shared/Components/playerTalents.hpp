#pragma once

#include <stdint.h>

namespace RakNet
{
    class BitStream;
}

namespace OpenGMP
{
    class PlayerTalents
    {
    public:
        typedef enum EnumTalents
        {
            Sneaking = 0,
            Thief,
            OpeningLocks,
            SloshBlades,
            CreatingRunes,
            Alchemy,
            CollectingTrophies,
            Acrobatics,
            TALENTS_MAX = 32
        } EnumTalents;

        PlayerTalents();
        uint32_t HasTalent(EnumTalents talent);
        void SetTalent(EnumTalents talent);
        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);

        uint32_t talents;
    };
}

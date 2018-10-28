#pragma once

#include "../Objects/iStreamObject.hpp"

namespace OpenGMP
{
    class PlayerTalents : public IStreamObject
    {
    public:
        typedef enum EnumTalents
        {
            Sneaking,
            Thief,
            OpeningLocks,
            SloshBlades,
            CreatingRunes,
            Alchemy,
            CollectingTrophies,
            Acrobatics
        } EnumTalents;

        int HasTalent(EnumTalents talent);
        void SetTalent(EnumTalents talent);
        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);

        int talents;
    };
}

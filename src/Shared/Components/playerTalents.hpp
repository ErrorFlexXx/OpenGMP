#pragma once

#include "../Objects/iStreamObject.hpp"

namespace OpenGMP
{
    namespace Components
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
            void ReadStream(RakNet::BitStream &stream);

            int talents;
        };
    }
}

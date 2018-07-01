#pragma once

#include "../Objects/iStreamObject.hpp"

namespace OpenGMP
{
    namespace Components
    {
        class PlayerSkills : public IStreamObject
        {
        public:
            int skill_1h;
            int skill_2h;
            int skill_bow;
            int skill_cbow;

            void WriteStream(RakNet::BitStream &stream) const;
            void ReadStream(RakNet::BitStream &stream);
        };
    }
}

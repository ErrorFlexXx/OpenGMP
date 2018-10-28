#pragma once

#include "../Objects/iStreamObject.hpp"
#include <stdint.h>

namespace OpenGMP
{
    class PlayerSkills : public IStreamObject
    {
    public:
        int32_t skill_1h;
        int32_t skill_2h;
        int32_t skill_bow;
        int32_t skill_cbow;

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);
    };
}

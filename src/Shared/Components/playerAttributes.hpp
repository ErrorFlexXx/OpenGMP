#pragma once

#include "../Objects/iStreamObject.hpp"

namespace OpenGMP
{
    namespace Components
    {
        class PlayerAttributes : public IStreamObject
        {
        public:
            int level;
            int learn_points;
            int experience;
            int experience_next_level;
            int magic_level;
            int health;
            int max_health;
            int mana;
            int max_mana;
            int strength;
            int dexterity;

            void WriteStream(RakNet::BitStream &stream) const;
            void ReadStream(RakNet::BitStream &stream);
        };
    }
}

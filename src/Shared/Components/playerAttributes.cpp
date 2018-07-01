#include "playerAttributes.hpp"

using namespace OpenGMP::Components;

void PlayerAttributes::WriteStream(RakNet::BitStream &stream) const
{
    stream.Write(level);
    stream.Write(learn_points);
    stream.Write(experience);
    stream.Write(experience_next_level);
    stream.Write(magic_level);
    stream.Write(health);
    stream.Write(max_health);
    stream.Write(mana);
    stream.Write(max_mana);
    stream.Write(strength);
    stream.Write(dexterity);
}

void PlayerAttributes::ReadStream(RakNet::BitStream &stream)
{
    stream.Read(level);
    stream.Read(learn_points);
    stream.Read(experience);
    stream.Read(experience_next_level);
    stream.Read(magic_level);
    stream.Read(health);
    stream.Read(max_health);
    stream.Read(mana);
    stream.Read(max_mana);
    stream.Read(strength);
    stream.Read(dexterity);
}

#include "playerAttributes.h"

PlayerAttributes::PlayerAttributes()
    : level(0)
    , learn_points(0)
    , experience(0)
    , experience_next_level(0)
    , magic_level(0)
    , health(0)
    , max_health(0)
    , mana(0)
    , max_mana(0)
    , strength(0)
    , dexterity(0)
{}

void PlayerAttributes::WriteStream(RakNet::BitStream &stream)
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
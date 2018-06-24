#include "playerSkills.h"

PlayerSkills::PlayerSkills()
    : skill_1h(0)
    , skill_2h(0)
    , skill_bow(0)
    , skill_cbow(0)
{}

void PlayerSkills::WriteStream(RakNet::BitStream &stream)
{
    stream.Write(skill_1h);
    stream.Write(skill_2h);
    stream.Write(skill_bow);
    stream.Write(skill_cbow);
}

void PlayerSkills::ReadStream(RakNet::BitStream &stream)
{
    stream.Read(skill_1h);
    stream.Read(skill_2h);
    stream.Read(skill_bow);
    stream.Read(skill_cbow);
}
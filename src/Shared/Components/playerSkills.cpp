#include "playerSkills.hpp"

using namespace OpenGMP::Components;

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

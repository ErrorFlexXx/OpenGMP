#include "playerSkills.hpp"
#include <BitStream.h>

using namespace OpenGMP;

PlayerSkills::PlayerSkills()
        : skill_1h(0)
        , skill_2h(0)
        , skill_bow(0)
        , skill_cbow(0)
{}

void PlayerSkills::WriteStream(RakNet::BitStream &stream) const
{
    stream.Write(skill_1h);
    stream.Write(skill_2h);
    stream.Write(skill_bow);
    stream.Write(skill_cbow);
}

bool PlayerSkills::ReadStream(RakNet::BitStream &stream)
{
    bool success;

                success = stream.Read(skill_1h);
    if(success) success = stream.Read(skill_2h);
    if(success) success = stream.Read(skill_bow);
    if(success) success = stream.Read(skill_cbow);

    return success;
}

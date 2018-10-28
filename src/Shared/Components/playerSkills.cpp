#include "playerSkills.hpp"

using namespace OpenGMP;

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

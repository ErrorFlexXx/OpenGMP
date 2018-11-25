#include "playerAttributes.hpp"
#include <BitStream.h>

using namespace OpenGMP;

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

bool PlayerAttributes::ReadStream(RakNet::BitStream &stream)
{
    bool success;

                success = stream.Read(level);
    if(success) success = stream.Read(learn_points);
    if(success) success = stream.Read(experience);
    if(success) success = stream.Read(experience_next_level);
    if(success) success = stream.Read(magic_level);
    if(success) success = stream.Read(health);
    if(success) success = stream.Read(max_health);
    if(success) success = stream.Read(mana);
    if(success) success = stream.Read(max_mana);
    if(success) success = stream.Read(strength);
    if(success) success = stream.Read(dexterity);

    return success;
}

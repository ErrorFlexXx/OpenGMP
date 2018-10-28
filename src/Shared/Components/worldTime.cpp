#include "worldTime.hpp"

using namespace OpenGMP;

void WorldTime::WriteStream(RakNet::BitStream &stream) const
{
    stream.Write(totalSeconds);
}

bool WorldTime::ReadStream(RakNet::BitStream &stream)
{
    bool success;

    success = stream.Read(totalSeconds);

    return success;
}

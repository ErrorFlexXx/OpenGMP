#include "worldTime.hpp"

WorldTime::WorldTime(int totalSeconds)
    : totalSeconds(totalSeconds)
{}


void WorldTime::WriteStream(RakNet::BitStream &stream)
{
    stream.Write(totalSeconds);
}

void WorldTime::ReadStream(RakNet::BitStream &stream)
{
    stream.Read(totalSeconds);
}

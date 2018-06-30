#include "worldTime.hpp"

using namespace OpenGMP::Components;

void WorldTime::WriteStream(RakNet::BitStream &stream)
{
    stream.Write(totalSeconds);
}

void WorldTime::ReadStream(RakNet::BitStream &stream)
{
    stream.Read(totalSeconds);
}

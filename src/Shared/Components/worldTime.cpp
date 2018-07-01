#include "worldTime.hpp"

using namespace OpenGMP::Components;

void WorldTime::WriteStream(RakNet::BitStream &stream) const
{
    stream.Write(totalSeconds);
}

void WorldTime::ReadStream(RakNet::BitStream &stream)
{
    stream.Read(totalSeconds);
}

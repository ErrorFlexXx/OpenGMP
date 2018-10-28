#include "netId.hpp"

using namespace OpenGMP;

void NetId::WriteStream(RakNet::BitStream &stream) const
{   //Never transmitted
}

bool NetId::ReadStream(RakNet::BitStream &stream)
{   //Never transmitted
    return true;
}

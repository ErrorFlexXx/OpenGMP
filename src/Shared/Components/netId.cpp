#include "netId.hpp"

using namespace OpenGMP::Components;

void NetId::WriteStream(RakNet::BitStream &stream) const
{   //Never transmitted
}

bool NetId::ReadStream(RakNet::BitStream &stream)
{   //Never transmitted
    return true;
}

RakNet::RakNetGUID NetId::GetRakNetId() const
{
    return rakNetId;
}

void NetId::SetRakNetId(const RakNet::RakNetGUID &value)
{
    rakNetId = value;
}

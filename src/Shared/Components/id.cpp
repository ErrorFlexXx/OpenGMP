#include "id.hpp"

using namespace OpenGMP::Components;

Id::Id()
    : id(-1) //used for unassigned checking in container systems. Do not change.
{}

void Id::WriteStream(RakNet::BitStream &stream) const
{
    stream.Write(id);
}

void Id::ReadStream(RakNet::BitStream &stream)
{
    stream.Read(id);
}

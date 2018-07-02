#include "id.hpp"

using namespace OpenGMP::Components;

Id::Id()
    : id(-1) //used for unassigned checking in container systems. Do not change.
{}

void Id::WriteStream(RakNet::BitStream &stream) const
{
    stream.Write(id);
}

bool Id::ReadStream(RakNet::BitStream &stream)
{
    bool success = stream.Read(id);
    return success;
}

int Id::GetId() const
{
    return id;
}

void Id::SetId(int value)
{
    id = value;
}

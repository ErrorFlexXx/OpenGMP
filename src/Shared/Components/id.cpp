#include "id.hpp"
#include <BitStream.h>

using namespace OpenGMP;

Id::Id()
    : id(-1) //used for unassigned checking in container systems. Do not change.
{}

Id::Id(int value)
{
    id = value;
}

Id::Id(RakNet::BitStream &stream)
{
    ReadStream(stream);
}

void Id::WriteStream(RakNet::BitStream &stream) const
{
    stream.Write(id);
}

bool Id::ReadStream(RakNet::BitStream &stream)
{
    bool success = stream.Read(id);
    return success;
}

std::ostream & operator<< (std::ostream &out, const OpenGMP::Id &t)
{
    out << t.id;
    return out;
}

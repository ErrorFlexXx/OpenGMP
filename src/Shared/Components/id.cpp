#include "id.h"

Id::Id(int id)
    :id(id)
{}

void Id::WriteStream(RakNet::BitStream &stream)
{
    stream.Write(id);
}

void Id::ReadStream(RakNet::BitStream &stream)
{
    stream.Read(id);
}
#include "scale.h"

Scale::Scale(float x, float y, float z)
    : x(x)
    , y(y)
    , z(z)
{}

void Scale::WriteStream(RakNet::BitStream &stream)
{
    stream.Write(x);
    stream.Write(y);
    stream.Write(z);
}

void Scale::ReadStream(RakNet::BitStream &stream)
{
    stream.Read(x);
    stream.Read(y);
    stream.Read(z);
}
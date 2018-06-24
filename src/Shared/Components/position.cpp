#include "position.h"

Position::Position(float x, float y, float z, float angle)
    : x(x)
    , y(y)
    , z(z)
    , angle(angle)
{}

void Position::WriteStream(RakNet::BitStream &stream)
{
    stream.Write(x);
    stream.Write(y);
    stream.Write(z);
    stream.Write(angle);
}

void Position::ReadStream(RakNet::BitStream &stream)
{
    stream.Read(x);
    stream.Read(y);
    stream.Read(z);
    stream.Read(angle);
}
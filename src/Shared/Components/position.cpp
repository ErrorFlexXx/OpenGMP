#include "position.hpp"

using namespace OpenGMP;

Position::Position()
    : x(0.f)
    , y(0.f)
    , z(0.f)
    , angle(0.f)
{}

Position::Position(float x, float y, float z, float angle)
    : x(x)
    , y(y)
    , z(z)
    , angle(angle)
{}

Position::Position(RakNet::BitStream &stream)
{
    ReadStream(stream);
}

Position & Position::operator+=(const Position &rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    angle += rhs.angle;
}

void Position::WriteStream(RakNet::BitStream &stream) const
{
    stream.Write(x);
    stream.Write(y);
    stream.Write(z);
    stream.Write(angle);
}

bool Position::ReadStream(RakNet::BitStream &stream)
{
    bool success;

                success = stream.Read(x);
    if(success) success = stream.Read(y);
    if(success) success = stream.Read(z);
    if(success) success = stream.Read(angle);

    return success;
}

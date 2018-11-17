#include "vec3.hpp"

using namespace OpenGMP;

Vec3::Vec3()
    : x(0.f)
    , y(0.f)
    , z(0.f)
{}

Vec3::Vec3(float x, float y, float z)
    : x(x)
    , y(y)
    , z(z)
{}

Vec3::Vec3(RakNet::BitStream &stream)
{
    ReadStream(stream);
}

void Vec3::WriteStream(RakNet::BitStream &stream) const
{
    stream.Write(x);
    stream.Write(y);
    stream.Write(z);
}

bool Vec3::ReadStream(RakNet::BitStream &stream)
{
    bool success;

                success = stream.Read(x);
    if(success) success = stream.Read(y);
    if(success) success = stream.Read(z);

    return success;
}

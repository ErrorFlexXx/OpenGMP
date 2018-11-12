#include "scale.hpp"

using namespace OpenGMP;

Scale::Scale()
    : x(1.f)
    , y(1.f)
    , z(1.f)
{}

Scale::Scale(float x, float y, float z)
    : x(x)
    , y(y)
    , z(z)
{}

void Scale::WriteStream(RakNet::BitStream &stream) const
{
    stream.Write(x);
    stream.Write(y);
    stream.Write(z);
}

bool Scale::ReadStream(RakNet::BitStream &stream)
{
    bool success;

                success = stream.Read(x);
    if(success) success = stream.Read(y);
    if(success) success = stream.Read(z);

    return success;
}

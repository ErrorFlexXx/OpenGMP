#include "position.hpp"

using namespace OpenGMP;

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

#include "scale.hpp"

using namespace OpenGMP::Components;

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

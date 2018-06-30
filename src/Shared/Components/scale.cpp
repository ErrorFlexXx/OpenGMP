#include "scale.hpp"

using namespace OpenGMP::Components;

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

#include "string.hpp"
#include <RakString.h>

using namespace RakNet;
using namespace OpenGMP;

void String::WriteStream(BitStream &stream) const
{
    RakString rakString("%s", text.c_str());

    stream.Write(rakString);
}

bool String::ReadStream(BitStream &stream)
{
    RakString rakString;
    bool success;

    success = stream.Read(rakString);

    if(success)
    {
        text = rakString;
    }
    return success;
}

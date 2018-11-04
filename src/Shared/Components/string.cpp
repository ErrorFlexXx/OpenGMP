#include "string.hpp"
#include <RakString.h>

using namespace RakNet;
using namespace OpenGMP;

String::String()
{}

String::String(const char *value)
{
    text = value;
}

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

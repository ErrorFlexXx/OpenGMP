#include "string.hpp"
#include <RakString.h>

using namespace RakNet;
using namespace OpenGMP;

String::String()
    : text("")
{}

String::String(const std::string &value)
{
    text = value;
}

String::String(const char *value)
    : text(value)
{}

String & String::operator<< (float arg)
{
    this->text.append(std::to_string(arg));
    return *this;
}

String &String::operator<< (const String &arg)
{
    this->text.append(arg.text);
    return *this;
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

std::ostream & operator<< (std::ostream &out, const OpenGMP::String &t)
{
    out << t.text;
    return out;
}

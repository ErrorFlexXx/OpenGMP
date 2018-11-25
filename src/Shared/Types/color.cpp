#include "color.hpp"
#include <BitStream.h>

using namespace OpenGMP;

//Static colors:
const Color Color::White = Color(255, 255, 255, 255);
const Color Color::Black = Color(0, 0, 0, 255);
const Color Color::Red = Color(255, 0, 0, 255);
const Color Color::Green = Color(0, 255, 0, 255);
const Color Color::Blue = Color(0, 0, 255, 255);
const Color Color::Grey = Color(155, 155, 155, 255);
const Color Color::Yellow = Color(255, 255, 0, 255);
const Color Color::Orange = Color(255, 165, 0, 255);

Color::Color()
    : Color(255, 255, 255, 255)
{
}

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    : r(r)
    , g(g)
    , b(b)
    , a(a)
{}

void Color::WriteStream(RakNet::BitStream &stream) const
{
    stream.Write(r);
    stream.Write(g);
    stream.Write(b);
    stream.Write(a);
}

bool Color::ReadStream(RakNet::BitStream &stream)
{
    bool success;

                success = stream.Read(r);
    if(success) success = stream.Read(g);
    if(success) success = stream.Read(b);
    if(success) success = stream.Read(a);

    return success;
}

#include "color.h"

Color::Color() : Color(255, 255, 255) {}

Color::Color(unsigned char r, unsigned char g, unsigned char b) : Color(r, g, b, 255) {}

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    : r(r)
    , g(g)
    , b(b)
    , a(a)
{}

void Color::WriteStream(RakNet::BitStream &stream)
{
    stream.Write(r);
    stream.Write(g);
    stream.Write(b);
    stream.Write(a);
}

void Color::ReadStream(RakNet::BitStream &stream)
{
    stream.Read(r);
    stream.Read(g);
    stream.Read(b);
    stream.Read(a);
}
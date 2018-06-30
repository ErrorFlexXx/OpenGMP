#include "color.hpp"

using namespace OpenGMP::Components;

Color::Color()
    : Color(255, 255, 255, 255)
{
}

Color::Color(const unsigned char &r, const unsigned char &g, const unsigned char &b, const unsigned char &a)
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

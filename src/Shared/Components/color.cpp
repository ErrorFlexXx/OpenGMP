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

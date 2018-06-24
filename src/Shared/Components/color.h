#pragma once

#include "../Objects/iStreamObject.hpp"

/**
 * @describe The Color class
 *   Covers a r, g, b, a color.
 */
class Color : public IStreamObject
{
public:
    Color();
    Color(unsigned char r, unsigned char g, unsigned char b);
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

    virtual void WriteStream(RakNet::BitStream &stream) override;
    virtual void ReadStream(RakNet::BitStream &stream) override;

    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

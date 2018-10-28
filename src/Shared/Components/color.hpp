#pragma once

#include "../Objects/iStreamObject.hpp"

namespace OpenGMP
{
    /**
     * @describe The Color class
     *   Covers a r, g, b, a color.
     */
    class Color : public IStreamObject
    {
    public:
        Color();
        Color(const unsigned char &r, const unsigned char &g, const unsigned char &b, const unsigned char &a);

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);

        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
}

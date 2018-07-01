#pragma once

#include "../Objects/iStreamObject.hpp"

namespace OpenGMP
{
    namespace Components
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

            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
        };
    }
}

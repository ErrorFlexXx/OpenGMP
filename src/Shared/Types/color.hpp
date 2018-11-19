#pragma once

#include "../Objects/iStreamObject.hpp"

namespace OpenGMP
{
    /**
     * @brief The Color class
     */
    class Color : public IStreamObject
    {
    public:
        Color();
        Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);

        static const Color White;   //!< constant for a white color.
        static const Color Black;   //!< constant for a black color.
        static const Color Red;     //!< constant for a red color.
        static const Color Green;   //!< constant for a green color.
        static const Color Blue;    //!< constant for a blue color.
        static const Color Grey;    //!< constant for a grey color.
        static const Color Yellow;  //!< constant for a yellow color.
        static const Color Orange;  //!< constant for an orange color.

        uint8_t r; //!< the red color component.
        uint8_t g; //!< the green color component.
        uint8_t b; //!< the blue color component.
        uint8_t a; //!< the alpha color component.
    };
}

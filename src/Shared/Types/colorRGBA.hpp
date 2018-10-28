#pragma once

namespace OpenGMP
{
    /**
     * @brief The ColorRGBA class
     *  This class covers objects of color with color components red, green, blue and alpha.
     */
    class ColorRGBA
    {
    public:
        /**
         * @brief ColorRGBA constructor without alpha (defaults 255).
         * @param r the red component.
         * @param g the green component.
         * @param b the blue component.
         */
        ColorRGBA(const unsigned char r,const unsigned char g,const unsigned char b);

        /**
         * @brief ColorRGBA complete constructor.
         * @param r the red component.
         * @param g the green component.
         * @param b the blue component.
         * @param a the alpha component.
         */
        ColorRGBA(const unsigned char r, const unsigned char g, const unsigned char b,const unsigned char a);

        /**
         * @brief set setter for the object.
         * @param r the red component.
         * @param g the green component.
         * @param b the blue component.
         * @param a the alpha component.
         */
        void set(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a);

        /**
         * @brief r
         * @return the red component.
         */
        unsigned char r() const;

        /**
         * @brief g
         * @return the green component.
         */
        unsigned char g() const;

        /**
         * @brief b
         * @return the blue component.
         */
        unsigned char b() const;

        /**
         * @brief a
         * @return the alpha component.
         */
        unsigned char a() const;

        static const ColorRGBA White;   //!< constant for a white color.
        static const ColorRGBA Black;   //!< constant for a black color.
        static const ColorRGBA Red;     //!< constant for a red color.
        static const ColorRGBA Green;   //!< constant for a green color.
        static const ColorRGBA Blue;    //!< constant for a blue color.
        static const ColorRGBA Grey;    //!< constant for a grey color.
        static const ColorRGBA Yellow;  //!< constant for a yellow color.
        static const ColorRGBA Orange;  //!< constant for an orange color.

    private:
        unsigned char m_r; //!< Red color component
        unsigned char m_g; //!< Green color component
        unsigned char m_b; //!< Blue color component
        unsigned char m_a; //!< Alpha color component
    };
}

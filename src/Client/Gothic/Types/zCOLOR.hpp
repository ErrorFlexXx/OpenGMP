#pragma once

#include "../xcall.h"
#include "zSTRING.hpp"

class zCOLOR
{
public:
    /**
     * @brief Constructs a color with default values (white, without transparency)
     */
    zCOLOR()
        : m_r(255)
        , m_g(255)
        , m_b(255)
        , m_a(255)
    {
    }

    /**
     * @brief Constructs a color from an int value.
     * @param color describes the whole color in the string like: 0xBBGGRRAA
     */
    zCOLOR::zCOLOR(int color)
    {
        XCALL(0x00401F20);
    }

    /**
     * @brief Constructs a color from unsigned char values.
     */
    zCOLOR(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        XCALL(0x0078AEF0);
    }

    /**
     * @brief Reset: Sets all components to zero.
     */
    void Reset(void)
    {
        XCALL(0x00572900);
    }

    /**
     * @brief GetDescription: Creates and returns a textual description of the color components.
     */
    zSTRING GetDescription() const
    {
        XCALL(0x005FABA0);
    }

    /**
     * @brief SetByDescription(zSTRING): Set's the color attributes from a textual description.
     */
    void SetByDescription(zSTRING const &)
    {
        XCALL(0x005FAF10);
    }

    /**
     * @brief GetDescriptionRGB: Creates and returns a textual description from the components R, G, B
     */
    zSTRING GetDescriptionRGB() const
    {
        XCALL(0x005FB190);
    }

    /**
     * @brief SetRGB: Sets the components r, g and b.
     */
    void SetRGB(unsigned char r, unsigned char g, unsigned char b)
    {
        XCALL(0x0062A740);
    }

    /**
     * @brief Returns the current red value.
     */
    unsigned char r()
    {
        return m_r;
    }

    /**
     * @brief Returns the current green value.
     */
    unsigned char g()
    {
        return m_g;
    }

    /**
     * @brief Returns the current blue value.
     */
    unsigned char b()
    {
        return m_b;
    }

    /**
     * @brief Returns the current alpha value.
     */
    unsigned char a()
    {
        return m_a;
    }

private:
    unsigned char m_b; //!< The blue component.
    unsigned char m_g; //!< The green component.
    unsigned char m_r; //!< The red component.
    unsigned char m_a; //!< The alpha/opacity/transparency component.
};

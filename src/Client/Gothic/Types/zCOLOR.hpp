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

/* Some colors from GII data segment: */
zCOLOR *zCOLOR_RED();
zCOLOR *zCOLOR_PALEGREEN();
zCOLOR *zCOLOR_SKY();
zCOLOR *zCOLOR_BROWN();
zCOLOR *zCOLOR_DOCHRE();
zCOLOR *zCOLOR_GREEN();
zCOLOR *zCOLOR_IVORY();
zCOLOR *zCOLOR_YELLOW();
zCOLOR *zCOLOR_PINK();
zCOLOR *zCOLOR_ORCHID();
zCOLOR *zCOLOR_DGREEN();
zCOLOR *zCOLOR_OCHRE();
zCOLOR *zCOLOR_PURPLE();
zCOLOR *zCOLOR_ORANGE();
zCOLOR *zCOLOR_BLACK();
zCOLOR *zCOLOR_BLUE();
zCOLOR *zCOLOR_DPINK();
zCOLOR *zCOLOR_AQUA();
zCOLOR *zCOLOR_FLESH();
zCOLOR *zCOLOR_LPINK();
zCOLOR *zCOLOR_STEEL();
zCOLOR *zCOLOR_DBLUE();
zCOLOR *zCOLOR_VIOLET();
zCOLOR *zCOLOR_DRED();
zCOLOR *zCOLOR_LBLUE();
zCOLOR *zCOLOR_WARMGREY();
zCOLOR *zCOLOR_CYAN();
zCOLOR *zCOLOR_KHAKI();
zCOLOR *zCOLOR_INDIGO();
zCOLOR *zCOLOR_LYELLOW();
zCOLOR *zCOLOR_COLDGREY();
zCOLOR *zCOLOR_CARROT();
zCOLOR *zCOLOR_GOLD();
zCOLOR *zCOLOR_WHITE();
zCOLOR *zCOLOR_GREY();
zCOLOR *zCOLOR_MBLUE();
zCOLOR *zCOLOR_MAGENTA();
zCOLOR *zCOLOR_OLIVE();
zCOLOR *zCOLOR_BEIGE();
zCOLOR *zCOLOR_LGREY();
zCOLOR *zCOLOR_DORANGE();

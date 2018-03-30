#pragma once

#include "../xcall.h"

class zVEC3;

class zVEC4
{
public:
    float components[4];

    zVEC4::zVEC4()
    {
        XCALL(0x00479B50);
    }

    zVEC4(const zVEC4  &copy)
    {
        XCALL(0x00483980);
    }

    zVEC4(float a, float b, float c, float d)
    {
        XCALL(0x004B4140);
    }

    zVEC4(const zVEC3 &init, float unknown)
    {
        XCALL(0x005B8580);
    }

    float LengthApprox()
    {
        XCALL(0x005133A0);
    }

    zVEC4 & Normalize()
    {
        XCALL(0x00513480);
    }

    zVEC4 & Apply(float(__cdecl*func)(float))
    {
        XCALL(0x005134D0);
    }
};
#include "zVEC3.hpp"

zVEC3 __cdecl RotateVec(class zVEC3 &, class zVEC3 &, float, float)
{
    XCALL(0x00735A40);
}

zVEC3 __cdecl zLerp(float, class zVEC3 const &, class zVEC3 const)
{
    XCALL(0x005D0690);
}

zVEC3 __cdecl operator*(class zVEC3 const &, class zMAT4 const &)
{
    XCALL(0x0054B130);
}

zVEC3 __cdecl operator*(class zMAT3 const &, class zVEC3 const &)
{
    XCALL(0x00514780);
}

zVEC3 __cdecl operator-(class zVEC3 const &)
{
    XCALL(0x004B9DD0);
}

zVEC3 __cdecl operator/(class zVEC3 const &, float)
{
    XCALL(0x004B6AF0);
}

zVEC3 __cdecl operator^(class zVEC3 const &, class zVEC3 const &)
{
    XCALL(0x00498A80);
}

zVEC3 __cdecl operator-(class zVEC3 const &, class zVEC3 const &)
{
    XCALL(0x004889F0);
}

zVEC3 __cdecl operator+(class zVEC3 const &, class zVEC3 const &)
{
    XCALL(0x00478990);
}

zVEC3 __cdecl operator*(class zVEC3 const &, float)
{
    XCALL(0x00475170);
}

zVEC3 __cdecl operator*(class zMAT4 const &, class zVEC3 const &)
{
    XCALL(0x00474370);
}

zVEC3 __cdecl Alg_Prod(class zVEC3 const &, class zVEC3 const &)
{
    XCALL(0x00513370);
}

zVEC3 __cdecl Alg_Min(class zVEC3 const &, class zVEC3 const &)
{
    XCALL(0x00513290);
}

zVEC3 __cdecl Alg_Max(class zVEC3 const &, class zVEC3 const &)
{
    XCALL(0x00513300);
}

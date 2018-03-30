#include "zVEC2.hpp"

zVEC2 __cdecl operator*(class zVEC2 const &, float)
{
    XCALL(0x00499480);
}

float __cdecl operator*(class zVEC2 const &, class zVEC2 const &)
{
    XCALL(0x004B4E20);
}

class zVEC2 __cdecl Alg_Min(class zVEC2 const &, class zVEC2 const &)
{
    XCALL(0x00512FC0);
}

class zVEC2 __cdecl Alg_Max(class zVEC2 const &, class zVEC2 const &)
{
    XCALL(0x00513010);
}

class zVEC2 __cdecl Alg_Prod(class zVEC2 const &, class zVEC2 const &)
{
    XCALL(0x00513060);
}

class zVEC2 __cdecl operator+(class zVEC2 const &, class zVEC2 const &)
{
    XCALL(0x0056CB80);
}

class zVEC2 __cdecl operator-(class zVEC2 const &, class zVEC2 const &)
{
    XCALL(0x006011C0);
}
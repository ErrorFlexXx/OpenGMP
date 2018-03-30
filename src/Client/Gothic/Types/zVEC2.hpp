#pragma once

#include "../xcall.h"
#include "zSTRING.hpp"

class zVEC2
{
public:
    /////////////////////
    // Constructors    //
    /////////////////////
    zVEC2()
    {
        XCALL(0x00788490);
    }

    zVEC2(float x, float y)
    {
        XCALL(0x004B4DC0);
    }

    zVEC2(class zVEC2 const &)
    {
        XCALL(0x0052ED60);
    }

    /////////////////////
    // Methods         //
    /////////////////////

    float Length2()
    {
        XCALL(0x004B4E00);
    }
    
    zSTRING GetDescription(void) const
    {
        XCALL(0x00512A30);
    }
    
    void SetByDescription(class zSTRING const &)
    {
        XCALL(0x00512C70);
    }
    
    zVEC2 & Apply(float(__cdecl*)(float))
    {
        XCALL(0x00512A10);
    }

    /////////////////////
    // Operators       //
    /////////////////////

    zVEC2 & operator+=(class zVEC2 const &)
    {
        XCALL(0x005B02F0);
    }
        
    zVEC2 & operator-=(class zVEC2 const &)
    {
        XCALL(0x00691020);
    }
        
    zVEC2 & operator*=(float)
    {
        XCALL(0x00691040);
    }
        
    zVEC2 & operator/=(float)
    {
        XCALL(0x004B4DE0);
    }

private:
    float x; //!< The first component of the vector.
    float y; //!< The second component of the vector.
};

//Non member operators:
zVEC2 __cdecl operator*(class zVEC2 const &, float);
float __cdecl operator*(class zVEC2 const &, class zVEC2 const &);
class zVEC2 __cdecl Alg_Min(class zVEC2 const &, class zVEC2 const &);
class zVEC2 __cdecl Alg_Max(class zVEC2 const &, class zVEC2 const &);
class zVEC2 __cdecl Alg_Prod(class zVEC2 const &, class zVEC2 const &);
class zVEC2 __cdecl operator+(class zVEC2 const &, class zVEC2 const &);
class zVEC2 __cdecl operator-(class zVEC2 const &, class zVEC2 const &);
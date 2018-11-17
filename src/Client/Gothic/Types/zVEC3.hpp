#pragma once

#include "../xcall.h"
#include "zSTRING.hpp"
#include <Shared/Components/vec3.hpp>

class zVEC3
{
public:
    zVEC3()
    {
        XCALL(0x00489F30);
    }
    
    zVEC3(float, float, float)
    {
        XCALL(0x00408EC0);
    }

    zVEC3(const OpenGMP::Vec3 &vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }

    operator OpenGMP::Vec3()
    {
        return OpenGMP::Vec3(x, y, z);
    }

    zVEC3(float)
    {
        XCALL(0x005375B0);
    }
        
    zVEC3(class zVEC3 const &)
    {
        XCALL(0x00420B40);
    }
        
    float Length2() const
    {
        XCALL(0x00474C30);
    }
        
    float LengthApprox() const
    {
        XCALL(0x00490E10);
    }
    
    zVEC3 & Normalize()
    {
        XCALL(0x00490EA0);
    }
    
    zVEC3 & NormalizeSafe()
    {
        XCALL(0x00498A20);
    }
    
    zVEC3 & NormalizeApprox()
    {
        XCALL(0x0054E750);
    }
    
    zVEC3 & operator/=(float)
    {
        XCALL(0x004B60D0);
    }
        
    zVEC3 & operator-=(class zVEC3 const &)
    {
        XCALL(0x00554A00);
    }
    
    zVEC3 & operator*=(float)
    {
        XCALL(0x00554A30);
    }
    
    float & operator[](int)
    {
        XCALL(0x0067A880);
    }
    
    zVEC3 & Apply(float(__cdecl*)(float))
    {
        XCALL(0x00513080);
    }
    
    zSTRING GetString() const
    {
        XCALL(0x005375D0);
    }
    
    int IsEqualEps(class zVEC3 const &) const
    {
        XCALL(0x00564880);
    }

    float x, y, z;
};

//Non member operators:
class zVEC3 __cdecl RotateVec(class zVEC3 &, class zVEC3 &, float, float);
class zVEC3 __cdecl zLerp(float, class zVEC3 const &, class zVEC3 const);
class zVEC3 __cdecl operator*(class zVEC3 const &, class zMAT4 const &);
class zVEC3 __cdecl operator*(class zMAT3 const &, class zVEC3 const &);
class zVEC3 __cdecl operator-(class zVEC3 const &);
class zVEC3 __cdecl operator/(class zVEC3 const &, float);
class zVEC3 __cdecl operator^(class zVEC3 const &, class zVEC3 const &);
class zVEC3 __cdecl operator-(class zVEC3 const &, class zVEC3 const &);
class zVEC3 __cdecl operator+(class zVEC3 const &, class zVEC3 const &);
class zVEC3 __cdecl operator*(class zVEC3 const &, float);
class zVEC3 __cdecl operator*(class zMAT4 const &, class zVEC3 const &);
class zVEC3 __cdecl Alg_Prod(class zVEC3 const &, class zVEC3 const &);
class zVEC3 __cdecl Alg_Min(class zVEC3 const &, class zVEC3 const &);
class zVEC3 __cdecl Alg_Max(class zVEC3 const &, class zVEC3 const &);

#pragma once

#include "../xcall.h"
#include "zSTRING.hpp"

class zVEC3;

class zTPlane
{
public:
    float load[3];

    enum zTPlaneClass
    {
        unknownContent
    };

    int CalcSignbits() const
    {
        XCALL(0x0054B1A0);
    }
    
    int ClassifyPointBSPBuild(const zVEC3 &vec) const
    {
        XCALL(0x005FB440);
    }

    zSTRING Print() const
    {
        XCALL(0x005FB490);
    }

    void Calc(const zVEC3 &vec1, const zVEC3 &vec2, const zVEC3 &vec3)
    {
        XCALL(0x005FB870);
    }

    void GetOriginUpRight(zVEC3 &vec1, zVEC3 &vec2, zVEC3 &vec3) const
    {
        XCALL(0x005FB950);
    }
};
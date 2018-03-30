#pragma once

#include "../xcall.h"
#include "zTPlane.hpp"

class zCOLOR;
class zVEC3;

class zTBSphere3D
{
public:
    float load[4];
    
    int IsIntersecting(const zVEC3 &vec1, const zVEC3 &vec2) const
    {
        XCALL(0x00543FD0);
    }
    
    int IsIntersecting(const zTBSphere3D &sphere) const
    {
        XCALL(0x005440E0);
    }

    int ClassifyPlane(zTPlane plane) const
    {
        XCALL(0x005441A0);
    }

    void Draw(const zCOLOR &color) const
    {
        XCALL(0x005441F0);
    }
};
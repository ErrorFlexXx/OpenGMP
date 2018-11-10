#pragma once

#include "../Classes/zCVob.hpp"

class oCVob : public zCVob
{
public:
    int HasNpcEnoughSpace(class zVEC3 &vec)
    {
        XCALL(0x0077C3C0);
    }

    int HasEnoughSpace(class zVEC3 &vec)
    {
        XCALL(0x0077C6B0);
    }
        
    int SearchNpcPosition(class zVEC3 &vec)
    {
        XCALL(0x0077C860);
    }

    int SearchFreePosition(class zVEC3 &fit, class zCVob *origin)
    {
        XCALL(0x0077CCB0);
    }
        
    void SetOnFloor(class zVEC3 &pos)
    {
        XCALL(0x0077D0E0);
    }

    int GetFloorPosition(class zVEC3 &pos)
    {
        XCALL(0x0077D130);
    }
        
    int GetFloorPositionWithVob(class zVEC3 &centerPostition, class zCVob * &standOnVob)
    {
        XCALL(0x0077D200);
    }
};
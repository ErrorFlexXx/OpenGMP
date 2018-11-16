#pragma once

#include "../xcall.h"

class zCModelAni
{
public:
};

class zCModel
{
public:
    int IsAniActive(zCModelAni *)
    {
        XCALL(0x00472F90);
    }

    void StartAnimation(class zSTRING const &aniName)
    {
        XCALL(0x005765E0);
    }

    void StopAnimation(class zSTRING const &aniName)
    {
        XCALL(0x005765F0);
    }
    
    int IsAnimationActive(class zSTRING const &aniName)
    {
        XCALL(0x00576690);
    }

    int ApplyModelProtoOverlay(class zSTRING const &)
    {
        XCALL(0x005787F0);
    }
};
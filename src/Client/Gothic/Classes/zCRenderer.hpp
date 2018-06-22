#pragma once

#include "../xcall.h"

enum zTRnd_AlphaBlendFunc
{
    Default,
    None,
    Blend,
    Add,
    Sub,
    Mul,
    Mul2
};

class zCRenderer
{
public:

    static zCRenderer *GetRenderer()
    {
        return *(zCRenderer**)(0x00982F08);
    }

    static int PlayerLightInt()
    {
        return *((int*)(0x89EBB4));
    }
    
    static void PlayerLightInt(int value)
    {
        *((int*)(0x89EBB4)) = value;
    }

    /*virtual*/ void Vid_Clear(class zCOLOR &, int)
    {
        XCALL(0x00657E20);
    }

    /*virtual*/ void BeginFrame(void)
    {
        XCALL(0x0064DD20);
    }
    
    /*virtual*/ void EndFrame(void)
    {
        XCALL(0x0064DF20);
    }

    /*virtual*/ void Vid_Blit(int, /*struct tagRECT **/ int, /*struct tagRECT **/ int)
    {
        XCALL(0x00657670);
    }

    /*virtual*/ void /*zCRnd_D3D::*/SetFogRange(float near, float far, /*enum zTRnd_FogMode*/ int mode)
    {
        XCALL(0x006521E0);
    }

    /*virtual*/ void /*zCRnd_D3D::*/FlushPolys(void)
    {
        XCALL(0x0064DD10);
    }

    /*virtual*/ void /*zCRnd_D3D::*/SetZBufferWriteEnabled(int)
    {
        XCALL(0x006524E0);
    }

    /* virtual*/ void SetAlphaBlendFunc(enum zTRnd_AlphaBlendFunc const &)
    {
        XCALL(0x0064A1D0);
    }
};
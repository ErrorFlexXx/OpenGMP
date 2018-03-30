#pragma once

#include "../xcall.h"
#include "zCView.hpp"

class zCViewProgressBar : public zCView
{
public:
    zCViewProgressBar(int,int,int,int,zTviewID)
    {
        XCALL(0x0046E9D0);
    }

    /* virtual*/ ~zCViewProgressBar(void)
    {
        XCALL(0x0046EBE0);
    }

    /*virtual*/ void Init(void)
    {
        XCALL(0x0046ED40);
    }

    void SetPercent(int,class zSTRING)
    {
        XCALL(0x0046EEC0);
    }

    void SetRange(int,int)
    {
        XCALL(0x0046F340);
    }

    void ResetRange(void)
    {
        XCALL(0x0046F400);
    }

    /*virtual*/ void HandleChange(void)
    {
        XCALL(0x0046F190);
    }

    /*virtual*/ void Draw(void)
    {
        XCALL(0x0046F300);
    }

private:
    unsigned char data[0x30]; //+base of 0x100 bytes size.

    float CalcPercentOf(float,float,float)
    {
        XCALL(0x0046EEA0);
    }
};
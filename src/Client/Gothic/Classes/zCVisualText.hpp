#pragma once

#include "../xcall.h"
#include "zCView.hpp"
#include "../Types/zSTRING.hpp"

class zCViewText : public zCView
{
public:
    zCViewText(int,int,class zSTRING const &)
    {
        XCALL(0x007AC220);
    }

    zCViewText(int,int,class zSTRING const &,float &,struct zCOLOR &,int,int)
    {
        XCALL(0x007AC3E0);
    }

    void Create(int,int,class zSTRING const &,float &,struct zCOLOR &,int,int)
    {
        XCALL(0x007AC580);
    }

    /*virtual*/ ~zCViewText(void)
    {
        XCALL(0x007AC700);
    }
private:
    unsigned int VTBL;
    int PosX;
    int PosY;
    zSTRING text;
    zCFont font;
    float timer;
    unsigned int inPrintwin,
    zCOLOR color,
    unsigned int timed;
    unsigned int colored;
};

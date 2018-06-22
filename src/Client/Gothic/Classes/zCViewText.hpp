#pragma once

#include "../xcall.h"
#include "zCView.hpp"
#include "zCFont.hpp"
#include "zCFontMan.hpp"
#include "../Types/zSTRING.hpp"
#include "../Types/zCOLOR.hpp"

class zCViewText : public zCView
{
public:
    zCViewText(int,int,class zSTRING const &)
    {
        XCALL(0x007AC220);
    }

    zCViewText(int,int,class zSTRING const &,float &,zCOLOR &,int,int)
    {
        XCALL(0x007AC3E0);
    }

    void Create(int,int,class zSTRING const &,float &,zCOLOR &,int,int)
    {
        XCALL(0x007AC580);
    }

    /*virtual*/ ~zCViewText(void)
    {
        XCALL(0x007AC700);
    }

    void SetPosX(int val)
    {
        PosX = val;
    }

    void SetPosY(int val)
    {
        PosY = val;
    }

    zSTRING & Text()
    {
        return text;
    }

    void Text(zSTRING value)
    {
        text = value;
    }

private:
    unsigned int VTBL;
    int PosX;
    int PosY;
    zSTRING text;
    zCFont *font;
    float timer;
    unsigned int inPrintwin;
    zCOLOR color;
    unsigned int timed;
    unsigned int colored;
};

#pragma once

#include "../xcall.h"
#include "zCView.hpp"
#include "zCFont.hpp"
#include "zCFontMan.hpp"
#include "../Types/zSTRING.hpp"
#include "../Types/zCOLOR.hpp"

class zCViewText : public zCView
{
    static const struct VarOffsets
    {
        static const unsigned int vtbl = 0;
        static const unsigned int posX = 4;
        static const unsigned int posY = 8;
        static const unsigned int text = 12;
        static const unsigned int font = 32;
        static const unsigned int timer = 36;
        static const unsigned int inPrintWin = 40;
        static const unsigned int color= 44;
        static const unsigned int timed = 48;
        static const unsigned int colored = 52;
    } VarOffsets;

public:
    //Do not call Constructors - size missing
    /*zCViewText(int,int,class zSTRING const &)
    {
        XCALL(0x007AC220);
    }

    zCViewText(int,int,class zSTRING const &,float &,zCOLOR &,int,int)
    {
        XCALL(0x007AC3E0);
    }*/

    void Create(int,int,class zSTRING const &,float &,zCOLOR &,int,int)
    {
        XCALL(0x007AC580);
    }

    /*virtual*/ ~zCViewText(void)
    {
        XCALL(0x007AC700);
    }

    int GetPosX()
    {
        return *(int*)((unsigned int)this + VarOffsets::posX);
    }

    void SetPosX(int val)
    {
        *(int*)((unsigned int)this + VarOffsets::posX) = val;
    }

    int GetPosY()
    {
        return *(int*)((unsigned int)this + VarOffsets::posY);
    }

    void SetPosY(int val)
    {
        *(int*)((unsigned int)this + VarOffsets::posY) = val;
    }

    zSTRING & Text()
    {
        return *(zSTRING*)((unsigned int)this + VarOffsets::text);
    }

    void Text(const std::string &val)
    {
        Text().Clear();
        Text().Insert(0, val);
    }

    zCFont *GetFont()
    {
        return *(zCFont**)((unsigned int)this + VarOffsets::font);
    }

    void SetFont(zCFont *val)
    {
        *(zCFont**)((unsigned int)this + VarOffsets::font) = val;
    }

    void SetFont(const std::string &fontStr)
    {
        zCFontMan *fontMan = zCFontMan::GetInstance();
        SetFont(fontMan->GetFont(fontMan->Load(fontStr)));
    }

    zCOLOR *GetColor()
    {
        return (zCOLOR *)((unsigned int)this + VarOffsets::color);
    }

    float GetTimer()
    {
        return *(float*)((unsigned int)this + VarOffsets::timer);
    }

    void SetTimer(float val)
    {
        *(float*)((unsigned int)this + VarOffsets::timer) = val;
    }

    int GetTimed()
    {
        return *(int*)((unsigned int)this + VarOffsets::timed);
    }

    void SetTimed(int val)
    {
        *(int*)((unsigned int)this + VarOffsets::timed) = val;
    }

    int GetColored()
    {
        return *(int*)((unsigned int)this + VarOffsets::colored);
    }

    void SetColored(int val)
    {
        *(int*)((unsigned int)this + VarOffsets::colored) = val;
    }

private:    
};

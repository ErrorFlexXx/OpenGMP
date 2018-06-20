#pragma once

#include "../xcall.h"

class zSTRING;
class zCFont;

class zCFontMan
{
public:
    zCFontMan(void)
    {
        XCALL(0x00788030);
    }

    ~zCFontMan(void)
    {
        XCALL(0x00788040);
    }

    /* Returns XCALLs FontManager (created in zUlfi::StartUp) */
    static zCFontMan *GetInstance()
    {
        return *(zCFontMan**)(0x00AB39D4);
    }

    /* Return -- Maybe ID ? */
    int Load(const zSTRING &fontName)
    {
        XCALL(0x007882D0);
    }

    int GetNumber(void)
    {
        XCALL(0x007884A0);
    }

    zCFont * GetFont(int id)
    {
        XCALL(0x007884B0);
    }

private:
    unsigned char load[0x0C];

    int SearchFont(const zSTRING &fontName)
    {
        XCALL(0x00788110);
    }
};
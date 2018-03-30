#pragma once

#include "../xcall.h"
#include "../Types/zSTRING.hpp"

class zVEC2;

class zCFont
{
public:
    zCFont(class zSTRING const &)
    {
        XCALL(0x00788780);
    }

    ~zCFont(void)
    {
        XCALL(0x00788920);
    }

    int CacheIn(void)
    {
        XCALL(0x007884D0);
    }

    int SaveFontData(void)
    {
        XCALL(0x00788B00);
    }

    int LoadFontData(void)
    {
        XCALL(0x00788F20);
    }

    zSTRING GetFontName(void)
    {
        XCALL(0x007894A0);
    }

    int GetFontY(void)
    {
        XCALL(0x007894E0);
    }

    int GetFontX(const zSTRING &text)
    {
        XCALL(0x007894F0);
    }

    int GetWidth(char character)
    {
        XCALL(0x00789520);
    }

    int GetLetterDistance(void)
    {
        XCALL(0x00789530);
    }

    int GetFontData(unsigned char unknown, int &unknown2, zVEC2 &unknown3, zVEC2 &unknown4)
    {
        XCALL(0x0078A390);
    }

private:
    unsigned char load[0x100]; //Estimated... Refer zCFontMan::Load addr: 0x007883FC ?

    int LoadFontTexture(class zSTRING const &)
    {
        XCALL(0x00788510);
    }

    int LoadSource(class zSTRING const &)
    {
        XCALL(0x007889B0);
    }

    char MapToAscii(char)
    {
        XCALL(0x00789540);
    }

    int GetSizex(void)
    {
        XCALL(0x007895E0);
    }

    int GetSizey(void)
    {
        XCALL(0x00789610);
    }

    int GetPixel(int, int)
    {
        XCALL(0x00789640);
    }

    int GetPixelAlpha(int, int)
    {
        XCALL(0x00789780);
    }

    int NextPixelX(int, int, int &)
    {
        XCALL(0x007898C0);
    }

    int NextPixelY(int, int, int &)
    {
        XCALL(0x00789920);
    }

    int NextPixelXAlpha(int, int, int &)
    {
        XCALL(0x00789980);
    }

    int NextPixelYAlpha(int, int, int &)
    {
        XCALL(0x007899E0);
    }

    int NextPixelXCol(int, int, int)
    {
        XCALL(0x00789A40);
    }

    int NextPixelYCol(int, int, int)
    {
        XCALL(0x00789AC0);
    }

    int AnalyseLetters(void)
    {
        XCALL(0x00789B40);
    }
};
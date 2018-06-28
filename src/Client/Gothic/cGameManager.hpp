#pragma once

#include "xcall.h"
#include "Types/zSTRING.hpp"

class oCGame;

class CGameManager
{
public:
    static CGameManager *GetInstance()
    {
        return *(CGameManager**)(0x008C2958);
    }

    oCGame * GetGame()
    {
        XCALL(0x0042B1B0);
    }

    int IsIntroActive()
    {
        XCALL(0x0042B1C0);
    }

    void InsertMenuWorld(class zSTRING &, class zSTRING &)
    {
        XCALL(0x0042B1E0);
    }

    void RemoveMenuWorld()
    {
        XCALL(0x0042B1F0);
    }

    int IsGameRunning()
    {
        XCALL(0x0042B200);
    }

    int IntroduceChapter()
    {
        XCALL(0x0042B220);
    }

    int IntroduceChapter(class zSTRING, class zSTRING, class zSTRING, class zSTRING, int)
    {
        XCALL(0x0042B7E0);
    }

    int PlayVideo(class zSTRING)
    {
        XCALL(0x0042B940);
    }

    int PlayVideoEx(class zSTRING, short, int)
    {
        XCALL(0x0042BB10);
    }

    void ShowRealPlayTime()
    {
        XCALL(0x0042BDE0);
    }

    int ExitGame(void)
    {
        XCALL(0x00425780);
    }

private:
    CGameManager(); //Abstract class (size unknown) -> Do not create one
};
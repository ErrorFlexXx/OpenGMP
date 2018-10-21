#pragma once

#include "../xcall.h"

class oCWorldTimer;

class oCGame
{
public:
    /**
     * @brief struct for with addresses used for hooks
     */
    static const struct Addresses
    {
        static const unsigned int Render = 0x006C86A0;
    } Addresses;

    void LoadWorld(int, class zSTRING const &)
    {
        XCALL(0x006C90B0);
    }
        
    /* virtual */ void Render()
    {
        XCALL(0x006C86A0);
    }

    /* protected: */ void Menu(int)
    {
        XCALL(0x004292D0);
    }
        
    /* virtual */ void Pause(int)
    {
        XCALL(0x006C8AD0);
    }
        
    /* virtual */ void Unpause()
    {
        XCALL(0x006C8D50);
    }
        
    /* virtual */ void SetTime(int, int, int)
    {
        XCALL(0x006C4DE0);
    }
        
    /* virtual */ void GetTime(int &, int &, int &)
    {
        XCALL(0x006C4E70);
    }
    
    /* private: virtual */ void ChangeLevel(class zSTRING const &, class zSTRING const &)
    {
        XCALL(0x006C7290);
    }
        
    void UpdateScreenResolution()
    {
        XCALL(0x006C2E00);
    }
        
    oCWorldTimer * GetWorldTimer()
    {
        XCALL(0x006C2C80);
    }
        
    /* virtual */ void Init()
    {
        XCALL(0x006C1060);
    }
        
    /* virtual */ void Done()
    {
        XCALL(0x006C0D80);
    }

    void SwitchCamToNextNpc()
    {
        XCALL(0x006FBF40);
    }
        
    void RefreshNpcs()
    {
        XCALL(0x006CB5F0);
    }
        
    void DeleteTorches()
    {
        XCALL(0x006CB640);
    }

    //Detour declarations:
    void GMP_Render();
};
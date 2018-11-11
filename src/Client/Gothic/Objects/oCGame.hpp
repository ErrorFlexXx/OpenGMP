#pragma once

#include "../xcall.h"

class oCWorldTimer;
class oCWorld;
class zCCamera;
class zCVob;

extern DWORD origRenderAddr;

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

    static const struct VarOffsets
    {
        static const unsigned int World  = 0x8;
        static const unsigned int Cam    = 0x0C;
        static const unsigned int CamVob = 0x14;
    } VarOffsets;

    zCCamera *GetCamera()
    {
        return *(zCCamera**)((DWORD)this + VarOffsets::Cam);
    }

    zCVob *GetCamVob()
    {
        return *(zCVob**)((DWORD)this + VarOffsets::CamVob);
    }

    oCWorld *GetWorld()
    {
        return *(oCWorld**)((DWORD)this + VarOffsets::World);
    }

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

    class zCViewProgressBar *GetProgressBar()
    {
        return *(zCViewProgressBar**)((DWORD)this + 0x17C);
    }

    void OpenLoadscreen(bool gamestart, zSTRING worldName)
    {
        XCALL(0x006C2690);
    }

    void CloseLoadscreen()
    {
        XCALL(0x006C2BD0);
    }

    void ClearGameState()
    {
        XCALL(0x006C5ED0);
    }

    void EnterWorld(class oCNpc *npc, int setPosition, class zSTRING const &waypoint)
    {
        XCALL(0x006C96F0);
    }

    //Detour declarations:
    void Orig_Render()
    {
        XCALL(origRenderAddr);
    }
    void GMP_Render();
};
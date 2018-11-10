#pragma once

#include "../xcall.h"
#include "oCVob.hpp"
#include "oCAniCtrl_Human.hpp"
#include "../Classes/zCModel.hpp"

class oCNpc : public oCVob
{
public:
    /**
    * @brief struct for with addresses used for hooks
    */
    static const struct VarOffsets
    {
        static const unsigned int speedTurn = 0x100;
    } VarOffsets;

    float GetTurnSpeed()
    {
        XCALL(0x00680970);
    }

    void SetTurnSpeed(float value)
    {
        *((float*)(DWORD)this + VarOffsets::speedTurn) = value;
    }

    int CanGo(float len, zVEC3 &normal)
    {
        XCALL(0x00680B30);
    }

    float GetAngle(zCVob *to)
    {
        XCALL(0x006811C0);
    }

    void GetAngles(zVEC3 &pos, float &azimuth, float &elevation)
    {
        XCALL(0x006812B0);
    }

    void GetAngles(zCVob *to, float &azimuth, float &elevation)
    {
        XCALL(0x00681680);
    }

    float GetDistanceToPos2(zVEC3 &position, int dimension)
    {
        XCALL(0x006816C0);
    }
    
    void CreateFallDamage(float dist)
    {
        XCALL(0x00681DA0);
    }

    void ResetPos(zVEC3 &position)
    {
        XCALL(0x006824D0);
    }

    void StandUp(int walkingAllowed, int startAniTransistion)
    {
        XCALL(0x00682B40);
    }

    float Turn(zVEC3 &direction)
    {
        XCALL(0x00683000);
    }

    float Turning(zVEC3 &direction)
    {
        XCALL(0x00683120);
    }

    zCModel *GetModel()
    {
        XCALL(0x00738720);
    }

    oCAniCtrl_Human * GetAnictrl()
    {
        XCALL(0x00734B40);
    }

    inline static oCNpc *GetHero()
    {
        return *(oCNpc**)0x00AB2684;
    }

    inline static void SetHero(oCNpc* newHero)
    {
        *(oCNpc**)0x00AB2684 = newHero;
    }
};
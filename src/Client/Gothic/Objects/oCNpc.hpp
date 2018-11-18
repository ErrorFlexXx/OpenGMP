#pragma once

#include "../xcall.h"
#include <Client/Gothic/cGameManager.hpp>
#include <Client/Gothic/Objects/oCVob.hpp>
#include <Client/Gothic/Objects/oCAniCtrl_Human.hpp>
#include <Client/Gothic/Objects/oCGame.hpp>
#include <Client/Gothic/Objects/oCWorld.hpp>
#include <Client/Gothic/Classes/zCModel.hpp>
#include <Client/Gothic/Types/zSTRING.hpp>
#include <Shared/Objects/player.hpp>
#include <iostream>

extern DWORD origIsDeadAddr;

class oCNpc : public oCVob
{
public:
    /**
    * @brief struct for with addresses used for hooks
    */
    static const struct VarOffsets
    {
        static const unsigned int speedTurn = 0x100;
        static const unsigned int hp_current = 0x1B8;
        static const unsigned int hp_max = 0x1BC;
        static const unsigned int mp_current = 0x1C0;
        static const unsigned int mp_max = 0x1C4;
        static const unsigned int strength = 0x1C8;
        static const unsigned int dexterity = 0x1CC;
    } VarOffsets;

    static const struct Addresses
    {
        static const unsigned int IsDead = 0x00736740;
    } Addresses;

    void Setup(OpenGMP::Player &player)
    {
        SetVobName("PC_Hero");
        SetVisual("HUMANS.MDS");
        GetModel();
        InitHumanAI();
        GetAnictrl()->InitAnimations();
        SetCollDet(0);
        player.position = player.position.ClampToWorldLimits();
        SetPosition(player.position);
        SetHeadingYWorld(player.rotation.ClampToWorldLimits());
        SetCollDet(1);
        SetSleeping(0);
        CGameManager::GetInstance()->GetGame()->GetWorld()->EnableVob(this);
        SetAdditionalVisuals(player.visual.bodyModel, player.visual.bodyTextureId, 0, player.visual.headModel, player.visual.headTextureId, 0, -1);
        HP_Max(player.attributes.max_health);
        HP(player.attributes.health);
        if (!player.rotation.IsNull())
        {
            //CGameManager::GetInstance()->GetGame()->Orig_Render();
            SetHeadingAtWorld(player.rotation.ClampToWorldLimits());
        }
    }

    int HP()
    {
        return *(int*)((DWORD)this + VarOffsets::hp_current);
    }

    void HP(int value)
    {
        *(int*)((DWORD)this + VarOffsets::hp_current) = value;
    }

    int HP_Max()
    {
        return *(int*)((DWORD)this + VarOffsets::hp_max);
    }

    void HP_Max(int value)
    {
        *(int*)((DWORD)this + VarOffsets::hp_max) = value;
    }

    void SetAsPlayer()
    {
        XCALL(0x007426A0);
    }

    void SetAdditionalVisuals(const zSTRING &body, int bodyTexNr, int bodyColor, const zSTRING &head, int headTextNr, int teethTexNr, int armorInst)
    {
        XCALL(0x00738350);
    }

    void InitHumanAI()
    {
        XCALL(0x0072F5B0);
    }

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

    class zVEC3 GetAtVectorWorld() const
    {
        XCALL(0x0052DCB0);
    }

    void SetHeadingAtWorld(class zVEC3 const &)
    {
        XCALL(0x0061CBC0);
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

    int Orig_IsDead()
    {
        XCALL(origIsDeadAddr);
    }

    int GMP_IsDead()
    {
        return false;
    }
};
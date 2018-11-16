#pragma once

#include "../xcall.h"
#include "zCObject.hpp"
#include "../Types/zSTRING.hpp"
#include "../Types/zCOLOR.hpp"
#include "../Types/zVEC3.hpp"
#include "../Types/zMAT4.hpp"
#include "../Types/zTBBox3D.hpp"

class zCCollisionObject;    //Implement if needed
class zCRigidBody;          //Implement if needed
class zCAIBase;             //Implement if needed
class zCEventManager;       //Implement if needed
class zCVisual;

class zCVob : public zCObject
{
public:
    static const enum class BitFlag0 : unsigned int
    {
        showVisual = 1 << 0,
        drawBBox3D = 1 << 1,
        visualAlphaEnabled = 1 << 2,
        physicsEnabled = 1 << 3,
        staticVob = 1 << 4,
        ignoredByTraceRay = 1 << 5,
        collDetectionStatic = 1 << 6,
        collDetectionDynamic = 1 << 7,
        castDynShadow = 1 << 8, // 2 bits
        lightColorStatDirty = 1 << 10,
        lightColorDynDirty = 1 << 11,
        movementMode = 1 << 12 // 2 bits
    } BitFlag0;

    static const enum class zTVobType : unsigned char
    {
        VOB,
        LIGHT = 1,
        SOUND = 2,
        STARTPOINT = 6,
        WAYPOINT = 7,
        MOB = 128,
        ITEM = 129,
        NPC = 130
    } zTVobType;

    static const struct VarOffsets
    {
        static const unsigned int globalVobTreeNode = 0x0024;
        static const unsigned int lastTimeDrawn = 0x0028;
        static const unsigned int lastTimeCollected = 0x002C;
        static const unsigned int vobLeafList = 0x0030;//zCArray<zCBspLeaf*>
        static const unsigned int trafoObjToWorld = 0x003C;//int[16]
        static const unsigned int bbox3D = 0x007C;
        static const unsigned int bsphere3D = 0x0094;
        static const unsigned int touchVobList = 0x00A4;//zCArray<zCVob*>
        static const unsigned int type = 0x00B0;
        static const unsigned int groundShadowSizePacked = 0x00b4;
        static const unsigned int homeWorld = 0x00B8;
        static const unsigned int groundPoly = 0x00BC;
        static const unsigned int callback_ai = 0x00C0;
        static const unsigned int trafo = 0x00C4;
        static const unsigned int visual = 0x00C8;
        static const unsigned int visualAlpha = 0x00CC;
        static const unsigned int vobFarClipZScale = 0x00D0;
        static const unsigned int aniMode = 0x00D4;
        static const unsigned int aniModeStrength = 0x00D8;
        static const unsigned int zBias = 0x00DC;
        static const unsigned int rigidBody = 0x00E0;
        static const unsigned int lightColorStat = 0x00E4;
        static const unsigned int lightColorDyn = 0x00E8;
        static const unsigned int lightDirectionStat = 0x00EC;
        static const unsigned int vobPresetName = 0x00F8;
        static const unsigned int eventManager = 0x00FC;
        static const unsigned int nextOnTimer = 0x0100;
        static const unsigned int bitfield = 0x0104;
        static const unsigned int CollisionObjectClass = 0x0118;
        static const unsigned int CollisionObject = 0x011C;
    } VarOffsets;    

    static zCVob * _CreateNewInstance()
    {
        XCALL(0x005FD940);
    }

    ~zCVob()
    {
        ScalarDeletingDestructor(1);
    }

    /*protected*/ /*virtual*/void *ScalarDeletingDestructor(unsigned int)
    {
        XCALL(0x005FE440);
    }

    void SetCollDet(int)
    {
        XCALL(0x006D0000);
    }

    float VisualAlpha() const
    {
        return *(float*)((DWORD)this + VarOffsets::visualAlpha);
    }

    void VisualAlpha(float value)
    {
        *(float*)((DWORD)this + VarOffsets::visualAlpha) = value;
    }

    static unsigned long GetNextFreeVobID()
    {
        XCALL(0x005FE8D0);
    }

    static void InitVobSystem()
    {
        XCALL(0x005FE6E0);
    }

    static void CleanupVobSystem()
    {
        XCALL(0x005FE800);
    }

    static void ResetIDCtr()
    {
        XCALL(0x005FE8C0);
    }

    static zCVob * GetAutoLinkParent(zCVob *)
    {
        XCALL(0x0061A6C0);
    }

    static int CanAutoLinkWith(class zCVob *, class zCVob *)
    {
        XCALL(0x0061A700);
    }

    static void CheckAutoLink(class zCVob *, class zCVob *)
    {
        XCALL(0x0061A840);
    }
    
    static void CheckAutoUnlink(class zCVob *)
    {
        XCALL(0x0061AAC0);
    }
        
    void SetVobID(unsigned long const &)
    {
        XCALL(0x005FE8E0);
    }
    
    void SetAI(class zCAIBase *)
    {
        XCALL(0x005FE8F0);
    }
        
    void SetVobPresetName(class zSTRING const &)
    {
        XCALL(0x005FE940);
    }
    
    zSTRING const & GetVobPresetName(void) const
    {
        XCALL(0x005FE950);
    }
    
    zCRigidBody * GetRigidBody()
    {
        XCALL(0x005FE960);
    }
        
    void SetVobName(class zSTRING const &)
    {
        XCALL(0x005FFDD0);
    }
        
    zCEventManager * __fastcall GetEM(int)
    {
        XCALL(0x005FFE10);
    }
        
    zCOLOR CalcLightSampleAtOrigin()
    {
        XCALL(0x00600130);
    }
        
    zCOLOR GetLightColorStat()
    {
        XCALL(0x006001B0);
    }
        
    zCOLOR GetLightColorStatGroundPoly()
    {
        XCALL(0x00600440);
    }
        
    zCOLOR GetLightColorDyn()
    {
        XCALL(0x00600470);
    }
        
    zSTRING const * GetSectorNameVobIsIn() const
    {
        XCALL(0x00600AE0);
    }
        
    zCOLOR GetLightColorAtCenter() const
    {
        XCALL(0x00601AC0);
    }
        
    void RemoveVobFromWorld()
    {
        XCALL(0x00601C40);
    }
        
    void RemoveVobSubtreeFromWorld()
    {
        XCALL(0x00601C60);
    }
        
    zSTRING GetVobInfo()
    {
        XCALL(0x00602100);
    }

    /*virtual*/ void SetVisual(class zSTRING const &)
    {
        XCALL(0x00602680);
    }
        
    void CalcRenderAlpha(float, class zCVisual * &, float &)
    {
        XCALL(0x006013E0);
    }
    
    zVEC3 GetPositionWorld() const
    {
        XCALL(0x0052DC90);
    }
        
    zVEC3 GetAtVectorWorld() const
    {
        XCALL(0x0052DCB0);
    }
        
    zVEC3 GetUpVectorWorld() const
    {
        XCALL(0x0052DCD0);
    }
        
    zVEC3 GetRightVectorWorld() const
    {
        XCALL(0x0052DCF0);
    }
        
    void SetSleeping(int isSleeping)
    {
        XCALL(0x00602930);
    }
        
    void UpdateVisualDependencies(int)
    {
        XCALL(0x00602B20);
    }

    void AddVobToWorld_CorrectParentDependencies()
    {
        XCALL(0x00602BB0);
    }
       
    void ResetOnTimer()
    {
        XCALL(0x00602BD0);
    }
        
    void SetOnTimer(float)
    {
        XCALL(0x00602BE0);
    }
        
    int IsOnTimer() const
    {
        XCALL(0x00602C10);
    }
        
    void DoFrameActivity()
    {
        XCALL(0x00602C60);
    }
        
    int GetIsProjectile() const
    {
        XCALL(0x00606C00);
    }
        
    zCVisual * GetVisual() const
    {
        XCALL(0x00616B20);
    }
        
    void CalcGroundPoly()
    {
        XCALL(0x0061ACD0);
    }
    
    void CalcWaterVob()
    {
        XCALL(0x0061AE20);
    }
        
    void SetCollTypeDefaultFromVisual()
    {
        XCALL(0x0061AEF0);
    }
        
    void TouchMovement()
    {
        XCALL(0x0061B060);
    }
        
    zMAT4 const & GetNewTrafoObjToWorld() const
    {
        XCALL(0x0061B080);
    }
        
    zMAT4 & __thiscall GetNewTrafoObjToWorld()
    {
        XCALL(0x0061B0A0);
    }
        
    void SetNewTrafoObjToWorld(class zMAT4 const &)
    {
        XCALL(0x0061B0C0);
    }
        
    void SetBBox3DWorld(class zTBBox3D const &)
    {
        XCALL(0x0061B0E0);
    }
        
    void SetBBox3DLocal(class zTBBox3D const &)
    {
        XCALL(0x0061B140);
    }
        
    zTBBox3D GetBBox3DLocal() const
    {
        XCALL(0x0061B1F0);
    }
        
    void Move(float, float, float)
    {
        XCALL(0x0061B2E0);
    }
        
    void MoveWorld(float, float, float)
    {
        XCALL(0x0061B350);
    }
    
    void MoveLocal(float, float, float)
    {
        XCALL(0x0061B3C0);
    }
        
    void SetRotationWorld(class zCQuat const &)
    {
        XCALL(0x0061B4C0);
    }
        
    void RotateWorld(class zVEC3 const &, float)
    {
        XCALL(0x0061B520);
    }
        
    void RotateLocal(class zVEC3 const &, float)
    {
        XCALL(0x0061B610);
    }
        
    void RotateLocalX(float)
    {
        XCALL(0x0061B6B0);
    }
        
    void RotateLocalY(float)
    {
        XCALL(0x0061B720);
    }
        
    void RotateLocalZ(float)
    {
        XCALL(0x0061B790);
    }
        
    void RotateWorldX(float)
    {
        XCALL(0x0061B800);
    }
        
    void RotateWorldY(float)
    {
        XCALL(0x0061B830);
    }
        
    void RotateWorldZ(float)
    {
        XCALL(0x0061B860);
    }
    
    void GetPositionWorld(float &, float &, float &) const
    {
        XCALL(0x0061B890);
    }
        
    void GetPositionLocal(float &, float &, float &) const
    {
        XCALL(0x0061B8C0);
    }
        
    float GetDistanceToVob(class zCVob &)
    {
        XCALL(0x0061B910);
    }
    
    float GetDistanceToVobApprox(class zCVob &)
    {
        XCALL(0x0061B970);
    }
    
    float GetDistanceToVob2(class zCVob &)
    {
        XCALL(0x0061BA40);
    }
        
    void SetPositionLocal(class zVEC3 const &)
    {
        XCALL(0x0061BAA0);
    }
        
    void SetPositionWorld(class zVEC3 const &)
    {
        XCALL(0x0061BB70);
    }

    void SetPosition(const zVEC3 &set)
    {
        *(float*)((DWORD)this + 0x48) = set.x; //(float)zCVob + 0x48 X
        *(float*)((DWORD)this + 0x58) = set.y; //(float)zCVob + 0x68 Y
        *(float*)((DWORD)this + 0x68) = set.z; //(float)zCVob + 0x58 Z
    }

    void GetPosition(float &x, float &y, float &z)
    {
        x = *(float*)((DWORD)this + 0x48); //(float)zCVob + 0x48 X
        y = *(float*)((DWORD)this + 0x58); //(float)zCVob + 0x68 Y
        z = *(float*)((DWORD)this + 0x68); //(float)zCVob + 0x58 Z
    }
        
    void SetTrafo(class zMAT4 const &)
    {
        XCALL(0x0061BBD0);
    }
        
    void SetTrafoObjToWorld(class zMAT4 const &)
    {
        XCALL(0x0061BC80);
    }
    
    void ResetRotationsLocal()
    {
        XCALL(0x0061BCF0);
    }
        
    void ResetXZRotationsLocal()
    {
        XCALL(0x0061BE20);
    }
        
    void ResetRotationsWorld()
    {
        XCALL(0x0061C000);
    }
        
    void ResetXZRotationsWorld()
    {
        XCALL(0x0061C090);
    }
        
    void SetHeadingYLocal(class zVEC3 const &)
    {
        XCALL(0x0061C1B0);
    }
        
    void SetHeadingYWorld(class zVEC3 const &)
    {
        XCALL(0x0061C280);
    }
        
    void SetHeadingYWorld(class zCVob *)
    {
        XCALL(0x0061C450);
    }
        
    void SetHeadingLocal(class zVEC3 const &)
    {
        XCALL(0x0061C5E0);
    }
        
    void SetHeadingWorld(class zVEC3 const &)
    {
        XCALL(0x0061C6B0);
    }
        
    void SetHeadingWorld(class zCVob *)
    {
        XCALL(0x0061C780);
    }
        
    void SetHeadingAtLocal(class zVEC3 const &)
    {
        XCALL(0x0061C860);
    }

    int HasParentVob() const
    {
        XCALL(0x0061CBA0);
    }
        
    void SetHeadingAtWorld(class zVEC3 const &)
    {
        XCALL(0x0061CBC0);
    }
        
    void __fastcall SetCollDetStat(int)
    {
        XCALL(0x0061CE50);
    }
        
    void __fastcall SetCollDetDyn(int)
    {
        XCALL(0x0061CF40);
    }
        
    void DoneWithTrafoLocal()
    {
        XCALL(0x0061D0B0);
    }
    
    void CreateTrafoLocal() const
    {
        XCALL(0x0061D100);
    }
    
    void SetPhysicsEnabled(int)
    {
        XCALL(0x0061D190);
    }
    
    zVEC3 GetVelocity()
    {
        XCALL(0x0061D1C0);
    }
        
    int DetectCollision(class zMAT4 *)
    {
        XCALL(0x0061D890);
    }
        
    void BeginMovement()
    {
        XCALL(0x0061DA80);
    }
    
    void ResetToOldMovementState()
    {
        XCALL(0x0061DC00);
    }
        
    void SetCollisionObject(class zCCollisionObject *)
    {
        XCALL(0x0061E5E0);
    }
        
    void SetCollisionClass(class zCCollisionObjectDef *)
    {
        XCALL(0x0061E610);
    }
    
    zCCollisionObject * GetCollisionObject() const
    {
        XCALL(0x0061E650);
    }
    
    void CreateCollisionObject()
    {
        XCALL(0x0061E660);
    }
    
    void __fastcall DestroyCollisionObject(int)
    {
        XCALL(0x0061E6D0);
    }

    int GetGroundPoly()
    {
        return *((int*)((unsigned int)this + VarOffsets::groundPoly));
    }

    void SetGroundPoly(int value)
    {
        *((int*)((unsigned int)this + VarOffsets::groundPoly)) = value;
    }

    class zMAT4 *GetTrafoObjToWorld()
    {
        return (zMAT4*)((unsigned int)this + VarOffsets::trafoObjToWorld);
    }

    zVEC3 Position()
    {
        return GetTrafoObjToWorld()->Position();
    }

    void Position(const zVEC3 &newPos)
    {
        GetTrafoObjToWorld()->Position(newPos);
    }

    zVEC3 Direction()
    {
        return GetTrafoObjToWorld()->Direction();
    }

    void Direction(const zVEC3 &newDir)
    {
        GetTrafoObjToWorld()->Direction(newDir);
    }

    int LastTimeDrawn()
    {
        return *(int*)((unsigned int)this + VarOffsets::lastTimeDrawn);
    }

    void LastTimeDrawn(int value)
    {
        *(int*)((unsigned int)this + VarOffsets::lastTimeDrawn) = value;
    }
};
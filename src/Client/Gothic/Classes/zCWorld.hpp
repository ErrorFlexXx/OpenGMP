#pragma once

#include "../xcall.h"

class zCWorld
{
public:
    static const struct VarOffsets
    {
        static const int bIsInventoryWorld = 136;
        static const int bDrawVobBBox3D = 0x224;
        static const int BspTreeMode = 0x204;
    } VarOffsets;

    static zCWorld * _CreateInstance(void)
    {
        XCALL(0x0061F9B0);
    }

    zCWorld(void)
    {
        XCALL(0x0061FA40);
    }
    /* Don't implement base destructors if you will destruct inherited objects.
     * Code of destructor in child will implicitly call the base distructor and
     * this destructor will cause a double free.
     *
    ~zCWorld(void)
    {
        XCALL(0x006200F0);
    }
    */

    bool IsInventoryWorld()
    {
        return *((bool*)(this + VarOffsets::bIsInventoryWorld));
    }

    void IsInventoryWorld(bool value)
    {
        *((bool*)(this + VarOffsets::bIsInventoryWorld)) = value;
    }

    bool DrawVobBBox3D()
    {
        return *((bool*)(this + VarOffsets::bDrawVobBBox3D));
    }

    void DrawVobBBox3D(bool value)
    {
        *((bool*)(this + VarOffsets::bDrawVobBBox3D)) = value;
    }

    int BspTreeMode()
    {
        return *((int*)(this + VarOffsets::BspTreeMode));
    }

    void BspTreeMode(int value)
    {
        *((int*)(this + VarOffsets::BspTreeMode)) = value;
    }
    
    void Render(class zCCamera &)
    {
        XCALL(0x00621700);
    }

    class zCSkyControler * GetActiveSkyControler(void)
    {
        XCALL(0x006203A0);
    }

    void SetSkyControlerIndoor(class zCSkyControler *)
    {
        XCALL(0x006203D0);
    }

    void SetSkyControlerOutdoor(class zCSkyControler *)
    {
        XCALL(0x00620410);
    }

    void SearchZoneListByClass(class zCClassDef *,class zCArray<class zCZone *> &)
    {
        XCALL(0x00624400);
    }

    class zCZone * SearchZoneDefaultByClass(class zCClassDef *)
    {
        XCALL(0x00624530);
    }

    int ShouldAddThisVobToBsp(class zCVob *)const
    {
        XCALL(0x006247B0);
    }

    class zCTree<class zCVob> * AddVobAsChild(class zCVob *,class zCVob *)
    {
        XCALL(0x006247F0);
    }

    class zCTree<class zCVob> * AddVob(class zCVob *)
    {
        XCALL(0x00624810);
    }

    void RemoveVob(class zCTree<class zCVob> *)
    {
        XCALL(0x00624BA0);
    }

    /*virtual*/ void RemoveVobSubtree(class zCVob *)
    {
        XCALL(0x00624D60);
    }

    /*void RemoveVobSubtree(class zCTree<class zCVob> *)
    {
        XCALL(0x00624D90);
    }*/

    void MoveVobSubtreeTo(class zCVob *,class zCVob *)
    {
        XCALL(0x00624E70);
    }

    void MoveVobSubtreeToWorldSpace(class zCVob *)
    {
        XCALL(0x00624E90);
    }

    void RemoveVobFromLists(class zCVob *)
    {
        XCALL(0x00624EB0);
    }

    void PrintStatus(void)
    {
        XCALL(0x00625080);
    }

    void PrintGlobalVobTree(class zCTree<class zCVob> *,int)
    {
        XCALL(0x00625AE0);
    }

    void PrintActiveVobs(void)
    {
        XCALL(0x00625DA0);
    }

    void MoveVobs(void)
    {
        XCALL(0x00626050);
    }

    void AdvanceClock(float)
    {
        XCALL(0x006260E0);
    }

    void SaveBspTree(class zFILE &)
    {
        XCALL(0x00626120);
    }

    int LoadBspTree(class zFILE &,int)
    {
        XCALL(0x006262A0);
    }

    void DebugMarkOccluderPolys(void)
    {
        XCALL(0x006263D0);
    }

    class zCViewProgressBar * GetProgressBar(void)const
    {
        XCALL(0x006269C0);
    }

    void TraverseVobTree(class zCVobCallback &,void *,class zCTree<class zCVob> *)
    {
        XCALL(0x00627F10);
    }

    void SetOwnerSession(class zCSession *)
    {
        XCALL(0x00628430);
    }

    class zCSession * GetOwnerSession(void)
    {
        XCALL(0x00628480);
    }

    void RegisterPerFrameCallback(class zCWorldPerFrameCallback *)
    {
        XCALL(0x006284E0);
    }

    void UnregisterPerFrameCallback(class zCWorldPerFrameCallback *)
    {
        XCALL(0x00628610);
    }
};

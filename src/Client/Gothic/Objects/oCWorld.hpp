#pragma once

#include "../xcall.h"
#include "../Types/zSTRING.hpp"

class oCWorld
{
public:
    oCWorld(void)
    {
        XCALL(0x0077ED80);
    }

     /*virtual*/ ~oCWorld(void)
     {
         XCALL(0x0077EFE0);
     }

    static oCWorld * _CreateNewInstance(void)
    {
        XCALL(0x0077ED20);
    }

    class zSTRING GetWorldName(void)
    {
        XCALL(0x0042A6B0);
    }

    class zSTRING GetWorldFilename(void)
    {
        XCALL(0x0068DE60);
    }

    class oCVob * CreateVob(enum zTVobType,class zSTRING const &)
    {
        XCALL(0x0077F240);
    }

    /*virtual*/ class oCVob * CreateVob(enum zTVobType,int)
    {
        XCALL(0x0077F3F0);
    }

    /*virtual*/ class zCTree<class zCVob> * AddVobAsChild(class zCVob *,class zCTree<class zCVob> *)
    {
        XCALL(0x0077FE30);
    }

    /*virtual*/ void RemoveVob(class zCVob *)
    {
        XCALL(0x007800C0);
    }

    /*virtual*/ void InsertVobInWorld(class zCVob *)
    {
        XCALL(0x00780330);
    }

    /*virtual*/ void EnableVob(class zCVob *,class zCVob *)
    {
        XCALL(0x00780340);
    }

    /*virtual*/ void DisableVob(class zCVob *)
    {
        XCALL(0x00780460);
    }

    /*virtual*/ class zCVob * SearchVob(class zCVob *,class zCTree<class zCVob> *)
    {
        XCALL(0x00780570);
    }

    /*virtual*/ class zCVob * SearchVobByID(unsigned long,class zCTree<class zCVob> *)
    {
        XCALL(0x007805C0);
    }

    /*virtual*/ class zCVob * SearchVobByName(class zSTRING const &)
    {
        XCALL(0x00780610);
    }

    /*virtual*/ void SearchVobListByName(class zSTRING const &,class zCArray<class zCVob *> &)
    {
        XCALL(0x007806C0);
    }

    /*virtual*/ void TraverseVobList(class zCVobCallback &,void *)
    {
        XCALL(0x00780830);
    }

    void ClearNpcPerceptionVobLists(void)
    {
        XCALL(0x00780870);
    }

    /*virtual*/ void DisposeVobs(void)
    {
        XCALL(0x00780BD0);
    }

    /*virtual*/ void DisposeWorld(void)
    {
        XCALL(0x00780D50);
    }

protected:
    void __fastcall InsertInLists(class zCVob *)
    {
        XCALL(0x007808B0);
    }

    void __fastcall RemoveFromLists(class zCVob *)
    {
        XCALL(0x00780990);
    }
};

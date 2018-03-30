#pragma once

#include "../xcall.h"
#include "zVEC3.hpp"
#include "zSTRING.hpp"
#include "zTBSphere3D.hpp"

class zTPlane;
class zCFileBIN;
class zVEC3;
class zMAT4;
class zCOLOR;

class zTBBox3D
{
public:
    float load[6];

    zTBBox3D()
    {
        XCALL(0x00540E50);
    }

    zTBBox3D(const zTBBox3D &toCopy)
    {
        XCALL(0x0052F6B0);
    }

    void AddPoint(const zVEC3 &point)
    {
        XCALL(0x0052CD90);
    }

    void Init(void)
    {
        XCALL(0x0053AB70);
    }

    void SetMaximumBox()
    {
        XCALL(0x00544510);
    }

    float GetVolume() const
    {
        XCALL(0x00544530);
    }

    void CalcGreaterBBox3D(const zTBBox3D &box)
    {
        XCALL(0x00544550);
    }

    void ClipToBBox3D(const zTBBox3D &)
    {
        XCALL(0x005445B0);
    }

    zSTRING GetDescription() const
    {
        XCALL(0x00544630);
    }

    void SetByDescription(zSTRING &desc)
    {
        XCALL(0x00544C40);
    }

    void Transform(const zMAT4 &matrix, zTBBox3D &box) const
    {
        XCALL(0x00544F10);
    }

    void UnTransform(const zMAT4 &matrix, zTBBox3D &box) const
    {
        XCALL(0x00545020);
    }

    int IsIntersecting(const zVEC3 &vec1, const zVEC3 &vec2, float &f1, float &f2) const
    {
        XCALL(0x00545370);
    }

    int IsIntersectingSweep(const zVEC3 &vec, const zTBBox3D &box, float &f) const
    {
        XCALL(0x005454E0);
    }

    int IsIntersectingSweep(const zTBBox3D &, const zTBBox3D &, const zTBBox3D &, float &) const
    {
        XCALL(0x00545680);
    }

    int IsTrivIn(const zTBBox3D &box) const
    {
        XCALL(0x00545700);
    }

    int IsTrivInLine(const zVEC3 &vec1, const zVEC3 &vec2) const
    {
        XCALL(0x00545760);
    }

    int Classify(const zTBBox3D &box) const
    {
        XCALL(0x00545840);
    }

    zVEC3 GetNearestPoint(const zTPlane *plane) const
    {
        XCALL(0x00545900);
    }

    void Scale(float factor)
    {
        XCALL(0x00545BF0);
    }

    void Scale(const zVEC3 &scaleVector)
    {
        XCALL(0x00545C30);
    }

    float GetMinExtent() const
    {
        XCALL(0x00545C80);
    }

    zTBSphere3D GetSphere3D() const
    {
        XCALL(0x00545CC0);
    }

    int TraceRay(const zVEC3 &vec1, const zVEC3 &vec2, const zVEC3 &vec3) const
    {
        XCALL(0x00545D40);
    }

    void Draw(const zCOLOR &color) const
    {
        XCALL(0x00545EE0);
    }

    void GetCornerPoints(zVEC3 *point) const
    {
        XCALL(0x00546240);
    }

    float GetScreenSize() const
    {
        XCALL(0x005463B0);
    }

    enum zTPlaneClass ClassifyToPlane(const zTPlane &plane) const
    {
        XCALL(0x005464D0);
    }

    enum zTPlaneClass ClassifyToPlane(const zTPlane &plane, int unknown) const
    {
        XCALL(0x005465C0);
    }

    int ClassifyToPlaneSides(const zTPlane &plane) const
    {
        XCALL(0x005467E0);
    }

    int ClassifyToPlaneSides(const zTPlane &plane, int unknown) const
    {
        XCALL(0x005468B0);
    }

    void SaveBIN(zCFileBIN &saveFile)
    {
        XCALL(0x00546AD0);
    }

    void LoadBIN(zCFileBIN &loadFile)
    {
        XCALL(0x00546AF0);
    }

    zVEC3 GetCenterFloor() const
    {
        XCALL(0x0054E040);
    }

    zVEC3 GetCenter() const
    {
        XCALL(0x0054E7A0);
    }

    void InitZero()
    {
        XCALL(0x0055F3D0);
    }

    int IsIntersecting(const zTBSphere3D &sphere) const
    {
        XCALL(0x005D4F70);
    }

    int IsIntersecting(const zTBBox3D &box) const
    {
        XCALL(0x006039C0);
    }
};
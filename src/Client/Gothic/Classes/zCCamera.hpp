#pragma once

#include "../xcall.h"
#include "../Types/zVEC3.hpp"
#include "../Types/zCOLOR.hpp"
#include "../Types/zTBBox3D.hpp"
#include "../Types/zSTRING.hpp"

class zCCamera
{
public:
    static const struct VarOffsets
    {
        static const unsigned int CamVob = 0x920;
    } VarOffsets;

    static zVEC3 GetActiveCamPos()
    {
        return *(zVEC3*)0x008D7F88;
    }

    static zCCamera *GetActiveCam()
    {
        return *((zCCamera **)0x008D7F94);
    }

    static void SetActiveCam(zCCamera *value)
    {
        *((zCCamera **)0x008D7F94) = value;
    }

    zCCamera(void)
    {
        XCALL(0x00549E60);
    }

    ~zCCamera(void)
    {
        XCALL(0x0054A290);
    }

    void Project(class zVEC3 const *const, float &, float &) const
    {
        XCALL(0x00530030);
    }

    void Project(class zVEC3 const *const, int &, int &)
    {
        XCALL(0x0057A440);
    }

    void Project(class zVEC3 const *const, float, float &, float &) const
    {
        XCALL(0x00604ED0);
    }

    void PushTransform(enum zTCamTrafoType)
    {
        XCALL(0x0054A370);
    }

    void PopTransform(enum zTCamTrafoType)
    {
        XCALL(0x0054A400);
    }

    void SetTransform(enum zTCamTrafoType, class zMAT4 const &)
    {
        XCALL(0x0054A540);
    }

    class zMAT4 const &GetTransform(enum zTCamTrafoType)
    {
        XCALL(0x0054A6A0);
    }

    void Activate(void)
    {
        XCALL(0x0054A700);
    }

    float GetFOV(void) const
    {
        XCALL(0x0054A8E0);
    }

    void GetFOV(float &, float &) const
    {
        XCALL(0x0054A8F0);
    }

    void SetFOV(float)
    {
        XCALL(0x0054A920);
    }

    void SetFOV(float, float)
    {
        XCALL(0x0054A960);
    }

    void UpdateViewport(void)
    {
        XCALL(0x0054AA90);
    }

    void SetRenderTarget(class zCViewBase *)
    {
        XCALL(0x0054ABD0);
    }

    void SetRenderScreenFadeTex(zSTRING)
    {
        XCALL(0x0054ABF0);
    }

    void SetUpFrustum(void)
    {
        XCALL(0x0054AD20);
    }

    void SetFarClipZ(float)
    {
        XCALL(0x0054B200);
    }

    enum zTCam_ClipType BBox3DInFrustum(zTBBox3D const &)
    {
        XCALL(0x0054B3B0);
    }

    enum zTCam_ClipType BBox3DInFrustum(zTBBox3D const &, int &)
    {
        XCALL(0x0054B410);
    }

    void StopTremor(void)
    {
        XCALL(0x0054B650);
    }

    void AddTremor(class zVEC3 const &, float, float, class zVEC3 const &)
    {
        XCALL(0x0054B660);
    }

    void PreRenderProcessing(void)
    {
        XCALL(0x0054B7D0);
    }

    void PostRenderProcessing(void)
    {
        XCALL(0x0054B920);
    }

    void GetCamPos(class zVEC3 &) const
    {
        XCALL(0x0054B960);
    }

    /*
    void DrawPolySimple(class zCCamera::zTCamVertSimple *, int, class zCMaterial *, int)
    {
        XCALL(0x0054BAB0);
    }
    */

    void SetRenderScreenFade(zCOLOR)
    {
        XCALL(0x0054BBC0);
    }

    void SetRenderScreenFadeTexAniFPS(float)
    {
        XCALL(0x0054BBE0);
    }

    void SetRenderScreenFadeTexBlendFunc(enum zTRnd_AlphaBlendFunc)
    {
        XCALL(0x0054BC10);
    }

    void SetRenderCinemaScope(zCOLOR)
    {
        XCALL(0x0054BC20);
    }

    int __fastcall ScreenProjectionTouchesPortalRough(class zTBBox3D const &, struct zTBBox2D const &)
    {
        XCALL(0x0054BE80);
    }

    int __fastcall ScreenProjectionTouchesPortal(class zTBBox3D const &, struct zTBBox2D const &)
    {
        XCALL(0x0054C100);
    }

    void ProjectClamp(class zCVertexTransform *, float) const
    {
        XCALL(0x0056BD00);
    }

    class zCVob *CamVob()
    {
        return *(zCVob**)((unsigned int)this + VarOffsets::CamVob);
    }

    void CamVob(class zCVob *value)
    {
        *(zCVob**)((unsigned int)this + VarOffsets::CamVob) = value;
    }

private:
    unsigned char load[0x934];

    void CreateProjectionMatrix(class zMAT4 &, float, float, float, float)
    {
        XCALL(0x0054A810);
    }

    void UpdateProjectionMatrix(void)
    {
        XCALL(0x0054A890);
    }

    void InitDrawPolySimple(void)
    {
        XCALL(0x0054B990);
    }

    void CleanupDrawPolySimple(void)
    {
        XCALL(0x0054BA50);
    }

    void RenderScreenFade(void)
    {
        XCALL(0x0054BC40);
    }

    void RenderCinemaScope(void)
    {
        XCALL(0x0054BD30);
    }
};
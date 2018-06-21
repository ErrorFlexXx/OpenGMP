#include "hView.hpp"
#include "../Gothic/Classes/zCView.hpp"
#include "../Gothic/Classes/zCVob.hpp"
#include "../Gothic/Classes/zCWorld.hpp"
#include "../Gothic/Classes/zCCamera.hpp"
#include "../Gothic/Classes/zCSkyController.hpp"
#include "../Gothic/Classes/zCRenderer.hpp"
#include "../Gothic/Classes/zCEventManager.hpp"
#include "../Gothic/Types/zVEC3.hpp"
#include <limits.h>

using namespace OpenGMP::Hooks;

//Static vars:
bool HView::inited = false;
HView *HView::instance = nullptr;
std::map<zCView*, zCVob*> HView::vobRenderList;
zCWorld *HView::rndrWorld = nullptr;
zCVob *HView::camVob = nullptr;
zCCamera *HView::camera = nullptr;

//Address casting:
typedef void (zCView::*DrawItemsDetourPtr)();
DrawItemsDetourPtr drawItemsAddress = &zCView::DrawItemsDetour; //Get address of detour method.

HView::HView()
    : hookDrawItems(false, (DWORD)zCView::Addresses::DrawItems, (DWORD)(void*&)drawItemsAddress)
{
}

HView *HView::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new HView();
    }
    return instance;
}

void HView::DoHook()
{
    hookDrawItems.DoHook();
}

void HView::UndoHook()
{
    hookDrawItems.UndoHook();
}

/* This one replaces zCView DrawItems */
void zCView::DrawItemsDetour()
{
    auto viewIt = HView::vobRenderList.find(this);
    if (viewIt != HView::vobRenderList.end())
    {
        zCVob *renderVob = viewIt->second;

        if (HView::rndrWorld == nullptr)
        {
            HView::rndrWorld = zCWorld::_CreateInstance();
            HView::rndrWorld->IsInventoryWorld(true);
            HView::rndrWorld->DrawVobBBox3D(false);
            HView::rndrWorld->BspTreeMode(0);
            HView::rndrWorld->GetActiveSkyControler()->FillBackground(false);

            HView::camera = new zCCamera();
            HView::camera->SetFarClipZ((float)INT_MAX);

            HView::camVob = zCVob::_CreateNewInstance();
            HView::rndrWorld->AddVob(HView::camVob);
            HView::camera->CamVob(HView::camVob);
        }

        zCCamera *oldCam = zCCamera::GetActiveCam();
        zCRenderer *renderer = zCRenderer::GetRenderer();
        int light = zCRenderer::PlayerLightInt();

        renderVob->SetPositionWorld(zVEC3(0.f, 0.f, 0.f));
        renderVob->SetGroundPoly(0);
        HView::rndrWorld->AddVob(renderVob);

        zCRenderer::PlayerLightInt(5000);
        renderVob->SetPositionWorld(HView::camVob->Direction() * 150);
        renderVob->SetHeadingWorld(HView::camVob->Position() - renderVob->Position());
        HView::camera->SetRenderTarget(this);
        renderVob->LastTimeDrawn(-1);
        zCEventManager::DisableEventManagers(true);
        renderer->SetAlphaBlendFunc(zTRnd_AlphaBlendFunc::None);
        HView::rndrWorld->Render(*HView::camera);
        zCEventManager::DisableEventManagers(false);
        HView::rndrWorld->RemoveVobSubtree(renderVob);
        zCCamera::SetActiveCam(oldCam);
        zCRenderer::PlayerLightInt(light);
    }
}

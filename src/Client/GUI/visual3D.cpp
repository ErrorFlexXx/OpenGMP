#include "visual3D.hpp"

#include "../Hooks/hView.hpp"
#include "../Gothic/Classes/zCVob.hpp"

using namespace OpenGMP::GUI;

Visual3D::Visual3D(int x, int y, int w, int h)
    : Visual3D(x, y, w, h, false)
{}

Visual3D::Visual3D(int x, int y, int w, int h, bool virtuals)
    : Visual(x, y, w, h, virtuals)
{
    zView->Blit();
    zView->FillZ(true);
}

void Visual3D::Show()
{
    if (shown)
    {
        HView::vobRenderList.erase(zView);
    }
    Visual::Show();
    HView::vobRenderList.insert(std::pair<zCView*, zCVob*>(zView, vob));
}

void Visual3D::Hide()
{
    if (shown)
    {
        HView::vobRenderList.erase(zView);
        Visual::Hide();
    }
}

void Visual3D::SetVob(zCVob *vob)
{
    this->vob = vob;
}

void Visual3D::SetVisual(std::string &name)
{
    vob->SetVisual(name);
}
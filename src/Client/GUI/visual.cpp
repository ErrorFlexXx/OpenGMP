#include "visual.hpp"
#include "visualText.hpp"
#include "../Gothic/Classes/zCViewText.hpp"

using namespace OpenGMP::GUI;

Visual::Visual()
    : Visual(0, 0, 0x2000, 0x2000, true) {}

Visual::Visual(int x, int y, int w, int h)
    : Visual(x, y, w, h, false) {}

Visual::Visual(int x, int y, int w, int h, bool virtuals)
    : Visual(x, y, w, h, virtuals, nullptr) {}

Visual::Visual(int x, int y, int w, int h, bool virtuals, Visual *p)
{
    parent = p;
    if (virtuals)
    {
        vpos.x = x;
        vpos.y = y;
        vsize.x = w;
        vsize.y = h;
    }
    else
    {
        vpos = PixelToVirtual(x, y);
        vsize = PixelToVirtual(w, h);
    }
    zView = new zCView(vpos.x, vpos.y, vpos.x + vsize.x, vpos.y + vsize.y, zTviewID::VIEW_ITEM);
    font = Fonts::Default;
    shown = false;
}

Visual::~Visual()
{
    Hide(); //Hide this visual and all childs.

    delete zView; //Cleanup view
    
    while (0 < texts.size()) //Cleanup texts
    {
        delete texts.front();   //Destroy visual text
        texts.pop_front();      //Remove from list
    }

    while (0 < children.size())  //Cleanup children
    {
        delete children.front(); //Destroy child view
        children.pop_front();    //Remove from list
    }
}

void Visual::Show()
{
    zCView::GetScreen()->InsertItem(zView, 0);
    for (View *child : children)
        child->Show();
    shown = true;
}

void Visual::Hide()
{
    if (shown)
    {
        zCView::GetScreen()->RemoveItem(zView);
        for (View *child : children)
            child->Hide();
        shown = false;
    }
}

VisualText *Visual::CreateTextCenterX(const std::string &text, int y)
{
    VisualText *newText = CreateText(text, 0, y, false);
    newText->SetCenteredX(true);
    return newText;
}

VisualText *Visual::CreateText(const std::string &text)
{
    VisualText * newText = CreateText(text, 0, 0, true);
    newText->SetCenteredX(true);
    newText->SetCenteredY(true);
    return newText;
}

VisualText *Visual::CreateText(const std::string &text, int x, int y)
{
    return CreateText(text, x, y, false);
}

VisualText *Visual::CreateText(const std::string &text, int x, int y, bool virtuals)
{
    VisualText *newText = new VisualText(text, x, y, this, virtuals);
    texts.push_back(newText);
    return newText;
}

void Visual::SetBackTexture(const std::string &tex)
{
    zView->InsertBack(tex);
}

void Visual::SetPosX(int newPosX, bool virtuals)
{
    if (!virtuals)
        newPosX = PixelToVirtualX(newPosX);
    
    int diff = newPosX - vpos.x;
    vpos.x = newPosX;
    zView->SetPos(vpos.x, vpos.y);

    //Update children
    for (View *child : children)
    {
        Visual *visualChild = dynamic_cast<Visual*>(child);
        if (visualChild)
            visualChild->SetPosX(visualChild->vpos.x + diff);
    }
}

void Visual::SetPosY(int newPosY, bool virtuals)
{
    if (!virtuals)
        newPosY = PixelToVirtualY(newPosY);

    int diff = newPosY - vpos.y;
    vpos.y = newPosY;
    zView->SetPos(vpos.x, vpos.y);

    //Update children
    for (View *child : children)
    {
        Visual *visualChild = dynamic_cast<Visual*>(child);
        if (visualChild)
            visualChild->SetPosY(visualChild->vpos.y + diff);
    }
}

void Visual::SetPos(int x, int y, bool virtuals)
{
    ViewPoint newPos;
    newPos.x = x;
    newPos.y = y;
    
    SetPos(newPos, virtuals);
}

void Visual::SetPos(ViewPoint newPos, bool virtuals)
{
    if (!virtuals)
        newPos = PixelToVirtual(newPos);

    int diffX = newPos.x - vpos.x;
    int diffY = newPos.y - vpos.y;
    vpos = newPos;
    zView->SetPos(vpos.x, vpos.y);

    //Update children
    for (View *child : children)
    {
        Visual *visualChild = dynamic_cast<Visual*>(child);
        if (visualChild)
            visualChild->SetPos(visualChild->vpos.x + diffX, visualChild->vpos.y, true);
    }
}

void Visual::SetWidth(int width, bool virtuals)
{
    vsize.x = virtuals ? width : PixelToVirtualX(width);
    zView->SetSize(vsize.x, vsize.y);
}

void Visual::SetHeight(int height, bool virtuals)
{
    vsize.y = virtuals ? height : PixelToVirtualY(height);
    zView->SetSize(vsize.x, vsize.y);
}

void Visual::SetSize(int width, int height, bool virtuals)
{
    ViewPoint newSize;
    newSize.x = width;
    newSize.y = height;

    SetSize(newSize, virtuals);
}

void Visual::SetSize(ViewPoint newSize, bool virtuals)
{
    vsize = virtuals ? newSize : PixelToVirtual(newSize);
    zView->SetSize(vsize.x, vsize.y);
}

View::Fonts Visual::GetFont()
{
    return font;
}

void Visual::SetFont(View::Fonts font)
{
    this->font = font;
    auto it = fontDict.find(font);
    if (it != fontDict.end())
    {
        zView->SetFont(it->second);
        for (VisualText *currentText : texts)
        {
            currentText->GetZViewText()->SetFont(it->second);
            currentText->SetCenteredX(currentText->GetCenteredX()); //Update centering
        }
    }
}

ViewPoint Visual::GetPosition()
{
    return vpos;
}

ViewPoint Visual::GetSize()
{
    return vsize;
}

View *Visual::GetParent()
{
    return parent;
}

zCView *Visual::GetZView()
{
    return zView;
}

bool Visual::Shown()
{
    return shown;
}

const std::list<VisualText*> &Visual::Texts()
{
    return texts;
}
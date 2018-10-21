#include "notificationBox.hpp"
#include <Shared/Components/gameTime.hpp>
#include <Client/GUI/visualtext.hpp>

using namespace OpenGMP;
using namespace OpenGMP::GUI;
using namespace OpenGMP::Components;

NotificationBox::NotificationBox()
    : NotificationText()
    , shown(0)
    , inited(0)
{
}

void NotificationBox::Create()
{
    ViewPoint screenSize = View::GetPixelScreenSize();
    ViewPoint dim;
    dim.x = (int)(640);
    dim.y = (int)(50);
    pos.x = (screenSize.x - dim.x) / 2;
    pos.y = this->posY;
    vis = new Visual(pos.x, pos.y, dim.x, dim.y);
    vis->SetBackTexture("Menu_Ingame.tga");
    vis->SetFont(Visual::Fonts::Default);
    vis->CreateTextCenterX(this->text, 20);
}

void NotificationBox::Update(unsigned long long now)
{
    if (startTimeMS != 0 &&
        shown)
    {
        if (now > startTimeMS + durationMS)
            Hide();
    }
}

void NotificationBox::Show()
{
    if (!inited)
    {
        inited = 1;
        Create();
    }
    if (duration != 0)
    {
        startTimeMS = GameTime::GetTicks();
        durationMS = duration * 1000;
    }
    else
        startTimeMS = 0;
    VisualText *visText = vis->Texts().front();
    visText->SetText(text); //Update text
    visText->SetColor(zCOLOR(this->color));
    vis->SetPosY(this->posY);
    vis->Show();
    shown = 1;
}

void NotificationBox::Hide()
{
    if(shown)
        vis->Hide();
    shown = 0;
    startTimeMS = 0;
}
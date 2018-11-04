#include "menuSystem.hpp"
#include <Client/gameClient.hpp>
#include <Client/GUI/menu.hpp>
#include <Shared/Types/Messages/menuSystemMessages.hpp>
#include <Shared/Components/notificationText.hpp>
#include <Shared/Components/gameTime.hpp>
#include <BitStream.h>
#include <libintl.h>
#define _(string) gettext (string)

using namespace OpenGMP;
using namespace RakNet;

MenuSystem::MenuSystem(GameClient &gameClient)
    : gameClient(gameClient)
    , menuMain(gameClient)
    , menuRegister(gameClient)
    , menuLogin(gameClient)
    , notification()
{}

void MenuSystem::CloseActiveMenus()
{
    while (0 < GUI::Menu::activeMenus.size())
    {
        GUI::Menu *menu = GUI::Menu::activeMenus.back();
        menu->Close();
    }
}

bool MenuSystem::IsMenuActive()
{
    return 0 < GUI::Menu::activeMenus.size();
}

bool MenuSystem::KeyDownUpdateMenus(VirtualKeys key)
{
    if (0 < GUI::Menu::activeMenus.size())
    {
        GUI::Menu::activeMenus.front()->KeyDown(key);
        return true;
    }
    return false;
}

bool MenuSystem::KeyUpUpdateMenus(VirtualKeys key)
{
    if (0 < GUI::Menu::activeMenus.size())
    {
        GUI::Menu::activeMenus.front()->KeyUp(key);
        return true;
    }
    return false;
}

void MenuSystem::UpdateMenus(unsigned long long now)
{
    for (GUI::Menu *menu : GUI::Menu::activeMenus)
    {
        menu->Update(now);
    }
}

void MenuSystem::UpdateNotification(unsigned long long now)
{
    notification.Update(now);
}

void MenuSystem::ShowNotification(int posY, std::string &text, Color &color, uint32_t duration)
{
    notification.text = text;
    notification.posY = posY;
    notification.color = color;
    notification.duration = duration;
    notification.Show();
}

void MenuSystem::HideNotification()
{
    notification.Hide();
}

void MenuSystem::Process(RakNet::Packet *packet)
{
    NetMessage command;
    BitStream bsIn(packet->data, packet->length, false);
    bsIn.IgnoreBytes(1); //MenuSystem
    bsIn.Read(command); //Read command

    switch (command)
    {
        case MenuSystemMessages::SHOW_NOTIFICATION:
        {
            if (notification.shown)
                notification.Hide();
            if (notification.ReadStream(bsIn))
            {
                notification.duration = 0;
                notification.Show();
            }
            break;
        }
        case SHOW_TIMED_NOTIFICATION:
        {
            if (notification.shown)
                notification.Hide();
            if (notification.ReadStream(bsIn))
            {
                notification.Show();
            }
            break;
        }
        case MenuSystemMessages::HIDE_NOTIFICATION:
        {
            if (notification.shown)
                notification.Hide();
            break;
        }
        default:
        {
#ifdef DBG_NETWORK
            gameClient.menuSystem.ShowNotification(
                20,
                std::string(_("MenuSystem RakNet Message not handled! ID is")).append(": ").append(std::to_string((int)command)).append("!"),
                Color(255, 0, 0, 255),
                10
            );
#endif
        }
    }
}
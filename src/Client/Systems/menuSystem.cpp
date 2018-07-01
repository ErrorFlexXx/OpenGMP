#include "menuSystem.hpp"
#include "../gameClient.hpp"
#include "../GUI/menu.hpp"

using namespace OpenGMP;
using namespace OpenGMP::Systems;
using namespace OpenGMP::Types;

MenuSystem::MenuSystem(GameClient &gameClient)
    : gameClient(gameClient)
    , menuMain(gameClient)
    , menuRegister(gameClient)
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
#include "menuSystem.hpp"
#include "../gameClient.hpp"
#include "../GUI/menu.hpp"
#include "../Menus/ogmpMainMenu.hpp"
#include "../Menus/ogmpRegisterMenu.hpp"

using namespace OpenGMP;
using namespace OpenGMP::Systems;
using namespace OpenGMP::Types;

MenuSystem::MenuSystem(GameClient &gameClient)
    : gameClient(gameClient)
{}

void MenuSystem::OpenMainMenu()
{
    CloseActiveMenus(); //MainMenus never overlap

    //Lookup OpenGMP Main Menu
    for (GUI::Menu *menu : createdMenus)
    {
        Menus::OGMPMainMenu *mainMenu = dynamic_cast<Menus::OGMPMainMenu*>(menu);
        if (mainMenu) //Found ?
        {
            mainMenu->Open();
            return;
        }
    }
    //No main menu found -- Create one
    Menus::OGMPMainMenu *mainMenu = new Menus::OGMPMainMenu(gameClient);
    createdMenus.push_back(mainMenu);
    mainMenu->Open();
}

void MenuSystem::OpenRegisterMenu()
{
    CloseActiveMenus(); //MainMenus never overlap

    //Lookup OpenGMP Main Menu
    for (GUI::Menu *menu : createdMenus)
    {
        Menus::OGMPRegisterMenu *registerMenu = dynamic_cast<Menus::OGMPRegisterMenu*>(menu);
        if (registerMenu) //Found ?
        {
            registerMenu->Open();
            return;
        }
    }
    //No main menu found -- Create one
    Menus::OGMPRegisterMenu *registerMenu = new Menus::OGMPRegisterMenu(gameClient);
    createdMenus.push_back(registerMenu);
    registerMenu->Open();
}

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
#include "menu.hpp"
#include "../gameClient.hpp"
#include "../Systems/inputSystem.hpp"

using namespace OpenGMP;
using namespace OpenGMP::GUI;

std::list<GUI::Menu*> Menu::activeMenus;

Menu::Menu(GameClient &gameClient)
    : gameClient(gameClient)
    , opened(false)
{}

bool Menu::Opened()
{
    return opened;
}

void Menu::Open()
{
    if (opened)
        activeMenus.remove(this);
    activeMenus.push_front(this);
    gameClient.inputSystem.keyDownReceipient = [=](VirtualKeys key) { this->KeyDown(key); };
    opened = true;
}

void Menu::Close()
{
    if (opened)
    {
        activeMenus.remove(this);
        gameClient.inputSystem.keyDownReceipient = nullptr;
        opened = false;
    }
}

void Menu::KeyDown(VirtualKeys key)
{}

void Menu::KeyUp(VirtualKeys key)
{}

void Menu::Update(unsigned long long now)
{}

void Menu::CloseActiveMenus()
{
    while (0 < activeMenus.size())
    {
        Menu *menu = activeMenus.back();
        menu->Close();
    }
}
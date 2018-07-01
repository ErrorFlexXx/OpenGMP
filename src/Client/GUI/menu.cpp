#include "menu.hpp"
#include "../gameClient.hpp"
#include "../Systems/inputSystem.hpp"

using namespace OpenGMP;
using namespace OpenGMP::GUI;
using namespace OpenGMP::Systems;

std::list<Menu*> Menu::activeMenus;

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
    gameClient.inputSystem.keyDownReceipient = [=](Types::VirtualKeys key) { this->KeyDown(key); };
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

void Menu::KeyDown(Types::VirtualKeys key)
{}

void Menu::KeyUp(Types::VirtualKeys key)
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
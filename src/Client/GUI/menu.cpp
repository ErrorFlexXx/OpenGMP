#include "menu.hpp"
#include <Client/Controls/inputHandler.hpp>

using namespace OpenGMP::GUI;

std::list<Menu*> Menu::activeMenus;

Menu::Menu()
    : opened(false)
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
    InputHandler::keyDownReceipient = [=](VirtualKeys key) { this->KeyDown(key); };
    opened = true;
}

void Menu::Close()
{
    if (opened)
    {
        activeMenus.remove(this);
        InputHandler::keyDownReceipient = nullptr;
        opened = false;
    }
}

void Menu::KeyDown(OpenGMP::VirtualKeys key)
{}

void Menu::KeyUp(OpenGMP::VirtualKeys key)
{}

void Menu::Update(unsigned long long now)
{}
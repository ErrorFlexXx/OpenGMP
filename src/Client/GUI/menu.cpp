#include "menu.hpp"
#include <Client/Core/inputHandler.hpp>

using namespace OpenGMP::GUI;

std::list<Menu*> Menu::activeMenus;

Menu::Menu()
    : opened(false)
{}

bool Menu::IsMenuActive()
{
    return 0 < activeMenus.size();
}

bool Menu::KeyDownUpdateMenus(OpenGMP::VirtualKeys key)
{
    if (0 < activeMenus.size())
    {
        activeMenus.front()->KeyDown(key);
        return true;
    }
    return false;
}

bool Menu::KeyUpUpdateMenus(OpenGMP::VirtualKeys key)
{
    if (0 < activeMenus.size())
    {
        activeMenus.front()->KeyUp(key);
        return true;
    }
    return false;
}

void Menu::UpdateMenus(unsigned long long now)
{
    for (Menu *menu : activeMenus)
    {
        menu->Update(now);
    }
}

void Menu::CloseActiveMenus()
{
    if (0 < activeMenus.size())
    {
        auto it = activeMenus.end();
        while(it-- != activeMenus.begin())
        {
            (*it)->Close();
        }
    }
}

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
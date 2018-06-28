#pragma once

#include "../Controls/virtualKeys.hpp"
#include <list>

namespace OpenGMP
{
    namespace GUI
    {
        class Menu;
    }

    namespace Systems
    {
        class MenuSystem
        {
        public:
            MenuSystem();

            static void OpenMainMenu();
            static void OpenRegisterMenu();
            static void CloseActiveMenus();
            static bool IsMenuActive();
            static bool KeyDownUpdateMenus(VirtualKeys key);
            static bool KeyUpUpdateMenus(OpenGMP::VirtualKeys key);
            static void UpdateMenus(unsigned long long now);

            static std::list<GUI::Menu*> createdMenus;
        };
    }
}
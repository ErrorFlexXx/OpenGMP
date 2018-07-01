#pragma once

#include "../Types/virtualKeys.hpp"
#include <list>

namespace OpenGMP
{
    class GameClient;

    namespace GUI
    {
        class Menu;
    }

    namespace Systems
    {
        class MenuSystem
        {
        public:
            MenuSystem(GameClient &gameClient);

            void OpenMainMenu();
            void OpenRegisterMenu();
            void CloseActiveMenus();
            bool IsMenuActive();
            bool KeyDownUpdateMenus(Types::VirtualKeys key);
            bool KeyUpUpdateMenus(Types::VirtualKeys key);
            void UpdateMenus(unsigned long long now);

            std::list<GUI::Menu*> createdMenus;

        private:
            GameClient &gameClient;
        };
    }
}
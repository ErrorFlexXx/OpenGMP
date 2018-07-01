#pragma once

#include "../Types/virtualKeys.hpp"
#include "../Components/menuMain.hpp"
#include "../Components/menuRegister.hpp"
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
            
            void CloseActiveMenus();
            bool IsMenuActive();
            bool KeyDownUpdateMenus(Types::VirtualKeys key);
            bool KeyUpUpdateMenus(Types::VirtualKeys key);
            void UpdateMenus(unsigned long long now);

            Components::MenuMain menuMain;
            Components::MenuRegister menuRegister;

        private:
            GameClient &gameClient;
        };
    }
}
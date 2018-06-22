#pragma once

#include "../GUI/mainMenu.hpp"

namespace OpenGMP
{
    namespace GUI
    {
        class MenuButton;
    }

    namespace Menus
    {
        class OGMPMainMenu : public GUI::MainMenu
        {
        public:
            OGMPMainMenu();
            virtual void OnCreate() override;
            virtual void Open() override;

        private:
            GUI::MenuButton *btnLogin;
            GUI::MenuButton *btnRegister;
            GUI::MenuButton *btnQuit;
            bool ingame;
        };
    }
}
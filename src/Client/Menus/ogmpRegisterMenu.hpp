#pragma once

#include "../GUI/mainMenu.hpp"

namespace OpenGMP
{
    namespace GUI
    {
        class MenuButton;
        class MenuTextBox;
    }

    namespace Menus
    {
        class OGMPRegisterMenu : public GUI::MainMenu
        {
        public:
            OGMPRegisterMenu() {};
            virtual void OnCreate() override;
            virtual void Open() override;
            void Register();
            void ToggleShowPassword();

        private:
            GUI::MenuTextBox *txtUsername;
            GUI::MenuTextBox *txtPassword;
            GUI::MenuButton *btnShowPassword;
            GUI::MenuButton *btnCreate;
            GUI::MenuButton *btnBack;
        };
    }
}
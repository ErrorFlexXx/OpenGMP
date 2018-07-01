#pragma once

#include "../GUI/mainMenu.hpp"

namespace OpenGMP
{
    class GameClient;

    namespace GUI
    {
        class MenuButton;
        class MenuTextBox;
    }

    namespace Components
    {
        class MenuRegister : public GUI::MainMenu
        {
        public:
            MenuRegister(GameClient &gameClient);
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
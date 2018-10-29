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

    class MenuLogin : public GUI::MainMenu
    {
    public:
        MenuLogin(GameClient &gameClient);
        virtual void OnCreate() override;
        virtual void Open() override;
        void Login();
        void DisableLoginButton();
        void EnableLoginButton();
        void ToggleShowPassword();

    private:
        GUI::MenuTextBox *txtUsername;
        GUI::MenuTextBox *txtPassword;
        GUI::MenuButton *btnShowPassword;
        GUI::MenuButton *btnLogin;
        GUI::MenuButton *btnBack;
    };
}
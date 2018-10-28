#pragma once

#include "../GUI/mainMenu.hpp"

class CGameManager;

namespace OpenGMP
{
    class GameClient;

    namespace GUI
    {
        class MenuButton;
    }

    class MenuMain : public GUI::MainMenu
    {
    public:
        MenuMain(GameClient &gameClient);
        virtual void OnCreate() override;
        virtual void Open() override;
        void EnableNetworkElements();
        void DisableNetworkElements();

    private:
        GUI::MenuButton *btnLogin;
        GUI::MenuButton *btnRegister;
        GUI::MenuButton *btnQuit;
        CGameManager *gameManager;
        bool ingame;
    };
}
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

    namespace Menus
    {
        class OGMPMainMenu : public GUI::MainMenu
        {
        public:
            OGMPMainMenu(GameClient &gameClient);
            virtual void OnCreate() override;
            virtual void Open() override;

        private:
            GUI::MenuButton *btnLogin;
            GUI::MenuButton *btnRegister;
            GUI::MenuButton *btnQuit;
            CGameManager *gameManager;
            bool ingame;
        };
    }
}
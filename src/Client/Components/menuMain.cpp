#include "menuMain.hpp"
#include "../gameClient.hpp"
#include "../GUI/menuButton.hpp"
#include "../Gothic/cGameManager.hpp"
#include "../Systems/menuSystem.hpp"
#include <libintl.h>
#define _(string) gettext (string)

using namespace OpenGMP;

MenuMain::MenuMain(GameClient &gameClient)
    : MainMenu(gameClient)
    , ingame(false)
{
}

void MenuMain::OnCreate()
{
    MainMenu::OnCreate();
    gameManager = CGameManager::GetInstance();
    back->CreateTextCenterX(_("Mainmenu"), 70);

    const int offset = 200;
    const int dist = 38;

    btnLogin = AddButton(_("Login"), _("Log into an existing account."), offset + dist * 0, [=]() { gameClient.menuSystem.menuLogin.Open(); });
    btnRegister = AddButton(_("Register"), _("Create a new account."), offset + dist * 1, [=]() { gameClient.menuSystem.menuRegister.Open(); });
    btnQuit = AddButton(_("Quit"), _("Quit the game. Switch to the desktop."), offset + dist * 3, [=]() { gameManager->ExitGame(); });
    
    btnLogin->Enabled(false);
    btnRegister->Enabled(false);
    btnQuit->Enabled(true);
}

void MenuMain::Open()
{
    OpenGMP::GUI::MainMenu::Open();
}

void MenuMain::EnableNetworkElements()
{
    btnLogin->Enabled(true);
    btnRegister->Enabled(true);
}

void MenuMain::DisableNetworkElements()
{
    btnLogin->Enabled(false);
    btnRegister->Enabled(false);
}
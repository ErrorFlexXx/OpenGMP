#include "ogmpMainMenu.hpp"
#include "../GUI/menuButton.hpp"
#include "../Gothic/cGameManager.hpp"
#include "../Systems/menuSystem.hpp"

using namespace OpenGMP::Menus;

OGMPMainMenu::OGMPMainMenu()
    : ingame(false)
{
    gameManager = CGameManager::GetInstance();
}

void OGMPMainMenu::OnCreate()
{
    back->CreateTextCenterX("Hauptmenü", 70);
    const int offset = 200;
    const int dist = 38;

    btnLogin = AddButton("Anmelden", "In einen bestehenden Account einloggen.", offset + dist * 0, nullptr);
    btnRegister = AddButton("Registrieren", "Einen neuen Account erstellen.", offset + dist * 1, []() { Systems::MenuSystem::OpenRegisterMenu(); });
    btnQuit = AddButton("Beenden", "Beendet das Spiel. Wechsel zum Desktop.", offset + dist * 3, [=]() { gameManager->ExitGame(); });
}

void OGMPMainMenu::Open()
{
    OpenGMP::GUI::MainMenu::Open();
    if (ingame) //loggedin
    {
        btnLogin->Enabled(false);
        btnRegister->Enabled(false);
        btnQuit->Enabled(true);
    }
    else //not logged in
    {
        btnLogin->Enabled(true);
        btnRegister->Enabled(true);
        btnQuit->Enabled(true);
    }
}
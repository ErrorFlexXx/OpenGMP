#include "ogmpMainMenu.hpp"
#include "../GUI/menuButton.hpp"

using namespace OpenGMP::Menus;

OGMPMainMenu::OGMPMainMenu()
    : ingame(false)
{}

void OGMPMainMenu::OnCreate()
{
    back.CreateTextCenterX("Hauptmenü", 70);
    const int offset = 200;
    const int dist = 38;

    btnLogin = AddButton("Anmelden", "In einen bestehenden Account einloggen.", offset + dist * 0, nullptr);
    btnRegister = AddButton("Registrieren", "Einen neuen Account erstellen.", offset + dist * 1, nullptr);
    btnQuit = AddButton("Beenden", "Beendet das Spiel. Wechsel zum Desktop.", offset + dist * 3, [=] () { exit(0); });
}

void OGMPMainMenu::Open()
{
    OpenGMP::GUI::MainMenu::Open();
    if (ingame) //loggedin
    {
        ;
    }
    else //not logged in
    {
        ;
    }
}
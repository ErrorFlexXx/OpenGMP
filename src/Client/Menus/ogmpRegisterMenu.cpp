#include "ogmpRegisterMenu.hpp"
#include "../GUI/menuButton.hpp"
#include "../GUI/menuTextBox.hpp"
#include "../Systems/menuSystem.hpp"

using namespace OpenGMP::Menus;
using namespace OpenGMP::GUI;

const std::string btnShowPasswordTextShow = "Zeige Passwort";
const std::string btnShowPasswordTextHide = "Verberge Passwort";

void OGMPRegisterMenu::OnCreate()
{
    back->CreateTextCenterX("Registrierung", 70);
    const int offset = 200;
    const int dist = 38;

    txtUsername = AddTextBox("Benutzername", "Benutzername des neuen Benutzers.", offset + dist * 0, 280, nullptr);
    txtPassword = AddTextBox("Passwort", "Passwort des neuen Benutzers.", offset + dist * 1, 280, nullptr, true);
    btnShowPassword = AddButton(btnShowPasswordTextShow, "Schaltet die Klartext-Passwortanzeige um.", offset + dist * 2, [=]() { this->ToggleShowPassword(); });
    btnCreate = AddButton("Registrieren", "Erstellt einen neuen Benutzer.", offset + dist * 4, [=]() { this->Register(); });
    btnBack = AddButton("Zurück", "Zum Hauptmenü zurückkehren.", offset + dist * 5, []() {Systems::MenuSystem::OpenMainMenu(); });
}

void OGMPRegisterMenu::Open()
{
    OpenGMP::GUI::MainMenu::Open();
    
    txtUsername->Enabled(true);
    txtPassword->Enabled(true);
    btnShowPassword->Enabled(true);
    btnCreate->Enabled(true);
    btnBack->Enabled(true);
}

void OGMPRegisterMenu::Register()
{
    ;
}

void OGMPRegisterMenu::ToggleShowPassword()
{
    bool isPasswordText = !txtPassword->GetPasswordText();
    txtPassword->SetPasswordText(isPasswordText);
    if (isPasswordText)
        btnShowPassword->Text(btnShowPasswordTextShow);
    else
        btnShowPassword->Text(btnShowPasswordTextHide);
}
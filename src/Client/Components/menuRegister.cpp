#include "menuRegister.hpp"
#include "../gameClient.hpp"
#include "../GUI/menuButton.hpp"
#include "../GUI/menuTextBox.hpp"
#include "../Systems/menuSystem.hpp"
#include <libintl.h>
#define _(string) gettext (string)

using namespace OpenGMP;
using namespace OpenGMP::GUI;

std::string MenuRegister::btnShowPasswordTextShow;
std::string MenuRegister::btnShowPasswordTextHide;

MenuRegister::MenuRegister(GameClient &gameClient)
    : MainMenu(gameClient)
{}

void MenuRegister::OnCreate()
{
    btnShowPasswordTextShow = _("Show password");
    btnShowPasswordTextHide = _("Hide password");

    MainMenu::OnCreate();
    back->CreateTextCenterX(_("Registration"), 70);
    const int offset = 200;
    const int dist = 38;

    txtUsername = AddTextBox(_("Username"), _("Username of the created user."), offset + dist * 0, 280, nullptr);
    txtPassword = AddTextBox(_("Password"), _("Password of the created user."), offset + dist * 1, 280, nullptr, true);
    btnShowPassword = AddButton(btnShowPasswordTextShow, _("Toggles the password plain text view."), offset + dist * 2, [=]() { this->ToggleShowPassword(); });
    btnCreate = AddButton(_("Register"), _("Creates a new user."), offset + dist * 4, [=]() { this->Register(); });
    btnBack = AddButton(_("Back"), _("Goes back to the main menu."), offset + dist * 5, [=]() {gameClient.menuSystem.menuMain.Open(); });

    txtUsername->Enabled(true);
    txtPassword->Enabled(true);
    btnShowPassword->Enabled(true);
    btnCreate->Enabled(true);
    btnBack->Enabled(true);
}

void MenuRegister::Open()
{
    OpenGMP::GUI::MainMenu::Open();
}

void MenuRegister::Register()
{
    gameClient.client.loginData.loginname = (std::string)*txtUsername;
    gameClient.client.loginData.password = (std::string)*txtPassword;
    gameClient.loginSystem.SendRegister(gameClient.client.loginData);
}

void MenuRegister::ToggleShowPassword()
{
    bool isPasswordText = !txtPassword->GetPasswordText();
    txtPassword->SetPasswordText(isPasswordText);
    if (isPasswordText)
        btnShowPassword->Text(btnShowPasswordTextShow);
    else
        btnShowPassword->Text(btnShowPasswordTextHide);
}

void MenuRegister::DisableRegisterButton()
{
    btnCreate->Enabled(false);
}

void MenuRegister::EnableRegisterButton()
{
    btnCreate->Enabled(true);
}
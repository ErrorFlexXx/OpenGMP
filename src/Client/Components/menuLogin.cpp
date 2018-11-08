#include "menuLogin.hpp"
#include "../gameClient.hpp"
#include "../GUI/menuButton.hpp"
#include "../GUI/menuTextBox.hpp"
#include "../Systems/menuSystem.hpp"
#include <libintl.h>
#define _(string) gettext (string)

using namespace OpenGMP;
using namespace OpenGMP::GUI;

std::string MenuLogin::btnShowPasswordTextShow;
std::string MenuLogin::btnShowPasswordTextHide;

MenuLogin::MenuLogin(GameClient &gameClient)
    : MainMenu(gameClient)
{}

void MenuLogin::OnCreate()
{
    btnShowPasswordTextShow = _("Show password");
    btnShowPasswordTextHide = _("Hide password");

    MainMenu::OnCreate();
    back->CreateTextCenterX(_("Login"), 70);
    const int offset = 200;
    const int dist = 38;

    txtUsername = AddTextBox(_("Username"), _("Username to log into."), offset + dist * 0, 280, nullptr);
    txtPassword = AddTextBox(_("Password"), _("Password of the user."), offset + dist * 1, 280, nullptr, true);
    btnShowPassword = AddButton(btnShowPasswordTextShow, _("Toggles the password plain text view."), offset + dist * 2, [=]() { this->ToggleShowPassword(); });
    btnLogin = AddButton(_("Login"), _("Login with given credentials."), offset + dist * 4, [=]() { this->Login(); });
    btnBack = AddButton(_("Back"), _("Goes back to the main menu."), offset + dist * 5, [=]() {gameClient.menuSystem.menuMain.Open(); });

    txtUsername->Enabled(true);
    txtPassword->Enabled(true);
    btnShowPassword->Enabled(true);
    btnLogin->Enabled(true);
    btnBack->Enabled(true);
}

void MenuLogin::Open()
{
    OpenGMP::GUI::MainMenu::Open();
}

void MenuLogin::Login()
{
    gameClient.client.loginData.loginname = *txtUsername;
    gameClient.client.loginData.password = *txtPassword;
    gameClient.loginSystem.SendLogin(gameClient.client.loginData);
}

void MenuLogin::ToggleShowPassword()
{
    bool isPasswordText = !txtPassword->GetPasswordText();
    txtPassword->SetPasswordText(isPasswordText);
    if (isPasswordText)
        btnShowPassword->Text(btnShowPasswordTextShow);
    else
        btnShowPassword->Text(btnShowPasswordTextHide);
}

void MenuLogin::DisableLoginButton()
{
    btnLogin->Enabled(false);
}

void MenuLogin::EnableLoginButton()
{
    btnLogin->Enabled(true);
}
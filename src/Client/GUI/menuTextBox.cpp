#include "menuTextBox.hpp"
#include "visualText.hpp"
#include "textBox.hpp"

using namespace OpenGMP;
using namespace OpenGMP::GUI;

const int MenuTextBox::defaultHeight = 35;
const std::string MenuTextBox::defaultBackTexture = "Menu_Choice_Back.tga";

MenuTextBox::MenuTextBox(const std::string &help, int x, int y, int width, std::function<void()> action, bool passwordText)
    : MenuTextBox("", help, x, y, width, defaultHeight, 0, action, passwordText) {}

MenuTextBox::MenuTextBox(const std::string &title, const std::string &help, int x, int y, int width, int titleX, std::function<void()> action, bool passwordText)
    : MenuTextBox(title, help, x, y, width, defaultHeight, titleX, action, passwordText) {}

MenuTextBox::MenuTextBox(const std::string &title, const std::string &help, int x, int y, int width, int height, int titleX, std::function<void()> action, bool passwordText)
    : MenuTextBox(title, help, x, y, width, height, titleX, y, action, passwordText) {}

MenuTextBox::MenuTextBox(const std::string &title, const std::string &help, int x, int y, int width, int height, int titleX, int titleY, std::function<void()> action, bool passwordText)
    : MenuTextBox(defaultBackTexture, title, help, x, y, width, height, titleX, titleY, action, passwordText) {}

MenuTextBox::MenuTextBox(const std::string &backTexture, const std::string &title, const std::string &help, int x, int y, int width, int height, int titleX, int titleY, std::function<void()> action, bool passwordText)
    : vis(x, y, width, height)
    , tb(x + 15, y + 7, width - 30, false, passwordText)
{
    helpText = help;
    onAction = action;
    this->backTexture = backTexture;
    
    titleVis = VisualText::Create(title, titleX, titleY);
    titleVis->SetFont(Fonts::Menu);

    vis.SetBackTexture(backTexture);
    
    tb.allowSpaces = false;
    Update = [=](unsigned long long now) { tb.Update(now); };
}

void MenuTextBox::Select()
{
    titleVis->SetFont(Fonts::Menu_Hi);
    tb.Enabled(true);
}

void MenuTextBox::Deselect()
{
    titleVis->SetFont(Fonts::Menu);
    tb.Enabled(false);
}

void MenuTextBox::Show()
{
    titleVis->Show();
    vis.Show();
    tb.Show();
}

void MenuTextBox::Hide()
{
    titleVis->Hide();
    vis.Hide();
    tb.Hide();
}

void MenuTextBox::KeyPressed(VirtualKeys key)
{
    tb.KeyPressed(key);
}

bool MenuTextBox::GetPasswordText()
{
    return tb.GetPasswordText();
}

void MenuTextBox::SetPasswordText(bool value)
{
    tb.SetPasswordText(value);
}
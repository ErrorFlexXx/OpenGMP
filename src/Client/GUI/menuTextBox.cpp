#include "menuTextBox.hpp"
#include "visualText.hpp"
#include "textBox.hpp"

using namespace OpenGMP;
using namespace OpenGMP::GUI;

const int MenuTextBox::defaultHeight = 30;
const std::string MenuTextBox::defaultBackTexture = "Menu_Choice_Back.tga";

MenuTextBox::MenuTextBox(const std::string &help, int x, int y, int width, std::function<void()> action)
    : MenuTextBox("", help, x, y, width, defaultHeight, 0, action) {}

MenuTextBox::MenuTextBox(const std::string &title, const std::string &help, int x, int y, int width, int titleX, std::function<void()> action)
    : MenuTextBox(title, help, x, y, width, defaultHeight, titleX, action) {}

MenuTextBox::MenuTextBox(const std::string &title, const std::string &help, int x, int y, int width, int height, int titleX, std::function<void()> action)
    : MenuTextBox(title, help, x, y, width, height, titleX, y + (height - fontSizeMenu) / 2, action) {}

MenuTextBox::MenuTextBox(const std::string &title, const std::string &help, int x, int y, int width, int height, int titleX, int titleY, std::function<void()> action)
    : MenuTextBox(defaultBackTexture, title, help, x, y, width, height, titleX, titleY, action) {}

MenuTextBox::MenuTextBox(const std::string &backTexture, const std::string &title, const std::string &help, int x, int y, int width, int height, int titleX, int titleY, std::function<void()> action)
    : vis(x, y, width, height)
    , tb(x + 15, y + 5, width - 30, true)
{
    helpText = help;
    onAction = action;
    this->backTexture = backTexture;
    
    titleVis = VisualText::Create(title, titleX, titleY);
    
    vis.SetBackTexture(backTexture);
    
    tb.allowSpaces = false;
    Update = [=](unsigned long long now) { tb.Update(now); };
}

void MenuTextBox::Select()
{
    titleVis->SetFont(Fonts::Menu_Hi);
    tb.enabled = true;
}

void MenuTextBox::Deselect()
{
    titleVis->SetFont(Fonts::Menu);
    tb.enabled = false;
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
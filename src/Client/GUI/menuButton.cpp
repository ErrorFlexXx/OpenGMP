#include "menuButton.hpp"

using namespace OpenGMP::GUI;

MenuButton::MenuButton(const std::string &text, const std::string &help, int y, std::function<void()> action, Fonts font)
    : MenuButton(text, help, 0, y, action, font)
{
    visualText->SetCenteredX(true);
}

MenuButton::MenuButton(const std::string &text, const std::string &help, int x, int y, std::function<void()> action, Fonts font)
{
    helpText = help;
    visual = VisualText::Create(text, x, y);
    visualText = visual->Texts().front();
    visualText->SetFormat(TextFormat::Center);
    visual->SetFont(font);
    this->onAction = action;
}

void MenuButton::Show()
{
    visual->Show();
}

void MenuButton::Hide()
{
    visual->Hide();
}

void MenuButton::Select()
{
    if (visual->GetFont() == Fonts::Menu)
        visual->SetFont(Fonts::Menu_Hi);
    else if (visual->GetFont() == Fonts::Default)
        visual->SetFont(Fonts::Default_Hi);
}

void MenuButton::Deselect()
{
    if (visual->GetFont() == Fonts::Menu_Hi)
        visual->SetFont(Fonts::Menu);
    else if (visual->GetFont() == Fonts::Default_Hi)
        visual->SetFont(Fonts::Default);
}

bool MenuButton::Enabled()
{
    return enabled;
}

void MenuButton::Enabled(bool value)
{
    enabled = value;
    if (value)
        visualText->SetColor(*zCOLOR_WHITE());
    else
        visualText->SetColor(*zCOLOR_GREY());
}

ViewPoint MenuButton::Position()
{
    return visualText->GetPosition();
}

void MenuButton::Text(const std::string &text)
{
    visualText->SetText(text);
}

const std::string &MenuButton::Text()
{
    return visualText->GetText();
}

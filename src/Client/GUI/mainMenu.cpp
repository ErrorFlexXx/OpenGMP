#include "mainMenu.hpp"
#include "visualText.hpp"
#include "menuItem.hpp"
#include "menuButton.hpp"
#include "menuTextBox.hpp"
#include <Shared\gameTime.hpp>

using namespace OpenGMP::GUI;

MainMenu::MainMenu()
{
    cursor = 0;
    preferredCursorItem = 0;
    ViewPoint screenSize = View::GetScreenSize();
    ViewPoint dim;
    dim.x = (int)((double)screenSize.x * 1.0 / 3.0);
    dim.y = (int)((double)screenSize.y * 2.0 / 3.0);
    pos.x = (screenSize.x - dim.x) / 2;
    pos.y = (screenSize.y - dim.y) / 2;
    isOpen = false;
    init = false;
    helpTextNextUpdateTime = 0;
    back = new Visual(pos.x, pos.y, dim.x, dim.y);
    back->SetBackTexture("Menu_Ingame.tga");
    back->SetFont(Visual::Fonts::Menu);
    helpVis = VisualText::Create("", 0, pos.y + (int)((double)dim.y * 9.0 / 10.0));
    HelpText()->SetCenteredX(true);
    
    //Setup key strokes for actions:
    std::list<VirtualKeys> combUp;
    combUp.push_back(VirtualKeys::Up);
    std::list<VirtualKeys> combDown;
    combDown.push_back(VirtualKeys::Down);
    std::list<VirtualKeys> combTab;
    combTab.push_back(VirtualKeys::Tab);
    std::function<void()> actionScrollUp = [=]() { this->MoveCursor(true); };
    std::function<void()> actionScrollDown = [=]() { this->MoveCursor(false); };
    scrollHelper.Add(combUp, actionScrollUp);
    scrollHelper.Add(combDown, actionScrollDown);
    scrollHelper.Add(combTab, actionScrollDown);
}

MenuItem *MainMenu::CurrentItem()
{
    if (0 <= cursor && cursor < items.size()) //Valid cursor range ?
    {
        return items[cursor];
    }
    return nullptr;
}

bool MainMenu::IsOpen()
{
    return isOpen;
}

void MainMenu::Open()
{
    CloseActiveMenus(); //MainMenus never overlap

    if (!init)
    {
        OnCreate();
        init = true;
    }

    Menu::Open();
    back->Show();
    helpVis->Show();
    for (MenuItem *item : items)
    {
        item->Show();
    }

    cursor = preferredCursorItem;
    MenuItem *currentItem;
    currentItem = CurrentItem();
    if (!currentItem->Enabled())
    {
        MoveCursor();
    }
    currentItem->Select();
    UpdateHelpText();
    isOpen = true;
}

void MainMenu::Close()
{
    Menu::Close();
    back->Hide();
    helpVis->Hide();
    for (MenuItem *item : items)
        item->Hide();
    CurrentItem()->Deselect();
    isOpen = false;
}

MenuButton * MainMenu::AddButton(const std::string &text, const std::string &help, int y, std::function<void()> onActivate)
{
    MenuButton *newButton = new MenuButton(text, help, pos.y + y, onActivate);
    items.push_back(newButton);
    return newButton;
}

MenuButton * MainMenu::AddButton(const std::string &text, const std::string &help, int x, int y, std::function<void()> onActivate)
{
    MenuButton *newButton = new MenuButton(text, help, pos.x + x, pos.y + y, onActivate);
    items.push_back(newButton);
    return newButton;
}

MenuTextBox * MainMenu::AddTextBox(const std::string &title, const std::string &help, int y, int width, std::function<void()> onActivate)
{
    int borderOffset = 70;
    MenuTextBox *newTextBox = new MenuTextBox(title, help, pos.x + 640 - width - borderOffset, pos.y + y, width, pos.x + borderOffset, onActivate);
    items.push_back(newTextBox);
    return newTextBox;
}

MenuTextBox * MainMenu::AddTextBox(const std::string &title, const std::string &help, int x, int y, int width, int titleX, std::function<void()> onActivate)
{
    MenuTextBox *newTextBox = new MenuTextBox(title, help, pos.x + x, pos.y + y, width, pos.x + titleX, onActivate);
    items.push_back(newTextBox);
    return newTextBox;
}

MenuTextBox * MainMenu::AddTextBox(const std::string &title, const std::string &help, int x, int y, int width, int titleX, int titleY, std::function<void()> onActivate)
{
    MenuTextBox *newTextBox = new MenuTextBox(title, help, pos.x + x, pos.y + y, width, pos.x + titleX, pos.y + titleY, onActivate);
    items.push_back(newTextBox);
    return newTextBox;
}

void MainMenu::UpdateHelpText()
{
    if (GameTime::GetTicks() > helpTextNextUpdateTime)
    {
        HelpText()->SetColor(*zCOLOR_WHITE());
        HelpText()->SetText(CurrentItem()->helpText);
    }
}

void MainMenu::SetHelpText(const std::string &text)
{
    HelpText()->SetColor(*zCOLOR_RED());
    HelpText()->SetText(text);
    helpTextNextUpdateTime = GameTime::GetTicks() + 2 * 2 * TICKS_PER_SECOND;
}

void MainMenu::SetCursor(size_t i)
{
    if (0 <= i && i < items.size())
    {
        MenuItem *newItem = items[i];
        if (newItem->Enabled())
        {
            CurrentItem()->Deselect();
            cursor = i;
            newItem->Select();
            UpdateHelpText();
        }
    }
}

void MainMenu::SetCursor(MenuItem *item)
{
    for (size_t i = 0; i < items.size(); i++)
    {
        if (items[i] == item)
        {
            SetCursor(i);
            break;
        }
    }
}

void MainMenu::MoveCursor()
{
    MoveCursor(false);
}

void MainMenu::MoveCursor(bool up)
{
    CurrentItem()->Deselect();
    //Search in all items, for the next selectable item.
    for (size_t i = 0; i < items.size(); i++)
    {
        if (up)
        {
            cursor--;
            if (cursor >= items.size()) //unsigned underflow
                cursor = items.size() - 1;
        }
        else //down
        {
            cursor++;
            if (cursor >= items.size())
                cursor = 0;
        }

        MenuItem *selectedItem = CurrentItem();
        if (selectedItem->Enabled())
        {
            selectedItem->Select();
            UpdateHelpText();
            break; //Found enabled next item. Stop searching.
        }
    }
}

void MainMenu::KeyDown(OpenGMP::VirtualKeys key)
{
    unsigned long long now = GameTime::GetTicks();
    
    switch (key)
    {
    case VirtualKeys::Return:
    {
        MenuItem *item = CurrentItem();
        if (item->onAction)
            item->onAction();
        break;
    }
    case VirtualKeys::Escape:
    {
        if (onEscape)
            onEscape();
        this->Close();
        break;
    }
    default:
    {
        MenuItem *item = CurrentItem();
        InputReceiver *ir = dynamic_cast<InputReceiver*>(item);
        if (ir)
        {
            ir->KeyPressed(key);
        }
    }
    }
}

void MainMenu::Update(unsigned long long now)
{
    scrollHelper.Update(now);
    MenuItem *item = CurrentItem();
    MenuTextBox *tb = dynamic_cast<MenuTextBox*>(item);
    if (tb)
    {
        if (tb->Update)
        {
            tb->Update(now);
        }
    }
}

VisualText *MainMenu::HelpText()
{
    return helpVis->Texts().front();
}
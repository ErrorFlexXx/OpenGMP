#pragma once

#include "menu.hpp"
#include "visual.hpp"
#include <Client/Systems/inputSystem.hpp>
#include <vector>
#include <functional>

namespace OpenGMP
{
    class GameClient;

    namespace GUI
    {
        class VisualText;
        class MenuItem;
        class MenuButton;
        class MenuTextBox;

        class MainMenu : public Menu
        {
        public:
            MainMenu(GameClient &gameClient);
            MenuItem *CurrentItem();
            bool IsOpen();

            virtual void OnCreate();
            virtual void Open() override;
            virtual void Close() override;
            virtual void KeyDown(Types::VirtualKeys key) override;
            virtual void Update(unsigned long long now) override;

        protected:
            MenuButton * AddButton(const std::string &text, const std::string &help, int y, std::function<void()> onActivate);
            MenuButton * AddButton(const std::string &text, const std::string &help, int x, int y, std::function<void()> onActivate);
            MenuTextBox * AddTextBox(const std::string &title, const std::string &help, int y, int width, std::function<void()> onActivate, bool passwordText = false);
            MenuTextBox * AddTextBox(const std::string &title, const std::string &help, int x, int y, int width, int titleX, std::function<void()> onActivate, bool passwordText = false);
            MenuTextBox * AddTextBox(const std::string &title, const std::string &help, int x, int y, int width, int titleX, int titleY, std::function<void()> onActivate, bool passwordText = false);
            void UpdateHelpText();
            void SetHelpText(const std::string &text);
            void SetCursor(size_t i);
            void SetCursor(MenuItem *item);
            void MoveCursor();
            void MoveCursor(bool up);
            
            Visual *back;
            Visual *helpVis;
            Visual *versionVis;
            VisualText *HelpText();
            std::vector<MenuItem*> items;
            size_t cursor;
            struct Pos
            {
                int x = 0;
                int y = 0;
            } pos;
            int preferredCursorItem;
            std::function<void()> onEscape;
            bool isOpen;
            unsigned long long helpTextNextUpdateTime;

        private:
            OpenGMP::Systems::InputSystemKeyCombination scrollHelper;
            bool init;
        };
    }
}
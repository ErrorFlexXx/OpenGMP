#pragma once

#include "menu.hpp"
#include "visual.hpp"
#include "../Controls/keyHoldHelper.hpp"
#include <vector>
#include <functional>

namespace OpenGMP
{
    namespace GUI
    {
        class VisualText;
        class MenuItem;
        class MenuButton;
        class MenuTextBox;

        class MainMenu : public Menu
        {
        public:
            MainMenu();
            MenuItem *CurrentItem();
            bool IsOpen();

            virtual void OnCreate() = 0;
            virtual void Open() override;
            virtual void Close() override;

        protected:
            MenuButton * AddButton(const std::string &text, const std::string &help, int y, std::function<void()> onActivate);
            MenuButton * AddButton(const std::string &text, const std::string &help, int x, int y, std::function<void()> onActivate);
            MenuTextBox * AddTextBox(const std::string &title, const std::string &help, int y, int width, std::function<void()> onActivate);
            MenuTextBox * AddTextBox(const std::string &title, const std::string &help, int x, int y, int width, int titleX, std::function<void()> onActivate);
            MenuTextBox * AddTextBox(const std::string &title, const std::string &help, int x, int y, int width, int titleX, int titleY, std::function<void()> onActivate);
            void UpdateHelpText();
            void SetHelpText(const std::string &text);
            void SetCursor(size_t i);
            void SetCursor(MenuItem *item);
            void MoveCursor();
            void MoveCursor(bool up);
            virtual void KeyDown(VirtualKeys key) override;
            virtual void Update(unsigned long long now) override;

            Visual back;
            Visual *helpVis;
            VisualText *HelpText();
            std::vector<MenuItem*> items;
            size_t cursor;
            struct Pos
            {
                Pos(int x, int y)
                    : x(x)
                    , y(y) {}
                int x;
                int y;
            } pos;
            int preferredCursorItem;
            std::function<void()> onEscape;
            bool isOpen;
            unsigned long long helpTextNextUpdateTime;

        private:
            OpenGMP::Controls::KeyHoldHelper scrollHelper;
            bool init;
        };
    }
}
#pragma once

#include "menuItem.hpp"
#include "visual.hpp"
#include "textBox.hpp"
#include <string>
#include <functional>

namespace OpenGMP
{
    namespace GUI
    {
        class MenuTextBox : public MenuItem, public InputReceiver
        {
        public:
            MenuTextBox(const std::string &help, int x, int y, int width, std::function<void()> action);
            MenuTextBox(const std::string &title, const std::string &help, int x, int y, int width, int titleX, std::function<void()> action);
            MenuTextBox(const std::string &title, const std::string &help, int x, int y, int width, int height, int titleX, std::function<void()> action);
            MenuTextBox(const std::string &title, const std::string &help, int x, int y, int width, int height, int titleX, int titleY, std::function<void()> action);
            MenuTextBox(const std::string &backTexture, const std::string &title, const std::string &help, int x, int y, int width, int height, int titleX, int titleY, std::function<void()> action);

            virtual void Select() override;
            virtual void Deselect() override;
            virtual void Show() override;
            virtual void Hide() override;
            std::function<void(unsigned long long)> Update;
        
        private:
            virtual void KeyPressed(VirtualKeys key) override;

            static const int defaultHeight;
            static const std::string defaultBackTexture;
            std::string backTexture;
            Visual vis;
            Visual *titleVis;
            TextBox tb;
        };
    }
}
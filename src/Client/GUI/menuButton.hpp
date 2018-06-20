#pragma once

#include "menuItem.hpp"
#include "visualText.hpp"
#include "visual.hpp"
#include <string>
#include <functional>

namespace OpenGMP
{
    namespace GUI
    {
        class MenuButton : public MenuItem
        {
        public:
            MenuButton(const std::string &text, const std::string &help, int y, std::function<void()> action, Fonts font = Fonts::Menu);
            MenuButton(const std::string &text, const std::string &help, int x, int y, std::function<void()> action, Fonts font = Fonts::Menu);

            virtual void Show() override;
            virtual void Hide() override;
            virtual void Select() override;
            virtual void Deselect() override;
            virtual bool Enabled() override;
            virtual void Enabled(bool value) override;
            
            ViewPoint Position();
            void Text(const std::string &text);
            const std::string &Text();

        private:
            Visual *visual;
            VisualText *visualText;
        };
    }
}
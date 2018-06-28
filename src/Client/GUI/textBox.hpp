#pragma once

#include "view.hpp"
#include "visual.hpp"
#include <string>

namespace OpenGMP
{
    namespace GUI
    {
        class VisualText;

        class TextBox : public View
        {
        public:
            TextBox(int x, int y, int w, bool fixedBorders, bool passwordText = false);

            virtual void Show() override;
            virtual void Hide() override;

            VisualText *InputText();
            void Update(unsigned long long now);
            void KeyPressed(VirtualKeys key);
            bool Enabled();
            void Enabled(bool value);
            std::string Input();
            void Input(const std::string &value);
            bool GetPasswordText();
            void SetPasswordText(bool value);

            size_t characterLimit;
            bool allowSpaces;
            bool allowSymbols;
            bool onlyNumbers;
            size_t hideChars;
            
            bool leftArrowShown;
            bool rightArrowShown;
            bool enabled;

        private:
            void UpdateInputVisual();
            char GetCharFromKey(VirtualKeys key);

            struct Pos
            {
                int x;
                int y;
            } pos;
            int width;
            int height;
            bool fixedBorders;
            bool passwordText;
            Visual inputVis;
            int startPos;
            static const size_t cursorSize;
            static const int cursorOffsetX;
            static const size_t cursorOffsetY;
            static const size_t arrowSize;
            size_t cursorPos;
            Visual cursorVis;
            Visual leftArrow;
            Visual rightArrow;
            unsigned long long cursorTime;
            std::string input;
        };
    }
}
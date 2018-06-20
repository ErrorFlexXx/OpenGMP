#pragma once

#include "view.hpp"
#include "../Gothic/Types/zCOLOR.hpp"
#include <string>

class zCViewText;

namespace OpenGMP
{
    namespace GUI
    {
        enum TextFormat
        {
            Left,
            Center,
            Right
        };

        class VisualText : public View
        {
        public:
            VisualText(const std::string &text, int x, int y, class Visual *parent, bool virtuals);
            static Visual *Create(const std::string &text, int x, int y);
            static Visual *Create(const std::string &text, int x, int y, bool virtuals);
            virtual ~VisualText() {};

            virtual void Show() override;
            virtual void Hide() override;
            
            zCOLOR GetColor();
            void SetColor(const zCOLOR &color);
            void SetPosX(int val, bool virtuals = false);
            void SetPosY(int val, bool virtuals = false);
            bool GetCenteredX();
            void SetCenteredX(bool value);
            bool GetCenteredY();
            void SetCenteredY(bool value);
            ViewPoint GetPosition();
            View::Fonts GetFont();
            void SetFont(View::Fonts font);
            TextFormat GetFormat();
            void SetFormat(TextFormat value);
            const std::string & GetText();
            void SetText(const std::string &text);
            zCViewText *GetZViewText();

        protected:
            std::string text;
            View::Fonts font;
            TextFormat format;
            bool centeredX;
            bool centeredY;
            void AlignText();

        private:
            class Visual *parent;
            zCViewText *zViewText;
            ViewPoint position;
            bool shown;
        };
    }
}
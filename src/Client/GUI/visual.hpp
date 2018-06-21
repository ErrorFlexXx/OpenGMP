#pragma once

#include "view.hpp"
#include "../Gothic/Classes/zCView.hpp"
#include "../Gothic/Classes/zCFont.hpp"
#include <list>
#include <string>

namespace OpenGMP
{
    namespace GUI
    {
        class Visual : public View
        {
        public:
            Visual();
            Visual(int x, int y, int w, int h);
            Visual(int x, int y, int w, int h, bool virtuals);
            Visual(int x, int y, int w, int h, bool virtuals, Visual *p);
            virtual ~Visual();

            virtual void Show() override;
            virtual void Hide() override;
            class VisualText *CreateText(const std::string &text);
            class VisualText *CreateText(const std::string &text, int x, int y);
            class VisualText *CreateText(const std::string &text, int x, int y, bool virtuals);

            void SetBackTexture(const std::string &tex);
            void SetPosX(int newPosX, bool virtuals = false);
            void SetPosY(int newPosY, bool virtuals = false);
            void SetPos(int x, int y, bool virtuals = false);
            void SetPos(ViewPoint newPos, bool virtuals = false);
            void SetWidth(int width, bool virtuals = false);
            void SetHeight(int height, bool virtuals = false);
            void SetSize(int width, int height, bool virtuals = false);
            void SetSize(ViewPoint newSize, bool virtuals = false);
            View::Fonts GetFont();
            void SetFont(View::Fonts font);
            ViewPoint GetPosition();
            ViewPoint GetSize();
            View *GetParent();
            zCView *GetZView();
            bool Shown();
            const std::list<VisualText*> &Texts();
        
        protected:
            View::Fonts font;
            std::list<VisualText*> texts;
            zCView *zView;
            View *parent;
            std::list<View*> children;
            ViewPoint vpos;
            ViewPoint vsize;
            bool shown;
        };
    }
}
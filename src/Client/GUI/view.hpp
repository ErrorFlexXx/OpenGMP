#pragma once

#include <map>

namespace OpenGMP
{
    namespace GUI
    {
        struct ViewPoint
        {
            int x;
            int y;
        } typedef ViewPoint;

        class View
        {
        public:
            enum Fonts
            {
                Default,
                Default_Hi,
                Menu,
                Menu_Hi
            };

            virtual ~View() {}

            const int fontSizeDefault = 18;
            const int fontSizeMenu = 32;
            static const std::map<Fonts, std::string> fontDict;
            
            static ViewPoint GetScreenSize();
            static ViewPoint PixelToVirtual(int x, int y);
            static ViewPoint PixelToVirtual(ViewPoint point);
            static int PixelToVirtualX(int x);
            static int PixelToVirtualY(int y);

            virtual void Show() = 0;
            virtual void Hide() = 0;
        };
    }
}
#pragma once

#include <map>
#include <vector>
#include <string>
#include "../Types/virtualKeys.hpp"

namespace OpenGMP
{
    namespace GUI
    {
        struct ViewPoint
        {
            int x;
            int y;
        } typedef ViewPoint;

        class InputReceiver
        {
        public:
            virtual void KeyPressed(Types::VirutalKeys key) = 0;
        };

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
            static const std::map<char, double> allChars;
            static const std::map<char, float> gothicChars;
            static std::vector<double> charWidths;
            
            static ViewPoint GetVirtualScreenSize();
            static ViewPoint GetPixelScreenSize();
            static ViewPoint PixelToVirtual(int x, int y);
            static ViewPoint PixelToVirtual(ViewPoint point);
            static int PixelToVirtualX(int x);
            static int PixelToVirtualY(int y);
            static inline double OGMPGetCharWidth(char c) { return (size_t)(unsigned char)c < charWidths.size() ? charWidths[(unsigned char)c] : 0.0; }
            static bool GothicContainsChar(char c);
            static double StringPixelWidth(const std::string &str);

            virtual void Show() = 0;
            virtual void Hide() = 0;

        private:
            static std::vector<double> InitCharWidths(); //Fast lookup array (prevent slow index based map access, which may occur often..)
        };
    }
}
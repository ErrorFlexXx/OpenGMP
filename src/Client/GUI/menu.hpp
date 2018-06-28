#pragma once

#include "../Controls/inputHandler.hpp"
#include <list>

namespace OpenGMP
{
    namespace GUI
    {
        class Menu
        {
        public:
            Menu();

            bool Opened();
            virtual void Open();
            virtual void Close();
            virtual void KeyDown(VirtualKeys key);
            virtual void KeyUp(VirtualKeys key);
            virtual void Update(unsigned long long now);

            static std::list<Menu*> activeMenus;

        private:
            bool opened;
        };
    }
}
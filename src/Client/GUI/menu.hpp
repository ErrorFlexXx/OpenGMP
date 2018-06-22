#pragma once

#include "../Core/inputHandler.hpp"
#include <list>

namespace OpenGMP
{
    namespace GUI
    {
        class Menu
        {
        public:
            Menu();

            static bool IsMenuActive();
            static bool KeyDownUpdateMenus(VirtualKeys key);
            static bool KeyUpUpdateMenus(VirtualKeys key);
            static void UpdateMenus(unsigned long long now);
            static void CloseActiveMenus();
            bool Opened();
            virtual void Open();
            virtual void Close();
            
        protected:
            virtual void KeyDown(VirtualKeys key);
            virtual void KeyUp(VirtualKeys key);
            virtual void Update(unsigned long long now);

        private:
            static std::list<Menu*> activeMenus;
            bool opened;
        };
    }
}
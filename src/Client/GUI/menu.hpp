#pragma once

#include "../Systems/inputSystem.hpp"
#include <list>

namespace OpenGMP
{
    class GameClient;

    namespace GUI
    {
        class Menu
        {
        public:
            Menu(GameClient &gameClient);

            bool Opened();
            virtual void Open();
            virtual void Close();
            virtual void KeyDown(VirtualKeys key);
            virtual void KeyUp(VirtualKeys key);
            virtual void Update(unsigned long long now);
            void CloseActiveMenus();

            static std::list<Menu*> activeMenus;

        protected:
            GameClient &gameClient;
        
        private:
            bool opened;
        };
    }
}
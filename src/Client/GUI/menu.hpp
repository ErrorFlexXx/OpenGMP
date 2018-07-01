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
            virtual void KeyDown(Types::VirtualKeys key);
            virtual void KeyUp(Types::VirtualKeys key);
            virtual void Update(unsigned long long now);

            static std::list<Menu*> activeMenus;

        protected:
            GameClient &gameClient;
        
        private:
            bool opened;
        };
    }
}
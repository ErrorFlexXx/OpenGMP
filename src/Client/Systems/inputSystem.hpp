#pragma once

#include "../Types/virtualKeys.hpp"
#define _WINSOCKAPI_ //Stop windows.h from including winsock.h (colliding with RakNet)
#include <windows.h>
#include <functional>
#include <map>

#define KEYCOUNT 255

namespace OpenGMP
{
    class GameClient;

    namespace Systems
    {
        class InputSystem
        {
        public:
            InputSystem(GameClient &gameClient);
            void Update();
            std::function<void(Types::VirtualKeys key)> keyDownReceipient;
            std::function<void(Types::VirtualKeys key)> keyUpReceipient;
            bool mouseShown;
            int movedX;
            int movedY;
            int MouseDistX();
            int MouseDistY();
            POINT oriPos;
            const int defaultMousePosX;
            const int defaultMousePosY;
            bool m_shown;
            bool IsPressed(Types::VirtualKeys key);

        private:
            GameClient &gameClient;
            bool m_keys[KEYCOUNT];
        };
    }
}

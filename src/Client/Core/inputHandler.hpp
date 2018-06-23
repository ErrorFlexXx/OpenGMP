#pragma once

#define _WINSOCKAPI_ //Stop windows.h from including winsock.h (colliding with RakNet)
#include <windows.h>
#include <functional>
#include <map>
#include "Enumeration/VirtualKeys.hpp"

namespace OpenGMP
{
    class InputHandler
    {
    public:
        static void Update();
        static std::function<void(VirtualKeys key)> keyDownReceipient;
        static std::function<void(VirtualKeys key)> keyUpReceipient;
        static bool MouseShown;
        static int movedX;
        static int movedY;
        static int MouseDistX();
        static int MouseDistY();
        static POINT oriPos;
        static const int DefaultMousePosX;
        static const int DefaultMousePosY;
        static bool m_shown;
        static bool IsPressed(VirtualKeys key);

    private:
        InputHandler(); //Abstract class
        static bool m_keys[];
    };
}

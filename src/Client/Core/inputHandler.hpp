#pragma once

#define _WINSOCKAPI_ //Stop windows.h from including winsock.h (colliding with RakNet)
#include <windows.h>
#include <map>
#include "Enumeration/VirtualKeys.hpp"

typedef void (*KeyEventHandler)(VirtualKeys::VirtualKeys key);
typedef void (*GlobalEventCallback)();

class InputHandler
{
public:
	static void Update();
    static KeyEventHandler OnKeyDown;   //KeyDown Callback
    static KeyEventHandler OnKeyUp;     //KeyUp Callback
	static bool MouseShown;
	static int movedX;
	static int movedY;
	static int MouseDistX();
	static int MouseDistY();
	static POINT oriPos;
	static const int DefaultMousePosX;
	static const int DefaultMousePosY;
	static bool m_shown;
    static bool IsPressed(VirtualKeys::VirtualKeys key);
	static std::map<unsigned short, GlobalEventCallback> m_globalEvents;

private:
    InputHandler(); //Abstract class
    static bool m_keys[];
};

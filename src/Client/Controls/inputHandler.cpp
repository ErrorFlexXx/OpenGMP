#include "inputHandler.hpp"
#include <Shared/Components/GameTime.hpp>
#include "../process.hpp"

#define KEYCOUNT 255

using namespace OpenGMP;

std::function<void(VirtualKeys key)> InputHandler::keyDownReceipient;
std::function<void(VirtualKeys key)> InputHandler::keyUpReceipient;
bool InputHandler::MouseShown = false;
int InputHandler::movedX = 0;
int InputHandler::movedY = 0;
POINT InputHandler::oriPos;
const int InputHandler::DefaultMousePosX = 320;
const int InputHandler::DefaultMousePosY = 240;
bool InputHandler::m_keys[KEYCOUNT];
bool InputHandler::m_shown = false;

int InputHandler::MouseDistX()
{
	return movedX;
}

int InputHandler::MouseDistY()
{
	return movedY;
}

void InputHandler::Update()
{
    unsigned long long ticks = GameTime::GetTicks();
	if(Process::IsForeground())
	{
		if(!m_shown)
		{
			m_shown = true;
			while(0 <= ShowCursor(false));
			GetCursorPos(&oriPos);
			SetCursorPos(DefaultMousePosX, DefaultMousePosY);
			movedX = 0;
			movedY = 0;
		}
		else
		{
			POINT pos;
			if(GetCursorPos(&pos))
			{
				movedX = pos.x - DefaultMousePosX;
				movedY = pos.y - DefaultMousePosY;
				SetCursorPos(DefaultMousePosX, DefaultMousePosY);
			}
		}
		for(int i = 1; i < KEYCOUNT; i++)
		{
			short keystate = GetAsyncKeyState(i);

			if((keystate & 0x8001) == 0x8001 ||
			   (keystate & 0x8000) == 0x8000) //Key is pressed
			{
				if(!m_keys[i]) //Was not pressed, so set it pressed
				{
					m_keys[i] = true;
					
					if(keyDownReceipient)
                    {
                        keyDownReceipient((VirtualKeys) i);
                    }
				}
			}
			else //Key is not pressed
			{
				if(m_keys[i]) //Release key
				{
					m_keys[i] = false;
					if(keyUpReceipient != NULL)
                        keyUpReceipient((VirtualKeys) i);
				}
			}
		}
	}
	else
	{
		if(m_shown)
		{
			m_shown = false;
			while(ShowCursor(true) < 0);
			SetCursorPos(oriPos.x, oriPos.y);
			movedX = 0;
			movedY = 0;
		}
	}
}

bool InputHandler::IsPressed(VirtualKeys key)
{
    return m_keys[(int)key];
}

#include "inputSystem.hpp"
#include <Shared/Components/GameTime.hpp>
#include "../Systems/windowSystem.hpp"

using namespace OpenGMP;
using namespace OpenGMP::Components;
using namespace OpenGMP::Systems;
using namespace OpenGMP::Types;

InputSystem::InputSystem(GameClient &gameClient)
    : gameClient(gameClient)
    , defaultMousePosX(320)
    , defaultMousePosY(240)
    , mouseShown(false)
    , movedX(false)
    , movedY(false)
    , m_keys()
    , m_shown(false)
{
    oriPos.x = 320;
    oriPos.y = 240;
}

int InputSystem::MouseDistX()
{
	return movedX;
}

int InputSystem::MouseDistY()
{
	return movedY;
}

void InputSystem::Update()
{
    unsigned long long ticks = GameTime::GetTicks();
	if(WindowSystem::IsForeground())
	{
		if(!m_shown)
		{
			m_shown = true;
			while(0 <= ShowCursor(false));
			GetCursorPos(&oriPos);
			SetCursorPos(defaultMousePosX, defaultMousePosY);
			movedX = 0;
			movedY = 0;
		}
		else
		{
			POINT pos;
			if(GetCursorPos(&pos))
			{
				movedX = pos.x - defaultMousePosX;
				movedY = pos.y - defaultMousePosY;
				SetCursorPos(defaultMousePosX, defaultMousePosY);
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

bool InputSystem::IsPressed(VirtualKeys key)
{
    return m_keys[(int)key];
}

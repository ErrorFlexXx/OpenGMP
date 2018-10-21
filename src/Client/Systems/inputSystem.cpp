#include "inputSystem.hpp"
#include <Shared/Components/GameTime.hpp>
#include <Client/gameClient.hpp>
#include <Client/Systems/windowSystem.hpp>

using namespace OpenGMP;
using namespace OpenGMP::Components;
using namespace OpenGMP::Systems;
using namespace OpenGMP::Types;

/* InputSystem Key Down Repeater*/

InputSystemKeyDownRepeat::InputSystemKeyDownRepeat(GameClient &gameClient, std::function<void(VirtualKeys)> action, int holdTime, int rate)
    : gameClient(gameClient)
{
    this->action = action;
    this->holdTime = holdTime;
    this->rate = rate;
    this->nextTime = ULLONG_MAX; //Do not repeat a never pressed key.
}

void InputSystemKeyDownRepeat::Update(unsigned long long now)
{
    //Repeat time reached and not after long focus lost ?
    if (now > nextTime && now < nextTime + 3 * rate)
    {
        nextTime = now + rate * TICKS_PER_MILLISECOND;
        if (gameClient.inputSystem.IsPressed(currentKey) && action)
            action(currentKey);
    }
}

void InputSystemKeyDownRepeat::KeyDown(const VirtualKeys &key, unsigned long long now)
{
    currentKey = key;
    nextTime = now + holdTime * TICKS_PER_MILLISECOND;
}

/* InputSystem - Key Combinations */

InputSystemKeyCombination::InputSystemKeyCombination(GameClient &gameClient, int holdTime, int rate)
    : gameClient(gameClient)
    , holdTime(holdTime)
    , rate(rate)
    , current(nullptr)
{}

void InputSystemKeyCombination::Add(const std::list<VirtualKeys> &keyCombination, const std::function<void()> &action)
{
    if (0 < keyCombination.size())
    {
        actionKeyCombinationBindings.push_back(new ActionKeyCombinationBinding(keyCombination, action));
    }
}

void InputSystemKeyCombination::Update(unsigned long long now)
{
    for (auto it : actionKeyCombinationBindings)
    {
        ActionKeyCombinationBinding *pair = it;
        bool allCombinationKeysPressed = true;
        for (const VirtualKeys &key : pair->keyCombination)
        {
            if (!gameClient.inputSystem.IsPressed(key))
            {
                allCombinationKeysPressed = false;
                break;
            }
        }
        if (allCombinationKeysPressed)
        {
            if (pair != current)
            {
                current = pair;
                nextTime = now + holdTime * TICKS_PER_MILLISECOND;
                if (pair->action)
                    pair->action();
            }
            else if (now > nextTime)
            {
                nextTime = now + rate * TICKS_PER_MILLISECOND;
                if (pair->action)
                    pair->action();
            }
            return;
        }
    }
    current = nullptr;
}

/* InputSystem */

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

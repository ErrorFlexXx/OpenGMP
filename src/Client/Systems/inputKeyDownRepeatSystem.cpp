#include "inputKeyDownRepeatSystem.hpp"
#include "inputSystem.hpp"
#include "../gameClient.hpp"
#include <Shared/Components/gameTime.hpp>
#include <limits.h>

using namespace OpenGMP;
using namespace OpenGMP::Types;
using namespace OpenGMP::Systems;

InputKeyDownRepeatSystem::InputKeyDownRepeatSystem(GameClient &gameClient, std::function<void(VirtualKeys)> action, int holdTime, int rate)
    : gameClient(gameClient)
{
    this->action = action;
    this->holdTime = holdTime;
    this->rate = rate;
    this->nextTime = ULLONG_MAX; //Do not repeat a never pressed key.
}

void InputKeyDownRepeatSystem::Update(unsigned long long now)
{
    //Repeat time reached and not after long focus lost ?
    if (now > nextTime && now < nextTime + 3 * rate)
    {
        nextTime = now + rate * TICKS_PER_MILLISECOND;
        if (gameClient.inputSystem.IsPressed(currentKey) && action)
            action(currentKey);
    }
}

void InputKeyDownRepeatSystem::KeyDown(const VirtualKeys &key, unsigned long long now)
{
    currentKey = key;
    nextTime = now + holdTime * TICKS_PER_MILLISECOND;
}
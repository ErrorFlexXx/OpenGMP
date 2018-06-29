#include "keyDownRepeatHelper.hpp"
#include "inputHandler.hpp"
#include <Shared/Components/gameTime.hpp>
#include <limits.h>

using namespace OpenGMP;
using namespace OpenGMP::Controls;

KeyDownRepeatHelper::KeyDownRepeatHelper(std::function<void(VirtualKeys)> action, int holdTime, int rate)
{
    this->action = action;
    this->holdTime = holdTime;
    this->rate = rate;
    this->nextTime = ULLONG_MAX; //Do not repeat a never pressed key.
}

void KeyDownRepeatHelper::Update(unsigned long long now)
{
    //Repeat time reached and not after long focus lost ?
    if (now > nextTime && now < nextTime + 3 * rate)
    {
        nextTime = now + rate * TICKS_PER_MILLISECOND;
        if (InputHandler::IsPressed(currentKey) && action)
            action(currentKey);
    }
}

void KeyDownRepeatHelper::KeyDown(const VirtualKeys &key, unsigned long long now)
{
    currentKey = key;
    nextTime = now + holdTime * TICKS_PER_MILLISECOND;
}
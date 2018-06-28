#include "keyHoldHelper.hpp"
#include "../Controls/inputHandler.hpp"
#include <Shared/Components/gameTime.hpp>

using namespace OpenGMP;
using namespace OpenGMP::Controls;

KeyHoldHelper::KeyHoldHelper(int holdTime, int rate)
    : holdTime(holdTime)
    , rate(rate)
    , current(nullptr)
{}

void KeyHoldHelper::Add(const std::list<VirtualKeys> &keyCombination, const std::function<void()> &action)
{
    if (0 < keyCombination.size())
    {
        actionKeyCombinationBindings.push_back(new ActionKeyCombinationBinding(keyCombination, action));
    }
}

void KeyHoldHelper::Update(unsigned long long now)
{
    for (auto it : actionKeyCombinationBindings)
    {
        ActionKeyCombinationBinding *pair = it;
        bool allCombinationKeysPressed = true;
        for (const VirtualKeys &key : pair->keyCombination)
        {
            if (!InputHandler::IsPressed(key))
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
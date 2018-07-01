#include "inputKeyCombSystem.hpp"
#include "inputSystem.hpp"
#include "../gameClient.hpp"
#include <Shared/Components/gameTime.hpp>

using namespace OpenGMP;
using namespace OpenGMP::Types;
using namespace OpenGMP::Systems;

InputKeyCombSystem::InputKeyCombSystem(GameClient &gameClient, int holdTime, int rate)
    : gameClient(gameClient)
    , holdTime(holdTime)
    , rate(rate)
    , current(nullptr)
{}

void InputKeyCombSystem::Add(const std::list<VirtualKeys> &keyCombination, const std::function<void()> &action)
{
    if (0 < keyCombination.size())
    {
        actionKeyCombinationBindings.push_back(new ActionKeyCombinationBinding(keyCombination, action));
    }
}

void InputKeyCombSystem::Update(unsigned long long now)
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
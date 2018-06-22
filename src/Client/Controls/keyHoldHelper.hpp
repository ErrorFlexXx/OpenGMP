#pragma once

#include "../Core/Enumeration/virtualKeys.hpp"
#include <list>
#include <functional>

namespace OpenGMP
{
    namespace Controls
    {
        struct ActionKeyCombinationBinding
        {
            ActionKeyCombinationBinding(
                const std::list<VirtualKeys> &keyCombination,
                const std::function<void()> &action)
                : keyCombination(keyCombination)
                , action(action) {}

            std::list<VirtualKeys> keyCombination;
            std::function<void()> action;
        };

        class KeyHoldHelper
        {
        public:
            KeyHoldHelper(int holdTime = 600, int rate = 150);

            int holdTime;
            int rate;
            void Add(const std::list<VirtualKeys> &keyCombination, const std::function<void()> &action);
            void Update(unsigned long long now);

        private:
            std::list <ActionKeyCombinationBinding*> actionKeyCombinationBindings;
            unsigned long long nextTime;
            ActionKeyCombinationBinding *current;
        };
    }
}
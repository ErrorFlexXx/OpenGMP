#pragma once

#include "../Types/virtualKeys.hpp"
#include <list>
#include <functional>

namespace OpenGMP
{
    class GameClient;

    namespace Systems
    {
        struct ActionKeyCombinationBinding
        {
            ActionKeyCombinationBinding(
                const std::list<Types::VirtualKeys> &keyCombination,
                const std::function<void()> &action)
                : keyCombination(keyCombination)
                , action(action) {}

            std::list<Types::VirtualKeys> keyCombination;
            std::function<void()> action;
        };

        class InputKeyCombSystem
        {
        public:
            InputKeyCombSystem(GameClient &gameClient, int holdTime = 600, int rate = 150);

            int holdTime;
            int rate;
            void Add(const std::list<Types::VirtualKeys> &keyCombination, const std::function<void()> &action);
            void Update(unsigned long long now);

        private:
            GameClient &gameClient;
            std::list <ActionKeyCombinationBinding*> actionKeyCombinationBindings;
            unsigned long long nextTime;
            ActionKeyCombinationBinding *current;
        };
    }
}
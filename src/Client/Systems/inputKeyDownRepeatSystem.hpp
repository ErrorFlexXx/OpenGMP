#pragma once

#include "../Types/virtualKeys.hpp"
#include <functional>

namespace OpenGMP
{
    class GameClient;

    namespace Systems
    {
        class InputKeyDownRepeatSystem
        {
            public:
                InputKeyDownRepeatSystem(GameClient &gameClient, std::function<void(Types::VirtualKeys)> action, int holdTime = 600, int rate = 75);

                int holdTime;
                int rate;
                void Update(unsigned long long now);
                void KeyDown(const Types::VirtualKeys &key, unsigned long long now);

            private:
                GameClient &gameClient;
                unsigned long long nextTime;
                Types::VirtualKeys currentKey;
                std::function<void(Types::VirtualKeys)> action;
        };
    }
}
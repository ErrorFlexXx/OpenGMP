#pragma once

#include "virtualKeys.hpp"
#include <functional>

namespace OpenGMP
{
    namespace Controls
    {
        class KeyDownRepeatHelper
        {
            
            public:
                KeyDownRepeatHelper(std::function<void(VirtualKeys)> action, int holdTime = 600, int rate = 75);

                int holdTime;
                int rate;
                void Update(unsigned long long now);
                void KeyDown(const VirtualKeys &key, unsigned long long now);

            private:
                unsigned long long nextTime;
                VirtualKeys currentKey;
                std::function<void(VirtualKeys)> action;
        };
    }
}
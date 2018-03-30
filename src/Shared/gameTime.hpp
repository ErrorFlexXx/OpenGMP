#pragma once

#include <GetTime.h>

#define TICKS_PER_SECOND        1000
#define TICKS_PER_MILLISECOND   1

class GameTime
{
public:
    /**
     * @brief Update updates the current ticks pronounced with GetTicks.
     */
    static void Update();

    /**
     * @brief GetTicks returns the current tick value.
     * @return current ticks in unsigned long long.
     */
    static unsigned long long GetTicks();
private:
    static unsigned long long ticks;    //!< Current ticks.
    static RakNet::TimeMS oldTicks;     //!< old ticks to impl. a 32-bit overflowing prevention.
};

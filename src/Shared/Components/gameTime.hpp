#pragma once

#include <GetTime.h>
#include "../Objects/iStreamObject.hpp"

#define TICKS_PER_SECOND        1000
#define TICKS_PER_MILLISECOND   1

class GameTime : public IStreamObject
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

    virtual void WriteStream(RakNet::BitStream &stream) override;
    virtual void ReadStream(RakNet::BitStream &stream) override;

    static unsigned long long ticks;    //!< Current ticks.

private:
    static RakNet::TimeMS oldTicks;     //!< old ticks to impl. a 32-bit overflowing prevention. <- ToDo: Move to system.
};
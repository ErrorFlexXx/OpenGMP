#include "gameTime.hpp"
#include <limits.h>

using namespace RakNet;
using namespace OpenGMP;

unsigned long long GameTime::ticks = GetTimeMS();
TimeMS GameTime::oldTicks = GetTimeMS();

/**
 * @brief GameTime::update
 *        Updates an unsigned long long counter with an unsigned long
 *        maybe overflowing Tick counter to get a final 64 bit counter.
 */
void GameTime::Update()
{
    TimeMS newTicks = RakNet::GetTimeMS();

    if(newTicks < oldTicks) //Overflow occured ?
    {
        TimeMS temp = ULONG_MAX - oldTicks; //ULONG is DWORD
        temp += newTicks;
        GameTime::ticks += temp;
    }
    else
    {
        GameTime::ticks += newTicks - oldTicks;
    }
    GameTime::oldTicks = newTicks;
}

unsigned long long GameTime::GetTicks()
{
    return GameTime::ticks;
}

void GameTime::WriteStream(RakNet::BitStream &stream) const
{
    stream.Write(ticks);
}

bool GameTime::ReadStream(RakNet::BitStream &stream)
{
    bool success;

    success = stream.Read(ticks);

    return success;
}

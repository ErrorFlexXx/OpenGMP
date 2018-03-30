#include "skyController.hpp"
#include <BitStream.h>
#include <Shared/Types/worldTime.hpp>
#include <Shared/WorldObjects/world.hpp>
#include <Shared/WorldObjects/WorldGlobals/worldClock.hpp>
#include <Shared/gameTime.hpp>

SkyController::SkyController(World *world)
    : m_world(world)
{
}

void SkyController::SetNextWeight(WorldTime time, float weight)
{
    m_startTime = m_world->GetWorldClock().GetTime();
    m_startWeight = m_currentWeight;

    m_endTime = time;
    if(weight < 0)
        m_endWeight = 0;
    else if(weight > 1)
        m_endWeight = 1;
    else
        m_endWeight = weight;
}

void SkyController::UpdateWeight()
{
    if(m_endTime != m_startTime)
    {
        float percent;
        unsigned long long currentTicks = m_world->GetWorldClock().GetPreciseTicks();
        unsigned long long startTicks = m_startTime.GetTotalSeconds() * TICKS_PER_SECOND;
        unsigned long long endTicks = m_endTime.GetTotalSeconds() * TICKS_PER_SECOND;

        if(currentTicks > endTicks)
            percent = 1;
        else if (currentTicks < startTicks)
            percent = 0;
        else
            percent = (float)((double)(currentTicks - startTicks) / (endTicks - startTicks));
        m_currentWeight = m_startWeight + (m_endWeight - m_startWeight) * percent;
    }
    else
        m_currentWeight = m_endWeight;
}

void SkyController::ReadStream(RakNet::BitStream &readStream)
{
    int endTimeTicks;

    readStream.Read(endTimeTicks);
    readStream.Read(m_endWeight);

    m_endTime = WorldTime(endTimeTicks);
}

void SkyController::WriteStream(RakNet::BitStream &writeStream)
{
    writeStream.Write(m_endTime.GetTotalSeconds());
    writeStream.Write(m_endWeight);
}

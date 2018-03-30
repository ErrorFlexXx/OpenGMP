#include "worldClock.hpp"
#include <Shared/gameTime.hpp>

WorldClock::WorldClock()
    : m_isRunning(false)
    , m_rate(1.f)
{
}

void WorldClock::SetTime(WorldTime time)
{
    SetTime(time, m_rate);
}

void WorldClock::SetTime(WorldTime time, float rate)
{
    m_time = time;
    m_rate = rate;

    if(m_isRunning)
        SetStartTicks();
}

void WorldClock::SetStartTicks()
{
    unsigned long long departedTicks = (unsigned long long)((TICKS_PER_SECOND * m_time.GetTotalSeconds()) / (double) m_rate);
    m_startTicks = GameTime::GetTicks() - departedTicks;
}

void WorldClock::Start()
{
    if(!m_isRunning)
    {
        m_isRunning = true;
        SetStartTicks();
    }
}

void WorldClock::Stop()
{
    if(m_isRunning)
    {
        m_isRunning = false;
    }
}

bool WorldClock::GetRunning()
{
    return m_isRunning;
}

void WorldClock::UpdateTime()
{
    if(m_isRunning)
    {
        WorldTime newTime((int)(GetPreciseTicks() / TICKS_PER_SECOND));
        m_time = newTime;
    }
}

WorldTime WorldClock::GetTime() const
{
    return m_time;
}

unsigned long long WorldClock::GetPreciseTicks()
{
    return (unsigned long long)(m_rate * (GameTime::GetTicks() - m_startTicks));
}

void WorldClock::ReadStream(RakNet::BitStream &readStream)
{
    int totalSeconds;
    float rate;

    readStream.Read(totalSeconds);
    readStream.Read(rate);
    WorldTime newTime(totalSeconds);
    m_time = newTime;
    m_rate = rate;
}

void WorldClock::WriteStream(RakNet::BitStream &writeStream)
{
    writeStream.Write(m_time.GetTotalSeconds());
    writeStream.Write(m_rate);
}

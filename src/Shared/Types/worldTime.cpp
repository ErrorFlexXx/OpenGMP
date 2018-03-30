#include "worldTime.hpp"
#include <limits.h>
#include <stdexcept>

WorldTime::WorldTime()
    : WorldTime(0)
{
}

WorldTime::WorldTime(int totalSeconds)
{
    m_totalSeconds = totalSeconds;
}

WorldTime::WorldTime(int day, int hour)
    : WorldTime(day, hour, 0, 0)
{
}

WorldTime::WorldTime(int day, int hour, int minute)
    : WorldTime(day, hour, minute, 0)
{
}

WorldTime::WorldTime(int day, int hour, int minute, int second)
{
    long long totalSeconds = (long long) second +
                             (long long) minute * SECONDS_PER_MINUTE +
                             (long long) hour * SECONDS_PER_HOUR +
                             (long long) day * SECONDS_PER_DAY;
    if(INT_MIN <= totalSeconds && totalSeconds <= INT_MAX)
    {   //Valid
        m_totalSeconds = (int) totalSeconds;
    }
    else //Overflow
    {
        throw std::overflow_error("WorldTime given time caused overflow!");
    }
}

float WorldTime::GetTotalDays()
{
    return m_totalSeconds / (float) SECONDS_PER_DAY;
}

float WorldTime::GetTotalHours()
{
    return m_totalSeconds / (float) SECONDS_PER_HOUR;
}

float WorldTime::GetTotalMinutes()
{
    return m_totalSeconds / (float) SECONDS_PER_MINUTE;
}

int WorldTime::GetTotalSeconds()
{
   return m_totalSeconds;
}

int WorldTime::GetDay()
{
    return m_totalSeconds / SECONDS_PER_DAY;
}

int WorldTime::GetHour()
{
    return m_totalSeconds % SECONDS_PER_DAY / SECONDS_PER_HOUR;
}

int WorldTime::GetMinute()
{
    return m_totalSeconds % SECONDS_PER_DAY % SECONDS_PER_HOUR / SECONDS_PER_MINUTE;
}

int WorldTime::GetSecond()
{
    return m_totalSeconds % SECONDS_PER_DAY % SECONDS_PER_HOUR % SECONDS_PER_MINUTE;
}

/* Operators */

WorldTime& WorldTime::operator -(const WorldTime& rhs)
{
    return *(new WorldTime(m_totalSeconds - rhs.m_totalSeconds));
}

WorldTime& WorldTime::operator -(const int rhs)
{
    return *(new WorldTime(m_totalSeconds - rhs));
}

WorldTime& WorldTime::operator +(const WorldTime& rhs)
{
    return *(new WorldTime(m_totalSeconds + rhs.m_totalSeconds));
}

WorldTime& WorldTime::operator +(const int rhs)
{
    return *(new WorldTime(m_totalSeconds + rhs));
}

WorldTime& WorldTime::operator ++()
{
    m_totalSeconds++;
    return *(this);
}

WorldTime& WorldTime::operator --()
{
    m_totalSeconds--;
    return *(this);
}

WorldTime& WorldTime::operator *(const float rhs)
{
    return *(new WorldTime(m_totalSeconds * rhs));
}

WorldTime& WorldTime::operator *(const int rhs)
{
    return *(new WorldTime(m_totalSeconds * rhs));
}

WorldTime& WorldTime::operator /(const float rhs)
{
    return *(new WorldTime(m_totalSeconds / rhs));
}

WorldTime& WorldTime::operator /(const int rhs)
{
    return *(new WorldTime(m_totalSeconds / rhs));
}

bool WorldTime::operator <(const WorldTime& rhs)
{
    return m_totalSeconds < rhs.m_totalSeconds;
}

bool WorldTime::operator <=(const WorldTime& rhs)
{
    return m_totalSeconds <= rhs.m_totalSeconds;
}

bool WorldTime::operator >(const WorldTime& rhs)
{
    return m_totalSeconds > rhs.m_totalSeconds;
}

bool WorldTime::operator >=(const WorldTime& rhs)
{
    return m_totalSeconds >= rhs.m_totalSeconds;
}

bool WorldTime::operator ==(const WorldTime& rhs)
{
    return m_totalSeconds == rhs.m_totalSeconds;
}

bool WorldTime::operator !=(const WorldTime& rhs)
{
    return m_totalSeconds != rhs.m_totalSeconds;
}

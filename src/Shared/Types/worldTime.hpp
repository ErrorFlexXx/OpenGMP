#pragma once

#define SECONDS_PER_DAY     86400
#define SECONDS_PER_HOUR    3600
#define SECONDS_PER_MINUTE  60

class WorldTime
{
public:
    WorldTime();
    WorldTime(int totalSeconds);
    WorldTime(int day, int hour);
    WorldTime(int day, int hour, int minute);
    WorldTime(int day, int hour, int minute, int second);

    float GetTotalDays();
    float GetTotalHours();
    float GetTotalMinutes();
    int GetTotalSeconds();
    int GetDay();
    int GetHour();
    int GetMinute();
    int GetSecond();

    /* Operators */
    WorldTime operator- (const WorldTime& rhs);
    WorldTime operator- (const int rhs);
    WorldTime operator+ (const WorldTime& rhs);
    WorldTime operator+ (const int rhs);
    WorldTime &operator++ ();
    WorldTime &operator-- ();
    WorldTime operator* (const float rhs);
    WorldTime operator* (const int rhs);
    WorldTime operator/ (const float rhs);
    WorldTime operator/ (const int rhs);
    bool operator< (const WorldTime& rhs);
    bool operator<= (const WorldTime& rhs);
    bool operator> (const WorldTime& rhs);
    bool operator>= (const WorldTime& rhs);
    bool operator== (const WorldTime& rhs);
    bool operator!= (const WorldTime& rhs);

private:
    int m_totalSeconds;
};

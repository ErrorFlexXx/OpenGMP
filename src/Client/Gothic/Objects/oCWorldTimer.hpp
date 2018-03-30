#pragma once

#include "../xcall.h"
#include "../Types/zSTRING.hpp"

class oCWorldTimer
{
public:
    void Timer()
    {
        XCALL(0x00780D80);
    }
        
    int GetDay()
    {
        XCALL(0x00780DD0);
    }
        
    void SetDay(int day)
    {
        XCALL(0x00780DE0);
    }
        
    void GetTime(int &, int &)
    {
        XCALL(0x00780DF0);
    }
        
    void SetTime(int hour, int minute)
    {
        XCALL(0x00780E40);
    }
        
    float GetFullTime()
    {
        XCALL(0x00780E80);
    }
        
    void SetFullTime(float fulltime)
    {
        XCALL(0x00780E90);
    }

    zSTRING GetTimeString()
    {
        XCALL(0x00780EC0);
    }
        
    int IsLater(int hour, int minute)
    {
        XCALL(0x00781110);
    }
        
    int IsLaterEqual(int hour, int minute)
    {
        XCALL(0x00781150);
    }
    
    int IsTimeBetween(int hourFrom, int minuteFrom, int hourTo, int minuteTo)
    {
        XCALL(0x00781190);
    }
        
    int GetPassedTime(float)
    {
        XCALL(0x00781220);
    }
    
    float GetSkyTime()
    {
        XCALL(0x00781240);
    }
    
    int IsDay()
    {
        XCALL(0x00781280);
    }

    int IsNight()
    {
        XCALL(0x00781300);
    }
    
    static void __cdecl AddTime(int &destHours, int &destMinutes, int addHours, int addMinutes)
    {
        XCALL(0x00781390);
    }
};
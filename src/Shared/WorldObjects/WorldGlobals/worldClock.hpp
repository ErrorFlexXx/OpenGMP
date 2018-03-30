#pragma once

#include <BitStream.h>
#include <Shared/GameObjects/gameObject.hpp>
#include <Shared/Types/worldTime.hpp>

class WorldInst;
class WorldTime;

class WorldClock : public GameObject
{
public:
    WorldClock();
    void SetTime(WorldTime time);
    void SetTime(WorldTime time, float rate);
    void Start();
    void Stop();
    bool GetRunning();
    void UpdateTime();
    WorldTime GetTime() const;
    unsigned long long GetPreciseTicks();
    virtual void ReadStream(RakNet::BitStream &readStream) override;
    virtual void WriteStream(RakNet::BitStream &writeStream) override;

private:
    bool m_isRunning;
    float m_rate;
    unsigned long long m_startTicks;
    WorldTime m_time;
    void SetStartTicks();
};

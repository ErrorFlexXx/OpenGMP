#pragma once

#include <Shared/GameObjects/gameObject.hpp>
#include <Shared/Types/worldTime.hpp>

class World;

class SkyController : public GameObject
{
public:
    SkyController(World *world);
    virtual void SetNextWeight(WorldTime time, float weight);
    virtual void UpdateWeight();
    virtual void ReadStream(RakNet::BitStream &readStream) override;
    virtual void WriteStream(RakNet::BitStream &writeStream) override;

    WorldTime GetStartTime();
    float GetStartWeight();
    WorldTime GetEndTime();
    float GetEndWeight();
    float GetCurrentWeight();

protected:

    /**
     * @brief m_world the world, the skyController is in.
     */
    World *m_world;

private:
    /**
     * @brief startTime The WorldTime from which the interpolation started.
     */
    WorldTime m_startTime;

    /**
     * @brief startWeight The startWeight from which the interpolation started.
     */
    float m_startWeight;

    /**
     * @brief endTime The WorldTime at which the interpolation reaches the EndWeight.
     */
    WorldTime m_endTime;

    /**
     * @brief endWeight The weight reached at the endTime.
     */
    float m_endWeight;

    /**
     * @brief currentWeight The current interpolated weight.
     */
    float m_currentWeight;
};

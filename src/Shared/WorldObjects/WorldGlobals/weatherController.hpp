#ifndef WEATHERCONTROLLER_H
#define WEATHERCONTROLLER_H

#include <Shared/Types/weatherTypes.hpp>
#include "skyController.hpp"
#include <BitStream.h>

class World;

class WeatherController : public SkyController
{
public:
    WeatherController(World *world);
    virtual void SetWeatherType(Types::WeatherTypes type);
    virtual void SetNextWeight(WorldTime time, float weight) override;
    virtual void UpdateWeight() override;
    virtual void ReadStream(RakNet::BitStream &readStream) override;
    virtual void WriteStream(RakNet::BitStream &writeStream) override;

protected:

private:

    Types::WeatherTypes m_type;
};

#endif //WEATHERCONTROLLER

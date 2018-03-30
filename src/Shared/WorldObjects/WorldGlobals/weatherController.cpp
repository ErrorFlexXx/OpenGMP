#include "weatherController.hpp"

WeatherController::WeatherController(World *world)
    : SkyController(world)
{
    m_type = Types::Rain;
}

void WeatherController::SetWeatherType(Types::WeatherTypes type)
{
    m_type = type;
}

void WeatherController::SetNextWeight(WorldTime time, float weight)
{
    SkyController::SetNextWeight(time, weight);
}

void WeatherController::UpdateWeight()
{
    SkyController::UpdateWeight();
}

void WeatherController::ReadStream(RakNet::BitStream &readStream)
{
    SkyController::ReadStream(readStream);
    readStream.Read(m_type);
}

void WeatherController::WriteStream(RakNet::BitStream &writeStream)
{
    SkyController::WriteStream(writeStream);
    writeStream.Write(m_type);
}

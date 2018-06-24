#pragma once

#include "../Objects/iStreamObject.hpp"

class WeatherState : public IStreamObject
{
public:
    WeatherState(const Types::WeatherTypes &type, const WorldTime &startTime,
									const float &startWeight, const WorldTime &endTime, const float &endWeight,
									const float &currentWeight );

	Types::WeatherTypes type;
	WorldTime startTime;
	float startWeight;
	WorldTime endTime;
	float endWeight;
	float currentWeight;

    virtual void WriteStream(RakNet::BitStream &stream) override;
    virtual void ReadStream(RakNet::BitStream &stream) override;
};

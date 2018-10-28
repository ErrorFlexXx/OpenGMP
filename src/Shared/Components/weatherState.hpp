#pragma once

#include "../Objects/iStreamObject.hpp"
#include "../Types/weatherTypes.hpp"

namespace OpenGMP
{
    class WeatherState : public IStreamObject
    {
    public:
        Types::WeatherTypes type;
        WorldTime startTime;
        float startWeight;
        WorldTime endTime;
        float endWeight;
        float currentWeight;

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);
    };
}

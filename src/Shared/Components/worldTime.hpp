#pragma once

#include "../Objects/iStreamObject.hpp"

class WorldTime : public IStreamObject
{
public:
    WorldTime(int totalSeconds);

    int totalSeconds;

    virtual void WriteStream(RakNet::BitStream &stream) override;
    virtual void ReadStream(RakNet::BitStream &stream) override;
};

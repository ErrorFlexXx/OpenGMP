#pragma once

#include "../Objects/iStreamObject.hpp"

class Position : public IStreamObject
{
public:
    Position(float x, float y, float z, float angle);

    float x;
    float y;
    float z;
    float angle;

    virtual void WriteStream(RakNet::BitStream &stream) override;
    virtual void ReadStream(RakNet::BitStream &stream) override;
};

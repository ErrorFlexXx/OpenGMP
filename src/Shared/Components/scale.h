#pragma once

#include "../Objects/iStreamObject.hpp"

class Scale : public IStreamObject
{
public:
    Scale(float x, float y, float z);

    float x;
    float y;
    float z;

    virtual void WriteStream(RakNet::BitStream &stream) override;
    virtual void ReadStream(RakNet::BitStream &stream) override;
};

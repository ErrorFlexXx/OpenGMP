#pragma once

#include "../Objects/iStreamObject.hpp"

class Id : public IStreamObject
{
public:
    Id(int id);

    int id;

    virtual void WriteStream(RakNet::BitStream &stream) override;
    virtual void ReadStream(RakNet::BitStream &stream) override;
};

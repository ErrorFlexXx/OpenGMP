#pragma once

#include "../Objects/iStreamObject.hpp"

class Version : public IStreamObject
{
public:
    Version(RakNet::BitStream &stream);
    Version(int version);

    int version;

    virtual void WriteStream(RakNet::BitStream &stream) override;
    virtual void ReadStream(RakNet::BitStream &stream) override;
};

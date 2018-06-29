#pragma once

#include "../Objects/iStreamObject.hpp"
#include <stdint.h>

class Version : public IStreamObject
{
public:
    Version(RakNet::BitStream &stream);
    Version(const uint32_t &version);

    uint32_t version;

    virtual void WriteStream(RakNet::BitStream &stream) override;
    virtual void ReadStream(RakNet::BitStream &stream) override;
};

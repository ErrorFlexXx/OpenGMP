#pragma once

#include <BitStream.h>

class IStreamObject
{
protected:
    virtual void WriteStream(RakNet::BitStream &stream) = 0;
    virtual void ReadStream(RakNet::BitStream &stream) = 0;
};

#pragma once

namespace RakNet
{
    class BitStream;
}

class GameObject
{
public:
    virtual void WriteStream(RakNet::BitStream &writeStream) = 0;
    virtual void ReadStream(RakNet::BitStream &readStream) = 0;
};

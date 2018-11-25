#pragma once

namespace RakNet
{
    class BitStream;
}

namespace OpenGMP
{
    class Scale
    {
    public:
        Scale();
        Scale(float x, float y, float z);

        float x;
        float y;
        float z;

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);
    };
}

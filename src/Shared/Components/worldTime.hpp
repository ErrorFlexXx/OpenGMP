#pragma once

namespace RakNet
{
    class BitStream;
}

namespace OpenGMP
{
    class WorldTime
    {
    public:
        int totalSeconds;

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);
    };
}

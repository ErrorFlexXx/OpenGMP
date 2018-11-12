#pragma once

#include "../Objects/iStreamObject.hpp"

namespace OpenGMP
{
    class Position : public IStreamObject
    {
    public:
        Position();
        Position(float x, float y, float z, float angle);
        Position(RakNet::BitStream &stream);

        Position & operator+=(const Position &rhs);

        float x;
        float y;
        float z;
        float angle;

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);
    };
}

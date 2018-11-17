#pragma once

#include "../Objects/iStreamObject.hpp"

namespace OpenGMP
{
    class Vec3 : public IStreamObject
    {
    public:
        Vec3();
        Vec3(float x, float y, float z);
        Vec3(RakNet::BitStream &stream);

        float x;
        float y;
        float z;

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);
    };
}

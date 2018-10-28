#pragma once

#include "../Objects/iStreamObject.hpp"

namespace OpenGMP
{
    class Scale : public IStreamObject
    {
    public:
        float x;
        float y;
        float z;

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);
    };
}

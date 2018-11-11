#pragma once

#include "../Objects/iStreamObject.hpp"
#include <stdint.h>
#include "string.hpp"

namespace OpenGMP
{
    class PlayerVisual //: public IStreamObject
    {
    public:
        String bodyModel;
        int32_t bodyTextureId;
        String headModel;
        int32_t headTextureId;
        float fatness;

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);
    };
}

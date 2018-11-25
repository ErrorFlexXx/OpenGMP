#pragma once

#include <Shared/Types/string.hpp>
#include <stdint.h>

namespace OpenGMP
{
    class PlayerVisual
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

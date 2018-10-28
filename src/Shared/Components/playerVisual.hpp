#pragma once

#include "../Objects/iStreamObject.hpp"
#include <stdint.h>
#include <string>

namespace OpenGMP
{
    class PlayerVisual //: public IStreamObject
    {
    public:
        std::string bodyModel;
        int32_t bodyTextureId;
        std::string headModel;
        int32_t headTextureId;
        float fatness;

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);
    };
}

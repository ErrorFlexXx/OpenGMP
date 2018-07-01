#pragma once

#include "../Objects/iStreamObject.hpp"
#include <string>

namespace OpenGMP
{
    namespace Components
    {
        class PlayerVisual : public IStreamObject
        {
        public:
            std::string bodyModel;
            int bodyTextureId;
            std::string headModel;
            int headTextureId;
            float fatness;

            void WriteStream(RakNet::BitStream &stream) const;
            void ReadStream(RakNet::BitStream &stream);
        };
    }
}

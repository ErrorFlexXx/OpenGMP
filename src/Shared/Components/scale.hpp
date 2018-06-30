#pragma once

#include "../Objects/iStreamObject.hpp"

namespace OpenGMP
{
    namespace Components
    {
        class Scale : public IStreamObject
        {
        public:
            float x;
            float y;
            float z;

            void WriteStream(RakNet::BitStream &stream);
            void ReadStream(RakNet::BitStream &stream);
        };
    }
}

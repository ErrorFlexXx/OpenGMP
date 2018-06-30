#pragma once

#include "../Objects/iStreamObject.hpp"

namespace OpenGMP
{
    namespace Components
    {
        class Position : public IStreamObject
        {
        public:
            float x;
            float y;
            float z;
            float angle;

            void WriteStream(RakNet::BitStream &stream);
            void ReadStream(RakNet::BitStream &stream);
        };
    }
}

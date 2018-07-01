#pragma once

#include "../Objects/iStreamObject.hpp"

namespace OpenGMP
{
    namespace Components
    {
        class Id : public IStreamObject
        {
        public:
            Id();

            int id;

            void WriteStream(RakNet::BitStream &stream);
            void ReadStream(RakNet::BitStream &stream);
        };
    }
}
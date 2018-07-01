#pragma once

#include "../Objects/iStreamObject.hpp"

namespace OpenGMP
{
    namespace Components
    {
        class WorldTime : public IStreamObject
        {
        public:
            int totalSeconds;

            void WriteStream(RakNet::BitStream &stream) const;
            bool ReadStream(RakNet::BitStream &stream);
        };
    }
}

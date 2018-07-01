#pragma once

#include "../Objects/iStreamObject.hpp"

#include <map>

namespace OpenGMP
{
    namespace Components
    {
        class IItem;

        class IInventory : public IStreamObject
        {
        public:

            void WriteStream(RakNet::BitStream &stream) const;
            void ReadStream(RakNet::BitStream &stream);
        };
    }
}

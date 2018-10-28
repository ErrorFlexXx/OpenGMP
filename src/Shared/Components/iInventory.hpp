#pragma once

#include "../Objects/iStreamObject.hpp"

#include <map>

namespace OpenGMP
{
    class IItem;

    class IInventory : public IStreamObject
    {
    public:

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);
    };
}

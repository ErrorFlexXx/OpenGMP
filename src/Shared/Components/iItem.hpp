#pragma once

#include "../Objects/iStreamObject.hpp"
#include <string>
#include "id.hpp"

namespace OpenGMP
{
    class IItem : public IStreamObject
    {
    public:
        Id id;
        std::string instance;
        int amount;

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream & stream);
    };
}

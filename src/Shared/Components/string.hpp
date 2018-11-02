#pragma once

#include <Shared/Objects/iStreamObject.hpp>
#include <string>
#include <BitStream.h>
#include <RakNetTypes.h>

namespace OpenGMP
{

    /**
     * @brief The String component
     */
    class String : public IStreamObject
    {
    public:
        std::string text;

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);
    };
}

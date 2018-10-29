#pragma once

#include <Shared/Objects/iStreamObject.hpp>
#include <string>
#include <BitStream.h>
#include <RakNetTypes.h>

namespace OpenGMP
{
    /**
     * @defgroup scriptObject
     * @brief ScriptObjects Elements exposed to scripts
     */

    /**
     * @brief The AuthData component
     * @ingroup scriptObject
     */
    class AuthData : public IStreamObject
    {
    public:
        uint32_t hddSerial;             //!< (available script attribute) the hdd serial
        std::string macAddress;         //!< (available script attribute) the mac address

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);
    };
}

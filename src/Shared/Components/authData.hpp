#pragma once

#include "../Objects/iStreamObject.hpp"
#include <string>
#include <BitStream.h>
#include <RakNetTypes.h>

namespace OpenGMP
{
    namespace Components
    {
        class AuthData : public IStreamObject
        {
        public:
            std::string loginname;
            std::string password;
            unsigned long hddSerial;
            std::string macAddress;
            RakNet::RakNetGUID rakNetGuid;

            void WriteStream(RakNet::BitStream &stream) const;
            void ReadStream(RakNet::BitStream &stream);
        };
    }
}

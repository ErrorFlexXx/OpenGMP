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
            uint32_t hddSerial;
            std::string macAddress;
            RakNet::RakNetGUID rakNetGuid;

            void WriteStream(RakNet::BitStream &stream) const;
            void ReadStream(RakNet::BitStream &stream);

            //Getter and setter for script interface:
            std::string GetLoginname() const;
            void SetLoginname(const std::string &value);
            std::string GetPassword() const;
            void SetPassword(const std::string &value);
            uint32_t GetHddSerial() const;
            void SetHddSerial(uint32_t value);
            std::string GetMacAddress() const;
            void SetMacAddress(const std::string &value);
            RakNet::RakNetGUID GetRakNetGuid() const;
            void SetRakNetGuid(const RakNet::RakNetGUID &value);
        };
    }
}

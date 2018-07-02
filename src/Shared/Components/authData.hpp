#pragma once

#include "../Objects/iStreamObject.hpp"
#include <string>
#include <BitStream.h>
#include <RakNetTypes.h>

namespace OpenGMP
{
    namespace Components
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
            std::string loginname;          //!< (available script attribute) the loginname
            std::string password;           //!< (available script attribute) the cleartext password
            uint32_t hddSerial;             //!< (available script attribute) the hdd serial
            std::string macAddress;         //!< (available script attribute) the mac address

            void WriteStream(RakNet::BitStream &stream) const;
            bool ReadStream(RakNet::BitStream &stream);

            //Getter and setter for script interface:
            std::string GetLoginname() const;
            void SetLoginname(const std::string &value);
            std::string GetPassword() const;
            void SetPassword(const std::string &value);
            uint32_t GetHddSerial() const;
            void SetHddSerial(uint32_t value);
            std::string GetMacAddress() const;
            void SetMacAddress(const std::string &value);
        };
    }
}

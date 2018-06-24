#pragma once

#include "../Objects/iStreamObject.hpp"
#include <string>
#include <BitStream.h>
#include <RakNetTypes.h>

class AuthData : public IStreamObject
{
public:
    //Server constructor
    AuthData(RakNet::BitStream &stream)
    {
        ReadStream(stream);
    }

    //Client constructor
    AuthData(const std::string &loginname,
             const std::string &password,
             int hddSerial,
             const std::string &macAddress,
             RakNet::RakNetGUID rakNetGuid)
        : loginname(loginname)
        , password(password)
        , hddSerial(hddSerial)
        , macAddress(macAddress)
        , rakNetGuid(rakNetGuid) {}

    std::string loginname;
    std::string password;
    int hddSerial;
    std::string macAddress;
    RakNet::RakNetGUID rakNetGuid;

    virtual void WriteStream(RakNet::BitStream &stream) override;
    virtual void ReadStream(RakNet::BitStream &stream) override;
};

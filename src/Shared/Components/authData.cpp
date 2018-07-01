#include "authData.hpp"
#include <RakString.h>
#include <utils/logger.h>

using namespace RakNet;
using namespace OpenGMP::Components;

void AuthData::WriteStream(BitStream &stream) const
{
    RakString rakLoginname("%s", loginname.c_str());
    RakString rakPassword("%s", password.c_str());
    RakString rakMacAddress("%s", macAddress.c_str());

    stream.Write(rakLoginname);
    stream.Write(rakPassword);
    stream.Write(hddSerial);
    stream.Write(rakMacAddress);
}

void AuthData::ReadStream(BitStream &stream)
{
    RakString rakLoginname;
    RakString rakPassword;
    RakString rakMacAddress;

    stream.Read(rakLoginname);
    stream.Read(rakPassword);
    stream.Read(hddSerial);
    stream.Read(rakMacAddress);

    loginname = rakLoginname;
    macAddress = rakMacAddress;
    password = rakPassword;
}

std::string AuthData::GetLoginname() const
{
    return loginname;
}

void AuthData::SetLoginname(const std::string &value)
{
    loginname = value;
}

std::string AuthData::GetPassword() const
{
    return password;
}

void AuthData::SetPassword(const std::string &value)
{
    password = value;
}

uint32_t AuthData::GetHddSerial() const
{
    return hddSerial;
}

void AuthData::SetHddSerial(uint32_t value)
{
    hddSerial = value;
}

std::string AuthData::GetMacAddress() const
{
    return macAddress;
}

void AuthData::SetMacAddress(const std::string &value)
{
    macAddress = value;
}

RakNet::RakNetGUID AuthData::GetRakNetGuid() const
{
    return rakNetGuid;
}

void AuthData::SetRakNetGuid(const RakNet::RakNetGUID &value)
{
    rakNetGuid = value;
}

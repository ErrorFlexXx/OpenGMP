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
    LogInfo() << stream.GetData();
    RakString rakLoginname;
    RakString rakPassword;
    RakString rakMacAddress;
    LogInfo() << "Hey1";
    stream.Read(rakLoginname);
    LogInfo() << "Hey2";
    stream.Read(rakPassword);
    LogInfo() << "Hey3";
    stream.Read(hddSerial);
    LogInfo() << "Hey4";
    stream.Read(rakMacAddress);
    LogInfo() << "Hey5";

    loginname = rakLoginname;
    LogInfo() << "Hey6";
    macAddress = rakMacAddress;
    LogInfo() << "Hey7";
    password = rakPassword;
    LogInfo() << "Hey8";
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

unsigned long AuthData::GetHddSerial() const
{
    return hddSerial;
}

void AuthData::SetHddSerial(unsigned long value)
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

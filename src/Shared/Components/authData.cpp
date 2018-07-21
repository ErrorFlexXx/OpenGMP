#include "authData.hpp"
#include <RakString.h>

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

bool AuthData::ReadStream(BitStream &stream)
{
    RakString rakLoginname;
    RakString rakPassword;
    RakString rakMacAddress;
    bool success;

                success = stream.Read(rakLoginname);
    if(success) success = stream.Read(rakPassword);
    if(success) success = stream.Read(hddSerial);
    if(success) success = stream.Read(rakMacAddress);

    if(success)
    {
        loginname = rakLoginname;
        macAddress = rakMacAddress;
        password = rakPassword;
    }
    return success;
}

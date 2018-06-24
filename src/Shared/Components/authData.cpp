#include "authData.h"
#include <RakString.h>

using namespace RakNet;

void AuthData::WriteStream(BitStream &stream)
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

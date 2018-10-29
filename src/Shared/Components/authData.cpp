#include "authData.hpp"
#include <RakString.h>

using namespace RakNet;
using namespace OpenGMP;

void AuthData::WriteStream(BitStream &stream) const
{
    RakString rakMacAddress("%s", macAddress.c_str());

    stream.Write(hddSerial);
    stream.Write(rakMacAddress);
}

bool AuthData::ReadStream(BitStream &stream)
{
    RakString rakMacAddress;
    bool success;

                success = stream.Read(hddSerial);
    if(success) success = stream.Read(rakMacAddress);

    if(success)
    {
        macAddress = rakMacAddress;
    }
    return success;
}

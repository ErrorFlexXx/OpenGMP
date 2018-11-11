#include "authData.hpp"
#include <RakString.h>

using namespace RakNet;
using namespace OpenGMP;

void AuthData::WriteStream(BitStream &stream) const
{
    stream.Write(hddSerial);
    macAddress.WriteStream(stream);
}

bool AuthData::ReadStream(BitStream &stream)
{
    bool success;

                success = stream.Read(hddSerial);
    if(success) success = macAddress.ReadStream(stream);

    return success;
}

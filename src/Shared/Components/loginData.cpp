#include "loginData.hpp"

using namespace RakNet;
using namespace OpenGMP;

void LoginData::WriteStream(BitStream &stream) const
{
    loginname.WriteStream(stream);
    password.WriteStream(stream);
}

bool LoginData::ReadStream(BitStream &stream)
{
    bool success;

    success = loginname.ReadStream(stream);
    if(success) success = password.ReadStream(stream);

    return success;
}

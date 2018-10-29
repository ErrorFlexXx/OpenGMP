#include "loginData.hpp"
#include <RakString.h>

using namespace RakNet;
using namespace OpenGMP;

void LoginData::WriteStream(BitStream &stream) const
{
    RakString rakLoginname("%s", loginname.c_str());
    RakString rakPassword("%s", password.c_str());

    stream.Write(rakLoginname);
    stream.Write(rakPassword);
}

bool LoginData::ReadStream(BitStream &stream)
{
    RakString rakLoginname;
    RakString rakPassword;
    bool success;

                success = stream.Read(rakLoginname);
    if(success) success = stream.Read(rakPassword);

    if(success)
    {
        loginname = rakLoginname;
        password = rakPassword;
    }
    return success;
}

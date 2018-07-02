#include "netIdObject.hpp"

using namespace OpenGMP::Components;
using namespace OpenGMP::Objects;

NetId NetIdObject::GetNetId() const
{
    return netId;
}

void NetIdObject::SetNetId(const NetId &value)
{
    netId = value;
}

#include "iItem.hpp"
#include <RakString.h>

using namespace RakNet;
using namespace OpenGMP::Components;

void IItem::WriteStream(BitStream &stream) const
{
    RakString rakInstance("%s", instance.c_str());

    id.WriteStream(stream);
    stream.Write(rakInstance);
    stream.Write(amount);
}

bool IItem::ReadStream(BitStream &stream)
{
    RakString rakInstance;
    bool success;

                success = id.ReadStream(stream);
    if(success) success = stream.Read(rakInstance);
    if(success) success = stream.Read(amount);

    if(success)
        instance = rakInstance;
    return success;
}

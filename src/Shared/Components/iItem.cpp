#include "iItem.hpp"
#include <RakString.h>

using namespace RakNet;
using namespace OpenGMP::Components;

void IItem::WriteStream(BitStream &stream)
{
    RakString rakInstance("%s", instance.c_str());

    id.WriteStream(stream);
    stream.Write(rakInstance);
    stream.Write(amount);
}

void IItem::ReadStream(BitStream &stream)
{
    RakString rakInstance;

    id.ReadStream(stream);
    stream.Read(rakInstance);
    stream.Read(amount);

    instance = rakInstance;
}

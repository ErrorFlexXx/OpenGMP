#include "iItem.h"

#include <RakString.h>

using namespace RakNet;

IItem::IItem()
    : id(0)
    , instance("")
    , amount(0)
{}

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

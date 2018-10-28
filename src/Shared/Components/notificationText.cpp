#include "notificationText.hpp"
#include <RakString.h>

using namespace RakNet;
using namespace OpenGMP;

NotificationText::NotificationText()
{
}

void NotificationText::WriteStream(BitStream &stream) const
{
    RakString rakText("%s", text.c_str());
    
    stream.Write(rakText);
    stream.Write(posY);
    color.WriteStream(stream);
    stream.Write(duration);    
}

bool NotificationText::ReadStream(BitStream &stream)
{
    RakString rakText;
    bool success;

    success = stream.Read(rakText);
    if (success) success = stream.Read(posY);
    if (success) success = color.ReadStream(stream);
    if (success) success = stream.Read(duration);

    if (success)
    {
        text = rakText;
    }
    return success;
}

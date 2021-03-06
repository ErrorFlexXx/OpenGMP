#include "notificationText.hpp"
#include <RakString.h>

using namespace RakNet;
using namespace OpenGMP;

NotificationText::NotificationText()
{
}

NotificationText::NotificationText(const std::string &text, uint32_t posY, const Color &color, uint32_t duration)
    : text(text)
    , posY(posY)
    , color(color)
    , duration(duration)
{
}

void NotificationText::WriteStream(BitStream &stream) const
{
    text.WriteStream(stream);
    stream.Write(posY);
    color.WriteStream(stream);
    stream.Write(duration);    
}

bool NotificationText::ReadStream(BitStream &stream)
{
    bool success;

    success = text.ReadStream(stream);
    if (success) success = stream.Read(posY);
    if (success) success = color.ReadStream(stream);
    if (success) success = stream.Read(duration);

    return success;
}

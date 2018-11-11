#include "playerVisual.hpp"
#include <RakString.h>

using namespace RakNet;
using namespace OpenGMP;

void PlayerVisual::WriteStream(BitStream &stream) const
{    
    bodyModel.WriteStream(stream);
    stream.Write(bodyTextureId);
    headModel.WriteStream(stream);
    stream.Write(headTextureId);
    stream.Write(fatness);
}

bool PlayerVisual::ReadStream(BitStream &stream)
{
    bool success;

                success = bodyModel.ReadStream(stream);
    if(success) success = stream.Read(bodyTextureId);
    if(success) success = headModel.ReadStream(stream);
    if(success) success = stream.Read(headTextureId);
    if(success) success = stream.Read(fatness);

    return success;
}

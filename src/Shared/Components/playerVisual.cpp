#include "playerVisual.hpp"
#include <RakString.h>

using namespace RakNet;
using namespace OpenGMP::Components;

void PlayerVisual::WriteStream(BitStream &stream) const
{
    RakString rakBodyModel("%S", bodyModel.c_str());
    RakString rakHeadModel("%s", headModel.c_str());
    
    stream.Write(rakBodyModel);
    stream.Write(bodyTextureId);
    stream.Write(rakHeadModel);
    stream.Write(headTextureId);
    stream.Write(fatness);
}

bool PlayerVisual::ReadStream(BitStream &stream)
{
    RakString rakBodyModel;
    RakString rakHeadModel;
    bool success;

                success = stream.Read(rakBodyModel);
    if(success) success = stream.Read(bodyTextureId);
    if(success) success = stream.Read(rakHeadModel);
    if(success) success = stream.Read(headTextureId);
    if(success) success = stream.Read(fatness);

    if(success)
    {
        bodyModel = rakBodyModel;
        headModel = rakHeadModel;
    }
    return success;
}

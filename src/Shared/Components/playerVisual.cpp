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

void PlayerVisual::ReadStream(BitStream &stream)
{
    RakString rakBodyModel;
    RakString rakHeadModel;

    stream.Read(rakBodyModel);
    stream.Read(bodyTextureId);
    stream.Read(rakHeadModel);
    stream.Read(headTextureId);
    stream.Read(fatness);

    bodyModel = rakBodyModel;
    headModel = rakHeadModel;
}

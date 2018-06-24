#pragma once

#include "../Objects/iStreamObject.hpp"

#include <string>

class PlayerVisual : public IStreamObject
{
public:
    PlayerVisual();

    std::string bodyModel;
    int bodyTextureId;
    std::string headModel;
    int headTextureId;
    float fatness;

    virtual void WriteStream(RakNet::BitStream &stream) override;
    virtual void ReadStream(RakNet::BitStream &stream) override;
};

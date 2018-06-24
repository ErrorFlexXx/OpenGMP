#pragma once

#include "../Objects/iStreamObject.hpp"

#include <string>

#include "id.h"

class IItem : public IStreamObject
{
public:
    IItem();
    virtual ~IItem() {}
    
    Id id;
    std::string instance;
    int amount;

    virtual void WriteStream(RakNet::BitStream &stream) override;
    virtual void ReadStream(RakNet::BitStream & stream) override;
};

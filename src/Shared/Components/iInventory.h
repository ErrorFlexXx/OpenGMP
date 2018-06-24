#pragma once

#include "../Objects/iStreamObject.hpp"

#include <map>

class IItem;

class IInventory : public IStreamObject
{
public:
    IInventory();
    virtual ~IInventory() {}
    
    std::map<int, IItem*> container;

    virtual void WriteStream(RakNet::BitStream &stream) override;
    virtual void ReadStream(RakNet::BitStream &stream) override;
};

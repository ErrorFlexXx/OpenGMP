#include "iInventory.h"

#include "iItem.h"

IInventory::IInventory()
{}

void IInventory::WriteStream(RakNet::BitStream &stream)
{
    unsigned int amount = container.size();
    
    stream.Write(amount);
    for (std::map<int, IItem*>::iterator it = container.begin(); it != container.end(); it++)
    {
        it->second->WriteStream(stream);
    }
}

void IInventory::ReadStream(RakNet::BitStream &stream)
{
    unsigned int amount;
    container.clear();

    stream.Read(amount);
    //Read all items
    for(unsigned int i = 0; i < amount && 0 < stream.GetNumberOfUnreadBits(); i++)
    {

    }
}
#include "iInventory.hpp"
#include "iItem.hpp"

using namespace OpenGMP::Components;

void IInventory::WriteStream(RakNet::BitStream &stream) const
{

}

bool IInventory::ReadStream(RakNet::BitStream &stream)
{
    bool success = true;
    return success;
}

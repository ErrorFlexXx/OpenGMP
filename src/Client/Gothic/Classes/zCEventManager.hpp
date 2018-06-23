#pragma once

#include "../xcall.h"

class zCEventManager
{
    static const struct VarOffsets
    {
        static const unsigned int OwnerAddress = 0x3C;
    } VarOffsets;

public:
    static bool DisableEventManagers()
    {
        return *(bool*)(0x00AB39C8);
    }

    static void DisableEventManagers(bool value)
    {
        *(bool*)(0x00AB39C8) = value;
    }

    int OwnerAddress()
    {
        return *(int*)((unsigned int)this + VarOffsets::OwnerAddress);
    }
};
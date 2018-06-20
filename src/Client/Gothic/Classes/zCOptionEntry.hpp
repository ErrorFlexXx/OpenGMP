#pragma once

#include "../xcall.h"
#include "../Types/zSTRING.hpp"

class zCOptionEntry
{
public:
    zCOptionEntry(class zSTRING const &, class zSTRING const &)
    {
        XCALL(0x0045FE00);
    }

    ~zCOptionEntry()
    {
        XCALL(0x004606F0);
    }

    zSTRING *GetVarName()
    {
        return (zSTRING*)((unsigned int)this + 16);
    }

    zSTRING *GetVarValue()
    {
        return (zSTRING*)((unsigned int)this + 36);
    }
};
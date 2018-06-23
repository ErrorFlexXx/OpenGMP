#pragma once

#include "../xcall.h"

class zCSkyControler
{
public:

    static const struct VarOffsets
    {
        static const int bFillBackground = 0x38;
    } VarOffsets;

    bool FillBackground()
    {
        return *((bool*)((unsigned int)this + VarOffsets::bFillBackground));
    }

    void FillBackground(bool value)
    {
        *((bool*)((unsigned int)this + VarOffsets::bFillBackground)) = value;
    }
};
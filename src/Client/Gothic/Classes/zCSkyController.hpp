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
        return *((bool*)(this + VarOffsets::bFillBackground));
    }

    void FillBackground(bool value)
    {
        *((bool*)(this + VarOffsets::bFillBackground)) = value;
    }
};
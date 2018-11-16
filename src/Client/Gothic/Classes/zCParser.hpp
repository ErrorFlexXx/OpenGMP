#pragma once

#include "../xcall.h"

class zCParser
{
public:
    static zCParser *GetParser()
    {
        return (zCParser*)0x00AB40C0;
    }

    int GetIndex(class zSTRING const &)
    {
        XCALL(0x00793470);
    };
};
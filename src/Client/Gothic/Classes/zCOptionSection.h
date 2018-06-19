#pragma once

#include "../xcall.h"
#include "../Types/zSTRING.h"

class zCOptionSection
{
public:
    zCOptionSection(class zSTRING const &)
    {
        XCALL(0x00460080);
    }

    ~zCOptionSection()
    {
        XCALL(0x00460240);
    }

    zSTRING sectionName; //Offset 0
    //Entry List Offset 20
};
#pragma once

#include "../xcall.h"

class zCObject
{
public:

    //Releases an object, which has been allocated with zNEW, if no one has a handle to it.
    //Hand made smart pointer.
    int Release()
    {
        XCALL(0x0040C310);
    }
};
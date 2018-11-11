#pragma once

#include "../xcall.h"

class oCNpc;
class oCItem;

class oCObjectFactory
{
public:
    static oCObjectFactory *GetFactory()
    {
        return *(oCObjectFactory**)0x008D8DF0;
    }

    oCNpc *CreateNpc(const int parserIndex = -1) //-1 : do not init by parser.
    {
        XCALL(0x0076FD20);
    }

    oCItem *CreateItem(const int parserIndex = -1) //-1 : do not init by parser.
    {
        XCALL(0x0076FDE0);
    }
};
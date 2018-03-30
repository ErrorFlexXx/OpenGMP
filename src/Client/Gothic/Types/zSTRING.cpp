#include "zSTRING.hpp"
#include "../xcall.h"

int __cdecl operator==(zSTRING const &, char const * const)
{
    XCALL(0x006CFF50);
}

int __cdecl operator==(zSTRING const &, zSTRING const &)
{
    XCALL(0x00674220);
}
#pragma once

#include "../xcall.h"
#include "oCVob.hpp"

class oCMOB : public oCVob
{
public:
    static oCMOB * CreateNewInstance()
    {
        XCALL(0x00718590);
    }

    void SetMoveable(int)
    {
        XCALL(0x0071BF00);
    }
        
    int IsMoveable(void)
    {
        XCALL(0x0071BF20);
    }
        
    void SetOwner(class zSTRING const &, class zSTRING const &)
    {
        XCALL(0x0071BF80);
    }
        
    void SetOwner(int, int)
    {
        XCALL(0x0071C170);
    }
        
    int IsOwner(class oCNpc *)
    {
        XCALL(0x0071C1D0);
    }
        
    void Hit(int)
    {
        XCALL(0x0071C220);
    }

private:
    oCMOB(); //Use CreateNewInstance for creation.
    unsigned char load[188];
};

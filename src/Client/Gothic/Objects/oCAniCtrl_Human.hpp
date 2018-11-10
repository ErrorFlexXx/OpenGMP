#pragma once

#include "../xcall.h"

enum {
    ANI_WALKMODE_RUN, ANI_WALKMODE_WALK, ANI_WALKMODE_SNEAK,
    ANI_WALKMODE_WATER, ANI_WALKMODE_SWIM, ANI_WALKMODE_DIVE
};

class oCAniCtrl_Human
{
public:
    void PC_GoForward()
    {
        XCALL(0x006B1D70);
    }
        
    void PC_GoBackward()
    {
        XCALL(0x006B1DC0);
    }
        
    void PC_JumpForward()
    {
        XCALL(0x006B1E00);
    }

    void _Stand()
    {
        XCALL(0x006B7490);
    }
    
    void _Forward()
    {
        XCALL(0x006B7900);
    }
    
    void _Backward()
    {
        XCALL(0x006B7BC0);
    }

    void StrafeLeft()
    {
        XCALL(0x006B1B40);
    }
        
    void StrafeRight()
    {
        XCALL(0x006B1B80);
    }

    void SetWalkMode(int walkmode)
    {
        XCALL(0x006A9820);
    }
    /**
     * @brief oCAniCtrl_Human::LookAtTarget
     *  Has to be called per frame, to actually move the head to the target. 
     */
    void LookAtTarget()
    {
        XCALL(0x006B62F0);
    }

    void SetLookAtTarget(float x, float y)
    {
        XCALL(0x006B6310);
    }
    
    void SetLookAtTarget(class zVEC3 &position)
    {
        XCALL(0x006B6360);
    }
        
    void SetLookAtTarget(class zCVob *target)
    {
        XCALL(0x006B6490);
    }
    
    void StopLookAtTarget()
    {
        XCALL(0x006B6640);    
    }

    void StopTurnAnis()
    {
        XCALL(0x006AE530);
    }

    void StartStandAni(void)
    {
        XCALL(0x006A5060);
    }

    void SearchStandAni(int force = 0)
    {
        XCALL(0x006A4D20);
    }

    int IsStanding()
    {
        XCALL(0x006ADEE0);
    }

    int IsJumpStanding()
    {
        XCALL(0x006AE080);
    }
        
    int IsWalking()
    {
        XCALL(0x006AE0E0);
    }
        
    int IsRunning()
    {
        XCALL(0x006AE200);
    }
    
    int IsWalkingBackward()
    {
        XCALL(0x006AE410);
    }

    float Turn(float deg, int playAnis)
    {
        XCALL(0x006AE540);
    }
};
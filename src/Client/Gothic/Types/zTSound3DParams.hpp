#pragma once

#include "../xcall.h"

class zTSound3DParams
{
public:
    zTSound3DParams() 
    { 
        SetDefaults();
    };
    
    //Note original was: zCSoundSystem::zTSound3DParams::SetDefaults(void)
    //Unsure if struct in class zCSoundSystem or class in class would be more correct.
    void zTSound3DParams::SetDefaults()
    {
        XCALL(0x00612F50);
    }

    int m_obstruction;
    float m_volume;
    float m_radius;
    int m_loopType;
    float m_angle;
    float m_reverb;
    int m_isAmbient;
    float m_pitch;
};
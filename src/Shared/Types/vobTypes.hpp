#pragma once

namespace OpenGMP
{
    /**
     * @brief The VobTypes enum
     *  Covers identifiers for all kinds of vobs.
     */
    enum VobTypes : unsigned char
    {
        Vob,
        NPC,
        Item,
        Projectile,
        Mob,
        MobInter,
        MobFire,
        MobLadder,
        MobSwitch,
        MobWheel,
        MobContainer,
        MobDoor,
        MobBed,
        Maximum //The 'size' element to get the maximum count of
        //available VobTypes.
    };
}

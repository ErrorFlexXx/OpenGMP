#pragma once

namespace OpenGMP
{
    enum NPCMovement : unsigned char
    {
        GOTOPOS,
        GOTOVOB,
        GOROUTE,
        TURN,
        TURNTOPOS,
        TURNTOVOB,
        TURNAWAY,
        JUMP,
        SETWALKMODE,
        WHIRLAROUND,
        STANDUP,
        STRAFE,
        GOTOFP,
        DODGE,
        BEAMTO,
        ALIGNTOFP
    };
}

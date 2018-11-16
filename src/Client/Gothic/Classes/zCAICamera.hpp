#pragma once

#include "../xcall.h"

enum zTAICamMsg
{
    zPLAYER_MOVED_FORWARD = 1 << 1,
    zPLAYER_MOVED_BACKWARD = 1 << 2,
    zPLAYER_MOVED_LEFT = 1 << 3,
    zPLAYER_MOVED_RIGHT = 1 << 4,
    zPLAYER_MOVED_UP = 1 << 5,
    zPLAYER_MOVED_DOWN = 1 << 6,
    zPLAYER_ROTATED_LEFT = 1 << 7,
    zPLAYER_ROTATED_RIGHT = 1 << 8,
    zPLAYER_ROTATED_UP = 1 << 9,
    zPLAYER_ROTATED_DOWN = 1 << 10,
    zPLAYER_MOVED = 1 << 11,
    zPLAYER_STAND = 1 << 12,
    zPLAYER_ROTATED = 1 << 13,
    zPLAYER_ROT_NONE = 1 << 14,
    zPLAYER_BEAMED = 1 << 15
};

class zCAICamera
{
public:
    void SetTarget(class zCVob *)
    {
        XCALL(0x004A1120);
    }

    void ClearTargetList()
    {
        XCALL(0x004A1870);
    }

    void ReceiveMsg(enum zTAICamMsg const &)
    {
        XCALL(0x004A0E30);
    }
};
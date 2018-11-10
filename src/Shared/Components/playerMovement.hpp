#pragma once

#include <BitStream.h>

namespace OpenGMP
{
    class PlayerMovement
    {
    public:
        enum Movement : unsigned char
        {
            Stand = 0,
            Forward,
            Backward,
            Left,
            Right,
            TurnLeft,
            TurnRight
        };
        
        PlayerMovement();
        PlayerMovement(unsigned char move);
        
        operator unsigned char() { return movementState; } //Allow implicit cast
        bool operator <(const PlayerMovement &rhs) const { return movementState < rhs.movementState; } //Required for storage in map

        void WriteStream(RakNet::BitStream &stream) const;
        bool ReadStream(RakNet::BitStream &stream);

        unsigned char movementState;
    };
}
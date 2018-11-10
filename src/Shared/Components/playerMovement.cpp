#include "playerMovement.hpp"

using namespace OpenGMP;

PlayerMovement::PlayerMovement()
    : movementState(Stand)
{}

PlayerMovement::PlayerMovement(unsigned char movement)
    : movementState(movement)
{}

void PlayerMovement::WriteStream(RakNet::BitStream &stream) const
{
    stream.Write(movementState);
}

bool PlayerMovement::ReadStream(RakNet::BitStream &stream)
{
    bool success;

    success = stream.Read(movementState);

    return success;
}
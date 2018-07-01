#include "playerTalents.hpp"

using namespace OpenGMP::Components;

int PlayerTalents::HasTalent(EnumTalents talent)
{
    return talents & (1 << talent);
}

void PlayerTalents::SetTalent(EnumTalents talent)
{
    talents |= (1 << talent);
}

void PlayerTalents::WriteStream(RakNet::BitStream &stream) const
{
    stream.Write(talents);
}

bool PlayerTalents::ReadStream(RakNet::BitStream &stream)
{
    bool success;

    success = stream.Read(talents);

    return success;
}

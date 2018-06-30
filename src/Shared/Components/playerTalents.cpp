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

void PlayerTalents::WriteStream(RakNet::BitStream &stream)
{
    stream.Write(talents);
}

void PlayerTalents::ReadStream(RakNet::BitStream &stream)
{
    stream.Read(talents);
}

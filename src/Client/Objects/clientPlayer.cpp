#include "clientPlayer.hpp"

using namespace OpenGMP;

ClientPlayer::ClientPlayer()
    : ClientPlayer(nullptr)
{}

ClientPlayer::ClientPlayer(oCNpc *gothicPlayer)
    : gothicPlayer(gothicPlayer)
{}


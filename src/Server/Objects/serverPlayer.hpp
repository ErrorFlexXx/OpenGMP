#pragma once

#include <Shared/Objects/player.hpp>
#include <Server/Objects/serverClient.hpp>

namespace OpenGMP
{
    class ServerWorld;

    class ServerPlayer : public Player
    {
    public:
        ServerPlayer() : Player() {}

        ServerWorld world;      //!< World the player is in
        ServerClient client;    //!< Client which controls the player
    };
}

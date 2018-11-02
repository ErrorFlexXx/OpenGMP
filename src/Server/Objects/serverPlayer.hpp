#pragma once

#include <Shared/Objects/player.hpp>
#include <Server/Objects/serverClient.hpp>

namespace OpenGMP
{
    class ServerWorld;

    class ServerPlayer : public Player
    {
    public:
        ServerPlayer()
            : world(nullptr)
            , client(nullptr)
        {}

        ServerWorld *world;
        ServerClient *client;
    };
}

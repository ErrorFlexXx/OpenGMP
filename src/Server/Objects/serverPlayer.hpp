#pragma once

#include <Shared/Objects/player.hpp>

namespace OpenGMP
{
    class ServerWorld;

    class ServerPlayer : public Player
    {
    public:
        ServerPlayer()
            : world(nullptr)
        {}

        ServerWorld *world;
    };
}

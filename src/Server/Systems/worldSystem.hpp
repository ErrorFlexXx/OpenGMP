#pragma once

#include <string>

namespace OpenGMP
{
    class GameServer;
    class ServerPlayer;
    class ServerWorld;

    class WorldSystem
    {
    public:
        WorldSystem(GameServer &gameServer);

        ServerWorld &AddWorld(std::string &worldName);
        void Spawn(ServerPlayer &player);

        GameServer &gameServer;
    };
}

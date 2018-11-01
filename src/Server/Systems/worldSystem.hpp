#pragma once

#include <string>

namespace OpenGMP
{
    class GameServer;
    class ServerPlayer;
    class ServerWorld;
    class Id;

    class WorldSystem
    {
    public:
        WorldSystem(GameServer &gameServer);

        ServerWorld &AddWorld(int id, std::string &worldName);
        void SpawnPlayer(ServerPlayer &player, ServerWorld &world);

        GameServer &gameServer;
    };
}

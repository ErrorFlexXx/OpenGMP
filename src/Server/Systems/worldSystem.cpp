#include "worldSystem.hpp"
#include <utils/logger.h>
#include "../gameServer.hpp"
#include <Server/Objects/serverWorld.hpp>
#include <Server/Objects/serverPlayer.hpp>
#include <Shared/Components/id.hpp>

using namespace OpenGMP;

WorldSystem::WorldSystem(GameServer &gameServer)
    : gameServer(gameServer)
{
}

ServerWorld &WorldSystem::AddWorld(int id, std::string &worldName)
{
    LogInfo() << "Hello World";
    Id worldId;
    worldId.id = id;
    ServerWorld &world = gameServer.worldContainer.Get(worldId);
    LogInfo() << "Added world " << id << " with name " << worldName;
    return world;
}

void WorldSystem::SpawnPlayer(ServerPlayer &player, ServerWorld &world)
{
    player.world = &world;
}

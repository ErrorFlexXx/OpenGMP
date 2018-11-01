#include "worldSystem.hpp"
#include <utils/logger.h>
#include "../gameServer.hpp"
#include <Server/Objects/serverWorld.hpp>
#include <Server/Objects/serverPlayer.hpp>

using namespace OpenGMP;

WorldSystem::WorldSystem(GameServer &gameServer)
    : gameServer(gameServer)
{
}

ServerWorld &WorldSystem::AddWorld(std::string &worldName)
{
    Id id;
    ServerWorld &world = gameServer.worldContainer.CreateEntity(id);
    LogInfo() << "Created world with name " << worldName << " ID: " << id.id;
    return world;
}

void WorldSystem::Spawn(ServerPlayer &player)
{

}

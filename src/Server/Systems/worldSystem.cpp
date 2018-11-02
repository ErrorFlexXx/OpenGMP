#include "worldSystem.hpp"
#include <utils/logger.h>
#include "../gameServer.hpp"
#include <Server/Objects/serverWorld.hpp>
#include <Server/Objects/serverPlayer.hpp>
#include <Shared/Components/id.hpp>
#include <Shared/Types/Messages/worldSystemMessages.hpp>

using namespace RakNet;
using namespace OpenGMP;

WorldSystem::WorldSystem(GameServer &gameServer)
    : gameServer(gameServer)
{
}

ServerWorld &WorldSystem::AddWorld(int id, std::string &worldName)
{
    Id worldId;
    worldId.id = id;
    ServerWorld &world = gameServer.worldContainer.Get(worldId);
    world.worldName.text = worldName;
    LogInfo() << "Added world " << id << " with name " << worldName;
    return world;
}

ServerWorld &WorldSystem::GetStoredWorld(int index)
{
    Id id;
    id.id = index;
    return gameServer.worldContainer.Get(id);
}

void WorldSystem::LoadWorld(ServerClient &client, ServerWorld &world)
{
    LogInfo() << "Peak";
    BitStream bs;
    LogInfo() << "Peak";
    bs.Write(NetworkSystemMessages::WorldSystem);
    LogInfo() << "Peak";
    bs.Write(worldSystemMessages::LOAD_WORLD);
    LogInfo() << "Peak";
    world.id.WriteStream(bs);
    LogInfo() << "Peak";
    world.worldName.WriteStream(bs);
    LogInfo() << "Peak";
    SendWorldSystemMessage(client.netId.rakNetId, bs);
    LogInfo() << "Peak";
}

void WorldSystem::SendWorldSystemMessage(const RakNetGUID &dest, const BitStream &bsOut)
{
    gameServer.networkSystem.peerInterface->Send(
                &bsOut, LOW_PRIORITY, RELIABLE_ORDERED, WorldSystemOrderingChannel, dest, false);
}

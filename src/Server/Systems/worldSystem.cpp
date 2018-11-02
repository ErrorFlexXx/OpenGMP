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
    LogInfo() << "Added world " << id << " with name " << worldName;
    return world;
}

void WorldSystem::LoadWorld(ServerClient &client, ServerWorld &world)
{
    BitStream bs;
    bs.Write(NetworkSystemMessages::WorldSystem);
    bs.Write(worldSystemMessages::LOAD_WORLD);
    world.id.WriteStream(bs);
    world.worldName.WriteStream(bs);
    SendWorldSystemMessage(client.netId.rakNetId, bs);
}

void WorldSystem::SendWorldSystemMessage(const RakNetGUID &dest, const BitStream &bsOut)
{
    gameServer.networkSystem.peerInterface->Send(
                &bsOut, LOW_PRIORITY, RELIABLE_ORDERED, WorldSystemOrderingChannel, dest, false);
}

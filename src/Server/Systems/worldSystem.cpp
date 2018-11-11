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
    ServerWorld &world = gameServer.worldContainer.Get(id);
    world.id = id;
    world.worldName = worldName;
    LogInfo() << "Added world ID: " << id << " Path: " << worldName;
    return world;
}

ServerWorld &WorldSystem::GetStoredWorld(int index)
{
    return gameServer.worldContainer.Get(index);
}

void WorldSystem::LoadWorld(ServerClient &client, ServerWorld &world)
{
    BitStream bs;
    bs.Write((NetMessage) NetworkSystemMessages::WorldSystem);
    bs.Write((NetMessage) WorldSystemMessages::LOAD_WORLD);
    world.id.WriteStream(bs);
    world.worldName.WriteStream(bs);
    SendWorldSystemMessage(client.netId.rakNetId, bs);
    client.world = world; //Assign world to client.
}

void WorldSystem::SendWorldSystemMessage(const RakNetGUID &dest, const BitStream &bsOut)
{
    gameServer.networkSystem.peerInterface->Send(
                &bsOut, LOW_PRIORITY, RELIABLE_ORDERED, WorldSystemOrderingChannel, dest, false);
}

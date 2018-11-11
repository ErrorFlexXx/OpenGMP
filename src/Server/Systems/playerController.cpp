#include "playerController.hpp"
#include <utils/logger.h>
#include "../gameServer.hpp"
#include <Server/Objects/serverWorld.hpp>
#include <Server/Objects/serverPlayer.hpp>
#include <Shared/Components/id.hpp>
#include <Shared/Types/Messages/playerControllerMessages.hpp>

using namespace RakNet;
using namespace OpenGMP;

PlayerController::PlayerController(GameServer &gameServer)
    : gameServer(gameServer)
{
}

void PlayerController::SpawnPlayer(ServerPlayer &player, ServerWorld &world)
{
    ;
}

void PlayerController::ClientEnteringWorld(ServerClient &client)
{
    //ToDo:
    //Will transmit all active playerContainer player from world.
    //Has to iterate to the dynamicContainer for that purpose.
}

void PlayerController::ControlPlayer(const ServerClient &client, const ServerPlayer &player)
{
    BitStream bs;
    bs.Write((NetMessage) NetworkSystemMessages::PlayerController);
    bs.Write((NetMessage) PlayerControllerMessages::CONTROL_PLAYER);
    player.id.WriteStream(bs);
    SendPlayerControllerMessage(client.netId.rakNetId, bs);
}

void PlayerController::SendPlayerControllerMessage(const RakNetGUID &dest, const BitStream &bsOut)
{
    gameServer.networkSystem.peerInterface->Send(
                &bsOut, LOW_PRIORITY, RELIABLE_ORDERED, PlayerControllerOrderingChannel, dest, false);
}

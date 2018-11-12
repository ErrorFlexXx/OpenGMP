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

void PlayerController::Process(RakNet::Packet *packet)
{
    NetMessage command;
    BitStream bsIn(packet->data, packet->length, false);
    bsIn.IgnoreBytes(1); //PlayerController
    bsIn.Read(command);

    switch(command)
    {
        case PlayerControllerMessages::MOVEMENT_CHANGE:
        {
            bool success;
            ServerPlayer &player = gameServer.playerContainer.Get(packet->guid, success);

            if(success)
            {
                player.movement.ReadStream(bsIn);
                BitStream bs;
                bs.Write((NetMessage)NetworkSystemMessages::PlayerController);
                bs.Write((NetMessage)PlayerControllerMessages::MOVEMENT_CHANGE);
                player.id.WriteStream(bs);
                player.movement.WriteStream(bs);
                for(auto &sendPlayer : gameServer.playerContainer)
                {
                    if(sendPlayer.world == player.world &&  //If in same world and
                       player != sendPlayer)                //not the movement change player itself
                        SendPlayerControllerMessage(sendPlayer, bs);
                }
            }
            else //Player not found
            {
                LogError() << "Cannot find player with given RakNet Address!";
            }
            break;
        }
        case PlayerControllerMessages::DELTA_UPDATE:
        {
            bool success;
            Id id(bsIn);
            ServerPlayer &player = gameServer.playerContainer.Get(id, success);

            if(success)
            {
                Position delta(bsIn);
                player.position += delta; //Do position update
                for(auto &sendPlayer : gameServer.playerContainer)
                {
                    if(sendPlayer.world == player.world &&  //If in same world and
                       sendPlayer != player)                //not the delta update player itself
                        SendPlayerControllerMessage(sendPlayer, bsIn); //Stream to all other players
                }
            }
            else
            {
                LogError() << "Cannot find player with given Id!";
            }
            break;
        }
        default:
        {
            LogWarn() << "PlayerController RakNet Message not handled! ID is: " << (int)command << ".";
        }
    }
}

void PlayerController::SpawnPlayer(ServerPlayer &player, ServerWorld &world)
{
    player.world = world;
    BitStream bs;

    BuildAddPlayerPacket(bs, player);

    for(auto &client : gameServer.clientContainer)
    {
        if(client.world == world) //Send AddPlayer if client is in same world
            SendPlayerControllerMessage(client, bs);
    }
}

void PlayerController::ClientEnteringWorld(ServerClient &client)
{
    for(auto &player : gameServer.playerContainer) //Send all player
    {
        if(player.world == client.world) //which are in the same world.
        {
            BitStream bs;
            BuildAddPlayerPacket(bs, player);
            SendPlayerControllerMessage(client, bs);
        }
    }
}

void PlayerController::ControlPlayer(const ServerClient &client, const ServerPlayer &player)
{
    BitStream bs;
    bs.Write((NetMessage) NetworkSystemMessages::PlayerController);
    bs.Write((NetMessage) PlayerControllerMessages::CONTROL_PLAYER);
    player.id.WriteStream(bs);
    SendPlayerControllerMessage(client, bs);
}

void PlayerController::SendPlayerControllerMessage(const RakNetGUID &dest, const BitStream &bsOut)
{
    gameServer.networkSystem.peerInterface->Send(
                &bsOut, LOW_PRIORITY, RELIABLE_ORDERED, PlayerControllerOrderingChannel, dest, false);
}

void PlayerController::BuildAddPlayerPacket(RakNet::BitStream &bs, const ServerPlayer &player)
{
    bs.Write((NetMessage) NetworkSystemMessages::PlayerController);
    bs.Write((NetMessage) PlayerControllerMessages::ADD_PLAYER);
    player.id.WriteStream(bs);
    player.position.WriteStream(bs);
    player.scale.WriteStream(bs);
    player.skills.WriteStream(bs);
    player.talents.WriteStream(bs);
}

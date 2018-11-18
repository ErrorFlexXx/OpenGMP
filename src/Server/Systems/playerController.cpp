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

ServerPlayer &PlayerController::GetNewPlayer(const ServerClient &client)
{
    ServerPlayer &player = gameServer.playerContainer.CreateEntity(client);
    player.client = client;
    return player;
}

void PlayerController::RemoveClientPlayer(ServerClient &client)
{
    for(auto &player : gameServer.playerContainer)
    {
        if(player.client == client)
            gameServer.playerController.RemovePlayer(player);
    }
}

void PlayerController::RemovePlayer(ServerPlayer &player)
{
    if(player.world != ServerWorld()) //Player spawned currently ?
        DespawnPlayer(player); //Then despawn it

    gameServer.playerContainer.Remove(player.id);
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
                Id id(bsIn);
                MovementChangeMessage::Unpack(bsIn, player);

                BitStream bs;
                MovementChangeMessage::Pack(bs, player);

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
        case PlayerControllerMessages::POSITION_UPDATE:
        {
            bool success;

            Id id(bsIn);
            ServerPlayer &player = gameServer.playerContainer.Get(id, success);

            if(success)
            {
                PositionUpdateMessage::Unpack(bsIn, player);
                BitStream bsOut;
                PositionUpdateMessage::Pack(bsOut, player);
                for(auto &sendPlayer : gameServer.playerContainer)
                {
                    if(sendPlayer.world == player.world) //If in same world and
                        SendPlayerControllerMessage(sendPlayer, bsOut); //Stream to all other players
                }
            }
            else
            {
                LogError() << "Cannot find player with given Id!";
            }
            break;
        }
        case PlayerControllerMessages::ENTERED_WORLD:
        {
            bool found;
            std::string ip = packet->systemAddress.ToString(false);
            ServerClient &client = gameServer.clientContainer.Get(packet->guid, found);
            if(found)
            {
                ClientEnteringWorld(client); //Player streaming basics.
                gameServer.scriptSystem.InvokeScriptFunction("ClientEnteredWorld", client); //Script functions
            }
            else
                LogWarn() << "Client EnteredWorld, but can't find him in clientContainer! IP: " << ip;
            break;
        }
        default:
        {
            LogWarn() << "PlayerController RakNet Message not handled! ID is: " << (int)command << ".";
        }
    }
}

void PlayerController::SpawnPlayer(ServerPlayer &player, const ServerWorld &world)
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

void PlayerController::DespawnPlayer(ServerPlayer &player)
{
    BitStream bs;
    bs.Write((NetMessage) NetworkSystemMessages::PlayerController);
    bs.Write((NetMessage)PlayerControllerMessages::REMOVE_PLAYER);
    player.id.WriteStream(bs);

    for(auto &sendPlayer : gameServer.playerContainer)
    {
        if(sendPlayer.world == player.world) //Send all players that are in same world
        {
            SendPlayerControllerMessage(sendPlayer, bs);
        }
    }
    player.world = ServerWorld(); //Reset world
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

void PlayerController::ControlPlayer(const ServerClient &client, ServerPlayer &player)
{
    player.client = client;
    BitStream bs;
    bs.Write((NetMessage) NetworkSystemMessages::PlayerController);
    bs.Write((NetMessage) PlayerControllerMessages::CONTROL_PLAYER);
    player.id.WriteStream(bs);
    SendPlayerControllerMessage(client, bs);
}

void PlayerController::StopControl(const ServerClient &client)
{
    BitStream bs;
    bs.Write((NetMessage) NetworkSystemMessages::PlayerController);
    bs.Write((NetMessage) PlayerControllerMessages::STOP_CONTROL);
    SendPlayerControllerMessage(client, bs);
}

void PlayerController::SendPlayerControllerMessage(const RakNetGUID &dest, const BitStream &bsOut)
{
    gameServer.networkSystem.peerInterface->Send(
                &bsOut, LOW_PRIORITY, RELIABLE_ORDERED, PlayerControllerOrderingChannel, dest, false);
}

void PlayerController::BuildAddPlayerPacket(RakNet::BitStream &bs, const ServerPlayer &player)
{
    AddPlayerMessage::Pack(bs, player);
}

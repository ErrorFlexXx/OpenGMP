#include "playerController.hpp"
#include <Client/gameClient.hpp>
#include <Client/Objects/clientPlayer.hpp>
#include <Client/Gothic/Objects/oCNpc.hpp>
#include <Client/Gothic/Objects/oCObjectFactory.hpp>
#include <Client/Gothic/cGameManager.hpp>
#include <Client/Gothic/Objects/oCGame.hpp>
#include <Client/Gothic/Objects/oCWorld.hpp>
#include <Client/Systems/inputSystem.hpp>
#include <Shared/Types/Messages/playerControllerMessages.hpp>
#include <Shared/Components/gameTime.hpp>
#include <BitStream.h>
#include <libintl.h>
#include <iostream>
#define _(string) gettext (string)

using namespace std;
using namespace RakNet;
using namespace OpenGMP;

PlayerController::PlayerController(GameClient &gameClient)
    : gameClient(gameClient)
    , active(false)
    , lastUpdate(0)
    , updateTimeSpan(200)
    , posAccuracy(0.1f)
    , angleAccuracy(0.1f)
    , activePlayer(gameClient.playerContainer.Get(0)) //We just need any player reference.
    , keyBindings({
        make_pair<PlayerMovement, list<VirtualKeys>>(PlayerMovement::Forward, { VirtualKeys::W, VirtualKeys::Up }),
        make_pair<PlayerMovement, list<VirtualKeys>>(PlayerMovement::Backward, { VirtualKeys::S, VirtualKeys::Down }),
        make_pair<PlayerMovement, list<VirtualKeys>>(PlayerMovement::Left, { VirtualKeys::A, VirtualKeys::Left }),
        make_pair<PlayerMovement, list<VirtualKeys>>(PlayerMovement::Right, { VirtualKeys::D, VirtualKeys::Right }),
        make_pair<PlayerMovement, list<VirtualKeys>>(PlayerMovement::TurnLeft, {VirtualKeys::Q}),
        make_pair<PlayerMovement, list<VirtualKeys>>(PlayerMovement::TurnRight,{ VirtualKeys::E }),
    })
{}

void PlayerController::Process(RakNet::Packet *packet)
{
    NetMessage command;
    BitStream bsIn(packet->data, packet->length, false);
    bsIn.IgnoreBytes(1); //PlayerController
    bsIn.Read(command); //Read command

    switch (command)
    {
    case PlayerControllerMessages::ADD_PLAYER:
    {
        Id id(bsIn);
        ClientPlayer &addPlayer = gameClient.playerContainer.Get(id);
        addPlayer.position.ReadStream(bsIn);
        addPlayer.scale.ReadStream(bsIn);
        addPlayer.skills.ReadStream(bsIn);
        addPlayer.talents.ReadStream(bsIn);
        
        addPlayer.gothicPlayer = oCObjectFactory::GetFactory()->CreateNpc();
        addPlayer.gothicPlayer->Setup(addPlayer);
        CGameManager::GetInstance()->GetGame()->GetWorld()->InsertVobInWorld(addPlayer.gothicPlayer);
        break;
    }
    case PlayerControllerMessages::REMOVE_PLAYER:
    {
        Id id(bsIn);
        ClientPlayer &removePlayer = gameClient.playerContainer.Get(id);
        if (removePlayer.gothicPlayer)
        {
            CGameManager::GetInstance()->GetGame()->GetWorld()->RemoveVob(removePlayer.gothicPlayer);
            removePlayer.gothicPlayer->Release();
            removePlayer.gothicPlayer = nullptr;
        }
    }
    case PlayerControllerMessages::CONTROL_PLAYER:
    {
        Id id(bsIn);
        ClientPlayer &controlPlayer = gameClient.playerContainer.Get(id);
        ControlPlayer(controlPlayer);
    }
    case PlayerControllerMessages::MOVEMENT_CHANGE:
    {
        Id id(bsIn);
        ClientPlayer &player = gameClient.playerContainer.Get(id);
        player.movement.ReadStream(bsIn);
        UpdatePlayerMovement(player);
        break;
    }
    case PlayerControllerMessages::DELTA_UPDATE:
    {
        Id id(bsIn);
        ClientPlayer &player = gameClient.playerContainer.Get(id);
        Position oldPos = player.position;
        
        //Receiving deltas
        float dx, dy, dz, dangle; //Delta values
        bsIn.Read(dx);
        bsIn.Read(dy);
        bsIn.Read(dz);
        bsIn.Read(dangle);

        //Update position
        player.position.x += dx;
        player.position.y += dy;
        player.position.z += dz;
        player.position.angle += dangle;

        //Check accuracy
        if (fabs(player.position.x - oldPos.x) >= posAccuracy ||
            fabs(player.position.y - oldPos.y) >= posAccuracy ||
            fabs(player.position.z - oldPos.z) >= posAccuracy ||
            fabs(player.position.angle - oldPos.angle) >= angleAccuracy)
        {   //Correct position / rotation
            player.gothicPlayer->SetPositionWorld(player.position);
            player.gothicPlayer->ResetXZRotationsWorld(); //Reset azi + elev
            player.gothicPlayer->RotateWorldY(player.position.angle); //Set azi
        }
        break;
    }
    default:
    {
#ifdef DBG_NETWORK
        gameClient.menuSystem.ShowNotification(
            20,
            std::string(_("PlayerController RakNet Message not handled! ID is")).append(": ").append(std::to_string((int)command)).append("!"),
            Color(255, 0, 0, 255),
            10
        );
#endif
        break;
    }
    }
}

//Test
void PlayerController::ControlCurrentPlayer()
{
    activePlayer.gothicPlayer = oCNpc::GetHero();
    activePlayer.movement = PlayerMovement::Stand;
    active = true;
}

void PlayerController::ControlPlayer(ClientPlayer &player)
{
    activePlayer = player;
    activePlayer.movement = PlayerMovement::Stand;
    
    if (player.gothicPlayer)
    {
        oCNpc::SetHero(player.gothicPlayer);
        active = true;
    }
}

void PlayerController::StopControl()
{
    active = false;
    if (activePlayer.movement != PlayerMovement::Stand)
    {
        ; //Send server stop control
    }
}

int PlayerController::BindingPressed(PlayerMovement move)
{
    list<VirtualKeys> keys = keyBindings[move]; //Get bound keys
    for (VirtualKeys &key : keys) //Check if any key is pressed
    {
        if (gameClient.inputSystem.IsPressed(key))
            return true; //Key pressed.
    }

    return false; //No key pressed
}

void PlayerController::Update()
{
    if (active)
    {
        if (activePlayer.movement == PlayerMovement::Stand)
        {
            if (BindingPressed(PlayerMovement::Forward))
            {
                activePlayer.movement = PlayerMovement::Forward;
                activePlayer.gothicPlayer->GetAnictrl()->_Forward();
            }
            else if (BindingPressed(PlayerMovement::Backward))
            {
                activePlayer.movement = PlayerMovement::Backward;
                activePlayer.gothicPlayer->GetAnictrl()->_Backward();
            }
            else if (BindingPressed(PlayerMovement::Left))
            {
                activePlayer.movement = PlayerMovement::Left;
                activePlayer.gothicPlayer->GetAnictrl()->StrafeLeft();
            }
            else if (BindingPressed(PlayerMovement::Right))
            {
                activePlayer.movement = PlayerMovement::Right;
                activePlayer.gothicPlayer->GetAnictrl()->StrafeRight();
            }
            else if (BindingPressed(PlayerMovement::TurnLeft))
            {
                activePlayer.movement = PlayerMovement::TurnLeft;
                activePlayer.gothicPlayer->GetAnictrl()->Turn(-1.f, true);
            } 
            else if (BindingPressed(PlayerMovement::TurnRight))
            {
                activePlayer.movement = PlayerMovement::TurnRight;
                activePlayer.gothicPlayer->GetAnictrl()->Turn(1.f, true);
            }
        }
        else //Stop running action ?
        {
            PlayerMovement currentMove = activePlayer.movement;
            if (!BindingPressed(currentMove))
            {
                activePlayer.movement = PlayerMovement::Stand;
                activePlayer.gothicPlayer->GetAnictrl()->StopTurnAnis();
                activePlayer.gothicPlayer->GetAnictrl()->_Stand();
                activePlayer.gothicPlayer->GetAnictrl()->SearchStandAni();
            }
            else //Movement action running
            {
                if (BindingPressed(PlayerMovement::TurnLeft))
                {
                    activePlayer.gothicPlayer->GetAnictrl()->Turn(-1.f, false);
                }
                else if (BindingPressed(PlayerMovement::TurnRight))
                {
                    activePlayer.gothicPlayer->GetAnictrl()->Turn(1.f, false);
                }
                Stream(GameTime::GetTicks());                
            }
        }
    }
}

void PlayerController::UpdatePlayerMovement(ClientPlayer &player)
{
    if (player.movement.movementState == PlayerMovement::Stand)
    {
        player.gothicPlayer->GetAnictrl()->StopTurnAnis();
        player.gothicPlayer->GetAnictrl()->_Stand();
        player.gothicPlayer->GetAnictrl()->SearchStandAni();
    }
    else if (player.movement.movementState == PlayerMovement::Forward)
    {
        player.gothicPlayer->GetAnictrl()->_Forward();
    }
    else if (player.movement.movementState == PlayerMovement::Backward)
    {
        player.gothicPlayer->GetAnictrl()->_Backward();
    }
    else if (player.movement.movementState == PlayerMovement::Left)
    {
        player.gothicPlayer->GetAnictrl()->StrafeLeft();
    }
    else if (player.movement.movementState == PlayerMovement::Right)
    {
        player.gothicPlayer->GetAnictrl()->StrafeRight();
    }
    else if (player.movement.movementState == PlayerMovement::TurnLeft)
    {
        player.gothicPlayer->GetAnictrl()->Turn(-1.f, true);
    }
    else if (player.movement.movementState == PlayerMovement::TurnRight)
    {
        player.gothicPlayer->GetAnictrl()->Turn(1.f, true);
    }
}

void PlayerController::SendMovementStateChange()
{
    BitStream bsOut;
    bsOut.Write((NetMessage)NetworkSystemMessages::PlayerController);
    bsOut.Write((NetMessage)PlayerControllerMessages::MOVEMENT_CHANGE);
    bsOut.Write(activePlayer.movement.movementState);
    SendPlayerControllerPacket(bsOut);
}

void PlayerController::Stream(unsigned long long now)
{
    if (lastUpdate + updateTimeSpan < now) //Update required ?
    {
        float azi, elev;
        zVEC3 pos = activePlayer.gothicPlayer->GetPositionWorld();
        activePlayer.gothicPlayer->GetAngles(pos, azi, elev);

        zVEC3 deltaPos = pos - activePlayer.position;
        float deltaAngle = azi - activePlayer.position.angle;

        BitStream bsOut;
        bsOut.Write((NetMessage)NetworkSystemMessages::PlayerController);
        bsOut.Write((NetMessage)PlayerControllerMessages::DELTA_UPDATE);
        activePlayer.id.WriteStream(bsOut);
        bsOut.Write(deltaPos.x);
        bsOut.Write(deltaPos.y);
        bsOut.Write(deltaPos.z);
        bsOut.Write(deltaAngle);
        SendPlayerControllerPacket(bsOut);

        lastUpdate = now;
    }
}

void PlayerController::SendPlayerControllerPacket(const RakNet::BitStream &bsOut)
{
    gameClient.networkSystem.peerInterface->Send(
        &bsOut, LOW_PRIORITY, RELIABLE_ORDERED, PlayerControllerOrderingChannel, gameClient.networkSystem.serverAddress, false);
}

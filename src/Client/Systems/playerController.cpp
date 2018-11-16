#include "playerController.hpp"
#include <Client/gameClient.hpp>
#include <Client/Objects/clientPlayer.hpp>
#include <Client/Gothic/Objects/oCNpc.hpp>
#include <Client/Gothic/Objects/oCObjectFactory.hpp>
#include <Client/Gothic/cGameManager.hpp>
#include <Client/Gothic/Objects/oCGame.hpp>
#include <Client/Gothic/Objects/oCWorld.hpp>
#include <Client/Gothic/Classes/zCParser.hpp>
#include <Client/Gothic/Classes/zCAICamera.hpp>
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
    , updateTimeSpan(50)
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
        addPlayer.visual.ReadStream(bsIn);
        addPlayer.attributes.ReadStream(bsIn);
        addPlayer.gothicPlayer = oCObjectFactory::GetFactory()->CreateNpc(/*zCParser::GetParser()->GetIndex("PC_Hero")*/);
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
        std::cout << "Remove_Player" << std::endl;
        break;
    }
    case PlayerControllerMessages::CONTROL_PLAYER:
    {
        Id id(bsIn);
        ClientPlayer &controlPlayer = gameClient.playerContainer.Get(id);
        ControlPlayer(controlPlayer);
        std::cout << "Control_Player" << std::endl;
        break;
    }
    case PlayerControllerMessages::STOP_CONTROL:
    {
        StopControl();
        std::cout << "StopControl_Player" << std::endl;
        break;
    }
    case PlayerControllerMessages::MOVEMENT_CHANGE:
    {
        Id id(bsIn);
        ClientPlayer &player = gameClient.playerContainer.Get(id);
        player.movement.ReadStream(bsIn);
        UpdatePlayerMovement(player);
        std::cout << "Movement Change" << std::endl;
        break;
    }
    case PlayerControllerMessages::POSITION_UPDATE:
    {
        Id id(bsIn);
        ClientPlayer &player = gameClient.playerContainer.Get(id);
        
        player.position.ReadStream(bsIn);

        //Check accuracy
        player.gothicPlayer->SetPositionWorld(player.position);
        player.gothicPlayer->ResetXZRotationsWorld(); //Reset azi + elev
        player.gothicPlayer->RotateWorldY(player.position.angle); //Set azi
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
        //player.gothicPlayer->SetAsPlayer();
        oCNpc::SetHero(player.gothicPlayer);
        oCGame *game = CGameManager::GetInstance()->GetGame();
        zCAICamera *aiCam = game->GetCameraAI();
        zCVob *camVob = game->GetCamVob();
        aiCam->ClearTargetList();
        aiCam->SetTarget(player.gothicPlayer);
        aiCam->ReceiveMsg(zPLAYER_BEAMED);
        camVob->SetPositionWorld(player.gothicPlayer->GetPositionWorld() - player.gothicPlayer->GetAtVectorWorld() * 200);
        camVob->SetHeadingAtWorld(player.gothicPlayer->GetAtVectorWorld());
        active = true;
    }
}

void PlayerController::StopControl()
{
    active = false;
    if (activePlayer.movement != PlayerMovement::Stand)
    {
        activePlayer.movement = PlayerMovement::Stand;
        SendMovementStateChange();
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
            bool movementChanged = true;

            if (gameClient.inputSystem.IsPressed(VirtualKeys::P))
            {
                if (oCNpc::GetHero())
                {
                    float x, y, z;
                    oCNpc::GetHero()->GetPosition(x, y, z);
                    std::cout << "Pos: " << x << " " << y << " " << z << std::endl;
                }
            }

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
            else //No key binding fired -> movement not changed.
            {
                movementChanged = false;
            }
            if (movementChanged)
                SendMovementStateChange();
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
                SendMovementStateChange();
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

void PlayerController::SendEnteredWorld()
{
    BitStream bsOut;
    bsOut.Write((NetMessage)NetworkSystemMessages::PlayerController);
    bsOut.Write((NetMessage)PlayerControllerMessages::ENTERED_WORLD);
    SendPlayerControllerPacket(bsOut);
}

void PlayerController::Stream(unsigned long long now)
{
    if (lastUpdate + updateTimeSpan < now) //Update required ?
    {
        float azi, elev;
        zVEC3 pos = activePlayer.gothicPlayer->GetPositionWorld();
        activePlayer.gothicPlayer->GetAngles(pos, azi, elev);
        
        Position newPosition(pos.x, pos.y, pos.z, azi);

        BitStream bsOut;
        bsOut.Write((NetMessage)NetworkSystemMessages::PlayerController);
        bsOut.Write((NetMessage)PlayerControllerMessages::POSITION_UPDATE);
        activePlayer.id.WriteStream(bsOut);
        newPosition.WriteStream(bsOut);

        SendPlayerControllerPacket(bsOut);
        lastUpdate = now;
    }
}

void PlayerController::SendPlayerControllerPacket(const RakNet::BitStream &bsOut)
{
    gameClient.networkSystem.peerInterface->Send(
        &bsOut, LOW_PRIORITY, RELIABLE_ORDERED, PlayerControllerOrderingChannel, gameClient.networkSystem.serverAddress, false);
}

#include "playerController.hpp"
#include <Client/gameClient.hpp>
#include <Client/Objects/clientPlayer.hpp>
#include <Client/Gothic/Objects/oCNpc.hpp>
#include <Client/Systems/inputSystem.hpp>

using namespace std;
using namespace OpenGMP;

PlayerController::PlayerController(GameClient &gameClient)
    : gameClient(gameClient)
    , active(false)
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
            } else if (BindingPressed(PlayerMovement::TurnRight))
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
            else if (BindingPressed(PlayerMovement::TurnLeft))
            {
                activePlayer.gothicPlayer->GetAnictrl()->Turn(-1.f, false);
            }
            else if (BindingPressed(PlayerMovement::TurnRight))
            {
                activePlayer.gothicPlayer->GetAnictrl()->Turn(1.f, false);
            }
        }
    }
}

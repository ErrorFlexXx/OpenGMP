#pragma once

#include <Client/Types/virtualKeys.hpp>
#include <Shared/Components/playerMovement.hpp>
#include <map>
#include <list>

namespace OpenGMP
{
    class GameClient;
    class ClientPlayer;

    class PlayerController
    {
    public:
        PlayerController(GameClient &gameClient);

        void ControlCurrentPlayer();
        void ControlPlayer(ClientPlayer &player);
        void StopControl();
        void Update();
        int BindingPressed(PlayerMovement move);

        GameClient &gameClient; //!< Game client reference this system works for.
        bool active;    //!< Is this controller currently activated ?
        ClientPlayer &activePlayer; //!< Player that is currently beeing controlled.
        std::map<PlayerMovement, std::list<VirtualKeys>> keyBindings;
    };
}
#pragma once

#include <Client/Types/virtualKeys.hpp>
#include <Shared/Components/playerMovement.hpp>
#include <map>
#include <list>

//Forward declarations:
namespace RakNet
{
    struct Packet;
}

namespace OpenGMP
{
    class GameClient;
    class ClientPlayer;

    class PlayerController
    {
    public:
        PlayerController(GameClient &gameClient);

        void Process(RakNet::Packet *packet);
        void SendPlayerControllerPacket(const RakNet::BitStream &bsOut);
        void ControlCurrentPlayer();
        void ControlPlayer(ClientPlayer &player);
        void StopControl();
        void Update();
        void UpdatePlayerMovement(ClientPlayer &player);
        void SendMovementStateChange();
        void Stream(unsigned long long now);
        int BindingPressed(PlayerMovement move);

        GameClient &gameClient; //!< Game client reference this system works for.
        bool active;    //!< Is this controller currently activated ?
        unsigned long long lastUpdate; //!< Time of last delta update sending.
        unsigned long long updateTimeSpan; //!< Time between delta movement updates.
        float posAccuracy; //!< Accuracy of positioning (pos)
        float angleAccuracy; //!< Accuracy of positioning (angle)
        ClientPlayer &activePlayer; //!< Player that is currently beeing controlled.
        std::map<PlayerMovement, std::list<VirtualKeys>> keyBindings;
    };
}
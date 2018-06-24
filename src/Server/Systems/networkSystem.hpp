#pragma once

#include <RakPeerInterface.h>

//Forward declaration:
class GameServer;

namespace RakNet
{
    class RakPeerInterface;
    class SocketDescriptor;
    class Packet;
}

class NetworkSystem
{
public:
    NetworkSystem(GameServer &gameServer, const int &gameport, const int &playerslots);

    ~NetworkSystem();

    /**
     * @brief Startup, opens a listening socket
     * @return true, if startup was successfull
     */
    bool Startup();

    /**
     * @brief Shutdown stops the network interface
     */
    void Shutdown();

    /**
     * @brief Update
     * @return true if there was something to do, false otherwise
     */
    bool Update();

private:
    GameServer &gameServer;
    int gameport;     //!< UDP RakNet listening port.
    int playerslots;  //!< Currently accepted simulateously active connected players.
    RakNet::RakPeerInterface *peerInterface;      //!< RakNet PeerInterface object.
    RakNet::SocketDescriptor socketDescriptor;    //!< Socket descriptor holding maxConns.
};

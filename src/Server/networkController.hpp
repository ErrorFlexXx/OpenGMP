#pragma once

#include <vector>
#include <RakPeerInterface.h>

//Forward declaration:
namespace RakNet
{
    class RakPeerInterface;
    class SocketDescriptor;
    class Packet;
}

/**
 * @brief The NetworkController classis responsible for collection incoming packets.
 */
class NetworkController
{
public:
    /**
     * @brief NetworkController constructs a Network Controller object.
     * @param gameport the server is listening on.
     * @param playerslots max. accepted sim. active connected player.
     */
    NetworkController(const int gameport, const int playerslots);

    /**
     * @brief ~NetworkController stops the listening socket.
     */
    ~NetworkController();

    /**
     * @brief Exec receives packages.
     */
    void Exec();

protected:
    /**
     * @brief startup -- Initializes and start the server socket.
     * @return true if successfull, false otherwise
     */
    virtual bool Startup();

private:
    int m_gameport;     //!< UDP RakNet listening port.
    int m_playerslots;  //!< Currently accepted simulateously active connected players.
    RakNet::RakPeerInterface *m_peerInterface;      //!< RakNet PeerInterface object.
    RakNet::SocketDescriptor m_socketDescriptor;    //!< Socket descriptor holding maxConns.

};

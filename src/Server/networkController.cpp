#include "networkController.hpp"
#include <utils/logger.h>
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>
#include <RakNetTypes.h>
#include "gameServer.hpp"

using namespace RakNet;

NetworkController::NetworkController(const int gameport, const int playerslots)
    : m_gameport(gameport)
    , m_playerslots(playerslots)
    , m_peerInterface(RakPeerInterface::GetInstance())
    , m_socketDescriptor(gameport, 0)
{
}

NetworkController::~NetworkController()
{
    LogInfo() << "NetworkController shutdown ok.";
    RakPeerInterface::DestroyInstance(m_peerInterface);
}

void NetworkController::Exec()
{
    Packet *packet;

    for (packet = m_peerInterface->Receive(); //Initially fetch packet
         packet; //Loop while there is a receipt package
         m_peerInterface->DeallocatePacket(packet), packet = m_peerInterface->Receive()) //Dealloc packet and fetch next
    {
        ;
    }
}

bool NetworkController::Startup()
{
    if(!m_peerInterface)
    {
        return false;
    }

    m_peerInterface->SetMaximumIncomingConnections(m_playerslots);
    StartupResult res = m_peerInterface->Startup(2 * m_playerslots, &m_socketDescriptor, 1);
    if(res == RAKNET_STARTED)
    {
        LogInfo() << "NetworkController started! Listening on port " << m_gameport << " with " << m_playerslots << " slots.";
        return true;
    }
    else if(res == SOCKET_PORT_ALREADY_IN_USE)
    {
        LogError() << "Port " << m_gameport << " is already in use! Can't open server socket!";
        return false;
    }
    else
        LogError() << "Unknown RakNet error. Startup failed!";
    return false;
}



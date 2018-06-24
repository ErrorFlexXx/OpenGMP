#include "networkSystem.hpp"
#include "../gameServer.hpp"
#include <Shared/Types/Messages/networkSystemMessages.hpp>
#include <utils/logger.h>

using namespace RakNet;
using namespace OpenGMP::Types;

NetworkSystem::NetworkSystem(GameServer &gameServer, const int &gameport, const int &playerslots)
    : gameServer(gameServer)
    , gameport(gameport)
    , playerslots(playerslots)
    , peerInterface(RakPeerInterface::GetInstance())
    , socketDescriptor(gameport, 0)
{}

NetworkSystem::~NetworkSystem()
{
    LogInfo() << "NetworkSystem shutting down.";
    peerInterface->IsActive();
    Shutdown();
}

bool NetworkSystem::Startup()
{
    if(!peerInterface)
    {
        return false;
    }

    peerInterface->SetMaximumIncomingConnections(playerslots);
    StartupResult res = peerInterface->Startup(2 * playerslots, &socketDescriptor, 1);
    if(res == RAKNET_STARTED)
    {
        LogInfo() << "NetworkController started! Listening on port " << gameport << " with " << playerslots << " slots.";
        return true;
    }
    else if(res == SOCKET_PORT_ALREADY_IN_USE)
    {
        LogError() << "Port " << gameport << " is already in use! Can't open server socket!";
        return false;
    }
    else
        LogError() << "Unknown RakNet error. Startup failed!";
    return false;
}

void NetworkSystem::Shutdown()
{
    peerInterface->Shutdown(1000);
}

bool NetworkSystem::Update()
{
    Packet *packet;
    bool packetReceipt = false;

    while(packet = peerInterface->Receive())
    {
        packetReceipt = true;
        if(0 < packet->length)
        {
            switch(packet->data[0])
            {
                case NetworkSystemMessages::LoginSystem:
                {
                    gameServer.loginSystem.Process(packet);
                    break;
                }
            }
        }
        peerInterface->DeallocatePacket(packet);
    }
    return packetReceipt;
}

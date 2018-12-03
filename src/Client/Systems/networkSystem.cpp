#include "networkSystem.hpp"
#include "../gameClient.hpp"
#include <BitStream.h>
#include <GetTime.h>
#include <MessageIdentifiers.h>
#include <Shared/Types/constants.hpp>
#include <Shared/Types/color.hpp>
#include <Shared/Types/Messages/networkSystemMessages.hpp>
#include <Shared/Types/Messages/menuSystemMessages.hpp>
#include <NativeFeatureIncludes.h>
#include <SecureHandshake.h>
#include <iostream>
#include <libintl.h>
#define _(string) gettext (string)

#if LIBCAT_SECURITY!=1
#error "Define LIBCAT_SECURITY 1 in lib/RakNet/Source/NativeFeatureIncludesOverrides.h to enable Encryption"
#endif

using namespace OpenGMP;
using namespace RakNet;

bool NetworkSystem::started = false;

NetworkSystem::NetworkSystem(GameClient &gameClient)
    : gameClient(gameClient)
    , ping(0)
    , peerInterface(RakPeerInterface::GetInstance())
{}

bool NetworkSystem::Startup()
{
    if (started == false) //Don't start twice
    {
        started = true; //Network system running now.
        if (!gameClient.webStatusSystem.Startup(server))
        {
            gameClient.menuSystem.ShowNotification(
                20,
                std::string(_("Network cannot be started! WebStatusSystem Startup failed!")),
                Color(255, 0, 0, 255)
            );
            StartupFailed();
            return false;
        }
        if (!gameClient.webStatusSystem.GetConnectData(server))
        {
            gameClient.menuSystem.ShowNotification(
                20,
                std::string(_("Network Start failed! Server unreachable!")),
                Color(255, 0, 0, 255)
            );
            StartupFailed();
            return false;
        }
        StartupResult result = peerInterface->Startup(1, &socketDescriptor, 1);
        if (result != RAKNET_STARTED)
        {            
            gameClient.menuSystem.ShowNotification(
                20,
                std::string(_("Network cannot be started!")).append(" (RakNet StartupResult: ").append(std::to_string(result)).append(")."),
                Color(255, 0, 0, 255)
            );
            StartupFailed();
            return false;
        }
        //Optional password:
        const char *password = nullptr;
        if (server.password.length() > 0) //Use password ?
            password = server.password.c_str();
        //Optional public key:
        PublicKey *pubKey = nullptr;
        if (server.publicKey.size() > 0) //Use public key ?
        {
            pubKey = &pk;
            pubKey->remoteServerPublicKey = server.publicKey.data();
            pubKey->publicKeyMode = PKM_USE_KNOWN_PUBLIC_KEY;
        }
        //Do connect
        ConnectionAttemptResult conResult = peerInterface->Connect(server.hostname.c_str(), server.gamePort, password, server.password.length(), pubKey);
        if (conResult != CONNECTION_ATTEMPT_STARTED)
        {
            gameClient.menuSystem.ShowNotification(
                20,
                std::string(_("Connection failed!")).append(" (RakNet ConnectionAttemptResult: ").append(std::to_string(conResult)).append(")."),
                Color(255, 0, 0, 255)
            );
            StartupFailed();
            return false;
        }
        gameClient.menuSystem.ShowNotification(
            20,
            std::string(_("Connecting to server")).append(" (Host: ").append(server.hostname).append(" Port: ").append(std::to_string(server.gamePort)).append(")."),
            Color(255, 255, 255, 255)
        );
        return true;
    }
    return false;
}

void NetworkSystem::Shutdown()
{
    started = false; //Network system no longer running.
    peerInterface->Shutdown(1000);
}

void NetworkSystem::Update()
{
    for (RakNet::Packet *packet = peerInterface->Receive();
         packet;
         peerInterface->DeallocatePacket(packet), packet = peerInterface->Receive())
    {
        if (0 < packet->length)
        {
            NetMessage command = packet->data[0];

            switch (command)
            {
            case NetworkSystemMessages::LoginSystem:
            case ID_CONNECTION_LOST:
            case ID_CONNECTION_REQUEST_ACCEPTED:
            case ID_CONNECTION_ATTEMPT_FAILED:
            case ID_DISCONNECTION_NOTIFICATION:
            {
                gameClient.loginSystem.Process(packet);
                break;
            }
            case ID_UNCONNECTED_PONG:
            {
                TimeMS currentTime = RakNet::GetTimeMS();
                TimeMS time;

                BitStream bsIn(packet->data, packet->length, false);
                bsIn.Read(time);
                ping = currentTime - time;

                RakNet::BitStream bsOut;
                bsOut.Write((NetMessage) NetworkSystemMessages::Ping);
                bsOut.Write(ping); //ping

                peerInterface->Send(&bsOut, PacketPriority::LOW_PRIORITY, PacketReliability::UNRELIABLE, 0, serverAddress, false);
                peerInterface->DeallocatePacket(packet);
                std::cout << "Send ping with value " << ping << std::endl;
                break;
            }
            case NetworkSystemMessages::MenuSystem:
            {
                gameClient.menuSystem.Process(packet);
                break;
            }
            case NetworkSystemMessages::WorldSystem:
            {
                gameClient.worldSystem.Process(packet);
                break;
            }
            case NetworkSystemMessages::PlayerController:
            {
                gameClient.playerController.Process(packet);
                break;
            }
            default:
            {
#ifdef DBG_NETWORK
                gameClient.menuSystem.ShowNotification(
                    20,
                    std::string(_("NetworkSystem RakNet Message not handled! ID is")).append(": ").append(std::to_string((int)command)).append("!"),
                    Color(255, 0, 0, 255),
                    10
                );
#endif
                break;
            }
            }
        }
    }
}

void NetworkSystem::StartupFailed()
{
    started = false; //NetworkSystem no longer running.
}
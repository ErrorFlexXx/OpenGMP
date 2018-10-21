#include "networkSystem.hpp"
#include "../gameClient.hpp"
#include <BitStream.h>
#include <GetTime.h>
#include <MessageIdentifiers.h>
#include <Shared/Components/color.hpp>
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
using namespace OpenGMP::Types;
using namespace OpenGMP::Systems;
using namespace OpenGMP::Components;
using namespace RakNet;

bool NetworkSystem::started = false;
char NetworkSystem::public_key[] = { (char)0x04, (char)0xBB, (char)0x07, (char)0xEC, (char)0x1B, (char)0x19, (char)0x21, (char)0x7A, (char)0xDE, (char)0x0F, (char)0xF8, (char)0xC5, (char)0x89, (char)0x61, (char)0x71, (char)0x94, (char)0xA5, (char)0x22, (char)0x2C, (char)0x4A, (char)0xB1, (char)0x1C, (char)0x1E, (char)0xD2, (char)0x1D, (char)0x03, (char)0x17, (char)0x89, (char)0x5B, (char)0xEF, (char)0x6B, (char)0x06, (char)0x1A, (char)0x3B, (char)0xF7, (char)0xD4, (char)0x78, (char)0xC8, (char)0xE9, (char)0x4E, (char)0x8B, (char)0x3B, (char)0x0E, (char)0xB8, (char)0xE0, (char)0x0D, (char)0x70, (char)0x6B, (char)0xB7, (char)0x71, (char)0x46, (char)0xD5, (char)0x42, (char)0xB6, (char)0xCB, (char)0xAB, (char)0x74, (char)0x3A, (char)0x06, (char)0x3F, (char)0x55, (char)0xA6, (char)0xAD, (char)0x13 };

NetworkSystem::NetworkSystem(GameClient &gameClient)
    : gameClient(gameClient)
    , hostname("")
    , port(0)
    , ping(0)
    , peerInterface(RakPeerInterface::GetInstance())
{
    pk.remoteServerPublicKey = public_key;
    pk.publicKeyMode = PKM_USE_KNOWN_PUBLIC_KEY;
}

bool NetworkSystem::Startup()
{
    if (started == false) //Don't start twice
    {
        started = true; //Network system running now.
        gameClient.ReadEnvironmentConnectData(); //Update connect data
        hostname = GameClient::serverName;  //Use hostname from GameClient
        port = GameClient::serverPort;      //Use port from GameClient

        StartupResult result = peerInterface->Startup(1, &socketDescriptor, 1);
        if (result != RAKNET_STARTED)
        {
            std::cout << "peerInterface Startup failed with result: " << result << std::endl;
            StartupFailed();
            return false;
        }

        ConnectionAttemptResult conResult = peerInterface->Connect(hostname.c_str(), port, 0, 0, &pk);
        if (conResult != CONNECTION_ATTEMPT_STARTED)
        {
            std::cout << "peerInterface connect failed with result: " << conResult << std::endl;
            StartupFailed();
            return false;
        }
        gameClient.menuSystem.ShowNotification(
            20,
            std::string(_("Connecting to server (Host: ")).append(gameClient.serverName).append(_(" Port: ")).append(std::to_string(gameClient.serverPort)).append(")."),
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
            switch (packet->data[0])
            {
            case NetworkSystemMessages::LoginSystem:
            case ID_CONNECTION_LOST:
            case ID_CONNECTION_REQUEST_ACCEPTED:
            case ID_CONNECTION_ATTEMPT_FAILED:
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
                bsOut.Write(NetworkSystemMessages::ClientPing);
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
            default:
            {
                std::cout << "Got unhandled package with id: " << (int)packet->data[0] << std::endl;
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
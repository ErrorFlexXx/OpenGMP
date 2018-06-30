#include "networkSystem.hpp"
#include <RakSleep.h>
#include <BitStream.h>
#include <GetTime.h>
#include <MessageIdentifiers.h>
#include <Shared/Types/Messages/networkSystemMessages.hpp>
#include <NativeFeatureIncludes.h>
#include <SecureHandshake.h>
#include <iostream>

#if LIBCAT_SECURITY!=1
#error "Define LIBCAT_SECURITY 1 in lib/RakNet/Source/NativeFeatureIncludesOverrides.h to enable Encryption"
#endif

using namespace OpenGMP::Types;
using namespace OpenGMP::Systems;
using namespace RakNet;

bool NetworkSystem::runNetwork = false;
bool NetworkSystem::started = false;
char NetworkSystem::public_key[] = { (char)0xE3, (char)0x1C, (char)0x4C, (char)0xC4, (char)0x38, (char)0x52, (char)0x32, (char)0x55, (char)0x22, (char)0x51, (char)0xA9, (char)0x6B, (char)0x82, (char)0x96, (char)0xE3, (char)0xEB, (char)0x82, (char)0x92, (char)0xF4, (char)0xAA, (char)0x37, (char)0x44, (char)0x39, (char)0xF4, (char)0x08, (char)0xA6, (char)0x4D, (char)0xE1, (char)0x16, (char)0xC4, (char)0x64, (char)0xD1, (char)0x04, (char)0x17, (char)0xB5, (char)0xF6, (char)0x11, (char)0xBE, (char)0xAE, (char)0x4E, (char)0x0C, (char)0xAE, (char)0xEC, (char)0x2B, (char)0xE7, (char)0xF5, (char)0x6B, (char)0xA3, (char)0x65, (char)0x42, (char)0xA0, (char)0x5F, (char)0x03, (char)0xC4, (char)0x80, (char)0x68, (char)0x25, (char)0xD9, (char)0xC7, (char)0x93, (char)0x91, (char)0x0F, (char)0x9A, (char)0x1F };

NetworkSystem::NetworkSystem()
    : NetworkSystem("127.0.0.1", 1760)
{}

NetworkSystem::NetworkSystem(const std::string &hostname, unsigned short port)
    : hostname(hostname)
    , port(port)
    , ping(0)
    , peerInterface(RakPeerInterface::GetInstance())
{
    pk.remoteServerPublicKey = public_key;
    pk.publicKeyMode = PKM_USE_KNOWN_PUBLIC_KEY;
}

bool NetworkSystem::Startup()
{
    if (started == false) //Don't start multiple threads
    {
        runNetwork = true;
        started = true;
        std::thread networkThread(&NetworkSystem::NetworkLoop, this);
        networkThread.detach(); //Threads ran independently. std::thread can be destroyed now.
        return true;
    }
    return false;
}

void NetworkSystem::Shutdown()
{
    runNetwork = false;
}

void NetworkSystem::NetworkLoop()
{
    bool idle = true;
    
    StartupResult result = peerInterface->Startup(1, &socketDescriptor, 1);
    if (result != RAKNET_STARTED)
    {
        std::cout << "peerInterface Startup failed with result: " << result << std::endl;
        StartupFailed();
        return;
    }

    ConnectionAttemptResult conResult = peerInterface->Connect(hostname.c_str(), port, 0, 0, &pk);
    if (conResult != CONNECTION_ATTEMPT_STARTED)
    {
        std::cout << "peerInterface connect failed with result: " << conResult << std::endl;
        StartupFailed();
        return;
    }

    while (runNetwork)
    {
        idle = true;
        Packet *packet = peerInterface->Receive();
        if (packet)
        {
            idle = false;
            std::cout << "Got Package with size: " << packet->length << " id: " << (int)packet->data[0] << std::endl;
            if (0 < packet->length)
            {
                switch (packet->data[0])
                {
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
                case ID_CONNECTION_REQUEST_ACCEPTED:
                {
                    serverAddress = packet->systemAddress;
                    peerInterface->DeallocatePacket(packet);
                    std::cout << "Successfully connected!" << std::endl;
                    break;
                }
                case ID_CONNECTION_ATTEMPT_FAILED:
                {
                    peerInterface->DeallocatePacket(packet);
                    std::cout << "Can't connect to server!" << std::endl;
                    break;
                }
                default:
                {
                    std::cout << "Unknown response: " << (int)packet->data[0] << std::endl;
                    peerInterface->DeallocatePacket(packet);
                    break;
                }
                }
            }
        }
        
        if (idle)
            RakSleep(1);
    }

    //Exiting...    
    started = false; //New thread possible.
    peerInterface->Shutdown(1000);
}

void NetworkSystem::StartupFailed()
{
    started = false;
}
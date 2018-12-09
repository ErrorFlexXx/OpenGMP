#include "networkSystem.hpp"
#include "../gameServer.hpp"
#include "../Systems/netDynamicContainer.hpp"
#include <Shared/Types/Messages/networkSystemMessages.hpp>
#include <utils/logger.h>
#include <fstream>
#include <iostream>

#if LIBCAT_SECURITY!=1
#error "Define LIBCAT_SECURITY 1 in lib/RakNet/Source/NativeFeatureIncludesOverrides.h to enable Encryption"
#endif

using namespace RakNet;
using namespace OpenGMP;

NetworkSystem::NetworkSystem(GameServer &gameServer, const int &gameport, const int &playerslots,
                             const std::string &keyDirectory, const std::string &publicKeyfileName, const std::string &privateKeyfileName)
    : gameServer(gameServer)
    , gameport(gameport)
    , playerslots(playerslots)
    , peerInterface(RakPeerInterface::GetInstance())
    , socketDescriptor(gameport, 0)
    , keyDirectory(keyDirectory)
    , publicKeyfileName(publicKeyfileName)
    , privateKeyfileName(privateKeyfileName)
{}

NetworkSystem::~NetworkSystem()
{
    LogInfo() << "NetworkSystem shutting down.";
    peerInterface->IsActive();
    Shutdown();
}

bool NetworkSystem::ReadEncryptionKeys()
{
    std::string pubKeyFilepath = std::string(keyDirectory).append("/").append(publicKeyfileName);
    std::string privKeyFilepath = std::string(keyDirectory).append("/").append(privateKeyfileName);
    size_t expectedPubKeySize = cat::EasyHandshake::PUBLIC_KEY_BYTES;
    size_t expectedPrivKeySize = cat::EasyHandshake::PRIVATE_KEY_BYTES;

    std::ifstream fp;
    fp.open(pubKeyFilepath.c_str(), std::ios::in | std::ios::binary);
    if(!fp.is_open())
    {
        LogWarn() << "Cannot open public key file \"" << pubKeyFilepath << "\" for read! Creating new keys...";
        if(0 != GenKeys(keyDirectory, publicKeyfileName, privateKeyfileName))
        {
            LogError() << "Cannot create keys! Please check or explicitly set the key path! Make sure, it is writable!";
            return false;
        }
        fp.open(pubKeyFilepath.c_str(), std::ios::in | std::ios::binary);
        if(!fp.is_open())
        {
            LogError() << "Cannot read public key! Filepath is: " << pubKeyFilepath;
            return false;
        }
    }
    fp.read(public_key, sizeof(public_key));
    size_t readBytes = fp.gcount();
    fp.close();

    if(expectedPubKeySize != readBytes)
    {
        LogError() << "Read public key has an invalid size! Expected: " << expectedPubKeySize << " Bytes, but read only: " << readBytes <<"! Aborting.";
        return false;
    }

    //Update the public key in the server object.
    gameServer.server.publicKey.clear();
    for(size_t i = 0; i < expectedPubKeySize; i++)
        gameServer.server.publicKey.push_back(public_key[i]);

    fp.open(privKeyFilepath.c_str(), std::ios::in | std::ios::binary);
    if(!fp.is_open())
    {
        LogError() << "Cannot open private key file \"" << privKeyFilepath << "\" for read! Startup failed!";
        return false;
    }
    fp.read(private_key, sizeof(private_key));
    readBytes = fp.gcount();
    fp.close();

    if(expectedPrivKeySize != readBytes)
    {
        LogError() << "Read private key has an invalid size! Expected: " << expectedPrivKeySize << " Bytes, but read only: " << readBytes << "! Aborting.";
        return false;
    }
    return true;
}

bool NetworkSystem::Startup()
{
    if(!peerInterface)
    {
        return false;
    }

    if(!ReadEncryptionKeys())
    {
        LogError() << "Failed to read encryption keys! Startup failed!";
        return false;
    }

    if(!peerInterface->InitializeSecurity(public_key, private_key, false))
    {
        LogError() << "RakNet told encryption keys are invalid! Please generate a new pair. Startup failed!";
        return false;
    }

    StartupResult res = peerInterface->Startup(2 * playerslots, &socketDescriptor, 1);

    if(res == RAKNET_STARTED)
    {
        //Update server object.
        gameServer.server.servername = "OpenGMP-Server";
        gameServer.server.password.clear();
        gameServer.server.gamePort = gameport;
        LogInfo() << "NetworkController started! Listening on port " << gameport << " with " << playerslots << " slots.";
        peerInterface->SetMaximumIncomingConnections(2 * playerslots);
        peerInterface->SetOccasionalPing(1);
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
    bool packetReceipt = false;

    for (RakNet::Packet *packet = peerInterface->Receive();
         packet;
         peerInterface->DeallocatePacket(packet), packet = peerInterface->Receive())
    {
        packetReceipt = true;
        if(0 < packet->length)
        {
            switch(packet->data[0])
            {
                case NetworkSystemMessages::LoginSystem:
                case ID_NEW_INCOMING_CONNECTION:
                case ID_CONNECTION_LOST:
                case ID_DISCONNECTION_NOTIFICATION:
                {
                    gameServer.loginSystem.Process(packet);
                    break;
                }
                case NetworkSystemMessages::PlayerController:
                {
                    gameServer.playerController.Process(packet);
                    break;
                }
                case NetworkSystemMessages::Ping:
                {
                    break;
                }
                default:
                {
                    LogInfo() << "Got unhandled package with id: " << (int)packet->data[0];
                }
            }
        }
    }
    return packetReceipt;
}

int NetworkSystem::GenKeys(const std::string &keyDir,
                           const std::string &pubKeyfileName,
                           const std::string &privKeyfileName)
{
    std::string pubKeyFilepath = std::string(keyDir).append("/").append(pubKeyfileName);
    std::string privKeyFilepath = std::string(keyDir).append("/").append(privKeyfileName);

    cat::EasyHandshake::Initialize();
    cat::EasyHandshake handshake;
    char public_key[cat::EasyHandshake::PUBLIC_KEY_BYTES];
    char private_key[cat::EasyHandshake::PRIVATE_KEY_BYTES];
    handshake.GenerateServerKey(public_key, private_key);

    //Write public key to file:
    std::ofstream fp;
    fp.open(pubKeyFilepath.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
    if(!fp.is_open())
    {
        LogError() << "Cannot write public key to file!";
        return 1;
    }
    fp.write(public_key, sizeof(public_key));
    fp.close();

    //Write private key to file:
    fp.open(privKeyFilepath.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
    if(!fp.is_open())
    {
        LogError() << "Cannot write private key to file!";
        return 1;
    }
    fp.write(private_key, sizeof(private_key));
    fp.close();

    LogInfo() << "New generated keys successfully written to files. Exiting now.";
    return 0;
}

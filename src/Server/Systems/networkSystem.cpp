#include "networkSystem.hpp"
#include "../gameServer.hpp"
#include <Shared/Types/Messages/networkSystemMessages.hpp>
#include <utils/logger.h>

#if LIBCAT_SECURITY!=1
#error "Define LIBCAT_SECURITY 1 in lib/RakNet/Source/NativeFeatureIncludesOverrides.h to enable Encryption"
#endif

using namespace RakNet;
using namespace OpenGMP::Types;
using namespace OpenGMP::Systems;

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

    FILE *fp = fopen(pubKeyFilepath.c_str(), "r");
    if(!fp)
    {
        LogError() << "Cannot open public key file \"" << pubKeyFilepath << "\" for read! Startup failed!";
        return false;
    }
    size_t readBytes = fread(public_key, 1, sizeof(public_key), fp);
    fclose(fp);

    if(expectedPubKeySize != readBytes)
    {
        LogError() << "Read public key has an invalid size! Expected: " << expectedPubKeySize << " Bytes, but read only: " << readBytes <<"! Aborting.";
        return false;
    }

    fp = fopen(privKeyFilepath.c_str(), "r");
    if(!fp)
    {
        LogError() << "Cannot open private key file \"" << privKeyFilepath << "\" for read! Startup failed!";
        return false;
    }
    readBytes = fread(private_key, 1, sizeof(private_key), fp);
    fclose(fp);

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
        LogInfo() << "NetworkController started! Listening on port " << gameport << " with " << playerslots << " slots.";
        peerInterface->SetMaximumIncomingConnections(2 * playerslots);
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

    while((packet = peerInterface->Receive()))
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
    FILE *fp = fopen(pubKeyFilepath.c_str(), "w");
    if(!fp)
    {
        LogError() << "Cannot write public key to file!";
        return 1;
    }
    fwrite(public_key, sizeof(public_key), 1, fp);
    fclose(fp);

    //Write private key to file:
    fp = fopen(privKeyFilepath.c_str(), "w");
    if(!fp)
    {
        LogError() << "Cannot write private key to file!";
        return 1;
    }
    fwrite(private_key, sizeof(private_key), 1, fp);
    fclose(fp);

    LogInfo() << "New generated keys successfully written to files. Exiting now.";
    return 0;
}

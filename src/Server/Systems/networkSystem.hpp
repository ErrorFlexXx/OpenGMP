#pragma once

#include <string>
#include <RakPeerInterface.h>
#include <NativeFeatureIncludes.h>
#include <SecureHandshake.h>

namespace RakNet
{
    class RakPeerInterface;
    class SocketDescriptor;
    struct Packet;
}

namespace OpenGMP
{
    class GameServer;

    class NetworkSystem
    {
    public:
        NetworkSystem(GameServer &gameServer, const int &gameport, const int &playerslots,
                      const std::string &keyDirectory, const std::string &publicKeyfileName, const std::string &privateKeyfileName);

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

        /**
         * @brief ReadEncryptionKeys
         * @return true if keys are found and data has correct length.
         */
        bool ReadEncryptionKeys();

        /**
         * @brief GenKeys creates a new keypair of pub/priv keys.
         * @param keyDir directory, where new key files are created.
         * @return 0 on success, something other otherwise.
         */
        static int GenKeys(const std::string &keyDir,
                           const std::string &pubKeyfileName,
                           const std::string &privKeyfileName);

        RakNet::RakPeerInterface *peerInterface;    //!< RakNet PeerInterface object.

    private:
        GameServer &gameServer; //!< The GameServer instance this System acts for.
        int gameport;           //!< UDP RakNet listening port.
        int playerslots;        //!< Currently accepted simulateously active connected players.
        std::string keyDirectory;
        std::string publicKeyfileName;
        std::string privateKeyfileName;
        char public_key[cat::EasyHandshake::PUBLIC_KEY_BYTES] = {};
        char private_key[cat::EasyHandshake::PUBLIC_KEY_BYTES] = {};
        RakNet::SocketDescriptor socketDescriptor;  //!< Socket descriptor holding maxConns.
    };
}

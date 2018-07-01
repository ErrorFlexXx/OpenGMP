#pragma once

#include <RakPeerInterface.h>
#include <PacketPriority.h>
#include <thread>
#include <string>
#include <mutex>
#include <stdint.h>

namespace OpenGMP
{
    class GameClient;

    namespace Systems
    {
        class NetworkSystem
        {
        public:
            NetworkSystem(GameClient &gameClient); //dev std constructor
            NetworkSystem(GameClient &gameClient, const std::string &hostname, unsigned short port);

            bool Startup();

            void Shutdown();

            void Update();
            
            void StartupFailed();
            
        private:
            GameClient &gameClient;
            static bool started;
            static char public_key[];
            RakNet::RakPeerInterface *peerInterface;    //!< RakNet PeerInterface object.
            RakNet::SocketDescriptor socketDescriptor;  //!< RakNet SocketDescriptor.
            RakNet::SystemAddress serverAddress;        //!< RakNet SystemAddress of the server.
            RakNet::PublicKey pk;
            std::mutex networkMutex;    //!< Mutex to sync renderer - network threads.
            std::string hostname;
            unsigned short port;
            uint32_t ping;
        };
    }
}
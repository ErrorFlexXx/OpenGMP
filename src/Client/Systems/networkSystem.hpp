#pragma once

#include <RakPeerInterface.h>
#include <PacketPriority.h>
#include <thread>
#include <string>
#include <mutex>
#include <stdint.h>

namespace OpenGMP
{
    namespace Systems
    {
        class NetworkSystem
        {
        public:
            NetworkSystem(); //dev std constructor
            NetworkSystem(const std::string &hostname, unsigned short port);

            /* Starts a network thread, which will connect to a server */
            bool Startup();

            /* Signals the network thread to quit */
            void Shutdown();

            /* Called from GameLoop */
            bool Update();

            /* Started in a separate thread */
            void NetworkLoop();

            /* Called from network thread */
            void StartupFailed();
            
        private:
            static bool runNetwork;
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
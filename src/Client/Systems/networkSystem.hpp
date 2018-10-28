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

    class NetworkSystem
    {
    public:
        NetworkSystem(GameClient &gameClient); //dev std constructor

        bool Startup();

        void Shutdown();

        void Update();

        void StartupFailed();

        RakNet::SystemAddress serverAddress;        //!< RakNet SystemAddress of the server.
        RakNet::RakPeerInterface *peerInterface;    //!< RakNet PeerInterface object.

    private:
        GameClient &gameClient;
        static bool started;
        static char public_key[];
        RakNet::SocketDescriptor socketDescriptor;  //!< RakNet SocketDescriptor.
        RakNet::PublicKey pk;
        std::mutex networkMutex;    //!< Mutex to sync renderer - network threads.
        std::string hostname;
        unsigned short port;
        uint32_t ping;
    };
}
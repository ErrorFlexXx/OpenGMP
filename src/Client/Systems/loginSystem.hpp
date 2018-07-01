#pragma once

#include <string>

namespace RakNet
{
    struct Packet;
}

namespace OpenGMP
{
    class GameClient;

    namespace Systems
    {
        class LoginSystem
        {
        public:
            LoginSystem(GameClient &gameClient);
            
            void Process(RakNet::Packet *packet);

        private:
            GameClient &gameClient;
        };
    }
}
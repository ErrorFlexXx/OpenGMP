#pragma once

#include <string>

namespace RakNet
{
    struct Packet;
}

namespace OpenGMP
{
    class GameClient;

    namespace Components
    {
        class AuthData;
    }

    namespace Systems
    {
        class LoginSystem
        {
        public:
            LoginSystem(GameClient &gameClient);
            
            void Process(RakNet::Packet *packet);

            void SendRegister(const Components::AuthData &authData);

            void GetMac(Components::AuthData &authData);

            void LoginSystem::GetHDDSerial(Components::AuthData &authData);

        private:

            GameClient &gameClient;
        };
    }
}
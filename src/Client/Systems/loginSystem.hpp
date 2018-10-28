#pragma once

#include <string>

namespace RakNet
{
    struct Packet;
}

namespace OpenGMP
{
    class GameClient;
    class AuthData;

    class LoginSystem
    {
    public:
        LoginSystem(GameClient &gameClient);

        void Process(RakNet::Packet *packet);

        void SendRegister(const AuthData &authData);

        void GetMac(AuthData &authData);

        void LoginSystem::GetHDDSerial(AuthData &authData);

    private:

        GameClient &gameClient;
    };
}
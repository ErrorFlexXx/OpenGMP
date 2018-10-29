#pragma once

#include <string>

namespace RakNet
{
    struct Packet;
    class BitStream;
}

namespace OpenGMP
{
    class GameClient;
    class AuthData;
    class LoginData;

    class LoginSystem
    {
    public:
        LoginSystem(GameClient &gameClient);

        void Process(RakNet::Packet *packet);

        void SendLoginSystemPacket(const RakNet::BitStream &bsOut);

        void SendRegister(const LoginData &loginData);

        void SendLogin(const LoginData &loginData);

        void GetMac(AuthData &authData);

        void LoginSystem::GetHDDSerial(AuthData &authData);

    private:

        GameClient &gameClient;
    };
}
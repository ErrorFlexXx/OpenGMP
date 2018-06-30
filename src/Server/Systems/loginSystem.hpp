#pragma once

#include <string>

namespace RakNet
{
    class Packet;
}

namespace OpenGMP
{
    class GameServer;

    namespace Objects
    {
        class ServerClient;
    }

    namespace Systems
    {
        class LoginSystem
        {
        public:
            LoginSystem(GameServer &gameServer);

            void Process(RakNet::Packet *packet);

            void SendBanned(RakNet::Packet *packet);

            void CloseConnection(RakNet::Packet *packet);

            bool IsBanned(const std::string &ip);

            bool IsBanned(Objects::ServerClient &client);

            void BanByMac(Objects::ServerClient &client);

            void UnbanByMac(Objects::ServerClient &client);

            void BanByHDD(Objects::ServerClient &client);

            void UnbanByHDD(Objects::ServerClient &client);

            void BanByLoginname(Objects::ServerClient &client);

            void UnbanByLoginname(Objects::ServerClient &client);

        protected:
            void AddEntryToList(const std::string &filename, const std::string &entry);
            void RemoveEntryFromList(const std::string &filename, const std::string &entry);
            bool CheckEntryExists(const std::string &filename, const std::string &entry);

        private:
            GameServer &gameServer;
        };
    }
}

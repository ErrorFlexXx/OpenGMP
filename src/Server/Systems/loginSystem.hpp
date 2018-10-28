#pragma once

#include <string>

namespace RakNet
{
    struct Packet;
}

namespace OpenGMP
{
    class GameServer;
    class ServerClient;

    class LoginSystem
    {
    public:
        /**
         * @brief handles requests regarding to connecting/disconnecting a client.
         * @param gameServer the GameServer object, this loginSystem acts for.
         */
        LoginSystem(GameServer &gameServer);

        /**
         * @brief Process processes RakNet messages reagarding connection or loginSystem messages.
         * @param packet the inbound RakNet::Packet to process.
         */
        void Process(RakNet::Packet *packet);

        /**
         * @brief SendBanned sends a banned packet to the client.
         * @param packet a packet including the sender address, which is used as destination.
         */
        void SendBanned(RakNet::Packet *packet);

        /**
         * @brief SendServerFull sends a server full packet to the client.
         * @param packet a packet including the sender address, which is used as destination.
         */
        void SendServerFull(RakNet::Packet *packet);

        /**
         * @brief SendAuth sends an auth packet to the client, to signal Login/Register is possible now.
         * @param packet a packet including the sender address, which is used as destination.
         */
        void SendAuth(RakNet::Packet *packet);

        /**
         * @brief CloseConnection closes the network connection with the peer.
         * @param packet a packet including the sender address, which is used as destination.
         */
        void CloseConnection(RakNet::Packet *packet);

        /**
         * @brief IsBanned checks, if an IP is banned on the system.
         * @param ip as string.
         * @return true if banned, false otherwise.
         */
        bool IsBanned(const std::string &ip);

        /**
         * @brief IsBanned checks, if an client is banned on any known AuthData attribute.
         * @param client to check.
         * @return true if banned, false otherwise.
         */
        bool IsBanned(ServerClient &client);

        /**
         * @brief BanByMac bans a client by adding its mac address to the banned entries.
         * @param client to ban.
         */
        void BanByMac(ServerClient &client);

        /**
         * @brief UnbanByMac removes a mac address from banned entries.
         * @param client to take the mac address from.
         */
        void UnbanByMac(ServerClient &client);

        /**
         * @brief BanByHDD bans a client by it's hdd serial.
         * @param client to take the hdd serial from.
         */
        void BanByHDD(ServerClient &client);

        /**
         * @brief UnbanByHDD removes a hdd serial from banned entries.
         * @param client to take the hdd serial from.
         */
        void UnbanByHDD(ServerClient &client);

        /**
         * @brief BanByLoginname bans a client by it's loginname.
         * @param client to take the loginname from.
         */
        void BanByLoginname(ServerClient &client);

        /**
         * @brief UnbanByLoginname removes an loginname from banned entries.
         * @param client to take the loginname from.
         */
        void UnbanByLoginname(ServerClient &client);

        void Unban(ServerClient &client);

    protected:

        /**
         * @brief AddEntryToList adds an string entry to a file.
         * @param filename to write the entry in.
         * @param entry to write to the file.
         */
        void AddEntryToList(const std::string &filename, const std::string &entry);

        /**
         * @brief RemoveEntryFromList removes an string entry from a file.
         * @param filename to remove the entry from.
         * @param entry to remove from the file.
         */
        void RemoveEntryFromList(const std::string &filename, const std::string &entry);

        /**
         * @brief CheckEntryExists checks if an entry exists in a file.
         * @param filename to check for the entry.
         * @param entry to search in the file.
         * @return true if included, false otherwise.
         */
        bool CheckEntryExists(const std::string &filename, const std::string &entry);

    private:
        GameServer &gameServer; //!< The GameServer instance this System acts for.
    };
}

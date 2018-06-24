#pragma once

class GameServer;
class ServerClient;

namespace RakNet
{
    class Packet;
}

class LoginSystem
{
public:
    LoginSystem(GameServer &gameServer);

    void Process(RakNet::Packet *packet);

    bool IsBanned(ServerClient &client);

    void BanByMac(ServerClient &client);

    void UnbanByMac(ServerClient &client);

    void BanByHDD(ServerClient &client);

    void UnbanByHDD(ServerClient &client);

    void BanByLoginname(ServerClient &client);

    void UnbanByLoginname(ServerClient &client);

protected:
    void AddEntryToList(const std::string &filename, const std::string &entry);
    void RemoveEntryFromList(const std::string &filename, const std::string &entry);
    bool CheckEntryExists(const std::string &filename, const std::string &entry);

private:
    GameServer &gameServer;
};

#include "loginSystem.hpp"
#include "scriptSystem.hpp"
#include <Server/gameServer.hpp>
#include <Server/Objects/serverClient.hpp>
#include <Server/Utils/utils.h>
#include <Shared/Types/Messages/loginSystemMessages.hpp>
#include <utils/logger.h>
#include <BitStream.h>
#include <MessageIdentifiers.h>
#include <RakSleep.h>

using namespace RakNet;
using namespace OpenGMP;

const std::string MACBANLIST_FILE = "macbanlist.txt";
const std::string HDDBANLIST_FILE = "hddbanlist.txt";
const std::string LOGINNAMEBANLIST_FILE = "loginnamebanlist.txt";
const std::string IPBANLIST_FILE = "ipbanlist.txt";

LoginSystem::LoginSystem(GameServer &gameServer)
    : gameServer(gameServer)
{}

void LoginSystem::Process(Packet *packet)
{
    unsigned char command;
    BitStream bsIn(packet->data, packet->length, false);
    bsIn.Read(command);

    if(command < ID_USER_PACKET_ENUM) //RakNet System message
    {
        switch(command)
        {
            case ID_NEW_INCOMING_CONNECTION:
            {
                RakNet::RakNetGUID guid = packet->guid;
                std::string ip = packet->systemAddress.ToString(false);
                Id id;
                bool created;
                int connectedClients = gameServer.clientContainer.Count();

                if(connectedClients >= gameServer.clientContainer.capacity)
                {
                    SendServerFull(packet);
                    CloseConnection(packet);
                }

                if(IsBanned(ip))
                {
                    SendBanned(packet);
                    CloseConnection(packet);
                }
                ServerClient &client = gameServer.clientContainer.CreateEntity(created, id, guid);
                client.netId.rakNetId = packet->guid;
                LogInfo() << "Client connected. IP: " << ip << ", ID: " << id.id << ", added to clientContainer: " << (created ? "true" : "false") << ".";
                SendAuth(packet);
                break;
            }
            case ID_CONNECTION_LOST:
            {
                std::string ip = packet->systemAddress.ToString(false);
                bool removed = gameServer.clientContainer.Remove(packet->guid);
                LogInfo() << "Client lost connection. IP: " << ip << ". " << (removed ? "Successfully removed from clientContainer." : "Wasn't in clientContainer, not removed.");
                break;
            }
            case ID_DISCONNECTION_NOTIFICATION:
            {
                std::string ip = packet->systemAddress.ToString(false);
                bool removed = gameServer.clientContainer.Remove(packet->guid);
                LogInfo() << "Client disconnected. IP: " << ip << ". " << (removed ? "Successfully removed from clientContainer." : "Wasn't in clientContainer, not removed.");
                break;
            }
            default:
            {
                LogWarn() << "LoginSystem RakNet Message not handled! ID is: " << (int)command << ".";
            }
        }
    }
    else //OpenGMP Message
    {
        bsIn.Read(command); //Read LoginSystem command

        switch(command)
        {
            case LoginSystemMessages::REGISTER:
            {
                bool success;
                ServerClient &client = gameServer.clientContainer.Get(packet->guid, success);
                client.authData.ReadStream(bsIn);
                gameServer.scriptSystem.InvokeScriptFunction("Register", client);
                break;
            }
            default:
            {
                LogWarn() << "Unknown LoginSystemMessages id " << (int)(command);
                break;
            }
        }
    }
}

void LoginSystem::SendBanned(Packet *packet)
{
    BitStream bsOut;
    bsOut.Write(NetworkSystemMessages::LoginSystem);
    bsOut.Write(LoginSystemMessages::BANNED);
    gameServer.networkSystem.peerInterface->Send(
                &bsOut, LOW_PRIORITY, RELIABLE, LoginSystemOrderingChannel, packet->systemAddress, false);
}

void LoginSystem::SendServerFull(Packet *packet)
{
    BitStream bsOut;
    bsOut.Write(NetworkSystemMessages::LoginSystem);
    bsOut.Write(LoginSystemMessages::SERVERFULL);
    gameServer.networkSystem.peerInterface->Send(
                &bsOut, LOW_PRIORITY, RELIABLE, LoginSystemOrderingChannel, packet->systemAddress, false);
}

void LoginSystem::SendAuth(Packet *packet)
{
    BitStream bsOut;
    bsOut.Write(NetworkSystemMessages::LoginSystem);
    bsOut.Write(LoginSystemMessages::AUTH);
    gameServer.networkSystem.peerInterface->Send(
                &bsOut, LOW_PRIORITY, RELIABLE, LoginSystemOrderingChannel, packet->systemAddress, false);
}

void LoginSystem::CloseConnection(Packet *packet)
{
    gameServer.networkSystem.peerInterface->CloseConnection(packet->systemAddress, true, LoginSystemOrderingChannel);
    gameServer.clientContainer.Remove(packet->guid);
}

bool LoginSystem::IsBanned(const std::string &ip)
{
    bool banned = false;

    //Check ip ban.
    banned |= CheckEntryExists(IPBANLIST_FILE, ip);
    if(banned)
    {
        LogInfo() << "Client " << ip << " banned by ip.";
        return banned;
    }

    return banned; //False if we reached this line.
}

bool LoginSystem::IsBanned(ServerClient &client)
{
    bool banned = false;

    //Check mac ban.
    banned |= CheckEntryExists(MACBANLIST_FILE, client.authData.macAddress);
    if(banned)
    {
        LogInfo() << "Player " << client.authData.loginname << " banned by mac: " << client.authData.macAddress;
        return banned;
    }
    //Check hdd ban.
    std::string hddSerial = std::to_string(client.authData.hddSerial);
    banned |= CheckEntryExists(HDDBANLIST_FILE, hddSerial);
    if(banned)
    {
        LogInfo() << "Player " << client.authData.loginname << " banned by hdd: " << hddSerial;
        return banned;
    }
    //Check login ban.
    banned |= CheckEntryExists(LOGINNAMEBANLIST_FILE, client.authData.loginname);
    if(banned)
    {
        LogInfo() << "Player " << client.authData.loginname << " banned by loginname: " << client.authData.loginname;
        return banned;
    }

    return banned; //False if we reached this line.
}

void LoginSystem::AddEntryToList(const std::string &filename, const std::string &entry)
{
    std::string filepath = Utils::getUserDataLocation() + "/" + filename;
    std::string userdata = Utils::getUserDataLocation();
    std::string fileContents;

    if(0 == entry.size())
    {
        LogWarn() << "Will not add empty entry to list: " << filename;
        return;
    }

    if(Utils::fileExists(filepath))
        fileContents = Utils::readFileContents(filepath);
    fileContents.append(std::string(entry).append("\r\n"));

    if (!Utils::mkdir(userdata))
        LogWarn() << "Failed to create userdata-directory at: " << userdata;

    // Now create the file
    if (!Utils::writeFile(filename, userdata, fileContents))
        LogWarn() << "Failed to write banlist-file to: " << filepath;
}

void LoginSystem::RemoveEntryFromList(const std::string &filename, const std::string &entry)
{
    std::string filepath = Utils::getUserDataLocation() + "/" + filename;
    std::string userdata = Utils::getUserDataLocation();
    std::string fileContents;

    if(0 == entry.size())
    {
        LogWarn() << "Will not remove empty entry from list: " << filename;
        return;
    }

    if(!Utils::fileExists(filepath))
    {
        LogWarn() << "Cannot open banlist to remove an entry. File: " << filename;
        return;
    }

    fileContents = Utils::readFileContents(filepath);
    std::string::size_type index = fileContents.find(entry.c_str());
    if(index == std::string::npos)
    {
        LogWarn() << "Cannot delete entry \"" << entry << "\" from file \"" << filename << "\". Entry not found.";
        return;
    }
    fileContents.erase(index, entry.length() + 2); //Remove entry + <CR><LF>

    if (!Utils::writeFile(filename, userdata, fileContents))
        LogWarn() << "Failed to write banlist-file to: " << filepath;
}

bool LoginSystem::CheckEntryExists(const std::string &filename, const std::string &entry)
{
    std::string filepath = Utils::getUserDataLocation() + "/" + filename;
    std::string userdata = Utils::getUserDataLocation();
    std::string fileContents;

    if(0 == entry.size())
    {
        LogInfo() << "Cannot lookup empty entry in list \"" << filename << "\".";
        return false;
    }

    if(!Utils::fileExists(filepath))
    {
        if (!Utils::writeFile(filename, userdata, std::string("")))
            LogError() << "List \"" << filename << "\" does not exists. Cannot lookup entry \"" << entry << "\". Can't create list - directory not writable: \"" << userdata << "\".";
        else
            LogInfo() << "List \"" << filename << "\" does not exists. Cannot lookup entry \"" << entry << "\". Blank list created.";

        return false;
    }

    fileContents = Utils::readFileContents(filepath);
    std::string::size_type index = fileContents.find(entry.c_str());
    if(index == std::string::npos) //Not found ?
    {
        return false;
    }
    return true;
}

void LoginSystem::BanByMac(ServerClient &client)
{
    AddEntryToList(MACBANLIST_FILE, client.authData.macAddress);
}

void LoginSystem::UnbanByMac(ServerClient &client)
{
    RemoveEntryFromList(MACBANLIST_FILE, client.authData.macAddress);
}

void LoginSystem::BanByHDD(ServerClient &client)
{
    AddEntryToList(HDDBANLIST_FILE, std::to_string(client.authData.hddSerial));
}

void LoginSystem::UnbanByHDD(ServerClient &client)
{
    RemoveEntryFromList(HDDBANLIST_FILE, std::to_string(client.authData.hddSerial));
}

void LoginSystem::BanByLoginname(ServerClient &client)
{
    AddEntryToList(LOGINNAMEBANLIST_FILE, client.authData.loginname);
}

void LoginSystem::UnbanByLoginname(ServerClient &client)
{
    RemoveEntryFromList(LOGINNAMEBANLIST_FILE, client.authData.loginname);
}


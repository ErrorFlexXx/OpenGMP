#include "loginSystem.hpp"
#include "../gameServer.hpp"
#include "../Objects/serverClient.hpp"
#include <Shared/Types/Messages/loginSystemMessages.hpp>
#include <utils/logger.h>
#include <BitStream.h>
#include "../Utils/utils.h"
//Script system includes:
#include "../ScriptController/scriptController.hpp"
#include <cpgf/metatraits/gmetaconverter_string.h>
#include <cpgf/gmetadefine.h>
#include <cpgf/goutmain.h>

using namespace RakNet;
using namespace OpenGMP::Types;
using namespace OpenGMP::Systems;

const std::string MACBANLIST_FILE = "macbanlist.txt";
const std::string HDDBANLIST_FILE = "hddbanlist.txt";
const std::string LOGINNAMEBANLIST_FILE = "loginnamebanlist.txt";

LoginSystem::LoginSystem(GameServer &gameServer)
    : gameServer(gameServer)
{}

void LoginSystem::Process(Packet *packet)
{
    LoginSystemMessages command;
    BitStream stream(packet->data, packet->length, false);

    stream.IgnoreBytes(1);
    stream.Read(command);

    switch(command)
    {
        case(LoginSystemMessages::LOGIN):
        {

            break;
        }
        default:
        {
            LogWarn() << "Unknown LoginSystemMessages id " << (int)(command);
            break;
        }
    }
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
    std::string fileContents;

    if(0 == entry.size())
    {
        LogInfo() << "Cannot lookup empty entry in list \"" << filename << "\".";
        return false;
    }

    if(!Utils::fileExists(filepath))
    {
        LogInfo() << "Cannot lookup entry \"" << entry << "\" in list \"" << filename << "\". File cannot be opened.";
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


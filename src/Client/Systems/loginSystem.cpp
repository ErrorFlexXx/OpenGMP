#include "loginSystem.hpp"
#include "../gameClient.hpp"
#include <Shared/Systems/versionSystem.hpp>
#include <Shared/Components/authData.hpp>
#include <Shared/Components/loginData.hpp>
#include <Shared/Types/Messages/networkSystemMessages.hpp>
#include <Shared/Types/Messages/loginSystemMessages.hpp>
#include <iostream>
#include <string>
#include <BitStream.h>
#include <MessageIdentifiers.h>
#include <iphlpapi.h>
#include <libintl.h>
#define _(string) gettext (string)

using namespace RakNet;
using namespace OpenGMP;

LoginSystem::LoginSystem(GameClient &gameClient)
    : gameClient(gameClient)
{}

void LoginSystem::Process(RakNet::Packet *packet)
{
    NetMessage command;
    BitStream bsIn(packet->data, packet->length, false);
    bsIn.Read(command);

    if (command < ID_USER_PACKET_ENUM) //RakNet System message
    {
        switch (command)
        {
        case ID_CONNECTION_LOST:
        {
            gameClient.menuSystem.menuMain.DisableNetworkElements();
            gameClient.menuSystem.ShowNotification(
                20,
                std::string(_("Connection to server lost!")),
                Color(255, 0, 0, 255)
            );
            break;
        }
        case ID_DISCONNECTION_NOTIFICATION:
        {
            gameClient.menuSystem.ShowNotification(
                20,
                std::string(_("Connection has been closed by the server!")),
                Color(255, 0, 0, 255)
            );
            break;
        }
        case ID_CONNECTION_REQUEST_ACCEPTED:
        {
            gameClient.networkSystem.serverAddress = packet->systemAddress;
            gameClient.menuSystem.HideNotification();
            break;
        }
        case ID_CONNECTION_ATTEMPT_FAILED:
        {
            gameClient.menuSystem.ShowNotification(
                20,
                std::string(_("Connection attempt failed!")).append(" Hostname: ").append(gameClient.networkSystem.server.hostname).append(
                    " Port: ").append(std::to_string(gameClient.networkSystem.server.gamePort)).append("!"),
                Color(255, 0, 0, 255)
            );
            break;
        }
        default:
        {
#ifdef DBG_NETWORK
            gameClient.menuSystem.ShowNotification(
                20,
                std::string(_("LoginSystem RakNet Message not handled! ID is")).append(": ").append(std::to_string((int)command)).append("!"),
                Color(255, 0, 0, 255),
                10
            );
#endif
            break;
        }
        }
    }
    else //OpenGMP Message
    {
        bsIn.Read(command); //Read LoginSystem command

        switch (command)
        {
        case LoginSystemMessages::AUTH:
        {
            GetMac(gameClient.client.authData);
            GetHDDSerial(gameClient.client.authData);

            BitStream bsOut;
            bsOut.Write((NetMessage)NetworkSystemMessages::LoginSystem);
            bsOut.Write((NetMessage)LoginSystemMessages::AUTH);
            gameClient.client.authData.WriteStream(bsOut);
            gameClient.client.version.WriteStream(bsOut);
            SendLoginSystemPacket(bsOut);
            break;
        }
        case LoginSystemMessages::AUTH_ACCEPTED:
        {
            gameClient.menuSystem.menuMain.EnableNetworkElements();
            break;
        }
        case LoginSystemMessages::BANNED:
        {
            gameClient.menuSystem.ShowNotification(
                20,
                std::string(_("You're banned on this server!")),
                Color(255, 0, 0, 255)
            );
        }
        case LoginSystemMessages::SERVERFULL:
        {
            gameClient.menuSystem.ShowNotification(
                20,
                std::string(_("The server is full! Please try again later.")),
                Color(255, 0, 0, 255)
            );
        }
        case LoginSystemMessages::VERSION_INCOMPATIBLE:
        {
            gameClient.menuSystem.ShowNotification(
                20,
                std::string(_("Your client version is incompatible with this server!")),
                Color(255, 0, 0, 255)
            );
        }
        default:
        {
#ifdef DBG_NETWORK
            gameClient.menuSystem.ShowNotification(
                20,
                std::string(_("LoginSystem RakNet Message not handled! ID is")).append(": ").append(std::to_string((int)command)).append("!"),
                Color(255, 0, 0, 255),
                10
            );
#endif
            break;
        }
        }
    }
}

void LoginSystem::SendLoginSystemPacket(const BitStream &bsOut)
{
    gameClient.networkSystem.peerInterface->Send(
        &bsOut, LOW_PRIORITY, RELIABLE, LoginSystemOrderingChannel, gameClient.networkSystem.serverAddress, false);
}

void LoginSystem::SendRegister(const LoginData &loginData)
{
    BitStream bsOut;
    bsOut.Write((NetMessage) NetworkSystemMessages::LoginSystem);
    bsOut.Write((NetMessage) LoginSystemMessages::REGISTER);
    loginData.WriteStream(bsOut);
    SendLoginSystemPacket(bsOut);
    gameClient.menuSystem.menuRegister.DisableRegisterButton();
}

void LoginSystem::SendLogin(const LoginData &loginData)
{
    BitStream bsOut;
    bsOut.Write((NetMessage) NetworkSystemMessages::LoginSystem);
    bsOut.Write((NetMessage) LoginSystemMessages::LOGIN);
    loginData.WriteStream(bsOut);
    SendLoginSystemPacket(bsOut);
}

void LoginSystem::GetMac(AuthData &authData)
{
    IP_ADAPTER_INFO AdapterInfo[16];
    DWORD bufLen = sizeof(AdapterInfo);
    DWORD dwStatus = GetAdaptersInfo(AdapterInfo, &bufLen);
    
    if (dwStatus == ERROR_SUCCESS)
    {
        PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo; //Take first adapter
        while (
            pAdapterInfo && //As long as there is an adapter
            pAdapterInfo->Address[0] == 0 && //and the current adapter
            pAdapterInfo->Address[0] == 0 && //has a
            pAdapterInfo->Address[0] == 0 && //totally zero
            pAdapterInfo->Address[0] == 0 && //mac
            pAdapterInfo->Address[0] == 0)   //address
        {
            pAdapterInfo = pAdapterInfo->Next; //Take next adapter
        }

        if (pAdapterInfo) //If we found an adapter
        {
            const int BufSize = 18;
            char mac[BufSize] = {};
            sprintf_s(mac, BufSize, "%02X-%02X-%02X-%02X-%02X-%02X", //format the mac address
                pAdapterInfo->Address[0],
                pAdapterInfo->Address[1],
                pAdapterInfo->Address[2],
                pAdapterInfo->Address[3],
                pAdapterInfo->Address[4],
                pAdapterInfo->Address[5]);
            authData.macAddress = mac; //and attach it to authData component.
        }
    }
}

void LoginSystem::GetHDDSerial(AuthData &authData)
{
    DWORD serial;
    GetVolumeInformation("C:\\", NULL, 0, &serial, NULL, NULL, NULL, 0);
    authData.hddSerial = (uint32_t)serial;
}
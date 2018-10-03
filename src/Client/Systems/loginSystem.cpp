#include "loginSystem.hpp"
#include "../gameClient.hpp"
#include <Shared/Components/authData.hpp>
#include <Shared/Types/Messages/networkSystemMessages.hpp>
#include <Shared/Types/Messages/loginSystemMessages.hpp>
#include <iostream>
#include <BitStream.h>
#include <MessageIdentifiers.h>
#include <iphlpapi.h>

using namespace RakNet;
using namespace OpenGMP;
using namespace OpenGMP::Components;
using namespace OpenGMP::Systems;
using namespace OpenGMP::Types;

LoginSystem::LoginSystem(GameClient &gameClient)
    : gameClient(gameClient)
{}

void LoginSystem::Process(RakNet::Packet *packet)
{
    unsigned char command;
    BitStream bsIn(packet->data, packet->length, false);
    bsIn.Read(command);

    if (command < ID_USER_PACKET_ENUM) //RakNet System message
    {
        switch (command)
        {
        case ID_CONNECTION_LOST:
        {
            gameClient.menuSystem.menuMain.DisableNetworkElements();
            std::cout << "Connection Lost." << std::endl;
            break;
        }
        case ID_CONNECTION_REQUEST_ACCEPTED:
        {
            gameClient.networkSystem.serverAddress = packet->systemAddress;
            std::cout << "Connection established." << std::endl;
            break;
        }
        case ID_CONNECTION_ATTEMPT_FAILED:
        {
            std::cout << "Connection attempt failed (Host: \"" << gameClient.serverName << "\" Port: " << gameClient.serverPort << ")!" << std::endl;
            break;
        }
        default:
        {
            std::cout << "LoginSystem RakNet Message not handled! ID is: " << (int)command << ".";
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
            gameClient.menuSystem.menuMain.EnableNetworkElements();
            break;
        }
        default:
        {
            std::cout << "Unknown LoginSystemMessages id " << (int)(command);
            break;
        }
        }
    }
}

void LoginSystem::SendRegister(const Components::AuthData &authData)
{
    BitStream bsOut;
    bsOut.Write(NetworkSystemMessages::LoginSystem);
    bsOut.Write(LoginSystemMessages::REGISTER);
    authData.WriteStream(bsOut);
    gameClient.networkSystem.peerInterface->Send(
        &bsOut, LOW_PRIORITY, RELIABLE, LoginSystemOrderingChannel, gameClient.networkSystem.serverAddress, false);
    gameClient.menuSystem.menuRegister.DisableRegisterButton();
}

void LoginSystem::GetMac(Components::AuthData &authData)
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

void LoginSystem::GetHDDSerial(Components::AuthData &authData)
{
    DWORD serial;
    GetVolumeInformation("C:\\", NULL, 0, &serial, NULL, NULL, NULL, 0);
    authData.hddSerial = (uint32_t)serial;
}
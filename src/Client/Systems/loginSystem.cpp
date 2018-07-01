#include "loginSystem.hpp"
#include <Shared/Types/Messages/networkSystemMessages.hpp>
#include <Shared/Types/Messages/loginSystemMessages.hpp>
#include <iostream>
#include <BitStream.h>
#include <MessageIdentifiers.h>

using namespace RakNet;
using namespace OpenGMP;
using namespace OpenGMP::Systems;
using namespace OpenGMP::Types;

LoginSystem::LoginSystem(GameClient &gameClient)
    : gameClient(gameClient)
{}

void LoginSystem::Process(Packet *packet)
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
            std::cout << "Connection Lost." << std::endl;
            break;
        }
        case ID_CONNECTION_REQUEST_ACCEPTED:
        {
            std::cout << "Connection established." << std::endl;
            break;
        }
        case ID_CONNECTION_ATTEMPT_FAILED:
        {
            std::cout << "Connection attempt failed." << std::endl;
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
            std::cout << "Got packet Login::Auth" << std::endl;
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
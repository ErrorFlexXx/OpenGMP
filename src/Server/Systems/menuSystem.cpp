#include "menuSystem.hpp"
#include <Server/gameServer.hpp>
#include <Server/Objects/serverClient.hpp>
#include <Server/Systems/networkSystem.hpp>
#include <Shared/Components/notificationText.hpp>
#include <Shared/Types/Messages/menuSystemMessages.hpp>

using namespace RakNet;
using namespace OpenGMP;

MenuSystem::MenuSystem(GameServer &gameServer)
    : gameServer(gameServer)
{}

void MenuSystem::Process(Packet *packet)
{
    //Nothing to process at the moment.
}

void MenuSystem::ShowNotification(ServerClient &client, NotificationText &text)
{
    BitStream bs;
    bs.Write(NetworkSystemMessages::MenuSystem);
    bs.Write(MenuSystemMessages::SHOW_NOTIFICATION);
    //gameServer.networkSystem.peerInterface->Send(&bs, )
}

void MenuSystem::ShowTimedNotificaton(ServerClient &client, NotificationText &text)
{

}

void MenuSystem::HideNotification(ServerClient &client)
{

}

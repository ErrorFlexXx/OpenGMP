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
    bs.Write((NetMessage) NetworkSystemMessages::MenuSystem);
    bs.Write((NetMessage) MenuSystemMessages::SHOW_NOTIFICATION);
    text.WriteStream(bs);
    gameServer.networkSystem.peerInterface->Send(&bs, LOW_PRIORITY, RELIABLE, MenuSystemOrderingChannel,
                                                 client.netId.rakNetId, false);
}

void MenuSystem::ShowTimedNotificaton(ServerClient &client, NotificationText &text)
{
    BitStream bs;
    bs.Write((NetMessage) NetworkSystemMessages::MenuSystem);
    bs.Write((NetMessage) MenuSystemMessages::SHOW_TIMED_NOTIFICATION);
    text.WriteStream(bs);
    gameServer.networkSystem.peerInterface->Send(&bs, LOW_PRIORITY, RELIABLE, MenuSystemOrderingChannel,
                                                 client.netId.rakNetId, false);
}

void MenuSystem::HideNotification(ServerClient &client)
{
    BitStream bs;
    bs.Write((NetMessage) NetworkSystemMessages::MenuSystem);
    bs.Write((NetMessage) MenuSystemMessages::HIDE_NOTIFICATION);
    gameServer.networkSystem.peerInterface->Send(&bs, LOW_PRIORITY, RELIABLE, MenuSystemOrderingChannel,
                                                 client.netId.rakNetId, false);
}

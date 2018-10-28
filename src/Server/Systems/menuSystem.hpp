#pragma once

//Forward declarations:
namespace RakNet
{
    struct Packet;
}

namespace OpenGMP
{
    class GameServer;
    class ServerClient;
    class NotificationText;

    class MenuSystem
    {
    public:
        /**
         * @brief handles requests regarding to displayed elements on a client.
         * @param gameServer the GameServer object, this menuSystem acts for.
         */
        MenuSystem(GameServer &gameServer);

        /**
         * @brief Process processes RakNet messages reagarding MenuSystem messages.
         * @param packet the inbound RakNet::Packet to process.
         */
        void Process(RakNet::Packet *packet);

        void ShowNotification(ServerClient &client, NotificationText &text);

        void ShowTimedNotificaton(ServerClient &client, NotificationText &text);

        void HideNotification(ServerClient &client);

    private:
        GameServer &gameServer; //!< The GameServer instance this System acts for.
    };
}

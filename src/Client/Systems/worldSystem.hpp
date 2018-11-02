#pragma once

//Forward declarations:
namespace RakNet
{
    struct Packet;
}

namespace OpenGMP
{
    class GameClient;

    namespace GUI
    {
        class Menu;
    }

    class WorldSystem
    {
    public:
        WorldSystem(GameClient &gameClient);

        void Process(RakNet::Packet *packet);

    private:
        GameClient &gameClient;
    };
}
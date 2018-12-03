#pragma once

#define _WINSOCKAPI_ //Stop windows.h from including winsock.h (colliding with RakNet)
#include <windows.h>
#include <string>
#include "Hooks/hGame.hpp"
#include "Objects/clientClient.hpp"
#include "Objects/clientWorld.hpp"
#include "Objects/clientPlayer.hpp"
#include "Systems/networkSystem.hpp"
#include "Systems/loginSystem.hpp"
#include "Systems/inputSystem.hpp"
#include "Systems/menuSystem.hpp"
#include "Systems/worldSystem.hpp"
#include "Systems/playerController.hpp"
#include "Systems/webStatusSystem.hpp"
#include <Shared/Systems/staticContainer.hpp>
#include <Shared/Objects/server.hpp>

namespace OpenGMP
{
    class GameClient
    {
    public:
        GameClient();
        void Startup(HINSTANCE inst);   // Initializes the game client
        void Stop();                    // Stops the OpenGMP instance (do cleanup..)
        bool IsGothic2exe();
        std::string ReadEnvironmentVariable(const char *varName);

        static HINSTANCE dllInstance;
        ClientClient client;
        NetworkSystem networkSystem;
        LoginSystem loginSystem;
        InputSystem inputSystem;
        MenuSystem menuSystem;
        WorldSystem worldSystem;
        PlayerController playerController;
        WebStatusSystem webStatusSystem;
        HGame hookGame; //GameLoop hooks (Menu & Ingame)

        /* Global containers */
        StaticContainer<ClientWorld> worldContainer;
        StaticContainer<ClientPlayer> playerContainer;
    
    private:
        GameClient(const GameClient&);  //!< No Copy allowed!

        bool inited;
    };
}
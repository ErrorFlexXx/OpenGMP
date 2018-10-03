#pragma once

#define _WINSOCKAPI_ //Stop windows.h from including winsock.h (colliding with RakNet)
#include <windows.h>
#include <string>
#include "Hooks/hGame.hpp"
#include "Objects/clientClient.hpp"
#include "Systems/networkSystem.hpp"
#include "Systems/loginSystem.hpp"
#include "Systems/inputSystem.hpp"
#include "Systems/menuSystem.hpp"

namespace OpenGMP
{
    class GameClient
    {
    public:
        GameClient();
        void Startup(HINSTANCE inst);   // Initializes the game client
        void Stop();                    // Stops the OpenGMP instance (do cleanup..)
        bool IsGothic2exe();
        void ReadEnvironmentConnectData();

        static HINSTANCE dllInstance;
        static std::string serverName;
        static unsigned short serverPort;
        Objects::ClientClient client;
        Systems::NetworkSystem networkSystem;
        Systems::LoginSystem loginSystem;
        Systems::InputSystem inputSystem;
        Systems::MenuSystem menuSystem;
        Hooks::HGame hookGame; //GameLoop hooks (Menu & Ingame)
    
    private:
        GameClient(const GameClient&);  //!< No Copy allowed!

        bool inited;
    };
}
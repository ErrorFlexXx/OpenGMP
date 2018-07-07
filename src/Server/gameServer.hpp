#pragma once

#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <RakNetTypes.h>
#include "Objects/serverClient.hpp"
#include "Systems/networkSystem.hpp"
#include "Systems/loginSystem.hpp"
#include "Systems/netContainerSystem.hpp"
#include "Systems/scriptSystem.hpp"

namespace OpenGMP
{
    /**
     * @brief The GameServer class
     */
    class GameServer
    {
    public:
        GameServer(int gameport,
                   int playerslots,
                   const std::string &scriptDirectory,
                   const std::string &keyDir,
                   const std::string &pubKeyfileName,
                   const std::string &privKeyfileName);
        virtual ~GameServer();

        /**
         * @brief Startup initializes structures necessary to start the gameserver.
         * @return
         */
        bool Startup();

        /**
         * @brief Shutdown unloads and stops all ressources.
         */
        void Shutdown();

        /**
         * @brief Process GameServer Loop
         */
        void Process();

        /**
         * @brief GetGlobalGameServer returns a reference to global
         * @return
         */
        static GameServer &GetGameServerInstance();

        /* Global Systems */
        static GameServer *gameServer;
        OpenGMP::Systems::NetworkSystem networkSystem;
        OpenGMP::Systems::LoginSystem loginSystem;
        OpenGMP::Systems::ScriptSystem scriptSystem;

        /* Global Containers */
        OpenGMP::Systems::NetContainerSystem<Objects::ServerClient> clientContainer;

        std::string scriptDirectory;  //!< Directory to load server scripts from.

    private:
        bool serverRunning;
        bool serverStopped;
    };
}

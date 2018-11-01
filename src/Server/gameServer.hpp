#pragma once

#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <RakNetTypes.h>
#include <Shared/Systems/dynamicContainer.hpp>
#include "Objects/serverClient.hpp"
#include "Objects/serverPlayer.hpp"
#include "Objects/serverWorld.hpp"
#include "Systems/networkSystem.hpp"
#include "Systems/loginSystem.hpp"
#include "Systems/netDynamicContainer.hpp"
#include "Systems/scriptSystem.hpp"
#include "Systems/menuSystem.hpp"
#include "Systems/terminalSystem.hpp"
#include "Systems/worldSystem.hpp"

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
        NetworkSystem networkSystem;
        LoginSystem loginSystem;
        MenuSystem menuSystem;
        ScriptSystem scriptSystem;
        TerminalSystem terminalSystem;
        WorldSystem worldSystem;

        NetworkSystem &GetNetworkSystem();
        LoginSystem &GetLoginSystem();
        ScriptSystem &GetScriptSystem();
        MenuSystem &GetMenuSystem();

        /* Global Containers */
        NetDynamicContainer<ServerClient> clientContainer;
        NetDynamicContainer<ServerPlayer> playerContainer;
        DynamicContainer<ServerWorld> worldContainer;

        std::string scriptDirectory;  //!< Directory to load server scripts from.

    private:
        bool serverRunning;
        bool serverStopped;
    };
}

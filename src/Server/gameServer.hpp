#pragma once

#include <string>
#include <vector>
#include <RakNetTypes.h>
#include "Systems/networkSystem.hpp"
#include "Systems/loginSystem.hpp"

//Forward declarations:
class NetworkSystem;
class IClient;
class IPlayer;
class IWorld;

/**
 * @brief The GameServer class
 */
class GameServer
{
public:
    GameServer(int gameport, int playerslots, const std::string &scriptDirectory);
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

    /* Global Collections */
    std::vector<IClient*> clientList;
    std::vector<IPlayer*> playerList;
    std::vector<IWorld*>  worldList;

private:
    bool serverRunning;
    bool serverStopped;
    std::string scriptDirectory;  //!< Directory to load server scripts from.
};

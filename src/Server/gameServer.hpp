#pragma once

#include <string>
#include <vector>
#include <RakNetTypes.h>
#include "networkController.hpp"

//Forward declarations:
class World;

/**
 * @brief The GameServer class
 */
class GameServer : public NetworkController
{
public:
    GameServer(int gameport, int playerslots, const std::string scriptDirectory);
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

private:
    std::vector<World*> m_worlds;   //!< Loaded world objects.
    std::string m_scriptDirectory;  //!< Directory to load server scripts from.
};

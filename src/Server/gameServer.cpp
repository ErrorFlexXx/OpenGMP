#include "gameServer.hpp"
#include <utils/logger.h>
#include "WorldObjects/serverWorld.hpp"
#include "ScriptController/scriptController.hpp"

using namespace std;

GameServer::GameServer(int gameport, int playerslots, const string scriptDirectory)
    : NetworkController(gameport, playerslots)
    , m_scriptDirectory(scriptDirectory)
{
}

GameServer::~GameServer()
{
}

/**
 * @brief GameServer::run
 *        Main gameserver loop.
 */
bool GameServer::Startup()
{
    bool result = NetworkController::Startup();

    ScriptController::LoadScriptsFromDir(m_scriptDirectory);

    return result;
}

void GameServer::Shutdown()
{
    LogInfo() << "GameServer is going to shutdown now.";
}

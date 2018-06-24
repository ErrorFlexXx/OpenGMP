#include "gameServer.hpp"
#include <utils/logger.h>
#include "WorldObjects/serverWorld.hpp"
#include "ScriptController/scriptController.hpp"
#include <RakSleep.h>

using namespace std;

GameServer *GameServer::gameServer = nullptr;

GameServer::GameServer(int gameport, int playerslots, const string &scriptDirectory)
    : networkSystem(*this, gameport, playerslots)
    , loginSystem(*this)
    , scriptDirectory(scriptDirectory)
    , serverRunning(true)
    , serverStopped(false)
{
}

GameServer::~GameServer()
{
    LogInfo() << testAttribute;
}

/**
 * @brief GameServer::run
 *        Main gameserver loop.
 */
bool GameServer::Startup()
{
    if(!networkSystem.Startup()) //Start network
        return false;

    //Load scripts from scripts dir
    ScriptController::LoadScriptsFromDir(scriptDirectory);

    return true;
}

void GameServer::Shutdown()
{
    LogInfo() << "GameServer is going to shutdown now.";
    serverRunning = false;
    for(int i = 0; !serverStopped && i < 100; i++) //While serverRunning and time < 10 s
    {
        Process();
        RakSleep(100); //Wait for server shutdown.
    }
    if(serverStopped)
        LogInfo() << "GameServer loop exited normally.";
    else
        LogInfo() << "GameServer loop exited by timeout.";
}

void GameServer::Process()
{
    while(serverRunning)
    {
        bool idle;

        idle = !networkSystem.Update();

        if(idle)
            RakSleep(1);
    }
    serverStopped = true;
}

GameServer &GameServer::GetGameServerInstance()
{
    return *gameServer;
}

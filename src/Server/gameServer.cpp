#include "gameServer.hpp"
#include <utils/logger.h>
#include "WorldObjects/serverWorld.hpp"
#include "Systems/scriptSystem.hpp"
#include <RakSleep.h>

using namespace std;
using namespace OpenGMP;
using namespace OpenGMP::Systems;

GameServer *GameServer::gameServer = nullptr;

GameServer::GameServer(int gameport,
                       int playerslots,
                       const std::string &scriptDirectory,
                       const std::string &keyDir,
                       const std::string &pubKeyfileName,
                       const std::string &privKeyfileName)
    : clientContainer(playerslots)
    , networkSystem(*this, gameport, playerslots, keyDir, pubKeyfileName, privKeyfileName)
    , loginSystem(*this)
    , scriptDirectory(scriptDirectory)
    , serverRunning(true)
    , serverStopped(false)
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
    if(!networkSystem.Startup()) //Start network
    {
        LogError() << "NetworkSystem startup failed! Aborting.";
        return false;
    }

    //Load scripts from scripts dir
    ScriptSystem::LoadScriptsFromDir(scriptDirectory);

    LogInfo() << "GameServer Startup complete!";
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

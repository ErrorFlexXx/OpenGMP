#include "gameServer.hpp"
#include <utils/logger.h>
#include "WorldObjects/serverWorld.hpp"
#include "Systems/scriptSystem.hpp"
#include <RakSleep.h>

using namespace std;
using namespace OpenGMP;

GameServer *GameServer::gameServer = nullptr;

GameServer::GameServer(int gameport,
                       int playerslots,
                       const std::string &scriptDirectory,
                       const std::string &keyDir,
                       const std::string &pubKeyfileName,
                       const std::string &privKeyfileName)
    : clientContainer(playerslots)
    , playerContainer(playerslots)
    , worldContainer(10)
    , networkSystem(*this, gameport, playerslots, keyDir, pubKeyfileName, privKeyfileName)
    , loginSystem(*this)
    , scriptDirectory(scriptDirectory)
    , scriptSystem(*this)
    , menuSystem(*this)
    , terminalSystem(*this)
    , worldSystem(*this)
    , serverRunning(true)
    , serverStopped(false)
{
}

GameServer::~GameServer()
{
    GameServer::gameServer = nullptr;
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
    scriptSystem.LoadScriptsFromDir(scriptDirectory);

    //Install terminal commands
    terminalSystem.AddCommand("reload", "Reloads all scripts from script directory.",
                              [=]() {
        scriptSystem.UnloadScripts();
        scriptSystem.LoadScriptsFromDir(scriptDirectory);
    });
    terminalSystem.AddCommand("help", "Outputs all registered commands with descriptions.",
                              [=]() {
        terminalSystem.GetHelp();
    });

    terminalSystem.Startup();

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
        bool idle = false;

        idle |= !networkSystem.Update();
        idle |= !terminalSystem.Update();

        if(idle) //All systems idle ?
            RakSleep(1); //Then don't waste the cpu
    }
    serverStopped = true;
}

GameServer &GameServer::GetGameServerInstance()
{
    return *gameServer;
}

NetworkSystem &GameServer::GetNetworkSystem()
{
    return networkSystem;
}

LoginSystem &GameServer::GetLoginSystem()
{
    return loginSystem;
}

ScriptSystem &GameServer::GetScriptSystem()
{
    return scriptSystem;
}

MenuSystem &GameServer::GetMenuSystem()
{
    return menuSystem;
}

WorldSystem & GameServer::GetWorldSystem()
{
    return worldSystem;
}

#include "gameServer.hpp"
#include <utils/logger.h>
#include "WorldObjects/serverWorld.hpp"
#include "Systems/scriptSystem.hpp"
#include <RakSleep.h>
#include <thread>

using namespace std;
using namespace OpenGMP;

GameServer *GameServer::gameServer;

GameServer::GameServer(int gameport,
                       int webport,
                       int playerslots,
                       const std::string &scriptDirectory,
                       const std::string &keyDir,
                       const std::string &pubKeyfileName,
                       const std::string &privKeyfileName)
    : clientContainer(playerslots)
    , playerContainer(playerslots)
    , worldContainer(10)
    , networkSystem(*this, gameport, playerslots, keyDir, pubKeyfileName, privKeyfileName)
    , webStatusSystem(*this, webport)
    , loginSystem(*this)
    , scriptDirectory(scriptDirectory)
    , menuSystem(*this)
    , terminalSystem(*this)
    , worldSystem(*this)
    , playerController(*this)
    , scriptSystem(*this) //Init after all other systems
    , serverRunning(true)
    , serverStopped(false)
    , ownerThreadId(std::this_thread::get_id())
{
    GameServer::gameServer = this;
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

    if(!webStatusSystem.Startup()) //Start webserver
    {
        LogError() << "WebStatusSystem startup failed! Aborting.";
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
    serverRunning = false;
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

bool GameServer::IAmOwner() const
{
    if(std::this_thread::get_id() == ownerThreadId)
        return true;
    return false;
}

GameServer &GameServer::GetGameServerInstance()
{
    return *GameServer::gameServer;
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

PlayerController &GameServer::GetPlayerController()
{
    return playerController;
}

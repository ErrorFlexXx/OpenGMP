#include "gameClient.hpp"
#include "Hooks/otherHooks.hpp"
#include "Hooks/hGame.hpp"

using namespace std;
using namespace OpenGMP;
using namespace OpenGMP::Hooks;
using namespace OpenGMP::Systems;

bool GameClient::inited = false;
HINSTANCE GameClient::dllInstance = nullptr;
NetworkSystem GameClient::networkSystem;

void GameClient::Startup(HINSTANCE inst)
{
    if (!inited) //If no instance created yet
    {
        OtherHooks::Hook(); //Controls, SpawnRange, Camera, etc...
        HGame::GetInstance()->DoHook(); //Game Loops
        inited = true;
        dllInstance = inst;
    }
}

void GameClient::Stop()
{
    ;
}
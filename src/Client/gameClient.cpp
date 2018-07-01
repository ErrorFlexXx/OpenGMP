#include "gameClient.hpp"
#include "Hooks/otherHooks.hpp"
#include "Hooks/hGame.hpp"

using namespace std;
using namespace OpenGMP;
using namespace OpenGMP::Hooks;
using namespace OpenGMP::Systems;

HINSTANCE GameClient::dllInstance = nullptr;

GameClient::GameClient()
    : inited(false)
    , networkSystem(*this)
    , loginSystem(*this)
    , inputSystem(*this)
    , menuSystem(*this)
    , hookGame(*this)
{}

void GameClient::Startup(HINSTANCE inst)
{
    if (!inited) //If no instance created yet
    {
        OtherHooks::Hook(); //Controls, SpawnRange, Camera, etc...
        hookGame.Startup(); //Hook Game Loops (Menu & Ingame)
        inited = true;
        dllInstance = inst;
    }
}

void GameClient::Stop()
{
    ;
}
#include "openGMP.hpp"
#include "Hooks/otherHooks.hpp"
#include "Hooks/hGame.hpp"

using namespace std;
using namespace OpenGMP::Hooks;

bool OGMP::inited = false;
HINSTANCE OGMP::dllInstance = nullptr;

void OGMP::Startup(HINSTANCE inst)
{
    if (!inited) //If no instance created yet
    {
        OtherHooks::Hook(); //Controls, SpawnRange, Camera, etc...
        HGame::GetInstance()->DoHook(); //Game Loops
        inited = true;
        dllInstance = inst;
    }
}

void OGMP::Stop()
{
    ;
}
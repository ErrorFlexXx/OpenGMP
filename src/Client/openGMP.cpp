#include "openGMP.hpp"
#define _WINSOCKAPI_ //Stop windows.h from including winsock.h (colliding with RakNet)
#include <windows.h>
#include <iostream>
#include "Hooks/otherHooks.hpp"
#include "Hooks/hGame.hpp"

using namespace std;
using namespace OpenGMP::Hooks;

bool OGMP::inited = false;

void OGMP::Startup()
{
    if (!inited) //If no instance created yet
    {
        OtherHooks::Hook(); //Controls, SpawnRange, Camera, etc...
        HGame::GetInstance()->DoHook(); //Game Loops
        inited = true;
    }
}

void OGMP::Stop()
{
    ;
}
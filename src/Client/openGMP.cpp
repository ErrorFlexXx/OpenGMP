#include "openGMP.hpp"
#define _WINSOCKAPI_ //Stop windows.h from including winsock.h (colliding with RakNet)
#include <windows.h>
#include "Hooks/otherHooks.hpp"
#include "Hooks/hGame.hpp"

using namespace std;
using namespace OpenGMP::Hooks;

OGMP *OGMP::m_instance = nullptr;

OGMP::OGMP()
    : m_worker(&OGMP::Init, this)
{
    m_worker.detach(); //Start independent from creator thread.
}

OGMP * OGMP::GetInstance()
{
    if (m_instance == nullptr) //If no instance created yet
    {
        m_instance = new OGMP(); //Create single instance
    }
    return m_instance; //Return static instance
}

void OGMP::Init()
{
    OtherHooks::Hook(); //Controls, SpawnRange, Camera, etc...
    HGame::GetInstance()->DoHook(); //Game Loops
}

void OGMP::Stop()
{
    ;
}
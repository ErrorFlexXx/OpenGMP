#include "openGMP.hpp"
#define _WINSOCKAPI_ //Stop windows.h from including winsock.h (colliding with RakNet)
#include <windows.h>
#include "Hooks/otherHooks.hpp"

using namespace std;

OpenGMP *OpenGMP::m_instance = nullptr;

OpenGMP::OpenGMP()
    : m_worker(&OpenGMP::Init, this)
{
    m_worker.detach(); //Start independent from creator thread.
}

OpenGMP * OpenGMP::GetInstance()
{
    if (m_instance == nullptr) //If no instance created yet
    {
        m_instance = new OpenGMP(); //Create single instance
    }
    return m_instance; //Return static instance
}

void OpenGMP::Init()
{
    OtherHooks::Hook(); //Controls, SpawnRange, Camera, etc...
}

void OpenGMP::Stop()
{
    ;
}
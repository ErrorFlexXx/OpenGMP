#define _WINSOCKAPI_ //Stop windows.h from including winsock.h (colliding with RakNet)
#include <windows.h>
#include "openGMP.hpp"

OGMP *openGMPInstance = nullptr;

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD reason, LPVOID reserved)
{
    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
        {
            openGMPInstance = OGMP::GetInstance(); //Start OpenGMP instance
            break;
        }
        case DLL_PROCESS_DETACH:
        {
            if(openGMPInstance != nullptr)
                openGMPInstance->Stop();
        }
    }
    return 1;
}
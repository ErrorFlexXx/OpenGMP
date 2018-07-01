#define _WINSOCKAPI_ //Stop windows.h from including winsock.h (colliding with RakNet)
#include <windows.h>
#include "gameClient.hpp"

using namespace OpenGMP;

GameClient gameClient;

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD reason, LPVOID reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
    {
        gameClient.Startup(hInstance);
        break;
    }
    case DLL_PROCESS_DETACH:
    {
        gameClient.Stop();
        break;
    }
    }
    return 1;
}
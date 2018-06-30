#define _WINSOCKAPI_ //Stop windows.h from including winsock.h (colliding with RakNet)
#include <windows.h>
#include "gameClient.hpp"

using namespace OpenGMP;

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD reason, LPVOID reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
    {
        GameClient::Startup(hInstance);
        break;
    }
    case DLL_PROCESS_DETACH:
    {
        GameClient::Stop();
        break;
    }
    }
    return 1;
}
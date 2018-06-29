#pragma once

#define _WINSOCKAPI_ //Stop windows.h from including winsock.h (colliding with RakNet)
#include <windows.h>

class GameClient
{
public:
    static void Startup(HINSTANCE inst);  //!< Initializes the game client
    static void Stop();     //!< Stops the OpenGMP instance (do cleanup..)
    
    static HINSTANCE dllInstance;

private:
    GameClient();                   //!< Object creation not from outside allowed!
    GameClient(const GameClient&);  //!< No Copy allowed!
    
    static bool inited;
};
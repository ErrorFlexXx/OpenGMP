#pragma once

#define _WINSOCKAPI_ //Stop windows.h from including winsock.h (colliding with RakNet)
#include <windows.h>

class OGMP
{
public:
    static void Startup(HINSTANCE inst);  //!< Initializes OpenGMP
    static void Stop();     //!< Stops the OpenGMP instance (do cleanup..)
    
    static HINSTANCE dllInstance;

private:
    OGMP();                  //!< Object creation not from outside allowed!
    OGMP(const OGMP&);    //!< No Copy allowed!
    
    static bool inited;
};
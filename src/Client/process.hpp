#pragma once

#define _WINSOCKAPI_ //Stop windows.h from including winsock.h (colliding with RakNet)
#include <windows.h>

class Process
{
public:
    static bool IsForeground();
    static DWORD m_procId;
};
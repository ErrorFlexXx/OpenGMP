#pragma once

#include <Client/Objects/CDetour.h>
#include <string>
#define _WINSOCKAPI_ //Stop windows.h from including winsock.h (colliding with RakNet)
#include <windows.h>

namespace OpenGMP
{
    namespace Systems
    {
        HBITMAP WINAPI DetourLoadBitmap(HINSTANCE inst, LPCSTR lpBitmapName);

        class WindowSystem
        {
        public:
            static void SetWindowTitle(const std::string &title);
            static void UpdateWindowIcon();
            static bool IsForeground();

        private:
            static DWORD procId;
            static CDetour splashDetour;
        };
    }
}
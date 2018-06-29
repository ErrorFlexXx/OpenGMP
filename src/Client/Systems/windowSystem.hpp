#pragma once

#include "../hook.hpp"
#include <string>
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
            static Hook splashHook;
        };
    }
}
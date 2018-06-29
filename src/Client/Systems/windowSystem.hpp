#pragma once

#include <string>
#include <windows.h>

namespace OpenGMP
{
    namespace Systems
    {
        class WindowSystem
        {
        public:
            static void SetWindowTitle(const std::string &title);
            static void UpdateWindowIcon();
            static bool IsForeground();

        private:
            static DWORD procId;
        };
    }
}
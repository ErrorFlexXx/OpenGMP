#include "windowSystem.hpp"
#include "../openGMP.hpp"

using namespace OpenGMP::Systems;

DWORD WindowSystem::procId = GetCurrentProcessId();

void WindowSystem::SetWindowTitle(const std::string &title)
{
    if (IsForeground())
    {
        SetWindowTextA(GetForegroundWindow(), title.c_str());
    }
}

void WindowSystem::UpdateWindowIcon()
{
    if (IsForeground() && OGMP::dllInstance)
    {
        HWND wnd = GetForegroundWindow();
        HICON hicon = (HICON)LoadImage(OGMP::dllInstance, MAKEINTRESOURCE(102), IMAGE_ICON, 32, 32, LR_SHARED);
        if (hicon)
        {
            SendMessage(wnd, (UINT)WM_SETICON, ICON_SMALL, (LPARAM)hicon);
            SendMessage(wnd, (UINT)WM_SETICON, ICON_BIG,   (LPARAM)hicon);
        }
    }
}

bool WindowSystem::IsForeground()
{
    DWORD foregroundProcId;
    HWND fWnd = GetForegroundWindow();
    GetWindowThreadProcessId(fWnd, &foregroundProcId);
    return foregroundProcId == procId;
}
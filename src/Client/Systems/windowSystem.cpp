#include "windowSystem.hpp"
#include "../openGMP.hpp"
#include "../OpenGMP/OpenGMP/resource.h"

using namespace OpenGMP::Systems;

DWORD WindowSystem::procId = GetCurrentProcessId();
Hook WindowSystem::splashHook(true, (DWORD)GetProcAddress(LoadLibrary("user32.dll"), "LoadBitmapA"), (DWORD)&DetourLoadBitmap);

HBITMAP WINAPI OpenGMP::Systems::DetourLoadBitmap(HINSTANCE inst, LPCSTR lpBitmapName)
{
    return (HBITMAP)LoadImageA(OGMP::dllInstance, MAKEINTRESOURCE(Splash), IMAGE_BITMAP, 0, 0, LR_SHARED);
}

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
        HICON hicon = (HICON)LoadImage(OGMP::dllInstance, MAKEINTRESOURCE(APP_ICON), IMAGE_ICON, 32, 32, LR_SHARED);
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
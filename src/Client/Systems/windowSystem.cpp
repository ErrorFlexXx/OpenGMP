#include "windowSystem.hpp"
#include "../gameClient.hpp"
#include "../OpenGMP/OpenGMP/resource.h"

using namespace OpenGMP;
using namespace OpenGMP::Systems;

DWORD WindowSystem::procId = GetCurrentProcessId();
CDetour WindowSystem::splashDetour((DWORD)GetProcAddress(LoadLibrary("user32.dll"), "LoadBitmapA"), 5, (DWORD)&DetourLoadBitmap, FASTHOOK);

HBITMAP WINAPI OpenGMP::Systems::DetourLoadBitmap(HINSTANCE inst, LPCSTR lpBitmapName)
{
    return (HBITMAP)LoadImageA(GameClient::dllInstance, MAKEINTRESOURCE(Splash), IMAGE_BITMAP, 0, 0, LR_SHARED);
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
    if (IsForeground() && GameClient::dllInstance)
    {
        HWND wnd = GetForegroundWindow();
        HICON hicon = (HICON)LoadImage(GameClient::dllInstance, MAKEINTRESOURCE(APP_ICON), IMAGE_ICON, 32, 32, LR_SHARED);
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
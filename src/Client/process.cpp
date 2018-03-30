#include "process.hpp"

DWORD Process::m_procId = GetCurrentProcessId();

bool Process::IsForeground()
{
    DWORD fProcId;
    HWND fWnd = GetForegroundWindow();
    GetWindowThreadProcessId(fWnd, &fProcId);
    return fProcId == m_procId;
}
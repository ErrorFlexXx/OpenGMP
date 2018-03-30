#include "hook.hpp"

/* Static class members: */
const int Hook::m_HOOK_LENGTH = 6;

Hook::Hook(bool fastHook, DWORD origAddress, DWORD targetAddress)
    : m_targetAddress(targetAddress)
    , m_origAddress(origAddress)
    , m_isHooked(fastHook)
{
    if (fastHook)
        this->DoHook();
}

Hook::ReturnCode Hook::DoHook()
{
    unsigned char hookHead[6] = {
        0xE9,                   //JMP
        0x00, 0x00, 0x00, 0x00, //Space for the address
        0xC3                    //RET
    };
    DWORD protectionBackup; //VirtualProtect protection reminder
    unsigned int jmpOffset = (m_targetAddress - m_origAddress - 5); //Calculate offset for jump ((to)-(from)-5)
    memcpy(hookHead + 1, &jmpOffset, 4); //Save offset in hook head assembly code
    SIZE_T backupBytesRead; //Amount of successfully read backup bytes
    SIZE_T hookBytesWritten;//Amount of successfully written hook bytes
    int result; //Result of function returns

    result = ReadProcessMemory(GetCurrentProcess(), (LPVOID)m_origAddress, (LPVOID)m_origHeader, m_HOOK_LENGTH, &backupBytesRead);

    if (!result || backupBytesRead != m_HOOK_LENGTH) //Failed or read not all bytes requested ?
    {
        return CHOOK_BACKUP_READ_FAILED; //Return with error and stop hooking.
    }

    result = GetWritePermissions(&protectionBackup);
    if (!result) //If we can't get the permission to write
    {
        return CHOOK_SET_PERMS_FAILED; //Return with error and stop hooking.
    }

    result = WriteProcessMemory(GetCurrentProcess(), (LPVOID)m_origAddress, hookHead, m_HOOK_LENGTH, &hookBytesWritten);
    if (!result || hookBytesWritten != m_HOOK_LENGTH) //Failed or can't write all bytes requested ?
    {
        return CHOOK_HOOK_WRITE_FAILED;
    }
    m_isHooked = true; //Function is hooked now.

    result = RestorePermissions(protectionBackup);
    if (!result)
    {
        return CHOOK_SET_PERMS_FAILED;
    }
    return CHOOK_SUCCESS;
}

Hook::ReturnCode Hook::UndoHook()
{
    DWORD protectionBackup;  //VirtualProtect protection reminder
    SIZE_T hookBytesWritten; //Amount of successfully written hook bytes
    int result;             //Result of function/method calls

    result = GetWritePermissions(&protectionBackup);
    if (!result) //If we can't get the permission to write
    {
        return CHOOK_SET_PERMS_FAILED; //Return with error and stop hooking.
    }

    result = WriteProcessMemory(GetCurrentProcess(), (LPVOID)m_origAddress, m_origHeader, m_HOOK_LENGTH, &hookBytesWritten);
    if (!result || hookBytesWritten != m_HOOK_LENGTH) //Failed or can't write all bytes requested ?
    {
        return CHOOK_HOOK_WRITE_FAILED;
    }
    m_isHooked = false; //Function is no longer hooked now.

    result = RestorePermissions(protectionBackup);
    if (!result) //If we can't get the permission to write
    {
        return CHOOK_SET_PERMS_FAILED; //Return with error and stop hooking.
    }
    return CHOOK_SUCCESS;
}

void OneWayHook(DWORD originAddress, DWORD destAddress)
{
    BYTE hookHead[6] = {
        0xE9,                   //JMP
        0x00, 0x00, 0x00, 0x00, //Space for the address
        0xC3                    //RET
    };
    DWORD jmpOffset = (destAddress - originAddress - 5); //Calculate offset for jump ((to)-(from)-5)
    memcpy(hookHead + 1, &jmpOffset, 4); //Save offset in hook head assembly code
    WriteProcessMemory(GetCurrentProcess(), (LPVOID)originAddress, hookHead, 6, 0);
}

bool Hook::IsHooked()
{
    return m_isHooked;
}

BOOL Hook::GetWritePermissions(DWORD *protectionBackup)
{
    int result = VirtualProtect(LPVOID(m_origAddress), (SIZE_T)m_HOOK_LENGTH, //Get write permissions on process.
        PAGE_EXECUTE_READWRITE, protectionBackup);
    return result;
}

BOOL Hook::RestorePermissions(DWORD &protectionBackup)
{
    DWORD dummy; //Dummy var to satisfy VirtualProtect, not being able to discard the backup (Will fail otherwise).
    BOOL result = VirtualProtect(LPVOID(m_origAddress), (SIZE_T)m_HOOK_LENGTH, //Restore old permissions
        protectionBackup, &dummy);
    return result;
}
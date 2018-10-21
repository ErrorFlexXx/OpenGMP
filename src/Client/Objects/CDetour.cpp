#include "CDetour.h"
#include <stdio.h>

using namespace std;
using namespace OpenGMP;

map<DWORD, CDetour*> CDetour::detourPool; //Pool of registered detours

CDetour::CDetour(DWORD originAddr, size_t hookLength, void *detourAddr, int fastHook)
    : originAddr(originAddr)
    , hookLength(hookLength)
    , detourAddr((DWORD)detourAddr)
    , isSet(0)
{
    if (fastHook)
        Activate();
}

int CDetour::Activate()
{
    if (!isSet)
    {
        isSet = 1;
        if (SetupTrampoline() != 0)
        {
            fprintf(stderr, "Error in setup of trampoline!\n");
            return -1; //Stop here
        }
        if (SetupDetour() != 0)
        {
            fprintf(stderr, "Error in setup of detour!\n");
            return -1; //Stop here
        }
        return RegisterDetour();
    }
    return -1;
}

DWORD CDetour::OriginalCallAddress(DWORD originAddr)
{
    map<DWORD, CDetour*>::iterator it = detourPool.find(originAddr);
    if (it != detourPool.end()) //Found ?
        return it.operator*().second->trampolineAddr;
    return 0;
}

int CDetour::SetupTrampoline()
{
    DWORD oldProt; //Old protection (VirtualProtects needs this)
    DWORD relJmp;

    trampolineAddr = (DWORD) new unsigned char[hookLength + 5]; //Get memory for original func header
    if (trampolineAddr == 0)
    {
        fprintf(stderr, "SetupTrampoline: Can't get memory!");
        return 1; //Error - Can't get memory!
    }
    if (0 != memcpy_s((void*)trampolineAddr, hookLength + 5, (void*)originAddr, hookLength))
    {
        fprintf(stderr, "SetupTrampoline: memcpy_s failed!");
        return 1; //Error - Copy failed
    }    
    ((unsigned char*)trampolineAddr)[hookLength] = 0xE9; //Write Jmp
    relJmp = originAddr - trampolineAddr - 5;
    *(DWORD*)((unsigned char*)trampolineAddr + hookLength + 1) = relJmp; //Write JMP argument
    if (0 == VirtualProtect((LPVOID)trampolineAddr, hookLength + 5, PAGE_EXECUTE_READWRITE, &oldProt))
    {
        fprintf(stderr, "SetupTrampoline: Virtual Protect failed!");
        return 1; //Error - Can't set execute protection for trampoline
    }
    return 0; //Success
}

int CDetour::SetupDetour()
{
    unsigned char writeBuffer[5];

    writeBuffer[0] = 0xE9; //JMP
    *((DWORD*)(writeBuffer + 1)) = detourAddr - originAddr - 5;
    if (0 == WriteProcessMemory(GetCurrentProcess(), (LPVOID)originAddr, (LPVOID)writeBuffer, 5, 0))
        return 1; //Error - Can't write to process.
    return 0;
}

int CDetour::RegisterDetour()
{
    detourPool.insert(make_pair(originAddr, this));
    return 0;
}
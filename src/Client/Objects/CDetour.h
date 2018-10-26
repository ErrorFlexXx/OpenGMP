#pragma once

#define _WINSOCKAPI_ //Stop windows.h from including winsock.h (colliding with RakNet)
#include <windows.h>
#include <map>

#define FASTHOOK    1
#define GetMemberFuncPtr(dst, src)  __asm { lea eax, src} \
                                    __asm { mov dst, eax }

/**
 * @brief CDetour class
 * Class to detour functions and call the original afterwards or not.
 */
namespace OpenGMP
{
    class CDetour
    {
    public:
        CDetour(DWORD originAddr, size_t hookLength, DWORD detourAddr, int fastHook = 0); //Setup a new detour
        int Activate();
        static DWORD OriginalCallAddress(DWORD detourAddress); //Get the address to call the original function.

    private:
        DWORD originAddr;       //!< Address of to be detoured function
        DWORD detourAddr;       //!< Address to replacment function
        DWORD trampolineAddr;   //!< Address to tramp. to call original function.
        size_t hookLength;      //!< Length of hook header (min 5, has to align with assembly)
        static std::map<DWORD, CDetour*> detourPool; //!< Pool of activated detours (To get OriginalCallAddress)
        int isSet;              //!< Reminder, if this detour is set (double setup will cause crash.)

        int SetupTrampoline();  //!< Setup of a trampoline to call the original function.
        int SetupDetour();      //!< Setup the jump from original to detour.
        int RegisterDetour();   //!< Register this CDetour in detourPool.
    };
}
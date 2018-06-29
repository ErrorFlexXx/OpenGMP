#pragma once

#define _WINSOCKAPI_ //Stop windows.h from including winsock.h (colliding with RakNet)
#include <windows.h>

/**
* @brief The CHook class
*  CHook is class that covers all relevant informations to hook a function and actually
*  can apply a hook and revert a placed hook. This class is designed for windows.
* @date 03-17-2018
*/
class Hook
{
public:
    /**
    *  @brief ReturnCode is an enumeration containing all possible return values from this class.
    **/
    enum ReturnCode : unsigned char
    {
        CHOOK_SUCCESS = 0,			//!< is returned on success
        CHOOK_BACKUP_READ_FAILED,   //!< is returned if ReadProcessMemory failed
        CHOOK_HOOK_WRITE_FAILED,    //!< is returned if WriteProcessMemory failed
        CHOOK_SET_PERMS_FAILED      //!< is returned if VirtualProtect can't change permissions
    };

    Hook(bool fastHook, DWORD origAddress, DWORD targetAddress);

    /**
     * @brief Hook is a method to apply a hook.
     */
    ReturnCode DoHook();

    /**
     * @brief DeHook is a method to revert a placed hook.
     */
    ReturnCode UndoHook();

    /**
     * @brief IsHooked is a method to get the current state of the hook.
     */
    bool IsHooked();

private:
    DWORD m_origAddress;		    //!< Address to place the hook at.
    DWORD m_targetAddress;          //!< Address the hook show point to.
    unsigned char m_origHeader[6];  //!< Original bytes overriden with hook jump.
    bool m_isHooked;                //!< Flag to indicate, if the hook was placed.
    static const int m_HOOK_LENGTH; //!< Length of the placed hook instructions.

    /**
     * @brief gets write permissions on the process bytes and stores the old protection.
     */
    BOOL GetWritePermissions(DWORD *protectionBackup);

    /**
     * @brief restores the protectionBackup permissions on the process bytes.
     */
    BOOL RestorePermissions(DWORD &protectionBackup);
};
#include "otherHooks.hpp"
#define _WINSOCKAPI_ //Stop windows.h from including winsock.h (colliding with RakNet)
#include <windows.h>

using namespace OpenGMP;

const unsigned char OtherHooks::SkipIntroVideos[] = { 0xE9, 0xA3, 0x00, 0x00, 0x00 };
const unsigned char OtherHooks::SkipSavegamemManagerInit[] = { 0xEB, 0x35 };
const unsigned char OtherHooks::SkipOutputUnitsInit[] = { 0xC3 };
const unsigned char OtherHooks::SkipFallingAnimationStart[] = { 0xEB, 0x15 };
const unsigned char OtherHooks::SkipDropUnconscious[] = { 0xC2, 0x08, 0x00 };
const unsigned char OtherHooks::SkipDropWeaponOnDeath[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
const unsigned char OtherHooks::SkipGothicControl1[] = { 0xE9, 0x3E, 0x04, 0x00, 0x00 };
const unsigned char OtherHooks::SkipGothicControl2[] = { 0xC3, 0xE8, 0x8B, 0xE6, 0xFF, 0xFF, 0xC3 };
const unsigned char OtherHooks::SkipGothicControl3[] = { 0x90, 0x90, 0x90, 0x90, 0x90 };
const unsigned char OtherHooks::ReduceLoadingScreenWait[] = { 0xD8, 0x1D, 0xB4, 0x04, 0x83, 0x00 };
const float OtherHooks::SpawnManagerInsertRange = 18000.0f;
const float OtherHooks::SpawnManagerRemoveRange = 20000.0f;
const unsigned char OtherHooks::RainDropsBlockedByVobs[] = { 0xE0 };
const unsigned char OtherHooks::SkipInitScripts[] = { 0xC3 };
const unsigned char OtherHooks::SkipStartupScripts[] = { 0xC3 };
const unsigned char OtherHooks::BleedWithLower25Health[] = { 0xDC, 0x0D, 0x30, 0xEB, 0x82, 0x00 };
const unsigned char OtherHooks::DisablePlayerAI[] = { 0xE9, 0xB0, 0x01, 0x00, 0x00 };
const unsigned char OtherHooks::DisableFocusHighlighting[] = { 0xE9, 0x89, 0, 0, 0, 0x90 };
const unsigned char OtherHooks::SkipoCAniCtrl_HumanCreateHitEnemyCheck[] = { 0x90, 0x90, 0x90, 0x90, 0x90,
                                                                             0x90, 0x90, 0x90, 0x90, 0x90,
                                                                             0x90, 0x90 };
const unsigned char OtherHooks::SkipoCNPCProcessNPC[] = { 0xC3 };
const unsigned char OtherHooks::SkipDamage[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
const unsigned char OtherHooks::SkipTime[] = { 0xC3 };
const unsigned char OtherHooks::SkipDeadCharacterDeletion[] = { 0x33, 0xC0, 0xC2, 0x04, 0x00 };
const unsigned char OtherHooks::SkipNPCIsInRoutineCheck[] = { 0x31, 0xC0, 0xC3 };
const unsigned char OtherHooks::SkipPerceptionCheck[] = { 0xEB, 0x21 };
const unsigned char OtherHooks::SkipDoAIState[] = { 0x31, 0xC0, 0xC3 };
const unsigned char OtherHooks::SkipDialogCams[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
const unsigned char OtherHooks::SkipVisualVdfsInit[] = { 0xE9, 0x8C, 0x00, 0x00, 0x00 };
const unsigned char OtherHooks::SkipForcedVdfsInit[] = { 0xE9, 0x96, 0x02, 0x00, 0x00 };

void OtherHooks::Hook()
{
    HANDLE currentProcess = GetCurrentProcess();   
    WriteProcessMemory(currentProcess, (LPVOID)0x0042687F, SkipIntroVideos, 5, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x00424EE2, SkipSavegamemManagerInit, 2, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x005DEA4B, SkipOutputUnitsInit, 1, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x006B5A44, SkipFallingAnimationStart, 2, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x00735EB0, SkipDropUnconscious, 3, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x00736898, SkipDropWeaponOnDeath, 7, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x004D3DF6, SkipGothicControl1, 5, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x004D5700, SkipGothicControl2, 7, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x006C8A71, SkipGothicControl3, 5, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x006C873D, ReduceLoadingScreenWait, 6, NULL);
    *((float*)(0x008BACD0)) = SpawnManagerInsertRange;
    *((float*)(0x008BACD4)) = SpawnManagerRemoveRange;
    WriteProcessMemory(currentProcess, (LPVOID)0x005E227A, RainDropsBlockedByVobs, 1, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x006C1F60, SkipInitScripts, 1, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x006C1C70, SkipStartupScripts, 1, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x0069C2DA, BleedWithLower25Health, 6, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x0069C08B, DisablePlayerAI, 5, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x0069BFCB, DisableFocusHighlighting, 6, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x006B0896, SkipoCAniCtrl_HumanCreateHitEnemyCheck, 12, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x0073E480, SkipoCNPCProcessNPC, 1, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x0066CAC9, SkipDamage, 10, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x00780D80, SkipTime, 1, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x007792E0, SkipDeadCharacterDeletion, 5, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x0076D8A0, SkipNPCIsInRoutineCheck, 3, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x0069C247, SkipPerceptionCheck, 2, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x0076D1A0, SkipDoAIState, 3, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x004A059C, SkipDialogCams, 7, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x44AEDF, SkipVisualVdfsInit, 5, NULL);
    WriteProcessMemory(currentProcess, (LPVOID)0x00470846, SkipForcedVdfsInit, 5, NULL);
}
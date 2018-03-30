#pragma once

class OtherHooks
{
public:
    static void Hook();
private:
    OtherHooks(); //Abstract class

    static const unsigned char OtherHooks::SkipIntroVideos[];
    static const unsigned char OtherHooks::SkipSavegamemManagerInit[];
    static const unsigned char OtherHooks::SkipOutputUnitsInit[];
    static const unsigned char OtherHooks::SkipFallingAnimationStart[];
    static const unsigned char OtherHooks::SkipDropUnconscious[];
    static const unsigned char OtherHooks::SkipDropWeaponOnDeath[];
    static const unsigned char OtherHooks::SkipGothicControl1[];
    static const unsigned char OtherHooks::SkipGothicControl2[];
    static const unsigned char OtherHooks::SkipGothicControl3[];
    static const unsigned char OtherHooks::ReduceLoadingScreenWait[];
    static const float OtherHooks::SpawnManagerInsertRange;
    static const float OtherHooks::SpawnManagerRemoveRange;
    static const unsigned char OtherHooks::RainDropsBlockedByVobs[];
    static const unsigned char OtherHooks::SkipInitScripts[];
    static const unsigned char OtherHooks::SkipStartupScripts[];
    static const unsigned char OtherHooks::BleedWithLower25Health[];
    static const unsigned char OtherHooks::DisablePlayerAI[];
    static const unsigned char OtherHooks::DisableFocusHighlighting[];
    static const unsigned char OtherHooks::SkipoCAniCtrl_HumanCreateHitEnemyCheck[];
    static const unsigned char OtherHooks::SkipoCNPCProcessNPC[];
    static const unsigned char OtherHooks::SkipDamage[];
    static const unsigned char OtherHooks::SkipTime[];
    static const unsigned char OtherHooks::SkipDeadCharacterDeletion[];
    static const unsigned char OtherHooks::SkipNPCIsInRoutineCheck[];
    static const unsigned char OtherHooks::SkipPerceptionCheck[];
    static const unsigned char OtherHooks::SkipDoAIState[];
    static const unsigned char OtherHooks::SkipDialogCams[];
};
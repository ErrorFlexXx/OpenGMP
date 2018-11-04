#pragma once

namespace OpenGMP
{
    class OtherHooks
    {
    public:
        static void Hook();
    private:
        OtherHooks(); //Abstract class

        static const unsigned char SkipIntroVideos[];
        static const unsigned char SkipSavegamemManagerInit[];
        static const unsigned char SkipOutputUnitsInit[];
        static const unsigned char SkipFallingAnimationStart[];
        static const unsigned char SkipDropUnconscious[];
        static const unsigned char SkipDropWeaponOnDeath[];
        static const unsigned char SkipGothicControl1[];
        static const unsigned char SkipGothicControl2[];
        static const unsigned char SkipGothicControl3[];
        static const unsigned char ReduceLoadingScreenWait[];
        static const float SpawnManagerInsertRange;
        static const float SpawnManagerRemoveRange;
        static const unsigned char RainDropsBlockedByVobs[];
        static const unsigned char SkipInitScripts[];
        static const unsigned char SkipStartupScripts[];
        static const unsigned char BleedWithLower25Health[];
        static const unsigned char DisablePlayerAI[];
        static const unsigned char DisableFocusHighlighting[];
        static const unsigned char SkipoCAniCtrl_HumanCreateHitEnemyCheck[];
        static const unsigned char SkipoCNPCProcessNPC[];
        static const unsigned char SkipDamage[];
        static const unsigned char SkipTime[];
        static const unsigned char SkipDeadCharacterDeletion[];
        static const unsigned char SkipNPCIsInRoutineCheck[];
        static const unsigned char SkipPerceptionCheck[];
        static const unsigned char SkipDoAIState[];
        static const unsigned char SkipDialogCams[];
        static const unsigned char SkipVisualVdfsInit[];
        static const unsigned char SkipForcedVdfsInit[];
    };
}
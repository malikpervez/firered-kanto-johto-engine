#include "global.h"

#ifdef FIRERED
#include "battle.h"
#include "event_data.h"
#include "johto_campaign.h"
#include "rainbow_story.h"
#include "regional_save.h"
#include "script.h"
#include "constants/johto_ids.h"
#include "constants/rainbow_story.h"

STATIC_ASSERT(RAINBOW_STORY_FLAGS_FIRST > BUILD_FLAGS_END, RainbowStoryBelowNativeEnd);
STATIC_ASSERT(RAINBOW_STORY_FLAGS_LAST < ENGINE_FLAGS_START, RainbowStoryBelowEngineFlags);
STATIC_ASSERT(RAINBOW_STORY_FLAGS_FIRST > DAILY_FLAGS_END, RainbowStoryOutsideDailyFlags);
STATIC_ASSERT(FLAG_LG_MOLTRES_CAUGHT - FLAG_LG_ARTICUNO_DEFEATED + 1 == LG_REPLICA_COUNT * 2, RainbowStoryReplicaPairs);

static u16 ReplicaResult(u16 replica)
{
    u16 flag;
    if (replica >= LG_REPLICA_COUNT)
        return LG_REPLICA_UNRESOLVED;
    flag = FLAG_LG_ARTICUNO_DEFEATED + replica * 2;
    return FlagGet(flag) | (FlagGet(flag + 1) << 1);
}

static bool8 ReceiptsValid(void)
{
    u32 i;
    // Unknown occupied bits and impossible two-bit outcomes are never erased.
    if (FlagGet(0x91E) || FlagGet(0x91F))
        return FALSE;
    for (i = 0; i < LG_REPLICA_COUNT; i++)
        if (ReplicaResult(i) > LG_REPLICA_CAUGHT)
            return FALSE;
    return TRUE;
}

bool8 RainbowStory_IsReady(void)
{
    return gSaveBlock1Ptr != NULL
        && FlagGet(FLAG_RAINBOW_STORY_ADOPTED)
        && FlagGet(FLAG_LG_LEGACY_CLASSIFIED)
        && ReceiptsValid();
}

static void ClassifyLegacyLugia(void)
{
    if (JohtoCampaign_IsSeeded())
    {
        u16 lugia = VarGet(JOHTO_VAR_COMPLETED_LUGIA);
        u16 branch = VarGet(JOHTO_VAR_LUGIA_OR_HOOH);
        // A caught receipt is reliable. Silver's completed theater establishes
        // the old Whirl story resolution. Gold state3 alone is suppression.
        // Old Gold state4 can also conceal a past defeat: exempt it honestly,
        // without inventing played battles or consuming the native encounter.
        if (FlagGet(JOHTO_FLAG_CAUGHT_LUGIA)
         || (branch == 1 && VarGet(JOHTO_VAR_ECRUTEAK_CITY_THEATER) >= 8 && (lugia == 3 || lugia == 4))
         || (branch == 2 && lugia == 4))
            FlagSet(FLAG_LG_LEGACY_EXEMPT);
    }
    FlagSet(FLAG_LG_LEGACY_CLASSIFIED);
}

bool8 RainbowStory_TryAdopt(void)
{
    u16 flag;
    if (RainbowStory_IsReady())
        return TRUE;
    if (gSaveBlock1Ptr == NULL || gSaveBlock3Ptr == NULL
     || !RegionalSave_FoundationValid((const u8 *)gSaveBlock3Ptr))
        return FALSE;
    // Only the known blank old allocation is adopted. Do not reset unknown
    // development state, infer opening memories, or seed Johto to store Kanto.
    for (flag = RAINBOW_STORY_FLAGS_FIRST; flag <= RAINBOW_STORY_FLAGS_LAST; flag++)
        if (FlagGet(flag))
            return FALSE;
    ClassifyLegacyLugia();
    FlagSet(FLAG_RAINBOW_STORY_ADOPTED);
    return TRUE;
}

void RainbowStory_NewGame(void)
{
    // Called only after native new-game initialization has cleared all flags.
    // Returning old trainers never become members of the fresh opening cohort.
    FlagSet(FLAG_LG_LEGACY_CLASSIFIED);
    FlagSet(FLAG_RB_FRESH_COHORT);
    FlagSet(FLAG_RAINBOW_STORY_ADOPTED);
}

u16 RainbowStory_GetReplicaResult(u16 replica)
{
    return RainbowStory_IsReady() ? ReplicaResult(replica) : LG_REPLICA_UNRESOLVED;
}

bool8 RainbowStory_AllReplicasResolved(void)
{
    u32 i;
    if (!RainbowStory_IsReady())
        return FALSE;
    for (i = 0; i < LG_REPLICA_COUNT; i++)
        if (ReplicaResult(i) == LG_REPLICA_UNRESOLVED)
            return FALSE;
    return TRUE;
}

void Special_RainbowStoryAdopt(void)
{
    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    gSpecialVar_Result = RainbowStory_TryAdopt();
}

void Special_RainbowStoryAdoptWhirl(void)
{
    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    gSpecialVar_Result = RainbowStory_TryAdopt();
}

void Special_RainbowStoryIsReady(void)
{
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = RainbowStory_IsReady();
}

void Special_RainbowStoryGetReplicaResult(void)
{
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = RainbowStory_GetReplicaResult(gSpecialVar_0x8004);
}

void Special_RainbowStoryRecordReplicaResult(void)
{
    u16 replica = gSpecialVar_0x8004;
    u16 flag;
    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    gSpecialVar_Result = FALSE;
    // Call only immediately after this replica's normal wild-battle return.
    // Loss, flee, teleport, an unfinished battle and unknown outcomes do not
    // create a receipt. The ordinary party/PC delivery path owns captures.
    if (!RainbowStory_IsReady() || replica >= LG_REPLICA_COUNT
     || !FlagGet(FLAG_LG_ATTACK_SEEN)
     || FlagGet(FLAG_LG_LEGACY_EXEMPT) || FlagGet(FLAG_LG_FINAL_RESOLVED)
     || ReplicaResult(replica) != LG_REPLICA_UNRESOLVED)
        return;
    flag = FLAG_LG_ARTICUNO_DEFEATED + replica * 2;
    if (gBattleOutcome == B_OUTCOME_WON)
        FlagSet(flag);
    else if (gBattleOutcome == B_OUTCOME_CAUGHT)
        FlagSet(flag + 1);
    else
        return;
    gSpecialVar_Result = TRUE;
}

void Special_RainbowStoryAllReplicasResolved(void)
{
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = RainbowStory_AllReplicasResolved();
}
#endif

#include "global.h"

#include "battle.h"
#include "character_story.h"
#include "event_data.h"
#include "follower_npc.h"
#include "friends_story.h"
#include "johto_campaign.h"
#include "load_save.h"
#include "pokemon.h"
#include "regional_save.h"
#include "script.h"
#include "constants/battle.h"
#include "constants/character_story.h"
#include "constants/friends_story.h"
#include "constants/johto_ids.h"
#include "constants/map_groups.h"
#include "constants/species.h"

STATIC_ASSERT(FRIENDS_STORY_FLAGS_FIRST > BUILD_FLAGS_END, FriendsAboveNativeFlags);
STATIC_ASSERT(FRIENDS_STORY_FLAGS_LAST < ENGINE_FLAGS_START, FriendsBelowEngineFlags);
STATIC_ASSERT(FRIENDS_STORY_FLAGS_FIRST > DAILY_FLAGS_END, FriendsOutsideDailyFlags);
STATIC_ASSERT(FRIENDS_STORY_SEEN_LAST - FRIENDS_STORY_SEEN_FIRST + 1 == FRIENDS_STORY_SCENE_COUNT, FriendsSceneReceipts);
STATIC_ASSERT(FRIENDS_STORY_TRAINER_LAST < MAX_TRAINERS_COUNT, FriendsTrainerFlagsAllocated);

static u16 ReadBits(u16 first, u16 count)
{
    u16 value = 0, i;
    for (i = 0; i < count; i++)
        value |= FlagGet(first + i) << i;
    return value;
}

static void WriteBits(u16 first, u16 count, u16 value)
{
    u16 i;
    for (i = 0; i < count; i++)
    {
        if (value & (1 << i))
            FlagSet(first + i);
        else
            FlagClear(first + i);
    }
}

static bool8 Seen(u16 scene)
{
    return scene > 0 && scene <= FRIENDS_STORY_SCENE_COUNT
        && FlagGet(FRIENDS_STORY_SEEN_FIRST + scene - 1);
}

static u16 CurrentMap(void)
{
    return (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
}

bool8 FriendsStory_AllocationValid(void)
{
    u16 flag, stage, loss, scene;
    if (gSaveBlock1Ptr == NULL)
        return FALSE;
    if (!FlagGet(FLAG_FRIENDS_STORY_ADOPTED))
    {
        for (flag = FRIENDS_STORY_FLAGS_FIRST; flag <= FRIENDS_STORY_FLAGS_LAST; flag++)
            if (FlagGet(flag))
                return FALSE;
        return TRUE;
    }
    stage = ReadBits(FRIENDS_STORY_STAGE_FIRST, FRIENDS_STORY_STAGE_BITS);
    loss = ReadBits(FRIENDS_STORY_LOSS_FIRST, FRIENDS_STORY_LOSS_BITS);
    if (stage > FRIENDS_STORY_SCENE_COUNT || loss > 14)
        return FALSE;
    for (flag = FRIENDS_STORY_UNUSED_FIRST; flag <= FRIENDS_STORY_FLAGS_LAST; flag++)
        if (FlagGet(flag))
            return FALSE;
    for (scene = 1; scene <= FRIENDS_STORY_SCENE_COUNT; scene++)
        if (Seen(scene) && scene > stage)
            return FALSE;
    if ((FlagGet(FLAG_FRIENDS_FAREWELL_INVITED) && stage < 21)
     || (Seen(21) && !FlagGet(FLAG_FRIENDS_FAREWELL_INVITED))
     || (FlagGet(FLAG_FRIENDS_REUNION_ARMED) && !Seen(21))
     || (stage == 22 && (!Seen(21) || !FlagGet(FLAG_FRIENDS_REUNION_ARMED))))
        return FALSE;
    return TRUE;
}

bool8 FriendsStory_IsReady(void)
{
    return gSaveBlock1Ptr != NULL && FlagGet(FLAG_FRIENDS_STORY_ADOPTED)
        && FriendsStory_AllocationValid() && CharacterStory_IsReady();
}

bool8 FriendsStory_TryAdopt(void)
{
    u16 flag;
    u16 previousResult;
    if (FriendsStory_IsReady())
        return TRUE;
    // Reuse the existing supported native6 blank-window adoption first. Do not
    // leave a hidden VAR_RESULT mutation in ordinary map loading.
    if (!CharacterStory_IsReady())
    {
        previousResult = gSpecialVar_Result;
        Special_CharacterStoryAdopt();
        gSpecialVar_Result = previousResult;
    }
    if (gSaveBlock1Ptr == NULL || gSaveBlock3Ptr == NULL
     || !CharacterStory_IsReady()
     || !RegionalSave_FoundationValid((const u8 *)gSaveBlock3Ptr))
        return FALSE;
    // Accept only blank older allocation. Never erase unknown flags or awards.
    for (flag = FRIENDS_STORY_FLAGS_FIRST; flag <= FRIENDS_STORY_FLAGS_LAST; flag++)
        if (FlagGet(flag))
            return FALSE;
    for (flag = TRAINER_FLAGS_START + FRIENDS_STORY_TRAINER_FIRST;
         flag <= TRAINER_FLAGS_START + FRIENDS_STORY_TRAINER_LAST; flag++)
        if (FlagGet(flag))
            return FALSE;
    FlagSet(FLAG_FRIENDS_STORY_ADOPTED);
    return TRUE;
}

void FriendsStory_NewGame(void)
{
    // Native clearing precedes this hook. No scene or battle is fabricated.
    FlagSet(FLAG_FRIENDS_STORY_ADOPTED);
}

u16 FriendsStory_GetStage(void)
{
    return FriendsStory_IsReady()
        ? ReadBits(FRIENDS_STORY_STAGE_FIRST, FRIENDS_STORY_STAGE_BITS) : 0;
}

static bool8 JohtoChampion(void)
{
    // Kanto's native game-clear flag cannot satisfy this independent milestone.
    // Native GameClear/EnterHallOfFame write SYS_GAME_CLEAR only for Johto.
    // The earlier scripted IS_CHAMPION flag is not the completed HOF receipt.
    return JohtoCampaign_IsSeeded() && FlagGet(JOHTO_FLAG_SYS_GAME_CLEAR);
}

static bool8 FinalBattlesReady(void)
{
    return JohtoCampaign_IsSeeded() && FlagGet(JOHTO_FLAG_BADGE08_GET)
        && VarGet(JOHTO_VAR_BLACKTHORN_CITY_STATE) >= 4;
}

bool8 FriendsStory_GetGate(u16 scene)
{
    if (gSaveBlock1Ptr == NULL || scene < 1 || scene > FRIENDS_STORY_SCENE_COUNT)
        return FALSE;
    if (scene <= 11 && FlagGet(FLAG_SYS_GAME_CLEAR))
        return FALSE; // Late champions enter at the current chapter, not old fights.
    if (scene >= 13 && scene <= 19 && JohtoChampion())
        return FALSE;
    switch (scene)
    {
    case 1: case 2: case 4: case 5: case 6: case 9:
        return FlagGet(FLAG_SYS_POKEDEX_GET);
    case 3:
        return FlagGet(FLAG_GOT_FOSSIL_FROM_MT_MOON);
    case 7:
        return FlagGet(FLAG_HIDE_CELADON_ROCKETS);
    case 8:
        return FlagGet(FLAG_GOT_POKE_FLUTE);
    case 10:
        return FlagGet(FLAG_HIDE_SAFFRON_ROCKETS) && FlagGet(FLAG_GOT_MASTER_BALL_FROM_SILPH);
    case 11:
        return FlagGet(FLAG_HIDE_POKEMON_MANSION_B1F_SECRET_KEY);
    case 12:
        return FlagGet(FLAG_SYS_GAME_CLEAR) && VarGet(VAR_MAP_SCENE_PALLET_TOWN_OAK) >= 3;
    case 13: case 14:
        return CharacterStory_HasMetElm();
    case 15:
        return JohtoCampaign_IsSeeded() && VarGet(JOHTO_VAR_AZALEA_TOWN_STATE) >= 3
            && FlagGet(JOHTO_FLAG_HIDE_AZALEA_TOWN_ROCKETS);
    case 16:
        return JohtoCampaign_IsSeeded()
            && ((VarGet(JOHTO_VAR_GOLDENROD_CITY_STATE) >= 1 && VarGet(JOHTO_VAR_GOLDENROD_CITY_STATE) < 6)
             || VarGet(JOHTO_VAR_GOLDENROD_CITY_STATE) >= 11);
    case 17:
        return JohtoCampaign_IsSeeded() && FlagGet(JOHTO_FLAG_RELEASED_BEASTS);
    case 18:
        return JohtoCampaign_IsSeeded() && FlagGet(JOHTO_FLAG_AMPHAROS_HEALED);
    case 19:
        return JohtoCampaign_IsSeeded() && VarGet(JOHTO_VAR_GOLDENROD_CITY_STATE) >= 11;
    case 20:
        return FinalBattlesReady();
    case 21:
        return JohtoChampion() && !Seen(21);
    case 22:
        return JohtoChampion() && Seen(21) && FlagGet(FLAG_FRIENDS_REUNION_ARMED);
    }
    return FALSE;
}

u16 FriendsStory_GetMapScene(void)
{
    if (gSaveBlock1Ptr == NULL)
        return 0;
    switch (CurrentMap())
    {
    case MAP_VIRIDIAN_CITY: return 1;
    case MAP_ROUTE2: return 2;
    case MAP_ROUTE4: return 3;
    case MAP_CERULEAN_CITY: return 4;
    case MAP_VERMILION_CITY: return 5;
    case MAP_ROUTE11: return 6;
    case MAP_CELADON_CITY: return 7;
    case MAP_LAVENDER_TOWN: case MAP_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE: return 8;
    case MAP_FUCHSIA_CITY: return 9;
    case MAP_SAFFRON_CITY: return 10;
    case MAP_CINNABAR_ISLAND: return 11;
    case MAP_PALLET_TOWN: return 12;
    case MAP_NEW_BARK_TOWN_HNS:
        if (Seen(21))
            return FlagGet(FLAG_FRIENDS_REUNION_ARMED) ? 22 : 0;
        return FriendsStory_GetGate(21) ? 21 : 13;
    case MAP_RUINS_OF_ALPH_OUTSIDE_HNS: return 14;
    case MAP_AZALEA_TOWN_HNS: return 15;
    case MAP_GOLDENROD_CITY_HNS: return FriendsStory_GetGate(19) ? 19 : 16;
    case MAP_ECRUTEAK_CITY_HNS: return 17;
    case MAP_OLIVINE_CITY_PORT_OUTSIDE_HNS: return 18;
    case MAP_BLACKTHORN_CITY_HNS: return 20;
    }
    return 0;
}

void FriendsStory_OnMapLoad(void)
{
    u16 stage, scene;
    // Native Continue restores the old map/cache before applying a pending
    // Continue warp. That abandoned cache is not a visit. Its destination runs
    // this hook after the native warp flag has been cleared.
    if (UseContinueGameWarp() == TRUE)
        return;
    if (!FriendsStory_TryAdopt())
        return;
    // A cold Continue in the departure map never arms or respawns the group.
    if (Seen(21) && CurrentMap() != MAP_NEW_BARK_TOWN_HNS)
        FlagSet(FLAG_FRIENDS_REUNION_ARMED);
    stage = FriendsStory_GetStage();
    scene = FriendsStory_GetMapScene();
    if (scene > stage && FriendsStory_GetGate(scene))
        WriteBits(FRIENDS_STORY_STAGE_FIRST, FRIENDS_STORY_STAGE_BITS, scene);
}

static bool8 Here(u16 scene)
{
    return FriendsStory_IsReady() && scene == FriendsStory_GetStage()
        && scene == FriendsStory_GetMapScene() && FriendsStory_GetGate(scene);
}

void FriendsStory_OnBattleOutcome(u16 trainerId, u32 outcome)
{
    if (!FriendsStory_IsReady() || trainerId < FRIENDS_STORY_TRAINER_FIRST
     || trainerId > FRIENDS_STORY_TRAINER_LAST)
        return;
    // Called after an actual finished battle, before the native blackout path.
    // Flee/forfeit/interrupted requests create no completed battle or follow-up.
    if (outcome == B_OUTCOME_LOST || outcome == B_OUTCOME_DREW)
        WriteBits(FRIENDS_STORY_LOSS_FIRST, FRIENDS_STORY_LOSS_BITS,
            trainerId - FRIENDS_STORY_TRAINER_FIRST + 1);
}

void Special_FriendsStoryAdopt(void)
{
    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    gSpecialVar_Result = FriendsStory_TryAdopt();
}

void Special_FriendsStoryGetStage(void)
{
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = FriendsStory_GetStage();
}

void Special_FriendsStoryGetGate(void)
{
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = FriendsStory_IsReady() && FriendsStory_GetGate(gSpecialVar_0x8004);
}

void Special_FriendsStoryGetSeen(void)
{
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = FriendsStory_IsReady() && Seen(gSpecialVar_0x8004);
}

void Special_FriendsStoryBegin(void)
{
    u16 scene = gSpecialVar_0x8004;
    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    FriendsStory_OnMapLoad();
    gSpecialVar_Result = Here(scene) ? (Seen(scene) ? 2 : 1) : 0;
}

void Special_FriendsStoryMarkSeen(void)
{
    u16 scene = gSpecialVar_0x8004;
    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    gSpecialVar_Result = FALSE;
    if (scene == 21)
    {
        Special_FriendsStoryCompleteDeparture();
        return;
    }
    if (Here(scene))
    {
        FlagSet(FRIENDS_STORY_SEEN_FIRST + scene - 1);
        gSpecialVar_Result = TRUE;
    }
}

void Special_FriendsStoryNeedsIntroduction(void)
{
    u16 scene;
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = FriendsStory_IsReady();
    for (scene = 1; scene <= FRIENDS_STORY_SCENE_COUNT; scene++)
        if (Seen(scene))
            gSpecialVar_Result = FALSE;
}

void Special_FriendsStoryCanFinalBattle(void)
{
    u16 stage = FriendsStory_GetStage();
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = FriendsStory_IsReady() && FinalBattlesReady()
        && (stage == 20 || stage == 21 || stage == 22) && Here(stage);
}

void Special_FriendsStoryCanBattle(void)
{
    static const u8 sEarlyScenes[] = {2, 3, 6, 6, 7, 9, 16};
    u16 trainer = gSpecialVar_0x8004;
    u16 stage = FriendsStory_GetStage();
    u32 i;
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = FALSE;
    if (!FriendsStory_IsReady() || !Here(stage) || PlayerHasFollowerNPC()
     || trainer < FRIENDS_STORY_TRAINER_FIRST || trainer > FRIENDS_STORY_TRAINER_LAST)
        return;
    if (trainer <= FRIENDS_STORY_EARLY_TRAINER_LAST)
    {
        if (stage != sEarlyScenes[trainer - FRIENDS_STORY_TRAINER_FIRST])
            return;
    }
    else if (stage < 20 || !FinalBattlesReady())
        return;
    for (i = 0; i < PARTY_SIZE; i++)
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) != SPECIES_NONE
         && !GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG)
         && GetMonData(&gPlayerParty[i], MON_DATA_HP) != 0)
            gSpecialVar_Result = TRUE;
}

void Special_FriendsStoryGetPendingLoss(void)
{
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = FriendsStory_IsReady()
        ? ReadBits(FRIENDS_STORY_LOSS_FIRST, FRIENDS_STORY_LOSS_BITS) : 0;
}

void Special_FriendsStoryClearPendingLoss(void)
{
    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    if (FriendsStory_IsReady())
        WriteBits(FRIENDS_STORY_LOSS_FIRST, FRIENDS_STORY_LOSS_BITS, 0);
    gSpecialVar_Result = FALSE;
}

void Special_FriendsStoryGetInvitation(void)
{
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = FriendsStory_IsReady() && FlagGet(FLAG_FRIENDS_FAREWELL_INVITED);
}

void Special_FriendsStoryMarkInvitation(void)
{
    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    gSpecialVar_Result = Here(21);
    if (gSpecialVar_Result)
        FlagSet(FLAG_FRIENDS_FAREWELL_INVITED);
}

void Special_FriendsStoryInvitation(void)
{
    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    gSpecialVar_Result = Here(21) && !FlagGet(FLAG_FRIENDS_FAREWELL_INVITED);
    if (gSpecialVar_Result)
        FlagSet(FLAG_FRIENDS_FAREWELL_INVITED);
}

void Special_FriendsStoryCompleteDeparture(void)
{
    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    gSpecialVar_Result = Here(21) && FlagGet(FLAG_FRIENDS_FAREWELL_INVITED);
    if (gSpecialVar_Result)
        FlagSet(FLAG_FRIENDS_DEPARTED);
}

void Special_FriendsStoryIsReunionReady(void)
{
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = Here(22);
}

#include "global.h"
#ifdef FIRERED
#include "battle_setup.h"
#include "data.h"
#include "johto_rematches.h"
#include "johto_campaign.h"
#include "event_data.h"
#include "regions.h"
#include "constants/johto_ids.h"
#include "constants/johto_trainers.h"

#define REMATCH(trainer1, trainer2, trainer3, trainer4, trainer5, map) \
{ \
    .trainerIds = {trainer1, trainer2, trainer3, trainer4, trainer5}, \
    .mapGroup = MAP_GROUP(map), \
    .mapNum = MAP_NUM(map), \
}
#include "data/johto_rematch_catalog.h"
#undef REMATCH

s32 JohtoRematch_CompactRow(u16 originalTableId)
{
    u32 i;
    for (i = 0; i < JOHTO_REMATCH_ROW_COUNT; i++)
        if (sJohtoRematchOriginalIds[i] == originalTableId)
            return i;
    return -1;
}

bool8 JohtoRematch_IsContext(void)
{
    return GetCurrentRegion() == REGION_JOHTO && JohtoCampaign_IsSeeded();
}

u8 JohtoRematch_GetReadiness(u16 originalTableId)
{
    s32 row = JohtoRematch_CompactRow(originalTableId);
    if (row < 0)
        return 0;
    return JohtoCampaign_GetRematchReadiness(row);
}

void JohtoRematch_SetReadiness(u16 originalTableId, u8 value)
{
    s32 row = JohtoRematch_CompactRow(originalTableId);
    if (row >= 0)
        JohtoCampaign_SetRematchReadiness(row, value);
}

u8 JohtoRematch_GetStepCounter(void)
{
    return JohtoCampaign_GetRematchStepCounter();
}

void JohtoRematch_SetStepCounter(u16 value)
{
    JohtoCampaign_SetRematchStepCounter(value);
}

// Original HnS ceilings and regional badge count; native Kanto flags are separate.
static const u8 sJohtoRematchLevelCeilings[17] =
{
    12, 16, 20, 25, 30, 32, 34, 43, 47, 52, 55, 57, 59, 61, 64, 67, MAX_LEVEL
};

static u32 CountJohtoRematchBadges(void)
{
    u32 i, count = 0;
    for (i = 0; i < 16; i++)
        if (FlagGet(JOHTO_FLAG_BADGE01_GET + i))
            count++;
    return count;
}

bool8 JohtoRematch_HasEnoughBadges(void)
{
    return CountJohtoRematchBadges() >= OW_REMATCH_BADGE_COUNT;
}

static s32 JohtoRematch_MaxStage(const struct RematchTrainer *entry)
{
    u32 i, levelCeiling;
    s32 maxStage = 1;
    if (FlagGet(JOHTO_FLAG_IS_KANTO_CHAMPION))
        return REMATCHES_COUNT - 1;
    levelCeiling = sJohtoRematchLevelCeilings[CountJohtoRematchBadges()];
    for (i = 2; i < REMATCHES_COUNT; i++)
    {
        const struct TrainerMon *party;
        u32 mon, partySize, maxLevel = 0;
        if (entry->trainerIds[i] == 0)
            break;
        party = GetTrainerPartyFromId(entry->trainerIds[i]);
        partySize = GetTrainerPartySizeFromId(entry->trainerIds[i]);
        if (party != NULL)
            for (mon = 0; mon < partySize; mon++)
                if (party[mon].lvl > maxLevel)
                    maxLevel = party[mon].lvl;
        if (maxLevel > levelCeiling)
            break;
        maxStage = i;
    }
    return maxStage;
}

u16 JohtoRematch_GetTrainerId(u16 firstTrainerId)
{
    s32 i, maxStage;
    s32 tableId = FirstBattleTrainerIdToRematchTableId(gJohtoRematchTable, firstTrainerId);
    const struct RematchTrainer *entry;
    if (tableId < 0)
        return FALSE;
    entry = &gJohtoRematchTable[tableId];
    maxStage = JohtoRematch_MaxStage(entry);
    for (i = 1; i <= maxStage; i++)
    {
        if (entry->trainerIds[i] == 0)
            return entry->trainerIds[i - 1];
        if (!HasTrainerBeenFought(entry->trainerIds[i]))
            return entry->trainerIds[i];
    }
    return entry->trainerIds[maxStage];
}

u16 JohtoRematch_GetLastBeatenTrainerId(u16 firstTrainerId)
{
    s32 i;
    s32 tableId = FirstBattleTrainerIdToRematchTableId(gJohtoRematchTable, firstTrainerId);
    const struct RematchTrainer *entry;
    if (tableId < 0)
        return FALSE;
    entry = &gJohtoRematchTable[tableId];
    for (i = 1; i < REMATCHES_COUNT; i++)
    {
        if (entry->trainerIds[i] == 0 || !HasTrainerBeenFought(entry->trainerIds[i]))
            return entry->trainerIds[i - 1];
    }
    return entry->trainerIds[REMATCHES_COUNT - 1];
}

bool32 JohtoRematch_IsRegistered(s32 tableId)
{
    return JohtoRematch_CompactRow(tableId) >= 0
        && FlagGet(JOHTO_REMATCH_REGISTERED_FLAGS_START + tableId);
}

void JohtoRematch_UpdateIfDefeated(s32 tableId)
{
    s32 i;
    if (JohtoRematch_CompactRow(tableId) < 0
     || !HasTrainerBeenFought(gJohtoRematchTable[tableId].trainerIds[0]))
        return;
    for (i = 1; i < REMATCHES_COUNT; i++)
        if (gJohtoRematchTable[tableId].trainerIds[i] == 0
         || !HasTrainerBeenFought(gJohtoRematchTable[tableId].trainerIds[i]))
            break;
    JohtoRematch_SetReadiness(tableId, i);
}

u16 JohtoRematch_CountMaxPossible(u16 tableId)
{
    u32 i;
    for (i = 1; i < REMATCHES_COUNT; i++)
        if (gJohtoRematchTable[tableId].trainerIds[i] == 0)
            return i;
    return REMATCHES_COUNT - 1;
}

u16 JohtoRematch_CountBattledTeams(u16 tableId)
{
    u32 i;
    if (!HasTrainerBeenFought(gJohtoRematchTable[tableId].trainerIds[0]))
        return 0;
    for (i = 1; i < REMATCHES_COUNT; i++)
        if (gJohtoRematchTable[tableId].trainerIds[i] == 0
         || !HasTrainerBeenFought(gJohtoRematchTable[tableId].trainerIds[i]))
            return i;
    return REMATCHES_COUNT - 1;
}
#endif

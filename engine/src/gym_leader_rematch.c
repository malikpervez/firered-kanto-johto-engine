#include "global.h"
#ifdef FIRERED
#include "random.h"
#include "event_data.h"
#include "battle_setup.h"
#include "gym_leader_rematch.h"
#include "johto_rematches.h"
#include "constants/johto_ids.h"

static const struct RematchTrainer *CurrentGymRematchTable(void)
{
    return JohtoRematch_IsContext() ? gJohtoRematchTable : gRematchTable;
}

static bool8 GymRematchFlag(u16 nativeFlag, u16 regionalFlag)
{
    return FlagGet(JohtoRematch_IsContext() ? regionalFlag : nativeFlag);
}

static u8 ReadGymRematchReadiness(u32 row)
{
    return JohtoRematch_IsContext() ? JohtoRematch_GetReadiness(row) : gSaveBlock1Ptr->trainerRematches[row];
}

static void WriteGymRematchReadiness(u32 row, u8 value)
{
    if (JohtoRematch_IsContext())
        JohtoRematch_SetReadiness(row, value);
    else
        gSaveBlock1Ptr->trainerRematches[row] = value;
}

static void UpdateGymLeaderRematchFromArray(const u16 *data, size_t size, u32 maxRematch);
#if FREE_MATCH_CALL == FALSE
static s32 GetRematchIndex(u32 trainerIdx);
#endif //FREE_MATCH_CALL

static const u16 GymLeaderRematches_AfterNewMauville[] = {
    REMATCH_ROXANNE,
    REMATCH_BRAWLY,
    REMATCH_WATTSON,
    REMATCH_FLANNERY,
    REMATCH_NORMAN,
    REMATCH_WINONA,
    REMATCH_TATE_AND_LIZA,
    REMATCH_JUAN
};

static const u16 GymLeaderRematches_BeforeNewMauville[] = {
    REMATCH_ROXANNE,
    REMATCH_BRAWLY,
    // Wattson isn't available at this time
    REMATCH_FLANNERY,
    REMATCH_NORMAN,
    REMATCH_WINONA,
    REMATCH_TATE_AND_LIZA,
    REMATCH_JUAN
};

void UpdateGymLeaderRematch(void)
{
    if (GymRematchFlag(FLAG_SYS_GAME_CLEAR, JOHTO_FLAG_SYS_GAME_CLEAR) && (Random() % 100) <= 30)
    {
        if (GymRematchFlag(FLAG_WATTSON_REMATCH_AVAILABLE, JOHTO_FLAG_WATTSON_REMATCH_AVAILABLE))
            UpdateGymLeaderRematchFromArray(GymLeaderRematches_AfterNewMauville, ARRAY_COUNT(GymLeaderRematches_AfterNewMauville), 5);
        else
            UpdateGymLeaderRematchFromArray(GymLeaderRematches_BeforeNewMauville, ARRAY_COUNT(GymLeaderRematches_BeforeNewMauville), 1);
    }
}

s32 GetCurrentGymLeaderRematchLevel(void)
{
    u32 i, j;
    u32 maxLevel = REMATCHES_COUNT;
    if (!GymRematchFlag(FLAG_SYS_GAME_CLEAR, JOHTO_FLAG_SYS_GAME_CLEAR))
        return 0;
    for (i = REMATCH_SPECIAL_TRAINER_START; i < REMATCH_ELITE_FOUR_ENTRIES; i++)
    {
        for (j = 0; j < REMATCHES_COUNT; j++)
        {
            if (!HasTrainerBeenFought(CurrentGymRematchTable()[i].trainerIds[j]))
                break;
        }
        if (maxLevel > j)
            j = maxLevel;
    }
    return maxLevel;
}

static void UpdateGymLeaderRematchFromArray(const u16 *data, size_t size, u32 maxRematch)
{
#if FREE_MATCH_CALL == FALSE
    s32 whichLeader = 0;
    s32 lowestRematchIndex = 5;
    u32 i;
    s32 rematchIndex;

    for (i = 0; i < size; i++)
    {
        if (!ReadGymRematchReadiness(data[i]))
        {
            rematchIndex = GetRematchIndex(data[i]);
            if (lowestRematchIndex > rematchIndex)
                lowestRematchIndex = rematchIndex;
            whichLeader++;
        }
    }
    if (whichLeader != 0 && lowestRematchIndex <= maxRematch)
    {
        whichLeader = 0;
        for (i = 0; i < size; i++)
        {
            if (!ReadGymRematchReadiness(data[i]))
            {
                rematchIndex = GetRematchIndex(data[i]);
                if (rematchIndex == lowestRematchIndex)
                    whichLeader++;
            }
        }
        if (whichLeader != 0)
        {
            whichLeader = Random() % whichLeader;
            for (i = 0; i < size; i++)
            {
                if (!ReadGymRematchReadiness(data[i]))
                {
                    rematchIndex = GetRematchIndex(data[i]);
                    if (rematchIndex == lowestRematchIndex)
                    {
                        if (whichLeader == 0)
                        {
                            WriteGymRematchReadiness(data[i], lowestRematchIndex);
                            break;
                        }
                        whichLeader--;
                    }
                }
            }
        }
    }
#endif //FREE_MATCH_CALL
}

#if FREE_MATCH_CALL == FALSE
static s32 GetRematchIndex(u32 trainerIdx)
{
    s32 i;
    for (i = 0; i < 5; i++)
    {
        if (!HasTrainerBeenFought(CurrentGymRematchTable()[trainerIdx].trainerIds[i]))
        {
            return i;
        }
    }
    return 5;
}
#endif //FREE_MATCH_CALL

#else // original implementation for every other target
#include "global.h"
#include "random.h"
#include "event_data.h"
#include "battle_setup.h"
#include "gym_leader_rematch.h"

static void UpdateGymLeaderRematchFromArray(const u16 *data, size_t size, u32 maxRematch);
#if FREE_MATCH_CALL == FALSE
static s32 GetRematchIndex(u32 trainerIdx);
#endif //FREE_MATCH_CALL

static const u16 GymLeaderRematches_AfterNewMauville[] = {
    REMATCH_ROXANNE,
    REMATCH_BRAWLY,
    REMATCH_WATTSON,
    REMATCH_FLANNERY,
    REMATCH_NORMAN,
    REMATCH_WINONA,
    REMATCH_TATE_AND_LIZA,
    REMATCH_JUAN
};

static const u16 GymLeaderRematches_BeforeNewMauville[] = {
    REMATCH_ROXANNE,
    REMATCH_BRAWLY,
    // Wattson isn't available at this time
    REMATCH_FLANNERY,
    REMATCH_NORMAN,
    REMATCH_WINONA,
    REMATCH_TATE_AND_LIZA,
    REMATCH_JUAN
};

void UpdateGymLeaderRematch(void)
{
    if (FlagGet(FLAG_SYS_GAME_CLEAR) && (Random() % 100) <= 30)
    {
        if (FlagGet(FLAG_WATTSON_REMATCH_AVAILABLE))
            UpdateGymLeaderRematchFromArray(GymLeaderRematches_AfterNewMauville, ARRAY_COUNT(GymLeaderRematches_AfterNewMauville), 5);
        else
            UpdateGymLeaderRematchFromArray(GymLeaderRematches_BeforeNewMauville, ARRAY_COUNT(GymLeaderRematches_BeforeNewMauville), 1);
    }
}

s32 GetCurrentGymLeaderRematchLevel(void)
{
    u32 i, j;
    u32 maxLevel = REMATCHES_COUNT;
    if (!FlagGet(FLAG_SYS_GAME_CLEAR))
        return 0;
    for (i = REMATCH_SPECIAL_TRAINER_START; i < REMATCH_ELITE_FOUR_ENTRIES; i++)
    {
        for (j = 0; j < REMATCHES_COUNT; j++)
        {
            if (!HasTrainerBeenFought(gRematchTable[i].trainerIds[j]))
                break;
        }
        if (maxLevel > j)
            j = maxLevel;
    }
    return maxLevel;
}

static void UpdateGymLeaderRematchFromArray(const u16 *data, size_t size, u32 maxRematch)
{
#if FREE_MATCH_CALL == FALSE
    s32 whichLeader = 0;
    s32 lowestRematchIndex = 5;
    u32 i;
    s32 rematchIndex;

    for (i = 0; i < size; i++)
    {
        if (!gSaveBlock1Ptr->trainerRematches[data[i]])
        {
            rematchIndex = GetRematchIndex(data[i]);
            if (lowestRematchIndex > rematchIndex)
                lowestRematchIndex = rematchIndex;
            whichLeader++;
        }
    }
    if (whichLeader != 0 && lowestRematchIndex <= maxRematch)
    {
        whichLeader = 0;
        for (i = 0; i < size; i++)
        {
            if (!gSaveBlock1Ptr->trainerRematches[data[i]])
            {
                rematchIndex = GetRematchIndex(data[i]);
                if (rematchIndex == lowestRematchIndex)
                    whichLeader++;
            }
        }
        if (whichLeader != 0)
        {
            whichLeader = Random() % whichLeader;
            for (i = 0; i < size; i++)
            {
                if (!gSaveBlock1Ptr->trainerRematches[data[i]])
                {
                    rematchIndex = GetRematchIndex(data[i]);
                    if (rematchIndex == lowestRematchIndex)
                    {
                        if (whichLeader == 0)
                        {
                            gSaveBlock1Ptr->trainerRematches[data[i]] = lowestRematchIndex;
                            break;
                        }
                        whichLeader--;
                    }
                }
            }
        }
    }
#endif //FREE_MATCH_CALL
}

#if FREE_MATCH_CALL == FALSE
static s32 GetRematchIndex(u32 trainerIdx)
{
    s32 i;
    for (i = 0; i < 5; i++)
    {
        if (!HasTrainerBeenFought(gRematchTable[trainerIdx].trainerIds[i]))
        {
            return i;
        }
    }
    return 5;
}
#endif //FREE_MATCH_CALL

#endif

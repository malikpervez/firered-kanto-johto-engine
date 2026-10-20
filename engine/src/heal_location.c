#include "global.h"
#include "event_data.h"
#include "heal_location.h"
#include "constants/event_objects.h"
#include "constants/heal_locations.h"
#include "constants/maps.h"

#include "data/heal_locations.h"

#ifdef FIRERED
STATIC_ASSERT(NUM_HEAL_LOCATIONS <= JOHTO_HEAL_LOCATION_BASE, NativeHealIdsDoNotOverlapJohto);
STATIC_ASSERT(JOHTO_HEAL_LOCATION_BASE + JOHTO_HEAL_LOCATION_COUNT <= 256, JohtoHealIdsFitScriptByte);

static bool8 IsJohtoHealLocation(u32 index)
{
    return index >= JOHTO_HEAL_LOCATION_BASE
        && index < JOHTO_HEAL_LOCATION_BASE + JOHTO_HEAL_LOCATION_COUNT;
}
#endif

u32 GetHealLocationIndexByMap(u16 mapGroup, u16 mapNum)
{
    u32 i;

#ifdef FIRERED
    for (i = 0; i < ARRAY_COUNT(sJohtoHealLocations); i++)
    {
        if (sJohtoHealLocations[i].mapGroup == mapGroup && sJohtoHealLocations[i].mapNum == mapNum)
            return JOHTO_HEAL_LOCATION_BASE + i;
    }
#endif
    for (i = 0; i < ARRAY_COUNT(sHealLocations); i++)
    {
        if (sHealLocations[i].mapGroup == mapGroup && sHealLocations[i].mapNum == mapNum)
            return i + 1;
    }
    return HEAL_LOCATION_NONE;
}

const struct HealLocation *GetHealLocationByMap(u16 mapGroup, u16 mapNum)
{
    u32 index = GetHealLocationIndexByMap(mapGroup, mapNum);

    if (index == HEAL_LOCATION_NONE)
        return NULL;
    else
#ifdef FIRERED
        return GetHealLocation(index);
#else
        return &sHealLocations[index - 1];
#endif
}

u32 GetHealLocationIndexByWarpData(struct WarpData *warp)
{
    u32 i;
#ifdef FIRERED
    for (i = 0; i < ARRAY_COUNT(sJohtoHealLocations); i++)
    {
        if (sJohtoHealLocations[i].mapGroup == warp->mapGroup
        && sJohtoHealLocations[i].mapNum == warp->mapNum
        && sJohtoHealLocations[i].x == warp->x
        && sJohtoHealLocations[i].y == warp->y)
            return JOHTO_HEAL_LOCATION_BASE + i;
    }
#endif
    for (i = 0; i < ARRAY_COUNT(sHealLocations); i++)
    {
        if (sHealLocations[i].mapGroup == warp->mapGroup
        && sHealLocations[i].mapNum == warp->mapNum
        && sHealLocations[i].x == warp->x
        && sHealLocations[i].y == warp->y)
            return i + 1;
    }
    return HEAL_LOCATION_NONE;
}

const struct HealLocation *GetHealLocation(u32 index)
{
#ifdef FIRERED
    if (IsJohtoHealLocation(index))
        return &sJohtoHealLocations[index - JOHTO_HEAL_LOCATION_BASE];
#endif
    if (index == HEAL_LOCATION_NONE)
        return NULL;
    else if (index > ARRAY_COUNT(sHealLocations))
        return NULL;
    else
        return &sHealLocations[index - 1];
}

static bool32 IsLastHealLocation(u32 healLocation)
{
    const struct HealLocation *loc = GetHealLocation(healLocation);
    const struct WarpData *warpData = &gSaveBlock1Ptr->lastHealLocation;

    return warpData->mapGroup == loc->mapGroup
        && warpData->mapNum == loc->mapNum
        && warpData->warpId == WARP_ID_NONE
        && warpData->x == loc->x
        && warpData->y == loc->y;
}

bool32 IsLastHealLocationPlayerHouse()
{
    if (IsLastHealLocation(HEAL_LOCATION_LITTLEROOT_TOWN_MAYS_HOUSE)
        || IsLastHealLocation(HEAL_LOCATION_LITTLEROOT_TOWN_MAYS_HOUSE_2F)
        || IsLastHealLocation(HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE)
        || IsLastHealLocation(HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F)
        || IsLastHealLocation(HEAL_LOCATION_PALLET_TOWN))
        return TRUE;

    return FALSE;
}

u32 GetHealNpcLocalId(u32 healLocationId)
{
#ifdef FIRERED
    // The actual upstream Johto records declare respawn_npc0. Preserve their
    // ordinary outdoor blackout destination rather than inventing an actor.
    if (IsJohtoHealLocation(healLocationId))
        return LOCALID_NONE;
#endif
    if (healLocationId == HEAL_LOCATION_NONE || healLocationId >= NUM_HEAL_LOCATIONS)
        return LOCALID_NONE;

    return sWhiteoutRespawnHealerNpcIds[healLocationId - 1];
}

void SetWhiteoutRespawnWarpAndHealerNPC(struct WarpData *warp)
{
    u32 healLocationId = GetHealLocationIndexByWarpData(&gSaveBlock1Ptr->lastHealLocation);
    u32 healNpcLocalId = GetHealNpcLocalId(healLocationId);

    if (!healNpcLocalId)
    {
        *(warp) = gSaveBlock1Ptr->lastHealLocation;
        return;
    }

    warp->mapGroup = sWhiteoutRespawnHealCenterMapIdxs[healLocationId - 1][0];
    warp->mapNum = sWhiteoutRespawnHealCenterMapIdxs[healLocationId - 1][1];
    warp->warpId = WARP_ID_NONE;
    warp->x = sWhiteoutRespawnHealCenterMapIdxs[healLocationId - 1][2];
    warp->y = sWhiteoutRespawnHealCenterMapIdxs[healLocationId - 1][3];
    gSpecialVar_LastTalked = healNpcLocalId;
    gSpecialVar_0x800B = healNpcLocalId;
}

// Kanto's overworld Pokémon outside its towns can be battled (the owner, 6 November 2026: they "should be slightly
// stronger compared to those found in that route. If the player chooses to fight them they should have a higher
// level and better IVs so it encourages the challenge").
//
// A walker given OverworldMon_EventScript_Encounter asks whether to battle it. Its level is a few above the highest
// wild Pokémon of the map it walks on (the land table, or the water table for one on water, at the time of day the
// game uses for encounters), and each of its IVs is at least OW_MON_ENCOUNTER_MIN_IV. Once battled it is gone until
// the player leaves the map: the game clears the record with the map's temporary flags (ClearTempFieldEventData).
#include "global.h"
#include "battle_setup.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "fieldmap.h"
#include "metatile_behavior.h"
#include "overworld_mon_encounter.h"
#include "pokemon.h"
#include "random.h"
#include "script.h"
#include "string_util.h"
#include "wild_encounter.h"
#include "constants/event_objects.h"
#include "constants/wild_encounter.h"

#define OW_MON_ENCOUNTER_LEVEL_BONUS 3  // levels above the map's highest wild Pokémon
#define OW_MON_ENCOUNTER_MIN_IV     20  // each IV is OW_MON_ENCOUNTER_MIN_IV..MAX_PER_STAT_IVS

// The walkers battled on the current map, by local id; cleared when the player leaves the map.
static EWRAM_DATA u8 sGone[256 / 8] = {0};

void OwMonEncounter_ClearGone(void)
{
    memset(sGone, 0, sizeof(sGone));
}

bool32 OwMonEncounter_IsGone(u8 localId)
{
    return (sGone[localId / 8] >> (localId % 8)) & 1;
}

static u8 HighestLevel(const struct WildPokemonInfo *info, u32 count)
{
    u32 i;
    u8 level = 0;

    if (info == NULL || info->wildPokemon == NULL)
        return 0;
    for (i = 0; i < count; i++)
        if (info->wildPokemon[i].maxLevel > level)
            level = info->wildPokemon[i].maxLevel;
    return level;
}

// The highest level among the map's wild Pokémon a walker standing here would be counted with: the water table on
// water, else the land table (or the water table where a map, like a sea route, has no land Pokémon).
static u8 HighestWildLevelHere(bool32 onWater)
{
    u16 headerId = GetCurrentMapWildMonHeaderId();
    const struct WildEncounterTypes *types;
    u8 land, water;

    if (headerId == HEADER_NONE)
        return 0;
    types = &gWildMonHeaders[headerId].encounterTypes[GetTimeOfDayForEncounters(headerId, WILD_AREA_LAND)];
    land = HighestLevel(types->landMonsInfo, LAND_WILD_COUNT);
    types = &gWildMonHeaders[headerId].encounterTypes[GetTimeOfDayForEncounters(headerId, WILD_AREA_WATER)];
    water = HighestLevel(types->waterMonsInfo, WATER_WILD_COUNT);
    if (onWater || land == 0)
        return water;
    return land;
}

static struct ObjectEvent *TalkedWalker(void)
{
    u8 objectEventId;

    // (TRUE when there is no such object)
    if (TryGetObjectEventIdByLocalIdAndMap(gSpecialVar_LastTalked, gSaveBlock1Ptr->location.mapNum,
                                           gSaveBlock1Ptr->location.mapGroup, &objectEventId))
        return NULL;
    if (!IS_OW_MON_OBJ(&gObjectEvents[objectEventId]))
        return NULL;
    return &gObjectEvents[objectEventId];
}

// Prepares the battle with the walker the player is talking to. Out: VAR_0x8004 its species, STR_VAR_1 its name,
// VAR_RESULT TRUE when the map has wild Pokémon to set its level by (FALSE: no battle).
void Special_OwMonEncounterPrepare(void)
{
    struct ObjectEvent *walker = TalkedWalker();
    u32 i, level;
    u16 species;

    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = FALSE;
    if (walker == NULL)
        return;
    species = OW_SPECIES(walker);
    gSpecialVar_0x8004 = species;
    StringCopy(gStringVar1, GetSpeciesName(species));
    level = HighestWildLevelHere(MetatileBehavior_IsSurfableWaterOrUnderwater(
        MapGridGetMetatileBehaviorAt(walker->currentCoords.x, walker->currentCoords.y)));
    if (level == 0)
        return;
    level += OW_MON_ENCOUNTER_LEVEL_BONUS;
    if (level > MAX_LEVEL)
        level = MAX_LEVEL;

    CreateWildMon(species, level);
    for (i = 0; i < NUM_STATS; i++)
    {
        u32 iv = OW_MON_ENCOUNTER_MIN_IV + Random() % (MAX_PER_STAT_IVS - OW_MON_ENCOUNTER_MIN_IV + 1);
        SetMonData(&gEnemyParty[0], MON_DATA_HP_IV + i, &iv);
    }
    if (walker->graphicsId & OBJ_EVENT_MON_SHINY)  // a shiny walker is a shiny Pokémon
    {
        bool32 shiny = TRUE;
        SetMonData(&gEnemyParty[0], MON_DATA_IS_SHINY, &shiny);
    }
    CalculateMonStats(&gEnemyParty[0]);
    gSpecialVar_Result = TRUE;
}

// After the battle (won, caught or run from): the walker goes, and stays gone until the player leaves the map.
void Special_OwMonEncounterRemove(void)
{
    struct ObjectEvent *walker = TalkedWalker();
    u8 localId = gSpecialVar_LastTalked;

    Script_RequestEffects(SCREFF_V1);
    sGone[localId / 8] |= 1 << (localId % 8);
    if (walker != NULL)
        RemoveObjectEvent(walker);
}

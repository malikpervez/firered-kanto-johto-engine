#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_effect.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "ow_synchronize.h"
#include "pokemon.h"
#include "random.h"
#include "roamer.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "constants/event_objects.h"
#include "pokedex.h"
#include "johto_campaign.h"
#include "firered_save.h"
#include "regions.h"

// Despite having a variable to track it, the roamer is
// hard-coded to only ever be in map group 0
#define ROAMER_MAP_GROUP 0

enum
{
    MAP_GRP, // map group
    MAP_NUM, // map number
};

EWRAM_DATA static u8 sLocationHistory[ROAMER_COUNT][3][2] = {0};
EWRAM_DATA static u8 sRoamerLocation[ROAMER_COUNT][2] = {0};
EWRAM_DATA u8 gEncounteredRoamerIndex = 0;

// This tag belongs only to the transient encounter index, never to a save flag.
#define JOHTO_ROAMER_ENCOUNTER_TAG 0x80
#define JOHTO_DOG_COUNT 2

static bool8 IsJohtoRoamerContext(void)
{
    return GetCurrentRegion() == REGION_JOHTO;
}

static bool8 UsesJohtoRoamerBank(u32 index)
{
    return (index & JOHTO_ROAMER_ENCOUNTER_TAG) || IsJohtoRoamerContext();
}

static u32 GetCurrentRoamerCount(void)
{
    if (IsJohtoRoamerContext())
        return JohtoCampaign_GetDogRoamer(0) != NULL ? JOHTO_DOG_COUNT : 0;
    return ROAMER_COUNT;
}

static struct Roamer *GetRoamerRecord(u32 index)
{
    if (UsesJohtoRoamerBank(index))
        return JohtoCampaign_GetDogRoamer(index & ~JOHTO_ROAMER_ENCOUNTER_TAG);
    return &gSaveBlock1Ptr->roamer[index];
}

static u8 (*GetRoamerHistory(u32 index))[3][2]
{
    if (UsesJohtoRoamerBank(index))
        return (u8 (*)[3][2])JohtoCampaign_GetDogLocationHistory(index & ~JOHTO_ROAMER_ENCOUNTER_TAG);
    return &sLocationHistory[index];
}

static u8 *GetCurrentRoamerLocation(u32 index)
{
    if (UsesJohtoRoamerBank(index))
        return JohtoCampaign_GetDogLocation(index & ~JOHTO_ROAMER_ENCOUNTER_TAG);
    return sRoamerLocation[index];
}

static void RoamerBeforeWrite(u32 index)
{
    if (UsesJohtoRoamerBank(index))
        FireRedSave_NotifyPersistentWrite();
}

struct Roamer *GetEncounteredRoamer(void)
{
    return GetRoamerRecord(gEncounteredRoamerIndex);
}

#define ROAMER(index) GetRoamerRecord(index)
#define ROAMER_HISTORY(index) (*GetRoamerHistory(index))
#define ROAMER_LOCATION(index) GetCurrentRoamerLocation(index)
#define CURRENT_ROAMER_COUNT GetCurrentRoamerCount()
#define ROAMER_BEFORE_WRITE(index) RoamerBeforeWrite(index)

#define ___ MAP_NUM(MAP_UNDEFINED) // For empty spots in the location table

// Note: There are two potential softlocks that can occur with this table if its maps are
//       changed in particular ways. They can be avoided by ensuring the following:
//       - There must be at least 2 location sets that start with a different map,
//         i.e. every location set cannot start with the same map. This is because of
//         the while loop in RoamerMoveToOtherLocationSet.
//       - Each location set must have at least 3 unique maps. This is because of
//         the while loop in RoamerMove. In this loop the first map in the set is
//         ignored, and an additional map is ignored if the roamer was there recently.
//       - Additionally, while not a softlock, it's worth noting that if for any
//         map in the location table there is not a location set that starts with
//         that map then the roamer will be significantly less likely to move away
//         from that map when it lands there.

static const u8 sRoamerLocationsHoenn[][6] =
{
    { MAP_NUM(MAP_ROUTE110), MAP_NUM(MAP_ROUTE111), MAP_NUM(MAP_ROUTE117), MAP_NUM(MAP_ROUTE118), MAP_NUM(MAP_ROUTE134), ___ },
    { MAP_NUM(MAP_ROUTE111), MAP_NUM(MAP_ROUTE110), MAP_NUM(MAP_ROUTE117), MAP_NUM(MAP_ROUTE118), ___, ___ },
    { MAP_NUM(MAP_ROUTE117), MAP_NUM(MAP_ROUTE111), MAP_NUM(MAP_ROUTE110), MAP_NUM(MAP_ROUTE118), ___, ___ },
    { MAP_NUM(MAP_ROUTE118), MAP_NUM(MAP_ROUTE117), MAP_NUM(MAP_ROUTE110), MAP_NUM(MAP_ROUTE111), MAP_NUM(MAP_ROUTE119), MAP_NUM(MAP_ROUTE123) },
    { MAP_NUM(MAP_ROUTE119), MAP_NUM(MAP_ROUTE118), MAP_NUM(MAP_ROUTE120), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE120), MAP_NUM(MAP_ROUTE119), MAP_NUM(MAP_ROUTE121), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE121), MAP_NUM(MAP_ROUTE120), MAP_NUM(MAP_ROUTE122), MAP_NUM(MAP_ROUTE123), ___, ___ },
    { MAP_NUM(MAP_ROUTE122), MAP_NUM(MAP_ROUTE121), MAP_NUM(MAP_ROUTE123), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE123), MAP_NUM(MAP_ROUTE122), MAP_NUM(MAP_ROUTE118), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE124), MAP_NUM(MAP_ROUTE121), MAP_NUM(MAP_ROUTE125), MAP_NUM(MAP_ROUTE126), ___, ___ },
    { MAP_NUM(MAP_ROUTE125), MAP_NUM(MAP_ROUTE124), MAP_NUM(MAP_ROUTE127), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE126), MAP_NUM(MAP_ROUTE124), MAP_NUM(MAP_ROUTE127), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE127), MAP_NUM(MAP_ROUTE125), MAP_NUM(MAP_ROUTE126), MAP_NUM(MAP_ROUTE128), ___, ___ },
    { MAP_NUM(MAP_ROUTE128), MAP_NUM(MAP_ROUTE127), MAP_NUM(MAP_ROUTE129), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE129), MAP_NUM(MAP_ROUTE128), MAP_NUM(MAP_ROUTE130), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE130), MAP_NUM(MAP_ROUTE129), MAP_NUM(MAP_ROUTE131), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE131), MAP_NUM(MAP_ROUTE130), MAP_NUM(MAP_ROUTE132), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE132), MAP_NUM(MAP_ROUTE131), MAP_NUM(MAP_ROUTE133), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE133), MAP_NUM(MAP_ROUTE132), MAP_NUM(MAP_ROUTE134), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE134), MAP_NUM(MAP_ROUTE133), MAP_NUM(MAP_ROUTE110), ___, ___, ___ },
    { ___, ___, ___, ___, ___, ___ },
};

enum
{
    ROAMER_LOC_TABLE_HOENN,
    ROAMER_LOC_TABLE_COUNT,
};

struct RoamerLocationTable
{
    const u8 (*locations)[6];
    u8 numSets;
};

static const struct RoamerLocationTable sRoamerLocationTables[ROAMER_LOC_TABLE_COUNT] =
{
    [ROAMER_LOC_TABLE_HOENN] = { sRoamerLocationsHoenn, ARRAY_COUNT(sRoamerLocationsHoenn) - 1 },
};


static const u8 sFireRedJohtoRoamerLocations[][6] =
{
    { MAP_NUM(MAP_ROUTE29_HNS), MAP_NUM(MAP_ROUTE30_HNS), MAP_NUM(MAP_ROUTE46_HNS), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE30_HNS), MAP_NUM(MAP_ROUTE29_HNS), MAP_NUM(MAP_ROUTE31_HNS), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE31_HNS), MAP_NUM(MAP_ROUTE30_HNS), MAP_NUM(MAP_ROUTE29_HNS), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE32_HNS), MAP_NUM(MAP_ROUTE31_HNS), MAP_NUM(MAP_ROUTE33_HNS), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE33_HNS), MAP_NUM(MAP_ROUTE32_HNS), MAP_NUM(MAP_ROUTE34_HNS), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE34_HNS), MAP_NUM(MAP_ROUTE33_HNS), MAP_NUM(MAP_ROUTE35_HNS), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE35_HNS), MAP_NUM(MAP_ROUTE34_HNS), MAP_NUM(MAP_ROUTE36_HNS), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE36_HNS), MAP_NUM(MAP_ROUTE31_HNS), MAP_NUM(MAP_ROUTE32_HNS), MAP_NUM(MAP_ROUTE35_HNS), MAP_NUM(MAP_ROUTE37_HNS), ___ },
    { MAP_NUM(MAP_ROUTE37_HNS), MAP_NUM(MAP_ROUTE36_HNS), MAP_NUM(MAP_ROUTE38_HNS), MAP_NUM(MAP_ROUTE42_HNS), ___, ___ },
    { MAP_NUM(MAP_ROUTE38_HNS), MAP_NUM(MAP_ROUTE37_HNS), MAP_NUM(MAP_ROUTE39_HNS), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE39_HNS), MAP_NUM(MAP_ROUTE48_HNS), MAP_NUM(MAP_ROUTE35_HNS), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE42_HNS), MAP_NUM(MAP_ROUTE37_HNS), MAP_NUM(MAP_ROUTE38_HNS), MAP_NUM(MAP_ROUTE43_HNS), MAP_NUM(MAP_ROUTE44_HNS), ___ },
    { MAP_NUM(MAP_ROUTE43_HNS), MAP_NUM(MAP_ROUTE42_HNS), MAP_NUM(MAP_ROUTE44_HNS), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE44_HNS), MAP_NUM(MAP_ROUTE42_HNS), MAP_NUM(MAP_ROUTE45_HNS), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE45_HNS), MAP_NUM(MAP_ROUTE44_HNS), MAP_NUM(MAP_ROUTE46_HNS), ___, ___, ___ },
    { MAP_NUM(MAP_ROUTE46_HNS), MAP_NUM(MAP_ROUTE45_HNS), MAP_NUM(MAP_ROUTE29_HNS), ___, ___, ___ },
    { ___, ___, ___, ___, ___, ___ },
};

#undef ___
#define NUM_LOCATIONS_PER_SET 6

static inline const u8 (*GetRoamerLocations(u32 roamerIndex))[6]
{
    if (UsesJohtoRoamerBank(roamerIndex))
        return sFireRedJohtoRoamerLocations;
    return sRoamerLocationTables[ROAMER(roamerIndex)->locationTableId].locations;
}

static inline u8 GetRoamerNumLocationSets(u32 roamerIndex)
{
    if (UsesJohtoRoamerBank(roamerIndex))
        return ARRAY_COUNT(sFireRedJohtoRoamerLocations) - 1;
    return sRoamerLocationTables[ROAMER(roamerIndex)->locationTableId].numSets;
}

static bool8 IsMapInRoamerTable(u32 roamerIndex, u8 mapNum)
{
    const u8 (*locs)[6] = GetRoamerLocations(roamerIndex);
    u8 numSets = GetRoamerNumLocationSets(roamerIndex);
    u32 i;

    for (i = 0; i < numSets; i++)
    {
        if (locs[i][0] == mapNum)
            return TRUE;
    }
    return FALSE;
}

static u8 CountLegendariesInParty(void)
{
    u8 count = 0;
    u32 i;

    for (i = 0; i < gPlayerPartyCount; i++)
    {
        u16 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES);
        if (species != SPECIES_NONE
            && (gSpeciesInfo[species].isRestrictedLegendary
                || gSpeciesInfo[species].isSubLegendary
                || gSpeciesInfo[species].isMythical))
            count++;
    }
    return count;
}

static void TryAttractRoamer(u32 roamerIndex)
{
    u8 playerMapNum = gSaveBlock1Ptr->location.mapNum;
    u8 legendCount = CountLegendariesInParty();

    if (legendCount == 0)
        return;

    if (!IsMapInRoamerTable(roamerIndex, playerMapNum))
        return;

    // 2% per legendary in party (max 12% with 6)
    if ((Random() % 100) < (legendCount * 2))
    {
        ROAMER_BEFORE_WRITE(roamerIndex);
        ROAMER_LOCATION(roamerIndex)[MAP_NUM] = playerMapNum;
    }
}

void DeactivateAllRoamers(void)
{
    u32 i;

    for (i = 0; i < CURRENT_ROAMER_COUNT; i++)
        SetRoamerInactive(i);
}

static void DeactivateRoamersByLocationTable(u8 locationTableId)
{
    u32 i;

    for (i = 0; i < CURRENT_ROAMER_COUNT; i++)
    {
        if (ROAMER(i)->active && ROAMER(i)->locationTableId == locationTableId)
            SetRoamerInactive(i);
    }
}

static void ClearRoamerLocationHistory(u32 roamerIndex)
{
    ROAMER_BEFORE_WRITE(roamerIndex);

    u32 i;

    for (i = 0; i < ARRAY_COUNT(ROAMER_HISTORY(roamerIndex)); i++)
    {
        ROAMER_HISTORY(roamerIndex)[i][MAP_GRP] = 0;
        ROAMER_HISTORY(roamerIndex)[i][MAP_NUM] = 0;
    }
}

void MoveAllRoamersToOtherLocationSets(void)
{
    u32 i;

    for (i = 0; i < CURRENT_ROAMER_COUNT; i++)
        RoamerMoveToOtherLocationSet(i);
}

void MoveAllRoamers(void)
{
    u32 i;

    for (i = 0; i < CURRENT_ROAMER_COUNT; i++)
    {
        RoamerMove(i);
        if (ROAMER(i)->active)
            TryAttractRoamer(i);
    }
}

static void CreateInitialRoamerMon(u8 index, u16 species, u8 level, u8 locationTableId)
{
    ROAMER_BEFORE_WRITE(index);

    ClearRoamerLocationHistory(index);
    ROAMER(index)->locationTableId = locationTableId;
    u32 personality = GetMonPersonality(species,
        GetSynchronizedGender(ROAMER_ORIGIN, species),
        GetSynchronizedNature(ROAMER_ORIGIN, species),
        RANDOM_UNOWN_LETTER);
    CreateMonWithIVs(&gEnemyParty[0], species, level, personality, OTID_STRUCT_PLAYER_ID, USE_RANDOM_IVS);
    GiveMonInitialMoveset(&gEnemyParty[0]);
    ROAMER(index)->ivs = GetMonData(&gEnemyParty[0], MON_DATA_IVS);
    ROAMER(index)->personality = GetMonData(&gEnemyParty[0], MON_DATA_PERSONALITY);
    ROAMER(index)->species = species;
    ROAMER(index)->level = level;
    ROAMER(index)->statusA = 0;
    ROAMER(index)->statusB = 0;
    ROAMER(index)->hp = GetMonData(&gEnemyParty[0], MON_DATA_MAX_HP);
    ROAMER(index)->cool = GetMonData(&gEnemyParty[0], MON_DATA_COOL);
    ROAMER(index)->beauty = GetMonData(&gEnemyParty[0], MON_DATA_BEAUTY);
    ROAMER(index)->cute = GetMonData(&gEnemyParty[0], MON_DATA_CUTE);
    ROAMER(index)->smart = GetMonData(&gEnemyParty[0], MON_DATA_SMART);
    ROAMER(index)->tough = GetMonData(&gEnemyParty[0], MON_DATA_TOUGH);
    ROAMER(index)->shiny = GetMonData(&gEnemyParty[0], MON_DATA_IS_SHINY);
    ROAMER(index)->active = TRUE;
    ROAMER_LOCATION(index)[MAP_GRP] = ROAMER_MAP_GROUP;
    const u8 (*locs)[6] = GetRoamerLocations(index);
    u8 numSets = GetRoamerNumLocationSets(index);
    ROAMER_LOCATION(index)[MAP_NUM] = locs[Random() % numSets][0];
}

static u8 GetFirstInactiveRoamerIndex(void)
{
    u32 i;

    for (i = 0; i < CURRENT_ROAMER_COUNT; i++)
    {
        if (!ROAMER(i)->active)
            return i;
    }
    return CURRENT_ROAMER_COUNT;
}

bool8 TryAddRoamer(u16 species, u8 level, u8 locationTableId)
{
    u8 index = GetFirstInactiveRoamerIndex();

    if (index < CURRENT_ROAMER_COUNT)
    {
        CreateInitialRoamerMon(index, species, level, locationTableId);
        return TRUE;
    }

    return FALSE;
}

// gSpecialVar_0x8004 here corresponds to the options in the multichoice MULTI_TV_LATI (0 for 'Red', 1 for 'Blue')
void InitRoamer(void)
{
    if (IsJohtoRoamerContext())
    {
        if (GetCurrentRoamerCount() == 0)
            return;
        DeactivateRoamersByLocationTable(0);
        GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_ENTEI), FLAG_SET_SEEN);
        GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_RAIKOU), FLAG_SET_SEEN);
        GetSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_SUICUNE), FLAG_SET_SEEN);
        TryAddRoamer(SPECIES_RAIKOU, 40, 0);
        TryAddRoamer(SPECIES_ENTEI, 40, 0);
        return;
    }
    if (gSpecialVar_0x8004 == 0) // Red
        TryAddRoamer(SPECIES_LATIAS, 40, ROAMER_LOC_TABLE_HOENN);
    else
        TryAddRoamer(SPECIES_LATIOS, 40, ROAMER_LOC_TABLE_HOENN);
}

void InitKantoRoamers(void)
{
}

void UpdateLocationHistoryForRoamer(void)
{
    ROAMER_BEFORE_WRITE(0);

    u32 i;

    for (i = 0; i < CURRENT_ROAMER_COUNT; i++)
    {
        ROAMER_HISTORY(i)[2][MAP_GRP] = ROAMER_HISTORY(i)[1][MAP_GRP];
        ROAMER_HISTORY(i)[2][MAP_NUM] = ROAMER_HISTORY(i)[1][MAP_NUM];

        ROAMER_HISTORY(i)[1][MAP_GRP] = ROAMER_HISTORY(i)[0][MAP_GRP];
        ROAMER_HISTORY(i)[1][MAP_NUM] = ROAMER_HISTORY(i)[0][MAP_NUM];

        ROAMER_HISTORY(i)[0][MAP_GRP] = gSaveBlock1Ptr->location.mapGroup;
        ROAMER_HISTORY(i)[0][MAP_NUM] = gSaveBlock1Ptr->location.mapNum;
    }
}

void RoamerMoveToOtherLocationSet(u32 roamerIndex)
{
    ROAMER_BEFORE_WRITE(roamerIndex);

    u8 mapNum = 0;

    if (!ROAMER(roamerIndex)->active)
        return;

    const u8 (*locs)[6] = GetRoamerLocations(roamerIndex);
    u8 numSets = GetRoamerNumLocationSets(roamerIndex);

    ROAMER_LOCATION(roamerIndex)[MAP_GRP] = ROAMER_MAP_GROUP;

    do
    {
        mapNum = locs[Random() % numSets][0];
        if (ROAMER_LOCATION(roamerIndex)[MAP_NUM] != mapNum)
        {
            ROAMER_LOCATION(roamerIndex)[MAP_NUM] = mapNum;
            return;
        }
    } while (ROAMER_LOCATION(roamerIndex)[MAP_NUM] == mapNum);
    ROAMER_LOCATION(roamerIndex)[MAP_NUM] = mapNum;
}

void RoamerMove(u32 roamerIndex)
{
    ROAMER_BEFORE_WRITE(roamerIndex);

    u8 locSet = 0;

    if ((Random() % 16) == 0)
    {
        RoamerMoveToOtherLocationSet(roamerIndex);
    }
    else
    {
        if (!ROAMER(roamerIndex)->active)
            return;

        const u8 (*locs)[6] = GetRoamerLocations(roamerIndex);
        u8 numSets = GetRoamerNumLocationSets(roamerIndex);

        while (locSet < numSets)
        {
            if (ROAMER_LOCATION(roamerIndex)[MAP_NUM] == locs[locSet][0])
            {
                u8 mapNum;
                do
                {
                    mapNum = locs[locSet][(Random() % (NUM_LOCATIONS_PER_SET - 1)) + 1];
                } while (mapNum == MAP_NUM(MAP_UNDEFINED));
                ROAMER_LOCATION(roamerIndex)[MAP_NUM] = mapNum;
                return;
            }
            locSet++;
        }
    }
}

bool8 IsRoamerAt(u32 roamerIndex, u8 mapGroup, u8 mapNum)
{
    if (ROAMER(roamerIndex) == NULL)
        return FALSE;
    if (ROAMER(roamerIndex)->active && mapGroup == ROAMER_LOCATION(roamerIndex)[MAP_GRP] && mapNum == ROAMER_LOCATION(roamerIndex)[MAP_NUM])
        return TRUE;
    else
        return FALSE;
}

void CreateRoamerMonInstance(u32 roamerIndex)
{
    u32 status = ROAMER(roamerIndex)->statusA + (ROAMER(roamerIndex)->statusB << 8);
    struct Pokemon *mon = &gEnemyParty[0];
    ZeroEnemyPartyMons();
    CreateMonWithIVsPersonality(mon, ROAMER(roamerIndex)->species, ROAMER(roamerIndex)->level, ROAMER(roamerIndex)->ivs, ROAMER(roamerIndex)->personality);
    SetMonData(mon, MON_DATA_STATUS, &status);
    SetMonData(mon, MON_DATA_HP, &ROAMER(roamerIndex)->hp);
    SetMonData(mon, MON_DATA_COOL, &ROAMER(roamerIndex)->cool);
    SetMonData(mon, MON_DATA_BEAUTY, &ROAMER(roamerIndex)->beauty);
    SetMonData(mon, MON_DATA_CUTE, &ROAMER(roamerIndex)->cute);
    SetMonData(mon, MON_DATA_SMART, &ROAMER(roamerIndex)->smart);
    SetMonData(mon, MON_DATA_TOUGH, &ROAMER(roamerIndex)->tough);
    SetMonData(mon, MON_DATA_IS_SHINY, &ROAMER(roamerIndex)->shiny);
}

bool8 TryStartRoamerEncounter(void)
{
    u32 i;

    for (i = 0; i < CURRENT_ROAMER_COUNT; i++)
    {
        if (IsRoamerAt(i, gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum) == TRUE && (Random() % 4) == 0)
        {
            CreateRoamerMonInstance(i);
            gEncounteredRoamerIndex = i | (IsJohtoRoamerContext() ? JOHTO_ROAMER_ENCOUNTER_TAG : 0);
            return TRUE;
        }
    }
    return FALSE;
}

void UpdateRoamerHPStatus(struct Pokemon *mon)
{
    ROAMER_BEFORE_WRITE(gEncounteredRoamerIndex);

    u32 status = GetMonData(mon, MON_DATA_STATUS);

    ROAMER(gEncounteredRoamerIndex)->hp = GetMonData(mon, MON_DATA_HP);
    ROAMER(gEncounteredRoamerIndex)->statusA = status;
    ROAMER(gEncounteredRoamerIndex)->statusB = status >> 8;

    RoamerMoveToOtherLocationSet(gEncounteredRoamerIndex);
}

void SetRoamerInactive(u32 roamerIndex)
{
    ROAMER_BEFORE_WRITE(roamerIndex);

    ROAMER(roamerIndex)->active = FALSE;
}

void GetRoamerLocation(u32 roamerIndex, u8 *mapGroup, u8 *mapNum)
{
    if (ROAMER(roamerIndex) == NULL)
    {
        *mapGroup = MAP_GROUP(MAP_UNDEFINED);
        *mapNum = MAP_NUM(MAP_UNDEFINED);
        return;
    }
    *mapGroup = ROAMER_LOCATION(roamerIndex)[MAP_GRP];
    *mapNum = ROAMER_LOCATION(roamerIndex)[MAP_NUM];
}

#define ROAMER_FLASH_VOBJ_ID 0xFF
#define ROAMER_FLASH_HORZ_SPEED 12
#define ROAMER_FLASH_VERT_SPEED 8

enum {
    ROAMER_FLASH_NONE,
    ROAMER_FLASH_CROSS_PATH,
    ROAMER_FLASH_RACE_PAST,
    ROAMER_FLASH_PEEK,
    ROAMER_FLASH_COUNT,
};

#define tSpriteId   data[0]
#define tDeltaX     data[1]
#define tDeltaY     data[2]
#define tFrames     data[3]
#define tMaxFrames  data[4]

static void DestroyRoamerFlashSprite(struct Sprite *sprite)
{
    u8 paletteNum = sprite->oam.paletteNum;
    u16 tileStart = sprite->sheetTileStart;
    DestroySprite(sprite);
    FieldEffectFreePaletteIfUnused(paletteNum);
    if (tileStart)
        FieldEffectFreeTilesIfUnused(tileStart);
}

static void Task_RoamerFlash(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    struct Sprite *sprite = &gSprites[task->tSpriteId];

    sprite->x += task->tDeltaX;
    sprite->y += task->tDeltaY;
    task->tFrames++;

    if (task->tFrames >= task->tMaxFrames)
    {
        DestroyRoamerFlashSprite(sprite);
        DestroyTask(taskId);
    }
}

enum {
    PEEK_PHASE_ENTER,
    PEEK_PHASE_LOOK_1,
    PEEK_PHASE_LOOK_2,
    PEEK_PHASE_EXIT,
};

#define tPhase      data[5]

static void Task_RoamerPeek(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    struct Sprite *sprite = &gSprites[task->tSpriteId];

    task->tFrames++;

    switch (task->tPhase)
    {
    case PEEK_PHASE_ENTER:
        sprite->y -= 3;
        if (task->tFrames >= 22)
        {
            task->tFrames = 0;
            task->tPhase = PEEK_PHASE_LOOK_1;
            TurnVirtualObject(ROAMER_FLASH_VOBJ_ID, DIR_WEST);
        }
        break;
    case PEEK_PHASE_LOOK_1:
        if (task->tFrames >= 10)
        {
            task->tFrames = 0;
            task->tPhase = PEEK_PHASE_LOOK_2;
            TurnVirtualObject(ROAMER_FLASH_VOBJ_ID, DIR_NORTH);
        }
        break;
    case PEEK_PHASE_LOOK_2:
        if (task->tFrames >= 8)
        {
            task->tFrames = 0;
            task->tPhase = PEEK_PHASE_EXIT;
            TurnVirtualObject(ROAMER_FLASH_VOBJ_ID, DIR_SOUTH);
        }
        break;
    case PEEK_PHASE_EXIT:
        sprite->y += 5;
        if (task->tFrames >= 28)
        {
            DestroyRoamerFlashSprite(sprite);
            DestroyTask(taskId);
        }
        break;
    }
}

static u16 GetFirstRoamerSpeciesOnCurrentMap(void)
{
    u32 i;

    for (i = 0; i < CURRENT_ROAMER_COUNT; i++)
    {
        if (IsRoamerAt(i, gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum))
            return ROAMER(i)->species;
    }
    return SPECIES_NONE;
}

void TryShowRoamerFlash(void)
{
    u16 species = GetFirstRoamerSpeciesOnCurrentMap();
    u8 spriteId;
    u8 taskId;
    s16 startX, startY;
    s16 playerX = gSaveBlock1Ptr->pos.x;
    s16 playerY = gSaveBlock1Ptr->pos.y;
    u8 facing = GetPlayerFacingDirection();
    u8 flashType;
    s16 deltaX = 0;
    s16 deltaY = 0;
    s16 maxFrames = 0;
    enum Direction spriteDir;

    if (species == SPECIES_NONE)
        return;

    if (CountFreeSpriteTiles() < 64)
        return;

    flashType = Random() % ROAMER_FLASH_COUNT;

    if (flashType == ROAMER_FLASH_NONE)
        return;

    PlayCry_Normal(species, 0);

    if (flashType == ROAMER_FLASH_CROSS_PATH)
    {
        switch (facing)
        {
        case DIR_NORTH:
            startX = playerX + 10;
            startY = playerY - 7;
            deltaX = -ROAMER_FLASH_VERT_SPEED;
            spriteDir = DIR_WEST;
            break;
        case DIR_SOUTH:
            startX = playerX - 10;
            startY = playerY + 7;
            deltaX = ROAMER_FLASH_VERT_SPEED;
            spriteDir = DIR_EAST;
            break;
        case DIR_EAST:
            startX = playerX + 7;
            startY = playerY - 10;
            deltaY = ROAMER_FLASH_VERT_SPEED;
            spriteDir = DIR_SOUTH;
            break;
        case DIR_WEST:
        default:
            startX = playerX - 7;
            startY = playerY - 10;
            deltaY = ROAMER_FLASH_VERT_SPEED;
            spriteDir = DIR_SOUTH;
            break;
        }
        maxFrames = (20 * 16) / ROAMER_FLASH_VERT_SPEED;
    }
    else if (flashType == ROAMER_FLASH_RACE_PAST)
    {
        startY = playerY - 4;
        if (facing == DIR_EAST)
        {
            startX = playerX - 12;
            deltaX = ROAMER_FLASH_HORZ_SPEED;
            spriteDir = DIR_EAST;
        }
        else
        {
            startX = playerX + 12;
            deltaX = -ROAMER_FLASH_HORZ_SPEED;
            spriteDir = DIR_WEST;
        }
        maxFrames = (24 * 16) / ROAMER_FLASH_HORZ_SPEED;
    }
    else
    {
        if (facing == DIR_EAST || facing == DIR_SOUTH)
            startX = playerX + 6;
        else
            startX = playerX - 6;
        startY = playerY + 8;
        spriteDir = DIR_NORTH;
    }

    spriteId = CreateVirtualObject(
        OBJ_EVENT_GFX_MON_BASE + species,
        ROAMER_FLASH_VOBJ_ID,
        startX, startY,
        3, spriteDir
    );

    if (spriteId == MAX_SPRITES)
        return;

    if (OW_GFX_COMPRESS && gSprites[spriteId].sheetTileStart == TAG_NONE)
    {
        DestroyRoamerFlashSprite(&gSprites[spriteId]);
        return;
    }

    if (flashType == ROAMER_FLASH_PEEK)
    {
        taskId = CreateTask(Task_RoamerPeek, 80);
        gTasks[taskId].tSpriteId = spriteId;
        gTasks[taskId].tFrames = 0;
        gTasks[taskId].tPhase = PEEK_PHASE_ENTER;
    }
    else
    {
        taskId = CreateTask(Task_RoamerFlash, 80);
        gTasks[taskId].tSpriteId = spriteId;
        gTasks[taskId].tDeltaX = deltaX;
        gTasks[taskId].tDeltaY = deltaY;
        gTasks[taskId].tFrames = 0;
        gTasks[taskId].tMaxFrames = maxFrames;
    }
}

#undef tSpriteId
#undef tDeltaX
#undef tDeltaY
#undef tFrames
#undef tMaxFrames
#undef tPhase

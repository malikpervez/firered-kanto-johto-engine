#include "global.h"
#include "nuzlocke.h"
#include "challenge_menu.h"
#include "event_data.h"
#include "item.h"
#include "party_menu.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/party_menu.h"
#include "constants/region_map_sections.h"
#include "overworld.h"
#include "pokedex.h"
#include "constants/pokedex.h"
#include "battle.h"
#include "bug_contest.h"

EWRAM_DATA u8 NuzlockeIsCaptureBlocked = FALSE;
EWRAM_DATA u8 NuzlockeIsSpeciesClauseActive = FALSE;
EWRAM_DATA u8 OneTypeChallengeCaptureBlocked = FALSE;

// Zone-to-bit mapping for one-encounter-per-area tracking.
// Only locations with wild encounters should be listed.
// Egg hatching counts as an encounter in the hatching zone.
// Special/gift Pokemon do NOT consume the zone's encounter.
static const u8 sNuzlockeLUT[] =
{
    // Hoenn Routes
    [MAPSEC_ROUTE_101]        = 0x00,
    [MAPSEC_ROUTE_102]        = 0x01,
    [MAPSEC_ROUTE_103]        = 0x02,
    [MAPSEC_ROUTE_104]        = 0x03,
    [MAPSEC_ROUTE_105]        = 0x04,
    [MAPSEC_ROUTE_106]        = 0x05,
    [MAPSEC_ROUTE_107]        = 0x06,
    [MAPSEC_ROUTE_108]        = 0x07,
    [MAPSEC_ROUTE_109]        = 0x08,
    [MAPSEC_ROUTE_110]        = 0x09,
    [MAPSEC_ROUTE_111]        = 0x0A,
    [MAPSEC_ROUTE_112]        = 0x0B,
    [MAPSEC_ROUTE_113]        = 0x0C,
    [MAPSEC_ROUTE_114]        = 0x0D,
    [MAPSEC_ROUTE_115]        = 0x0E,
    [MAPSEC_ROUTE_116]        = 0x0F,
    [MAPSEC_ROUTE_117]        = 0x10,
    [MAPSEC_ROUTE_118]        = 0x11,
    [MAPSEC_ROUTE_119]        = 0x12,
    [MAPSEC_ROUTE_120]        = 0x13,
    [MAPSEC_ROUTE_121]        = 0x14,
    [MAPSEC_ROUTE_122]        = 0x15,
    [MAPSEC_ROUTE_123]        = 0x16,
    [MAPSEC_ROUTE_124]        = 0x17,
    [MAPSEC_ROUTE_125]        = 0x18,
    [MAPSEC_ROUTE_126]        = 0x19,
    [MAPSEC_ROUTE_127]        = 0x1A,
    [MAPSEC_ROUTE_128]        = 0x1B,
    [MAPSEC_ROUTE_129]        = 0x1C,
    [MAPSEC_ROUTE_130]        = 0x1D,
    [MAPSEC_ROUTE_131]        = 0x1E,
    [MAPSEC_ROUTE_132]        = 0x1F,
    [MAPSEC_ROUTE_133]        = 0x20,
    [MAPSEC_ROUTE_134]        = 0x21,
    // Hoenn Dungeons
    [MAPSEC_GRANITE_CAVE]     = 0x22,
    [MAPSEC_MT_CHIMNEY]       = 0x23,
    [MAPSEC_PETALBURG_WOODS]  = 0x24,
    [MAPSEC_RUSTURF_TUNNEL]   = 0x25,
    [MAPSEC_ABANDONED_SHIP]   = 0x26,
    [MAPSEC_NEW_MAUVILLE]     = 0x27,
    [MAPSEC_METEOR_FALLS]     = 0x28,
    [MAPSEC_MT_PYRE]          = 0x29,
    [MAPSEC_SHOAL_CAVE]       = 0x2A,
    [MAPSEC_SEAFLOOR_CAVERN]  = 0x2B,
    [MAPSEC_VICTORY_ROAD]     = 0x2C,
    [MAPSEC_CAVE_OF_ORIGIN]   = 0x2D,
    [MAPSEC_FIERY_PATH]       = 0x2E,
    [MAPSEC_JAGGED_PASS]      = 0x2F,
    [MAPSEC_SKY_PILLAR]       = 0x30,
    [MAPSEC_SAFARI_ZONE]      = 0x31,
    [MAPSEC_SCORCHED_SLAB]    = 0x32,
    [MAPSEC_ISLAND_CAVE]      = 0x33,
    [MAPSEC_DESERT_RUINS]     = 0x34,
    [MAPSEC_ANCIENT_TOMB]     = 0x35,
    [MAPSEC_MIRAGE_ISLAND]    = 0x36,
    [MAPSEC_ARTISAN_CAVE]     = 0x37,
    [MAPSEC_MARINE_CAVE]      = 0x38,
    [MAPSEC_TERRA_CAVE]       = 0x39,
    [MAPSEC_DESERT_UNDERPASS] = 0x3A,
    [MAPSEC_ALTERING_CAVE]    = 0x3B,
    // Kanto Routes
    [MAPSEC_ROUTE_1]          = 0x3C,
    [MAPSEC_ROUTE_2]          = 0x3D,
    [MAPSEC_ROUTE_3]          = 0x3E,
    [MAPSEC_ROUTE_4]          = 0x3F,
    [MAPSEC_ROUTE_5]          = 0x40,
    [MAPSEC_ROUTE_6]          = 0x41,
    [MAPSEC_ROUTE_7]          = 0x42,
    [MAPSEC_ROUTE_8]          = 0x43,
    [MAPSEC_ROUTE_9]          = 0x44,
    [MAPSEC_ROUTE_10]         = 0x45,
    [MAPSEC_ROUTE_11]         = 0x46,
    [MAPSEC_ROUTE_12]         = 0x47,
    [MAPSEC_ROUTE_13]         = 0x48,
    [MAPSEC_ROUTE_14]         = 0x49,
    [MAPSEC_ROUTE_15]         = 0x4A,
    [MAPSEC_ROUTE_16]         = 0x4B,
    [MAPSEC_ROUTE_17]         = 0x4C,
    [MAPSEC_ROUTE_18]         = 0x4D,
    [MAPSEC_ROUTE_19]         = 0x4E,
    [MAPSEC_ROUTE_20]         = 0x4F,
    [MAPSEC_ROUTE_21]         = 0x50,
    [MAPSEC_ROUTE_22]         = 0x51,
    [MAPSEC_ROUTE_23]         = 0x52,
    [MAPSEC_ROUTE_24]         = 0x53,
    [MAPSEC_ROUTE_25]         = 0x54,
    // Kanto Dungeons
    [MAPSEC_VIRIDIAN_FOREST]  = 0x55,
    [MAPSEC_MT_MOON]          = 0x56,
    [MAPSEC_DIGLETTS_CAVE]    = 0x57,
    [MAPSEC_KANTO_VICTORY_ROAD] = 0x58,
    [MAPSEC_ROCK_TUNNEL]      = 0x59,
    [MAPSEC_SEAFOAM_ISLANDS]  = 0x5A,
    [MAPSEC_CERULEAN_CAVE]    = 0x5B,
    [MAPSEC_POWER_PLANT]      = 0x5C,
    [MAPSEC_POKEMON_TOWER]    = 0x5D,
    [MAPSEC_POKEMON_MANSION]  = 0x5E,
    [MAPSEC_KANTO_SAFARI_ZONE] = 0x5F,
    // FRLG Islands
    [MAPSEC_MT_EMBER]         = 0x60,
    [MAPSEC_BERRY_FOREST]     = 0x61,
    [MAPSEC_ICEFALL_CAVE]     = 0x62,
    [MAPSEC_LOST_CAVE]        = 0x63,
    [MAPSEC_PATTERN_BUSH]     = 0x64,
    [MAPSEC_BATTLE_FRONTIER]  = 0x65,
};

// The Bug Catching Contest and the Safari Zone hand out balls and expect the
// player to throw them freely, so the one-encounter-per-zone rule is suspended
// for their duration. Everything else about the Nuzlocke (deaths, revive
// blocking, PC rules) stays live -- clearing FLAG_START_NUZLOCKE would switch
// all of it off and let a Pokemon Center heal the dead mons in the PC.
bool8 IsNuzlockeCaptureSuspended(void)
{
    return FlagGet(FLAG_SYS_SAFARI_MODE) || GetBugContestFlag();
}

bool8 IsNuzlockeActive(void)
{
    struct ChallengeSettings *cs = &gSaveBlock3Ptr->challengeSettings;

    if (!FlagGet(FLAG_SYS_POKEMON_GET))
        return FALSE;
    if (!FlagGet(FLAG_START_NUZLOCKE))
        return FALSE;
    if (FlagGet(FLAG_END_NUZLOCKE))
        return FALSE;

    return cs->tx_Challenges_Nuzlocke;
}

bool8 IsNuzlockeEasyActive(void)
{
    struct ChallengeSettings *cs = &gSaveBlock3Ptr->challengeSettings;

    if (!FlagGet(FLAG_SYS_POKEMON_GET))
        return FALSE;
    if (!FlagGet(FLAG_START_NUZLOCKE))
        return FALSE;
    if (FlagGet(FLAG_END_NUZLOCKE))
        return FALSE;

    return cs->tx_Nuzlocke_EasyMode && !cs->tx_Challenges_Nuzlocke;
}

bool8 IsNuzlockeNicknamingActive(void)
{
    struct ChallengeSettings *cs = &gSaveBlock3Ptr->challengeSettings;

    if (!cs->tx_Challenges_Nuzlocke)
        return FALSE;
    if (FlagGet(FLAG_END_NUZLOCKE))
        return FALSE;

    return cs->tx_Nuzlocke_Nicknaming;
}

u8 NuzlockeFlagSet(u16 mapsec)
{
    // The B2 visit has no encounter allocation; never read an absent LUT entry.
    if (mapsec >= ARRAY_COUNT(sNuzlockeLUT))
        return 0;
    u16 id = sNuzlockeLUT[mapsec];
    u8 *ptr = &gSaveBlock3Ptr->challengeSettings.nuzlockeEncounterFlags[id / 8];

    *ptr |= 1 << (id & 7);
    return 0;
}

u8 NuzlockeFlagClear(u16 mapsec)
{
    if (mapsec >= ARRAY_COUNT(sNuzlockeLUT))
        return 0;
    u16 id = sNuzlockeLUT[mapsec];
    u8 *ptr = &gSaveBlock3Ptr->challengeSettings.nuzlockeEncounterFlags[id / 8];

    *ptr &= ~(1 << (id & 7));
    return 0;
}

u8 NuzlockeFlagGet(u16 mapsec)
{
    if (mapsec >= ARRAY_COUNT(sNuzlockeLUT))
        return 0;
    u16 id = sNuzlockeLUT[mapsec];
    u8 *ptr = &gSaveBlock3Ptr->challengeSettings.nuzlockeEncounterFlags[id / 8];

    if (!((*ptr >> (id & 7)) & 1))
        return 0;
    return 1;
}

void NuzlockeDeletePartyMon(u8 position)
{
    struct ChallengeSettings *cs = &gSaveBlock3Ptr->challengeSettings;

    if (!cs->tx_Nuzlocke_Deletion)
    {
        CopyMonToPC(&gPlayerParty[position]);
    }
    PurgeMonOrBoxMon(TOTAL_BOXES_COUNT, position);
}

void NuzlockeDeletePartyMonOption(u8 position)
{
    CopyMonToPC(&gPlayerParty[position]);
    PurgeMonOrBoxMon(TOTAL_BOXES_COUNT, position);
}

void NuzlockeDeleteFaintedPartyPokemon(void)
{
    u8 i;
    struct Pokemon *pokemon;
    u16 item = ITEM_NONE;
    struct ChallengeSettings *cs = &gSaveBlock3Ptr->challengeSettings;

    // The Bug Contest lends the player a one-mon party (SavePlayerParty on entry,
    // LoadPlayerParty on exit), so a faint there is not a real death -- the mon
    // comes back with the restored party. Deleting it here would only leave a
    // duplicate corpse in the PC under the cemetery option.
    if (GetBugContestFlag())
        return;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        pokemon = &gPlayerParty[i];
        if (GetMonData(pokemon, MON_DATA_SANITY_HAS_SPECIES, NULL)
            && !GetMonData(pokemon, MON_DATA_IS_EGG, NULL))
        {
            if (GetMonAilment(pokemon) == AILMENT_FNT)
            {
                u32 monItem = GetMonData(pokemon, MON_DATA_HELD_ITEM, NULL);
                if (monItem != ITEM_NONE)
                {
                    AddBagItem(monItem, 1);
                    SetMonData(pokemon, MON_DATA_HELD_ITEM, &item);
                }
                if (IsNuzlockeEasyActive())
                    NuzlockeDeletePartyMonOption(i);
                else
                    NuzlockeDeletePartyMon(i);
            }
        }
    }
    CompactPartySlots();
}

u8 NuzlockeGetCurrentRegionMapSectionId(void)
{
    return GetCurrentRegionMapSectionId();
}

static bool8 IsEvoFamilyCaught(u16 species)
{
    const struct Evolution *evolutions;
    int i;

    if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_GET_CAUGHT))
        return TRUE;

    evolutions = GetSpeciesEvolutions(species);
    if (evolutions == NULL)
        return FALSE;

    for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
    {
        if (IsEvoFamilyCaught(evolutions[i].targetSpecies))
            return TRUE;
    }
    return FALSE;
}

u8 NuzlockeIsCaptureBlockedBySpeciesClause(u16 species)
{
    u16 baseSpecies;
    struct ChallengeSettings *cs = &gSaveBlock3Ptr->challengeSettings;

    if (!cs->tx_Nuzlocke_SpeciesClause)
        return FALSE;

    if (GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_GET_CAUGHT))
        return 2;

    baseSpecies = species;
    while (GetSpeciesPreEvolution(baseSpecies) != SPECIES_NONE)
        baseSpecies = GetSpeciesPreEvolution(baseSpecies);

    if (IsEvoFamilyCaught(baseSpecies))
        return TRUE;

    return FALSE;
}

void SetNuzlockeChecks(void)
{
    OneTypeChallengeCaptureBlocked = !DoesSpeciesPassOneTypeChallenge(
        GetMonData(&gEnemyParty[0], MON_DATA_SPECIES));

    if (IsNuzlockeActive() && !IsNuzlockeCaptureSuspended())
    {
        NuzlockeIsSpeciesClauseActive = NuzlockeIsCaptureBlockedBySpeciesClause(
            GetMonData(&gEnemyParty[0], MON_DATA_SPECIES));

        NuzlockeIsCaptureBlocked = NuzlockeFlagGet(NuzlockeGetCurrentRegionMapSectionId());

        if ((IsMonShiny(&gEnemyParty[0]) && gSaveBlock3Ptr->challengeSettings.tx_Nuzlocke_ShinyClause)
            || (GetMonData(&gEnemyParty[0], MON_DATA_MODERN_FATEFUL_ENCOUNTER, NULL)))
        {
            NuzlockeIsCaptureBlocked = FALSE;
            NuzlockeIsSpeciesClauseActive = FALSE;
        }
    }
    else
    {
        NuzlockeIsCaptureBlocked = FALSE;
        NuzlockeIsSpeciesClauseActive = FALSE;
    }
}

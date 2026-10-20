#include "global.h"

#include "event_data.h"
#include "firered_save.h"
#include "johto_campaign.h"
#include "regional_save.h"
#include "script.h"
#include "string_util.h"
#include "strings.h"
#include "constants/characters.h"

STATIC_ASSERT(3 + JOHTO_CAMPAIGN_RAW_FLAG_COUNT - 32 - JOHTO_CAMPAIGN_RAW_TRAINER_COUNT <= REGIONAL_SAVE_EVENT_COUNT, JohtoCampaignEventBound);
STATIC_ASSERT(JOHTO_CAMPAIGN_RAW_TRAINER_COUNT <= REGIONAL_SAVE_TRAINER_COUNT, JohtoCampaignTrainerBound);
STATIC_ASSERT(1 + JOHTO_CAMPAIGN_RAW_VAR_LAST - JOHTO_CAMPAIGN_RAW_VAR_FIRST + 1 == REGIONAL_SAVE_VAR_COUNT, JohtoCampaignVariableBound);
STATIC_ASSERT((REGIONAL_SAVE_VARS_OFFSET & 1) == 0, JohtoCampaignVariablesAligned);

// Actual HnS reset-map defaults from data/scripts/new_game.inc. Null flag
// aliases are omitted; no native flag, party, inventory or option is reset.
static const u16 sInitialFlags[] =
{
    0x04C, // FLAG_HIDE_LAB_POLICEMAN: skipped resident Mom intro, upstream line230
    0x0E6, // FLAG_HIDE_BATTLE_TOWER_OPPONENT, upstream line322
    0x2E6, // FLAG_HIDE_DEOXYS, upstream line323
    0x04E, // FLAG_HIDE_MOMS_FRIEND2, upstream line325
    0x051, // FLAG_HIDE_SILVER_CHERRYGROVE, upstream line326
    0x04F, // FLAG_HIDE_ROUTE_30_NPCS, upstream line327
    0x050, // FLAG_HIDE_MRPOKEMON, upstream line328
    0x0DA, // FLAG_HIDE_TOHJO_GIOVANNI, upstream line329
    0x0A7, // FLAG_HIDE_LEAGUE_BLACKBELT, upstream line330
    0x0BF, // FLAG_HIDE_CELADON_FALKNER, upstream line331
    0x0C9, // FLAG_HIDE_DOJO_FALKNER, upstream line332
    0x0B0, // FLAG_HIDE_VIRIDIAN_BUGSY, upstream line333
    0x0C5, // FLAG_HIDE_DOJO_BUGSY, upstream line334
    0x070, // FLAG_HIDE_DEPTSTORE_WHITNEY, upstream line335
    0x0D1, // FLAG_HIDE_DOJO_WHITNEY, upstream line336
    0x07F, // FLAG_HIDE_BELLCHIME_MORTY, upstream line337
    0x0CD, // FLAG_HIDE_DOJO_MORTY, upstream line338
    0x0C6, // FLAG_HIDE_DOJO_CHUCK, upstream line339
    0x089, // FLAG_HIDE_CAFE_JASMINE, upstream line340
    0x0CB, // FLAG_HIDE_DOJO_JASMINE, upstream line341
    0x09D, // FLAG_HIDE_LAKE_PRYCE, upstream line342
    0x0CE, // FLAG_HIDE_DOJO_PRYCE, upstream line343
    0x09E, // FLAG_HIDE_DEN_CLAIR, upstream line344
    0x0C7, // FLAG_HIDE_DOJO_CLAIR, upstream line345
    0x0B3, // FLAG_HIDE_DIGLETT_BROCK, upstream line346
    0x0C4, // FLAG_HIDE_DOJO_BROCK, upstream line347
    0x0B8, // FLAG_HIDE_CAPE_MISTY, upstream line348
    0x0CC, // FLAG_HIDE_DOJO_MISTY, upstream line349
    0x0BD, // FLAG_HIDE_PLANT_SURGE, upstream line350
    0x0D0, // FLAG_HIDE_DOJO_SURGE, upstream line351
    0x0C1, // FLAG_HIDE_FOUNTAIN_ERIKA, upstream line352
    0x0C8, // FLAG_HIDE_DOJO_ERIKA, upstream line353
    0x0D9, // FLAG_HIDE_ROUTE22_JANINE, upstream line354
    0x0CA, // FLAG_HIDE_DOJO_JANINE, upstream line355
    0x082, // FLAG_HIDE_OLIVINE_SABRINA, upstream line356
    0x0CF, // FLAG_HIDE_DOJO_SABRINA, upstream line357
    0x0D4, // FLAG_HIDE_CINNABAR_BLAINE, upstream line358
    0x0C2, // FLAG_HIDE_DOJO_BLAINE, upstream line359
    0x0C3, // FLAG_HIDE_DOJO_BLUE, upstream line360
    0x063, // FLAG_HIDE_ILEX_FOREST_SECOND_CELEBI, upstream line361
    0x081, // FLAG_HIDE_OLIVINE_PORT_OAK, upstream line362
    0x0D8, // FLAG_HIDE_ROUTE22_GIOVANNI_SILVER, upstream line363
    0x049, // FLAG_HIDE_MTMOON_JIRACHI, upstream line364
    0x446, // FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU, upstream line365
    0x442, // FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU1, upstream line366
    0x443, // FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU2, upstream line367
    0x444, // FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU3, upstream line368
    0x445, // FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU4, upstream line369
    0x45E, // FLAG_HIDE_ROUTE13_BOAT, upstream line370
    0x3CE, // FLAG_HIDE_AZALEA_TOWN_TAILED_SLOWPOKES, upstream line371
    0x3CF, // FLAG_HIDE_VERMILION_CITY_SAMSON, upstream line372
    0x3D0, // FLAG_HIDE_ROUTE28_SCIENTIST, upstream line373
    0x3D1, // FLAG_EXTENDED_CONTENT_SET_103, upstream line374
    0x3D2, // FLAG_EXTENDED_CONTENT_SET_104, upstream line375
    0x3D3, // FLAG_EXTENDED_CONTENT_SET_105, upstream line376
    0x3D4, // FLAG_EXTENDED_CONTENT_SET_106, upstream line377
    0x3D5, // FLAG_EXTENDED_CONTENT_SET_107, upstream line378
    0x3D6, // FLAG_EXTENDED_CONTENT_SET_108, upstream line379
    0x3D7, // FLAG_EXTENDED_CONTENT_SET_109, upstream line380
    0x3D8, // FLAG_EXTENDED_CONTENT_SET_110, upstream line381
    0x2F7, // FLAG_HIDE_ICEPATH_B2F_BOULDER1, upstream line382
    0x2F8, // FLAG_HIDE_ICEPATH_B2F_BOULDER2, upstream line383
    0x2F9, // FLAG_HIDE_ICEPATH_B2F_BOULDER3, upstream line384
    0x2FA, // FLAG_HIDE_ICEPATH_B2F_BOULDER4, upstream line385
};

static const u16 sInitialVariables[] =
{
    0x4091, // VAR_VIOLET_CITY_STATE, upstream line422
    0x405A, // VAR_CHERRYGROVE_CITY_STATE, upstream line423
    0x4053, // VAR_AZALEA_TOWN_STATE, upstream line424
    0x4069, // VAR_GOLDENROD_CITY_STATE, upstream line425
    0x4061, // VAR_ECRUTEAK_CITY_STATE, upstream line426
    0x4072, // VAR_MAHOGANY_TOWN_STATE, upstream line427
    0x4077, // VAR_OLIVINE_CITY_STATE, upstream line428
    0x405B, // VAR_CIANWOOD_CITY_STATE, upstream line429
    0x4085, // VAR_SAFARI_ZONE_GATE_STATE, upstream line430
    0x4056, // VAR_BLACKTHORN_CITY_STATE, upstream line431
    0x4094, // VAR_PALLET_TOWN_STATE, upstream line432
    0x40C1, // VAR_VIRIDIAN_CITY_STATE, upstream line433
    0x4079, // VAR_PEWTER_CITY_STATE, upstream line434
    0x4059, // VAR_CERULEAN_CITY_STATE, upstream line435
    0x408F, // VAR_VERMILION_CITY_STATE, upstream line436
    0x4096, // VAR_LAVENDER_TOWN_STATE, upstream line437
    0x4093, // VAR_CELADON_CITY_STATE, upstream line438
    0x40BD, // VAR_SAFFRON_CITY_STATE, upstream line439
    0x4067, // VAR_FUCHSIA_CITY_STATE, upstream line440
    0x405C, // VAR_CINNABAR_ISLAND_STATE, upstream line441
    0x4073, // VAR_MT_SILVER_STATE, upstream line442
    0x4082, // VAR_ROUTE27_STATE, upstream line443
    0x4070, // VAR_LEAGUE_STATE, upstream line444
    0x408B, // VAR_SSAQUA_STATE, upstream line445
    0x408C, // VAR_SUICUNE_ENCOUNTERS, upstream line446
    0x4076, // VAR_NUM_BADGES, upstream line447
    0x406D, // VAR_KANTO_SAFARI_ZONE_PROGRESS, upstream line448
    0x4054, // VAR_BAOBA_QUEST_STATE, upstream line449
    0x4078, // VAR_PALLETTOWN_LABSTATE, upstream line450
    0x408D, // VAR_TOHJO_FALLS_GIOVANNI_STATE, upstream line451
    0x4080, // VAR_ROUTE22_GIOVANNI_STATE, upstream line452
    0x4081, // VAR_ROUTE27_BAOBA_CALL, upstream line453
};

static bool8 FlagIndex(u16 rawId, u16 *index, bool8 *trainer)
{
    if (rawId < 32 || rawId >= JOHTO_CAMPAIGN_RAW_FLAG_COUNT)
        return FALSE;
    *trainer = rawId >= JOHTO_CAMPAIGN_RAW_TRAINER_START
        && rawId < JOHTO_CAMPAIGN_RAW_TRAINER_START + JOHTO_CAMPAIGN_RAW_TRAINER_COUNT;
    if (*trainer)
        *index = rawId - JOHTO_CAMPAIGN_RAW_TRAINER_START;
    else
        *index = 3 + rawId - 32 - (rawId >= JOHTO_CAMPAIGN_RAW_TRAINER_START ? JOHTO_CAMPAIGN_RAW_TRAINER_COUNT : 0);
    return TRUE;
}

bool8 JohtoCampaign_IsFlagId(u16 id)
{
    return id >= JOHTO_CAMPAIGN_FLAG_ID_BASE && id < JOHTO_CAMPAIGN_FLAG_ID_PAGE_END;
}

bool8 JohtoCampaign_IsVarId(u16 id)
{
    return id >= JOHTO_CAMPAIGN_VAR_ID_BASE && id < JOHTO_CAMPAIGN_VAR_ID_PAGE_END;
}

bool8 JohtoCampaign_IsSeeded(void)
{
    const u8 *image = (const u8 *)gSaveBlock3Ptr;
    // Live compound writes may temporarily violate snapshot semantics. Bind
    // the typed views to registered metadata; full validation runs on saving.
    return image != NULL
        && memcmp(image + REGIONAL_SAVE_HEADER_OFFSET, "FRJS", 4) == 0
        && RegionalSave_Read16(image + REGIONAL_SAVE_SCHEMA_OFFSET) == REGIONAL_SAVE_SCHEMA
        && RegionalSave_Read16(image + REGIONAL_SAVE_HEADER_LENGTH_OFFSET) == REGIONAL_SAVE_HEADER_SIZE
        && RegionalSave_Read16(image + REGIONAL_SAVE_LENGTH_OFFSET) == REGIONAL_SAVE_SIZE
        && RegionalSave_Read16(image + REGIONAL_SAVE_RECORD_COUNT_OFFSET) == 2
        && RegionalSave_Read16(image + REGIONAL_SAVE_RESERVED_OFFSET) == 0
        && RegionalSave_Read32(image + REGIONAL_SAVE_LAYOUT_OFFSET) == REGIONAL_SAVE_LAYOUT_ID
        && RegionalSave_Read32(image + REGIONAL_SAVE_CONTENT_OFFSET) == REGIONAL_SAVE_CONTENT_ID
        && RegionalSave_Read16(image + REGIONAL_SAVE_FLAGS_OFFSET) == REGIONAL_SAVE_HEADER_CAMPAIGN_SEEDED
        && RegionalSave_Read16(image + REGIONAL_SAVE_KANTO_OFFSET) == REGIONAL_SAVE_KANTO
        && RegionalSave_Read16(image + REGIONAL_SAVE_KANTO_OFFSET + 2) == 1
        && RegionalSave_Read16(image + REGIONAL_SAVE_JOHTO_OFFSET) == REGIONAL_SAVE_JOHTO
        && RegionalSave_Read16(image + REGIONAL_SAVE_JOHTO_OFFSET + 2) == 1
        && RegionalSave_Read32(image + REGIONAL_SAVE_JOHTO_FLAGS_OFFSET) == REGIONAL_SAVE_JOHTO_INITIALIZED
        && RegionalSave_Read32(image + REGIONAL_SAVE_JOHTO_EVENT_REVISION_OFFSET) == REGIONAL_SAVE_CAMPAIGN_MAPPING_REVISION
        && RegionalSave_Read32(image + REGIONAL_SAVE_JOHTO_TRAINER_REVISION_OFFSET) == REGIONAL_SAVE_CAMPAIGN_MAPPING_REVISION
        && RegionalSave_Read32(image + REGIONAL_SAVE_JOHTO_VAR_REVISION_OFFSET) == REGIONAL_SAVE_CAMPAIGN_MAPPING_REVISION;
}

struct MomSavingsData *JohtoCampaign_GetMomSavings(void)
{
    if (!JohtoCampaign_IsSeeded())
        return NULL;
    return (struct MomSavingsData *)((u8 *)gSaveBlock3Ptr + REGIONAL_SAVE_MOM_SAVINGS_OFFSET);
}

struct Roamer *JohtoCampaign_GetDogRoamer(u32 index)
{
    if (index >= REGIONAL_SAVE_DOG_ROAMER_COUNT || !JohtoCampaign_IsSeeded())
        return NULL;
    return (struct Roamer *)((u8 *)gSaveBlock3Ptr + REGIONAL_SAVE_DOG_ROAMERS_OFFSET + index * REGIONAL_SAVE_DOG_ROAMER_SIZE);
}

u8 (*JohtoCampaign_GetDogLocationHistory(u32 index))[2]
{
    if (index >= REGIONAL_SAVE_DOG_ROAMER_COUNT || !JohtoCampaign_IsSeeded())
        return NULL;
    return (u8 (*)[2])((u8 *)gSaveBlock3Ptr + REGIONAL_SAVE_DOG_HISTORY_OFFSET + index * 3 * 2);
}

u8 *JohtoCampaign_GetDogLocation(u32 index)
{
    if (index >= REGIONAL_SAVE_DOG_ROAMER_COUNT || !JohtoCampaign_IsSeeded())
        return NULL;
    return (u8 *)gSaveBlock3Ptr + REGIONAL_SAVE_DOG_LOCATIONS_OFFSET + index * 2;
}

bool8 JohtoCampaign_GetFlag(u16 encodedId)
{
    u16 index;
    bool8 trainer;
    bool8 value = FALSE;
    if (!JohtoCampaign_IsFlagId(encodedId) || !JohtoCampaign_IsSeeded()
     || !FlagIndex(encodedId - JOHTO_CAMPAIGN_FLAG_ID_BASE, &index, &trainer))
        return FALSE;
    if (trainer)
        RegionalSave_GetTrainer((const u8 *)gSaveBlock3Ptr, REGIONAL_SAVE_JOHTO, index, &value);
    else
        RegionalSave_GetEvent((const u8 *)gSaveBlock3Ptr, REGIONAL_SAVE_JOHTO, index, &value);
    return value;
}

void JohtoCampaign_SetFlag(u16 encodedId, bool8 value)
{
    u8 *image = (u8 *)gSaveBlock3Ptr;
    u16 rawId;
    u16 index;
    bool8 trainer;
    if (!JohtoCampaign_IsFlagId(encodedId) || value > TRUE || !JohtoCampaign_IsSeeded())
        return;
    rawId = encodedId - JOHTO_CAMPAIGN_FLAG_ID_BASE;
    if (!FlagIndex(rawId, &index, &trainer) || JohtoCampaign_GetFlag(encodedId) == value)
        return;
    FireRedSave_NotifyPersistentWrite();
    if (trainer)
        RegionalSave_SetTrainer(image, REGIONAL_SAVE_JOHTO, index, value);
    else
        RegionalSave_SetEvent(image, REGIONAL_SAVE_JOHTO, index, value);
    if (rawId >= 0x880 && rawId <= 0x887)
    {
        if (value)
            image[REGIONAL_SAVE_JOHTO_BADGES_OFFSET] |= 1 << (rawId - 0x880);
        else
            image[REGIONAL_SAVE_JOHTO_BADGES_OFFSET] &= ~(1 << (rawId - 0x880));
    }
}

u16 *JohtoCampaign_GetVarPointer(u16 encodedId)
{
    u8 *image = (u8 *)gSaveBlock3Ptr;
    if (!JohtoCampaign_IsVarId(encodedId) || encodedId > JOHTO_CAMPAIGN_VAR_ID_LAST
     || !JohtoCampaign_IsSeeded())
        return NULL;
    // ARM is little endian; SB3 and its variable array are naturally aligned.
    return (u16 *)(image + REGIONAL_SAVE_VARS_OFFSET + 2 * (1 + encodedId - JOHTO_CAMPAIGN_VAR_ID_BASE));
}

void JohtoCampaign_BeforeVarWrite(u16 encodedId)
{
    // Existing script pointer writers call this for both namespaces. Native
    // FireRed variables also live in the frozen main-save image; the script
    // effect analyzer is not a save-transaction mutation guard.
    if (!Script_IsAnalyzingEffects()
     && ((encodedId >= VARS_START && encodedId < VARS_START + VARS_COUNT)
      || JohtoCampaign_GetVarPointer(encodedId) != NULL))
        FireRedSave_NotifyPersistentWrite();
}

bool8 JohtoCampaign_IsTrainerDefeated(u16 rawId)
{
    bool8 value = FALSE;
    if (rawId < JOHTO_CAMPAIGN_RAW_TRAINER_COUNT && JohtoCampaign_IsSeeded())
        RegionalSave_GetTrainer((const u8 *)gSaveBlock3Ptr, REGIONAL_SAVE_JOHTO, rawId, &value);
    return value;
}

void JohtoCampaign_SetTrainerDefeated(u16 rawId)
{
    if (rawId >= JOHTO_CAMPAIGN_RAW_TRAINER_COUNT || !JohtoCampaign_IsSeeded()
     || JohtoCampaign_IsTrainerDefeated(rawId))
        return;
    FireRedSave_NotifyPersistentWrite();
    RegionalSave_SetTrainer((u8 *)gSaveBlock3Ptr, REGIONAL_SAVE_JOHTO, rawId, TRUE);
}

void JohtoCampaign_ClearTrainerDefeated(u16 rawId)
{
    if (rawId >= JOHTO_CAMPAIGN_RAW_TRAINER_COUNT || !JohtoCampaign_IsSeeded()
     || !JohtoCampaign_IsTrainerDefeated(rawId))
        return;
    FireRedSave_NotifyPersistentWrite();
    RegionalSave_SetTrainer((u8 *)gSaveBlock3Ptr, REGIONAL_SAVE_JOHTO, rawId, FALSE);
}

u8 JohtoCampaign_GetRematchReadiness(u16 compactRow)
{
    u32 bit;
    u8 readiness = 0;
    const u8 *image = (const u8 *)gSaveBlock3Ptr;
    if (compactRow >= REGIONAL_SAVE_REMATCH_COUNT || !JohtoCampaign_IsSeeded())
        return 0;
    for (bit = 0; bit < 3; bit++)
    {
        u32 index = REGIONAL_SAVE_REMATCH_BIT_OFFSET + compactRow * 3 + bit;
        readiness |= ((image[REGIONAL_SAVE_TRAINERS_OFFSET + (index >> 3)] >> (index & 7)) & 1) << bit;
    }
    return readiness;
}

bool8 JohtoCampaign_SetRematchReadiness(u16 compactRow, u8 readiness)
{
    u32 bit;
    u8 *image = (u8 *)gSaveBlock3Ptr;
    if (compactRow >= REGIONAL_SAVE_REMATCH_COUNT || readiness > 5 || !JohtoCampaign_IsSeeded())
        return FALSE;
    if (JohtoCampaign_GetRematchReadiness(compactRow) == readiness)
        return TRUE;
    FireRedSave_NotifyPersistentWrite();
    for (bit = 0; bit < 3; bit++)
        RegionalSave_SetTrainer(image, REGIONAL_SAVE_JOHTO, REGIONAL_SAVE_REMATCH_BIT_OFFSET + compactRow * 3 + bit, (readiness >> bit) & 1);
    return TRUE;
}

u8 JohtoCampaign_GetRematchStepCounter(void)
{
    if (!JohtoCampaign_IsSeeded())
        return 0;
    return ((const u8 *)gSaveBlock3Ptr)[REGIONAL_SAVE_TRAINERS_OFFSET + REGIONAL_SAVE_REMATCH_STEP_BIT_OFFSET / 8];
}

bool8 JohtoCampaign_SetRematchStepCounter(u16 steps)
{
    u8 *image = (u8 *)gSaveBlock3Ptr;
    if (!JohtoCampaign_IsSeeded())
        return FALSE;
    if (steps > 255)
        steps = 255;
    if (JohtoCampaign_GetRematchStepCounter() == steps)
        return TRUE;
    FireRedSave_NotifyPersistentWrite();
    image[REGIONAL_SAVE_TRAINERS_OFFSET + REGIONAL_SAVE_REMATCH_STEP_BIT_OFFSET / 8] = steps;
    return TRUE;
}

bool8 JohtoCampaign_Initialize(void)
{
    u8 *image = (u8 *)gSaveBlock3Ptr;
    u32 i;
    u16 index;
    bool8 trainer;

    if (!RegionalSave_FoundationValid(image))
        return FALSE;
    if (JohtoCampaign_IsSeeded())
        return TRUE;
    FireRedSave_NotifyPersistentWrite();
    if (!RegionalSave_UpgradeToCampaign(image))
        return FALSE;
    RegionalSave_Write32(image + REGIONAL_SAVE_JOHTO_FLAGS_OFFSET, REGIONAL_SAVE_JOHTO_INITIALIZED);
    RegionalSave_Write32(image + REGIONAL_SAVE_JOHTO_EVENT_REVISION_OFFSET, REGIONAL_SAVE_CAMPAIGN_MAPPING_REVISION);
    RegionalSave_Write32(image + REGIONAL_SAVE_JOHTO_TRAINER_REVISION_OFFSET, REGIONAL_SAVE_CAMPAIGN_MAPPING_REVISION);
    RegionalSave_Write32(image + REGIONAL_SAVE_JOHTO_VAR_REVISION_OFFSET, REGIONAL_SAVE_CAMPAIGN_MAPPING_REVISION);
    for (i = 0; i < ARRAY_COUNT(sInitialFlags); i++)
    {
        if (FlagIndex(sInitialFlags[i], &index, &trainer) && !trainer)
            RegionalSave_SetEvent(image, REGIONAL_SAVE_JOHTO, index, TRUE);
    }
    for (i = 0; i < ARRAY_COUNT(sInitialVariables); i++)
    {
        if (sInitialVariables[i] >= JOHTO_CAMPAIGN_RAW_VAR_FIRST && sInitialVariables[i] <= JOHTO_CAMPAIGN_RAW_VAR_LAST)
            RegionalSave_SetVar(image, REGIONAL_SAVE_JOHTO, 1 + sInitialVariables[i] - JOHTO_CAMPAIGN_RAW_VAR_FIRST, 0);
    }
    // Arrive as Oak's established trainer at the original Elm-first gate.
    // Raw HnS VAR_NEWBARKTOWN_LABSTATE=0x4074, TOWN_STATE=0x4075.
    RegionalSave_SetVar(image, REGIONAL_SAVE_JOHTO, 1 + 0x4074 - JOHTO_CAMPAIGN_RAW_VAR_FIRST, 0);
    RegionalSave_SetVar(image, REGIONAL_SAVE_JOHTO, 1 + 0x4075 - JOHTO_CAMPAIGN_RAW_VAR_FIRST, 2);
    // Actual HnS FLAG_VISITED_NEWBARK_TOWN=0x8F0. Seeding occurs after the
    // confirmed forward trip; the skipped resident intro cannot set it now.
    if (FlagIndex(0x8F0, &index, &trainer) && !trainer)
        RegionalSave_SetEvent(image, REGIONAL_SAVE_JOHTO, index, TRUE);
    // The owner-selected Johto research branch is Chikorita. It describes the
    // regional story without granting a creature or changing Kanto's starter.
    image[REGIONAL_SAVE_JOHTO_STARTER_STATE_OFFSET] = 1;
    RegionalSave_Write16(image + REGIONAL_SAVE_JOHTO_STARTER_SPECIES_OFFSET, SPECIES_CHIKORITA);
    RegionalSave_SetVar(image, REGIONAL_SAVE_JOHTO, 1 + 0x4023 - JOHTO_CAMPAIGN_RAW_VAR_FIRST, 0);
    // Match original InitMomSavings once, solely in the allocated Johto slot.
    image[REGIONAL_SAVE_MOM_SAVINGS_OFFSET + 7] = TRUE;
    // The upstream HnS default is SILVER. This independent fixed slot does not
    // touch the native FireRed BLUE name or any existing creature nickname.
    memset(image + REGIONAL_SAVE_JOHTO_RIVAL_OFFSET, EOS, 8);
    StringCopy(image + REGIONAL_SAVE_JOHTO_RIVAL_OFFSET, gText_ExpandedPlaceholder_Silver);
    // Commit the once-only marker last, after the regional seed is complete.
    RegionalSave_Write16(image + REGIONAL_SAVE_FLAGS_OFFSET, REGIONAL_SAVE_HEADER_CAMPAIGN_SEEDED);
    return RegionalSave_FoundationValid(image);
}

void Special_JohtoCampaignGetState(void)
{
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = JohtoCampaign_IsSeeded();
}

void Special_JohtoCampaignInitialize(void)
{
    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    gSpecialVar_Result = JohtoCampaign_Initialize();
}

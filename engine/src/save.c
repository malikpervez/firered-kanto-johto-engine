#include "global.h"
#include "agb_flash.h"
#include "gba/flash_internal.h"
#include "fieldmap.h"
#include "save.h"
#include "task.h"
#include "decompress.h"
#include "load_save.h"
#include "overworld.h"
#include "hall_of_fame.h"
#include "pokemon_storage_system.h"
#include "trainer_hill.h"
#include "link.h"
#include "constants/game_stat.h"
#include "constants/rematches.h"
#include "event_data.h"
#ifdef FIRERED
#include "regional_save.h"
#include "new_game.h"
#endif

static u16 CalculateChecksum(void *, u16);
static bool8 ReadFlashSector(u8, struct SaveSector *);
#ifndef FIRERED
static u8 GetSaveValidStatus(const struct SaveSectorLocation *);
static u8 CopySaveSlotData(u16, struct SaveSectorLocation *);
static u8 HandleWriteSector(u16, const struct SaveSectorLocation *);
static u8 HandleReplaceSector(u16, const struct SaveSectorLocation *);
static void CopyToSaveBlock3(u32, struct SaveSector *);
static void CopyFromSaveBlock3(u32, struct SaveSector *);
#endif
static u8 TryWriteSector(u8, u8 *);
#ifdef FIRERED
static bool32 SetDamagedSectorBits(u8, u8);
static u8 HandleWriteSectorNBytes(u8, u8 *, u16);
#endif

// Divide save blocks into individual chunks to be written to flash sectors

/*
 * Sector Layout:
 *
 * Sectors 0 - 13:      Save Slot 1
 * Sectors 14 - 27:     Save Slot 2
 * Sectors 28 - 29:     Hall of Fame
 * Sector 30:           Trainer Hill
 * Sector 31:           Recorded Battle
 *
 * There are two save slots for saving the player's game data. We alternate between
 * them each time the game is saved, so that if the current save slot is corrupt,
 * we can load the previous one. We also rotate the sectors in each save slot
 * so that the same data is not always being written to the same sector. This
 * might be done to reduce wear on the flash memory, but I'm not sure, since all
 * 14 sectors get written anyway.
 *
 * See SECTOR_ID_* constants in save.h
 */

#define SAVEBLOCK_CHUNK(structure, chunkNum)                                   \
{                                                                              \
    chunkNum * SECTOR_DATA_SIZE,                                               \
    sizeof(structure) >= chunkNum * SECTOR_DATA_SIZE ?                         \
    min(sizeof(structure) - chunkNum * SECTOR_DATA_SIZE, SECTOR_DATA_SIZE) : 0 \
}

struct
{
    u16 offset;
    u16 size;
} static const sSaveSlotLayout[NUM_SECTORS_PER_SLOT] =
{
    SAVEBLOCK_CHUNK(struct SaveBlock2, 0), // SECTOR_ID_SAVEBLOCK2

    SAVEBLOCK_CHUNK(struct SaveBlock1, 0), // SECTOR_ID_SAVEBLOCK1_START
    SAVEBLOCK_CHUNK(struct SaveBlock1, 1),
    SAVEBLOCK_CHUNK(struct SaveBlock1, 2),
    SAVEBLOCK_CHUNK(struct SaveBlock1, 3), // SECTOR_ID_SAVEBLOCK1_END

    SAVEBLOCK_CHUNK(struct PokemonStorage, 0), // SECTOR_ID_PKMN_STORAGE_START
    SAVEBLOCK_CHUNK(struct PokemonStorage, 1),
    SAVEBLOCK_CHUNK(struct PokemonStorage, 2),
    SAVEBLOCK_CHUNK(struct PokemonStorage, 3),
    SAVEBLOCK_CHUNK(struct PokemonStorage, 4),
    SAVEBLOCK_CHUNK(struct PokemonStorage, 5),
    SAVEBLOCK_CHUNK(struct PokemonStorage, 6),
    SAVEBLOCK_CHUNK(struct PokemonStorage, 7),
    SAVEBLOCK_CHUNK(struct PokemonStorage, 8), // SECTOR_ID_PKMN_STORAGE_END
};

// These will produce an error if a save struct is larger than the space
// alloted for it in the flash.
STATIC_ASSERT(sizeof(struct SaveBlock3) <= SAVE_BLOCK_3_CHUNK_SIZE * NUM_SECTORS_PER_SLOT, SaveBlock3FreeSpace);

// ChallengeSettings is a packed bitfield block living in SaveBlock3 ahead of
// registeredItemHold, so growing it shifts that member and silently corrupts
// existing saves. The size is pinned here to turn that into a build error.
// Note the ABI: CFLAGS uses -mabi=apcs-gnu, which rounds every struct up to a
// multiple of 4 bytes, so the 31 bytes of fields occupy 32 and the last byte is
// trailing padding. Headroom before the size actually moves (to 36, not 33):
// 12 spare bits scattered through the field bytes, wherever a wide bitfield had
// to skip the tail of a partly-filled byte, plus the 8 bits of trailing padding.
// If this fires, that headroom is gone and the new setting needs a save
// migration rather than another field.
STATIC_ASSERT(sizeof(struct ChallengeSettings) == 32, ChallengeSettingsLayoutPinned);
STATIC_ASSERT(sizeof(struct SaveBlock2) <= SECTOR_DATA_SIZE, SaveBlock2FreeSpace);
STATIC_ASSERT(sizeof(struct SaveBlock1) <= SECTOR_DATA_SIZE * (SECTOR_ID_SAVEBLOCK1_END - SECTOR_ID_SAVEBLOCK1_START + 1), SaveBlock1FreeSpace);
STATIC_ASSERT(sizeof(struct PokemonStorage) <= SECTOR_DATA_SIZE * (SECTOR_ID_PKMN_STORAGE_END - SECTOR_ID_PKMN_STORAGE_START + 1), PokemonStorageFreeSpace);

COMMON_DATA u16 gLastWrittenSector = 0;
COMMON_DATA u32 gLastSaveCounter = 0;
COMMON_DATA u16 gLastKnownGoodSector = 0;
COMMON_DATA u32 gDamagedSaveSectors = 0;
COMMON_DATA u32 gSaveCounter = 0;
COMMON_DATA struct SaveSector *gReadWriteSector = NULL; // Pointer to a buffer for reading/writing a sector
COMMON_DATA u16 gIncrementalSectorId = 0;
COMMON_DATA u16 gSaveUnusedVar = 0;
COMMON_DATA u16 gSaveFileStatus = 0;
COMMON_DATA MainCallback gGameContinueCallback = NULL;
COMMON_DATA struct SaveSectorLocation gRamSaveSectorLocations[NUM_SECTORS_PER_SLOT] = {0};
COMMON_DATA u16 gSaveUnusedVar2 = 0;
COMMON_DATA u16 gSaveAttemptStatus = 0;

EWRAM_DATA struct SaveSector gSaveDataBuffer = {0}; // Buffer used for reading/writing sectors

#ifdef FIRERED
enum FireRedSavePhase
{
    FR_SAVE_IDLE,
    FR_SAVE_PREPARING,
    FR_SAVE_FROZEN,
    FR_SAVE_BODY,
    FR_SAVE_HEADER,
    FR_SAVE_PREPARED,
    FR_SAVE_COMMITTING,
    FR_SAVE_LOADING,
    FR_SAVE_VALIDATING,
    FR_SAVE_SPECIAL,
};

struct FireRedSaveBank
{
    u32 generation;
    u16 mask;
    u8 rotation;
    u8 status;
    u8 physical[NUM_SECTORS_PER_SLOT];
};

struct FireRedSaveScratch
{
    u8 saveBlock2[3892];
    u8 saveBlock3[REGIONAL_SAVE_SIZE];
    struct RegionalSaveSha256Context hash;
    struct RegionalSaveSha256Schedule schedule;
    struct FireRedSaveBank banks[NUM_SAVE_SLOTS];
    u32 oldCounter;
    u32 nextCounter;
    u16 oldRotation;
    u16 nextRotation;
    u8 selectedBank;
    u8 sourceBank;
    u8 targetBank;
    volatile u8 phase;
    u8 nextId;
    u8 partial;
    u8 result;
    bool8 loaded;
    bool8 probed;
    bool8 timerHeld;
    bool8 hallOfFamePrepared;
    u32 hallOfFameStatBefore;
    u32 *trainerHillCounter;
};

STATIC_ASSERT(sizeof(struct SaveBlock2) == 3892, FireRedSave2SizePinned);
STATIC_ASSERT(sizeof(struct SaveBlock1) == 15868, FireRedSave1SizePinned);
STATIC_ASSERT(sizeof(struct PokemonStorage) == 34144, FireRedStorageSizePinned);
STATIC_ASSERT(sizeof(struct FireRedSaveScratch) <= 5504, FireRedSaveScratchBudget);
STATIC_ASSERT(GAME_VERSION == VERSION_FIRE_RED, FireRedSaveTargetPinned);

static EWRAM_DATA struct FireRedSaveScratch sFireRedSave = {0};

static void UpdateSaveAddresses(void);

static u16 FireRedEnterCritical(void)
{
    u16 ime = REG_IME;
    REG_IME = 0;
    asm volatile("" ::: "memory");
    return ime;
}

static void FireRedLeaveCritical(u16 ime)
{
    asm volatile("" ::: "memory");
    REG_IME = ime;
}

static void FireRedHoldTimer(void)
{
    sFireRedSave.trainerHillCounter = gTrainerHillVBlankCounter;
    sFireRedSave.timerHeld = TRUE;
    gTrainerHillVBlankCounter = NULL;
}

static void FireRedRestoreTimer(void)
{
    if (sFireRedSave.timerHeld)
    {
        gTrainerHillVBlankCounter = sFireRedSave.trainerHillCounter;
        sFireRedSave.timerHeld = FALSE;
    }
}

// Do not let an interrupt cancellation be overwritten by a later publication.
static bool8 FireRedAdvancePhase(u8 expected, u8 next, u8 result)
{
    u16 ime = FireRedEnterCritical();
    bool8 advanced = FALSE;
    if (sFireRedSave.phase == expected)
    {
        sFireRedSave.phase = next;
        sFireRedSave.result = result;
        advanced = TRUE;
    }
    FireRedLeaveCritical(ime);
    return advanced;
}

static bool8 FireRedBeginSpecial(void)
{
    u16 ime = FireRedEnterCritical();
    bool8 started = FALSE;
    if ((sFireRedSave.phase == FR_SAVE_IDLE || sFireRedSave.phase == FR_SAVE_SPECIAL)
     && sFireRedSave.result == SAVE_STATUS_OK)
    {
        sFireRedSave.phase = FR_SAVE_SPECIAL;
        started = TRUE;
    }
    FireRedLeaveCritical(ime);
    return started;
}

bool8 FireRedSave_IsBusy(void)
{
    return sFireRedSave.phase != FR_SAVE_IDLE;
}

bool8 FireRedSave_IsLoaded(void)
{
    return sFireRedSave.loaded;
}

u8 FireRedSave_LastResult(void)
{
    return sFireRedSave.result;
}

void FireRedSave_Abort(void)
{
    u16 ime = FireRedEnterCritical();
    // A failed main transaction must not replay this once-only preparation.
    if (sFireRedSave.hallOfFamePrepared)
    {
        gSaveBlock1Ptr->gameStats[GAME_STAT_ENTERED_HOF] = sFireRedSave.hallOfFameStatBefore;
        sFireRedSave.hallOfFamePrepared = FALSE;
    }
    if (FireRedSave_IsBusy())
    {
        if (sFireRedSave.phase != FR_SAVE_LOADING && sFireRedSave.phase != FR_SAVE_SPECIAL)
        {
            gSaveCounter = sFireRedSave.oldCounter;
            gLastWrittenSector = sFireRedSave.oldRotation;
        }
        sFireRedSave.phase = FR_SAVE_IDLE;
    }
    FireRedRestoreTimer();
    sFireRedSave.result = SAVE_STATUS_ERROR;
    gSaveAttemptStatus = SAVE_STATUS_ERROR;
    FireRedLeaveCritical(ime);
}

void FireRedSave_NotifyPersistentWrite(void)
{
    if (FireRedSave_IsBusy() && sFireRedSave.phase != FR_SAVE_PREPARING)
        FireRedSave_Abort();
}

void FireRedSave_ResetSession(void)
{
    if (FireRedSave_IsBusy())
    {
        FireRedSave_Abort();
        return;
    }
    sFireRedSave.loaded = FALSE;
    sFireRedSave.probed = FALSE;
    sFireRedSave.selectedBank = NUM_SAVE_SLOTS;
    sFireRedSave.result = SAVE_STATUS_EMPTY;
}

static u32 FireRedChunkSize(u16 id)
{
    u32 offset = id * SAVE_BLOCK_3_CHUNK_SIZE;
    if (offset >= REGIONAL_SAVE_SIZE)
        return 0;
    return min(SAVE_BLOCK_3_CHUNK_SIZE, REGIONAL_SAVE_SIZE - offset);
}

static bool8 FireRedReadChecked(u8 bank, u16 id, const struct FireRedSaveBank *descriptor)
{
    u16 size;
    if (!FireRedSave_IsBusy() || bank >= NUM_SAVE_SLOTS || id >= NUM_SECTORS_PER_SLOT)
        return FALSE;
    size = RegionalSave_MainSectorSize(id);
    ReadFlashSector(bank * NUM_SECTORS_PER_SLOT + descriptor->physical[id], &gSaveDataBuffer);
    return FireRedSave_IsBusy()
        && gSaveDataBuffer.id == id
        && gSaveDataBuffer.signature == SECTOR_SIGNATURE
        && gSaveDataBuffer.counter == descriptor->generation
        && gSaveDataBuffer.checksum == CalculateChecksum(gSaveDataBuffer.data, size);
}

static u8 FireRedValidateBank(u8 bank)
{
    struct FireRedSaveBank *descriptor = &sFireRedSave.banks[bank];
    u16 physical, id, size, nativeVersion = 0;
    u32 nativeMagic = 0;
    bool8 occupied = FALSE;
    u8 headerStatus;

    if (!FireRedSave_IsBusy())
        return descriptor->status = SAVE_STATUS_CORRUPT;

    memset(descriptor, 0, sizeof(*descriptor));
    memset(sFireRedSave.saveBlock3, 0, sizeof(sFireRedSave.saveBlock3));
    descriptor->status = SAVE_STATUS_EMPTY;
    for (physical = 0; physical < NUM_SECTORS_PER_SLOT; physical++)
    {
        u16 byte;
        u8 rotation;
        if (!FireRedSave_IsBusy())
            return descriptor->status = SAVE_STATUS_CORRUPT;
        ReadFlashSector(bank * NUM_SECTORS_PER_SLOT + physical, &gSaveDataBuffer);
        if (!FireRedSave_IsBusy())
            return descriptor->status = SAVE_STATUS_CORRUPT;
        for (byte = 0; byte < SECTOR_SIZE; byte++)
        {
            if (((u8 *)&gSaveDataBuffer)[byte] != 0xFF)
            {
                occupied = TRUE;
                break;
            }
        }
        if (gSaveDataBuffer.signature != SECTOR_SIGNATURE)
            continue;
        id = gSaveDataBuffer.id;
        if (id >= NUM_SECTORS_PER_SLOT || (descriptor->mask & (1 << id)))
            return descriptor->status = SAVE_STATUS_CORRUPT;
        size = RegionalSave_MainSectorSize(id);
        if (gSaveDataBuffer.checksum != CalculateChecksum(gSaveDataBuffer.data, size))
            return descriptor->status = SAVE_STATUS_CORRUPT;
        rotation = (physical + NUM_SECTORS_PER_SLOT - id) % NUM_SECTORS_PER_SLOT;
        if (descriptor->mask == 0)
        {
            descriptor->generation = gSaveDataBuffer.counter;
            descriptor->rotation = rotation;
        }
        else if (descriptor->generation != gSaveDataBuffer.counter || descriptor->rotation != rotation)
        {
            return descriptor->status = SAVE_STATUS_CORRUPT;
        }
        descriptor->mask |= 1 << id;
        descriptor->physical[id] = physical;
        if (FireRedChunkSize(id))
            memcpy(sFireRedSave.saveBlock3 + id * SAVE_BLOCK_3_CHUNK_SIZE,
                   gSaveDataBuffer.saveBlock3Chunk, FireRedChunkSize(id));
        if (id == SECTOR_ID_SAVEBLOCK2)
            memcpy(sFireRedSave.saveBlock2, gSaveDataBuffer.data, sizeof(sFireRedSave.saveBlock2));
        if (id == SECTOR_ID_SAVEBLOCK1_START)
            nativeVersion = RegionalSave_Read16(gSaveDataBuffer.data + offsetof(struct SaveBlock1, saveVersion));
        if (id == SECTOR_ID_SAVEBLOCK1_START + offsetof(struct SaveBlock1, saveVersionMagic) / SECTOR_DATA_SIZE)
            nativeMagic = RegionalSave_Read32(gSaveDataBuffer.data + offsetof(struct SaveBlock1, saveVersionMagic) % SECTOR_DATA_SIZE);
    }
    if (!occupied)
        return descriptor->status = SAVE_STATUS_EMPTY;
    if (descriptor->mask != (1 << NUM_SECTORS_PER_SLOT) - 1
     || descriptor->generation % NUM_SAVE_SLOTS != bank)
        return descriptor->status = SAVE_STATUS_CORRUPT;
    if (nativeVersion != SAVE_VERSION)
        return descriptor->status = SAVE_STATUS_UNSUPPORTED;
    if (nativeMagic != SAVE_VERSION_MAGIC)
        return descriptor->status = SAVE_STATUS_CORRUPT;
    headerStatus = RegionalSave_CheckHeader(sFireRedSave.saveBlock3, descriptor->generation);
    if (headerStatus == REGIONAL_SAVE_HEADER_UNSUPPORTED)
        return descriptor->status = SAVE_STATUS_UNSUPPORTED;
    if (headerStatus != REGIONAL_SAVE_HEADER_VALID
     || !RegionalSave_CheckCrc(sFireRedSave.saveBlock3)
     || !RegionalSave_FoundationValid(sFireRedSave.saveBlock3))
        return descriptor->status = SAVE_STATUS_CORRUPT;
    RegionalSave_HashMainInit(&sFireRedSave.hash, &sFireRedSave.schedule, sFireRedSave.saveBlock3);
    for (id = 1; id <= NUM_SECTORS_PER_SLOT; id++)
    {
        u16 logical = id % NUM_SECTORS_PER_SLOT;
        if (!FireRedReadChecked(bank, logical, descriptor)
         || !RegionalSave_HashMainSector(&sFireRedSave.hash, &sFireRedSave.schedule,
                                        logical, gSaveDataBuffer.data, RegionalSave_MainSectorSize(logical)))
            return descriptor->status = SAVE_STATUS_CORRUPT;
    }
    RegionalSave_Sha256Final(&sFireRedSave.hash, &sFireRedSave.schedule, gSaveDataBuffer.data);
    if (memcmp(gSaveDataBuffer.data, sFireRedSave.saveBlock3 + REGIONAL_SAVE_DIGEST_OFFSET, 32))
        return descriptor->status = SAVE_STATUS_CORRUPT;
    if (!FireRedSave_IsBusy())
        return descriptor->status = SAVE_STATUS_CORRUPT;
    return descriptor->status = SAVE_STATUS_OK;
}

static u8 FireRedSelectBank(void)
{
    u8 first = FireRedValidateBank(0);
    u8 second;
    sFireRedSave.selectedBank = NUM_SAVE_SLOTS;
    if (!FireRedSave_IsBusy())
        return SAVE_STATUS_CORRUPT;
    second = FireRedValidateBank(1);
    if (!FireRedSave_IsBusy())
        return SAVE_STATUS_CORRUPT;
    if (first == SAVE_STATUS_OK && second == SAVE_STATUS_OK)
    {
        if (sFireRedSave.banks[0].generation + 1 == sFireRedSave.banks[1].generation)
            sFireRedSave.selectedBank = 1;
        else if (sFireRedSave.banks[1].generation + 1 == sFireRedSave.banks[0].generation)
            sFireRedSave.selectedBank = 0;
        else
            return SAVE_STATUS_CORRUPT;
        return SAVE_STATUS_OK;
    }
    if (first == SAVE_STATUS_OK || second == SAVE_STATUS_OK)
    {
        u8 valid = first == SAVE_STATUS_OK ? 0 : 1;
        u8 other = valid ^ 1;
        u8 otherStatus = sFireRedSave.banks[other].status;
        if (otherStatus == SAVE_STATUS_UNSUPPORTED
         && sFireRedSave.banks[other].generation + 1 != sFireRedSave.banks[valid].generation)
            return SAVE_STATUS_UNSUPPORTED;
        sFireRedSave.selectedBank = valid;
        return otherStatus == SAVE_STATUS_EMPTY ? SAVE_STATUS_OK : SAVE_STATUS_RECOVERED;
    }
    if (first == SAVE_STATUS_EMPTY && second == SAVE_STATUS_EMPTY)
        return SAVE_STATUS_EMPTY;
    if (first == SAVE_STATUS_UNSUPPORTED || second == SAVE_STATUS_UNSUPPORTED)
        return SAVE_STATUS_UNSUPPORTED;
    return SAVE_STATUS_CORRUPT;
}

u8 FireRedSave_Probe(void)
{
    u8 result;
    if (FireRedSave_IsBusy())
    {
        FireRedSave_Abort();
        return SAVE_STATUS_ERROR;
    }
    sFireRedSave.loaded = FALSE;
    sFireRedSave.probed = TRUE;
    if (gFlashMemoryPresent != TRUE)
        return sFireRedSave.result = SAVE_STATUS_NO_FLASH;
    sFireRedSave.oldCounter = gSaveCounter;
    sFireRedSave.oldRotation = gLastWrittenSector;
    sFireRedSave.phase = FR_SAVE_VALIDATING;
    result = FireRedSelectBank();
    if (sFireRedSave.selectedBank < NUM_SAVE_SLOTS
     && FireRedValidateBank(sFireRedSave.selectedBank) != SAVE_STATUS_OK)
        result = SAVE_STATUS_CORRUPT;
    if (!FireRedAdvancePhase(FR_SAVE_VALIDATING, FR_SAVE_IDLE, result))
        sFireRedSave.result = SAVE_STATUS_CORRUPT;
    return sFireRedSave.result;
}

static u8 FireRedLoadGame(void)
{
    u8 result;
    u16 id, ime;
    u32 generation;
    u8 rotation, selected;
    if (FireRedSave_IsBusy())
    {
        FireRedSave_Abort();
        return SAVE_STATUS_ERROR;
    }
    if (!sFireRedSave.probed)
        FireRedSave_Probe();
    result = sFireRedSave.result;
    if (result != SAVE_STATUS_OK && result != SAVE_STATUS_RECOVERED)
        return result;
    selected = sFireRedSave.selectedBank;
    generation = sFireRedSave.banks[selected].generation;
    rotation = sFireRedSave.banks[selected].rotation;
    sFireRedSave.phase = FR_SAVE_LOADING;
    FireRedHoldTimer();
    if (FireRedValidateBank(selected) != SAVE_STATUS_OK
     || sFireRedSave.banks[selected].generation != generation
     || sFireRedSave.banks[selected].rotation != rotation)
    {
        sFireRedSave.phase = FR_SAVE_IDLE;
        FireRedRestoreTimer();
        sFireRedSave.loaded = FALSE;
        return sFireRedSave.result = SAVE_STATUS_CORRUPT;
    }
    // Flash-buffer ownership is exclusive from validation through copying.
    ime = FireRedEnterCritical();
    if (sFireRedSave.phase != FR_SAVE_LOADING)
    {
        FireRedLeaveCritical(ime);
        sFireRedSave.loaded = FALSE;
        return sFireRedSave.result = SAVE_STATUS_CORRUPT;
    }
    memcpy(gSaveBlock2Ptr, sFireRedSave.saveBlock2, sizeof(sFireRedSave.saveBlock2));
    FireRedLeaveCritical(ime);
    for (id = 1; id < NUM_SECTORS_PER_SLOT; id++)
    {
        if (!FireRedSave_IsBusy() || !FireRedReadChecked(selected, id, &sFireRedSave.banks[selected]))
        {
            sFireRedSave.phase = FR_SAVE_IDLE;
            FireRedRestoreTimer();
            sFireRedSave.loaded = FALSE;
            return sFireRedSave.result = SAVE_STATUS_CORRUPT;
        }
        ime = FireRedEnterCritical();
        if (sFireRedSave.phase != FR_SAVE_LOADING)
        {
            FireRedLeaveCritical(ime);
            sFireRedSave.loaded = FALSE;
            return sFireRedSave.result = SAVE_STATUS_CORRUPT;
        }
        memcpy(gRamSaveSectorLocations[id].data, gSaveDataBuffer.data, RegionalSave_MainSectorSize(id));
        FireRedLeaveCritical(ime);
    }
    ime = FireRedEnterCritical();
    if (sFireRedSave.phase != FR_SAVE_LOADING)
    {
        FireRedLeaveCritical(ime);
        sFireRedSave.loaded = FALSE;
        return sFireRedSave.result = SAVE_STATUS_CORRUPT;
    }
    memcpy(&gSaveblock3, sFireRedSave.saveBlock3, REGIONAL_SAVE_SIZE);
    gSaveCounter = generation;
    gLastWrittenSector = rotation;
    sFireRedSave.phase = FR_SAVE_IDLE;
    FireRedRestoreTimer();
    sFireRedSave.loaded = TRUE;
    sFireRedSave.probed = FALSE;
    sFireRedSave.result = result;
    FireRedLeaveCritical(ime);
    return result;
}

static const u8 *FireRedSourcePayload(u16 id)
{
    if (id == SECTOR_ID_SAVEBLOCK2)
        return sFireRedSave.saveBlock2;
    if (sFireRedSave.partial && id >= SECTOR_ID_PKMN_STORAGE_START)
    {
        if (!FireRedReadChecked(sFireRedSave.sourceBank, id, &sFireRedSave.banks[sFireRedSave.sourceBank]))
            return NULL;
        return gSaveDataBuffer.data;
    }
    return gRamSaveSectorLocations[id].data;
}

static bool8 FireRedBeginSave(bool8 partial, bool8 hallOfFame)
{
    u8 status;
    u16 id, ime;
    if (FireRedSave_IsBusy())
    {
        FireRedSave_Abort();
        return FALSE;
    }
    gSaveAttemptStatus = SAVE_STATUS_ERROR;
    sFireRedSave.result = SAVE_STATUS_ERROR;
    if (gFlashMemoryPresent != TRUE)
        return FALSE;
    sFireRedSave.oldCounter = gSaveCounter;
    sFireRedSave.oldRotation = gLastWrittenSector;
    sFireRedSave.phase = FR_SAVE_VALIDATING;
    FireRedHoldTimer();
    status = FireRedSelectBank();
    if (!FireRedSave_IsBusy()
     || (status != SAVE_STATUS_OK && status != SAVE_STATUS_RECOVERED && status != SAVE_STATUS_EMPTY))
    {
        FireRedSave_Abort();
        return FALSE;
    }
    if (partial && (sFireRedSave.selectedBank >= NUM_SAVE_SLOTS || gDifferentSaveFile))
    {
        FireRedSave_Abort();
        return FALSE;
    }
    ime = FireRedEnterCritical();
    if (sFireRedSave.phase != FR_SAVE_VALIDATING)
    {
        FireRedLeaveCritical(ime);
        return FALSE;
    }
    sFireRedSave.sourceBank = sFireRedSave.selectedBank;
    sFireRedSave.oldCounter = status == SAVE_STATUS_EMPTY ? 0 : sFireRedSave.banks[sFireRedSave.sourceBank].generation;
    sFireRedSave.oldRotation = status == SAVE_STATUS_EMPTY ? 0 : sFireRedSave.banks[sFireRedSave.sourceBank].rotation;
    sFireRedSave.nextCounter = sFireRedSave.oldCounter + 1;
    sFireRedSave.nextRotation = (sFireRedSave.oldRotation + 1) % NUM_SECTORS_PER_SLOT;
    sFireRedSave.targetBank = sFireRedSave.nextCounter % NUM_SAVE_SLOTS;
    sFireRedSave.partial = partial;
    sFireRedSave.nextId = 1;
    sFireRedSave.phase = FR_SAVE_PREPARING;
    FireRedLeaveCritical(ime);
    gDamagedSaveSectors = 0;
    UpdateSaveAddresses();
    if (hallOfFame && GetGameStat(GAME_STAT_ENTERED_HOF) < 999)
    {
        sFireRedSave.hallOfFameStatBefore = gSaveBlock1Ptr->gameStats[GAME_STAT_ENTERED_HOF];
        sFireRedSave.hallOfFamePrepared = TRUE;
        IncrementGameStat(GAME_STAT_ENTERED_HOF);
    }
    CopyPartyAndObjectsToSave();
    if (sFireRedSave.phase != FR_SAVE_PREPARING)
        return FALSE;
    ime = FireRedEnterCritical();
    if (sFireRedSave.phase != FR_SAVE_PREPARING)
    {
        FireRedLeaveCritical(ime);
        return FALSE;
    }
    memcpy(sFireRedSave.saveBlock2, gSaveBlock2Ptr, sizeof(sFireRedSave.saveBlock2));
    memcpy(sFireRedSave.saveBlock3, &gSaveblock3, REGIONAL_SAVE_SIZE);
    sFireRedSave.phase = FR_SAVE_FROZEN;
    FireRedLeaveCritical(ime);
    RegionalSave_SetGeneration(sFireRedSave.saveBlock3, sFireRedSave.nextCounter);
    if (gSaveBlock1Ptr->saveVersion != SAVE_VERSION
     || gSaveBlock1Ptr->saveVersionMagic != SAVE_VERSION_MAGIC
     || RegionalSave_CheckHeader(sFireRedSave.saveBlock3, sFireRedSave.nextCounter) != REGIONAL_SAVE_HEADER_VALID
     || !RegionalSave_FoundationValid(sFireRedSave.saveBlock3))
    {
        FireRedSave_Abort();
        return FALSE;
    }
    RegionalSave_HashMainInit(&sFireRedSave.hash, &sFireRedSave.schedule, sFireRedSave.saveBlock3);
    for (id = 1; id <= NUM_SECTORS_PER_SLOT; id++)
    {
        u16 logical = id % NUM_SECTORS_PER_SLOT;
        const u8 *payload = FireRedSourcePayload(logical);
        if (!FireRedSave_IsBusy() || payload == NULL
         || !RegionalSave_HashMainSector(&sFireRedSave.hash, &sFireRedSave.schedule,
                                        logical, payload, RegionalSave_MainSectorSize(logical)))
        {
            FireRedSave_Abort();
            return FALSE;
        }
    }
    RegionalSave_Sha256Final(&sFireRedSave.hash, &sFireRedSave.schedule, gSaveDataBuffer.data);
    RegionalSave_Finalize(sFireRedSave.saveBlock3, gSaveDataBuffer.data);
    return FireRedAdvancePhase(FR_SAVE_FROZEN, FR_SAVE_BODY, SAVE_STATUS_OK);
}

static u16 FireRedTargetSector(u16 id)
{
    return sFireRedSave.targetBank * NUM_SECTORS_PER_SLOT
         + (id + sFireRedSave.nextRotation) % NUM_SECTORS_PER_SLOT;
}

static bool8 FireRedBuildSector(u16 id)
{
    const u8 *payload = FireRedSourcePayload(id);
    u16 size = RegionalSave_MainSectorSize(id);
    if (payload == NULL || !FireRedSave_IsBusy())
        return FALSE;
    // A partial PC read already occupies the shared buffer. Retain its payload.
    if (payload == gSaveDataBuffer.data)
        memset(gSaveDataBuffer.data + size, 0, SECTOR_SIZE - size);
    else
    {
        memset(&gSaveDataBuffer, 0, sizeof(gSaveDataBuffer));
        memcpy(gSaveDataBuffer.data, payload, size);
    }
    if (FireRedChunkSize(id))
        memcpy(gSaveDataBuffer.saveBlock3Chunk,
               sFireRedSave.saveBlock3 + id * SAVE_BLOCK_3_CHUNK_SIZE, FireRedChunkSize(id));
    gSaveDataBuffer.id = id;
    gSaveDataBuffer.checksum = CalculateChecksum(gSaveDataBuffer.data, size);
    gSaveDataBuffer.signature = SECTOR_SIGNATURE;
    gSaveDataBuffer.counter = sFireRedSave.nextCounter;
    return TRUE;
}

static bool8 FireRedWriteBody(void)
{
    u16 id = sFireRedSave.nextId;
    u16 ime;
    if (sFireRedSave.phase != FR_SAVE_BODY || id >= NUM_SECTORS_PER_SLOT)
        return FALSE;
    if (!FireRedBuildSector(id)
     || TryWriteSector(FireRedTargetSector(id), gSaveDataBuffer.data) != SAVE_STATUS_OK
     || !FireRedSave_IsBusy())
    {
        FireRedSave_Abort();
        return FALSE;
    }
    ime = FireRedEnterCritical();
    if (sFireRedSave.phase != FR_SAVE_BODY)
    {
        FireRedLeaveCritical(ime);
        return FALSE;
    }
    sFireRedSave.nextId++;
    if (sFireRedSave.nextId == NUM_SECTORS_PER_SLOT)
        sFireRedSave.phase = FR_SAVE_HEADER;
    FireRedLeaveCritical(ime);
    return TRUE;
}

static bool8 FireRedVerifyBody(void)
{
    u16 id;
    RegionalSave_HashMainInit(&sFireRedSave.hash, &sFireRedSave.schedule, sFireRedSave.saveBlock3);
    for (id = 1; id < NUM_SECTORS_PER_SLOT; id++)
    {
        ReadFlashSector(FireRedTargetSector(id), &gSaveDataBuffer);
        if (!FireRedSave_IsBusy()
         || gSaveDataBuffer.id != id
         || gSaveDataBuffer.counter != sFireRedSave.nextCounter
         || gSaveDataBuffer.signature != SECTOR_SIGNATURE
         || gSaveDataBuffer.checksum != CalculateChecksum(gSaveDataBuffer.data, RegionalSave_MainSectorSize(id))
         || (FireRedChunkSize(id)
             && memcmp(gSaveDataBuffer.saveBlock3Chunk,
                       sFireRedSave.saveBlock3 + id * SAVE_BLOCK_3_CHUNK_SIZE, FireRedChunkSize(id)))
         || !RegionalSave_HashMainSector(&sFireRedSave.hash, &sFireRedSave.schedule,
                                        id, gSaveDataBuffer.data, RegionalSave_MainSectorSize(id)))
            return FALSE;
    }
    if (!RegionalSave_HashMainSector(&sFireRedSave.hash, &sFireRedSave.schedule,
                                    0, sFireRedSave.saveBlock2, sizeof(sFireRedSave.saveBlock2)))
        return FALSE;
    RegionalSave_Sha256Final(&sFireRedSave.hash, &sFireRedSave.schedule, gSaveDataBuffer.data);
    return !memcmp(gSaveDataBuffer.data, sFireRedSave.saveBlock3 + REGIONAL_SAVE_DIGEST_OFFSET, 32)
        && RegionalSave_CheckCrc(sFireRedSave.saveBlock3);
}

static bool8 FireRedPrepareHeader(void)
{
    if (sFireRedSave.phase != FR_SAVE_HEADER || !FireRedVerifyBody() || !FireRedBuildSector(0))
    {
        FireRedSave_Abort();
        return FALSE;
    }
    ((u8 *)&gSaveDataBuffer.signature)[0] = 0xFF;
    if (TryWriteSector(FireRedTargetSector(0), gSaveDataBuffer.data) != SAVE_STATUS_OK
     || !FireRedSave_IsBusy())
    {
        FireRedSave_Abort();
        return FALSE;
    }
    return FireRedAdvancePhase(FR_SAVE_HEADER, FR_SAVE_PREPARED, SAVE_STATUS_OK);
}

static bool8 FireRedCommit(void)
{
    u16 sector = FireRedTargetSector(0);
    u16 ime;
    if (sFireRedSave.phase != FR_SAVE_PREPARED)
    {
        FireRedSave_Abort();
        return FALSE;
    }
    ReadFlashSector(sector, &gSaveDataBuffer);
    if (!FireRedSave_IsBusy()
     || gSaveDataBuffer.id != 0
     || gSaveDataBuffer.counter != sFireRedSave.nextCounter
     || gSaveDataBuffer.signature != ((SECTOR_SIGNATURE & 0xFFFFFF00) | 0xFF)
     || gSaveDataBuffer.checksum != CalculateChecksum(sFireRedSave.saveBlock2, sizeof(sFireRedSave.saveBlock2))
     || memcmp(gSaveDataBuffer.data, sFireRedSave.saveBlock2, sizeof(sFireRedSave.saveBlock2))
     || memcmp(gSaveDataBuffer.saveBlock3Chunk, sFireRedSave.saveBlock3, SAVE_BLOCK_3_CHUNK_SIZE))
    {
        FireRedSave_Abort();
        return FALSE;
    }
    if (!FireRedAdvancePhase(FR_SAVE_PREPARED, FR_SAVE_COMMITTING, SAVE_STATUS_OK))
        return FALSE;
    if (ProgramFlashByte(sector, SECTOR_SIGNATURE_OFFSET, SECTOR_SIGNATURE & 0xFF))
    {
        SetDamagedSectorBits(ENABLE, sector);
        FireRedSave_Abort();
        return FALSE;
    }
    if (!FireRedSave_IsBusy() || FireRedValidateBank(sFireRedSave.targetBank) != SAVE_STATUS_OK || !FireRedSave_IsBusy())
    {
        FireRedSave_Abort();
        return FALSE;
    }
    ime = FireRedEnterCritical();
    if (sFireRedSave.phase != FR_SAVE_COMMITTING)
    {
        FireRedLeaveCritical(ime);
        return FALSE;
    }
    gSaveCounter = sFireRedSave.nextCounter;
    gLastWrittenSector = sFireRedSave.nextRotation;
    gLastSaveCounter = sFireRedSave.oldCounter;
    gLastKnownGoodSector = sFireRedSave.oldRotation;
    // Keep live RTC/setting prefix ticks; only the new serialized tail is updated.
    memcpy((u8 *)&gSaveblock3 + REGIONAL_SAVE_PREFIX_SIZE,
           sFireRedSave.saveBlock3 + REGIONAL_SAVE_PREFIX_SIZE,
           REGIONAL_SAVE_SIZE - REGIONAL_SAVE_PREFIX_SIZE);
    sFireRedSave.selectedBank = sFireRedSave.targetBank;
    sFireRedSave.phase = FR_SAVE_IDLE;
    FireRedRestoreTimer();
    sFireRedSave.loaded = TRUE;
    sFireRedSave.probed = FALSE;
    sFireRedSave.hallOfFamePrepared = FALSE;
    sFireRedSave.result = SAVE_STATUS_OK;
    gSaveAttemptStatus = SAVE_STATUS_OK;
    FireRedLeaveCritical(ime);
    return TRUE;
}

static u8 FireRedHandleSavingData(u8 saveType)
{
    bool8 partial = saveType == SAVE_LINK || saveType == SAVE_EREADER;
    bool8 hallOfFame = saveType == SAVE_HALL_OF_FAME || saveType == SAVE_HALL_OF_FAME_ERASE_BEFORE;
    u32 *backupVar = gTrainerHillVBlankCounter;
    gTrainerHillVBlankCounter = NULL;
    if (!FireRedBeginSave(partial, hallOfFame))
    {
        gTrainerHillVBlankCounter = backupVar;
        return SAVE_STATUS_ERROR;
    }
    while (sFireRedSave.phase == FR_SAVE_BODY)
        if (!FireRedWriteBody())
            break;
    if (sFireRedSave.phase != FR_SAVE_HEADER || !FireRedPrepareHeader() || !FireRedCommit())
    {
        gTrainerHillVBlankCounter = backupVar;
        return SAVE_STATUS_ERROR;
    }
    if (saveType == SAVE_OVERWRITE_DIFFERENT_FILE || saveType == SAVE_HALL_OF_FAME_ERASE_BEFORE)
    {
        u16 i;
        if (!FireRedBeginSpecial())
        {
            gTrainerHillVBlankCounter = backupVar;
            return SAVE_STATUS_ERROR;
        }
        for (i = SECTOR_ID_HOF_1; i < SECTORS_COUNT; i++)
            if (EraseFlashSector(i) || sFireRedSave.phase != FR_SAVE_SPECIAL)
            {
                gTrainerHillVBlankCounter = backupVar;
                FireRedSave_Abort();
                return SAVE_STATUS_ERROR;
            }
    }
    if (hallOfFame && gHoFSaveBuffer != NULL)
    {
        u8 *data = (u8 *)gHoFSaveBuffer;
        if (!FireRedBeginSpecial())
        {
            gTrainerHillVBlankCounter = backupVar;
            return SAVE_STATUS_ERROR;
        }
        if (HandleWriteSectorNBytes(SECTOR_ID_HOF_1, data, SECTOR_DATA_SIZE) != SAVE_STATUS_OK
         || sFireRedSave.phase != FR_SAVE_SPECIAL
         || HandleWriteSectorNBytes(SECTOR_ID_HOF_2, data + SECTOR_DATA_SIZE, SECTOR_DATA_SIZE) != SAVE_STATUS_OK
         || sFireRedSave.phase != FR_SAVE_SPECIAL)
        {
            gTrainerHillVBlankCounter = backupVar;
            FireRedSave_Abort();
            return SAVE_STATUS_ERROR;
        }
    }
    if (sFireRedSave.phase == FR_SAVE_SPECIAL
     && !FireRedAdvancePhase(FR_SAVE_SPECIAL, FR_SAVE_IDLE, SAVE_STATUS_OK))
    {
        gTrainerHillVBlankCounter = backupVar;
        return SAVE_STATUS_ERROR;
    }
    gTrainerHillVBlankCounter = backupVar;
    return sFireRedSave.result;
}
#endif // FIRERED

void ClearSaveData(void)
{
    u16 i;
#ifdef FIRERED
    if (FireRedSave_IsBusy())
    {
        FireRedSave_Abort();
        return;
    }
#endif

    // Clear the full save two sectors at a time
    for (i = 0; i < SECTORS_COUNT / 2; i++)
    {
        EraseFlashSector(i);
        EraseFlashSector(i + SECTORS_COUNT / 2);
    }
#ifdef FIRERED
    FireRedSave_ResetSession();
#endif
}

void Save_ResetSaveCounters(void)
{
    gSaveCounter = 0;
    gLastWrittenSector = 0;
    gDamagedSaveSectors = 0;
}

static bool32 SetDamagedSectorBits(u8 op, u8 sectorId)
{
    bool32 retVal = FALSE;

    switch (op)
    {
    case ENABLE:
        gDamagedSaveSectors |= (1 << sectorId);
        break;
    case DISABLE:
        gDamagedSaveSectors &= ~(1 << sectorId);
        break;
    case CHECK: // unused
        if (gDamagedSaveSectors & (1 << sectorId))
            retVal = TRUE;
        break;
    }

    return retVal;
}

#ifndef FIRERED
static u8 WriteSaveSectorOrSlot(u16 sectorId, const struct SaveSectorLocation *locations)
{
    u32 status;
    u16 i;

    gReadWriteSector = &gSaveDataBuffer;

    if (sectorId != FULL_SAVE_SLOT)
    {
        // A sector was specified, just write that sector.
        // This is never reached, FULL_SAVE_SLOT is always used instead.
        status = HandleWriteSector(sectorId, locations);
    }
    else
    {
        // No sector was specified, write full save slot.
        gLastKnownGoodSector = gLastWrittenSector; // backup the current written sector before attempting to write.
        gLastSaveCounter = gSaveCounter;
        gLastWrittenSector++;
        gLastWrittenSector = gLastWrittenSector % NUM_SECTORS_PER_SLOT;
        gSaveCounter++;
        status = SAVE_STATUS_OK;

        for (i = 0; i < NUM_SECTORS_PER_SLOT; i++)
            HandleWriteSector(i, locations);

        if (gDamagedSaveSectors)
        {
            // At least one sector save failed
            status = SAVE_STATUS_ERROR;
            gLastWrittenSector = gLastKnownGoodSector;
            gSaveCounter = gLastSaveCounter;
        }
    }

    return status;
}

static u8 HandleWriteSector(u16 sectorId, const struct SaveSectorLocation *locations)
{
    u16 i;
    u16 sector;
    u8 *data;
    u16 size;

    // Adjust sector id for current save slot
    sector = sectorId + gLastWrittenSector;
    sector %= NUM_SECTORS_PER_SLOT;
    sector += NUM_SECTORS_PER_SLOT * (gSaveCounter % NUM_SAVE_SLOTS);

    // Get current save data
    data = locations[sectorId].data;
    size = locations[sectorId].size;

    // Clear temp save sector
    for (i = 0; i < SECTOR_SIZE; i++)
        ((u8 *)gReadWriteSector)[i] = 0;

    // Set footer data
    gReadWriteSector->id = sectorId;
    gReadWriteSector->signature = SECTOR_SIGNATURE;
    gReadWriteSector->counter = gSaveCounter;

    // Copy current data to temp buffer for writing
    for (i = 0; i < size; i++)
        gReadWriteSector->data[i] = data[i];

    CopyFromSaveBlock3(sectorId, gReadWriteSector);

    gReadWriteSector->checksum = CalculateChecksum(data, size);

    return TryWriteSector(sector, gReadWriteSector->data);
}

#endif // !FIRERED

static u8 HandleWriteSectorNBytes(u8 sectorId, u8 *data, u16 size)
{
    u16 i;
    struct SaveSector *sector = &gSaveDataBuffer;

    // Clear temp save sector
    for (i = 0; i < SECTOR_SIZE; i++)
        ((u8 *)sector)[i] = 0;

    sector->signature = SECTOR_SIGNATURE;

    // Copy data to temp buffer for writing
    for (i = 0; i < size; i++)
        sector->data[i] = data[i];

    sector->id = CalculateChecksum(data, size); // though this appears to be incorrect, it might be some sector checksum instead of a whole save checksum and only appears to be relevent to HOF data, if used.
    return TryWriteSector(sectorId, sector->data);
}

static u8 TryWriteSector(u8 sector, u8 *data)
{
    if (ProgramFlashSectorAndVerify(sector, data)) // is damaged?
    {
        // Failed
        SetDamagedSectorBits(ENABLE, sector);
        return SAVE_STATUS_ERROR;
    }
    else
    {
        // Succeeded
        SetDamagedSectorBits(DISABLE, sector);
        return SAVE_STATUS_OK;
    }
}

#ifndef FIRERED
static u32 RestoreSaveBackupVarsAndIncrement(const struct SaveSectorLocation *locations)
{
    gReadWriteSector = &gSaveDataBuffer;
    gLastKnownGoodSector = gLastWrittenSector;
    gLastSaveCounter = gSaveCounter;
    gLastWrittenSector++;
    gLastWrittenSector %= NUM_SECTORS_PER_SLOT;
    gSaveCounter++;
    gIncrementalSectorId = 0;
    gDamagedSaveSectors = 0;
    return 0;
}

static u32 RestoreSaveBackupVars(const struct SaveSectorLocation *locations)
{
    gReadWriteSector = &gSaveDataBuffer;
    gLastKnownGoodSector = gLastWrittenSector;
    gLastSaveCounter = gSaveCounter;
    gIncrementalSectorId = 0;
    gDamagedSaveSectors = 0;
    return 0;
}

static u8 HandleWriteIncrementalSector(u16 numSectors, const struct SaveSectorLocation *locations)
{
    u8 status;

    if (gIncrementalSectorId < numSectors - 1)
    {
        status = SAVE_STATUS_OK;
        HandleWriteSector(gIncrementalSectorId, locations);
        gIncrementalSectorId++;
        if (gDamagedSaveSectors)
        {
            status = SAVE_STATUS_ERROR;
            gLastWrittenSector = gLastKnownGoodSector;
            gSaveCounter = gLastSaveCounter;
        }
    }
    else
    {
        // Exceeded max sector, finished
        status = SAVE_STATUS_ERROR;
    }

    return status;
}

static u8 HandleReplaceSectorAndVerify(u16 sectorId, const struct SaveSectorLocation *locations)
{
    u8 status = SAVE_STATUS_OK;

    HandleReplaceSector(sectorId - 1, locations);

    if (gDamagedSaveSectors)
    {
        status = SAVE_STATUS_ERROR;
        gLastWrittenSector = gLastKnownGoodSector;
        gSaveCounter = gLastSaveCounter;
    }
    return status;
}

// Similar to HandleWriteSector, but fully erases the sector first, and skips writing the first signature byte
static u8 HandleReplaceSector(u16 sectorId, const struct SaveSectorLocation *locations)
{
    u16 i;
    u16 sector;
    u8 *data;
    u16 size;
    u8 status;

    // Adjust sector id for current save slot
    sector = sectorId + gLastWrittenSector;
    sector %= NUM_SECTORS_PER_SLOT;
    sector += NUM_SECTORS_PER_SLOT * (gSaveCounter % NUM_SAVE_SLOTS);

    // Get current save data
    data = locations[sectorId].data;
    size = locations[sectorId].size;

    // Clear temp save sector.
    for (i = 0; i < SECTOR_SIZE; i++)
        ((u8 *)gReadWriteSector)[i] = 0;

    // Set footer data
    gReadWriteSector->id = sectorId;
    gReadWriteSector->signature = SECTOR_SIGNATURE;
    gReadWriteSector->counter = gSaveCounter;

    // Copy current data to temp buffer for writing
    for (i = 0; i < size; i++)
        gReadWriteSector->data[i] = data[i];

    CopyFromSaveBlock3(sectorId, gReadWriteSector);

    gReadWriteSector->checksum = CalculateChecksum(data, size);

    // Erase old save data
    EraseFlashSector(sector);

    status = SAVE_STATUS_OK;

    // Write new save data up to signature field
    for (i = 0; i < SECTOR_SIGNATURE_OFFSET; i++)
    {
        if (ProgramFlashByte(sector, i, ((u8 *)gReadWriteSector)[i]))
        {
            status = SAVE_STATUS_ERROR;
            break;
        }
    }

    if (status == SAVE_STATUS_ERROR)
    {
        // Writing save data failed
        SetDamagedSectorBits(ENABLE, sector);
        return SAVE_STATUS_ERROR;
    }
    else
    {
        // Writing save data succeeded, write signature and counter
        status = SAVE_STATUS_OK;

        // Write signature (skipping the first byte) and counter fields.
        // The byte of signature that is skipped is instead written by WriteSectorSignatureByte or WriteSectorSignatureByte_NoOffset
        for (i = 0; i < SECTOR_SIZE - (SECTOR_SIGNATURE_OFFSET + 1); i++)
        {
            if (ProgramFlashByte(sector, SECTOR_SIGNATURE_OFFSET + 1 + i, ((u8 *)gReadWriteSector)[SECTOR_SIGNATURE_OFFSET + 1 + i]))
            {
                status = SAVE_STATUS_ERROR;
                break;
            }
        }

        if (status == SAVE_STATUS_ERROR)
        {
            // Writing signature/counter failed
            SetDamagedSectorBits(ENABLE, sector);
            return SAVE_STATUS_ERROR;
        }
        else
        {
            // Succeeded
            SetDamagedSectorBits(DISABLE, sector);
            return SAVE_STATUS_OK;
        }
    }
}

static u8 WriteSectorSignatureByte_NoOffset(u16 sectorId, const struct SaveSectorLocation *locations)
{
    // Adjust sector id for current save slot
    // This first line lacking -1 is the only difference from WriteSectorSignatureByte
    u16 sector = sectorId + gLastWrittenSector;
    sector %= NUM_SECTORS_PER_SLOT;
    sector += NUM_SECTORS_PER_SLOT * (gSaveCounter % NUM_SAVE_SLOTS);

    // Write just the first byte of the signature field, which was skipped by HandleReplaceSector
    if (ProgramFlashByte(sector, SECTOR_SIGNATURE_OFFSET, SECTOR_SIGNATURE & 0xFF))
    {
        // Sector is damaged, so enable the bit in gDamagedSaveSectors and restore the last written sector and save counter.
        SetDamagedSectorBits(ENABLE, sector);
        gLastWrittenSector = gLastKnownGoodSector;
        gSaveCounter = gLastSaveCounter;
        return SAVE_STATUS_ERROR;
    }
    else
    {
        // Succeeded
        SetDamagedSectorBits(DISABLE, sector);
        return SAVE_STATUS_OK;
    }
}

static u8 CopySectorSignatureByte(u16 sectorId, const struct SaveSectorLocation *locations)
{
    // Adjust sector id for current save slot
    u16 sector = sectorId + gLastWrittenSector - 1;
    sector %= NUM_SECTORS_PER_SLOT;
    sector += NUM_SECTORS_PER_SLOT * (gSaveCounter % NUM_SAVE_SLOTS);

    // Copy just the first byte of the signature field from the read/write buffer
    if (ProgramFlashByte(sector, SECTOR_SIGNATURE_OFFSET, ((u8 *)gReadWriteSector)[SECTOR_SIGNATURE_OFFSET]))
    {
        // Sector is damaged, so enable the bit in gDamagedSaveSectors and restore the last written sector and save counter.
        SetDamagedSectorBits(ENABLE, sector);
        gLastWrittenSector = gLastKnownGoodSector;
        gSaveCounter = gLastSaveCounter;
        return SAVE_STATUS_ERROR;
    }
    else
    {
        // Succeeded
        SetDamagedSectorBits(DISABLE, sector);
        return SAVE_STATUS_OK;
    }
}

static u8 WriteSectorSignatureByte(u16 sectorId, const struct SaveSectorLocation *locations)
{
    // Adjust sector id for current save slot
    u16 sector = sectorId + gLastWrittenSector - 1;
    sector %= NUM_SECTORS_PER_SLOT;
    sector += NUM_SECTORS_PER_SLOT * (gSaveCounter % NUM_SAVE_SLOTS);

    // Write just the first byte of the signature field, which was skipped by HandleReplaceSector
    if (ProgramFlashByte(sector, SECTOR_SIGNATURE_OFFSET, SECTOR_SIGNATURE & 0xFF))
    {
        // Sector is damaged, so enable the bit in gDamagedSaveSectors and restore the last written sector and save counter.
        SetDamagedSectorBits(ENABLE, sector);
        gLastWrittenSector = gLastKnownGoodSector;
        gSaveCounter = gLastSaveCounter;
        return SAVE_STATUS_ERROR;
    }
    else
    {
        // Succeeded
        SetDamagedSectorBits(DISABLE, sector);
        return SAVE_STATUS_OK;
    }
}

static u8 TryLoadSaveSlot(u16 sectorId, struct SaveSectorLocation *locations)
{
    u8 status;
    gReadWriteSector = &gSaveDataBuffer;
    if (sectorId != FULL_SAVE_SLOT)
    {
        // This function may not be used with a specific sector id
        status = SAVE_STATUS_ERROR;
    }
    else
    {
        status = GetSaveValidStatus(locations);
        CopySaveSlotData(FULL_SAVE_SLOT, locations);
    }

    return status;
}

// sectorId arg is ignored, this always reads the full save slot
static u8 CopySaveSlotData(u16 sectorId, struct SaveSectorLocation *locations)
{
    u16 i;
    u16 checksum;
    u16 slotOffset = NUM_SECTORS_PER_SLOT * (gSaveCounter % NUM_SAVE_SLOTS);
    u16 id;

    for (i = 0; i < NUM_SECTORS_PER_SLOT; i++)
    {
        ReadFlashSector(i + slotOffset, gReadWriteSector);

        id = gReadWriteSector->id;
        if (id == 0)
            gLastWrittenSector = i;

        checksum = CalculateChecksum(gReadWriteSector->data, locations[id].size);

        // Only copy data for sectors whose signature and checksum fields are correct
        if (gReadWriteSector->signature == SECTOR_SIGNATURE && gReadWriteSector->checksum == checksum)
        {
            u16 j;
            for (j = 0; j < locations[id].size; j++)
                ((u8 *)locations[id].data)[j] = gReadWriteSector->data[j];
            CopyToSaveBlock3(id, gReadWriteSector);
        }
    }

    return SAVE_STATUS_OK;
}

static u8 GetSaveValidStatus(const struct SaveSectorLocation *locations)
{
    u16 i;
    u16 checksum;
    u32 saveSlot1Counter = 0;
    u32 saveSlot2Counter = 0;
    u32 validSectorFlags = 0;
    bool8 signatureValid = FALSE;
    u8 saveSlot1Status;
    u8 saveSlot2Status;

    // Check save slot 1
    for (i = 0; i < NUM_SECTORS_PER_SLOT; i++)
    {
        ReadFlashSector(i, gReadWriteSector);
        if (gReadWriteSector->signature == SECTOR_SIGNATURE)
        {
            signatureValid = TRUE;
            checksum = CalculateChecksum(gReadWriteSector->data, locations[gReadWriteSector->id].size);
            if (gReadWriteSector->checksum == checksum)
            {
                saveSlot1Counter = gReadWriteSector->counter;
                validSectorFlags |= 1 << gReadWriteSector->id;
            }
        }
    }

    if (signatureValid)
    {
        if (validSectorFlags == (1 << NUM_SECTORS_PER_SLOT) - 1)
            saveSlot1Status = SAVE_STATUS_OK;
        else
            saveSlot1Status = SAVE_STATUS_ERROR;
    }
    else
    {
        // No sectors in slot 1 have the correct signature, treat it as empty
        saveSlot1Status = SAVE_STATUS_EMPTY;
    }

    validSectorFlags = 0;
    signatureValid = FALSE;

    // Check save slot 2
    for (i = 0; i < NUM_SECTORS_PER_SLOT; i++)
    {
        ReadFlashSector(i + NUM_SECTORS_PER_SLOT, gReadWriteSector);
        if (gReadWriteSector->signature == SECTOR_SIGNATURE)
        {
            signatureValid = TRUE;
            checksum = CalculateChecksum(gReadWriteSector->data, locations[gReadWriteSector->id].size);
            if (gReadWriteSector->checksum == checksum)
            {
                saveSlot2Counter = gReadWriteSector->counter;
                validSectorFlags |= 1 << gReadWriteSector->id;
            }
        }
    }

    if (signatureValid)
    {
        if (validSectorFlags == (1 << NUM_SECTORS_PER_SLOT) - 1)
            saveSlot2Status = SAVE_STATUS_OK;
        else
            saveSlot2Status = SAVE_STATUS_ERROR;
    }
    else
    {
        // No sectors in slot 2 have the correct signature, treat it as empty.
        saveSlot2Status = SAVE_STATUS_EMPTY;
    }

    if (saveSlot1Status == SAVE_STATUS_OK && saveSlot2Status == SAVE_STATUS_OK)
    {
        if ((saveSlot1Counter == -1 && saveSlot2Counter ==  0)
         || (saveSlot1Counter ==  0 && saveSlot2Counter == -1))
        {
            if ((unsigned)(saveSlot1Counter + 1) < (unsigned)(saveSlot2Counter + 1))
                gSaveCounter = saveSlot2Counter;
            else
                gSaveCounter = saveSlot1Counter;
        }
        else
        {
            if (saveSlot1Counter < saveSlot2Counter)
                gSaveCounter = saveSlot2Counter;
            else
                gSaveCounter = saveSlot1Counter;
        }
        return SAVE_STATUS_OK;
    }

    // One or both save slots are not OK

    if (saveSlot1Status == SAVE_STATUS_OK)
    {
        gSaveCounter = saveSlot1Counter;
        if (saveSlot2Status == SAVE_STATUS_ERROR)
            return SAVE_STATUS_ERROR; // Slot 2 errored
        return SAVE_STATUS_OK; // Slot 1 is OK, slot 2 is empty
    }

    if (saveSlot2Status == SAVE_STATUS_OK)
    {
        gSaveCounter = saveSlot2Counter;
        if (saveSlot1Status == SAVE_STATUS_ERROR)
            return SAVE_STATUS_ERROR; // Slot 1 errored
        return SAVE_STATUS_OK; // Slot 2 is OK, slot 1 is empty
    }

    // Neither slot is OK, check if both are empty
    if (saveSlot1Status == SAVE_STATUS_EMPTY
     && saveSlot2Status == SAVE_STATUS_EMPTY)
    {
        gSaveCounter = 0;
        gLastWrittenSector = 0;
        return SAVE_STATUS_EMPTY;
    }

    // Both slots errored
    gSaveCounter = 0;
    gLastWrittenSector = 0;
    return SAVE_STATUS_CORRUPT;
}

#endif // !FIRERED

static u8 TryLoadSaveSector(u8 sectorId, u8 *data, u16 size)
{
    u16 i;
    struct SaveSector *sector = &gSaveDataBuffer;
    ReadFlashSector(sectorId, sector);
    if (sector->signature == SECTOR_SIGNATURE)
    {
        u16 checksum = CalculateChecksum(sector->data, size);
        if (sector->id == checksum)
        {
            // Signature and checksum are correct, copy data
            for (i = 0; i < size; i++)
                data[i] = sector->data[i];
            return SAVE_STATUS_OK;
        }
        else
        {
            // Incorrect checksum
            return SAVE_STATUS_CORRUPT;
        }
    }
    else
    {
        // Incorrect signature value
        return SAVE_STATUS_EMPTY;
    }
}

// Return value always ignored
static bool8 ReadFlashSector(u8 sectorId, struct SaveSector *sector)
{
    ReadFlash(sectorId, 0, sector->data, SECTOR_SIZE);
    return TRUE;
}

static u16 CalculateChecksum(void *data, u16 size)
{
    u16 i;
    u32 checksum = 0;

    for (i = 0; i < (size / 4); i++)
    {
        checksum += *((u32 *)data);
        data += sizeof(u32);
    }

    return ((checksum >> 16) + checksum);
}

static void UpdateSaveAddresses(void)
{
    int i = SECTOR_ID_SAVEBLOCK2;
    gRamSaveSectorLocations[i].data = (void *)(gSaveBlock2Ptr) + sSaveSlotLayout[i].offset;
    gRamSaveSectorLocations[i].size = sSaveSlotLayout[i].size;

    for (i = SECTOR_ID_SAVEBLOCK1_START; i <= SECTOR_ID_SAVEBLOCK1_END; i++)
    {
        gRamSaveSectorLocations[i].data = (void *)(gSaveBlock1Ptr) + sSaveSlotLayout[i].offset;
        gRamSaveSectorLocations[i].size = sSaveSlotLayout[i].size;
    }

    for (; i <= SECTOR_ID_PKMN_STORAGE_END; i++) //setting i to SECTOR_ID_PKMN_STORAGE_START does not match
    {
        gRamSaveSectorLocations[i].data = (void *)(gPokemonStoragePtr) + sSaveSlotLayout[i].offset;
        gRamSaveSectorLocations[i].size = sSaveSlotLayout[i].size;
    }
}

u8 HandleSavingData(u8 saveType)
{
#ifdef FIRERED
    return FireRedHandleSavingData(saveType);
#else
    u8 i;
    u32 *backupVar = gTrainerHillVBlankCounter;

    gTrainerHillVBlankCounter = NULL;
    UpdateSaveAddresses();
    switch (saveType)
    {
    case SAVE_HALL_OF_FAME_ERASE_BEFORE:
        // Unused. Erases the special save sectors (HOF, Trainer Hill, Recorded Battle)
        // before overwriting HOF.
        for (i = SECTOR_ID_HOF_1; i < SECTORS_COUNT; i++)
            EraseFlashSector(i);
        // fallthrough
    case SAVE_HALL_OF_FAME:
        if (GetGameStat(GAME_STAT_ENTERED_HOF) < 999)
            IncrementGameStat(GAME_STAT_ENTERED_HOF);

        // Write the full save slot first
        CopyPartyAndObjectsToSave();
        WriteSaveSectorOrSlot(FULL_SAVE_SLOT, gRamSaveSectorLocations);

        // Save the Hall of Fame
        if (gHoFSaveBuffer != NULL)
        {
            u8 *tempAddr = (void *) gHoFSaveBuffer;
            HandleWriteSectorNBytes(SECTOR_ID_HOF_1, tempAddr, SECTOR_DATA_SIZE);
            HandleWriteSectorNBytes(SECTOR_ID_HOF_2, tempAddr + SECTOR_DATA_SIZE, SECTOR_DATA_SIZE);
        }
        break;
    case SAVE_NORMAL:
    default:
        CopyPartyAndObjectsToSave();
        WriteSaveSectorOrSlot(FULL_SAVE_SLOT, gRamSaveSectorLocations);
        break;
    case SAVE_LINK:
    case SAVE_EREADER: // Dummied, now duplicate of SAVE_LINK
        // Used by link / Battle Frontier
        // Write only SaveBlocks 1 and 2 (skips the PC)
        CopyPartyAndObjectsToSave();
        for (i = SECTOR_ID_SAVEBLOCK2; i <= SECTOR_ID_SAVEBLOCK1_END; i++)
            HandleReplaceSector(i, gRamSaveSectorLocations);
        for (i = SECTOR_ID_SAVEBLOCK2; i <= SECTOR_ID_SAVEBLOCK1_END; i++)
            WriteSectorSignatureByte_NoOffset(i, gRamSaveSectorLocations);
        break;
    case SAVE_OVERWRITE_DIFFERENT_FILE:
        // Erase Hall of Fame
        for (i = SECTOR_ID_HOF_1; i < SECTORS_COUNT; i++)
            EraseFlashSector(i);

        // Overwrite save slot
        CopyPartyAndObjectsToSave();
        WriteSaveSectorOrSlot(FULL_SAVE_SLOT, gRamSaveSectorLocations);
        break;
    }
    gTrainerHillVBlankCounter = backupVar;
    return 0;
#endif
}

u8 TrySavingData(u8 saveType)
{
#ifdef FIRERED
    u8 status = HandleSavingData(saveType);
    gSaveAttemptStatus = status;
    if (status != SAVE_STATUS_OK)
        DoSaveFailedScreen(saveType);
    return status;
#else
    if (gFlashMemoryPresent != TRUE)
    {
        gSaveAttemptStatus = SAVE_STATUS_ERROR;
        return SAVE_STATUS_ERROR;
    }

    HandleSavingData(saveType);
    if (!gDamagedSaveSectors)
    {
        gSaveAttemptStatus = SAVE_STATUS_OK;
        return SAVE_STATUS_OK;
    }
    else
    {
        DoSaveFailedScreen(saveType);
        gSaveAttemptStatus = SAVE_STATUS_ERROR;
        return SAVE_STATUS_ERROR;
    }
#endif
}

bool8 LinkFullSave_Init(void)
{
#ifdef FIRERED
    return !FireRedBeginSave(FALSE, FALSE);
#else
    if (gFlashMemoryPresent != TRUE)
        return TRUE;
    UpdateSaveAddresses();
    CopyPartyAndObjectsToSave();
    RestoreSaveBackupVarsAndIncrement(gRamSaveSectorLocations);
    return FALSE;
#endif
}

bool8 LinkFullSave_WriteSector(void)
{
#ifdef FIRERED
    if (sFireRedSave.phase == FR_SAVE_BODY)
    {
        if (!FireRedWriteBody())
            return TRUE;
        return sFireRedSave.phase == FR_SAVE_HEADER;
    }
    return TRUE;
#else
    u8 status = HandleWriteIncrementalSector(NUM_SECTORS_PER_SLOT, gRamSaveSectorLocations);
    if (gDamagedSaveSectors)
        DoSaveFailedScreen(SAVE_NORMAL);

    // In this case "error" either means that an actual error was encountered
    // or that the given max sector has been reached (meaning it has finished successfully).
    // If there was an actual error the save failed screen above will also be shown.
    if (status == SAVE_STATUS_ERROR)
        return TRUE;
    else
        return FALSE;
#endif
}

bool8 LinkFullSave_ReplaceLastSector(void)
{
#ifdef FIRERED
    return !FireRedPrepareHeader();
#else
    HandleReplaceSectorAndVerify(NUM_SECTORS_PER_SLOT, gRamSaveSectorLocations);
    if (gDamagedSaveSectors)
        DoSaveFailedScreen(SAVE_NORMAL);
    return FALSE;
#endif
}

bool8 LinkFullSave_SetLastSectorSignature(void)
{
#ifdef FIRERED
    return !FireRedCommit();
#else
    CopySectorSignatureByte(NUM_SECTORS_PER_SLOT, gRamSaveSectorLocations);
    if (gDamagedSaveSectors)
        DoSaveFailedScreen(SAVE_NORMAL);
    return FALSE;
#endif
}

bool8 WriteSaveBlock2(void)
{
#ifdef FIRERED
    return !FireRedBeginSave(TRUE, FALSE) || !FireRedWriteBody();
#else
    if (gFlashMemoryPresent != TRUE)
        return TRUE;

    UpdateSaveAddresses();
    CopyPartyAndObjectsToSave();
    RestoreSaveBackupVars(gRamSaveSectorLocations);

    // Because RestoreSaveBackupVars is called immediately prior, gIncrementalSectorId will always be 0 below,
    // so this function only saves the first sector (SECTOR_ID_SAVEBLOCK2)
    HandleReplaceSectorAndVerify(gIncrementalSectorId + 1, gRamSaveSectorLocations);
    return FALSE;
#endif
}

// Used in conjunction with WriteSaveBlock2 to write both for certain link saves.
// This will be called repeatedly in a task, writing each sector of SaveBlock1 incrementally.
// It returns TRUE when finished.
bool8 WriteSaveBlock1Sector(void)
{
#ifdef FIRERED
    if (sFireRedSave.phase == FR_SAVE_BODY)
    {
        if (!FireRedWriteBody())
            return TRUE;
        return FALSE;
    }
    if (sFireRedSave.phase == FR_SAVE_HEADER)
    {
        if (!FireRedPrepareHeader())
            return TRUE;
        FireRedCommit();
    }
    return TRUE;
#else
    bool32 finished = FALSE;
    u16 sectorId = ++gIncrementalSectorId; // Because WriteSaveBlock2 will have been called prior, this will be SECTOR_ID_SAVEBLOCK1_START
    if (sectorId <= SECTOR_ID_SAVEBLOCK1_END)
    {
        // Write a single sector of SaveBlock1
        HandleReplaceSectorAndVerify(gIncrementalSectorId + 1, gRamSaveSectorLocations);
        WriteSectorSignatureByte(sectorId, gRamSaveSectorLocations);
    }
    else
    {
        // Beyond SaveBlock1, don't write the sector.
        // Does write 1 byte of the next sector's signature field, but as these
        // are the same for all valid sectors it doesn't matter.
        WriteSectorSignatureByte(sectorId, gRamSaveSectorLocations);
        finished = TRUE;
    }

    if (gDamagedSaveSectors)
        DoSaveFailedScreen(SAVE_LINK);

    return finished;
#endif
}

u8 LoadGameSave(u8 saveType)
{
    u8 status;

    if (gFlashMemoryPresent != TRUE)
    {
        gSaveFileStatus = SAVE_STATUS_NO_FLASH;
        return SAVE_STATUS_ERROR;
    }

    UpdateSaveAddresses();
#ifdef FIRERED
    if (FireRedSave_IsBusy())
    {
        FireRedSave_Abort();
        return SAVE_STATUS_ERROR;
    }
    if (saveType == SAVE_HALL_OF_FAME)
    {
        if (gHoFSaveBuffer == NULL)
            return SAVE_STATUS_ERROR;
        status = TryLoadSaveSector(SECTOR_ID_HOF_1, (u8 *)gHoFSaveBuffer, SECTOR_DATA_SIZE);
        if (status == SAVE_STATUS_OK)
            status = TryLoadSaveSector(SECTOR_ID_HOF_2, (u8 *)gHoFSaveBuffer + SECTOR_DATA_SIZE, SECTOR_DATA_SIZE);
        return status;
    }
    status = FireRedLoadGame();
    if (FireRedSave_IsLoaded() && (status == SAVE_STATUS_OK || status == SAVE_STATUS_RECOVERED))
        CopyPartyAndObjectsFromSave();
    gSaveFileStatus = status;
    gGameContinueCallback = NULL;
    return status;
#else
    switch (saveType)
    {
    case SAVE_NORMAL:
    default:
        status = TryLoadSaveSlot(FULL_SAVE_SLOT, gRamSaveSectorLocations);
        CopyPartyAndObjectsFromSave();
        gSaveFileStatus = status;
        gGameContinueCallback = NULL;
        break;
    case SAVE_HALL_OF_FAME:
        if (gHoFSaveBuffer != NULL)
        {
            u8 *hofData = (u8 *) gHoFSaveBuffer;
            status = TryLoadSaveSector(SECTOR_ID_HOF_1, hofData, SECTOR_DATA_SIZE);
            if (status == SAVE_STATUS_OK)
                status = TryLoadSaveSector(SECTOR_ID_HOF_2, &hofData[SECTOR_DATA_SIZE], SECTOR_DATA_SIZE);
        }
        else
        {
            status = SAVE_STATUS_ERROR;
        }
        break;
    }

    // Save version migration: detect pre-versioned saves and run upgrades
    if (gSaveBlock1Ptr->saveVersionMagic != SAVE_VERSION_MAGIC)
    {
        gSaveBlock1Ptr->saveVersion = 0;
        gSaveBlock1Ptr->saveVersionMagic = SAVE_VERSION_MAGIC;
    }
    if (gSaveBlock1Ptr->saveVersion < 1)
    {
#if IS_HNS
        FlagSet(FLAG_ENABLE_CONDITION);
#endif
        gSaveBlock1Ptr->saveVersion = 1;
    }
    if (gSaveBlock1Ptr->saveVersion < 2)
    {
#if IS_HNS
        FlagClear(FLAG_ITEM_ICEPATH4_TM_AVALANCHE);
        FlagClear(FLAG_ITEM_VICTORYROAD1_TM_EARTHQUAKE);
#endif
        gSaveBlock1Ptr->saveVersion = 2;
    }

    if (gSaveBlock1Ptr->saveVersion < 4)
    {
#if FREE_MATCH_CALL == FALSE
        // Irwin, Derek and Beverly used to fill all five rematch slots with their
        // first-battle trainer ID, so SetRematchIdForTrainer counted every slot as
        // already beaten and stored REMATCHES_COUNT. Now that they have real tiers,
        // knock any pending rematch back to the first one so it lines up with the
        // tier the player will actually be handed. Harmless on non-HnS builds, where
        // these slots are Brooke/Jessica/John & Jay and the value is only ever
        // tested against zero.
        static const u8 sRematchIdsToReset[] = {
            REMATCH_BROOKE,       // Irwin
            REMATCH_JESSICA,      // Derek
            REMATCH_JOHN_AND_JAY, // Beverly
        };
        u32 i;

        for (i = 0; i < ARRAY_COUNT(sRematchIdsToReset); i++)
        {
            if (gSaveBlock1Ptr->trainerRematches[sRematchIdsToReset[i]] != 0)
                gSaveBlock1Ptr->trainerRematches[sRematchIdsToReset[i]] = 1;
        }
#endif //FREE_MATCH_CALL
        gSaveBlock1Ptr->saveVersion = 4;
    }
    if (gSaveBlock1Ptr->saveVersion < 5)
    {
#if IS_HNS
        FlagSet(FLAG_HIDE_VERMILION_CITY_SAMSON);
        FlagSet(FLAG_HIDE_ROUTE28_SCIENTIST);
        VarSet(VAR_VERMILION_CITY_SAMSON, 0);
        VarSet(VAR_ROUTE28_SCIENTIST, 0);
#endif
        gSaveBlock1Ptr->saveVersion = 5;
    }

    // Add version migration steps here:
    // if (gSaveBlock1Ptr->saveVersion < 1)
    // {
    //     /* migration code */
    //     gSaveBlock1Ptr->saveVersion = 1;
    // }
    return status;
#endif
}

u16 GetSaveBlocksPointersBaseOffset(void)
{
#ifdef FIRERED
    u8 status = FireRedSave_Probe();
    u16 offset = offsetof(struct SaveBlock2, playerTrainerId);
    if (status != SAVE_STATUS_OK && status != SAVE_STATUS_RECOVERED)
        return 0;
    return sFireRedSave.saveBlock2[offset] + sFireRedSave.saveBlock2[offset + 1]
         + sFireRedSave.saveBlock2[offset + 2] + sFireRedSave.saveBlock2[offset + 3];
#else
    u16 i, slotOffset;
    struct SaveSector *sector;

    sector = gReadWriteSector = &gSaveDataBuffer;
    if (gFlashMemoryPresent != TRUE)
        return 0;
    UpdateSaveAddresses();
    GetSaveValidStatus(gRamSaveSectorLocations);
    slotOffset = NUM_SECTORS_PER_SLOT * (gSaveCounter % NUM_SAVE_SLOTS);
    for (i = 0; i < NUM_SECTORS_PER_SLOT; i++)
    {
        ReadFlashSector(i + slotOffset, gReadWriteSector);

        // Base offset for SaveBlock2 is calculated using the trainer id
        if (gReadWriteSector->id == SECTOR_ID_SAVEBLOCK2)
            return sector->data[offsetof(struct SaveBlock2, playerTrainerId[0])] +
                   sector->data[offsetof(struct SaveBlock2, playerTrainerId[1])] +
                   sector->data[offsetof(struct SaveBlock2, playerTrainerId[2])] +
                   sector->data[offsetof(struct SaveBlock2, playerTrainerId[3])];
    }
    return 0;
#endif
}

u32 TryReadSpecialSaveSector(u8 sector, u8 *dst)
{
#ifdef FIRERED
    if (FireRedSave_IsBusy())
    {
        FireRedSave_Abort();
        return SAVE_STATUS_ERROR;
    }
#endif
    s32 i;
    s32 size;
    u8 *savData;

    if (sector != SECTOR_ID_TRAINER_HILL && sector != SECTOR_ID_RECORDED_BATTLE)
        return SAVE_STATUS_ERROR;

    ReadFlash(sector, 0, (u8 *)&gSaveDataBuffer, SECTOR_SIZE);
    if (*(u32 *)(&gSaveDataBuffer.data[0]) != SPECIAL_SECTOR_SENTINEL)
        return SAVE_STATUS_ERROR;

    // Copies whole save sector except u32 counter
    i = 0;
    size = SECTOR_COUNTER_OFFSET - 1;
    savData = &gSaveDataBuffer.data[4]; // data[4] to skip past SPECIAL_SECTOR_SENTINEL
    for (; i <= size; i++)
        dst[i] = savData[i];
    return SAVE_STATUS_OK;
}

u32 TryWriteSpecialSaveSector(u8 sector, u8 *src)
{
#ifdef FIRERED
    if (FireRedSave_IsBusy())
    {
        FireRedSave_Abort();
        return SAVE_STATUS_ERROR;
    }
#endif
    s32 i;
    s32 size;
    u8 *savData;
    void *savDataBuffer;

    if (sector != SECTOR_ID_TRAINER_HILL && sector != SECTOR_ID_RECORDED_BATTLE)
        return SAVE_STATUS_ERROR;

    savDataBuffer = &gSaveDataBuffer;
    *(u32 *)(savDataBuffer) = SPECIAL_SECTOR_SENTINEL;

    // Copies whole save sector except u32 counter
    i = 0;
    size = SECTOR_COUNTER_OFFSET - 1;
    savData = &gSaveDataBuffer.data[4]; // data[4] to skip past SPECIAL_SECTOR_SENTINEL
    for (; i <= size; i++)
        savData[i] = src[i];
    if (ProgramFlashSectorAndVerify(sector, savDataBuffer) != 0)
        return SAVE_STATUS_ERROR;
    return SAVE_STATUS_OK;
}

#define tState         data[0]
#define tTimer         data[1]
#define tInBattleTower data[2]

// Note that this is very different from TrySavingData(SAVE_LINK).
// Most notably it does save the PC data.
void Task_LinkFullSave(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
#ifdef FIRERED
    if (tState >= 4 && FireRedSave_LastResult() != SAVE_STATUS_OK)
    {
        FireRedSave_Abort();
        gSoftResetDisabled = FALSE;
        DestroyTask(taskId);
        DoSaveFailedScreen(SAVE_NORMAL);
        return;
    }
#endif

    switch (tState)
    {
    case 0:
        gSoftResetDisabled = TRUE;
        tState = 1;
        break;
    case 1:
        SetLinkStandbyCallback();
        tState = 2;
        break;
    case 2:
        if (IsLinkTaskFinished())
        {
            if (!tInBattleTower)
                SaveMapView();
            tState = 3;
        }
        break;
    case 3:
        if (!tInBattleTower)
            SetContinueGameWarpStatusToDynamicWarp();
#ifdef FIRERED
        if (LinkFullSave_Init())
        {
            gSoftResetDisabled = FALSE;
            DestroyTask(taskId);
            DoSaveFailedScreen(SAVE_NORMAL);
            return;
        }
#else
        LinkFullSave_Init();
#endif
        tState = 4;
        break;
    case 4:
        if (++tTimer == 5)
        {
            tTimer = 0;
            tState = 5;
        }
        break;
    case 5:
        if (LinkFullSave_WriteSector())
            tState = 6;
        else
            tState = 4; // Not finished, delay again
        break;
    case 6:
#ifdef FIRERED
        if (LinkFullSave_ReplaceLastSector())
        {
            gSoftResetDisabled = FALSE;
            DestroyTask(taskId);
            DoSaveFailedScreen(SAVE_NORMAL);
            return;
        }
#else
        LinkFullSave_ReplaceLastSector();
#endif
        tState = 7;
        break;
    case 7:
        if (!tInBattleTower)
            ClearContinueGameWarpStatus2();
        SetLinkStandbyCallback();
        tState = 8;
        break;
    case 8:
        if (IsLinkTaskFinished())
        {
#ifdef FIRERED
            if (LinkFullSave_SetLastSectorSignature() || FireRedSave_IsBusy())
            {
                FireRedSave_Abort();
                gSoftResetDisabled = FALSE;
                DestroyTask(taskId);
                DoSaveFailedScreen(SAVE_NORMAL);
                return;
            }
#else
            LinkFullSave_SetLastSectorSignature();
#endif
            tState = 9;
        }
        break;
    case 9:
        SetLinkStandbyCallback();
        tState = 10;
        break;
    case 10:
        if (IsLinkTaskFinished())
            tState++;
        break;
    case 11:
        if (++tTimer > 5)
        {
            gSoftResetDisabled = FALSE;
            DestroyTask(taskId);
        }
        break;
    }
}

#ifndef FIRERED
static u32 SaveBlock3Size(u32 sectorId)
{
    s32 begin = sectorId * SAVE_BLOCK_3_CHUNK_SIZE;
    s32 end = (sectorId + 1) * SAVE_BLOCK_3_CHUNK_SIZE;
    return max(0, min(end, (s32)sizeof(gSaveblock3)) - begin);
}

static void CopyToSaveBlock3(u32 sectorId, struct SaveSector *sector)
{
    u32 size = SaveBlock3Size(sectorId);
    memcpy((u8 *)&gSaveblock3 + (sectorId * SAVE_BLOCK_3_CHUNK_SIZE), sector->saveBlock3Chunk, size);
}

static void CopyFromSaveBlock3(u32 sectorId, struct SaveSector *sector)
{
    u32 size = SaveBlock3Size(sectorId);
    memcpy(sector->saveBlock3Chunk, (u8 *)&gSaveblock3 + (sectorId * SAVE_BLOCK_3_CHUNK_SIZE), size);
}
#endif // !FIRERED

#ifndef GUARD_REGIONAL_SAVE_H
#define GUARD_REGIONAL_SAVE_H

#include "global.h"

#ifdef FIRERED
#define REGIONAL_SAVE_SIZE 1332
#define REGIONAL_SAVE_PREFIX_SIZE 52
#define REGIONAL_SAVE_HEADER_SIZE 64
#define REGIONAL_SAVE_HEADER_OFFSET 52
#define REGIONAL_SAVE_SCHEMA_OFFSET 56
#define REGIONAL_SAVE_HEADER_LENGTH_OFFSET 58
#define REGIONAL_SAVE_LENGTH_OFFSET 60
#define REGIONAL_SAVE_FLAGS_OFFSET 62
#define REGIONAL_SAVE_GENERATION_OFFSET 64
#define REGIONAL_SAVE_CONTENT_OFFSET 68
#define REGIONAL_SAVE_LAYOUT_OFFSET 72
#define REGIONAL_SAVE_RECORD_COUNT_OFFSET 76
#define REGIONAL_SAVE_RESERVED_OFFSET 78
#define REGIONAL_SAVE_CRC_OFFSET 80
#define REGIONAL_SAVE_DIGEST_OFFSET 84
#define REGIONAL_SAVE_KANTO_OFFSET 116
#define REGIONAL_SAVE_JOHTO_OFFSET 148
#define REGIONAL_SAVE_JOHTO_FLAGS_OFFSET 152
#define REGIONAL_SAVE_JOHTO_BADGES_OFFSET 156
#define REGIONAL_SAVE_JOHTO_STARTER_STATE_OFFSET 157
#define REGIONAL_SAVE_JOHTO_STARTER_SPECIES_OFFSET 158
#define REGIONAL_SAVE_JOHTO_RIVAL_OFFSET 160
#define REGIONAL_SAVE_JOHTO_EVENT_REVISION_OFFSET 168
#define REGIONAL_SAVE_JOHTO_TRAINER_REVISION_OFFSET 172
#define REGIONAL_SAVE_JOHTO_VAR_REVISION_OFFSET 176
#define REGIONAL_SAVE_JOHTO_INITIALIZED 1
#define REGIONAL_SAVE_EVENTS_OFFSET 180
#define REGIONAL_SAVE_TRAINERS_OFFSET 436
#define REGIONAL_SAVE_VARS_OFFSET 564
#define REGIONAL_SAVE_TRAVEL_OFFSET 1044
#define REGIONAL_SAVE_RESERVE_OFFSET 1076
#define REGIONAL_SAVE_RESERVE_SIZE 256
#define REGIONAL_SAVE_EVENT_COUNT 2048
#define REGIONAL_SAVE_CAMPAIGN_EVENT_COUNT 1539
#define REGIONAL_SAVE_DOG_ROAMERS_OFFSET 376
#define REGIONAL_SAVE_DOG_ROAMER_SIZE 28
#define REGIONAL_SAVE_DOG_ROAMER_COUNT 2
#define REGIONAL_SAVE_MOM_SAVINGS_OFFSET 1044
#define REGIONAL_SAVE_DOG_LOCATIONS_OFFSET 1052
#define REGIONAL_SAVE_DOG_HISTORY_OFFSET 1056
#define REGIONAL_SAVE_REMATCH_BIT_OFFSET 864
#define REGIONAL_SAVE_REMATCH_COUNT 40
#define REGIONAL_SAVE_REMATCH_STEP_BIT_OFFSET 984
#define REGIONAL_SAVE_TRAINER_COUNT 1024
#define REGIONAL_SAVE_VAR_COUNT 240
#define REGIONAL_SAVE_SCHEMA 1
#define REGIONAL_SAVE_FOUNDATION_CONTENT_ID 1
#define REGIONAL_SAVE_PROTOTYPE_CONTENT_ID 2
#define REGIONAL_SAVE_CONTENT_ID 3
#define REGIONAL_SAVE_HEADER_CAMPAIGN_SEEDED 4
#define REGIONAL_SAVE_CAMPAIGN_MAPPING_REVISION 2
#define REGIONAL_SAVE_LAYOUT_ID 1
#define REGIONAL_SAVE_KANTO 1
#define REGIONAL_SAVE_JOHTO 2

enum RegionalSaveHeaderStatus
{
    REGIONAL_SAVE_HEADER_INVALID = 0,
    REGIONAL_SAVE_HEADER_VALID = 1,
    REGIONAL_SAVE_HEADER_UNSUPPORTED = 2,
};

// All hash scratch belongs to the caller; no mutable hash global is allocated.
struct RegionalSaveSha256Context
{
    u32 state[8];
    u32 bitCountLow;
    u32 bitCountHigh;
    u8 block[64];
    u32 blockLength;
};

struct RegionalSaveSha256Schedule
{
    u32 words[16];
};

STATIC_ASSERT(sizeof(struct RegionalSaveSha256Context) == 108, RegionalSaveShaContextSize);
STATIC_ASSERT(sizeof(struct RegionalSaveSha256Schedule) == 64, RegionalSaveShaScheduleSize);
STATIC_ASSERT(REGIONAL_SAVE_RESERVE_OFFSET + REGIONAL_SAVE_RESERVE_SIZE == REGIONAL_SAVE_SIZE, RegionalSaveAllocationSize);
STATIC_ASSERT(sizeof(struct Roamer) == REGIONAL_SAVE_DOG_ROAMER_SIZE, RegionalSaveDogRoamerSize);
STATIC_ASSERT(sizeof(struct MomSavingsData) == 8, RegionalSaveMomSavingsSize);
STATIC_ASSERT((REGIONAL_SAVE_DOG_ROAMERS_OFFSET & 3) == 0 && (REGIONAL_SAVE_MOM_SAVINGS_OFFSET & 3) == 0, RegionalSaveTypedAlignment);
STATIC_ASSERT(REGIONAL_SAVE_EVENTS_OFFSET + (REGIONAL_SAVE_CAMPAIGN_EVENT_COUNT + 7) / 8 <= REGIONAL_SAVE_DOG_ROAMERS_OFFSET, RegionalSaveDogEventSeparation);
STATIC_ASSERT(REGIONAL_SAVE_DOG_ROAMERS_OFFSET + REGIONAL_SAVE_DOG_ROAMER_COUNT * REGIONAL_SAVE_DOG_ROAMER_SIZE <= REGIONAL_SAVE_TRAINERS_OFFSET, RegionalSaveDogAllocationBound);
STATIC_ASSERT(REGIONAL_SAVE_DOG_HISTORY_OFFSET + REGIONAL_SAVE_DOG_ROAMER_COUNT * 3 * 2 <= REGIONAL_SAVE_RESERVE_OFFSET, RegionalSaveDogHistoryBound);
STATIC_ASSERT(REGIONAL_SAVE_REMATCH_BIT_OFFSET + REGIONAL_SAVE_REMATCH_COUNT * 3 == REGIONAL_SAVE_REMATCH_STEP_BIT_OFFSET, RegionalSaveRematchAllocation);
STATIC_ASSERT(REGIONAL_SAVE_REMATCH_STEP_BIT_OFFSET + 8 <= REGIONAL_SAVE_TRAINER_COUNT, RegionalSaveRematchStepBound);

u16 RegionalSave_Read16(const u8 *bytes);
u32 RegionalSave_Read32(const u8 *bytes);
void RegionalSave_Write16(u8 *bytes, u16 value);
void RegionalSave_Write32(u8 *bytes, u32 value);
void RegionalSave_InitExtension(u8 *image);
bool8 RegionalSave_InitializeJohto(u8 *image);
bool8 RegionalSave_UpgradeToCampaign(u8 *image);
void RegionalSave_SetGeneration(u8 *image, u32 generation);
u8 RegionalSave_CheckHeader(const u8 *image, u32 generation);
bool8 RegionalSave_FoundationValid(const u8 *image);
u32 RegionalSave_Crc32(const u8 *bytes, u32 length);
u32 RegionalSave_ComputeCrc(const u8 *image);
bool8 RegionalSave_CheckCrc(const u8 *image);
void RegionalSave_Finalize(u8 *image, const u8 digest[32]);

void RegionalSave_Sha256Init(struct RegionalSaveSha256Context *context);
void RegionalSave_Sha256Update(struct RegionalSaveSha256Context *context, struct RegionalSaveSha256Schedule *schedule, const u8 *bytes, u32 length);
void RegionalSave_Sha256Final(struct RegionalSaveSha256Context *context, struct RegionalSaveSha256Schedule *schedule, u8 digest[32]);
void RegionalSave_HashMainInit(struct RegionalSaveSha256Context *context, struct RegionalSaveSha256Schedule *schedule, const u8 *image);
u16 RegionalSave_MainSectorSize(u16 id);
bool8 RegionalSave_HashMainSector(struct RegionalSaveSha256Context *context, struct RegionalSaveSha256Schedule *schedule, u16 id, const u8 *payload, u16 size);

// Bounded buffer codecs. Content1/2 retain their exact legacy meanings;
// content3 adds an explicit regional namespace without changing the layout.
// Live writers must notify the save coordinator before mutation.
bool8 RegionalSave_GetEvent(const u8 *image, u16 region, u16 index, bool8 *value);
bool8 RegionalSave_SetEvent(u8 *image, u16 region, u16 index, bool8 value);
bool8 RegionalSave_GetTrainer(const u8 *image, u16 region, u16 index, bool8 *value);
bool8 RegionalSave_SetTrainer(u8 *image, u16 region, u16 index, bool8 value);
bool8 RegionalSave_GetVar(const u8 *image, u16 region, u16 index, u16 *value);
bool8 RegionalSave_SetVar(u8 *image, u16 region, u16 index, u16 value);
#endif // FIRERED

#endif // GUARD_REGIONAL_SAVE_H

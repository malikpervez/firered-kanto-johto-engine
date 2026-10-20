#ifndef GUARD_JOHTO_CAMPAIGN_H
#define GUARD_JOHTO_CAMPAIGN_H

#include "global.h"

#ifdef FIRERED
#define JOHTO_CAMPAIGN_FLAG_ID_BASE 0x2000
#define JOHTO_CAMPAIGN_FLAG_ID_PAGE_END 0x3000
#define JOHTO_CAMPAIGN_VAR_ID_BASE 0x5000
#define JOHTO_CAMPAIGN_VAR_ID_LAST 0x50EE
#define JOHTO_CAMPAIGN_VAR_ID_PAGE_END 0x5100
#define JOHTO_CAMPAIGN_RAW_FLAG_COUNT 0x980
#define JOHTO_CAMPAIGN_RAW_TRAINER_START 0x500
#define JOHTO_CAMPAIGN_RAW_TRAINER_COUNT 864
#define JOHTO_CAMPAIGN_RAW_VAR_FIRST 0x4010
#define JOHTO_CAMPAIGN_RAW_VAR_LAST 0x40FE

// Encoded IDs are explicit namespace tags, independent of the player's map.
bool8 JohtoCampaign_IsFlagId(u16 id);
bool8 JohtoCampaign_IsVarId(u16 id);
bool8 JohtoCampaign_GetFlag(u16 encodedId);
void JohtoCampaign_SetFlag(u16 encodedId, bool8 value);
u16 *JohtoCampaign_GetVarPointer(u16 encodedId);
void JohtoCampaign_BeforeVarWrite(u16 encodedId);

// Only a raw HnS trainer ID is accepted, never a native FireRed flag ID.
bool8 JohtoCampaign_IsTrainerDefeated(u16 rawId);
void JohtoCampaign_SetTrainerDefeated(u16 rawId);
void JohtoCampaign_ClearTrainerDefeated(u16 rawId);
// Compact rows follow the frozen original40-row HnS rematch table order.
u8 JohtoCampaign_GetRematchReadiness(u16 compactRow);
bool8 JohtoCampaign_SetRematchReadiness(u16 compactRow, u8 readiness);
u8 JohtoCampaign_GetRematchStepCounter(void);
bool8 JohtoCampaign_SetRematchStepCounter(u16 steps);

bool8 JohtoCampaign_IsSeeded(void);
bool8 JohtoCampaign_Initialize(void);
// Seeded live storage views. Callers notify before mutating; getters never do.
struct MomSavingsData *JohtoCampaign_GetMomSavings(void);
struct Roamer *JohtoCampaign_GetDogRoamer(u32 index);
u8 (*JohtoCampaign_GetDogLocationHistory(u32 index))[2];
u8 *JohtoCampaign_GetDogLocation(u32 index);
void Special_JohtoCampaignGetState(void);
void Special_JohtoCampaignInitialize(void);
#endif // FIRERED

#endif // GUARD_JOHTO_CAMPAIGN_H

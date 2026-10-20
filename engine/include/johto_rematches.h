#ifndef GUARD_JOHTO_REMATCHES_H
#define GUARD_JOHTO_REMATCHES_H

#include "global.h"
#include "battle_setup.h"

#ifdef FIRERED
#include "constants/johto_ids.h"
#define JOHTO_REMATCH_ROW_COUNT 40
#define JOHTO_REMATCH_REGISTERED_FLAGS_START JOHTO_FLAG_REGISTERED_JOEY_HNS
extern const struct RematchTrainer gJohtoRematchTable[REMATCH_TABLE_ENTRIES];
s32 JohtoRematch_CompactRow(u16 originalTableId);
bool8 JohtoRematch_IsContext(void);
u8 JohtoRematch_GetReadiness(u16 originalTableId);
void JohtoRematch_SetReadiness(u16 originalTableId, u8 value);
u8 JohtoRematch_GetStepCounter(void);
void JohtoRematch_SetStepCounter(u16 value);
u16 JohtoRematch_GetTrainerId(u16 firstTrainerId);
u16 JohtoRematch_GetLastBeatenTrainerId(u16 firstTrainerId);
bool8 JohtoRematch_HasEnoughBadges(void);
bool32 JohtoRematch_IsRegistered(s32 tableId);
void JohtoRematch_UpdateIfDefeated(s32 tableId);
u16 JohtoRematch_CountMaxPossible(u16 tableId);
u16 JohtoRematch_CountBattledTeams(u16 tableId);
#endif

#endif

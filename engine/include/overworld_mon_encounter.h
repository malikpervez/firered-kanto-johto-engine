#ifndef GUARD_OVERWORLD_MON_ENCOUNTER_H
#define GUARD_OVERWORLD_MON_ENCOUNTER_H

void OwMonEncounter_ClearGone(void);
bool32 OwMonEncounter_IsGone(u8 localId);
void Special_OwMonEncounterPrepare(void);
void Special_OwMonEncounterRemove(void);

#endif // GUARD_OVERWORLD_MON_ENCOUNTER_H

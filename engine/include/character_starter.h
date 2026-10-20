#ifndef GUARD_CHARACTER_STARTER_H
#define GUARD_CHARACTER_STARTER_H

#include "global.h"
struct Pokemon;
bool8 CharacterStarter_IsPikachuCohort(void);
u16 CharacterStarter_GetKantoSpecies(void);
void Special_CharacterStarterSpecies(void);
void Special_CharacterStarterPreflight(void);
bool8 CharacterStarter_TryCreateBlueParty(struct Pokemon *party, u16 trainerNum,
    bool8 firstTrainer, u32 battleTypeFlags, u8 *result);

#endif

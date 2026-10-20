#ifndef GUARD_CHARACTER_STORY_H
#define GUARD_CHARACTER_STORY_H

#include "global.h"
void CharacterStory_NewGame(void);
void CharacterStory_OnObjectSpawn(u8 objectEventId);
bool8 CharacterStory_IsReady(void);
bool8 CharacterStory_HasMetElm(void);
void Special_CharacterStoryAdopt(void);
void Special_CharacterStoryElmProgress(void);
void Special_CharacterStoryPartner(void);
void Special_CharacterStoryTrioReveal(void);

#endif

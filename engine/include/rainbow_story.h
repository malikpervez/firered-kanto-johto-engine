#ifndef GUARD_RAINBOW_STORY_H
#define GUARD_RAINBOW_STORY_H

#include "global.h"

void RainbowStory_NewGame(void);
bool8 RainbowStory_IsReady(void);
bool8 RainbowStory_TryAdopt(void);
u16 RainbowStory_GetReplicaResult(u16 replica);
bool8 RainbowStory_AllReplicasResolved(void);
void Special_RainbowStoryAdopt(void);
void Special_RainbowStoryIsReady(void);
void Special_RainbowStoryAdoptWhirl(void);
void Special_RainbowStoryGetReplicaResult(void);
void Special_RainbowStoryRecordReplicaResult(void);
void Special_RainbowStoryAllReplicasResolved(void);

#endif

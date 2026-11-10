#ifndef GUARD_FRIENDS_STORY_H
#define GUARD_FRIENDS_STORY_H

bool8 FriendsStory_AllocationValid(void);
bool8 FriendsStory_IsReady(void);
bool8 FriendsStory_TryAdopt(void);
void FriendsStory_NewGame(void);
u16 FriendsStory_GetStage(void);
u16 FriendsStory_GetMapScene(void);
bool8 FriendsStory_GetGate(u16 scene);
void FriendsStory_OnMapLoad(void);
void FriendsStory_OnBattleOutcome(u16 trainerId, u32 outcome);
void Special_FriendsStoryAdopt(void);
void Special_FriendsStoryGetStage(void);
void Special_FriendsStoryGetGate(void);
void Special_FriendsStoryGetSeen(void);
void Special_FriendsStoryMarkSeen(void);
void Special_FriendsStoryBegin(void);
void Special_FriendsStoryNeedsIntroduction(void);
void Special_FriendsStoryCanBattle(void);
void Special_FriendsStoryCanFinalBattle(void);
void Special_FriendsStoryGetPendingLoss(void);
void Special_FriendsStoryClearPendingLoss(void);
void Special_FriendsStoryGetInvitation(void);
void Special_FriendsStoryMarkInvitation(void);
void Special_FriendsStoryInvitation(void);
void Special_FriendsStoryCompleteDeparture(void);
void Special_FriendsStoryIsReunionReady(void);

#endif

#ifndef GUARD_FRIENDS_SCENE_H
#define GUARD_FRIENDS_SCENE_H
#ifdef FIRERED
struct ObjectEvent;
struct Sprite;
// Derived field rendering only; native object/collision/options remain intact.
bool8 FriendsScene_HideOverlappingFollower(const struct ObjectEvent *object, const struct Sprite *sprite);
bool8 FriendsScene_ShouldSpawn(u8 localId, u8 mapNum, u8 mapGroup);
void FriendsScene_OnMapLoad(void);
bool32 FriendsScene_GetFramePoint(s16 *x, s16 *y);
void Special_FriendsStoryStage(void);
void Special_FriendsStoryGetActorLocalId(void);
void Special_FriendsStoryFocusSpeaker(void);
void Special_FriendsStoryStep(void);
void Special_FriendsStoryWaitMovement(void);
void FriendsScene_ClearVisitors(void);
u16 FriendsScene_GetMovementFault(void);
void Special_FriendsStoryEndScene(void);
void Special_FriendsStoryPrepareMenu(void);
void Special_FriendsStoryAtFujiHouse(void);
void Special_FriendsStoryReadFujiReturn(void);
void Special_FriendsStoryPrepareFujiWarp(void);
void Special_FriendsStoryConsumeFujiWarp(void);
#endif
#endif

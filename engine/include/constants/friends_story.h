#ifndef GUARD_CONSTANTS_FRIENDS_STORY_H
#define GUARD_CONSTANTS_FRIENDS_STORY_H

// Audited, already allocated native flags. No SaveBlock or regional reserve grows.
#define FRIENDS_STORY_FLAGS_FIRST           0x934
#define FLAG_FRIENDS_STORY_ADOPTED          0x934
#define FRIENDS_STORY_SEEN_FIRST            0x935
#define FRIENDS_STORY_SEEN_LAST             0x94A
#define FRIENDS_STORY_STAGE_FIRST           0x94B
#define FRIENDS_STORY_STAGE_BITS            5
#define FLAG_FRIENDS_FAREWELL_INVITED       0x950
#define FRIENDS_STORY_LOSS_FIRST            0x951
#define FRIENDS_STORY_LOSS_BITS             4
#define FLAG_FRIENDS_REUNION_ARMED          0x955
#define FRIENDS_STORY_UNUSED_FIRST          0x956
#define FRIENDS_STORY_FLAGS_LAST            0x95F
#define FRIENDS_STORY_SCENE_COUNT           22
// The October 19 handoff's seven new scenes, FG-A..FG-G, take the receipts 0x956..0x95C in letter order. Their stage
// numbers follow FG22's, also in letter order: FG-A..FG-G are scenes 23..29, so scene s's receipt is
// FRIENDS_STORY_NEW_SEEN_FIRST + s - 23 (all inside the 5-bit stage field and the flags above). The story order is
// separate (FriendsStory_Order). Only the scenes named here are built; every other receipt stays required-zero.
#define FRIENDS_STORY_NEW_SCENE_FIRST       23
#define FRIENDS_STORY_NEW_SEEN_FIRST        0x956
#define FRIENDS_SCENE_FG_D                  26 // Cianwood beach, receipt 0x959
#define FRIENDS_SCENE_FG_E                  27 // Lake of Rage, receipt 0x95A
#define FRIENDS_SCENE_FG_F                  28 // Ice Path 1F, receipt 0x95B
#define FRIENDS_STORY_STAGE_MAX             28
#define FLAG_FRIENDS_FG_D_SEEN              (FRIENDS_STORY_NEW_SEEN_FIRST + FRIENDS_SCENE_FG_D - FRIENDS_STORY_NEW_SCENE_FIRST)
#define FLAG_FRIENDS_FG_E_SEEN              (FRIENDS_STORY_NEW_SEEN_FIRST + FRIENDS_SCENE_FG_E - FRIENDS_STORY_NEW_SCENE_FIRST)
#define FLAG_FRIENDS_FG_F_SEEN              (FRIENDS_STORY_NEW_SEEN_FIRST + FRIENDS_SCENE_FG_F - FRIENDS_STORY_NEW_SCENE_FIRST)
// Staging beats the scripts and friends_scene.c share (Special_FriendsStoryStage, VAR_0x8005).
#define FRIENDS_FG_E_BEAT_PARTNERS          14 // LB sits down: Jigglypuff and Murkrow appear
#define FRIENDS_FG_F_BEAT_SWINUB_GONE       12 // the Swinub has trotted off
#define FLAG_FRIENDS_ARRIVED_IN_VIRIDIAN    0x935 // FRIENDS_STORY_SEEN_FIRST: scene 1 seen
#define FLAG_FRIENDS_DEPARTED               (FRIENDS_STORY_SEEN_FIRST + 20)
#define FLAG_FRIENDS_REUNION_SEEN           (FRIENDS_STORY_SEEN_FIRST + 21)

// Native trainer defeat flags remain independent of witnessed story scenes.
#define FRIENDS_STORY_TRAINER_FIRST         626
#define FRIENDS_STORY_EARLY_TRAINER_LAST    632
#define FRIENDS_STORY_FINAL_TRAINER_FIRST   633
#define FRIENDS_STORY_TRAINER_LAST          639

#endif

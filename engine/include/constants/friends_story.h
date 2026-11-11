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
// FG-A to FG-G, the October 19 handoff's new scenes, are scenes 23-29, with the handoff's receipts 0x956-0x95C
// (scene 23 + n has receipt 0x956 + n). They play beside the stage, which stays 0-22 and never holds their numbers:
// each opens while the stage is at the placement next to it, and retires when the stage moves past.
#define FRIENDS_STORY_EXTRA_SCENE_FIRST     23
#define FRIENDS_STORY_EXTRA_SCENE_LAST      29
#define FRIENDS_STORY_EXTRA_SEEN_FIRST      0x956
#define FRIENDS_STORY_UNUSED_FIRST          0x95D
#define FRIENDS_STORY_FLAGS_LAST            0x95F
#define FRIENDS_STORY_SCENE_COUNT           22
#define FLAG_FRIENDS_ARRIVED_IN_VIRIDIAN    0x935 // FRIENDS_STORY_SEEN_FIRST: scene 1 seen
#define FLAG_FRIENDS_FG11_SEEN              (FRIENDS_STORY_SEEN_FIRST + 10) // FG11, the television in the water
#define FLAG_FRIENDS_FG_A_SEEN              0x956 // scene 23, FG-A Tim finds the resort
#define FLAG_FRIENDS_FG_D_SEEN              0x959 // scene 26, FG-D Someone louder than Jon
#define FLAG_FRIENDS_FG_E_SEEN              0x95A // scene 27, FG-E The lake that was told to be angry
#define FLAG_FRIENDS_DEPARTED               (FRIENDS_STORY_SEEN_FIRST + 20)
#define FLAG_FRIENDS_FG_B_SEEN              0x957 // scene 24, FG-B The road nobody paved
#define FLAG_FRIENDS_REUNION_SEEN           (FRIENDS_STORY_SEEN_FIRST + 21)
#define FLAG_FRIENDS_FG_C_SEEN              0x958 // scene 25, FG-C The tower that sways

// The stage's five bits by name, so a replay test can start the Friends at a placement (stage 11: 1, 2 and 8).
#define FLAG_FRIENDS_STAGE_1                (FRIENDS_STORY_STAGE_FIRST + 0)
#define FLAG_FRIENDS_STAGE_2                (FRIENDS_STORY_STAGE_FIRST + 1)
#define FLAG_FRIENDS_STAGE_4                (FRIENDS_STORY_STAGE_FIRST + 2)
#define FLAG_FRIENDS_STAGE_8                (FRIENDS_STORY_STAGE_FIRST + 3)
#define FLAG_FRIENDS_STAGE_16               (FRIENDS_STORY_STAGE_FIRST + 4)

// The stage's five bits by name, so a replay test can start the Friends at a placement (stage 11: 1, 2 and 8).
#define FLAG_FRIENDS_STAGE_1                (FRIENDS_STORY_STAGE_FIRST + 0)
#define FLAG_FRIENDS_STAGE_2                (FRIENDS_STORY_STAGE_FIRST + 1)
#define FLAG_FRIENDS_STAGE_4                (FRIENDS_STORY_STAGE_FIRST + 2)
#define FLAG_FRIENDS_STAGE_8                (FRIENDS_STORY_STAGE_FIRST + 3)
#define FLAG_FRIENDS_STAGE_16               (FRIENDS_STORY_STAGE_FIRST + 4)

// The stage's five bits by name, so a replay test can start the Friends at a placement (stage 11: 1, 2 and 8).
#define FLAG_FRIENDS_STAGE_1                (FRIENDS_STORY_STAGE_FIRST + 0)
#define FLAG_FRIENDS_STAGE_2                (FRIENDS_STORY_STAGE_FIRST + 1)
#define FLAG_FRIENDS_STAGE_4                (FRIENDS_STORY_STAGE_FIRST + 2)
#define FLAG_FRIENDS_STAGE_8                (FRIENDS_STORY_STAGE_FIRST + 3)
#define FLAG_FRIENDS_STAGE_16               (FRIENDS_STORY_STAGE_FIRST + 4)

// The stage's five bits by name, so a replay test can start the Friends at a placement (stage 11: 1, 2 and 8).
#define FLAG_FRIENDS_STAGE_1                (FRIENDS_STORY_STAGE_FIRST + 0)
#define FLAG_FRIENDS_STAGE_2                (FRIENDS_STORY_STAGE_FIRST + 1)
#define FLAG_FRIENDS_STAGE_4                (FRIENDS_STORY_STAGE_FIRST + 2)
#define FLAG_FRIENDS_STAGE_8                (FRIENDS_STORY_STAGE_FIRST + 3)
#define FLAG_FRIENDS_STAGE_16               (FRIENDS_STORY_STAGE_FIRST + 4)

// Native trainer defeat flags remain independent of witnessed story scenes.
#define FRIENDS_STORY_TRAINER_FIRST         626
#define FRIENDS_STORY_EARLY_TRAINER_LAST    632
#define FRIENDS_STORY_FINAL_TRAINER_FIRST   633
#define FRIENDS_STORY_TRAINER_LAST          639

#endif

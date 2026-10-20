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
#define FLAG_FRIENDS_DEPARTED               (FRIENDS_STORY_SEEN_FIRST + 20)
#define FLAG_FRIENDS_REUNION_SEEN           (FRIENDS_STORY_SEEN_FIRST + 21)

// Native trainer defeat flags remain independent of witnessed story scenes.
#define FRIENDS_STORY_TRAINER_FIRST         626
#define FRIENDS_STORY_EARLY_TRAINER_LAST    632
#define FRIENDS_STORY_FINAL_TRAINER_FIRST   633
#define FRIENDS_STORY_TRAINER_LAST          639

#endif

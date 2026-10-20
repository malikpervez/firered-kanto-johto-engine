#ifndef GUARD_CONSTANTS_FLAGS_H
#define GUARD_CONSTANTS_FLAGS_H

#include "constants/trainers.h"
#include "constants/opponents.h"
#include "constants/rematches.h"


// Temporary Flags
// These temporary flags are are cleared every time a map is loaded. They are used
// for things like shortening an NPCs introduction text if the player already spoke
// to them once.
#define TEMP_FLAGS_START 0x0
#define FLAG_TEMP_1      (TEMP_FLAGS_START + 0x1)
#define FLAG_TEMP_2      (TEMP_FLAGS_START + 0x2)
#define FLAG_TEMP_3      (TEMP_FLAGS_START + 0x3)
#define FLAG_TEMP_4      (TEMP_FLAGS_START + 0x4)
#define FLAG_TEMP_5      (TEMP_FLAGS_START + 0x5)  // Unused Flag
#define FLAG_TEMP_6      (TEMP_FLAGS_START + 0x6)  // Unused Flag
#define FLAG_TEMP_7      (TEMP_FLAGS_START + 0x7)  // Unused Flag
#define FLAG_TEMP_8      (TEMP_FLAGS_START + 0x8)  // Unused Flag
#define FLAG_TEMP_9      (TEMP_FLAGS_START + 0x9)  // Unused Flag
#define FLAG_TEMP_A      (TEMP_FLAGS_START + 0xA)  // Unused Flag
#define FLAG_TEMP_B      (TEMP_FLAGS_START + 0xB)  // Unused Flag
#define FLAG_TEMP_C      (TEMP_FLAGS_START + 0xC)  // Unused Flag
#define FLAG_TEMP_D      (TEMP_FLAGS_START + 0xD)  // Unused Flag
#define FLAG_TEMP_E      (TEMP_FLAGS_START + 0xE)  // When set, follower pokemon won't be spawned
#define FLAG_TEMP_F      (TEMP_FLAGS_START + 0xF)  // Unused Flag
#define FLAG_TEMP_10     (TEMP_FLAGS_START + 0x10) // Unused Flag
#define FLAG_TEMP_11     (TEMP_FLAGS_START + 0x11)
#define FLAG_TEMP_12     (TEMP_FLAGS_START + 0x12)
#define FLAG_TEMP_13     (TEMP_FLAGS_START + 0x13)
#define FLAG_TEMP_14     (TEMP_FLAGS_START + 0x14)
#define FLAG_TEMP_15     (TEMP_FLAGS_START + 0x15)
#define FLAG_TEMP_16     (TEMP_FLAGS_START + 0x16)
#define FLAG_TEMP_17     (TEMP_FLAGS_START + 0x17)
#define FLAG_TEMP_18     (TEMP_FLAGS_START + 0x18)
#define FLAG_TEMP_19     (TEMP_FLAGS_START + 0x19)
#define FLAG_TEMP_1A     (TEMP_FLAGS_START + 0x1A)
#define FLAG_TEMP_1B     (TEMP_FLAGS_START + 0x1B)
#define FLAG_TEMP_1C     (TEMP_FLAGS_START + 0x1C)
#define FLAG_TEMP_1D     (TEMP_FLAGS_START + 0x1D)
#define FLAG_TEMP_1E     (TEMP_FLAGS_START + 0x1E)
#define FLAG_TEMP_1F     (TEMP_FLAGS_START + 0x1F)
#define TEMP_FLAGS_END   FLAG_TEMP_1F
#define NUM_TEMP_FLAGS   (TEMP_FLAGS_END - TEMP_FLAGS_START + 1)
#define FLAG_SYS_GBS_ENABLED    0x20 // GBS Flag
#define FLAG_ITEM_PLAYER_ROOM_GB_PLAYER 0x21 //GBS Flag 2


#include "constants/flags_frlg.h"


// Several engine systems predate multi-region badge counts and only handle 8 badges
// (badge-count-indexed tables like sBadgeLevel/sWhiteOutBadgeMoney, gBadgeFlags, etc).
// HnS has 16 badges, so NUM_BADGES cannot be used to size or index any of those - use
// this clamped count instead, or they read past the end of their tables.
#define NUM_BADGES_CAPPED                       (NUM_BADGES > 8 ? 8 : NUM_BADGES)

// Engine-wide flags for options/challenge settings (shared across all builds).
// Fixed 32-flag block; not cleared by ClearDailyFlags or ClearTempFieldEventData.
//
// This address is PINNED and must never change. It used to be (BUILD_FLAGS_END + 1),
// which meant every daily flag added to any build slid this whole block up by one and
// silently renumbered it. Flag IDs are absolute bit indices baked into save files, so
// that renumbering re-pointed live save data at the wrong flags (e.g. a save's
// "Exp. Share on" bit became FLAG_LIMIT_TO_50, capping the party at level 50).
//
// Every build's flags must stay below this address. Current headroom below 0x960:
// HnS ends at 0x91A (69 free), FRLG at 0x8FF (96 free), Emerald at 0x95F (0 free).
// If a build ever needs to grow past it, raise the pin AND bump SAVE_VERSION with a
// migration - do not let it float again.
#define ENGINE_FLAGS_START                      0x960
#define NUM_ENGINE_FLAGS                        32
#define FLAG_EVEN_FASTER_JOY                    (ENGINE_FLAGS_START + 0)
#define FLAG_MINTS_DISABLED                     (ENGINE_FLAGS_START + 1)
#define FLAG_RECEIVED_FIRST_BALLS               (ENGINE_FLAGS_START + 2)
#define FLAG_START_NUZLOCKE                     (ENGINE_FLAGS_START + 3)
#define FLAG_END_NUZLOCKE                       (ENGINE_FLAGS_START + 4)
#define FLAG_DISABLE_ENCOUNTERS                 (ENGINE_FLAGS_START + 5)
#define FLAG_DISABLE_TRAINERS                   (ENGINE_FLAGS_START + 6)
#define FLAG_LIMIT_TO_50                        (ENGINE_FLAGS_START + 7)
#define FLAG_EXP_SHARE_ENABLED                  (ENGINE_FLAGS_START + 8)
#define FLAG_SMART_WILD_AI                      (ENGINE_FLAGS_START + 9)
#define FLAG_NO_WILD_RUNNING                      (ENGINE_FLAGS_START + 10)
#define FLAG_NO_WILD_CATCHING                      (ENGINE_FLAGS_START + 11)
#define FLAG_DISABLE_EXP_GAIN                      (ENGINE_FLAGS_START + 12)
#define ENGINE_FLAGS_END                        (ENGINE_FLAGS_START + NUM_ENGINE_FLAGS - 1)

#define FLAGS_COUNT (ENGINE_FLAGS_END + 1)

#if TESTING
#define TESTING_FLAGS_START                     0x5000
#define TESTING_FLAG_SLEEP_CLAUSE               (TESTING_FLAGS_START + 0x0)
#define TESTING_FLAG_INVERSE_BATTLE             (TESTING_FLAGS_START + 0x1)
#define TESTING_FLAG_TRAINER_SLIDES             (TESTING_FLAGS_START + 0x2)
#define TESTING_FLAG_UNUSED_3                   (TESTING_FLAGS_START + 0x3)
#define TESTING_FLAG_UNUSED_4                   (TESTING_FLAGS_START + 0x4)
#define TESTING_FLAG_UNUSED_5                   (TESTING_FLAGS_START + 0x5)
#define TESTING_FLAG_UNUSED_6                   (TESTING_FLAGS_START + 0x6)
#define TESTING_FLAG_UNUSED_7                   (TESTING_FLAGS_START + 0x7)
#endif // TESTING


#endif // GUARD_CONSTANTS_FLAGS_H

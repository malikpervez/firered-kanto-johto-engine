#ifndef GUARD_CONSTANTS_CHARACTER_STORY_H
#define GUARD_CONSTANTS_CHARACTER_STORY_H

#ifdef FIRERED
// Audited native SaveBlock1 bits, independent of the older Rainbow cohort.
#define FLAG_CHARACTER_STORY_ADOPTED     0x920
#define FLAG_ST01_NEW_COHORT             0x921
#define FLAG_ST02_GIVEN                  0x922
#define FLAG_ST03_GIVEN                  0x923
#define FLAG_ST04_GIVEN                  0x924
#define FLAG_ST04_INTRO_SEEN             0x925
#define FLAG_JT01_SEEN                   0x926
#define FLAG_JT02_SEEN                   0x927
#define FLAG_JT03_SEEN                   0x928
#define FLAG_JT04_SEEN                   0x929
#define FLAG_BL01_SEEN                   0x92A
#define FLAG_BL02_SEEN                   0x92B
#define FLAG_BL03_SEEN                   0x92C
#define FLAG_SV01_SEEN                   0x92D
#define FLAG_SV02_SEEN                   0x92E
#define FLAG_SV03_SEEN                   0x92F
#define FLAG_ST02_CARE_DONE              0x930
#define FLAG_ST03_SHELTER_DONE           0x931
#define FLAG_ST04_RESCUE_DONE            0x932
#define FLAG_ST01_GIVEN                  0x933
#define CHARACTER_STORY_FLAGS_FIRST     0x920
#define CHARACTER_STORY_FLAGS_LAST      0x93F
#define CHARACTER_STORY_UNUSED_FIRST    0x934
#endif

#endif

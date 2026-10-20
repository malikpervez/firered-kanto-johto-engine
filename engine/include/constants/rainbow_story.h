#ifndef GUARD_CONSTANTS_RAINBOW_STORY_H
#define GUARD_CONSTANTS_RAINBOW_STORY_H

// FireRed-only story receipts in audited, previously unused native flags.
// These are existing SaveBlock1 bits, not Johto IDs or new save storage.
#define FLAG_RB_OPENING_SEEN             0x900
#define FLAG_RB_NAO_INTRODUCED           0x901
#define FLAG_RB_FUJI_SCENE_SEEN          0x902
#define FLAG_RB_NOTEBOOK_SCENE_SEEN      0x903
#define FLAG_RB_ECRUTEAK_TRUTH_SEEN      0x904
#define FLAG_RB_RECORDING_STOPPED        0x905
#define FLAG_RB_WELCOME_SEEN             0x906
#define FLAG_RB_LETTER_READ              0x907
#define FLAG_RB_EPILOGUE_SEEN            0x908
#define FLAG_MW01_SEEN                   0x909
#define FLAG_MW02_SEEN                   0x90A
#define FLAG_MW03_SEEN                   0x90B
#define FLAG_MW04_SEEN                   0x90C
#define FLAG_MW05_SEEN                   0x90D
#define FLAG_MW06_SEEN                   0x90E
#define FLAG_MW07_SEEN                   0x90F
#define FLAG_MW09_SEEN                   0x910
#define FLAG_LG_ATTACK_SEEN              0x911
#define FLAG_LG_ARTICUNO_DEFEATED        0x912
#define FLAG_LG_ARTICUNO_CAUGHT          0x913
#define FLAG_LG_ZAPDOS_DEFEATED          0x914
#define FLAG_LG_ZAPDOS_CAUGHT            0x915
#define FLAG_LG_MOLTRES_DEFEATED         0x916
#define FLAG_LG_MOLTRES_CAUGHT           0x917
#define FLAG_LG_LINKS_OFF_SEEN           0x918
#define FLAG_LG_FINAL_RESOLVED           0x919
#define FLAG_LG_LEGACY_EXEMPT            0x91A
#define FLAG_RAINBOW_STORY_ADOPTED       0x91B
#define FLAG_RB_FRESH_COHORT             0x91C
#define FLAG_LG_LEGACY_CLASSIFIED        0x91D
// 0x91E and 0x91F remain unallocated and must remain zero.
#define RAINBOW_STORY_FLAGS_FIRST        0x900
#define RAINBOW_STORY_FLAGS_LAST         0x91F
#define LG_REPLICA_ARTICUNO              0
#define LG_REPLICA_ZAPDOS                1
#define LG_REPLICA_MOLTRES               2
#define LG_REPLICA_COUNT                 3
#define LG_REPLICA_UNRESOLVED            0
#define LG_REPLICA_DEFEATED              1
#define LG_REPLICA_CAUGHT                2

#endif

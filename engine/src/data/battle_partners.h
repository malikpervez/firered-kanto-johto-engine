//
// DO NOT MODIFY THIS FILE! It is auto-generated from src/data/battle_partners.party
//
// If you want to modify this file see expansion PR #7154
//

#line 1 "src/data/battle_partners.party"

#line 1
    [DIFFICULTY_NORMAL][PARTNER_NONE] =
    {
#line 3
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
#line 4
        .trainerPic = TRAINER_PIC_FRONT_BRENDAN,
#line 5
        .gender = TRAINER_GENDER_MALE,
#line 6
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
#line 7
        .trainerBackPic = TRAINER_PIC_BACK_BRENDAN,
        .partySize = 0,
        .party = (const struct TrainerMon[])
        {
        },
    },
#line 9
    [DIFFICULTY_NORMAL][PARTNER_STEVEN] =
    {
#line 10
        .trainerName = _("STEVEN"),
#line 11
        .trainerClass = TRAINER_CLASS_RIVAL,
#line 12
        .trainerPic = TRAINER_PIC_FRONT_STEVEN,
#line 13
        .gender = TRAINER_GENDER_MALE,
#line 14
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
#line 16
        .aiFlags = AI_FLAG_BASIC_TRAINER,
#line 15
        .trainerBackPic = TRAINER_PIC_BACK_STEVEN,
        .partySize = 3,
        .party = (const struct TrainerMon[])
        {
            {
#line 18
            .species = SPECIES_METANG,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 22
            .ev = TRAINER_PARTY_EVS(0, 252, 252, 0, 6, 0),
#line 21
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 20
            .lvl = 42,
            .ball = POKEBALL_COUNT,
#line 19
            .nature = NATURE_BRAVE,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 23
                MOVE_LIGHT_SCREEN,
                MOVE_PSYCHIC,
                MOVE_REFLECT,
                MOVE_METAL_CLAW,
            },
            },
            {
#line 28
            .species = SPECIES_SKARMORY,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 32
            .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 6, 252),
#line 31
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 30
            .lvl = 43,
            .ball = POKEBALL_COUNT,
#line 29
            .nature = NATURE_IMPISH,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 33
                MOVE_TOXIC,
                MOVE_AERIAL_ACE,
                MOVE_PROTECT,
                MOVE_STEEL_WING,
            },
            },
            {
#line 38
            .species = SPECIES_AGGRON,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 42
            .ev = TRAINER_PARTY_EVS(0, 252, 0, 0, 252, 6),
#line 41
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 40
            .lvl = 44,
            .ball = POKEBALL_COUNT,
#line 39
            .nature = NATURE_ADAMANT,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 43
                MOVE_THUNDER,
                MOVE_PROTECT,
                MOVE_SOLAR_BEAM,
                MOVE_DRAGON_CLAW,
            },
            },
        },
    },
#line 48
    [DIFFICULTY_NORMAL][PARTNER_LANCE_HNS] =
    {
#line 49
        .trainerName = _("LANCE"),
#line 50
        .trainerClass = TRAINER_CLASS_CHAMPION_HNS,
#line 51
        .trainerPic = TRAINER_PIC_FRONT_CHAMPION_LANCE_HNS,
#line 52
        .gender = TRAINER_GENDER_MALE,
#line 53
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_HG_CHAMPION,
#line 55
        .aiFlags = AI_FLAG_BASIC_TRAINER,
#line 54
        .trainerBackPic = TRAINER_PIC_BACK_LANCE_HNS,
        .partySize = 3,
        .party = (const struct TrainerMon[])
        {
            {
#line 57
            .species = SPECIES_DRAGONITE,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 61
            .ev = TRAINER_PARTY_EVS(0, 252, 252, 0, 0, 6),
#line 60
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 59
            .lvl = 42,
            .ball = POKEBALL_COUNT,
#line 58
            .nature = NATURE_ADAMANT,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 62
                MOVE_HYPER_BEAM,
                MOVE_THUNDER,
                MOVE_SAFEGUARD,
                MOVE_OUTRAGE,
            },
            },
            {
#line 67
            .species = SPECIES_DRAGONAIR,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 71
            .ev = TRAINER_PARTY_EVS(252, 0, 0, 252, 0, 6),
#line 70
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 69
            .lvl = 35,
            .ball = POKEBALL_COUNT,
#line 68
            .nature = NATURE_ADAMANT,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 72
                MOVE_BLIZZARD,
                MOVE_THUNDER_WAVE,
                MOVE_FLAMETHROWER,
                MOVE_QUICK_ATTACK,
            },
            },
            {
#line 77
            .species = SPECIES_CHARIZARD,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 81
            .ev = TRAINER_PARTY_EVS(0, 252, 0, 6, 0, 252),
#line 80
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 79
            .lvl = 36,
            .ball = POKEBALL_COUNT,
#line 78
            .nature = NATURE_ADAMANT,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 82
                MOVE_FLAMETHROWER,
                MOVE_WING_ATTACK,
                MOVE_DOUBLE_TEAM,
                MOVE_STEEL_WING,
            },
            },
        },
    },
#line 87
    [DIFFICULTY_NORMAL][PARTNER_SILVER_MEGANIUM_HNS] =
    {
#line 88
        .trainerName = _("{B_RIVAL_NAME}"),
#line 89
        .trainerClass = TRAINER_CLASS_RIVAL_HNS,
#line 90
        .trainerPic = TRAINER_PIC_FRONT_SILVER_HNS,
#line 91
        .gender = TRAINER_GENDER_MALE,
#line 92
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SILVER,
#line 94
        .aiFlags = AI_FLAG_BASIC_TRAINER,
#line 93
        .trainerBackPic = TRAINER_PIC_BACK_SILVER_HNS,
        .partySize = 3,
        .party = (const struct TrainerMon[])
        {
            {
#line 96
            .species = SPECIES_MEGANIUM,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 96
            .heldItem = ITEM_MIRACLE_SEED,
#line 98
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 97
            .lvl = 60,
            .ball = POKEBALL_COUNT,
            .nature = NATURE_HARDY,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 99
                MOVE_REFLECT,
                MOVE_GIGA_DRAIN,
                MOVE_SOLAR_BEAM,
                MOVE_BODY_SLAM,
            },
            },
            {
#line 104
            .species = SPECIES_CROBAT,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 104
            .heldItem = ITEM_LEFTOVERS,
#line 106
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 105
            .lvl = 58,
            .ball = POKEBALL_COUNT,
            .nature = NATURE_HARDY,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 107
                MOVE_TOXIC,
                MOVE_DOUBLE_TEAM,
                MOVE_CONFUSE_RAY,
                MOVE_WING_ATTACK,
            },
            },
            {
#line 112
            .species = SPECIES_GENGAR,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 114
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 113
            .lvl = 56,
            .ball = POKEBALL_COUNT,
            .nature = NATURE_HARDY,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 115
                MOVE_SHADOW_BALL,
                MOVE_SLUDGE_BOMB,
                MOVE_THUNDERBOLT,
                MOVE_HYPNOSIS,
            },
            },
        },
    },
#line 120
    [DIFFICULTY_NORMAL][PARTNER_SILVER_TYPHLOSION_HNS] =
    {
#line 121
        .trainerName = _("{B_RIVAL_NAME}"),
#line 122
        .trainerClass = TRAINER_CLASS_RIVAL_HNS,
#line 123
        .trainerPic = TRAINER_PIC_FRONT_SILVER_HNS,
#line 124
        .gender = TRAINER_GENDER_MALE,
#line 125
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SILVER,
#line 127
        .aiFlags = AI_FLAG_BASIC_TRAINER,
#line 126
        .trainerBackPic = TRAINER_PIC_BACK_SILVER_HNS,
        .partySize = 3,
        .party = (const struct TrainerMon[])
        {
            {
#line 129
            .species = SPECIES_TYPHLOSION,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 129
            .heldItem = ITEM_CHARCOAL,
#line 131
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 130
            .lvl = 60,
            .ball = POKEBALL_COUNT,
            .nature = NATURE_HARDY,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 132
                MOVE_FIRE_BLAST,
                MOVE_EARTHQUAKE,
                MOVE_IRON_TAIL,
                MOVE_THUNDER_PUNCH,
            },
            },
            {
#line 137
            .species = SPECIES_CROBAT,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 137
            .heldItem = ITEM_LEFTOVERS,
#line 139
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 138
            .lvl = 58,
            .ball = POKEBALL_COUNT,
            .nature = NATURE_HARDY,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 140
                MOVE_TOXIC,
                MOVE_DOUBLE_TEAM,
                MOVE_CONFUSE_RAY,
                MOVE_WING_ATTACK,
            },
            },
            {
#line 145
            .species = SPECIES_GENGAR,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 147
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 146
            .lvl = 56,
            .ball = POKEBALL_COUNT,
            .nature = NATURE_HARDY,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 148
                MOVE_SHADOW_BALL,
                MOVE_SLUDGE_BOMB,
                MOVE_THUNDERBOLT,
                MOVE_HYPNOSIS,
            },
            },
        },
    },
#line 153
    [DIFFICULTY_NORMAL][PARTNER_SILVER_FERALIGATR_HNS] =
    {
#line 154
        .trainerName = _("{B_RIVAL_NAME}"),
#line 155
        .trainerClass = TRAINER_CLASS_RIVAL_HNS,
#line 156
        .trainerPic = TRAINER_PIC_FRONT_SILVER_HNS,
#line 157
        .gender = TRAINER_GENDER_MALE,
#line 158
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_SILVER,
#line 160
        .aiFlags = AI_FLAG_BASIC_TRAINER,
#line 159
        .trainerBackPic = TRAINER_PIC_BACK_SILVER_HNS,
        .partySize = 3,
        .party = (const struct TrainerMon[])
        {
            {
#line 162
            .species = SPECIES_FERALIGATR,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 162
            .heldItem = ITEM_SCOPE_LENS,
#line 164
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 163
            .lvl = 60,
            .ball = POKEBALL_COUNT,
            .nature = NATURE_HARDY,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 165
                MOVE_ICE_BEAM,
                MOVE_SURF,
                MOVE_SLASH,
                MOVE_EARTHQUAKE,
            },
            },
            {
#line 170
            .species = SPECIES_CROBAT,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 170
            .heldItem = ITEM_LEFTOVERS,
#line 172
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 171
            .lvl = 58,
            .ball = POKEBALL_COUNT,
            .nature = NATURE_HARDY,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 173
                MOVE_TOXIC,
                MOVE_DOUBLE_TEAM,
                MOVE_CONFUSE_RAY,
                MOVE_WING_ATTACK,
            },
            },
            {
#line 178
            .species = SPECIES_GENGAR,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 180
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 179
            .lvl = 56,
            .ball = POKEBALL_COUNT,
            .nature = NATURE_HARDY,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 181
                MOVE_SHADOW_BALL,
                MOVE_SLUDGE_BOMB,
                MOVE_THUNDERBOLT,
                MOVE_HYPNOSIS,
            },
            },
        },
    },
#line 186
    [DIFFICULTY_NORMAL][PARTNER_DUMMY] =
    {
#line 188
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
#line 189
        .trainerPic = TRAINER_PIC_FRONT_BRENDAN,
#line 190
        .gender = TRAINER_GENDER_MALE,
#line 191
        .encounterMusic = TRAINER_ENCOUNTER_MUSIC_MALE,
#line 192
        .trainerBackPic = TRAINER_PIC_BACK_BRENDAN,
#line 193
        .partySize = 0,
        .poolSize = 1,
        .party = (const struct TrainerMon[])
        {
            {
#line 195
            .species = SPECIES_WYNAUT,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 196
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 196
            .lvl = 100,
            .ball = POKEBALL_COUNT,
            .nature = NATURE_HARDY,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            },
        },
    },

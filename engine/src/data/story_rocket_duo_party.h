// Shared across difficulties; ordinary native Pokémon/moves/animation pipeline.
static const struct TrainerMon sStoryJessieParty[] =
{
    {
        .species = SPECIES_EKANS,
        .lvl = 25,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_WRAP, MOVE_POISON_STING, MOVE_BITE, MOVE_GLARE },
    },
};
static const struct TrainerMon sStoryJamesParty[] =
{
    {
        .species = SPECIES_KOFFING,
        .lvl = 25,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_TACKLE, MOVE_SMOG, MOVE_SMOKESCREEN, MOVE_SLUDGE },
    },
};

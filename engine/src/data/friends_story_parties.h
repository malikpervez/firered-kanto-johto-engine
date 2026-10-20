#ifdef FIRERED
// Fixed novice/late teams. Explicit moves come from this build's GEN_7
// native level-up table at or below the declared level; no adaptive scaling.
static const struct TrainerMon sFriendsBrianEarlyParty[] =
{
    {
        .species = SPECIES_RATTATA,
        .lvl = 6,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_TACKLE, MOVE_TAIL_WHIP, MOVE_QUICK_ATTACK, MOVE_NONE },
    },
};
static const struct TrainerMon sFriendsJonEarlyParty[] =
{
    {
        .species = SPECIES_MANKEY,
        .lvl = 12,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_SCRATCH, MOVE_LOW_KICK, MOVE_FOCUS_ENERGY, MOVE_KARATE_CHOP },
    },
};
static const struct TrainerMon sFriendsNickEarlyParty[] =
{
    {
        .species = SPECIES_POLIWAG,
        .lvl = 20,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_WATER_GUN, MOVE_HYPNOSIS, MOVE_DOUBLE_SLAP, MOVE_RAIN_DANCE },
    },
};
static const struct TrainerMon sFriendsLbEarlyParty[] =
{
    {
        .species = SPECIES_JIGGLYPUFF,
        .lvl = 20,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_SING, MOVE_POUND, MOVE_DISARMING_VOICE, MOVE_DISABLE },
    },
};
static const struct TrainerMon sFriendsXEarlyParty[] =
{
    {
        .species = SPECIES_ODDISH,
        .lvl = 27,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_SLEEP_POWDER, MOVE_ACID, MOVE_MEGA_DRAIN, MOVE_MOONLIGHT },
    },
    {
        .species = SPECIES_PARAS,
        .lvl = 27,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_SPORE, MOVE_ABSORB, MOVE_FURY_CUTTER, MOVE_SLASH },
    },
};
static const struct TrainerMon sFriendsTimEarlyParty[] =
{
    {
        .species = SPECIES_SPEAROW,
        .lvl = 32,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_AERIAL_ACE, MOVE_PURSUIT, MOVE_FURY_ATTACK, MOVE_ROOST },
    },
    {
        .species = SPECIES_KRABBY,
        .lvl = 32,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_BUBBLE_BEAM, MOVE_METAL_CLAW, MOVE_STOMP, MOVE_PROTECT },
    },
};
static const struct TrainerMon sFriendsHamEarlyParty[] =
{
    {
        .species = SPECIES_PSYDUCK,
        .lvl = 35,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_WATER_GUN, MOVE_ZEN_HEADBUTT, MOVE_DISABLE, MOVE_AQUA_TAIL },
    },
    {
        .species = SPECIES_SENTRET,
        .lvl = 35,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_QUICK_ATTACK, MOVE_SLAM, MOVE_REST, MOVE_SUCKER_PUNCH },
    },
};
static const struct TrainerMon sFriendsBrianFinalParty[] =
{
    {
        .species = SPECIES_RATICATE,
        .lvl = 55,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_HYPER_FANG, MOVE_CRUNCH, MOVE_QUICK_ATTACK, MOVE_SUPER_FANG },
    },
    {
        .species = SPECIES_SLOWBRO,
        .lvl = 56,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_WATER_PULSE, MOVE_PSYCHIC, MOVE_SLACK_OFF, MOVE_AMNESIA },
    },
};
static const struct TrainerMon sFriendsXFinalParty[] =
{
    {
        .species = SPECIES_BELLOSSOM,
        .lvl = 56,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_QUIVER_DANCE, MOVE_GIGA_DRAIN, MOVE_MOONBLAST, MOVE_MOONLIGHT },
    },
    {
        .species = SPECIES_PARASECT,
        .lvl = 56,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_FURY_CUTTER, MOVE_SPORE, MOVE_SLASH, MOVE_GIGA_DRAIN },
    },
};
static const struct TrainerMon sFriendsTimFinalParty[] =
{
    {
        .species = SPECIES_FEAROW,
        .lvl = 56,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_DRILL_PECK, MOVE_DRILL_RUN, MOVE_ROOST, MOVE_ASSURANCE },
    },
    {
        .species = SPECIES_KINGLER,
        .lvl = 57,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_CRABHAMMER, MOVE_METAL_CLAW, MOVE_STOMP, MOVE_PROTECT },
    },
};
static const struct TrainerMon sFriendsLbFinalParty[] =
{
    {
        .species = SPECIES_WIGGLYTUFF,
        .lvl = 56,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_HYPER_VOICE, MOVE_PLAY_ROUGH, MOVE_SING, MOVE_DISABLE },
    },
    {
        .species = SPECIES_MURKROW,
        .lvl = 56,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_WING_ATTACK, MOVE_FOUL_PLAY, MOVE_TAUNT, MOVE_SUCKER_PUNCH },
    },
};
static const struct TrainerMon sFriendsNickFinalParty[] =
{
    {
        .species = SPECIES_POLIWHIRL,
        .lvl = 56,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_HYDRO_PUMP, MOVE_BODY_SLAM, MOVE_HYPNOSIS, MOVE_MUD_BOMB },
    },
    {
        .species = SPECIES_GRAVELER,
        .lvl = 57,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_EARTHQUAKE, MOVE_ROCK_BLAST, MOVE_STEALTH_ROCK, MOVE_ROCK_POLISH },
    },
};
static const struct TrainerMon sFriendsJonFinalParty[] =
{
    {
        .species = SPECIES_PRIMEAPE,
        .lvl = 57,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_CLOSE_COMBAT, MOVE_ASSURANCE, MOVE_FOCUS_ENERGY, MOVE_STOMPING_TANTRUM },
    },
    {
        .species = SPECIES_NOCTOWL,
        .lvl = 56,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_AIR_SLASH, MOVE_EXTRASENSORY, MOVE_ROOST, MOVE_HYPNOSIS },
    },
};
static const struct TrainerMon sFriendsHamFinalParty[] =
{
    {
        .species = SPECIES_GOLDUCK,
        .lvl = 56,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_HYDRO_PUMP, MOVE_AQUA_JET, MOVE_ZEN_HEADBUTT, MOVE_DISABLE },
    },
    {
        .species = SPECIES_FURRET,
        .lvl = 55,
        .iv = TRAINER_PARTY_IVS(0, 0, 0, 0, 0, 0),
        .nature = NATURE_HARDY,
        .gender = TRAINER_MON_RANDOM_GENDER,
        .ball = POKEBALL_COUNT,
        .moves = { MOVE_SLAM, MOVE_SUCKER_PUNCH, MOVE_PLAY_ROUGH, MOVE_COIL },
    },
};
#endif

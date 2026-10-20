#include "global.h"
#include "character_starter.h"
#include "character_story.h"
#include "challenge_menu.h"
#include "randomizer.h"
#include "battle.h"
#include "battle_main.h"
#include "data.h"
#include "event_data.h"
#include "pokemon.h"
#include "script.h"
#include "starter_choose.h"
#include "constants/abilities.h"
#include "constants/character_story.h"
#include "constants/flags.h"
#include "constants/johto_ids.h"
#include "constants/moves.h"
#include "constants/opponents.h"
#include "constants/species.h"

bool8 CharacterStarter_IsPikachuCohort(void)
{
    return CharacterStory_IsReady() && FlagGet(FLAG_ST01_NEW_COHORT)
        && FlagGet(FLAG_ST01_GIVEN);
}

u16 CharacterStarter_GetKantoSpecies(void)
{
    if (CharacterStarter_IsPikachuCohort())
        return SPECIES_PIKACHU;
    // The existing helper/table remains authoritative for older campaigns.
    return GetStarterPokemon(VarGet(VAR_STARTER_MON));
}

void Special_CharacterStarterSpecies(void)
{
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = CharacterStarter_GetKantoSpecies();
}

void Special_CharacterStarterPreflight(void)
{
    bool8 compatible;
    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    gSpecialVar_Result = FALSE;
    if (!CharacterStory_IsReady() || !FlagGet(FLAG_ST01_NEW_COHORT))
        return;
    if (!FlagGet(FLAG_ST01_GIVEN) && !FlagGet(FLAG_SYS_POKEMON_GET))
    {
        compatible = DoesSpeciesPassOneTypeChallenge(SPECIES_PIKACHU);
#if RANDOMIZER_AVAILABLE
        if (RandomizerFeatureEnabled(RANDOMIZE_FIXED_MON)
         || RandomizerFeatureEnabled(RANDOMIZE_STARTER_AND_GIFT_MON))
            compatible = FALSE;
#endif
        if (!compatible)
        {
            // Only the untouched opening may fall back to native choices.
            // Never force a type, box a first partner, or rewrite older history.
            FlagClear(FLAG_ST01_NEW_COHORT);
            FlagClear(FLAG_HIDE_BULBASAUR_BALL);
            FlagClear(FLAG_HIDE_SQUIRTLE_BALL);
            FlagClear(FLAG_HIDE_CHARMANDER_BALL);
            return;
        }
    }
    gSpecialVar_Result = TRUE;
}

static bool8 IsBluePartnerTrainer(u16 trainerNum)
{
    // Exact native Kanto family only. Silver/imported trainers never match.
    switch (trainerNum)
    {
    case TRAINER_RIVAL_OAKS_LAB_SQUIRTLE:
    case TRAINER_RIVAL_OAKS_LAB_BULBASAUR:
    case TRAINER_RIVAL_OAKS_LAB_CHARMANDER:
    case TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE:
    case TRAINER_RIVAL_ROUTE22_EARLY_BULBASAUR:
    case TRAINER_RIVAL_ROUTE22_EARLY_CHARMANDER:
    case TRAINER_RIVAL_CERULEAN_SQUIRTLE:
    case TRAINER_RIVAL_CERULEAN_BULBASAUR:
    case TRAINER_RIVAL_CERULEAN_CHARMANDER:
    case TRAINER_RIVAL_SS_ANNE_SQUIRTLE:
    case TRAINER_RIVAL_SS_ANNE_BULBASAUR:
    case TRAINER_RIVAL_SS_ANNE_CHARMANDER:
    case TRAINER_RIVAL_POKEMON_TOWER_SQUIRTLE:
    case TRAINER_RIVAL_POKEMON_TOWER_BULBASAUR:
    case TRAINER_RIVAL_POKEMON_TOWER_CHARMANDER:
    case TRAINER_RIVAL_SILPH_SQUIRTLE:
    case TRAINER_RIVAL_SILPH_BULBASAUR:
    case TRAINER_RIVAL_SILPH_CHARMANDER:
    case TRAINER_RIVAL_ROUTE22_LATE_SQUIRTLE:
    case TRAINER_RIVAL_ROUTE22_LATE_BULBASAUR:
    case TRAINER_RIVAL_ROUTE22_LATE_CHARMANDER:
    case TRAINER_CHAMPION_FIRST_SQUIRTLE:
    case TRAINER_CHAMPION_FIRST_BULBASAUR:
    case TRAINER_CHAMPION_FIRST_CHARMANDER:
    case TRAINER_CHAMPION_REMATCH_SQUIRTLE:
    case TRAINER_CHAMPION_REMATCH_BULBASAUR:
    case TRAINER_CHAMPION_REMATCH_CHARMANDER:
        return TRUE;
    default:
        return FALSE;
    }
}

static void SetBluePartnerMoves(struct TrainerMon *mon)
{
    // Audited GEN_7 level-up moves, keeping a usable attack at every stage.
    // None of the replaced Fire/Water/Grass partner moves are carried over.
    mon->moves[0] = MOVE_TACKLE;
    mon->moves[1] = MOVE_TAIL_WHIP;
    mon->moves[2] = mon->lvl >= 5 ? MOVE_SAND_ATTACK : MOVE_GROWL;
    mon->moves[3] = MOVE_GROWL;
    if (mon->species == SPECIES_UMBREON)
    {
        mon->moves[0] = MOVE_PURSUIT;
        mon->moves[1] = MOVE_TACKLE;
        mon->moves[2] = MOVE_TAIL_WHIP;
        mon->moves[3] = mon->lvl >= 5 ? MOVE_SAND_ATTACK : MOVE_HELPING_HAND;
        if (mon->lvl >= 13)
            mon->moves[1] = MOVE_QUICK_ATTACK;
        if (mon->lvl >= 17)
            mon->moves[3] = MOVE_CONFUSE_RAY;
        if (mon->lvl >= 20)
            mon->moves[0] = MOVE_FEINT_ATTACK;
        if (mon->lvl >= 25)
            mon->moves[1] = MOVE_ASSURANCE;
        if (mon->lvl >= 33)
            mon->moves[2] = MOVE_MOONLIGHT;
    }
    else
    {
        if (mon->lvl >= 13)
            mon->moves[0] = MOVE_QUICK_ATTACK;
        if (mon->lvl >= 17)
        {
            mon->moves[1] = MOVE_SWIFT;
            mon->moves[3] = MOVE_BITE;
        }
        if (mon->lvl >= 25)
            mon->moves[0] = MOVE_TAKE_DOWN;
        if (mon->lvl >= 29)
            mon->moves[2] = MOVE_CHARM;
        if (mon->lvl >= 37)
            mon->moves[0] = MOVE_DOUBLE_EDGE;
    }
}

bool8 CharacterStarter_TryCreateBlueParty(struct Pokemon *party, u16 trainerNum,
    bool8 firstTrainer, u32 battleTypeFlags, u8 *result)
{
    struct Trainer trainer;
    struct TrainerMon mons[PARTY_SIZE];
    struct TrainerMon *partner;
    const struct Trainer *original;
    if (!CharacterStarter_IsPikachuCohort() || !IsBluePartnerTrainer(trainerNum)
     || !(battleTypeFlags & BATTLE_TYPE_TRAINER)
     || (battleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_FRONTIER
        | BATTLE_TYPE_EREADER_TRAINER | BATTLE_TYPE_TRAINER_HILL
        | BATTLE_TYPE_RECORDED)))
        return FALSE;
    original = GetTrainerStructFromId(trainerNum);
    // Every audited native variant is a fixed, non-pool party with its partner
    // last. Unexpected future data falls back instead of guessing an index.
    if (original->partySize == 0 || original->partySize > PARTY_SIZE
     || original->poolSize != 0 || original->overrideTrainer != 0)
        return FALSE;
    partner = &mons[original->partySize - 1];
    memcpy(&trainer, original, sizeof(trainer));
    memcpy(mons, original->party, original->partySize * sizeof(*mons));
    switch (partner->species)
    {
    case SPECIES_BULBASAUR: case SPECIES_IVYSAUR: case SPECIES_VENUSAUR:
    case SPECIES_CHARMANDER: case SPECIES_CHARMELEON: case SPECIES_CHARIZARD:
    case SPECIES_SQUIRTLE: case SPECIES_WARTORTLE: case SPECIES_BLASTOISE:
        break;
    default:
        return FALSE;
    }
    partner->species = FlagGet(FLAG_BL03_SEEN)
        && CharacterStory_HasMetElm()
        ? SPECIES_UMBREON : SPECIES_EEVEE;
    partner->ability = ABILITY_NONE;
    SetBluePartnerMoves(partner);
    trainer.party = mons;
    // The native creator retains level/item/IVs/EVs/nature, normal difficulty,
    // randomizer policy, trainer identity, supporting team and stat calculation.
    *result = CreateNPCTrainerPartyFromTrainer(party, &trainer, firstTrainer, battleTypeFlags);
    return TRUE;
}

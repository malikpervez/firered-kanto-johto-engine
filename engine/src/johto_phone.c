#include "global.h"
#ifdef FIRERED
#include "johto_phone.h"
#include "event_data.h"
#include "pokedex.h"
#include "pokemon.h"
#include "constants/pokedex.h"

// Original HnS rating logic, with the explicit Johto list for the regional call.
extern const u8 J_gJohtoDexRatingText_Complete[];
#define gJohtoDexRatingText_Complete J_gJohtoDexRatingText_Complete
extern const u8 J_gJohtoDexRatingText_LessThan10[];
#define gJohtoDexRatingText_LessThan10 J_gJohtoDexRatingText_LessThan10
extern const u8 J_gJohtoDexRatingText_LessThan110[];
#define gJohtoDexRatingText_LessThan110 J_gJohtoDexRatingText_LessThan110
extern const u8 J_gJohtoDexRatingText_LessThan125[];
#define gJohtoDexRatingText_LessThan125 J_gJohtoDexRatingText_LessThan125
extern const u8 J_gJohtoDexRatingText_LessThan140[];
#define gJohtoDexRatingText_LessThan140 J_gJohtoDexRatingText_LessThan140
extern const u8 J_gJohtoDexRatingText_LessThan155[];
#define gJohtoDexRatingText_LessThan155 J_gJohtoDexRatingText_LessThan155
extern const u8 J_gJohtoDexRatingText_LessThan170[];
#define gJohtoDexRatingText_LessThan170 J_gJohtoDexRatingText_LessThan170
extern const u8 J_gJohtoDexRatingText_LessThan185[];
#define gJohtoDexRatingText_LessThan185 J_gJohtoDexRatingText_LessThan185
extern const u8 J_gJohtoDexRatingText_LessThan20[];
#define gJohtoDexRatingText_LessThan20 J_gJohtoDexRatingText_LessThan20
extern const u8 J_gJohtoDexRatingText_LessThan200[];
#define gJohtoDexRatingText_LessThan200 J_gJohtoDexRatingText_LessThan200
extern const u8 J_gJohtoDexRatingText_LessThan215[];
#define gJohtoDexRatingText_LessThan215 J_gJohtoDexRatingText_LessThan215
extern const u8 J_gJohtoDexRatingText_LessThan230[];
#define gJohtoDexRatingText_LessThan230 J_gJohtoDexRatingText_LessThan230
extern const u8 J_gJohtoDexRatingText_LessThan245[];
#define gJohtoDexRatingText_LessThan245 J_gJohtoDexRatingText_LessThan245
extern const u8 J_gJohtoDexRatingText_LessThan260[];
#define gJohtoDexRatingText_LessThan260 J_gJohtoDexRatingText_LessThan260
extern const u8 J_gJohtoDexRatingText_LessThan275[];
#define gJohtoDexRatingText_LessThan275 J_gJohtoDexRatingText_LessThan275
extern const u8 J_gJohtoDexRatingText_LessThan35[];
#define gJohtoDexRatingText_LessThan35 J_gJohtoDexRatingText_LessThan35
extern const u8 J_gJohtoDexRatingText_LessThan50[];
#define gJohtoDexRatingText_LessThan50 J_gJohtoDexRatingText_LessThan50
extern const u8 J_gJohtoDexRatingText_LessThan65[];
#define gJohtoDexRatingText_LessThan65 J_gJohtoDexRatingText_LessThan65
extern const u8 J_gJohtoDexRatingText_LessThan80[];
#define gJohtoDexRatingText_LessThan80 J_gJohtoDexRatingText_LessThan80
extern const u8 J_gJohtoDexRatingText_LessThan95[];
#define gJohtoDexRatingText_LessThan95 J_gJohtoDexRatingText_LessThan95
extern const u8 J_gJohtoDexRatingText_LessThanMaxDex[];
#define gJohtoDexRatingText_LessThanMaxDex J_gJohtoDexRatingText_LessThanMaxDex
extern const u8 J_gNationalDexRatingText_Complete[];
#define gNationalDexRatingText_Complete J_gNationalDexRatingText_Complete
extern const u8 J_gNationalDexRatingText_LessThan100[];
#define gNationalDexRatingText_LessThan100 J_gNationalDexRatingText_LessThan100
extern const u8 J_gNationalDexRatingText_LessThan150[];
#define gNationalDexRatingText_LessThan150 J_gNationalDexRatingText_LessThan150
extern const u8 J_gNationalDexRatingText_LessThan200[];
#define gNationalDexRatingText_LessThan200 J_gNationalDexRatingText_LessThan200
extern const u8 J_gNationalDexRatingText_LessThan250[];
#define gNationalDexRatingText_LessThan250 J_gNationalDexRatingText_LessThan250
extern const u8 J_gNationalDexRatingText_LessThan300[];
#define gNationalDexRatingText_LessThan300 J_gNationalDexRatingText_LessThan300
extern const u8 J_gNationalDexRatingText_LessThan350[];
#define gNationalDexRatingText_LessThan350 J_gNationalDexRatingText_LessThan350
extern const u8 J_gNationalDexRatingText_LessThan400[];
#define gNationalDexRatingText_LessThan400 J_gNationalDexRatingText_LessThan400
extern const u8 J_gNationalDexRatingText_LessThan435[];
#define gNationalDexRatingText_LessThan435 J_gNationalDexRatingText_LessThan435
extern const u8 J_gNationalDexRatingText_LessThan465[];
#define gNationalDexRatingText_LessThan465 J_gNationalDexRatingText_LessThan465
extern const u8 J_gNationalDexRatingText_LessThan475[];
#define gNationalDexRatingText_LessThan475 J_gNationalDexRatingText_LessThan475
extern const u8 J_gNationalDexRatingText_LessThanMaxDex[];
#define gNationalDexRatingText_LessThanMaxDex J_gNationalDexRatingText_LessThanMaxDex

const u8 *JohtoPhone_GetPokedexRatingText(u32 count)
{
    u32 i, j, k;
    // doesNotCountForRegionalPokedex
    u16 maxDex = JOHTO_DEX_COUNT - 1;
    for (i = 0; i < JOHTO_DEX_COUNT - 1; i++)
    {
        j = JohtoToNationalOrder(i + 1);
        k = NationalPokedexNumToSpecies(j);
        if (gSpeciesInfo[k].dexNotRequired || (gSpeciesInfo[k].isMythical && !gSpeciesInfo[k].dexForceRequired))
        {
            if (GetSetPokedexFlag(j, FLAG_GET_CAUGHT))
                count--;
            maxDex--;
        }
    }

    if (count >= maxDex)
    {
        gSpecialVar_Result = TRUE;
        return gJohtoDexRatingText_Complete;
    }

    gSpecialVar_Result = FALSE;

    if (count < 10)
        return gJohtoDexRatingText_LessThan10;

    if (count < 20)
        return gJohtoDexRatingText_LessThan20;

    if (count < 35)
        return gJohtoDexRatingText_LessThan35;

    if (count < 50)
        return gJohtoDexRatingText_LessThan50;

    if (count < 65)
        return gJohtoDexRatingText_LessThan65;

    if (count < 80)
        return gJohtoDexRatingText_LessThan80;

    if (count < 95)
        return gJohtoDexRatingText_LessThan95;

    if (count < 110)
        return gJohtoDexRatingText_LessThan110;

    if (count < 125)
        return gJohtoDexRatingText_LessThan125;

    if (count < 140)
        return gJohtoDexRatingText_LessThan140;

    if (count < 155)
        return gJohtoDexRatingText_LessThan155;

    if (count < 170)
        return gJohtoDexRatingText_LessThan170;

    if (count < 185)
        return gJohtoDexRatingText_LessThan185;

    if (count < 200)
        return gJohtoDexRatingText_LessThan200;

    if (count < 215)
        return gJohtoDexRatingText_LessThan215;

    if (count < 230)
        return gJohtoDexRatingText_LessThan230;

    if (count < 245)
        return gJohtoDexRatingText_LessThan245;

    if (count < 260)
        return gJohtoDexRatingText_LessThan260;

    if (count < 275)
        return gJohtoDexRatingText_LessThan275;

    return gJohtoDexRatingText_LessThanMaxDex;
}

const u8 *JohtoPhone_GetNationalPokedexRatingText(u32 count)
{
    u32 i, j, k;
    // doesNotCountForObtainablePokedex
    u16 maxDex = OBTAINABLE_DEX_COUNT - 1;
    for (i = 1; i < OBTAINABLE_DEX_COUNT - 1; i++)
    {
        j = ObtainableToNationalOrder(i + 1);
        k = NationalPokedexNumToSpecies(j);
        if (gSpeciesInfo[k].dexNotRequired || (gSpeciesInfo[k].isMythical && !gSpeciesInfo[k].dexForceRequired))
        {
            if (GetSetPokedexFlag(j, FLAG_GET_CAUGHT))
                count--;
            maxDex--;
        }
    }

    if (count >= maxDex)
    {
        gSpecialVar_Result = TRUE;
        return gNationalDexRatingText_Complete;
    }

    gSpecialVar_Result = FALSE;

    if (count < 100)
        return gNationalDexRatingText_LessThan100;

    if (count < 150)
        return gNationalDexRatingText_LessThan150;

    if (count < 200)
        return gNationalDexRatingText_LessThan200;

    if (count < 250)
        return gNationalDexRatingText_LessThan250;

    if (count < 300)
        return gNationalDexRatingText_LessThan300;

    if (count < 350)
        return gNationalDexRatingText_LessThan350;

    if (count < 400)
        return gNationalDexRatingText_LessThan400;

    if (count < 435)
        return gNationalDexRatingText_LessThan435;

    if (count < 465)
        return gNationalDexRatingText_LessThan465;

    if (count < 475)
        return gNationalDexRatingText_LessThan475;

    return gNationalDexRatingText_LessThanMaxDex;
}

#endif

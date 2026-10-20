#include "global.h"
#include "save.h"
#include "pokemon_storage_system.h"
#include "regional_save.h"
const u32 registered[] __attribute__((section(".registered"))) = {
 sizeof(struct SaveBlock1),sizeof(struct SaveBlock2),sizeof(struct SaveBlock3),
 sizeof(struct PokemonStorage),sizeof(struct Pokemon),sizeof(struct BoxPokemon),
 SAVE_VERSION,REGIONAL_SAVE_SCHEMA,REGIONAL_SAVE_CONTENT_ID,REGIONAL_SAVE_LAYOUT_ID,
 REGIONAL_SAVE_RESERVE_OFFSET,REGIONAL_SAVE_RESERVE_SIZE,
 __builtin_offsetof(struct SaveBlock1,flags),sizeof(((struct SaveBlock1*)0)->flags),
 __builtin_offsetof(struct SaveBlock1,vars),sizeof(((struct SaveBlock1*)0)->vars),
 __builtin_offsetof(struct SaveBlock1,roamer),sizeof(((struct SaveBlock1*)0)->roamer),
 __builtin_offsetof(struct SaveBlock1,roamerPadding),sizeof(((struct SaveBlock1*)0)->roamerPadding),
 __builtin_offsetof(struct SaveBlock1,rivalName),__builtin_offsetof(struct SaveBlock2,rivalName)
};

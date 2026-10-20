#include "global.h"
#include "main.h"
#include "crt0.h"
#include "gpu_regs.h"
#include "m4a.h"
#include "load_save.h"
#include "save.h"
#include "new_game.h"
#include "overworld.h"
#include "malloc.h"
#include "main_menu.h"

// Reloads the game, continuing from the point of the last save
// Used to gracefully exit after a link connection error
void ReloadSave(void)
{
    u16 imeBackup = REG_IME;
#ifdef FIRERED
    if (FireRedSave_IsBusy())
    {
        FireRedSave_Abort();
        return;
    }
#endif
    REG_IME = 0;
    RegisterRamReset(RESET_EWRAM);
    ReInitializeEWRAM();
    ClearGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_FORCED_BLANK);
    REG_IME = imeBackup;
    gMain.inBattle = FALSE;
    SetSaveBlocksPointers(GetSaveBlocksPointersBaseOffset());
    ResetMenuAndMonGlobals();
    Save_ResetSaveCounters();
    LoadGameSave(SAVE_NORMAL);
    if (gSaveFileStatus == SAVE_STATUS_EMPTY
#ifndef FIRERED
            || gSaveFileStatus == SAVE_STATUS_CORRUPT
#endif
        )
    {
        Sav2_ClearSetDefault();
        ClearSav3();
        SetDefaultChallengeSettings();
    }
    SetPokemonCryStereo(gSaveBlock2Ptr->optionsSound);
    InitHeap(gHeap, HEAP_SIZE);
#ifdef FIRERED
    if (!FireRedSave_IsLoaded())
    {
        SetMainCallback2(CB2_InitMainMenu);
        return;
    }
#endif
    SetMainCallback2(CB2_ContinueSavedGame);
}

#include "global.h"

#ifdef FIRERED
#include "event_data.h"
#include "firered_save.h"
#include "johto_progression.h"
#include "regional_save.h"
#include "script.h"

STATIC_ASSERT(JOHTO_ERRAND_VAR < REGIONAL_SAVE_VAR_COUNT, JohtoErrandVariableBound);
STATIC_ASSERT(JOHTO_ERRAND_EVENT_REWARDED < REGIONAL_SAVE_EVENT_COUNT, JohtoErrandEventBound);

static u16 GetErrandState(void)
{
    const u8 *image = (const u8 *)gSaveBlock3Ptr;
    u16 state;

    // Validate live semantic state, not its last persisted CRC/digest.
    if (!RegionalSave_FoundationValid(image))
        return JOHTO_ERRAND_INVALID;
    if (RegionalSave_Read32(image + REGIONAL_SAVE_JOHTO_FLAGS_OFFSET) == 0)
        return JOHTO_ERRAND_NOT_STARTED;
    if (!RegionalSave_GetVar(image, REGIONAL_SAVE_JOHTO, JOHTO_ERRAND_VAR, &state))
        return JOHTO_ERRAND_INVALID;
    return state;
}

static bool8 AdvanceErrand(u16 state, u16 event)
{
    u8 *image = (u8 *)gSaveBlock3Ptr;

    FireRedSave_NotifyPersistentWrite();
    return RegionalSave_SetEvent(image, REGIONAL_SAVE_JOHTO, event, TRUE)
        && RegionalSave_SetVar(image, REGIONAL_SAVE_JOHTO, JOHTO_ERRAND_VAR, state);
}

void Special_JohtoErrandGetState(void)
{
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = GetErrandState();
}

void Special_JohtoErrandAccept(void)
{
    u16 state;

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    state = GetErrandState();
    gSpecialVar_Result = FALSE;
    if (state == JOHTO_ERRAND_INVALID)
        return;
    if (state == JOHTO_ERRAND_NOT_STARTED)
    {
        FireRedSave_NotifyPersistentWrite();
        // Initializes revisions and accepted variable/event together.
        gSpecialVar_Result = RegionalSave_InitializeJohto((u8 *)gSaveBlock3Ptr);
    }
    else
    {
        gSpecialVar_Result = TRUE;
    }
}

void Special_JohtoErrandVisitGuide(void)
{
    u16 state;

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    state = GetErrandState();
    gSpecialVar_Result = FALSE;
    if (state == JOHTO_ERRAND_ACCEPTED)
        gSpecialVar_Result = AdvanceErrand(JOHTO_ERRAND_GUIDE_VISITED, JOHTO_ERRAND_EVENT_GUIDE_VISITED);
    else if (state == JOHTO_ERRAND_GUIDE_VISITED || state == JOHTO_ERRAND_REWARDED)
        gSpecialVar_Result = TRUE;
}

void Special_JohtoErrandClaimReward(void)
{
    bool8 itemAdded;

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    itemAdded = gSpecialVar_Result == TRUE;
    gSpecialVar_Result = FALSE;
    if (itemAdded && GetErrandState() == JOHTO_ERRAND_GUIDE_VISITED)
        gSpecialVar_Result = AdvanceErrand(JOHTO_ERRAND_REWARDED, JOHTO_ERRAND_EVENT_REWARDED);
}
#endif // FIRERED

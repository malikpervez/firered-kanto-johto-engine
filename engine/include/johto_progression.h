#ifndef GUARD_JOHTO_PROGRESSION_H
#define GUARD_JOHTO_PROGRESSION_H

#include "global.h"

#ifdef FIRERED
// These are regional codec indices, never native Kanto flag or variable IDs.
#define JOHTO_ERRAND_VAR 0
#define JOHTO_ERRAND_EVENT_ACCEPTED 0
#define JOHTO_ERRAND_EVENT_GUIDE_VISITED 1
#define JOHTO_ERRAND_EVENT_REWARDED 2

enum JohtoErrandState
{
    JOHTO_ERRAND_NOT_STARTED = 0,
    JOHTO_ERRAND_ACCEPTED = 1,
    JOHTO_ERRAND_GUIDE_VISITED = 2,
    JOHTO_ERRAND_REWARDED = 3,
    JOHTO_ERRAND_INVALID = 0xFFFF,
};

void Special_JohtoErrandGetState(void);
void Special_JohtoErrandAccept(void);
void Special_JohtoErrandVisitGuide(void);
// VAR_RESULT must still be the successful native additem result.
void Special_JohtoErrandClaimReward(void);
#endif // FIRERED

#endif // GUARD_JOHTO_PROGRESSION_H

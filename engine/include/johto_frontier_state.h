#ifndef GUARD_JOHTO_FRONTIER_STATE_H
#define GUARD_JOHTO_FRONTIER_STATE_H

#include "regions.h"
#include "constants/johto_ids.h"

// Call sites name both identities explicitly; this never redirects an
// arbitrary native variable or flag merely because the player is in Johto.
static inline u16 JohtoFrontierStateId(u16 nativeId, u16 johtoId)
{
    return IsJohtoCampaignMap() ? johtoId : nativeId;
}
#define FRONTIER_STATE_ID(nativeId, johtoId) JohtoFrontierStateId(nativeId, johtoId)
#define FRONTIER_GFX(nativeId, johtoId) JohtoFrontierStateId(nativeId, johtoId)
#define FRONTIER_LAYOUT(nativeId, johtoId) JohtoFrontierStateId(nativeId, johtoId)
#define FRONTIER_MAP(nativeId, johtoId) JohtoFrontierStateId(nativeId, johtoId)

#endif // GUARD_JOHTO_FRONTIER_STATE_H

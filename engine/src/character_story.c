#include "global.h"

#include "character_story.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "friends_story.h"
#include "johto_campaign.h"
#include "rainbow_story.h"
#include "regional_save.h"
#include "script.h"
#include "sprite.h"
#include "constants/character_story.h"
#include "constants/event_objects.h"
#include "constants/friends_story.h"
#include "constants/johto_ids.h"
#include "constants/map_groups.h"
#include "constants/maps.h"
#include "constants/starter_recruitment.h"
#include "constants/species.h"

STATIC_ASSERT(CHARACTER_STORY_FLAGS_FIRST > BUILD_FLAGS_END, CharacterStoryAboveNativeEnd);
STATIC_ASSERT(CHARACTER_STORY_FLAGS_LAST < ENGINE_FLAGS_START, CharacterStoryBelowEngineFlags);
STATIC_ASSERT(CHARACTER_STORY_FLAGS_FIRST > DAILY_FLAGS_END, CharacterStoryOutsideDailyFlags);

static bool8 UnassignedBitsClear(void)
{
    u16 flag;
    // The new registered Friends allocation owns 0x934..0x93F. Accept it only
    // when marked and typed-valid; unmarked older occupancy still fails closed.
    if (FlagGet(FLAG_FRIENDS_STORY_ADOPTED) && FriendsStory_AllocationValid())
        return TRUE;
    for (flag = CHARACTER_STORY_UNUSED_FIRST; flag <= CHARACTER_STORY_FLAGS_LAST; flag++)
        if (FlagGet(flag))
            return FALSE;
    return TRUE;
}

bool8 CharacterStory_IsReady(void)
{
    return gSaveBlock1Ptr != NULL && FlagGet(FLAG_CHARACTER_STORY_ADOPTED)
        && UnassignedBitsClear() && RainbowStory_IsReady();
}

bool8 CharacterStory_HasMetElm(void)
{
    // An unseeded regional variable has no pointer. Native VarGet then returns
    // its operand ID, which must never be interpreted as completed progress.
    return JohtoCampaign_IsSeeded()
        && VarGet(JOHTO_VAR_NEWBARKTOWN_LABSTATE) >= 2;
}

void Special_CharacterStoryElmProgress(void)
{
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = CharacterStory_HasMetElm();
}

void CharacterStory_NewGame(void)
{
    // This hook follows native flag clearing, never an older-save load.
    FlagSet(FLAG_CHARACTER_STORY_ADOPTED);
    FlagSet(FLAG_ST01_NEW_COHORT);
}

void Special_CharacterStoryAdopt(void)
{
    u16 flag;
    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    gSpecialVar_Result = CharacterStory_IsReady();
    if (gSpecialVar_Result)
        return;
    if (gSaveBlock1Ptr == NULL || gSaveBlock3Ptr == NULL
     || !RegionalSave_FoundationValid((const u8 *)gSaveBlock3Ptr))
        return;
    for (flag = CHARACTER_STORY_FLAGS_FIRST; flag <= CHARACTER_STORY_FLAGS_LAST; flag++)
        if (FlagGet(flag))
            return;
    if (!RainbowStory_TryAdopt())
        return;
    // Supported older native6 saves gain optional scenes/gifts, never a new
    // starter, a Pikachu memory, or fabricated earlier character meetings.
    FlagSet(FLAG_CHARACTER_STORY_ADOPTED);
    gSpecialVar_Result = TRUE;
}

// Upload the first frame after changing raw sheets, including Jessie's 32x32 OAM.
static void SetStoryGraphics(struct ObjectEvent *objectEvent, u16 graphicsId)
{
    ObjectEventSetGraphicsId(objectEvent, graphicsId);
    StartSpriteAnim(&gSprites[objectEvent->spriteId],
        GetFaceDirectionAnimNum(objectEvent->facingDirection));
    SeekSpriteAnim(&gSprites[objectEvent->spriteId], 0);
}

void Special_CharacterStoryTrioReveal(void)
{
    u8 id, actor;
    u16 map;
    Script_RequestEffects(SCREFF_V1 | SCREFF_HARDWARE);
    gSpecialVar_Result = FALSE;
    if (!CharacterStory_IsReady())
        return;
    map = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
    actor = gSpecialVar_0x8004;
    if (!((map == MAP_CELADON_CITY && actor == 20)
       || (map == MAP_GOLDENROD_CITY_HNS && actor == 41)))
        return;
    if (!TryGetObjectEventIdByLocalIdAndMap(actor,
        gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, &id))
        SetStoryGraphics(&gObjectEvents[id], OBJ_EVENT_GFX_JESSIE_STORY);
    if (!TryGetObjectEventIdByLocalIdAndMap(actor + 1,
        gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, &id))
        SetStoryGraphics(&gObjectEvents[id], OBJ_EVENT_GFX_JAMES_STORY);
    gSpecialVar_Result = TRUE;
}

// Refresh presentation only: no adoption, story writes, or saved-template edits.
void CharacterStory_OnObjectSpawn(u8 objectEventId)
{
    struct ObjectEvent *objectEvent;
    u16 map;
    if (objectEventId >= OBJECT_EVENTS_COUNT || !CharacterStory_IsReady())
        return;
    objectEvent = &gObjectEvents[objectEventId];
    if (!objectEvent->active || objectEvent->spriteId >= MAX_SPRITES
     || !gSprites[objectEvent->spriteId].inUse
     || objectEvent->mapGroup != gSaveBlock1Ptr->location.mapGroup
     || objectEvent->mapNum != gSaveBlock1Ptr->location.mapNum)
        return;
    map = (objectEvent->mapGroup << 8) | objectEvent->mapNum;
    if (map == MAP_VERMILION_CITY && objectEvent->localId == ST04_JENNY_ACTOR
     && objectEvent->graphicsId == OBJ_EVENT_GFX_POLICEMAN)
        SetStoryGraphics(objectEvent, OBJ_EVENT_GFX_JENNY_STORY);
    // Until the survey is seen, retain the intentional scientist disguises.
    // Afterwards the optional challenge survives menu, map and cold returns.
    if (map == MAP_CELADON_CITY && FlagGet(FLAG_JT02_SEEN))
    {
        if (objectEvent->localId == 20)
            SetStoryGraphics(objectEvent, OBJ_EVENT_GFX_JESSIE_STORY);
        else if (objectEvent->localId == 21)
            SetStoryGraphics(objectEvent, OBJ_EVENT_GFX_JAMES_STORY);
    }
}

void Special_CharacterStoryPartner(void)
{
    u16 starter, species;
    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    gSpecialVar_Result = FALSE;
    if (!CharacterStory_IsReady() || !JohtoCampaign_IsSeeded())
        return;
    if (gSpecialVar_0x8005 != 1 && gSpecialVar_0x8005 != 2)
        return;
    starter = VarGet(JOHTO_VAR_STARTER_MON);
    // These are the actual native Silver partner mappings, not the player's
    // unchanged Kanto starter. Unknown regional state hides the optional scene.
    if (starter == 0)
        species = gSpecialVar_0x8005 == 1 ? SPECIES_QUILAVA : SPECIES_TYPHLOSION;
    else if (starter == 1)
        species = gSpecialVar_0x8005 == 1 ? SPECIES_CROCONAW : SPECIES_FERALIGATR;
    else if (starter == 2)
        species = gSpecialVar_0x8005 == 1 ? SPECIES_BAYLEEF : SPECIES_MEGANIUM;
    else
        return;
    VarSet(VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_MON_BASE + species);
    gSpecialVar_Result = TRUE;
}


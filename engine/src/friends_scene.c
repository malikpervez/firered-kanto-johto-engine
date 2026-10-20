#include "global.h"

#ifdef FIRERED
#include "friends_scene.h"
#include "friends_camera.h"
#include "friends_story.h"
#include "friends_visuals.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "fieldmap.h"
#include "script.h"
#include "sprite.h"
#include "task.h"
#include "constants/event_objects.h"
#include "constants/friends_story.h"
#include "constants/event_object_movement.h"
#include "constants/map_groups.h"
#include "constants/maps.h"
#include "constants/species.h"

struct FriendsCamp { u16 map; s16 x, y; u8 firstLocalId; };
static const struct FriendsCamp sCamps[] = {
#include "data/friends_scene_locations.h"
};
// Keys match the immutable asset manifest: Brian, Ham, Jon, Nick, X, LB, Tim.
// Three foreground adults in ordinary scenes. The rest are nearby in fiction.
static const u8 sForeground[] = {
    0, 0x7F, 0x0D, 0x2C, 0x52, 0x4C, 0x29, 0x31, 0x0E, 0x49,
    0x51, 0x19, 0x49, 0x0B, 0x38, 0x0D, 0x2A, 0x19, 0x48, 0x0E,
    0x49, 0x7F, 0x7F,
};
static const u16 sFinalPartners[][2] = {
    {SPECIES_RATICATE, SPECIES_SLOWBRO},
    {SPECIES_BELLOSSOM, SPECIES_PARASECT},
    {SPECIES_FEAROW, SPECIES_KINGLER},
    {SPECIES_WIGGLYTUFF, SPECIES_MURKROW},
    {SPECIES_POLIWHIRL, SPECIES_GRAVELER},
    {SPECIES_PRIMEAPE, SPECIES_NOCTOWL},
    {SPECIES_GOLDUCK, SPECIES_FURRET},
};
static const u8 sDepartureOrder[] = {0, 4, 6, 5, 3, 2, 1};
static EWRAM_DATA bool8 sAllowTransient = FALSE;
static EWRAM_DATA u16 sMovementFault = 0;
// EWRAM .sbss requires zero initialization. Actual map setup resets the
// private speaker sentinel to0xFF before any optional Friends interaction.
static EWRAM_DATA u8 sPreviousSpeaker = 0;
static EWRAM_DATA u8 sPreviousCrossing = 0;
static EWRAM_DATA s16 sFujiReturnX = 0;
static EWRAM_DATA s16 sFujiReturnY = 0;
static EWRAM_DATA bool8 sFujiStartedInside = FALSE;
// Private one-warp handoff only. Native map loading resets the script context;
// no phase, route or additional receipt is stored in any native save sector.
static EWRAM_DATA u8 sFujiWarpPhase = 0;
static EWRAM_DATA bool8 sFujiContextValid = FALSE;

static const struct FriendsCamp *CurrentCamp(void)
{
    u32 i;
    u16 map = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
    for (i = 0; i < ARRAY_COUNT(sCamps); i++)
        if (sCamps[i].map == map)
            return &sCamps[i];
    return NULL;
}


struct FriendsSpriteBounds { s32 left, top, right, bottom; };

static void FriendsSpriteBounds(const struct Sprite *sprite,
    const struct ObjectEventGraphicsInfo *graphics, struct FriendsSpriteBounds *bounds)
{
    // Match native OAM/offscreen geometry, including both pixel offsets. These
    // are conservative frame rectangles; transparent margins may hide early.
    bounds->left = sprite->x + sprite->x2 + sprite->centerToCornerVecX;
    bounds->top = sprite->y + sprite->y2 + sprite->centerToCornerVecY;
    if (sprite->coordOffsetEnabled)
    {
        bounds->left += gSpriteCoordOffsetX;
        bounds->top += gSpriteCoordOffsetY;
    }
    bounds->right = bounds->left + graphics->width;
    bounds->bottom = bounds->top + graphics->height;
}

bool8 FriendsScene_HideOverlappingFollower(const struct ObjectEvent *object,
    const struct Sprite *sprite)
{
    const struct FriendsCamp *camp;
    const struct ObjectEventGraphicsInfo *graphics;
    struct FriendsSpriteBounds follower, friend;
    u32 i;
    if (object == NULL || sprite == NULL || !object->active
     || object->localId != OBJ_EVENT_ID_FOLLOWER || object->invisible
     || object->offScreen || !sprite->inUse)
        return FALSE;
    camp = CurrentCamp();
    if (camp == NULL)
        return FALSE;
    graphics = GetObjectEventGraphicsInfo(object->graphicsId);
    if (graphics->width != 64 || graphics->height != 64)
        return FALSE;
    FriendsSpriteBounds(sprite, graphics, &follower);
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        const struct ObjectEvent *actor = &gObjectEvents[i];
        const struct Sprite *actorSprite;
        u8 logical;
        if (!actor->active || actor->invisible || actor->offScreen
         || actor->mapNum != gSaveBlock1Ptr->location.mapNum
         || actor->mapGroup != gSaveBlock1Ptr->location.mapGroup
         || actor->localId < camp->firstLocalId || actor->localId >= camp->firstLocalId + 7)
            continue;
        logical = actor->localId - camp->firstLocalId;
        // Matching a local ID alone must never hide a follower for native NPCs.
        if (actor->graphicsId != OBJ_EVENT_GFX_FRIEND_BRIAN + logical
         || actor->spriteId >= MAX_SPRITES)
            continue;
        actorSprite = &gSprites[actor->spriteId];
        if (!actorSprite->inUse || actorSprite->invisible)
            continue;
        graphics = GetObjectEventGraphicsInfo(actor->graphicsId);
        FriendsSpriteBounds(actorSprite, graphics, &friend);
        if (friend.right <= 0 || friend.left >= DISPLAY_WIDTH
         || friend.bottom <= 0 || friend.top >= DISPLAY_HEIGHT)
            continue;
        if (follower.left < friend.right && friend.left < follower.right
         && follower.top < friend.bottom && friend.top < follower.bottom)
            return TRUE;
    }
    return FALSE;
}

static bool8 VisitorCellOccupied(const struct FriendsCamp *camp, s16 dx, s16 dy)
{
    const struct ObjectEvent *player;
    s16 x = MAP_OFFSET + camp->x + dx;
    s16 y = MAP_OFFSET + camp->y + dy;
    u8 i;
    if (gPlayerAvatar.objectEventId >= OBJECT_EVENTS_COUNT)
        return TRUE;
    player = &gObjectEvents[gPlayerAvatar.objectEventId];
    if (!player->active)
        return TRUE;
    // The camera lifecycle recalls/removes the player's actual follower before
    // any visitor appears, then restores it before menus/battles/release.
    if (player->currentCoords.x == x && player->currentCoords.y == y)
        return TRUE;
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        const struct ObjectEvent *actor = &gObjectEvents[i];
        if (!actor->active || actor->localId == OBJ_EVENT_ID_FOLLOWER)
            continue;
        if (actor->mapNum == gSaveBlock1Ptr->location.mapNum
         && actor->mapGroup == gSaveBlock1Ptr->location.mapGroup
         && ((actor->localId >= camp->firstLocalId && actor->localId < camp->firstLocalId + 7)
          || (actor->localId >= 227 && actor->localId <= 230)))
            continue;
        if (actor->currentCoords.x == x && actor->currentCoords.y == y)
            return TRUE;
    }
    return FALSE;
}

static s16 GiratinaOffsetX(const struct FriendsCamp *camp)
{
    if (camp->map == MAP_CINNABAR_ISLAND)
        return -4;
    if (camp->map == MAP_NEW_BARK_TOWN_HNS)
        return -6;
    return -5;
}

static const struct ObjectEventTemplate *OwnedTemplate(const struct FriendsCamp *camp, u8 logical)
{
    u32 i;
    if (gMapHeader.events != NULL)
        for (i = 0; i < gMapHeader.events->objectEventCount; i++)
            if (gMapHeader.events->objectEvents[i].localId == camp->firstLocalId + logical)
                return &gMapHeader.events->objectEvents[i];
    return NULL;
}

struct FriendsWalk { u8 scene, actor; s8 dx, dy; };
static const struct FriendsWalk sWalks[] = {
    {2, 2, 0, 1}, {3, 5, -1, 0}, {5, 6, -1, 0}, {6, 5, 0, -1},
    {7, 4, -1, 0}, {9, 6, 1, 0}, {11, 3, 1, 0}, {18, 6, 1, 0},
    {20, 3, 0, 1}, {21, 0, 0, -1}, {22, 3, 1, 0},
};

static bool8 WalkCellsFree(const struct FriendsCamp *camp, u16 scene)
{
    const struct ObjectEventTemplate *actor;
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sWalks); i++)
        if (sWalks[i].scene == scene)
        {
            actor = OwnedTemplate(camp, sWalks[i].actor);
            if (actor == NULL || VisitorCellOccupied(camp,
                actor->x + sWalks[i].dx - camp->x, actor->y + sWalks[i].dy - camp->y))
                return FALSE;
        }
    if (scene == 21)
        for (i = 0; i < 7; i++)
        {
            actor = OwnedTemplate(camp, i);
            if (actor == NULL || VisitorCellOccupied(camp, actor->x - camp->x, actor->y - 1 - camp->y))
                return FALSE;
        }
    return TRUE;
}

static bool8 VisitorCellsFree(const struct FriendsCamp *camp, u16 scene)
{
    // Current-scene union, including later acquisition/reveal beats. Each bit
    // names slot0/1/2 at the ordinary(-2/0/+2,-1) cells. Adult slots are never
    // checked: their own occupants are expected and must remain untouched.
    static const u8 sSlots[] = {
        0, 0, 5, 5, 7, 2, 5, 7, 0, 7, 0, 0, 0, 7, 2, 5, 5, 0, 3, 5, 5, 0, 1,
    };
    u8 slot, mask = sSlots[scene];
    if (scene == 8)
        mask = camp->map == MAP_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE ? 1 : 2;
    for (slot = 0; slot < 3; slot++)
        if ((mask & (1 << slot)) && VisitorCellOccupied(camp, slot == 0 ? -2 : slot == 2 ? 2 : 0, -1))
            return FALSE;
    if (scene == 21)
    {
        // Departure is a real one-tile upward step after closemessage. Check
        // both starts and destinations before any dialogue or camera motion.
        if (VisitorCellOccupied(camp, 2, 2) || VisitorCellOccupied(camp, 4, 2)
         || VisitorCellOccupied(camp, 2, 3) || VisitorCellOccupied(camp, 4, 3))
            return FALSE;
    }
    if (scene == 1 || scene == 11 || scene == 17 || scene == 21)
        if (VisitorCellOccupied(camp, GiratinaOffsetX(camp),
                camp->map == MAP_ECRUTEAK_CITY_HNS ? 0 : -1))
            return FALSE;
    return WalkCellsFree(camp, scene);
}

bool32 FriendsScene_GetFramePoint(s16 *x, s16 *y)
{
    const struct FriendsCamp *camp = CurrentCamp();
    u16 scene = FriendsStory_GetMapScene();
    if (camp == NULL || x == NULL || y == NULL || !FriendsStory_IsReady()
     || scene == 0 || scene > FRIENDS_STORY_SCENE_COUNT
     || scene != FriendsStory_GetStage() || !FriendsStory_GetGate(scene)
     || !VisitorCellsFree(camp, scene))
        return FALSE;
    // Raw map coordinates. The bounded native camera proxy performs actual
    // cache scrolling and restores the original focus before releasing control.
    *x = camp->x;
    // The small native Fuji house needs its upper speaking position in view.
    // This moves only our temporary camera focus; no actor or player is moved.
    *y = camp->map == MAP_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE
        ? camp->y - 1 : camp->y + 1;
    return TRUE;
}

static const struct FriendsCamp *FindCamp(u8 mapNum, u8 mapGroup)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sCamps); i++)
        if (sCamps[i].map == ((mapGroup << 8) | mapNum))
            return &sCamps[i];
    return NULL;
}

static u8 ResolveLocalId(u8 conceptualId)
{
    const struct FriendsCamp *camp = CurrentCamp();
    if (camp != NULL && conceptualId >= 220 && conceptualId <= 226)
        return camp->firstLocalId + conceptualId - 220;
    return conceptualId;
}

bool8 FriendsScene_ShouldSpawn(u8 localId, u8 mapNum, u8 mapGroup)
{
    u16 scene;
    const struct FriendsCamp *camp = FindCamp(mapNum, mapGroup);
    if (camp == NULL)
        return TRUE;
    if (localId < camp->firstLocalId || (localId >= camp->firstLocalId + 7 && (localId < 227 || localId > 230)))
        return TRUE;
    if (mapNum != gSaveBlock1Ptr->location.mapNum || mapGroup != gSaveBlock1Ptr->location.mapGroup)
        return FALSE;
    if (localId >= 227)
        return sAllowTransient;
    scene = FriendsStory_GetMapScene();
    if (scene == 1 && FlagGet(FRIENDS_STORY_SEEN_FIRST))
        return FALSE; // A completed arrival never respawns after the exit beat.
    return FriendsStory_IsReady() && scene == FriendsStory_GetStage()
        && FriendsStory_GetGate(scene) && scene > 0 && scene < ARRAY_COUNT(sForeground)
        && (sForeground[scene] & (1 << (localId - camp->firstLocalId)));
}

static void Remove(u8 localId)
{
    RemoveObjectEventByLocalIdAndMap(ResolveLocalId(localId),
        gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);
}

static void ClearPartners(void)
{
    Remove(227); Remove(228); Remove(229);
}

static void Animate(u8 localId, u8 movement)
{
    u8 id;
    if (!TryGetObjectEventIdByLocalIdAndMap(ResolveLocalId(localId),
        gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, &id))
    {
        ObjectEventClearHeldMovementIfActive(&gObjectEvents[id]);
        ObjectEventSetHeldMovement(&gObjectEvents[id], movement);
    }
}


// Never expose an absent actor to the native script movement opcodes.
static struct ObjectEvent *GetSceneActor(u16 logical)
{
    u8 id, localId;
    if (CurrentCamp() == NULL)
        return NULL;
    if (logical < 7)
        localId = ResolveLocalId(220 + logical);
    else if (logical == 7)
    {
        for (localId = 227; localId <= 230; localId++)
            if (!TryGetObjectEventIdByLocalIdAndMap(localId,
                gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, &id))
            {
                struct ObjectEvent *visitor = &gObjectEvents[id];
                if (visitor->graphicsId < OBJ_EVENT_GFX_MON_BASE
                 && visitor->graphicsId != OBJ_EVENT_GFX_FRIENDS_GIRATINA)
                    return visitor; // The actual clerk/Fuji/researcher first.
            }
        // FG08 uses the real, original Fuji inside his house. It must not
        // focus Mankey (or introduce a second Fuji) for the native speaker.
        if (((gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum)
                == MAP_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE
         && !TryGetObjectEventIdByLocalIdAndMap(1, gSaveBlock1Ptr->location.mapNum,
                gSaveBlock1Ptr->location.mapGroup, &id)
         && gObjectEvents[id].graphicsId == OBJ_EVENT_GFX_MR_FUJI)
            return &gObjectEvents[id];
        return NULL;
    }
    else if (logical >= 227 && logical <= 230)
        localId = logical;
    else
        return NULL;
    if (TryGetObjectEventIdByLocalIdAndMap(localId,
        gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, &id))
        return NULL;
    return &gObjectEvents[id];
}

void Special_FriendsStoryGetActorLocalId(void)
{
    struct ObjectEvent *actor = GetSceneActor(gSpecialVar_0x8004);
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = actor == NULL ? 0 : actor->localId;
}

void Special_FriendsStoryFocusSpeaker(void)
{
    struct ObjectEvent *speaker = GetSceneActor(gSpecialVar_0x8004);
    struct ObjectEvent *listener, *target;
    u8 i;
    Script_RequestEffects(SCREFF_V1 | SCREFF_HARDWARE);
    if (speaker == NULL || ObjectEventCheckHeldMovementStatus(speaker) == 0)
        return;
    // A reply attends to the previous present speaker; the opening addresses
    // the player. Consecutive pages by one speaker keep the same focus.
    target = GetSceneActor(sPreviousSpeaker);
    if (target == NULL || target == speaker)
        target = &gObjectEvents[gPlayerAvatar.objectEventId];
    if (sPreviousSpeaker != gSpecialVar_0x8004)
        ObjectEventTurn(speaker, GetDirectionToFace(speaker->currentCoords.x,
            speaker->currentCoords.y, target->currentCoords.x, target->currentCoords.y));
    sPreviousSpeaker = gSpecialVar_0x8004;
    for (i = 0; i < 7; i++)
    {
        listener = GetSceneActor(i);
        if (listener != NULL && listener != speaker
         && ObjectEventCheckHeldMovementStatus(listener) != 0)
            ObjectEventTurn(listener, GetDirectionToFace(listener->currentCoords.x,
                listener->currentCoords.y, speaker->currentCoords.x, speaker->currentCoords.y));
    }
}


void Special_FriendsStoryStep(void)
{
    struct ObjectEvent *actor = GetSceneActor(gSpecialVar_0x8004);
    s16 x, y;
    u16 direction = gSpecialVar_0x8005;
    Script_RequestEffects(SCREFF_V1 | SCREFF_HARDWARE);
    gSpecialVar_Result = FALSE;
    if (actor == NULL || direction < DIR_SOUTH || direction > DIR_EAST
     || ObjectEventCheckHeldMovementStatus(actor) == 0)
        return;
    x = actor->currentCoords.x;
    y = actor->currentCoords.y;
    MoveCoords(direction, &x, &y);
    // Routes are additionally audited against selected ROM ground/warps.
    // A player, follower or native NPC occupying the next tile aborts only
    // this optional reaction, without forcing another actor out of the way.
    if (MapGridGetCollisionAt(x, y) != 0
     || MapGridGetElevationAt(x, y) != actor->currentElevation
     || GetObjectEventIdByPosition(x, y, actor->currentElevation) != OBJECT_EVENTS_COUNT)
        return;
    ObjectEventClearHeldMovementIfActive(actor);
    gSpecialVar_Result = !ObjectEventSetHeldMovement(actor, GetWalkNormalMovementAction(direction));
}

static bool8 SceneMovementPending(void)
{
    struct ObjectEvent *actor;
    u8 i;
    bool8 pending = FALSE;
    for (i = 0; i < 11; i++)
    {
        actor = GetSceneActor(i < 7 ? i : 227 + i - 7);
        if (actor == NULL)
            continue;
        if (ObjectEventCheckHeldMovementStatus(actor) == 0)
            pending = TRUE;
        else
            ObjectEventClearHeldMovementIfFinished(actor);
    }
    return pending;
}

static void Task_WaitSceneMovement(u8 taskId)
{
    if (sMovementFault != 0)
        DestroyTask(taskId); // Keep script locked for the recorded scene fault.
    else if (!SceneMovementPending())
    {
        DestroyTask(taskId);
        ScriptContext_Enable();
    }
    else if (++gTasks[taskId].data[0] > 96)
    {
        // Stop the task and leave the script locked for diagnosis. No release,
        // menu, Save or scene receipt may follow a half-completed movement.
        sMovementFault = 1;
        DestroyTask(taskId);
    }
}

u16 FriendsScene_GetMovementFault(void)
{
    return sMovementFault;
}

void Special_FriendsStoryWaitMovement(void)
{
    u8 i;
    Script_RequestEffects(SCREFF_V1 | SCREFF_HARDWARE);
    gSpecialVar_Result = FALSE;
    if (sMovementFault != 0)
    {
        gSpecialVar_Result = TRUE; // Explicit diagnostic stop, no receipt.
        return;
    }
    if (!SceneMovementPending())
        return;
    for (i = 0; i < NUM_TASKS; i++)
        if (!gTasks[i].isActive)
        {
            CreateTask(Task_WaitSceneMovement, 79);
            gSpecialVar_Result = TRUE;
            return;
        }
    // Remain script-locked for a concrete allocation failure.
    sMovementFault = 2;
    gSpecialVar_Result = TRUE;
}

void FriendsScene_ClearVisitors(void)
{
    ClearPartners();
    Remove(230);
    FriendsVisuals_HideHome();
}

static void ShowMon(u16 species, u8 slot)
{
    const struct FriendsCamp *camp = CurrentCamp();
    u8 localId = 227 + slot;
    s16 offsetX = slot == 0 ? -2 : slot == 2 ? 2 : 0;
    s16 offsetY = -1;
    if (camp == NULL || slot > 3)
        return;
    if (FriendsStory_GetMapScene() == 21 && (slot == 0 || slot == 2))
    {
        // Conversation pairs sit below the unchanged home artwork and above
        // the native dialogue border. Departure starts one row lower only
        // after closemessage, then takes a real native upward step into view.
        offsetX = slot == 0 ? 2 : 4;
        offsetY = gSpecialVar_0x8005 >= 30 && gSpecialVar_0x8005 <= 36 ? 3 : 2;
    }
    if (slot == 3)
    {
        // Keep the exact native Giratina frame fully onscreen, clear of the
        // home inset and partner columns. Both exceptions use audited dry land.
        offsetX = GiratinaOffsetX(camp);
        offsetY = camp->map == MAP_ECRUTEAK_CITY_HNS ? 0 : -1;
    }
    Remove(localId);
    if (GetObjectEventIdByPosition(MAP_OFFSET + camp->x + offsetX,
        MAP_OFFSET + camp->y + offsetY, 3) != OBJECT_EVENTS_COUNT)
    {
        sMovementFault = 4;
        return;
    }
    sAllowTransient = TRUE;
    // The scripted visitor uses an exact static native frame. Its normal
    // species/follower graphics remain untouched, including existing saves.
    if (SpawnSpecialObjectEventParameterized(species == SPECIES_GIRATINA_ALTERED
        ? OBJ_EVENT_GFX_FRIENDS_GIRATINA : OBJ_EVENT_GFX_MON_BASE + species,
        MOVEMENT_TYPE_FACE_DOWN, localId,
        MAP_OFFSET + camp->x + offsetX,
        MAP_OFFSET + camp->y + offsetY, 3) >= OBJECT_EVENTS_COUNT)
        sMovementFault = 3;
    sAllowTransient = FALSE;
}

static void ShowPair(u16 first, u16 second)
{
    ClearPartners();
    ShowMon(first, 0);
    ShowMon(second, 2);
}

static void ShowHuman(u16 graphicsId, u8 slot)
{
    const struct FriendsCamp *camp = CurrentCamp();
    if (camp == NULL || slot > 2)
        return;
    Remove(227 + slot);
    if (GetObjectEventIdByPosition(MAP_OFFSET + camp->x + (slot == 0 ? -2 : slot == 2 ? 2 : 0),
        MAP_OFFSET + camp->y - 1, 3) != OBJECT_EVENTS_COUNT)
    {
        sMovementFault = 4;
        return;
    }
    sAllowTransient = TRUE;
    if (SpawnSpecialObjectEventParameterized(graphicsId, MOVEMENT_TYPE_FACE_DOWN,
        227 + slot, MAP_OFFSET + camp->x + (slot == 0 ? -2 : slot == 2 ? 2 : 0),
        MAP_OFFSET + camp->y - 1, 3) >= OBJECT_EVENTS_COUNT)
        sMovementFault = 3;
    sAllowTransient = FALSE;
}

void Special_FriendsStoryEndScene(void)
{
    u8 i, id;
    Script_RequestEffects(SCREFF_V1 | SCREFF_HARDWARE);
    ClearPartners();
    Remove(230);
    FriendsVisuals_HideHome();
    sPreviousCrossing = 0;
    sPreviousSpeaker = 0xFF;
    for (i = 220; i < 227; i++)
        if (!TryGetObjectEventIdByLocalIdAndMap(ResolveLocalId(i),
            gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, &id))
            ObjectEventClearHeldMovementIfActive(&gObjectEvents[id]);
}

void Special_FriendsStoryPrepareMenu(void)
{
    Script_RequestEffects(SCREFF_V1 | SCREFF_HARDWARE);
    ClearPartners(); Remove(230);
    FriendsVisuals_HideHome();
}

void Special_FriendsStoryAtFujiHouse(void)
{
    Script_RequestEffects(SCREFF_V1);
    sFujiReturnX = gSaveBlock1Ptr->pos.x;
    sFujiReturnY = gSaveBlock1Ptr->pos.y;
    sFujiStartedInside = ((gSaveBlock1Ptr->location.mapGroup << 8)
        | gSaveBlock1Ptr->location.mapNum) == MAP_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE;
    sFujiContextValid = sFujiStartedInside
        || ((gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum) == MAP_LAVENDER_TOWN;
    sFujiWarpPhase = 0;
    gSpecialVar_0x8007 = 0;
    gSpecialVar_Result = sFujiStartedInside;
}

void Special_FriendsStoryReadFujiReturn(void)
{
    Script_RequestEffects(SCREFF_V1);
    // Map callbacks may use ordinary special variables. Keep this transient
    // return point outside the save, and restore operands only when needed.
    gSpecialVar_0x8009 = sFujiStartedInside;
    gSpecialVar_0x800A = sFujiReturnX;
    gSpecialVar_0x800B = sFujiReturnY;
}

static bool8 FujiWarpHere(u8 phase)
{
    u16 map = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
    return sFujiContextValid && !sFujiStartedInside && FriendsStory_IsReady()
        && FriendsStory_GetStage() == 8 && FriendsStory_GetMapScene() == 8
        && FriendsStory_GetGate(8)
        && ((phase == 1 && map == MAP_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE
              && !FlagGet(FRIENDS_STORY_SEEN_FIRST + 7))
         || (phase == 2 && map == MAP_LAVENDER_TOWN
              && FlagGet(FRIENDS_STORY_SEEN_FIRST + 7)));
}

void Special_FriendsStoryPrepareFujiWarp(void)
{
    u8 phase = gSpecialVar_0x8005;
    u16 map = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = FALSE;
    gSpecialVar_0x8007 = 0;
    sFujiWarpPhase = 0;
    if (!sFujiContextValid || sFujiStartedInside || !FriendsStory_IsReady()
     || FriendsStory_GetStage() != 8 || FriendsStory_GetMapScene() != 8
     || !FriendsStory_GetGate(8))
        return;
    if ((phase == 1 && map == MAP_LAVENDER_TOWN
            && !FlagGet(FRIENDS_STORY_SEEN_FIRST + 7))
     || (phase == 2 && map == MAP_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE
            && FlagGet(FRIENDS_STORY_SEEN_FIRST + 7)))
    {
        // The on-frame marker remains zero until actual destination map setup.
        sFujiWarpPhase = phase;
        gSpecialVar_Result = TRUE;
    }
}

void Special_FriendsStoryConsumeFujiWarp(void)
{
    u8 phase = gSpecialVar_0x8005;
    Script_RequestEffects(SCREFF_V1);
    gSpecialVar_Result = phase == sFujiWarpPhase
        && gSpecialVar_0x8007 == phase && FujiWarpHere(phase);
    // One-shot before any dialogue, native movement or camera acquisition.
    gSpecialVar_0x8007 = 0;
    sFujiWarpPhase = 0;
    if (!gSpecialVar_Result || phase == 2)
        sFujiContextValid = FALSE;
}

void FriendsScene_OnMapLoad(void)
{
    u32 i;
    // Publish only an armed handoff on its actual destination. Both native
    // ON_LOAD and ON_TRANSITION may run; preserve the phase until the fresh
    // on-frame script consumes it. Unrelated map loads cannot replay the visit.
    if (sFujiWarpPhase != 0)
    {
        gSpecialVar_0x8007 = FujiWarpHere(sFujiWarpPhase) ? sFujiWarpPhase : 0;
        if (gSpecialVar_0x8007 == 0)
        {
            sFujiWarpPhase = 0;
            sFujiContextValid = FALSE;
        }
    }
    else
    {
        u16 map = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
        sFujiContextValid = FALSE;
        // These two audited maps do not own8007. Prevent an unrelated native
        // special's stale1/2 from dispatching even an invalid resume. Every
        // other map's special operands remain untouched.
        if (map == MAP_LAVENDER_TOWN || map == MAP_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE)
            gSpecialVar_0x8007 = 0;
    }
    // Called only by actual ON_LOAD/ON_TRANSITION map boundaries. Ordinary
    // scene/menu/battle branches restore framing through the script helper.
    FriendsCamera_OnMapLoad();
    sAllowTransient = FALSE;
    sMovementFault = 0;
    sPreviousSpeaker = 0xFF;
    sPreviousCrossing = 0;
    if (FriendsStory_IsReady() && CurrentCamp() != NULL && gMapHeader.events != NULL)
    {
        // Supported older native6 snapshots have no appended Friends slots.
        // Refresh exactly those seven ROM-owned slots, preserving every native
        // prefix, native actor position, party, bag and unrelated saved field.
        for (i = 0; i < gMapHeader.events->objectEventCount
                && i < ARRAY_COUNT(gSaveBlock1Ptr->objectEventTemplates); i++)
        {
            const struct ObjectEventTemplate *rom = &gMapHeader.events->objectEvents[i];
            struct ObjectEventTemplate *saved = &gSaveBlock1Ptr->objectEventTemplates[i];
            if (rom->localId >= CurrentCamp()->firstLocalId && rom->localId < CurrentCamp()->firstLocalId + 7
             && (saved->localId != rom->localId || saved->graphicsId != rom->graphicsId
              || saved->x != rom->x || saved->y != rom->y || saved->elevation != rom->elevation))
                *saved = *rom;
        }
    }
    // Remove only our audited IDs on our own maps; never another actor.
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        struct ObjectEvent *o = &gObjectEvents[i];
        const struct FriendsCamp *camp = FindCamp(o->mapNum, o->mapGroup);
        if (o->active && camp != NULL
         && ((o->localId >= camp->firstLocalId && o->localId < camp->firstLocalId + 7)
          || (o->localId >= 227 && o->localId <= 230))
         && !FriendsScene_ShouldSpawn(o->localId, o->mapNum, o->mapGroup))
            RemoveObjectEventByLocalIdAndMap(o->localId, o->mapNum, o->mapGroup);
    }
}

static void ShowHome(void)
{
    if (!FriendsVisuals_ShowHome())
        sMovementFault = 5;
}

void Special_FriendsStoryStage(void)
{
    u16 scene = gSpecialVar_0x8004, beat = gSpecialVar_0x8005;
    Script_RequestEffects(SCREFF_V1 | SCREFF_HARDWARE);
    gSpecialVar_Result = FALSE;
    if (CurrentCamp() == NULL || scene != FriendsStory_GetMapScene())
        return;
    if (beat == 0)
    {
        switch (scene)
        {
        case 1: ShowMon(SPECIES_GIRATINA_ALTERED, 3); break;
        case 2: ShowPair(SPECIES_RATTATA, SPECIES_MANKEY); break;
        case 3: ShowPair(SPECIES_JIGGLYPUFF, SPECIES_POLIWAG); break;
        case 4: ShowPair(SPECIES_ODDISH, SPECIES_PSYDUCK); ShowMon(SPECIES_SPEAROW, 1); break;
        case 5: ShowHuman(OBJ_EVENT_GFX_SAILOR_FRLG, 1); break;
        case 6: ShowPair(SPECIES_POLIWAG, SPECIES_JIGGLYPUFF); break;
        case 7: ShowPair(SPECIES_ODDISH, SPECIES_PARAS); break;
        case 8:
            if (((gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum) == MAP_LAVENDER_TOWN)
                ShowHuman(OBJ_EVENT_GFX_MR_FUJI, 1);
            break;
        case 9: ShowPair(SPECIES_SLOWPOKE, SPECIES_KRABBY); ShowMon(SPECIES_GEODUDE, 1); break;
        case 11: case 17: ShowHome(); break;
        case 13: ShowPair(SPECIES_SLOWPOKE, SPECIES_PSYDUCK); break;
        case 14: ShowHuman(OBJ_EVENT_GFX_SCIENTIST, 1); break;
        case 15: ShowPair(SPECIES_PRIMEAPE, SPECIES_HOOTHOOT); break;
        case 16: ShowMon(SPECIES_MURKROW, 0); break;
        case 18: ShowHuman(OBJ_EVENT_GFX_FAT_MAN_FRLG, 1); ShowMon(SPECIES_PIDOVE, 0); break;
        case 19: ShowPair(SPECIES_PRIMEAPE, SPECIES_JIGGLYPUFF); break;
        case 20: ShowPair(SPECIES_WIGGLYTUFF, SPECIES_MURKROW); break;
        case 21:
            ShowHome(); ShowMon(SPECIES_GIRATINA_ALTERED, 3);
            ShowPair(SPECIES_GOLDUCK, SPECIES_FURRET); break;
        case 22: ShowMon(SPECIES_SLOWBRO, 0); break;
        }
    }
    else if (scene == 1 && beat == 19)
    {
        Remove(230); Animate(221, MOVEMENT_ACTION_JUMP_IN_PLACE_DOWN);
    }
    else if (scene == 1 && beat == 90)
    {
        u8 i;
        Remove(230);
        for (i = 220; i < 227; i++) Remove(i);
    }
    else if ((scene == 2 && beat == 22) || (scene == 3 && beat == 19)
          || (scene == 4 && beat == 25) || (scene == 7 && beat == 26)
          || (scene == 9 && beat == 17) || (scene == 13 && beat == 21)
          || (scene == 15 && beat == 23) || (scene == 16 && beat == 5))
    {
        // Animate only newly accepted partners, never recapture one that
        // already belongs to a friend in the immediately preceding dialogue.
        if (scene == 2 || scene == 3 || scene == 9 || scene == 16)
            Animate(227, MOVEMENT_ACTION_ENTER_POKEBALL);
        if (scene == 9 || scene == 13)
            Animate(228, MOVEMENT_ACTION_ENTER_POKEBALL);
        if (scene == 2 || scene == 4 || scene == 7 || scene == 9 || scene == 15)
            Animate(229, MOVEMENT_ACTION_ENTER_POKEBALL);
    }
    else if (scene == 13 && beat == 8)
        ShowMon(SPECIES_SENTRET, 1);
    else if (scene == 8 && beat == 8)
    {
        ClearPartners();
        if (((gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum) == MAP_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE)
            ShowMon(SPECIES_MANKEY, 0);
    }
    else if (scene == 7 && beat == 22)
        ShowHuman(OBJ_EVENT_GFX_FAT_MAN_FRLG, 1);
    else if (scene == 16 && beat == 19)
    {
        ShowPair(SPECIES_PSYDUCK, SPECIES_PRIMEAPE);
        Animate(227, MOVEMENT_ACTION_JUMP_IN_PLACE_DOWN);
        Animate(229, MOVEMENT_ACTION_JUMP_IN_PLACE_DOWN);
    }
    else if ((scene == 11 && beat == 12) || (scene == 17 && beat == 17))
    {
        ShowMon(SPECIES_GIRATINA_ALTERED, 3);
        FriendsVisuals_HideHome();
    }
    else if (scene == 21 && beat >= 30 && beat <= 36)
    {
        u8 pair = beat - 30;
        if (pair == 0)
        {
            ShowHome();
            ShowMon(SPECIES_GIRATINA_ALTERED, 3);
        }
        if (sPreviousCrossing != 0)
            Remove(220 + sDepartureOrder[sPreviousCrossing - 1]);
        ShowPair(sFinalPartners[pair][0], sFinalPartners[pair][1]);
        Animate(227, MOVEMENT_ACTION_WALK_NORMAL_UP);
        Animate(229, MOVEMENT_ACTION_WALK_NORMAL_UP);
        Animate(220 + sDepartureOrder[pair], MOVEMENT_ACTION_WALK_NORMAL_UP);
        sPreviousCrossing = pair + 1;
    }
    else if (scene == 21 && beat == 11)
        ShowPair(SPECIES_RATICATE, SPECIES_SLOWBRO);
    else if (scene == 21 && (beat == 20 || beat == 23))
        ShowPair(SPECIES_PRIMEAPE, SPECIES_NOCTOWL);
    else if (scene == 21 && beat == 37)
    {
        u8 i;
        ClearPartners(); Remove(230); FriendsVisuals_HideHome();
        for (i = 220; i < 227; i++) Remove(i);
        sPreviousCrossing = 0;
    }
    gSpecialVar_Result = TRUE;
}
#endif

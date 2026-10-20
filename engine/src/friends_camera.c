#include "global.h"

#include "friends_camera.h"
#include "friends_scene.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_camera.h"
#include "field_screen_effect.h"
#include "fieldmap.h"
#include "firered_save.h"
#include "script.h"
#include "sprite.h"
#include "task.h"
#include "constants/event_object_movement.h"
#include "constants/event_objects.h"

// Twelve Manhattan tiles cover the audited camp interaction positions. Native
// CameraUpdate scrolls at most one pixel/frame, including during the return.
#define FRAME_MAX_PIXELS (12 * 16)
#define FRAME_SETTLE_FRAMES 2
#define FRAME_MAX_TICKS (FRAME_MAX_PIXELS + 8)

// Snapshot the lockall-era state as well as its native releaseall backups.
#define FOLLOWER_WAS_FROZEN          (1 << 0)
#define FOLLOWER_SPRITE_INVISIBLE    (1 << 1)
#define FOLLOWER_ANIM_PAUSED         (1 << 2)
#define FOLLOWER_AFFINE_PAUSED       (1 << 3)
#define FOLLOWER_ANIM_BACKUP         (1 << 4)
#define FOLLOWER_AFFINE_BACKUP       (1 << 5)

enum CameraPhase
{
    CAMERA_INACTIVE,
    CAMERA_OUTBOUND,
    CAMERA_HOLD,
    CAMERA_RETURNING,
    CAMERA_FAULT,
    CAMERA_RECALLING,
};

enum CameraFault
{
    CAMERA_FAULT_NONE,
    CAMERA_FAULT_OWNERSHIP,
    CAMERA_FAULT_WORLD,
    CAMERA_FAULT_SAVE,
    CAMERA_FAULT_TIMEOUT,
    CAMERA_FAULT_ALIGNMENT,
    CAMERA_FAULT_FOLLOWER,
};

struct FriendsCamera
{
    const struct MapLayout *layout;
    s16 originalFocusX, originalFocusY;
    s16 originalPlayerX, originalPlayerY;
    s16 originalProxyX, originalProxyY;
    s16 offsetX, offsetY;
    s16 targetX, targetY;
    u16 originalOffsetX, originalOffsetY;
    u16 ticks;
    s16 followerX, followerY;
    u16 followerGraphics;
    u8 followerDirection;
    bool8 followerPresent, followerInvisible;
    u8 followerId, followerSpriteId, followerState;
    u8 mapGroup, mapNum;
    u8 playerId, playerSpriteId;
    u8 trackerId, proxyId, taskId;
    u8 phase, settle;
    u8 fault;
};

static EWRAM_DATA struct FriendsCamera sCamera = {0};

static void Task_FriendsCamera(u8 taskId);

static void ProxyCallback(struct Sprite *sprite)
{
    // The task changes the proxy before AnimateSprites and CameraUpdate run.
    // No ObjectEvent, tile/palette allocation, or gameplay movement is needed.
    (void)sprite;
}

static s32 Magnitude(s32 value)
{
    return value < 0 ? -value : value;
}

static bool32 CameraAtRest(void)
{
    return gFieldCamera.x == 0 && gFieldCamera.y == 0
        && gFieldCamera.movementSpeedX == 0 && gFieldCamera.movementSpeedY == 0;
}

static bool32 OwnsTaskAndSprites(void)
{
    return sCamera.taskId < NUM_TASKS && gTasks[sCamera.taskId].isActive
        && gTasks[sCamera.taskId].func == Task_FriendsCamera
        && sCamera.proxyId < MAX_SPRITES && gSprites[sCamera.proxyId].inUse
        && gSprites[sCamera.proxyId].callback == ProxyCallback
        && sCamera.trackerId > 0 && sCamera.trackerId < MAX_SPRITES
        && gFieldCamera.spriteId == sCamera.trackerId
        && gSprites[sCamera.trackerId].inUse && gFieldCamera.callback != NULL;
}

static bool32 SameWorld(void)
{
    return gSaveBlock1Ptr->location.mapGroup == sCamera.mapGroup
        && gSaveBlock1Ptr->location.mapNum == sCamera.mapNum
        && gMapHeader.mapLayout == sCamera.layout
        && gPlayerAvatar.objectEventId == sCamera.playerId
        && gPlayerAvatar.spriteId == sCamera.playerSpriteId
        && sCamera.playerId < OBJECT_EVENTS_COUNT
        && gObjectEvents[sCamera.playerId].active
        && gObjectEvents[sCamera.playerId].isPlayer
        && gObjectEvents[sCamera.playerId].currentCoords.x == sCamera.originalPlayerX
        && gObjectEvents[sCamera.playerId].currentCoords.y == sCamera.originalPlayerY
        && ArePlayerFieldControlsLocked();
}

static void Fault(u8 reason)
{
    // Never resume a caller into a menu/battle/release with displaced focus.
    // This is an explicit diagnostic stop, not a teleport or a save repair.
    sCamera.fault = reason;
    sCamera.phase = CAMERA_FAULT;
}

static bool32 FocusIsSafe(s16 x, s16 y)
{
    u32 i;
    if (x < 0 || y < 0 || x >= gMapHeader.mapLayout->width
        || y >= gMapHeader.mapLayout->height)
        return FALSE;
    // CameraUpdate normally starts growth for newly visible berry trees. A
    // cinematic must not produce that unrelated persistent side effect.
    if (gMapHeader.events != NULL)
        for (i = 0; i < gMapHeader.events->objectEventCount; i++)
        {
            const struct ObjectEventTemplate *object = &gMapHeader.events->objectEvents[i];
            if (object->movementType == MOVEMENT_TYPE_BERRY_TREE_GROWTH
             && object->x >= x - 7 && object->x <= x + 7
             && object->y >= y - 4 && object->y <= y + 4)
                return FALSE;
        }
    return TRUE;
}

static bool32 PathIsSafe(s16 startX, s16 startY, s16 targetX, s16 targetY)
{
    if (Magnitude(targetX - startX) + Magnitude(targetY - startY) > FRAME_MAX_PIXELS / 16)
        return FALSE;
    for (;;)
    {
        if (!FocusIsSafe(startX, startY))
            return FALSE;
        if (startX != targetX)
            startX += startX < targetX ? 1 : -1;
        else if (startY != targetY)
            startY += startY < targetY ? 1 : -1;
        else
            return TRUE;
    }
}

static bool32 FocusMatches(s16 offsetX, s16 offsetY)
{
    return gSaveBlock1Ptr->pos.x == sCamera.originalFocusX + offsetX / 16
        && gSaveBlock1Ptr->pos.y == sCamera.originalFocusY + offsetY / 16
        && gTotalCameraPixelOffsetX == (u16)(sCamera.originalOffsetX - offsetX)
        && gTotalCameraPixelOffsetY == (u16)(sCamera.originalOffsetY - offsetY);
}

static struct ObjectEvent *OwnedFollower(void)
{
    struct ObjectEvent *follower;
    if (!sCamera.followerPresent || sCamera.followerId >= OBJECT_EVENTS_COUNT
     || sCamera.followerSpriteId >= MAX_SPRITES)
        return NULL;
    follower = &gObjectEvents[sCamera.followerId];
    if (!follower->active || follower->localId != OBJ_EVENT_ID_FOLLOWER
     || follower->spriteId != sCamera.followerSpriteId
     || follower->graphicsId != sCamera.followerGraphics
     || !gSprites[sCamera.followerSpriteId].inUse
     || GetFollowerObject() != follower)
        return NULL;
    return follower;
}

static bool32 PinFollower(void)
{
    struct ObjectEvent *follower = OwnedFollower();
    struct Sprite *sprite;
    if (follower == NULL)
        return FALSE;
    sprite = &gSprites[follower->spriteId];
    // Retain this exact native object, sprite, sheet and palette. Freeing the
    // large sheet here let camera-spawned NPCs fragment its return allocation.
    ClearObjectEventMovement(follower, sprite);
    FreezeObjectEvent(follower);
    follower->invisible = TRUE;
    sprite->invisible = TRUE;
    // An invisible recalled actor must not occupy a future visitor/walk cell.
    // The unchanged player's tile is excluded by every scene preflight; retain
    // the original follower coordinates separately for exact normal return.
    MoveObjectEventToMapCoords(follower, sCamera.originalPlayerX, sCamera.originalPlayerY);
    return follower->frozen;
}

static bool32 FollowerIsPinned(void)
{
    struct ObjectEvent *follower;
    if (!sCamera.followerPresent)
        return TRUE;
    follower = OwnedFollower();
    return follower != NULL && follower->frozen && follower->invisible
        && gSprites[follower->spriteId].invisible;
}

static bool32 RestoreFollower(void)
{
    struct ObjectEvent *follower;
    struct Sprite *sprite;
    if (!sCamera.followerPresent)
        return TRUE;
    follower = OwnedFollower();
    if (follower == NULL || !FollowerIsPinned())
        return FALSE;
    sprite = &gSprites[follower->spriteId];
    // No spawn, sheet allocation, option toggle or Pokemon mutation occurs.
    // Restore at the exact inverse camera endpoint while field input is locked.
    ClearObjectEventMovement(follower, sprite);
    MoveObjectEventToMapCoords(follower, sCamera.followerX, sCamera.followerY);
    ObjectEventTurn(follower, sCamera.followerDirection);
    follower->invisible = sCamera.followerInvisible;
    follower->frozen = !!(sCamera.followerState & FOLLOWER_WAS_FROZEN);
    follower->spriteAnimPausedBackup = !!(sCamera.followerState & FOLLOWER_ANIM_BACKUP);
    follower->spriteAffineAnimPausedBackup = !!(sCamera.followerState & FOLLOWER_AFFINE_BACKUP);
    sprite->invisible = !!(sCamera.followerState & FOLLOWER_SPRITE_INVISIBLE);
    sprite->animPaused = !!(sCamera.followerState & FOLLOWER_ANIM_PAUSED);
    sprite->affineAnimPaused = !!(sCamera.followerState & FOLLOWER_AFFINE_PAUSED);
    sCamera.followerPresent = FALSE;
    return TRUE;
}

static void Task_FriendsCamera(u8 taskId)
{
    if (sCamera.phase == CAMERA_FAULT || sCamera.phase == CAMERA_INACTIVE)
        return;
    if (!OwnsTaskAndSprites() || taskId != sCamera.taskId)
    {
        Fault(CAMERA_FAULT_OWNERSHIP);
        return;
    }
    if (!SameWorld())
    {
        Fault(CAMERA_FAULT_WORLD);
        return;
    }
    if (FireRedSave_IsBusy())
    {
        Fault(CAMERA_FAULT_SAVE);
        return;
    }
    if (sCamera.phase != CAMERA_RECALLING && !FollowerIsPinned())
    {
        Fault(CAMERA_FAULT_FOLLOWER);
        return;
    }
    if (sCamera.phase == CAMERA_HOLD)
        return;
    if (sCamera.phase == CAMERA_RECALLING)
    {
        struct ObjectEvent *follower = OwnedFollower();
        if (follower == NULL || ++sCamera.ticks > 48)
        {
            Fault(CAMERA_FAULT_FOLLOWER);
            return;
        }
        if (ObjectEventCheckHeldMovementStatus(follower) == 0)
            return;
        // The native ball-entry animation restores the original art/palette.
        // Keep that allocation reserved invisibly until the inverse pan ends.
        if (!PinFollower())
        {
            Fault(CAMERA_FAULT_FOLLOWER);
            return;
        }
        sCamera.ticks = 0;
        sCamera.phase = CAMERA_OUTBOUND;
        return;
    }
    if (++sCamera.ticks > FRAME_MAX_TICKS)
    {
        Fault(CAMERA_FAULT_TIMEOUT);
        return;
    }
    // Reverse the outbound X-then-Y path in Y-then-X order. The safe-focus
    // preflight therefore covers the return, including berry visibility.
    if (sCamera.phase == CAMERA_RETURNING && sCamera.offsetY != sCamera.targetY)
    {
        s16 step = sCamera.offsetY < sCamera.targetY ? 1 : -1;
        sCamera.offsetY += step;
        gSprites[sCamera.proxyId].y += step;
        sCamera.settle = 0;
        return;
    }
    if (sCamera.offsetX != sCamera.targetX)
    {
        s16 step = sCamera.offsetX < sCamera.targetX ? 1 : -1;
        sCamera.offsetX += step;
        gSprites[sCamera.proxyId].x += step;
        sCamera.settle = 0;
        return;
    }
    if (sCamera.offsetY != sCamera.targetY)
    {
        s16 step = sCamera.offsetY < sCamera.targetY ? 1 : -1;
        sCamera.offsetY += step;
        gSprites[sCamera.proxyId].y += step;
        sCamera.settle = 0;
        return;
    }
    // RunTasks precedes AnimateSprites/CameraUpdate. Wait for the final delta
    // and a zero-delta frame to be consumed before resuming script execution.
    if (++sCamera.settle < FRAME_SETTLE_FRAMES || !CameraAtRest())
        return;
    if (!FocusMatches(sCamera.targetX, sCamera.targetY))
    {
        Fault(CAMERA_FAULT_ALIGNMENT);
        return;
    }
    if (sCamera.phase == CAMERA_RETURNING)
    {
        if (gSprites[sCamera.proxyId].x != sCamera.originalProxyX
         || gSprites[sCamera.proxyId].y != sCamera.originalProxyY)
        {
            Fault(CAMERA_FAULT_ALIGNMENT);
            return;
        }
        // Rebinding is safe only after the inverse pan actually restored the
        // native focus, cache offsets, and original proxy pixel coordinates.
        if (!RestoreFollower())
        {
            Fault(CAMERA_FAULT_FOLLOWER);
            return;
        }
        CameraObjectSetFollowedSpriteId(sCamera.playerSpriteId);
        DestroySprite(&gSprites[sCamera.proxyId]);
        sCamera.phase = CAMERA_INACTIVE;
        DestroyTask(taskId);
    }
    else
        sCamera.phase = CAMERA_HOLD;
    ScriptContext_Enable();
}

void Special_FriendsCameraBegin(void)
{
    s16 x, y;
    u32 proxy;
    u8 i, task;
    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE | SCREFF_HARDWARE);
    gSpecialVar_Result = FALSE;
    // Fixed native Friends choice windows keep the locked cinematic context.
    // A valid settled HOLD already owns its camera/follower resources; callers
    // resume synchronously rather than waiting for another completion signal.
    if (sCamera.phase == CAMERA_HOLD)
    {
        if (!FireRedSave_IsBusy() && OwnsTaskAndSprites() && SameWorld()
         && CameraAtRest() && FocusMatches(sCamera.targetX, sCamera.targetY)
         && FollowerIsPinned())
            gSpecialVar_Result = 2;
        return;
    }
    if (sCamera.phase != CAMERA_INACTIVE || FireRedSave_IsBusy()
     || !ArePlayerFieldControlsLocked() || !IsPlayerStandingStill()
     || !CameraAtRest() || gMapHeader.mapLayout == NULL
     || gPlayerAvatar.objectEventId >= OBJECT_EVENTS_COUNT
     || gPlayerAvatar.spriteId >= MAX_SPRITES
     || !gObjectEvents[gPlayerAvatar.objectEventId].active
     || !gObjectEvents[gPlayerAvatar.objectEventId].isPlayer
     || gObjectEvents[gPlayerAvatar.objectEventId].currentCoords.x != gSaveBlock1Ptr->pos.x + MAP_OFFSET
     || gObjectEvents[gPlayerAvatar.objectEventId].currentCoords.y != gSaveBlock1Ptr->pos.y + MAP_OFFSET
     || gObjectEvents[gPlayerAvatar.objectEventId].spriteId != gPlayerAvatar.spriteId
     || !gSprites[gPlayerAvatar.spriteId].inUse
     || gFieldCamera.spriteId == 0 || gFieldCamera.spriteId >= MAX_SPRITES
     || !gSprites[gFieldCamera.spriteId].inUse || gFieldCamera.callback == NULL
     || !FriendsScene_GetFramePoint(&x, &y)
     || !PathIsSafe(gSaveBlock1Ptr->pos.x, gSaveBlock1Ptr->pos.y, x, y))
        return;
    // Native CreateTask asserts/returns slot0 when full; preflight capacity
    // before creating either resource. No other task runs during this call.
    for (i = 0; i < NUM_TASKS; i++)
        if (!gTasks[i].isActive)
            break;
    if (i == NUM_TASKS)
        return;
    proxy = CreateSpriteUnchecked(&gDummySpriteTemplate,
        gSprites[gPlayerAvatar.spriteId].x, gSprites[gPlayerAvatar.spriteId].y, 31);
    if (proxy == MAX_SPRITES)
        return;
    task = CreateTask(Task_FriendsCamera, 80);
    memset(&sCamera, 0, sizeof(sCamera));
    sCamera.layout = gMapHeader.mapLayout;
    sCamera.originalFocusX = gSaveBlock1Ptr->pos.x;
    sCamera.originalFocusY = gSaveBlock1Ptr->pos.y;
    sCamera.originalOffsetX = gTotalCameraPixelOffsetX;
    sCamera.originalOffsetY = gTotalCameraPixelOffsetY;
    sCamera.originalPlayerX = gObjectEvents[gPlayerAvatar.objectEventId].currentCoords.x;
    sCamera.originalPlayerY = gObjectEvents[gPlayerAvatar.objectEventId].currentCoords.y;
    sCamera.originalProxyX = gSprites[proxy].x;
    sCamera.originalProxyY = gSprites[proxy].y;
    sCamera.targetX = (x - sCamera.originalFocusX) * 16;
    sCamera.targetY = (y - sCamera.originalFocusY) * 16;
    sCamera.mapGroup = gSaveBlock1Ptr->location.mapGroup;
    sCamera.mapNum = gSaveBlock1Ptr->location.mapNum;
    sCamera.playerId = gPlayerAvatar.objectEventId;
    sCamera.playerSpriteId = gPlayerAvatar.spriteId;
    sCamera.trackerId = gFieldCamera.spriteId;
    sCamera.proxyId = proxy;
    sCamera.taskId = task;
    gSprites[proxy].callback = ProxyCallback;
    gSprites[proxy].invisible = TRUE;
    CameraObjectSetFollowedSpriteId(proxy);
    sCamera.phase = CAMERA_OUTBOUND;
    {
        struct ObjectEvent *follower = GetFollowerObject();
        if (follower != NULL)
        {
            sCamera.followerPresent = TRUE;
            sCamera.followerX = follower->currentCoords.x;
            sCamera.followerY = follower->currentCoords.y;
            sCamera.followerDirection = follower->facingDirection;
            sCamera.followerInvisible = follower->invisible;
            struct Sprite *sprite = &gSprites[follower->spriteId];
            sCamera.followerGraphics = follower->graphicsId;
            sCamera.followerId = follower - gObjectEvents;
            sCamera.followerSpriteId = follower->spriteId;
            sCamera.followerState = (follower->frozen ? FOLLOWER_WAS_FROZEN : 0)
                | (sprite->invisible ? FOLLOWER_SPRITE_INVISIBLE : 0)
                | (sprite->animPaused ? FOLLOWER_ANIM_PAUSED : 0)
                | (sprite->affineAnimPaused ? FOLLOWER_AFFINE_PAUSED : 0)
                | (follower->spriteAnimPausedBackup ? FOLLOWER_ANIM_BACKUP : 0)
                | (follower->spriteAffineAnimPausedBackup ? FOLLOWER_AFFINE_BACKUP : 0);
            if (follower->invisible)
            {
                if (!PinFollower())
                {
                    Fault(CAMERA_FAULT_FOLLOWER);
                    gSpecialVar_Result = TRUE;
                    return;
                }
            }
            else
            {
                // Native follower idle uses singleMovementActive. Its own
                // return-to-ball transition clears that movement first too.
                ClearObjectEventMovement(follower, &gSprites[follower->spriteId]);
                if (ObjectEventSetHeldMovement(follower, MOVEMENT_ACTION_ENTER_POKEBALL))
                {
                    Fault(CAMERA_FAULT_FOLLOWER);
                    gSpecialVar_Result = TRUE;
                    return;
                }
                sCamera.phase = CAMERA_RECALLING;
            }
        }
    }
    gSpecialVar_Result = TRUE;
}

void Special_FriendsCameraReturn(void)
{
    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE | SCREFF_HARDWARE);
    gSpecialVar_Result = sCamera.phase != CAMERA_INACTIVE;
    if (sCamera.phase == CAMERA_INACTIVE || sCamera.phase == CAMERA_FAULT)
        return;
    // Keep the task reserved throughout HOLD, so return never allocates. All
    // normal entry paths call this only after Begin's asynchronous completion.
    if (sCamera.phase != CAMERA_HOLD || !OwnsTaskAndSprites())
    {
        Fault(CAMERA_FAULT_OWNERSHIP);
        return;
    }
    // Release only owned temporary visitors before the inverse pan can spawn
    // ordinary NPCs. The retained follower never needs a return allocation.
    // Battle/warp/field release/Save regain normal field resources;
    // fixed native story choice windows retain HOLD until one of those exits.
    FriendsScene_ClearVisitors();
    sCamera.targetX = 0;
    sCamera.targetY = 0;
    sCamera.ticks = 0;
    sCamera.settle = 0;
    sCamera.phase = CAMERA_RETURNING;
}

void FriendsCamera_OnMapLoad(void)
{
    // Map setup resets native sprites/tasks/camera. IDs can already have been
    // reused; never destroy them or restore an old map's focus at this boundary.
    memset(&sCamera, 0, sizeof(sCamera));
}

u16 FriendsCamera_GetFault(void)
{
    return sCamera.fault;
}

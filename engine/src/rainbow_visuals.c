#include "global.h"
#ifdef FIRERED
#include "battle.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_effect.h"
#include "palette.h"
#include "malloc.h"
#include "pokemon.h"
#include "rainbow_visuals.h"
#include "rainbow_story.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "constants/event_objects.h"
#include "constants/map_groups.h"
#include "constants/johto_ids.h"
#include "constants/rainbow_story.h"
#include "constants/species.h"
#include "constants/rgb.h"

// Private presentation tags. Normal species and NPC palette tables are not edited.
#define CORRUPT_PAL_TAG 0x3F40
static EWRAM_DATA u8 sEncounterVisual = 0;
static const u16 sEncounterSpecies[] = {SPECIES_NONE, SPECIES_ARTICUNO, SPECIES_ZAPDOS, SPECIES_MOLTRES, SPECIES_LUGIA};
// Original scene palettes: dark violet bodies, cold/violent accents and red eyes.
// They affect only the scripted opponent, never the Pokemon's stored identity.
// Bound to qualified FireRed's P_GBA_STYLE_SPECIES_GFX=TRUE palette indices.
static const u16 sBattlePalettes[4][16] = {
    {RGB(0,0,0),RGB(25,19,31),RGB(20,13,29),RGB(15,8,24),RGB(10,5,18),RGB(6,3,12),RGB(3,2,6),RGB(31,0,31),RGB(31,0,31),RGB(25,25,29),RGB(16,16,23),RGB(9,8,16),RGB(31,3,8),RGB(31,12,20),RGB(2,2,3),RGB(29,29,31)},
    {RGB(0,0,0),RGB(29,29,31),RGB(23,23,27),RGB(15,15,21),RGB(8,7,13),RGB(2,2,3),RGB(31,0,31),RGB(31,0,31),RGB(20,10,29),RGB(14,5,23),RGB(13,4,10),RGB(30,20,31),RGB(28,7,29),RGB(20,4,23),RGB(12,3,17),RGB(7,2,9)},
    {RGB(0,0,0),RGB(29,29,31),RGB(22,22,27),RGB(14,2,16),RGB(24,14,30),RGB(29,8,28),RGB(31,6,18),RGB(18,2,23),RGB(20,8,28),RGB(14,4,22),RGB(7,2,13),RGB(31,25,31),RGB(30,15,30),RGB(28,6,25),RGB(13,3,18),RGB(2,2,3)},
    {RGB(0,0,0),RGB(13,7,22),RGB(10,5,18),RGB(7,3,14),RGB(5,2,10),RGB(3,2,6),RGB(29,29,31),RGB(24,25,28),RGB(18,19,23),RGB(10,10,16),RGB(31,3,8),RGB(20,1,5),RGB(6,3,12),RGB(3,2,6),RGB(2,1,4),RGB(2,1,4)}
};
static const u16 sLugiaFieldPalette[16] = {
    RGB(0,0,0),RGB(2,1,4),RGB(3,2,7),RGB(13,7,22),RGB(10,5,18),RGB(7,3,14),RGB(16,17,23),RGB(24,25,28),RGB(29,29,31),RGB(20,21,26),
    RGB(0,0,0),RGB(0,0,0),RGB(0,0,0),RGB(0,0,0),RGB(0,0,0),RGB(0,0,0)
};
// Legacy 32x32 NPC images share this index convention; Lugia's white index14
// becomes violet while its original blue wing/chest marks become silver.
static const u16 sFieldPalette[16] = {
    RGB(0,0,0),RGB(27,5,12),RGB(20,3,10),RGB(13,2,9),RGB(5,2,7),RGB(31,5,14),RGB(22,3,13),RGB(12,2,9),
    RGB(28,28,31),RGB(21,21,27),RGB(3,2,7),RGB(13,7,23),RGB(9,4,17),RGB(5,2,11),RGB(17,10,27),RGB(1,1,3)
};

// Original code-native eight-pixel prism: no legendary actor for the
// already-resolved/ambiguous welcome alternate, and no global palette fade.
static const u32 sPrismTile[8] = {0x00010000,0x00010000,0x00111000,0x11111110,0x00111000,0x00010000,0x00010000,0};
static const u16 sPrismPalette[16] = {0,RGB(31,20,4),RGB(31,6,12),RGB(12,31,18),RGB(14,20,31),RGB(31,31,31)};
static const struct SpriteFrameImage sPrismImages[] = {{.data = (const u8 *)sPrismTile, .size = 32}};
static const struct OamData sPrismOam = {0};
static const struct SpriteTemplate sPrismTemplate = {
    .tileTag = TAG_NONE, .paletteTag = CORRUPT_PAL_TAG + 2, .oam = &sPrismOam,
    .anims = gDummySpriteAnimTable, .images = sPrismImages,
    .affineAnims = gDummySpriteAffineAnimTable, .callback = SpriteCallbackDummy
};

static bool32 InWhirlChamber(void)
{
    return gSaveBlock1Ptr != NULL
        && gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_WHIRL_ISLANDS_LUGIA_CHAMBER_HNS)
        && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_WHIRL_ISLANDS_LUGIA_CHAMBER_HNS);
}

void RainbowVisuals_BeginEncounter(void)
{
    sEncounterVisual = InWhirlChamber() && gSpecialVar_0x8004 >= 1 && gSpecialVar_0x8004 <= 4 ? gSpecialVar_0x8004 : 0;
}

void RainbowVisuals_EndEncounter(void)
{
    sEncounterVisual = 0;
}

static bool32 IsCorruptOpponent(u32 battler, u32 species)
{
    return sEncounterVisual != 0 && sEncounterVisual <= 4 && InWhirlChamber()
        && !(gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        && !IsOnPlayerSide(battler) && species == sEncounterSpecies[sEncounterVisual]
        && gBattleOutcome != B_OUTCOME_CAUGHT;
}

const u16 *RainbowVisuals_BattlePalette(u32 battler, u32 species, const u16 *ordinary)
{
    return IsCorruptOpponent(battler, species) ? sBattlePalettes[sEncounterVisual - 1] : ordinary;
}

static u32 PixelOffset(u32 x, u32 y)
{
    return ((y >> 3) * 8 + (x >> 3)) * 32 + (y & 7) * 4 + ((x & 7) >> 1);
}

void RainbowVisuals_PatchBattleGfx(u32 battler, u32 species, void *tiles)
{
    u32 frame, x, y;
    u8 *data = tiles;
    if (!IsCorruptOpponent(battler, species) || species != SPECIES_LUGIA)
        return;
    // Two existing 64x64 front frames. Add angular silver wing bands and a
    // violet mask within the existing opaque silhouette; never touch back pics.
    for (frame = 0; frame < 2; frame++)
    {
        u8 *pic = data + frame * 2048;
        for (y = 12; y < 41; y++)
        {
            for (x = 4; x < 59; x++)
            {
                u32 offset = PixelOffset(x, y);
                u32 shift = (x & 1) * 4;
                u32 color = (pic[offset] >> shift) & 15;
                bool32 band = (x < 25 && 3 * y >= x + 52 && 3 * y <= x + 60)
                    || (x > 39 && x + 3 * y >= 117 && x + 3 * y <= 125);
                if (color != 0 && color < 14 && band)
                    pic[offset] = (pic[offset] & ~(15 << shift)) | (6 << shift);
            }
        }
    }
}

// Shared renderer core: never reads or changes script scratch variables.
static void ApplyCorruptionToObject(struct ObjectEvent *object, u32 kind)
{
    u8 oldPalette, newPalette;
    struct Sprite *sprite;
    struct SpritePalette palette = {sFieldPalette, CORRUPT_PAL_TAG};
    const struct ObjectEventGraphicsInfo *graphicsInfo;
    if (object->spriteId >= MAX_SPRITES || !gSprites[object->spriteId].inUse)
        return;
    sprite = &gSprites[object->spriteId];
    oldPalette = sprite->oam.paletteNum;
    if (kind == 0)
    {
        if (GetSpritePaletteTagByPaletteNum(oldPalette) >= CORRUPT_PAL_TAG && GetSpritePaletteTagByPaletteNum(oldPalette) < CORRUPT_PAL_TAG + 4)
        {
            graphicsInfo = GetObjectEventGraphicsInfo(object->graphicsId);
            if (object->graphicsId & OBJ_EVENT_MON)
            {
                u32 species = object->graphicsId & OBJ_EVENT_MON_SPECIES_MASK;
                struct SpritePalette ordinary = {gSpeciesInfo[species].overworldPalette, species + OBJ_EVENT_MON};
                newPalette = LoadSpritePalette(&ordinary);
            }
            else
                newPalette = LoadObjectEventPalette(graphicsInfo->paletteTag);
            if (newPalette < 16)
            {
                sprite->oam.paletteNum = newPalette;
                FieldEffectFreePaletteIfUnused(oldPalette);
            }
        }
        return;
    }
    // One common legacy palette fits simultaneous replicas + Lugia. The
    // native 64x64 Lugia has another index scheme and appears after they leave.
    if (kind == RAINBOW_VISUAL_LUGIA && (object->graphicsId & OBJ_EVENT_MON))
    {
        palette.data = sLugiaFieldPalette;
        palette.tag++;
    }
    newPalette = LoadSpritePalette(&palette);
    if (newPalette < 16)
    {
        sprite->oam.paletteNum = newPalette;
        if (oldPalette != newPalette)
            FieldEffectFreePaletteIfUnused(oldPalette);
    }
}

void RainbowVisuals_ApplyCorruption(void)
{
    u8 objectId;
    if (!InWhirlChamber() || gSpecialVar_0x8004 > 4
        || TryGetObjectEventIdByLocalIdAndMap(gSpecialVar_0x8005, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, &objectId))
        return;
    ApplyCorruptionToObject(&gObjectEvents[objectId], gSpecialVar_0x8004);
}

void RainbowVisuals_OnObjectSpawn(u8 objectId)
{
    static const u16 replicaGraphics[] = {OBJ_EVENT_GFX_ARTICUNO, OBJ_EVENT_GFX_ZAPDOS, OBJ_EVENT_GFX_MOLTRES};
    struct ObjectEvent *object;
    u32 replica;
    u16 lugia;
    // Camera-scroll spawning does not run map/menu/battle return scripts.
    // These are read-only guards; do not adopt state or manufacture receipts.
    if (objectId >= OBJECT_EVENTS_COUNT || !InWhirlChamber())
        return;
    object = &gObjectEvents[objectId];
    if (!object->active
        || object->mapGroup != MAP_GROUP(MAP_WHIRL_ISLANDS_LUGIA_CHAMBER_HNS)
        || object->mapNum != MAP_NUM(MAP_WHIRL_ISLANDS_LUGIA_CHAMBER_HNS)
        || !RainbowStory_IsReady() || !FlagGet(FLAG_LG_ATTACK_SEEN)
        || FlagGet(FLAG_LG_FINAL_RESOLVED) || FlagGet(FLAG_LG_LEGACY_EXEMPT))
        return;
    lugia = VarGet(JOHTO_VAR_COMPLETED_LUGIA);
    if (lugia != 2 && lugia != 4)
        return;
    if (object->localId >= 9 && object->localId <= 11)
    {
        replica = object->localId - 9;
        if (object->graphicsId == replicaGraphics[replica]
            && RainbowStory_GetReplicaResult(replica) == LG_REPLICA_UNRESOLVED)
            ApplyCorruptionToObject(object, replica + 1);
    }
    else if (object->localId == 1 && object->graphicsId == OBJ_EVENT_GFX_SPECIES(LUGIA)
        && RainbowStory_AllReplicasResolved())
        ApplyCorruptionToObject(object, RAINBOW_VISUAL_LUGIA);
}

static void FinishSkyTask(u8 taskId, bool32 completed)
{
    u8 spriteId = gTasks[taskId].data[0];
    if (spriteId < MAX_SPRITES && gSprites[spriteId].inUse && gSprites[spriteId].data[7] == 0x5257)
        FieldEffectFreeGraphicsResources(&gSprites[spriteId]);
    DestroyTask(taskId);
    gSpecialVar_Result = completed;
    ScriptContext_Enable();
}

static void Task_SkyVisit(u8 taskId)
{
    struct Task *task = &gTasks[taskId];
    struct Sprite *sprite = &gSprites[task->data[0]];
    s16 time = ++task->data[1];
    if (!sprite->inUse || sprite->data[7] != 0x5257
        || gSaveBlock1Ptr->location.mapNum != task->data[4]
        || gSaveBlock1Ptr->location.mapGroup != task->data[5])
    {
        FinishSkyTask(taskId, FALSE);
        return;
    }
    if (task->data[2] == 0)
    {
        sprite->x--;
        sprite->y2 = (time & 16) ? -1 : 0;
        if (time == 80)
            PlayCry_Normal(SPECIES_HO_OH, -20);
        if (time >= 288)
            FinishSkyTask(taskId, TRUE);
    }
    else
    {
        if (task->data[2] == 3)
        {
            u32 color = 1 + ((time / 16) % 5);
            LoadPalette(&sPrismPalette[color], OBJ_PLTT_ID(sprite->oam.paletteNum) + 1, sizeof(u16));
            sprite->x2 = ((time / 8) & 3) * 12 - 18;
        }
        sprite->invisible = time > task->data[3] - 16 && (time & 2);
        if (time >= task->data[3])
            FinishSkyTask(taskId, TRUE);
    }
}

static void StartSkyVisit(u32 kind)
{
    u8 taskId, spriteId, i;
    u16 paletteTag;
    u16 graphics = kind == 0 ? OBJ_EVENT_GFX_HOOH : (kind == 1 ? OBJ_EVENT_GFX_SPECIES(MEW) : OBJ_EVENT_GFX_SPECIES(MEWTWO));
    gSpecialVar_Result = 0;
    for (i = 0; i < NUM_TASKS && gTasks[i].isActive; i++);
    if (i == NUM_TASKS || FuncIsActiveTask(Task_SkyVisit))
        return;
    paletteTag = kind == 3 ? CORRUPT_PAL_TAG + 2 : (kind == 0 ? OBJ_EVENT_PAL_TAG_HO_OH : graphics);
    if (IndexOfSpritePaletteTag(paletteTag) == 0xFF)
    {
        for (i = gReservedSpritePaletteCount; i < 16 && GetSpritePaletteTagByPaletteNum(i) != TAG_NONE; i++);
        if (i == 16)
            return;
    }
    if (kind == 3)
    {
        const struct SpritePalette palette = {sPrismPalette, CORRUPT_PAL_TAG + 2};
        if (LoadSpritePalette(&palette) >= 16)
            return;
        spriteId = CreateSprite(&sPrismTemplate, 120, 32, 0);
    }
    else
    {
        const struct MemBlock *head = HeapHead(), *block = head;
        u32 needed = kind == 0 ? 64 : 3200;
        if (head == NULL)
            return;
        // The existing object helper allocates a template and decompresses the
        // small follower sheet. Defer safely instead of invoking its assertion.
        do
        {
            if (!block->allocated && block->size >= needed)
                break;
            block = block->next;
        } while (block != head);
        if (block == head && (block->allocated || block->size < needed))
            return;
        spriteId = CreateObjectGraphicsSprite(graphics, SpriteCallbackDummy, kind == 0 ? 260 : (kind == 1 ? 204 : 140), kind == 0 ? 40 : 48, 0);
    }
    if (spriteId >= MAX_SPRITES)
    {
        u8 palette = IndexOfSpritePaletteTag(paletteTag);
        if (palette < 16)
            FieldEffectFreePaletteIfUnused(palette);
        if (kind == 1 || kind == 2)
        {
            u16 tiles = GetSpriteTileStartByTag((u16)(COMP_OW_TILE_TAG_BASE + graphics));
            if (tiles != TAG_NONE)
                FieldEffectFreeTilesIfUnused(tiles);
        }
        return;
    }
    if (gSprites[spriteId].usingSheet && gSprites[spriteId].sheetTileStart == TAG_NONE)
    {
        FieldEffectFreeGraphicsResources(&gSprites[spriteId]);
        return;
    }
    taskId = CreateTask(Task_SkyVisit, 80);
    gTasks[taskId].data[0] = spriteId;
    gTasks[taskId].data[2] = kind;
    gTasks[taskId].data[3] = kind == 1 ? 64 : 120;
    gTasks[taskId].data[4] = gSaveBlock1Ptr->location.mapNum;
    gTasks[taskId].data[5] = gSaveBlock1Ptr->location.mapGroup;
    gSprites[spriteId].data[7] = 0x5257;
    gSprites[spriteId].oam.priority = 0;
    if (kind == 0)
        StartSpriteAnim(&gSprites[spriteId], ANIM_STD_GO_SOUTH);
    gSpecialVar_Result = 1;
}

void Special_RainbowHoOhFlyby(void)
{
    StartSkyVisit(0);
}

void Special_RainbowMewGlimpse(void)
{
    StartSkyVisit(gSpecialVar_0x8004 >= 2 ? 3 : (gSpecialVar_0x8004 ? 2 : 1));
}
#endif

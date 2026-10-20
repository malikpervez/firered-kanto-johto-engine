#include "global.h"

#include "friends_visuals.h"
#include "bg.h"
#include "decompress.h"
#include "malloc.h"
#include "menu.h"
#include "palette.h"
#include "task.h"
#include "tilesets.h"
#include "window.h"
#include "constants/rgb.h"

// Facility is a pinned native art donor, but its world-map Tileset descriptor
// is not selected by the FireRed build. Register only the immutable visual
// inputs here; this record never becomes a playable map or changes a tileset.
static const u32 sFriendsFacilityTiles[] = INCBIN_U32("data/tilesets/secondary/facility/tiles.4bpp.fastSmol");
static const u16 sFriendsFacilityMetatiles[] = INCBIN_U16("data/tilesets/secondary/facility/metatiles.bin");
static const u16 sFriendsFacilityPalettes[][16] = {
    INCBIN_U16("data/tilesets/secondary/facility/palettes/00.gbapal"),
    INCBIN_U16("data/tilesets/secondary/facility/palettes/01.gbapal"),
    INCBIN_U16("data/tilesets/secondary/facility/palettes/02.gbapal"),
    INCBIN_U16("data/tilesets/secondary/facility/palettes/03.gbapal"),
    INCBIN_U16("data/tilesets/secondary/facility/palettes/04.gbapal"),
    INCBIN_U16("data/tilesets/secondary/facility/palettes/05.gbapal"),
    INCBIN_U16("data/tilesets/secondary/facility/palettes/06.gbapal"),
    INCBIN_U16("data/tilesets/secondary/facility/palettes/07.gbapal"),
    INCBIN_U16("data/tilesets/secondary/facility/palettes/08.gbapal"),
    INCBIN_U16("data/tilesets/secondary/facility/palettes/09.gbapal"),
    INCBIN_U16("data/tilesets/secondary/facility/palettes/10.gbapal"),
    INCBIN_U16("data/tilesets/secondary/facility/palettes/11.gbapal"),
    INCBIN_U16("data/tilesets/secondary/facility/palettes/12.gbapal"),
    INCBIN_U16("data/tilesets/secondary/facility/palettes/13.gbapal"),
    INCBIN_U16("data/tilesets/secondary/facility/palettes/14.gbapal"),
    INCBIN_U16("data/tilesets/secondary/facility/palettes/15.gbapal"),
};
static const struct Tileset sFriendsFacility = {
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = sFriendsFacilityTiles,
    .palettes = sFriendsFacilityPalettes,
    .metatiles = sFriendsFacilityMetatiles,
};

// Pinned Emerald Facility furniture, not an invented substitute: the three
// actual blue sofa seats in Devon's president's office, with its wall/window
// and floor. The television is the original Building TV metatile2. These
// donor IDs use Emerald's512-tile partition, independently of the active map.
// All source art stays unchanged. A blue-gray reflected view uses one UI
// palette and cannot recolor any of the13 map palettes or OBJ actor palettes.
#define DONOR_SECONDARY_FIRST 512
#define DONOR_PALETTES_PRIMARY 6
#define HOME_ROOM_W 6
#define HOME_ROOM_H 4
#define HOME_WINDOW_W 13
#define HOME_WINDOW_H 9
#define HOME_WINDOW_LEFT 16
#define HOME_WINDOW_TOP 0
#define HOME_WINDOW_BASE 100
#define HOME_PALETTE 13
#define HOME_WINDOW_TILES (HOME_WINDOW_W * HOME_WINDOW_H)

static const u16 sHomeRoom[HOME_ROOM_H][HOME_ROOM_W] = {
    {0x388, 0x389, 0x388, 0x389, 0x388, 0x389},
    {0x390, 0x391, 0x349, 0x34A, 0x34B, 0x391},
    {0x380, 0x380, 0x351, 0x352, 0x353, 0x380},
    {0x380, 0x380, 0x380, 0x380, 0x380, 0x380},
};

static const struct WindowTemplate sHomeWindow = {
    .bg = 0,
    .tilemapLeft = HOME_WINDOW_LEFT,
    .tilemapTop = HOME_WINDOW_TOP,
    .width = HOME_WINDOW_W,
    .height = HOME_WINDOW_H,
    .paletteNum = HOME_PALETTE,
    .baseBlock = HOME_WINDOW_BASE,
};

struct HomeView
{
    u8 windowId;
    u8 taskId;
    u8 mapGroup;
    u8 mapNum;
    u8 *windowPixels;
    u16 oldPalette[16];
    u16 oldFadedPalette[16];
    u16 oldTilemap[HOME_WINDOW_TILES];
};

static EWRAM_DATA struct HomeView *sHomeView = NULL;

static bool8 WindowAreaFree(void)
{
    u32 i;
    for (i = 0; i < WINDOWS_MAX; i++)
    {
        const struct Window *win = &gWindows[i];
        const struct WindowTemplate *t = &win->window;
        if (win->tileData == NULL)
            continue;
        if (t->paletteNum == HOME_PALETTE)
            return FALSE;
        if (t->bg != 0)
            continue;
        // Both the screen rectangle and character-data range must be free.
        if ((t->baseBlock < HOME_WINDOW_BASE + HOME_WINDOW_TILES
          && t->baseBlock + t->width * t->height > HOME_WINDOW_BASE)
         || (t->tilemapLeft < HOME_WINDOW_LEFT + HOME_WINDOW_W
          && t->tilemapLeft + t->width > HOME_WINDOW_LEFT
          && t->tilemapTop < HOME_WINDOW_TOP + HOME_WINDOW_H
          && t->tilemapTop + t->height > HOME_WINDOW_TOP))
            return FALSE;
    }
    return TRUE;
}

static void CopyViewTilemap(u16 *saved, bool8 restore)
{
    u32 y;
    u16 *map = GetBgTilemapBuffer(0);
    for (y = 0; y < HOME_WINDOW_H; y++)
    {
        u16 *row = map + (HOME_WINDOW_TOP + y) * 32 + HOME_WINDOW_LEFT;
        if (restore)
            CpuCopy16(saved + y * HOME_WINDOW_W, row, HOME_WINDOW_W * 2);
        else
            CpuCopy16(row, saved + y * HOME_WINDOW_W, HOME_WINDOW_W * 2);
    }
}

static u8 ReflectedColor(u16 rgb)
{
    u32 r = rgb & 31;
    u32 g = (rgb >> 5) & 31;
    u32 b = (rgb >> 10) & 31;
    // Twelve ordered shades2..13, leaving distinct colors for the rim.
    return 2 + ((r * 3 + g * 6 + b) * 11 + 155) / 310;
}

static void PutViewPixel(u32 x, u32 y, u8 color)
{
    u32 tile = (y / 8) * HOME_WINDOW_W + x / 8;
    u32 offset = tile * 32 + (y & 7) * 4 + ((x & 7) / 2);
    u8 *pixel = sHomeView->windowPixels + offset;
    if (x & 1)
        *pixel = (*pixel & 0x0F) | (color << 4);
    else
        *pixel = (*pixel & 0xF0) | color;
}

static void DrawDonorMetatile(const u8 *tiles, bool8 facility, u16 metatile, u32 destX, u32 destY)
{
    const struct Tileset *donor = facility ? &sFriendsFacility : &gTileset_Building;
    const u16 *parts = donor->metatiles + (facility ? metatile - DONOR_SECONDARY_FIRST : metatile) * 8;
    u32 layer, quarter, x, y;
    for (layer = 0; layer < 2; layer++)
    {
        for (quarter = 0; quarter < 4; quarter++)
        {
            u16 word = parts[layer * 4 + quarter];
            u32 tile = word & 0x3FF;
            u32 pal = word >> 12;
            const u16 *palette;
            const u8 *pixels;
            if (facility)
            {
                // Audited donor entries refer to primary tile0 only for
                // transparent upper quadrants; no primary scratch is needed.
                if (tile < DONOR_SECONDARY_FIRST)
                    continue;
                tile -= DONOR_SECONDARY_FIRST;
            }
            palette = (pal < DONOR_PALETTES_PRIMARY ? &gTileset_Building : &sFriendsFacility)->palettes[pal];
            pixels = tiles + tile * 32;
            for (y = 0; y < 8; y++)
            {
                for (x = 0; x < 8; x++)
                {
                    u32 sourceX = word & 0x400 ? 7 - x : x;
                    u32 sourceY = word & 0x800 ? 7 - y : y;
                    u8 index = (pixels[sourceY * 4 + sourceX / 2] >> (4 * (sourceX & 1))) & 15;
                    if (layer != 0 && index == 0)
                        continue;
                    PutViewPixel(destX + (quarter & 1) * 8 + x,
                        destY + (quarter / 2) * 8 + y, ReflectedColor(palette[index]));
                }
            }
        }
    }
}

static void Task_HomeRim(u8 taskId)
{
    static const u16 colors[] = {
        RGB(15, 7, 24), RGB(20, 11, 29), RGB(25, 18, 31), RGB(20, 11, 29),
    };
    if (sHomeView == NULL || sHomeView->taskId != taskId)
    {
        DestroyTask(taskId);
        return;
    }
    if (gPaletteFade.active)
        return;
    gTasks[taskId].data[0] = (gTasks[taskId].data[0] + 1) & 31;
    if ((gTasks[taskId].data[0] & 7) == 0)
        LoadPalette(&colors[(gTasks[taskId].data[0] >> 3) & 3], HOME_PALETTE * 16 + 14, 2);
}

bool8 FriendsVisuals_ShowHome(void)
{
    u8 *scratch;
    u32 maxSize, x, y;
    u16 palette[16];
    struct HomeView *view;
    if (sHomeView != NULL)
        return TRUE;
    if (gSaveBlock1Ptr == NULL || GetBgTilemapBuffer(0) == NULL || !WindowAreaFree())
        return FALSE;
    maxSize = GetDecompressedDataSize(sFriendsFacility.tiles);
    if (maxSize < GetDecompressedDataSize(gTileset_Building.tiles))
        maxSize = GetDecompressedDataSize(gTileset_Building.tiles);
    scratch = Alloc(maxSize);
    view = AllocZeroed(sizeof(*view));
    if (scratch == NULL || view == NULL)
    {
        if (scratch != NULL)
            Free(scratch);
        if (view != NULL)
            Free(view);
        return FALSE;
    }
    view->windowId = AddWindow(&sHomeWindow);
    if (view->windowId == WINDOW_NONE)
    {
        Free(scratch);
        Free(view);
        return FALSE;
    }
    view->taskId = TASK_NONE;
    view->mapGroup = gSaveBlock1Ptr->location.mapGroup;
    view->mapNum = gSaveBlock1Ptr->location.mapNum;
    view->windowPixels = (u8 *)GetWindowAttribute(view->windowId, WINDOW_TILE_DATA);
    CpuCopy16(&gPlttBufferUnfaded[HOME_PALETTE * 16], view->oldPalette, 32);
    CpuCopy16(&gPlttBufferFaded[HOME_PALETTE * 16], view->oldFadedPalette, 32);
    CopyViewTilemap(view->oldTilemap, FALSE);
    sHomeView = view;

    palette[0] = RGB(0, 0, 0);
    palette[1] = RGB(7, 2, 13);
    for (x = 0; x < 12; x++)
        palette[x + 2] = RGB(2 + x * 2, 3 + x * 2, 7 + x * 2);
    palette[14] = RGB(20, 11, 29);
    palette[15] = RGB(29, 26, 31);
    LoadPalette(palette, HOME_PALETTE * 16, sizeof(palette));
    FillWindowPixelBuffer(view->windowId, PIXEL_FILL(1));
    FillWindowPixelRect(view->windowId, PIXEL_FILL(14), 2, 2, 100, 68);
    DecompressDataWithHeaderWram(sFriendsFacility.tiles, scratch);
    for (y = 0; y < HOME_ROOM_H; y++)
        for (x = 0; x < HOME_ROOM_W; x++)
            DrawDonorMetatile(scratch, TRUE, sHomeRoom[y][x], 4 + x * 16, 4 + y * 16);
    DecompressDataWithHeaderWram(gTileset_Building.tiles, scratch);
    DrawDonorMetatile(scratch, FALSE, 2, 12, 28);
    Free(scratch);
    PutWindowTilemap(view->windowId);
    CopyWindowToVram(view->windowId, COPYWIN_FULL);
    if (GetTaskCount() < NUM_TASKS)
        view->taskId = CreateTask(Task_HomeRim, 80);
    return TRUE;
}

void FriendsVisuals_HideHome(void)
{
    struct HomeView *view = sHomeView;
    if (view == NULL)
        return;
    sHomeView = NULL;
    if (view->taskId != TASK_NONE && gTasks[view->taskId].isActive
     && gTasks[view->taskId].func == Task_HomeRim)
        DestroyTask(view->taskId);
    // A defensive stale-context exit must not clear a newly initialized map
    // or an unrelated window if its numeric ID has since been reused.
    if (gSaveBlock1Ptr != NULL
     && view->mapGroup == gSaveBlock1Ptr->location.mapGroup
     && view->mapNum == gSaveBlock1Ptr->location.mapNum
     && gWindows[view->windowId].tileData == view->windowPixels
     && gWindows[view->windowId].window.baseBlock == HOME_WINDOW_BASE)
    {
        if (GetBgTilemapBuffer(0) != NULL)
        {
            CopyViewTilemap(view->oldTilemap, TRUE);
            ScheduleBgCopyTilemapToVram(0);
        }
        RemoveWindow(view->windowId);
        LoadPalette(view->oldPalette, HOME_PALETTE * 16, 32);
        CpuCopy16(view->oldFadedPalette, &gPlttBufferFaded[HOME_PALETTE * 16], 32);
    }
    Free(view);
}

bool8 FriendsVisuals_IsShowing(void)
{
    return sHomeView != NULL;
}

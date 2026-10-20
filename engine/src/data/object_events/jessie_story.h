#ifndef GUARD_JESSIE_STORY_GRAPHICS_H
#define GUARD_JESSIE_STORY_GRAPHICS_H

#ifdef FIRERED
// Technically converted from the local generated character sheet.
// Nine complete 512-byte frames preserve aspect ratio in a 32x32 canvas.
// The compact character retains the native feet baseline and walk order.
static const u16 sJessieStoryPic[] = INCBIN_U16("graphics/object_events/pics/people/story/jessie.4bpp");
static const u16 sJessieStoryPalette[] = INCBIN_U16("graphics/object_events/palettes/jessie_story.gbapal");

static const struct SpriteFrameImage sJessieStoryFrames[] = {
    overworld_frame(sJessieStoryPic, 4, 4, 0),
    overworld_frame(sJessieStoryPic, 4, 4, 1),
    overworld_frame(sJessieStoryPic, 4, 4, 2),
    overworld_frame(sJessieStoryPic, 4, 4, 3),
    overworld_frame(sJessieStoryPic, 4, 4, 4),
    overworld_frame(sJessieStoryPic, 4, 4, 5),
    overworld_frame(sJessieStoryPic, 4, 4, 6),
    overworld_frame(sJessieStoryPic, 4, 4, 7),
    overworld_frame(sJessieStoryPic, 4, 4, 8),
};

static const struct ObjectEventGraphicsInfo sJessieStoryGraphicsInfo = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_JESSIE_STORY,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .compressed = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_Standard,
    .images = sJessieStoryFrames,
    .affineAnims = gDummySpriteAffineAnimTable,
};
#endif

#endif

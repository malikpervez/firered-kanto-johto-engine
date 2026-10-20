#ifndef GUARD_JENNY_STORY_GRAPHICS_H
#define GUARD_JENNY_STORY_GRAPHICS_H

// Native encoding of the local Jenny atlas. No trainer or battle is attached.
static const u16 sJennyStoryPic[] = INCBIN_U16("graphics/object_events/pics/people/story/jenny.4bpp");
static const u16 sJennyStoryPalette[] = INCBIN_U16("graphics/object_events/palettes/jenny_story.gbapal");

static const struct SpriteFrameImage sJennyStoryFrames[] = {
    overworld_frame(sJennyStoryPic, 2, 4, 0),
    overworld_frame(sJennyStoryPic, 2, 4, 1),
    overworld_frame(sJennyStoryPic, 2, 4, 2),
    overworld_frame(sJennyStoryPic, 2, 4, 3),
    overworld_frame(sJennyStoryPic, 2, 4, 4),
    overworld_frame(sJennyStoryPic, 2, 4, 5),
    overworld_frame(sJennyStoryPic, 2, 4, 6),
    overworld_frame(sJennyStoryPic, 2, 4, 7),
    overworld_frame(sJennyStoryPic, 2, 4, 8),
};

static const struct ObjectEventGraphicsInfo sJennyStoryGraphicsInfo = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_JENNY_STORY,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 256,
    .width = 16,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = FALSE,
    .compressed = FALSE,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_16x32,
    .subspriteTables = sOamTables_16x32,
    .anims = sAnimTable_Standard,
    .images = sJennyStoryFrames,
    .affineAnims = gDummySpriteAffineAnimTable,
};

#endif

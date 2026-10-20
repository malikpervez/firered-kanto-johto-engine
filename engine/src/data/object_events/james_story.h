#ifndef GUARD_JAMES_STORY_GRAPHICS_H
#define GUARD_JAMES_STORY_GRAPHICS_H

// Exact package atlas: down/up/left idle, then two steps per facing.
// Right-facing poses use the native standard animation horizontal mirror.
static const u16 sJamesStoryPic[] = INCBIN_U16("graphics/object_events/pics/people/story/james.4bpp");
static const u16 sJamesStoryPalette[] = INCBIN_U16("graphics/object_events/palettes/james_story.gbapal");

static const struct SpriteFrameImage sJamesStoryFrames[] = {
    overworld_frame(sJamesStoryPic, 2, 4, 0),
    overworld_frame(sJamesStoryPic, 2, 4, 1),
    overworld_frame(sJamesStoryPic, 2, 4, 2),
    overworld_frame(sJamesStoryPic, 2, 4, 3),
    overworld_frame(sJamesStoryPic, 2, 4, 4),
    overworld_frame(sJamesStoryPic, 2, 4, 5),
    overworld_frame(sJamesStoryPic, 2, 4, 6),
    overworld_frame(sJamesStoryPic, 2, 4, 7),
    overworld_frame(sJamesStoryPic, 2, 4, 8),
};

static const struct ObjectEventGraphicsInfo sJamesStoryGraphicsInfo = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_JAMES_STORY,
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
    .images = sJamesStoryFrames,
    .affineAnims = gDummySpriteAffineAnimTable,
};

#endif

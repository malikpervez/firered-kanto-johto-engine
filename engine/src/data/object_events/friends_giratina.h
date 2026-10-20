#ifndef GUARD_FRIENDS_GIRATINA_GRAPHICS_H
#define GUARD_FRIENDS_GIRATINA_GRAPHICS_H

// Exact native Giratina Altered south-idle frame and original palette. Only
// this scripted presence uses the one-frame sheet; species/follower art and
// normal species graphics remain unchanged. No new form or acquisition route.
static const u16 sFriendsGiratinaPic[] = INCBIN_U16("graphics/object_events/pics/people/story/friends/giratina_presence.4bpp");
static const u16 sFriendsGiratinaPalette[] = INCBIN_U16("graphics/object_events/palettes/storyfriends/giratina_presence.gbapal");

static const struct SpriteFrameImage sFriendsGiratinaFrames[] = {
    overworld_frame(sFriendsGiratinaPic, 8, 8, 0),
};
static const union AnimCmd sFriendsGiratinaIdle[] = {
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_END,
};
static const union AnimCmd *const sFriendsGiratinaAnimations[] = {
    [ANIM_STD_FACE_SOUTH] = sFriendsGiratinaIdle,
    [ANIM_STD_FACE_NORTH] = sFriendsGiratinaIdle,
    [ANIM_STD_FACE_WEST] = sFriendsGiratinaIdle,
    [ANIM_STD_FACE_EAST] = sFriendsGiratinaIdle,
};
static const struct ObjectEventGraphicsInfo sFriendsGiratinaGraphicsInfo = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_FRIENDS_GIRATINA,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 2048,
    .width = 64,
    .height = 64,
    .paletteSlot = PALSLOT_NPC_3,
    .shadowSize = SHADOW_SIZE_M,
    .inanimate = TRUE,
    .compressed = FALSE,
    .tracks = TRACKS_NONE,
    .oam = &gObjectEventBaseOam_64x64,
    .subspriteTables = sOamTables_64x64,
    .anims = sFriendsGiratinaAnimations,
    .images = sFriendsGiratinaFrames,
    .affineAnims = gDummySpriteAffineAnimTable,
};
STATIC_ASSERT(sizeof(sFriendsGiratinaPic) == 2048, FriendsGiratinaSingleFrame);

#endif

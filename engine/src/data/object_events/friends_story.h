#ifndef GUARD_FRIENDS_STORY_GRAPHICS_H
#define GUARD_FRIENDS_STORY_GRAPHICS_H

#ifdef FIRERED
// Owner-supplied seven-walking-npcs-v1 atlases, preserved without art changes.
// Each sheet: south/up/left idle, then two steps per facing. Standard native
// animations mirror the left poses for right; no player-only frames are used.
static const u16 sFriendBrianPic[] = INCBIN_U16("graphics/object_events/pics/people/story/friends/brian.4bpp");
static const u16 sFriendBrianPalette[] = INCBIN_U16("graphics/object_events/palettes/storyfriends/brian.gbapal");
static const u16 sFriendHamPic[] = INCBIN_U16("graphics/object_events/pics/people/story/friends/ham.4bpp");
static const u16 sFriendHamPalette[] = INCBIN_U16("graphics/object_events/palettes/storyfriends/ham.gbapal");
static const u16 sFriendJonPic[] = INCBIN_U16("graphics/object_events/pics/people/story/friends/jon.4bpp");
static const u16 sFriendJonPalette[] = INCBIN_U16("graphics/object_events/palettes/storyfriends/jon.gbapal");
static const u16 sFriendNickPic[] = INCBIN_U16("graphics/object_events/pics/people/story/friends/nick.4bpp");
static const u16 sFriendNickPalette[] = INCBIN_U16("graphics/object_events/palettes/storyfriends/nick.gbapal");
static const u16 sFriendXPic[] = INCBIN_U16("graphics/object_events/pics/people/story/friends/x.4bpp");
static const u16 sFriendXPalette[] = INCBIN_U16("graphics/object_events/palettes/storyfriends/x.gbapal");
static const u16 sFriendLbPic[] = INCBIN_U16("graphics/object_events/pics/people/story/friends/lb.4bpp");
static const u16 sFriendLbPalette[] = INCBIN_U16("graphics/object_events/palettes/storyfriends/lb.gbapal");
static const u16 sFriendTimPic[] = INCBIN_U16("graphics/object_events/pics/people/story/friends/tim.4bpp");
static const u16 sFriendTimPalette[] = INCBIN_U16("graphics/object_events/palettes/storyfriends/tim.gbapal");

#define FRIEND_STORY_GRAPHICS(Name, PalTag) \
    static const struct SpriteFrameImage sFriend##Name##Frames[] = { \
        overworld_frame(sFriend##Name##Pic, 2, 4, 0), \
        overworld_frame(sFriend##Name##Pic, 2, 4, 1), \
        overworld_frame(sFriend##Name##Pic, 2, 4, 2), \
        overworld_frame(sFriend##Name##Pic, 2, 4, 3), \
        overworld_frame(sFriend##Name##Pic, 2, 4, 4), \
        overworld_frame(sFriend##Name##Pic, 2, 4, 5), \
        overworld_frame(sFriend##Name##Pic, 2, 4, 6), \
        overworld_frame(sFriend##Name##Pic, 2, 4, 7), \
        overworld_frame(sFriend##Name##Pic, 2, 4, 8), \
    }; \
    static const struct ObjectEventGraphicsInfo sFriend##Name##GraphicsInfo = { \
        .tileTag = TAG_NONE, \
        .paletteTag = PalTag, \
        .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE, \
        .size = 256, \
        .width = 16, \
        .height = 32, \
        .paletteSlot = PALSLOT_NPC_3, \
        .shadowSize = SHADOW_SIZE_M, \
        .inanimate = FALSE, \
        .compressed = FALSE, \
        .tracks = TRACKS_FOOT, \
        .oam = &gObjectEventBaseOam_16x32, \
        .subspriteTables = sOamTables_16x32, \
        .anims = sAnimTable_Standard, \
        .images = sFriend##Name##Frames, \
        .affineAnims = gDummySpriteAffineAnimTable, \
    };

FRIEND_STORY_GRAPHICS(Brian, OBJ_EVENT_PAL_TAG_FRIEND_BRIAN)
FRIEND_STORY_GRAPHICS(Ham, OBJ_EVENT_PAL_TAG_FRIEND_HAM)
FRIEND_STORY_GRAPHICS(Jon, OBJ_EVENT_PAL_TAG_FRIEND_JON)
FRIEND_STORY_GRAPHICS(Nick, OBJ_EVENT_PAL_TAG_FRIEND_NICK)
FRIEND_STORY_GRAPHICS(X, OBJ_EVENT_PAL_TAG_FRIEND_X)
FRIEND_STORY_GRAPHICS(Lb, OBJ_EVENT_PAL_TAG_FRIEND_LB)
FRIEND_STORY_GRAPHICS(Tim, OBJ_EVENT_PAL_TAG_FRIEND_TIM)

#undef FRIEND_STORY_GRAPHICS

// Same order as the audited contiguous graphics IDs568..574.
static const struct ObjectEventGraphicsInfo *const sFriendsStoryGraphicsInfoPointers[] = {
    &sFriendBrianGraphicsInfo,
    &sFriendHamGraphicsInfo,
    &sFriendJonGraphicsInfo,
    &sFriendNickGraphicsInfo,
    &sFriendXGraphicsInfo,
    &sFriendLbGraphicsInfo,
    &sFriendTimGraphicsInfo,
};
STATIC_ASSERT(ARRAY_COUNT(sFriendsStoryGraphicsInfoPointers) == 7, FriendsStoryGraphicsCount);
#endif

#endif

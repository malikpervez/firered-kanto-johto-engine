#ifndef GUARD_KANTO_CONNECTION_SEAM_H
#define GUARD_KANTO_CONNECTION_SEAM_H

#ifdef FIRERED
// ROM-only adapters for explicitly qualified incoming Kanto connection bands.
// No fields are added to MapLayout, MapHeader, saves, or animation RAM state.
struct KantoSeamMetatile
{
    const struct MapLayout *sourceLayout;
    u32 attributes;
    u16 sourceMid;
    u16 tiles[8];
    u8 layoutVersion;
};
struct KantoSeamGlyphRun
{
    const u16 *pixels;
    u16 destination;
    u16 size;
};
struct KantoSeamPalette
{
    u16 colors[16];
    u16 destination;
};
struct KantoSeamAnimation
{
    const u16 *const *frames;
    u16 destination;
    u16 size;
    u16 divisor;
    u16 phase;
    u16 frameCount;
    // Zero retains the descriptor period; nonzero keeps a borrowed source clock.
    u16 sourceCounterMax;
};
struct KantoSeam
{
    const struct MapLayout *layout;
    const struct KantoSeamMetatile *metatiles;
    const struct KantoSeamGlyphRun *glyphRuns;
    const struct KantoSeamPalette *palettes;
    const struct KantoSeamAnimation *animations;
    u16 firstMid;
    u16 metatileCount;
    u16 glyphRunCount;
    u16 paletteCount;
    u16 animationCount;
    u16 animationCounterMax;
};
const struct KantoSeam *KantoSeam_Find(const struct MapLayout *layout);
const struct KantoSeamMetatile *KantoSeam_GetMetatile(const struct MapLayout *layout, u16 mid);
u16 KantoSeam_TranslateBlock(const struct MapLayout *target, const struct MapLayout *source, u16 block);
u16 KantoSeam_ReencodeCacheBlock(const struct MapLayout *previous, const struct MapLayout *current, u16 block);
u16 KantoSeam_CanonicalMid(const struct MapLayout *layout, u16 mid);
u16 KantoSeam_CutResult(const struct MapLayout *layout, u16 previousMid, u16 result);
bool8 KantoSeam_ChangesPrimaryPalette(const struct MapLayout *layout);
void KantoSeam_LoadResources(const struct MapLayout *layout, bool8 skipFaded);
#endif

#endif

#ifndef GUARD_RAINBOW_VISUALS_H
#define GUARD_RAINBOW_VISUALS_H

// Transient presentation only: these values are never Pokemon species/forms or save data.
#define RAINBOW_VISUAL_ARTICUNO 1
#define RAINBOW_VISUAL_ZAPDOS 2
#define RAINBOW_VISUAL_MOLTRES 3
#define RAINBOW_VISUAL_LUGIA 4
void Special_RainbowHoOhFlyby(void);
void Special_RainbowMewGlimpse(void);
void RainbowVisuals_BeginEncounter(void);
void RainbowVisuals_EndEncounter(void);
void RainbowVisuals_ApplyCorruption(void);
void RainbowVisuals_OnObjectSpawn(u8 objectId);
const u16 *RainbowVisuals_BattlePalette(u32 battler, u32 species, const u16 *ordinary);
void RainbowVisuals_PatchBattleGfx(u32 battler, u32 species, void *tiles);
#endif

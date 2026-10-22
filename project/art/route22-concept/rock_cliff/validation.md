# Route 22 Rock & Cliff — validation

**Result: PASS — 17 checks.** Native import art and assembly metadata validated; no game/ROM runtime was supplied.

## Export dimensions

| Item | Native pixels | Quantity / layout |
|---|---:|---|
| Top master | 48×48 | One seamless repeating surface |
| Centre cuts | 16×16 | Nine, ordered as a 3×3 cycle |
| Phase boundary tiles | 16×16 | 13 × 9 phases = 117 |
| Compatibility set | 16×16 | Original sixteen names; aliases use phases 1–3 |
| Face components | 16×16 | 18 pieces: two rows × nine columns |
| Face columns | 16×32 | Left, three middles, right, four corner returns |
| Main face strip | 80×32 | Five columns × two rows |
| Corner strip | 64×32 | Four columns × two rows |
| Stair connector | 32×32 | Also split into four 16×16 pieces |
| Small / breakable rock | 16×16 | One each |
| Big boulder | 32×32 | One 2×2-block prop |
| Plateau scene | 160×128 / 640×512 | 10×8 blocks, native and 4× |
| Surface proof | 96×96 / 384×384 | 6×6 blocks, native and 4× |

There are 183 registered native indexed exports, including component art, aliases and assembly helpers. Their review copies use exact 4× pixel replication. Composed lawn/player scenes and the labelled overview are review-only images and include the existing ground/player palettes.

## Palette

All import PNGs use PNG colour type 3, 4-bit indices, the same 16-entry PLTE and binary transparency. Index 0 has alpha 0; indices 1–15 have alpha 255. All fifteen opaque colours are used across the pack. Every channel is divisible by 8. No image was reduced from a higher resolution.

| Index | Hex | Role | Alpha |
|---:|---|---|---:|
| 0 | #000000 | Transparent | 0 |
| 1 | #302830 | Deep foot / fissure | 255 |
| 2 | #504038 | Warm contact shadow | 255 |
| 3 | #685850 | Lower cliff shade | 255 |
| 4 | #887060 | Upper cliff shade | 255 |
| 5 | #A08870 | Warm stone mid | 255 |
| 6 | #B0A088 | Warm grey cliff top | 255 |
| 7 | #C8B898 | Lit cliff plane | 255 |
| 8 | #D8C8A8 | Sunlit cliff facet | 255 |
| 9 | #585848 | Grey rock / stair deep shade | 255 |
| 10 | #707060 | Grey rock / stair shade | 255 |
| 11 | #909080 | Grey rock / stair mid | 255 |
| 12 | #B8B8A0 | Grey rock / stair lit face | 255 |
| 13 | #D0C8B0 | Grey rock / stair highlight | 255 |
| 14 | #506840 | Moss shade | 255 |
| 15 | #789050 | Moss light | 255 |

## Revision 3

The main warm cliff ramp is retained. Five colours from the earlier grey rock family are shared by rocks and stair treads; two moss greens complete the single palette. Intermediate prop shades are consolidated. Short overhang shadows, deeper clefts and stronger side/foot shading add perceived depth while the face remains 32 pixels tall. Tile counts remain unchanged.

## Texture and boundaries

The centre master is authored on a 48×48 toroidal surface and cut without resampling. The six-block proof repeats the complete surface twice in each direction. Visual inspection found no 16-pixel crack stripe or block grid; the intended overall repeat remains 48 pixels. Centre pairs differ by at least 35.9% of their pixels (mean 47.7%).

Every phase edge preserves its own centre outside the allowed outer-6-pixel mask; inner notches are restricted to 6×6. Every centre, compatibility piece and phase edge shares the same inner 4×4. These top restrictions do not apply to the separate full-height cliff face, stairs or rock props.

All nine ordered pairs of middle face variants share matching two-pixel interfaces at the full 32-pixel height. Top and bottom pieces reconstruct their columns exactly. Face and stair joins were inspected in the assembled scene.

## Storage and integration

| Group | Unique 8×8 tiles, no flips |
|---|---:|
| Top and all edge phases | 180 |
| Face, corners and stairs | 50 |
| Rocks | 23 |
| Whole set | **253** |

Packed graphics: **8,096 bytes**. Palette: **32 bytes**. Atlas: 16 columns, 253 used slots, 3 unused transparent padding slots. The binary omits padding. Exact 8×8 matches are shared globally.

The expanded set exceeds the previous 120-tile cliff allowance; the old budget is not claimed as passed. Allocate the full 253-tile set or select only the needed pieces. The existing League gate and refined road are unchanged.

All 2,304 phase/neighbour-mask recipes and every atlas tile map reconstruct their source pixels exactly. The 4bpp graphics and GBA palette round-trip to the same indices and colours. Collision and elevations must be wired into the target map engine as described in README.md.

## Executed checks

1. **PASS** — One 15-colour palette plus transparent index 0; every channel is a multiple of 8.
2. **PASS** — 183 indexed exports: dimensions, palette entries, binary alpha, decoded colours and exact 4x reviews.
3. **PASS** — Nine centres are exact row-major cuts of the seamless 48x48 master and all share the required inner 4x4.
4. **PASS** — All centre variants are meaningfully different (at least 25% differing pixels for every pair).
5. **PASS** — All 117 phase edges preserve their selected centre outside the 6px side / 6x6 corner mask, and retain the common inner 4x4.
6. **PASS** — Legacy sixteen-name set is complete and uses exact centre aliases / phase-1 edges.
7. **PASS** — 6x6 proof exactly repeats the master four times with continuous phase at every 16px join.
8. **PASS** — Every face column is 16x32 and splits/rejoins exactly into its named top and bottom 16x16 pieces.
9. **PASS** — All nine middle-variant pairings share exact 2px interfaces at the full 32px height.
10. **PASS** — Small and breakable rocks are 16x16; boulder 32x32; every prop has a transparent exterior and solid footprint metadata.
11. **PASS** — Warm cliff colours retained; rocks and stair treads use five colours from the original grey family within the same palette.
12. **PASS** — Stair connector is an exact 2x2 assembly with no lawn pixels or transparent cross-row gap.
13. **PASS** — Both inner cliff returns are opaque beside the stair mouth; no lawn can leak through their upper joins.
14. **PASS** — Shared atlas and all exported tile maps reconstruct the native art exactly, without flips.
15. **PASS** — All 2304 phase/neighbour recipes use only atlas tiles and preserve the common 4x4.
16. **PASS** — GBA 4bpp binary and 15-bit palette round-trip to the same native pixels and colours.
17. **PASS** — 10x8 plateau and prop scenes are native compositions with exact 4x replication; 16x26 player witness.

Machine-readable results: validation.json. Validator: source/validate.cjs.

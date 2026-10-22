# Route 22 Rock & Cliff 3.2 — validation

**Result: PASS — 25 checks.** Native import art and assembly metadata validated; no game/ROM runtime was supplied.

## Export dimensions

| Item | Native pixels | Quantity / layout |
|---|---:|---|
| Top master | 48×48 | One seamless repeating surface |
| Centre cuts | 16×16 | Nine, ordered as a 3×3 cycle |
| Phase boundary tiles | 16×16 | 13 × 9 phases = 117 |
| Face-junction top tiles | 16×16 | Six families × nine phases = 54 |
| Compatibility set | 16×16 | Original sixteen names; aliases use phases 1–3 |
| Face components | 16×16 | 18 pieces: two rows × nine columns |
| Face columns | 16×32 | Left, three middles, right, four corner returns |
| Main face strip | 80×32 | Five columns × two rows |
| Corner strip | 64×32 | Four columns × two rows |
| Stair connector | 32×32 | Also split into four 16×16 pieces |
| Small / breakable rock | 16×16 | One each |
| Big boulder | 32×32 | One 2×2-block prop |
| Plateau scene | 160×128 / 640×512 | 10×8 blocks, native and 4× |
| Junction scene | 224×192 / 896×768 | 14×12 blocks; two-block strip, paired side faces, end cap |
| Surface proof | 96×96 / 384×384 | 6×6 blocks, native and 4× |

There are 237 registered native indexed exports, including component art, aliases and assembly helpers. Their review copies use exact 4× pixel replication. Composed lawn/player scenes and the labelled overview are review-only images and include the existing ground/player palettes.

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

## Revision 3.2: exact scope

SE and SW caps were corrected in all nine phases, together with the first eight rows of their outer face ends (left/right aliases follow those ends). The cap and face have the same one-pixel exterior inset at their join; the silhouette no longer pinches inward between them. All changed cap pixels are inside their 6×6 corner.

The new side_W_face and side_E_face families fill their entire side band with shaded rock. Their *_start versions align to the upper face block, and in_SW_face / in_SE_face replace the transparent lawn notch immediately above that start. Each family supplies nine phases. Side edits stay within six pixels; corner edits stay within 6×6. W and E have independent lighting.

The last three pixels at the contacting foot of inner_W and inner_E are sealed, six pixels total. These prevent a pinhole where the face bottom meets the side strip. The stair artwork itself is untouched.

Baseline comparisons verify that the palette, 48×48 texture, all nine centres, all unrelated top boundaries, three middle wall columns, stairs and rock props exactly match revision 3.1. Face height remains 32 pixels.

## Junction proof

All 18 cap-to-outer-face combinations pass the silhouette and opacity checks. All 162 ordered upper/lower side-phase pairs match their adjacent inner face pixel for pixel along the full 32-pixel contact. All 162 head/start phase pairs match at their six-pixel interface. The assembled strip test detects 96 transparent pixels in the old seam regions and **0** in revision 3.2. The count covers the tested side interfaces and head corners, not the intentionally transparent exterior.

See previews/junctions_3_2_4x.png and previews/junctions_comparison_4x.png. These are composed asset tests, not an in-game playtest.

## Texture and boundaries

The centre master is authored on a 48×48 toroidal surface and cut without resampling. The six-block proof repeats the complete surface twice in each direction. Visual inspection found no 16-pixel crack stripe or block grid; the intended overall repeat remains 48 pixels. Centre pairs differ by at least 35.9% of their pixels (mean 47.7%).

Every phase edge preserves its own centre outside the allowed outer-6-pixel mask; inner notches are restricted to 6×6. Every centre, compatibility piece and phase edge shares the same inner 4×4. These top restrictions do not apply to the separate full-height cliff face, stairs or rock props.

All nine ordered pairs of middle face variants share matching two-pixel interfaces at the full 32-pixel height. Top and bottom pieces reconstruct their columns exactly. Face and stair joins were inspected in the assembled scene.

## Storage and integration

| Group | Unique 8×8 tiles, no flips |
|---|---:|
| Top and all edge phases | 266 |
| Face, corners and stairs | 50 |
| Rocks | 23 |
| Whole set | **339** |

Packed graphics: **10,848 bytes**. Palette: **32 bytes**. Atlas: 16 columns, 339 used slots, 13 unused transparent padding slots. The binary omits padding. Exact 8×8 matches are shared globally.

The expanded set exceeds the previous 120-tile cliff allowance; the old budget is not claimed as passed. Allocate the full 339-tile set or select only the needed pieces. The existing League gate and refined road are unchanged.

All 2,304 phase/neighbour-mask recipes, 54 face-adjacency recipes and every atlas tile map reconstruct their source pixels exactly. The 4bpp graphics and GBA palette round-trip to the same indices and colours. Collision and elevations must be wired into the target map engine as described in README.md.

## Executed checks

1. **PASS** — One 15-colour palette plus transparent index 0; every channel is a multiple of 8.
2. **PASS** — 237 indexed exports: dimensions, palette entries, binary alpha, decoded colours and exact 4x reviews.
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
14. **PASS** — Revision 3.1 preservation: palette, full 48x48 texture, nine centres, stairs, props, middle walls and all unrelated boundaries are pixel-identical.
15. **PASS** — All 54 face-junction phase tiles are opaque, keep edits within their 6px side or 6x6 corner, and preserve their phase and common 4x4.
16. **PASS** — All nine SW/SE caps meet outer_W/outer_E flush: matched one-pixel exterior inset, opaque contact, and no inward notch across the 16px join.
17. **PASS** — 162 ordered side-phase pairs: both inner face edges match the touching top pixels for all 32 rows, including the sealed foot junction.
18. **PASS** — 162 ordered head/start phase pairs: in_SW_face/in_SE_face corner caps are opaque and meet their side-start tile with an exact 6px colour interface.
19. **PASS** — W and E junction art has separately authored lighting rather than mirrored pixels.
20. **PASS** — Assembled two-block strip: no transparent lawn gaps at either face seam or either three-way head corner; baseline fails the same test.
21. **PASS** — Shared atlas and all exported tile maps reconstruct the native art exactly, without flips.
22. **PASS** — All 2304 phase/neighbour recipes use only atlas tiles and preserve the common 4x4.
23. **PASS** — All 54 explicit face-adjacency recipes reconstruct their source tiles from the shared atlas.
24. **PASS** — GBA 4bpp binary and 15-bit palette round-trip to the same native pixels and colours.
25. **PASS** — Plateau, junction, terrace and prop scenes have exact 4x replication; junction preview is 14x12 blocks with a 16x26 player witness.

Machine-readable results: validation.json. Validator: source/validate.cjs.

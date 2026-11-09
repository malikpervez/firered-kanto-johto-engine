# Kanto Fuchsia City v0.1

Native asset review build, 2026-11-03. This set follows the Fuchsia City brief, the approved building guide and the existing Kanto pack format. It has **29 unique 8x8 graphics**, including all phases, borders and joins. It does not modify a ROM or game map.

## Reference status

The Drive folder supplied the prompt, the complete 48x40 text plan and five palettes. These four images named by the brief were not present when this review build was made:

- `reference_fuchsia_zones_2x.png`
- `reference_fuchsia_now_1x.png`
- `reference_fuchsia_zoo_3x.png`
- `reference_fuchsia_shore_3x.png`

The **native asset samples are complete**. Town scenes are explicitly provisional: they reconstruct the supplied text grid with approved native context art. They are not edits of the missing reference images. The office and unspecified houses use existing approved house stand-ins; characters are not drawn. Exact reference-map visual matching remains pending until those images are available. No new building art was made.

`previews/materials_review_1x.png` and its 3x copy show only the new materials and details on existing lawn. `previews/fuchsia_review_3x.png` shows four provisional scene crops. The full reconstructed map, larger scenes, 240x160 crops, labelled 4x autotiles and placement records are also included. All art displayed in these previews comes from the delivered native PNGs or the copied existing context assets.

## Pieces

| Piece | Use | Avoid |
|---|---|---|
| Sandstone | The entire Safari plaza, avenue, zoo walks, main street and shore street. Quiet warm flags, long and short rectangles, continuous joints and equal-height courses. | Leaving stretches of old cobble or dirt inside those town surfaces. Route roads and the beach path are the exceptions. |
| Bamboo palisade | Enclose the five pens and the pond garden. Golden canes, bamboo nodes, two cross-rails and pale rope; straight runs, corners, ends and junctions. | Gates in the zoo pens, bare-metal styling or collision gaps. A neighbouring board or house wall ends the fence at a post. |
| Exhibit board | One block in each pen's fence line. A timber panel on two bamboo posts with a small burned paw mark. | Replacing ordinary town signs or allowing passage through the board block. Keep the block below it accessible. |
| Fuchsia bush | The namesake garden beds and lawn beside houses. Dark rounded foliage, pink sepals and hanging violet petals. | Blocking the hedge garden's aisle, camp, actors, cut trees, hidden item or doorway approaches. It is solid. |

The optional hanging-basket street lamp is not included. The required set uses 29 of the 30 allowed graphics, leaving one tile. Existing kit lamps remain in the provisional preview. Their pixels are context only and are not new import assets.

The sandstone, palisade and shrub can be reused in other warm towns and Safari areas. Every block of each prop is solid. Sandstone and its joins are walkable. All pieces in this set have `over_rows: 0`; no over-player lamp was added. Transparent margins do not change collision.

## Paving coverage and borders

The supplied text grid contains 405 A/B/C blocks. Every one uses sandstone in the provisional preview, so there is a single material through the town's connected streets, plaza and zoo walks. Pen floors remain the text plan's lawn, dirt or pond. The beach path remains kit dirt.

The lawn edge is consistent on N, E, S and W: two pixels of exact kit lawn, then a warm joint and a pale stone lip. Outer and inner corners use that same edge. Unlike the transparent props, sandstone edge pieces include their kit lawn pixels and are fully opaque. No new lawn colours were introduced.

Joins supplied:

- `to_cobble_W`: west map edge, rows 18–20.
- `to_cobble_E`: east map edge, rows 20–23.
- `to_dirt_S`: below the shore street, toward the beach path. The text zones show columns 18–29 at the start of that path; the separate route-join note gives columns 19–28 at its far bottom edge. The preview follows the text grid within Fuchsia and does not edit Route 19.

Each join retains the kit material in its outer 8px half. `join_recipes.json` preserves any lawn edge on the sandstone half where a join meets a lawn corner. This avoids the inconsistent rim at a join that would result from using a plain join tile at every boundary.

## Palette choice

All five supplied GPL files are retained byte-for-byte and in the supplied index order. The new `fuchsia_town.gpl` uses bank 10. It is the kit ground palette with **only index 1 replaced by RGB 224,192,168**, a warm sun-bleached stone tone with a faint rose cast. The other fifteen entries, including transparency, remain exactly the kit ground entries. This gives the paving a distinct body colour while keeping its lawn greens, dirt browns and cobble greys exact in the same 8x8 tiles.

| Bank | Palette | New uses |
|---|---|---|
| 0 | kit_ground | Existing context; supplied unchanged |
| 1 | kit_water | Supplied unchanged; not used by new pieces |
| 2 | kit_wood | Supplied unchanged; not used by new pieces |
| 8 | kit_plants | Fuchsia bush |
| 9 | fuchsia_safari | Bamboo palisade and exhibit board |
| 10 | fuchsia_town | Sandstone, lawn borders and all joins |

Each 8x8 tile uses one palette, recorded explicitly by `palettes_8x8`. Every new PNG embeds that palette exactly. Do not replace bank 0 with the new bank 10 palette: existing ground art may use bank 0's original dark index 1.

The supplied WATER palette has non-multiple-of-eight channels at indices 9–11. It is retained unchanged, and no new piece uses those entries. All colours used by the new art have channels divisible by eight. The validator records the inherited palette exception explicitly.

## Native format and recipes

All asset PNGs are authored directly as native integer palette indices at 1x: 4-bit indexed PNG, 16 embedded colours, index 0 transparent and alpha only 0/255. There is no tracing, quantisation, downscaling, antialiasing or dithering. All footprints are whole 16px blocks. Enlarged previews use nearest-neighbour only.

Stone courses repeat on 32x32, using `large_NW`, `large_NE`, `large_SW`, `large_SE`. Courses have a constant 16px height. Use `phase_recipes.json` with a stable map-relative phase origin so neighbouring patches remain aligned. Generic `center` is a quiet infill, not the intended fill for a large plaza.

Surface masks cover all 256 combinations. Bits are N=1, E=2, S=4, W=8, NE=16, SE=32, SW=64, NW=128. A set bit means outside the sandstone. Cardinal boundaries override diagonal ones. Each recipe selects a source piece and quadrant. Inside corner names are ordered NE, SE, SW, NW. `join_recipes.json` supplies all 256 masks for each phase of each of the three joins. `reciprocal_joins.json` supplies reverse aliases to the same images, without extra import graphics.

Palisade recipes cover 16 cardinal masks. Here, a set bit means the fence continues in that direction. Boards and walls count as no fence. All five pens' closed boundaries, including the five solid boards, are checked against the text plan.

Every prop has its own JSON with footprint, per-8x8 palette grid, solid and walkable blocks, and `over_rows`. Surface pieces carry the same fields in `sandstone.json`. All coordinates start at the local top-left block. There are no animations in this static set.

`tiles_4bpp.bin` is the canonical shared graphics pool: 32 bytes per tile, left pixel in the low nibble. `tile_pool.json` describes it. The per-piece `tiles_8x8`, `flips_8x8` and `palettes_8x8` arrays reconstruct each indexed PNG exactly. IDs refer to the global pool. Ground, trees, water, buildings and existing Town Props used as preview context are not part of this new pool.

## Budgets

| Group | Unique 8x8 tiles | Limit |
|---|---:|---:|
| Sandstone, phases, edges, corners and joins | 14 | 16 |
| Bamboo palisade, all 16 pieces | 8 | 8 |
| Exhibit board | 3 | 3 |
| Fuchsia bush | 4 | 4 |
| **Whole set** | **29** | **30** |

H, V and combined mirrors count as one graphic; rotations do not. All supplied transition halves count. The ideal 26 was not reached; the hard limit is met with one tile remaining. If the town has the estimated 34 free slots, importing all 29 would leave about five. The optional lamp is omitted rather than exceeding the cap or dropping required joins.

## Validation and reproduction

`validation.json` independently checks PNG bit depth, 16-entry palette order, supplied palette bytes, one palette per 8x8 tile, used-channel quantisation, binary alpha, dimensions, footprints, collision, all tile budgets, binary/flip reconstruction, all 256 surface masks, all join masks, all 16 fence masks, exact kit RGB in joins, equal course heights, consistent lawn rims, and nearest-neighbour/GBA preview sizes. The text plan's camp, actors, cut trees, item and approaches remain clear of new props.

The status remains `PASS_WITH_REFERENCE_REVIEW_PENDING`: file and layout checks pass, but exact comparison against the four missing reference PNGs cannot yet be performed.

With Python, NumPy and Pillow installed:

```sh
python3 source/build.py
python3 source/previews.py
python3 source/validate.py
python3 source/package.py
```

The source references and context images included in this ZIP make these native samples and provisional previews reproducible. Final map placement and engine palette/layer assignment remain the game author's responsibility.

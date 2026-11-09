# Kanto Lavender Town v0.1

First review build, 2026-11-03. Native indexed GBA ground and reusable town details, following the supplied Lavender brief and the approved building guide. Placement previews are illustrative; Claude/the map author still places the pieces in the game. The game map itself is not changed.

Slate review correction: equal-height 16px courses, a consistent 8px stagger and continuous joints replace the uneven first-pass layout. The 32px repeat, colours, collision, map footprint and all other artwork are preserved.

## Preview tour

The cool slate square meets the existing cobble on the north, west and south. The middle stays open for the seven travellers. A slate walk continues east to the unchanged Tower entrance. A one-block clear gate opening, flanked by warm stone lanterns, leads to a gravel path through east-west lavender rows. Three memorial shapes and a small offering stone replace the stand-in rocks. The two existing Town Props benches face north toward the garden. Fuji's yard has paired bowls, a framed straw bed and an open wooden shelter.

Start with `previews/lavender_review_3x.png` and `previews/props_review_3x.png`. The folder also contains the full town, separate scene views at 1x/3x, four 240x160 GBA crops, every surface/railing autotile labelled at 4x, and the open gate at 4x. There are no animation strips because this version uses static beds and lanterns.

`previews/placements.json` records the illustrative positions. The camp, door approaches, sign-reading blocks, people and ghost areas are clear of new solid pieces. All existing buildings are unchanged. The garden's railing deliberately has openings around the west ghost area and the southern seating. The lavender bed beside the Tower is walkable and has no enclosing rail to trap the ghosts.

## Pieces and placement

| Piece | Use | Avoid |
|---|---|---|
| Slate | Calm town square, Tower walk, formal courtyards. Two subdued stone values, even 16px courses and an 8px stagger on a 32px repeat. | Replacing the three route roads; those remain cobble. |
| Gravel | Pale fine paths between beds; its four-way joins meet slate, cobble and lavender. | Turning the whole square into gravel. |
| Lavender beds | Purple spikes over sage foliage in east-west rows; three fill choices. All blocks are walkable. | Using the beds as a collision barrier or covering reserved actors with solid props. |
| Iron railing | Low transparent bars, straight runs, corners, ends and junctions. | Closing the worker/ghost routes or putting bars in a door approach. |
| Open gate | 3x1 footprint; two solid outer post/leaf blocks, completely clear middle block. Open leaves fold within the outer blocks. | Marking all three blocks solid or using the transparent post-block margins as walkable paths. |
| Rounded memorial | A simple upright stone, 1x1, for a quiet planted setting. | Dense rows which make the garden feel threatening. |
| Flat marker | Low 1x1 stone marker; also suitable beside paths in other towns. | Treating its low appearance as walkable: it is solid. |
| Carved-flower memorial | Upright 1x1 stone with a small floral engraving. | Religious, horror or broken-tomb additions. |
| Offering stone | 1x1 low stone, posy and candle; placed beside a memorial or on a lawn/gravel verge. | Spreading candle/flower pixels into the next block. |
| Stone lantern | 1x2 stone fixture with a warm recessed window; use in pairs around an entrance. | Blocking the only walkable row. Both blocks are solid; the upper row can overlap a player behind it. |
| Street lamp | 1x2 iron post with cool violet glass; suitable along the south road. | Replacing its violet glass with neon lighting. Both blocks are solid; upper row over-player. |
| Food/water bowls | 1x1 paired bowls for Fuji, homes, shelters and route rest areas. | Door approaches; the entire block is solid. |
| Straw bed | 1x1 straw in a low wooden frame; flat and walkable. | Treating the frame as a wall. |
| Rest shelter | 2x2 open-front wooden lean-to with the same straw bed under its roof. No door, bars or cage. | Using it as an enterable building. All four blocks are solid; roof row can overlap the player. |

The shelter is included even though listed as optional, because it is part of the requested yard preview. Optional lavender sway and lantern flicker are omitted in this review build.

## Palette decision

The five supplied GPL files are preserved **byte-for-byte**, in their supplied order. Ground uses the brief's bank-0 order, not the older street pack's reordered indices 1–7.

One new palette, `lavender_town.gpl` in bank 10, contains the quiet blue-grey slate ramp, three sage foliage tones, three flower purples, and copied kit stone colours. Slate, gravel and lavender use this bank. The palette includes the kit's exact cobble colours at indices 10–13; transition cobble pixels were copied from the native supplied map. Lawn is not recoloured or baked into a new palette: transparent edges show the existing lawn underneath.

| Bank | Palette | New uses |
|---|---|---|
| 0 | kit_ground | Existing map/lawn/cobble context, supplied unchanged |
| 1 | kit_water | Supplied unchanged; no new piece uses it |
| 2 | kit_wood | Iron railing, bowls, straw bed, shelter |
| 8 | kit_plants | Offering stone's upper two 8x8 tiles |
| 9 | lavender_tower | Memorial stonework, stone lantern, violet street lamp |
| 10 | lavender_town | Slate, gravel, lavender and their joins |

Every 8x8 tile uses exactly one bank. The offering stone intentionally combines plant-bank tiles above tower-bank tiles. Its PNG embeds a display palette containing the used RGB entries from both, without changing any index number. Its `palettes_8x8` grid is authoritative for import; do not load that combined display palette as a new game palette. Other pieces use one bank throughout.

The supplied WATER palette has non-multiple-of-eight channels at indices 9–11. It is preserved to obey the unchanged-palette requirement; **none of these entries is used by new art**. All colours actually used in new artwork have channels divisible by eight. `validation.json` records this inherited palette exception instead of claiming the entire supplied palette is compliant.

## Native format and import

- PNGs in `tiles/` and `transitions/` are authored directly as integer indices at 1x: 4-bit indexed PNG, 16 entries, index 0 transparent, alpha only 0/255. No tracing, downscaling, quantisation, antialiasing or dithering.
- Footprints use 16px blocks. Each per-piece JSON records its footprint, exact dimensions, solid and walkable block coordinates, and an 8x8 palette grid. Coordinates are local and start at the top left.
- `over_rows` is the **number** of leading 16px rows eligible to draw over a player behind the object. The lantern, street lamp and shelter use 1; other pieces use 0. Collision is independent of this drawing priority.
- New pieces have no cast pixels outside their footprint. Dark bases and soffits supply depth inside it. Upper-left light, recessed lamp windows, raised stone bases and roof eaves follow the approved guide; the brief's no-external-shadow rule takes precedence over general fixture shadows.
- Every piece is static in v0.1: one frame, `frame_speed: 0`. The `frames` field refers to its only full-size PNG.
- `tiles_4bpp.bin` contains the canonical shared graphics, 32 bytes per tile, left pixel in the low nibble. `tile_pool.json` describes it. Each piece supplies `tiles_8x8`, `flips_8x8` and `palettes_8x8`; IDs are zero-based into the global pool. The validator reconstructs every PNG's indices from this binary data.

## Autotile conventions

Each surface supplies all 256 masks. Bits are N=1, E=2, S=4, W=8, NE=16, SE=32, SW=64, NW=128. A set bit means lawn/outside that material, not a same-material neighbour. Cardinal boundaries take priority over diagonal ones. Quadrants are assembled from the referenced piece and quadrant in the recipe. Inside corner names follow NE, SE, SW, NW order.

Slate has four 16x16 phases, `large_NW`, `large_NE`, `large_SW`, `large_SE`, forming a 32x32 repeat. Use `slate/phase_recipes.json` to keep that phase at boundaries. Anchor the phase to the map or a fixed surface origin, not each individual patch. Generic `center` is a quiet infill; use the phase pieces for broad areas.

`to_<other>_<side>` puts the other surface in the named outer 8px half. `reciprocal_joins.json` provides the reverse naming aliases; they refer to the same image and should not be imported twice. Phased slate joins also include a final NW/NE/SW/SE suffix.

Lavender's `center_b` and `center_c` are optional interior fill alternatives. The edge recipes use the stable standard fill so the boundaries retain the same footprint. Beds are transparent between plants and should be placed on existing lawn. Gravel and slate also need the existing lawn beneath their transparent outside edges.

Railing has all 16 cardinal masks, with the opposite convention: a set N/E/S/W bit means the rail continues that way. The open gate is explicitly placed as a 3x1 assembly; it is not inferred from neighbouring rails. Place solid fixtures on complete blocks, even where the artwork has transparent margins.

## Tile budget

| Group, including joins | Unique 8x8 tiles | Limit |
|---|---:|---:|
| Slate | 17 | 20 |
| Gravel | 12 | 12 |
| Lavender beds | 9 | 16 |
| Iron railing and gate | 10 | 10 |
| Memorial pieces | 14 | 14 |
| Street lamp | 4 | 4 |
| Fuji's yard | 11 | 12 |
| **Shared union** | **67** | **90** |

Individual details: rounded stone 3, flat marker 2, flower stone 3, offering stone 3, stone lantern 4, street lamp 4, paired bowls 3, straw bed 2, shelter 8. The gate uses 4. Counts include the transparent tile where it occurs. Horizontal, vertical and combined mirrors merge; rotations remain distinct. Identical index graphics may share VRAM across different palette banks, with palette selection kept per map tile. Group counts therefore must not be added to obtain the union.

This is 9 below the ideal 76, 23 below the hard limit, and would leave 86 of the stated 153 free tile slots if all 67 new graphics are imported. Existing context buildings, cobble, lawn and Town Props benches are excluded. A town importing only selected pieces pays only their shared subset.

## Validation and reproduction

`validation.json` covers PNG bit depth, embedded colour counts, supplied palette preservation, each used tile's bank/RGB, binary alpha, dimensions, footprint/collision partitions, static frame alignment, canonical tile counts, binary+flip reconstruction, all neighbour recipes, reciprocal joins, gate clearance and preview reservations. It also checks exact nearest-neighbour preview copies and that the supplied buildings remain unchanged in the composite.

Run from any directory with Python, Pillow and NumPy installed:

```sh
python3 source/build.py
python3 source/previews.py
python3 source/validate.py
python3 source/package.py
```

The supplied native references, approved style guide and copied Town Props bench context are included for reproducibility. Those context images are not new deliverable tiles. This package is a review set, not a modified ROM or map file; actual engine palette-bank assignment and layering still follow the game's importer.

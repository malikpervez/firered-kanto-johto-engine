# Kanto Street Textures v0.3

Color revision for visual review. Small sidewalk diamonds alternate warm sand and cream; diagonal brick courses alternate rust and coral; large plaza diamonds alternate blue-gray and ivory, with a brass border and compass accent. The stronger v0.2 patterns remain. Asphalt and road markings are unchanged. All exported pieces retain their names and dimensions.

The supplied ground palette remains byte-identical. Only unused street slots 3–6 in the separate city palette change, so streets rendered through that palette still keep their original colors. No extra palette bank is introduced.

Native street surfaces following Claude's `Street_Textures_v0.1_prompt.md`. Asphalt, raised concrete pavement and crossings establish city streets; terracotta paving, larger granite slabs and planted islands distinguish shopping streets and civic plazas. The supplied ground palette is unchanged, byte for byte.

## Review images

- `previews/patterns_before_after_4x.png`: equal-scale v0.2/v0.3 material samples.

- `previews/saffron_city_block_1x.png` and `_3x.png`: a four-lane north–south avenue crossing a two-lane street, with four crossing approaches, lowered kerbs, tactile blocks, manholes, storm drains, street trees and a granite Silph plaza.
- `previews/celadon_shopping_street_1x.png` and `_3x.png`: terracotta shopping pavement, Department Store, Hotel and Game Corner, granite inset and planted islands.
- The `_gba_1x.png` files are exact **240×160** crops; `_gba_3x.png` magnifies those crops without smoothing.
- Eight `<surface>_autotiles_4x.png` sheets label every piece. The mosaic is also shown at exact 4×.

These are material demonstrations, not replacements for either city's actual map plan. Buildings, trees and bushes in the previews are unchanged approved references. Their artwork is retained in `source/context/` only to make previews reproducible and is excluded from this pack's street-tile counts.

## Tile allowances

All figures count the actual delivered 8×8 palette-index tiles, with horizontal, vertical and combined flips merged. Ninety-degree rotations are distinct. Counts include all transitions and reference-material halves; transparency counts if present. Counts overlap, so do not add individual rows to obtain a union.

| Selection | Unique tiles | Allowance |
|---|---:|---:|
| Part A, all streets | **52** | 64 |
| Part B, complete catalog | **44** | 48 |
| Granite + compass | 19 | Saffron has about 29 available |
| Granite + compass + planter | 24 | Saffron has about 29 available |
| Brick + planter | 26 | Celadon has about 39 available |
| Celadon supplied preset | **32** | 39 |
| Saffron supplied preset | **24** | 29 |

| Surface, including its transitions | Tiles on its own |
|---|---:|
| Asphalt | 23 |
| Pavement | 27 |
| Crossing | 3 |
| Details | 16 |
| Brick | 21 |
| Granite | 16 |
| Mosaic | 4 |
| Planter | 5 |

Part A uses 52 of the requested 64 tiles. The entire Part B catalog uses 44 of 48. **Do not import the whole Part B catalog into Celadon's stated 39-tile allowance.** Use `city_presets/celadon.json`: all brick, planter and compass pieces plus large granite phases and pavement joins, totaling 32 tiles. This includes every piece in the Celadon preview. Saffron's preset includes all granite, compass and planter pieces, totaling 24 tiles. Optional compact GBA pools under `tile_pools/celadon/` and `tile_pools/saffron/` contain these selections with remapped local tile IDs.

The selection is about available shapes, not reduced image quality. Celadon's preset supports its rectangular granite inset; full granite lawn-edge autotiling remains in the complete catalog and Saffron preset. Primary street graphics are separate from these city secondary counts. Claude must still check current map allocations and palette-bank availability in the game repository. No actual full-map import or 384-tile bank test was performed here.

## Formats and palette compatibility

Every game piece is a 4-bit indexed PNG with exactly 16 palette entries, transparent index 0 and alpha only 0/255. Every channel is divisible by eight. Pieces are 16×16, except the 32×32 compass. All artwork was authored directly as integer palette indices at its final native size. Preview enlargements use nearest-neighbour only.

`palettes/road_existing.gpl` is copied unchanged from the uploaded paving pack. Keep its index order during editing; Claude's importer maps it by RGB to the kit's existing ground bank. There is no proposed global palette change.

`palettes/streets_city.gpl` uses rust (index 3: 144,72,64), coral (4: 192,112,88), terracotta highlight (5: 224,152,112), and blue-gray (6: 136,168,176). These four slots replace the v0.2 city colors. Every colour actually used by Part A is retained at the same index in this palette, including the asphalt, concrete, paint, shadow and tactile colours. Thus **the street PNGs can also be assigned the city palette without recolouring their pixels**. Do not use this city palette to render the original lawn or other unrelated primary assets; green slots differ. Choose an available city palette bank from the game's established allocation, not an assumed fixed bank number.

`tile_pools/part_a/` and `part_b/` contain optional reversible GBA data: `tiles.4bpp`, BGR555 `palette.pal`, and `assemblies.json`. Each 8×8 tile is 32 bytes, lower nibble first. Assemblies store a local tile ID plus H/V flags per quadrant. They do not assign global tile IDs or palette banks. Surface JSONs include the same `tiles_8x8` and `tile_flips` arrays. These are graphics assemblies, not game collision or elevation data.

## Surface use

- **Asphalt:** ordinary city roads and long avenues. Its mid-dark base stays quieter than the buildings. Use `center` most often; place the patched/aggregate `center_b` and polished `center_c` sparingly, rather than alternating them everywhere. Keep countryside routes on their existing dirt or cobble.
- **Pavement:** small diamond-set concrete slabs in alternating sand and cream, with darker diagonal joints and short pale bevel highlights, repeating on a 16px grid. Sand uses the existing ground palette index 10; cream uses index 13. `center_b` adds a small crack; `center_c` adds an inset drain cover. Kerbs show a light top and a down/right shadow. Avoid covering all civic plazas with this smaller slab grid.
- **Crossing:** road markings and flush ramps, not obstacles. `road_EW` has north–south stripes for an east–west road; `road_NS` is the converse. `end_N/E/S/W` names the pavement-facing end. `dropped_kerb_N/E/S/W` names the road side. Put tactile paving on the pedestrian approach immediately behind a ramp. The same end art can repeat where its existing breathing margin already meets the ramp.
- **Details:** `manhole` belongs on asphalt; `tree_grate` and `tactile_paving` belong on pavement; `storm_drain_*` belongs on the corresponding pavement/asphalt kerb. A 16px tree grate goes under the trunk of an existing 2×2-block tree, not under its entire crown. Preserve the tree's existing palette and collision. Avoid placing obstacles on a ramp or the only walkable entrance approach.
- **Brick:** alternating rust and coral diagonal running-bond terracotta with clearly outlined larger pavers for Celadon pedestrian shopping streets and squares. Do not use it as the default vehicular road. The centre variants have identical borders.
- **Granite:** large civic forecourts, Silph and Department Store approaches. The `large_NW/NE/SW/SE` phase pieces form a repeating **32×32 diamond-slab pattern** with blue-gray and ivory slabs, a darker joint and a pale inner bevel. Repeat those four in a 2×2 block pattern. Ordinary `center` variants provide a smaller diamond pattern for patterned border strips; the edge pieces add a dark outline and a narrow brass border band. Do not randomly substitute a phase piece with a plain centre where that would break a slab joint.
- **Mosaic:** the 2×2-block compass is a flat inlay on granite, with a larger dark-outlined star, light stone facets and a brass centre, set into the surrounding diamond pattern. Keep it off a vehicular lane and leave room around it.
- **Planter:** a low raised stone rim with granite on the outside and a transparent planting area inside. Place approved lawn/flowers below it. It is a border overlay, not a new ground texture; `center`, `center_b` and `center_c` are deliberately transparent aliases because the underlying approved ground supplies their variation. Apply collision to the planted area/rim in the map, not to every transparent quadrant automatically. Use bushes or trees as separate existing objects.

## Autotiles and joins

The eight folders follow `dressed_stone.json` schema 1: a `<surface>.json`, `tiles/` and `transitions/`. For the four ground surfaces, `N` means **lawn outside to the north**, and likewise for other directions. Index 0 reveals the lawn underneath. The same pavement edge set can be composited over asphalt to make raised pavement islands and their corners. The planter uses the same outside-direction naming but has granite outside and lawn inside.

Each edged set has all four inside corners, all six pairs, all four triples and `in_ALL`. Corner lists use the clockwise order **NE, SE, SW, NW**, matching names such as `in_NE_SE_SW`. `autotile_recipes.json` supplies all 256 neighbor masks by assembling native 8×8 quadrants; no resampling or new graphics are necessary. Adjacent cardinal edges take precedence over their diagonal notches. Each named edge and corner combination is verified against its recipe.

`to_<other>_<side>` puts the other material on that half of the block. `pavement/to_asphalt_*` contains the raised kerb at the half-block boundary, with its face/contact shadow extending across that boundary where needed. The reference cobble and dressed-stone halves are copied exactly, not redrawn. Use the paired reference centres when continuing those materials.

Included joins: pavement↔asphalt; pavement↔cobble; pavement↔dressed stone; asphalt↔cobble; brick↔pavement; granite↔pavement. Reciprocal names that belong to existing materials need no new PNGs: use the opposite-side counterpart. For example, `cobble_to_asphalt_N` uses `asphalt/to_cobble_S`; `pavement_to_brick_N` uses `brick/to_pavement_S` **in the city palette**. The generated `reciprocal_joins.json` lists all such aliases.

Dashed `H`/`V` names describe the painted line's direction. The `_boundary` variants put the stroke on the block's top/left boundary for evenly spaced two-block lanes. `lane_edge_N/E/S/W` puts a solid line along the specified kerb side. Road paint never changes collision.

## References, validation and rebuild

Reference paving: [Dressed_Stone_Paving_v1.zip](https://drive.google.com/file/d/1jlGM88zTBtLJfB9PUzc1SD1HKP2C4U5N/view), exported by Claude from `v2-main`. Its source JSON, PNGs, palette and provenance README are preserved under `source/reference_paving/` and are excluded from new tile counts. Design brief: [Street_Textures_v0.1_prompt.md](https://drive.google.com/file/d/1b7RWCfBki-nkPc9_zqRZ6kt4fkxeySO7/view).

With Python 3, Pillow and NumPy, run `source/build.py`, `source/previews.py`, `source/export_validate.py`, then `source/package.py`. The validator independently reads exported PNGs and tests their format, palette, alpha, sizes, centre seams, complete corner naming, recipe equivalence, exact reference halves, counts and lossless GBA reconstruction. `validation.json` records every result. Full-map import, game rendering and collision remain Claude's integration checks after visual approval.

## Revision checks

`source/baseline_v02/` holds the immediate previous art for before/after evidence only; `baseline_v01/` retains the earlier pattern reference. Neither is additional art to import. The validator checks the unchanged ground palette, the exact four changed city slots, all road-only pieces, the asphalt halves of transitions and ramps, unchanged piece names and dimensions, and all native formats and corner recipes. City presets are independently counted, reconstructed from GBA data, and checked against actual preview placement records. `validation.json` records 547/547 passing checks.

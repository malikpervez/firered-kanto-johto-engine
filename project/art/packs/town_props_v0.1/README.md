# Kanto Town Props v0.1

Native street furniture for Kanto towns and routes, with reusable shapes for Johto. This review pack contains all nine requested categories: a self-contained animated fountain, four wooden bench facings and a stone bench, flower tub, litter bin, guardian statue, fingerpost, picnic table, bicycle rack, and twelve modular bridge pieces. Optional larger fountains and narrow statues are not included in this version.

The props follow the remakes' `BUILDING_STYLE_GUIDE.md`: upper-left light, raised lips and seats, shaded returns, dark undersides, restrained material seams, and a dark foundation inside the footprint. Every pixel is authored as an integer palette index on the final grid. No artwork is downsampled, traced, quantized, antialiased or dithered. Preview magnification is nearest-neighbour.

## Review images

Every scene below has a native **240×160** `_1x.png` and a **720×480** `_3x.png`:

- `town_square`: fountain, inward-facing benches, flower tubs and bin on the approved dressed-stone paving.
- `town_square_granite`: the same placements on the approved granite phases.
- `town_square_slate_blue_proof`: a color-compatibility proof, described below.
- `museum_front`: statue, stone benches and flower tubs before a civic facade stand-in.
- `route_corner`: fingerpost and picnic table on approved lawn, beside an existing dirt path.
- `bike_shop`: bicycle rack beside a shop entrance, with the entrance approach kept clear.
- `footbridge_canals`: north–south and east–west crossings, each at one- and two-block deck widths, over one- and two-block canals. Top-left is NS1, top-right EW1, bottom-left NS2, bottom-right EW2.
- `fountain_on_brick` and `fountain_on_lawn`: the identical fountain PNG directly on each ground. Neither scene uses pond water beneath the fountain.

`fountain_frames_1x.png` and `_4x.png` show all four full-size frames in sequence. `fountain_animation_3x.gif` previews motion. `props_gallery_1x.png` / `_3x.png` show all non-bridge pieces; `all_props_materials_1x.png` / `_3x.png` compare every prop and bridge middle on dressed stone, slate proof, granite and lawn. Label pixels in contact sheets are review typography, not game art.

**Context substitutions:** the supplied `reference_cerulean_square_3x.png` was not accessible in the connected folder. The slate-blue proof reuses the existing street brick's exact geometry with explicit indices from `kit_water`; it is a compatibility background, not a new ground asset. The museum scene uses the unchanged approved Pokémon Lab facade, still labeled LAB. The shop scene uses the unchanged approved Poké Mart. These are placement demonstrations, not museum/Bike Shop redesigns or replacements for map plans. No context building, tree, bush or terrain is part of the new prop tile counts. `source/context/provenance.json` records the references.

## Palettes and PNGs

The two GPL files are byte-for-byte copies of the uploaded `kit_water.gpl` and `kit_wood.gpl`. Index order is unchanged. Every game PNG is indexed, 4 bits per pixel, with exactly 16 palette entries, transparent index 0, and alpha only 0 or 255. All dimensions are whole 16px blocks. Each supplied piece uses one palette throughout; its JSON still names the palette for every 8×8 tile, so the importer has an explicit grid.

Use the existing kit water bank 1 and wood bank 2. No additional palette is proposed. The provided water RGB values at indices 9–11 include channels not divisible by eight. They are preserved exactly as requested, not silently rounded. No replacement hardware palette binary is supplied; use the game's existing banks. Preview backgrounds and approved buildings retain their own original palettes.

Blue-and-ivory flowers with warm centers fit the existing water palette; the tub uses its terracotta/sandstone colors. The bicycle has a red frame from the wood palette. Neither needs another color.

## Tiles and animation

Counts are unique 8×8 **palette-index graphics**, with H, V and combined flips merged; 90-degree rotations are distinct. Transparent tiles count if present. A palette bank is a tilemap attribute, so matching index graphics can share storage between banks. Individual counts overlap and must not be added to estimate a union.

| Piece or complete group | Runtime tiles | Budget |
|---|---:|---:|
| Fountain 3×3, including animation slots | 22 | 24 |
| Wooden bench, south alone | 4 | group below |
| Wooden bench, north alone | 4 | group below |
| Wooden bench, east alone | 4 | group below |
| Wooden bench, west alone | 4 | group below |
| All four wooden bench facings together | 10 | 16 |
| Stone bench | 4 | 4 |
| Flower tub | 4 | 4 |
| Litter bin | 3 | 4 |
| Guardian statue 2×2 | 9 | 12 |
| Fingerpost | 6 | 6 |
| Picnic table | 8 | 10 |
| Bicycle rack | 6 | 6 |
| All twelve footbridge modules together | 11 | 16 |
| Entire catalog together | 82 | no shared catalog target |

The full catalog has 50 water-palette and 33 wood-palette runtime graphics when counted separately, or 83 if the importer deliberately keeps separate palette pools. One graphic is shared across the banks, yielding **82** in a common graphics pool. A town takes only its selected pieces. The **3-tile litter bin** is a complete option for a town with just three free tiles.

Fountain timing is **16 game frames per image at 60 fps**: four frames loop every 64 game frames, about 1.067 seconds. The jet, falling water and basin ripples animate. Exactly **eight tile positions** change over the whole cycle; they reduce to five unique animation streams after flips. All frame silhouettes, origins, rim, foundation and pedestal stay fixed.

As requested, each animated tile stream counts **once** against the runtime budget. The fountain contains 22 resident graphics slots but 37 distinct graphic images across all animation frames. The entire catalog contains 97 distinct graphic images across time. `tile_report.json` exposes both counts so ROM artwork storage is not confused with simultaneous tileset occupancy. Do not deduplicate an animated tile against a static tile just because their first frame matches.

`tile_pools/tiles_f1.4bpp` through `tiles_f4.4bpp` are optional, reversible native GBA graphics. Each tile is 32 bytes, low nibble first. `assemblies.json` gives local tile IDs, flips, per-tile palettes and animated slot IDs. The first pool is the static/base state; only marked animation slots need updates. These are catalog-local IDs, not global tileset allocation. Import selected assets, not this whole convenience pool, into a town with limited room.

## Placement notes

| Piece | Footprint | Where it belongs | Avoid |
|---|---|---|---|
| Fountain | 3×3 | Cerulean square, town centers, civic plazas, broad parks | Door approaches, one-block paths, pond-water underlays. Its basin already holds water. |
| Wooden benches, S/N | 2×1 | Facing a fountain, statue, flower display or park path | Blocking the only entrance or crossing. Leave space in front. |
| Wooden benches, E/W | 1×2 | Side edges of a square, route rest areas | Treating the backrest as a walk-through row. |
| Stone bench | 2×1 | Museums, League forecourts, formal plazas | Dense rows that crowd the centerpiece. |
| Flower tub | 1×1 | Squares, doorsteps, path edges | A doorway's approach block or the only walkable lane. |
| Litter bin | 1×1 | Beside seating, shops and route picnic sites | The center of a ceremonial square or a door threshold. |
| Guardian statue | 2×2 | Museum/League forecourts, a square without a fountain | Small routes or placing it so close to a building that its head overlaps a doorway. It is a generic pointed-ear creature, not a named species. |
| Fingerpost | 1×2 | Route junctions and town edges | Drawing destination text into the PNG. Two arms point east and west; game dialogue supplies wording. |
| Picnic table | 2×2 | Parks, route rest stops, camps | A paved square's narrow circulation strip. Both attached benches belong to the solid prop. |
| Bicycle rack | 2×1 | Bike Shop, station or Cycling Road gates | Filling a gate's approach. Contains one bicycle and a small metal rack. |
| Footbridge | module-dependent | Narrow canals/streams, with both end modules on stable banks | Open sea, a terminating middle module, or making its entire deck solid. |

All solid props have every footprint block listed in `solid_blocks`, including transparent corners, per the brief. `walkable_blocks` is empty for those props. They have no hidden ground layer. The fountain has no cast shadow on surrounding ground: its dark lower course is part of the stone basin inside its own footprint.

## Layering and collision

`over_rows` is an integer **count of leading 16px block rows** drawn in the upper layer: 0 means none, 1 means row 0. `over_row_indices` supplies the equivalent explicit list. It does not change collision. Fountain, wooden benches, statue, fingerpost and picnic table use one over row; other supplied pieces use zero. This lets a player's tall sprite pass visually behind upper art while the prop's occupied blocks stay solid.

For bridges, all deck blocks are listed as walkable and `solid_blocks` is empty. Rail geometry lives inside those same narrow metatiles, so whole-block collision cannot separately mark just the rail pixels as solid. Each JSON therefore also supplies **`collision_edges`** to forbid movement off the two sides and `parapet_collision_rects_px` for the rail geometry. Preserve open movement along the bridge axis. Use the game's bridge/edge behavior when importing; do not invent solid deck blocks to emulate the rails. The one-block-wide bridge still provides one traversable metatile lane. The two-block version provides two lanes.

## Bridge pieces and assembly

| Orientation / deck size | End / middle / end | Module size | Tile counts individually |
|---|---|---|---|
| North–south, 1 block wide | `bridge_ns_1_north`, `bridge_ns_1_middle`, `bridge_ns_1_south` | 1×1 each | 4 / 2 / 4 |
| North–south, 2 blocks wide | `bridge_ns_2_north`, `bridge_ns_2_middle`, `bridge_ns_2_south` | 2×1 each | 5 / 3 / 5 |
| East–west, 1 block tall | `bridge_ew_1_west`, `bridge_ew_1_middle`, `bridge_ew_1_east` | 1×1 each | 3 / 2 / 3 |
| East–west, 2 blocks tall | `bridge_ew_2_west`, `bridge_ew_2_middle`, `bridge_ew_2_east` | 1×2 each | 4 / 3 / 4 |

Place the first end on its bank, repeat the middle for the water's width, then place the opposite end on the other bank. North–south decks cross water flowing east–west; east–west decks cross north–south water. Existing animated water remains underneath. Transparent margins and the small underside openings reveal it; no blue water is painted into any bridge PNG. End pieces contain their bank contact, while middle pieces repeat the stone deck and raised parapets. `footbridge/assembly_examples.json` contains sequences for 1-, 2-, 4- and 8-block canals, for both directions and both deck widths.

## Folder contract and rebuilding

Each requested category has its own folder, `tiles/` PNGs, one JSON per piece, and an `index.json` enumerating the pieces. `asset_index.json` indexes the entire pack. Every piece JSON includes footprint, frames/speed, palette grids, collision, over rows, local graphics IDs and flip flags. The fountain frames are full-size `fountain/tiles/fountain_3x3_f1.png` through `_f4.png`.

With Python 3, Pillow and NumPy, run `source/build.py`, `source/previews.py`, `source/validate.py`, then `source/package.py`. All authored prop pixels are in `build.py`; it writes native indices directly. Reference artwork is preserved in `source/context/`, so previews can be rebuilt even without the original folders. `source/BUILDING_STYLE_GUIDE.md` is the guide used for this pass.

Validation independently rereads exported files and reports **367/367 checks passed**: PNG encoding, exact palettes/order, alpha, footprints, collision coverage, over rows, every tile budget, animation alignment and changed positions, stable stone pixels, mirrored benches, bridge continuity, lossless reconstruction from 4bpp, and nearest-neighbor previews. Actual game import, final town-wide tile allocation, engine collision behavior and layer priority still need checking in the game repository.

This pack is for design review. It has not been uploaded to Google Drive.

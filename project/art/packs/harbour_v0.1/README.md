# Kanto Harbour Textures v0.1

Design-review pack for Vermilion and reusable Kanto/Johto ports. No game map, collision table, ROM, existing asset pack or approved palette was edited. Drive upload waits for design approval.

## What is included

| Surface | Unique 8x8 tiles | Budget |
|---|---:|---:|
| Fan setts, every phase, lawn boundary and join | 17 | 20 |
| Quay flags, lawn boundaries and joins | 14 | 14 |
| Coping, water faces, corners, ends, ladder and ring | 16 | 16 |
| All five details | 9 | 10 |
| **Union, shared graphics counted once** | **43** | **60** |

43 tiles occupy 1,376 bytes of uncompressed 4bpp graphics. Against the stated approximate 110 free tiles, this leaves about 67. This conservative count includes the existing cobble and pavement quarters present inside joins. Import only the pieces the map uses. Context buildings, streets, benches, sea, planks and editor overlays in the previews are existing art and are not part of the new pack's count.

H, V and HV reflections count once. Rotations remain separate. Transparent tiles count. There is no animation in this pack; water visible beneath the wall remains the game's animated open water.

## Surfaces and placement

**Fan setts.** Overlapping granite fans use two main stone tones and darker radial/course joints. Their repeat is 32x32, four native 16x16 pieces: `large_NW`, `large_NE`, `large_SW`, `large_SE`. Keep a fixed phase origin for each area. The reference square starts at block (24,7), so the origin is (24,7), independent of the global map parity. Use `phase_recipes.json` to keep the pattern through borders and concave corners. The small `center` is an alias of the NW phase for compatibility, not the recommended repeating fill. Use setts for squares and port approaches; avoid filling the entire city or mixing phase origins within one square. The optional red stones are omitted so the floor remains quiet.

**Quay flags.** Larger square stone flags have continuous mortar joints, restrained worn sections in the joints and pale bevels. Use them on waterfront walks, service edges and cargo courts. Their calm 16x16 repeat contrasts with the smaller fan setts. Do not use flags as a water bank or an impassable barrier. Lawn boundaries are transparent outside their rim, exposing the existing lawn underneath.

**Quay wall.** This is a two-block shoreline assembly, never a replacement water texture. The land block receives the coping overlay; the adjacent water block receives the transparent face. The south face is taller, the east and west faces are narrow, and the north water piece is only a shadow under the coping lip. Dark lower masonry, a wet band and a thin foam edge sit above open water. There is no natural grass/dirt water bank in these pieces.

| Water lies outside land to… | Land block | Water-block offset | Water overlay |
|---|---|---|---|
| South | `edge_S` | (0,+1) | `wall_S` |
| East | `edge_E` | (+1,0) | `wall_E` |
| West | `edge_W` | (-1,0) | `wall_W` |
| North | `edge_N` | (0,-1) | `wall_N` |

Use `quay_wall/autotile_recipes.json` for the coping, with 1 meaning water outside the current land block. Use `quay_wall/water_recipes.json` for the water overlay, with 1 meaning neighbouring land or dock. Both cover all 256 masks. The water recipes give cardinal faces precedence and join diagonal caps from the same native quarters. `wall_outer_*` and `wall_inner_*` are named corner conveniences. Inside corners are ordered NE, SE, SW, NW.

`wall_end_E` stops against a plank block on its east; `wall_end_W` stops against one on its west. They extend to the full block boundary, without a half-block water gap. These live in `quay_wall/transitions/`. Keep the game's planks in the neighbouring block. Do not apply a land coping across the player's path into a pier. The optional `wall_S_ladder` is decorative, not an automatic climb or Surf transition. `edge_S_ring` stays walkable.

Coping files are stored with the wall so all shoreline graphics have one budget group. The requested logical names `quay/edge_S`, `quay/edge_E`, `quay/edge_W` and `quay/edge_N`, including the corners and ring, resolve through `quay/coping_aliases.json`. They reference the same files and add no duplicate graphics.

## Harbour details

| Detail | Tiles alone | Collision | Where to use it |
|---|---:|---|---|
| `mooring_bollard` | 3 | Solid | Quay ends and cargo edges, leaving a walking lane behind it. |
| `bollard_rope` | 3 | Solid | Working docks and tied-up berths. Keep away from narrow entrances. |
| `coiled_rope` | 2 | Solid | Cargo corners or beside a bollard, not in the only walking lane. |
| `harbour_drain` | 1 | Walkable | Flat within flags, not on a wall face or on open water. |
| `lifebuoy_post` | 2 | Solid | Near a ladder or harbour corner. Its red is the pack's vermilion accent. |

The pieces are all 1x1 blocks, transparent around their silhouette. None extends into a block above its footprint, so `over_rows` is 0 for all five. All their blocks are solid except the drain. The optional anchor/plinth is not included.

These restrained materials suit Cinnabar, Olivine and Cianwood as well as Vermilion. No city name, lettering or local emblem is baked into the textures.

## Palettes and exact native pixels

The pack uses **the existing GROUND palette**, not a new Vermilion bank. Its grey stones, cream bevel and dark mortar cover the two floor surfaces. All three GPL files are copied byte-for-byte from the approved packs, with their original order:

- Bank 0: `road_existing.gpl`, JSON name `kit_ground`.
- Bank 1: `kit_water.gpl`, JSON name `kit_water`.
- Bank 2: `kit_wood.gpl`, JSON name `kit_wood`.

Every importable PNG is 16x16, indexed 4bpp, exactly 16 palette entries, with index 0 transparent and binary alpha. Every 8x8 quadrant has exactly one declared bank in `palettes_8x8`. No RGB conversion, automatic quantization, tracing, image downsampling, antialiasing or dithering was used. Native palette indices are authored directly. Enlarged previews use nearest-neighbour only. The supplied building style guide is included in `source/`.

**Existing palette conflict.** The approved WATER palette contains values not divisible by 8 at indices 9 `(112,172,228)`, 10 `(120,196,212)` and 11 `(208,236,244)`. Keeping that file exact and requiring all its entries to be multiples of 8 cannot both be satisfied. This pack preserves the file exactly and does not use those entries in any new harbour pixel. Every colour actually used by the new art is divisible by 8. `validation.json` records this explicitly as `PASS_WITH_PALETTE_EXCEPTION`, not as a fully compliant palette. Reference water in the previews is unchanged and may use those original entries.

`bollard_rope` mixes WATER in its top row of 8px tiles and WOOD in its bottom row. Its PNG embeds a display palette assembled from those existing colours: WATER entries plus WOOD entries 2–5. The used indices do not conflict, and each pixel already has the right numeric index for its assigned tile bank. This display palette is **not a new game palette**. Importers must obey `palettes_8x8` instead of assigning one bank to the whole image. All other pieces use one existing palette throughout.

## Schema and integration

`setts/setts.json`, `quay/quay.json` and `quay_wall/quay_wall.json` follow dressed-stone schema 1: native pieces in `tiles/`, boundaries in `transitions/`, and quadrant recipes for every neighbour mask. Mask bits are N=1, E=2, S=4, W=8, NE=16, SE=32, SW=64, NW=128. Each recipe copies 8x8 quadrants without scaling or rotation. Diagonal names follow NE, SE, SW, NW even though the raster assembly order is NW, NE, SW, SE.

`to_<other>_<side>` means the other material is on that side. Ground joins contain the original cobble or pavement half. Reciprocal names alias the identical PNG in `reciprocal_joins.json`. The setts include phase-specific versions of all joins so a long square keeps its 32px rhythm at the street and Route 6 connections. These variants add no unique graphics. The quay's `to_setts` boundary uses the canonical NW fan phase; align the adjacent fan phase to that boundary.

Each detail and wall piece also has its own JSON. It declares `footprint_blocks`, `palettes_8x8`, collision, walkability, `over_rows` and, for walls, `block_location: land|water`. Land coping and drains remain walkable. Water faces have `water_blocks: [[0,0]]` and `surfable: true`, with no land-walkable block. Use the engine's shore collision so a walking player cannot cross into water without Surf. The decorative wall should not accidentally make the water block solid.

Composite order is existing ground or animated open water, then the new overlay, then appropriate props/actors. Do not put a natural water-edge tile beneath the wall. Preserve the wooden deck's walkable behavior at pier openings.

`tile_pool/tiles.4bpp` and `tile_pool/assemblies.json` provide a lossless optional GBA export. Tiles are 32 bytes, low nibble first. The assemblies preserve H/V flips and each quadrant's palette bank. Only the selected graphics and metatiles need importing. No game map source or emulator was available for an engine import test; the exported data and collision declarations have been checked independently.

## Reference previews

The supplied unmarked map is exactly 60x42 blocks, 960x672 pixels. The previews composite directly onto it at 1x:

- A: (24,7), 19x4 blocks of fan setts. The north join remains cobble toward Route 6.
- B: (6,11), 54x4 blocks of the unchanged Street Textures v0.3 asphalt and kerbs.
- C: (7,22), 49x2 blocks of quay flags. Four Town Props south-facing benches occupy the original bench positions.
- D: water row 24, omitting the wooden pier at columns 37–39 and dock at columns 44–54. Wall returns follow the pier sides and dock sides/bottom. The dock's wooden interior and the full pier are pixel-identical to the reference.
- E: existing pier and dock artwork is retained. No new planks are supplied.

The buildings, NPCs and map-editor symbols remain original context. `previews/placements.json` gives the overlay locations. `source/context/provenance.json` identifies unchanged references and the native open-water/plank crops used in the reusable corner demonstration.

Previews include the complete before/after map at 1x and 3x, square and promenade close-ups, a reusable quay corner and pier-end demonstration, four 240x160 GBA crops with 3x copies, a materials gallery, every named tile labelled at 4x, and all 256 neighbour masks for each surface labelled at 4x. Preview RGB images and labels are not importable assets.

## Rebuilding and validation

Run in order with Python 3, Pillow and NumPy:

```
python3 source/build.py
python3 source/previews.py
python3 source/validate.py
python3 source/package.py
```

The included reference crops and palette copies make the pack reproducible. Validation checks PNG headers, palette order and byte identity, active RGB values, alpha, size, collision declarations, all recipe masks and phase variants, reciprocal files, transition halves, lossless 4bpp reconstruction, tile budgets, exact 3x enlargement and unchanged reference buildings/decks. Checksums cover the delivered contents.

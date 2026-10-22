# Route 22 — Rock & Cliff Pack

Revision 3.1: sealed stair joins, deeper overhangs and recesses, the approved warm cliff colours, and the earlier grey rock family shared with the stairs.

A replacement plateau surface, separate two-block-high south wall, and three faceted rock props. All import art uses one indexed palette: 15 opaque colours plus transparent index 0. Lighting comes from the upper left.

## Start here

- `previews/plateau_10x8_4x.png`: the assembled 10×8-block plateau, including a corner, recessed stairs, rocks and a 16×26-pixel player.
- `previews/cliff_top_6x6_4x.png`: a 6×6-block surface proof. The complete texture repeats every 48 pixels.
- `overview.png`: labelled review sheet.
- `previews/connected_terraces_4x.png`: two connected elevations, at player scale.
- `previews/firered_comparison.png`: original FireRed, previous attempt and revised native art.
- `previews/depth_colour_comparison.png`: revision 2 beside revision 3 at the same pixel scale.
- `validation.md`: measured dimensions, palette checks and tile counts.
- `asset_manifest.json`: exact file inventory and dimensions.

## Cliff top: keep the nine-tile phase

`cliff_top/top_texture_48x48.png` is the single authored surface. Its nine 16×16 cuts are in `cliff_top/centres/`, numbered left to right, then top to bottom:

| | Left | Middle | Right |
|---|---|---|---|
| Top | centre_1 | centre_2 | centre_3 |
| Middle | centre_4 | centre_5 | centre_6 |
| Bottom | centre_7 | centre_8 | centre_9 |

Repeat this 3×3 arrangement. Do not scatter the nine centres randomly. Keep one fixed phase origin for each map; moving a cliff boundary must not restart the pattern. The phase at block `(x,y)` is `1 + 3*positive_mod(y-origin_y,3) + positive_mod(x-origin_x,3)`.

Each phase has its own 13 boundary pieces in `cliff_top/phases/1/` through `9/`: N, NE, E, SE, S, SW, W, NW, in_NE, in_SE, in_SW, in_NW and single. Choose the edge from the same phase as the centre it replaces. For example, a north boundary on phase 5 uses `phases/5/N.png`.

This supplies edges for all nine texture tiles without flattening their interiors. Outside the allowed boundary mask, each piece is pixel-identical to its selected centre. Side bands stay in the outer 6 pixels; inner corners stay in their 6×6 square. Pixels 6–9 in both axes are identical across all centres and edges.

N means lawn north of the top tile. E/W show the narrow side lip; S is only the lit top cap. The height comes from the separate face below it.

`cliff_top/tiles/` also contains the original sixteen-name compatibility set. Its center, center_b and center_c aliases refer to centre_1, centre_2 and centre_3, and its edges use phase 1. That compatibility folder alone cannot reproduce the full 48×48 surface. Use the nine-phase set for the new cliff.

For engines that assemble metatiles from quadrants, `autotile_recipes.json` provides all 256 neighbour masks for every phase. Mask bits mean **outside the plateau**: N=1, E=2, S=4, W=8, NE=16, SE=32, SW=64, NW=128. Each recipe contains four shared 8×8 tile IDs arranged as two rows.

## Cliff face: reserve two map rows

Place the upper face directly south of the last top-surface row, and the lower face immediately below it. A plateau ending at map row 10 therefore uses face rows 11 and 12. Do not replace the top surface with a wall tile.

`cliff_face/face_strip.png` is 80×32 pixels: five columns in the order **left, middle_1, middle_2, middle_3, right**, with upper pieces in row 0 and lower pieces in row 1. The same pieces are exported separately in `cliff_face/tiles/`, and complete 16×32 columns in `cliff_face/columns/`.

Mix the three middle columns in any order. Their full-height interfaces match; keep each upper and lower pair together. The lower row includes the dark contact line and a transparent final row, so the lawn shows through at the foot.

`corners_strip.png` is 64×32, ordered **outer_W, inner_W, inner_E, outer_E**. Outer corners form a convex end where the face meets a side lip; inner corners form a darker recessed return, as beside the stairs. Select the appropriate W/E artwork rather than mirroring it: the lighting is directional.

The outer-6-pixel and inner-4×4 restrictions apply to the cliff **top** set. The face uses the full two-row height.

The stair connector is a bonus 32×32 piece, also split into four 16×16 tiles in `cliff_face/stairs/`. Replace two adjacent face columns with it. Continue the top surface into the stair mouth, removing its south cap across those two columns. `previews/plateau_layout.json` records the example's exact placements.

## Rock props

| Asset | Native size | Footprint | Use |
|---|---:|---:|---|
| small_rock | 16×16 | 1×1 | Lumpy mossy rock with lit facets |
| big_boulder | 32×32 | 2×2 | Larger, multi-faceted obstacle |
| breakable_rock | 16×16 | 1×1 | Deeply cracked Rock Smash prop |

All three have transparent exteriors and stepped, fully opaque contact-shadow pixels. No lawn is baked into them. They use the same palette on grass or on the cliff top. Their JSON files specify solid footprints. Rock Smash scripting and removal remain game events; this pack supplies the unbroken prop artwork.

## Palette and engine import

Use `palettes/rock_cliff.gpl`, the equivalent named JSON palette, or `rock_cliff.gbapal` (16 little-endian GBA colour entries). Index 0 is transparent; all other indices are opaque. Every RGB channel is a multiple of 8.

Revision 3 keeps the eight warm cliff/shadow entries and uses five of the original grey rock colours for both props and stair treads. Two moss greens complete the 15-colour palette. Intermediate rock/glint and moss shades are consolidated to keep this a single palette; the props retain their native silhouettes. Import the new palette with the new artwork rather than applying it to older indexed PNGs.

`tileset_8x8.png` is a shared, unflipped atlas with **253 used tiles**. Read tiles left to right, then top to bottom, 16 tiles per row. The final 3 cells are unused transparent padding. `tileset_4bpp.bin` contains just the 253 used tiles (8,096 bytes). Its low nibble is the left pixel. `integration/tile_maps.json` maps every import image to atlas indices.

| Group | Unique 8×8 tiles |
|---|---:|
| Top surface and all nine edge phases | 180 |
| Face, corners and stairs | 50 |
| Rocks | 23 |
| Whole pack, shared palette | **253** |

This expanded pack exceeds the old 120-tile allowance for the smaller cliff set. Allocate 253 tiles for the complete replacement, or import only the pieces the map uses. The report does not claim the old cap is met.

Mark the plateau top as walkable at its raised elevation, the cliff faces as solid, and stairs as the connection between elevations. Block the prop footprints using their JSON metadata. The top texture and tall faces require new map placements; replacing an old centre texture alone will not create cliff height. The existing League gate and paving are not included or changed.

## Files, previews and rebuilding

All game-art PNGs are native 4-bit indexed images. Every component tile is 16×16; the master texture, boulder, paired face columns, stair assembly, strips and atlas retain their explicitly documented larger dimensions. Adjacent `_4x.png` files are exact nearest-neighbour review copies.

The composed lawn/player previews and labelled overview are review images, not import tiles. They include the existing lawn and player palettes in addition to the cliff palette.

Editable native pixel drawing code, pixel arrays and the validator are in `source/`. With Node.js and `sharp` available, run from this folder:

```sh
node source/build.cjs
node source/validate.cjs
node source/context_preview.cjs
node source/review.cjs
node source/comparison.cjs
node source/depth_comparison.cjs
```

Validation checks image bytes, palette and alpha, phase assembly, wall joins, atlas reconstruction and GBA binary round trips. The previews have also been visually inspected. No game executable or ROM was supplied, so this is asset validation rather than an in-game playtest.

## What changed in revision 3

Revision 3.1 closes nine transparent pixels at the top of each inner face return (18 total). Those gaps had allowed the lawn to appear as little green dots beside the stairs. The join is now shaded rock. Palette and tile counts are unchanged. The validator now checks the adjacent inner returns as well as the stair connector.

Short projecting ledges now cast darker recessed shadows. Deeper clefts, darker east-facing corners and a stronger foot shadow increase perceived depth without changing the two-block wall height or the corner layout. The main warm cliff colours are retained. Rock props return to the earlier grey family, and the stair treads use that same grey ramp while their outer cheeks remain warm cliff stone. Tile counts are unchanged from revision 2.

## Earlier revision 2

The previous surface was too flat and the straight cream rim resembled architectural trim. Large face patches read as stone panels. The revision uses small angled facets across the entire surface, a broken rounded shoulder, a darker lower face and convex end shading that continues around the drop. The palette is warmer and has stronger separation between the lit top and shadowed front. Import the updated palette together with the artwork. Left/right end pieces now share the corresponding outer-corner art to avoid redundant tiles.

Comparison source: [original FireRed Route 22 map, Bulbagarden Archives](https://archives.bulbagarden.net/wiki/File:Kanto_Route_22_FRLG.png). The reference crop is included only in the labelled review comparison; none of its pixels are part of the importable artwork.

The `references/` folder contains review-only reference images for rebuilding the comparison sheet. Do not import these into the game tileset.

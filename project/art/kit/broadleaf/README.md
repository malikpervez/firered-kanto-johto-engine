# Sunlit Broadleaf Tree Pack v0.4

Native pixel-art implementation of the selected Sunlit Broadleaf design. **Design approved by Malik on 2026-10-22; upload to Pokemon Assets authorized.** It contains static graphics, not an animation.

## Changes from v0.3

Broader, overlapping leaf mounds replace the pointed crowns and repeated diagonal fans. Dark branch seams and hanging leaves separate the sunlit upper canopy from its underside. Rear crowns fill forest gaps, and narrower trunks expose a longer shaft with short roots. All three standalone silhouettes were revised. The shared palette, dimensions, anchors, collision recommendations and forest placement rules are unchanged.

`previews/comparison_v03_v04.png` puts matched v0.3/v0.4 native crops side by side, enlarged 4×. This comparison records the approved v0.4 design. See APPROVAL.md for release status.

## Review

- `previews/overview.png`: the native result at 4×, with the existing lawn, cobblestones and 16×26 player.
- `previews/town_context.png`: the same game-scale scene at 1×.
- `previews/standalone_scale_4x.png`: the three town trees beside the player.
- `previews/forest_repeat_6x6_4x.png`: a dense mixed forest with no lawn between interior cells.
- `previews/forest_junctions_4x.png`: outer/inner corners, strips, a recess and an opening.
- `validation.md`: measured palette, dimensions, joins and tile counts.

The artwork was drawn directly at 32×32. No concept-image pixels were sampled or downscaled. Every asset uses 15 colours plus transparent, with GBA channel values divisible by 8. All `_4x.png` files are exact nearest-neighbour review copies.

## Standalone trees

`trees/round_crown/`, `trees/offset_crown/` and `trees/broad_crown/` each contain the full 32×32 tree, four 16×16 cuts, 4× reviews and JSON metadata. Each has a 2×2-block footprint and bottom-centre draw anchor `(16,31)`. The lower two blocks are the recommended solid footprint; the upper two hold canopy. Adapt player-overlap priority using the game's existing tree logic. Transparency reveals the existing ground; no grass pixels are baked into the tree PNGs.

## Forest barricades

One forest cell is **32×32 pixels = 2×2 game blocks**. Anchor it at even block columns and rows. Do not scatter individual 16×16 quadrants independently.

Three crown variants, `a`, `b`, and `c`, share their outer five pixels and can be mixed. Each supplies 47 canonical border shapes, with all four blocks solid. Internal foliage is opaque. Border silhouettes and the space around exposed trunks are transparent.

`forest/forest.json` contains all recipes. Bits mean that a neighbouring **32×32 cell is outside the forest**:

| Direction | Bit |
|---|---:|
| N | 1 |
| E | 2 |
| S | 4 |
| W | 8 |
| NE | 16 |
| SE | 32 |
| SW | 64 |
| NW | 128 |

Discard a diagonal bit when either of its adjacent cardinal bits is set. This produces one of 47 masks. For example, `N` alone selects mask 1; N+E uses mask 3; all four sides outside uses mask 15; a lone diagonal opening to NE uses mask 16. `source/art.cjs` supplies the exact `normalize()` and `compose()` functions.

Use `forest/autotiles/<variant>/mask_NNN.png` or its atlas recipe. Each recipe also supplies four 16×16 quadrant maps. `forest/variants/<variant>/` contains named helpers, including ordinary sides, corners, inner corners, narrow NS/EW strips and single. The named helpers are for manual assembly; the 47-mask recipes cover combined cases. W and E retain separate lighting; do not mirror pieces.

## Palette and atlas

- `palettes/sunlit_broadleaf.gpl`: named palette including transparent index 0.
- `palettes/sunlit_broadleaf.json`: colour roles and alpha values.
- `palettes/sunlit_broadleaf.gbapal`: 32-byte GBA BGR555 palette.
- `integration/tileset_8x8.png`: shared atlas, read left-to-right then top-to-bottom in 16 columns.
- `integration/tileset_4bpp.bin`: 128 used tiles, 4,096 bytes; low nibble is the left pixel.
- `integration/tile_maps.json`: exact 8×8 index arrays for the exported images.

The atlas contains 128 unique tiles with no padding slots. Individual group counts are 46 for town trees and 85 for the forest, with three tiles shared. Preview-only ground/player colours are not part of this palette.

## Rebuild

With Node.js and `sharp` installed:

```sh
node source/build.cjs
node source/validate.cjs
node source/review.cjs
```

Editable native pixel drawing code and arrays are included. This is a new sibling pack, not a replacement of the existing in-game tree files. Design approval is complete. Engine integration still requires runtime testing. This approved v0.4 release is authorized for the Pokemon Assets Drive folder.

# Sunlit Broadleaf Bush Pack v0.2

**APPROVED — v0.2 design approved by Malik on 2026-10-22.**

This release contains the exact artwork shown in the v0.2 review. `previews/before_after_8x.png` preserves the original review labels for comparison; its draft label records the preview stage, not the release status.

Revision 0.2 replaces the paired large lobes and deep central groove with seven smaller, uneven leaf clusters. The front canopy stays continuous, with short isolated creases and broader shoulders. The palette and block size are unchanged.

Three native shrubs matching the approved **Sunlit Broadleaf Tree Pack v0.4**. Each shrub occupies one solid 16×16 block. The three variants have the same size, silhouette, baseline and contact pixels, so they may be mixed in either order in rows and columns.

## Import files

- `bushes/bush_a.png`, `bush_b.png`, `bush_c.png`: native 16×16, indexed 4-bit PNG.
- The corresponding `_4x.png` files are exact nearest-neighbour 64×64 review copies; import the 1× files.
- `palettes/sunlit_broadleaf.gpl`: copied byte-for-byte from the approved v0.4 tree pack, including its name, roles and index order.
- `validation.json`: exact palette, dimensions, binary alpha, tile counts, distinctness and neighbour-contact checks.

Mark each bush block solid. Place its top-left at the top-left of a 16×16 map block. Use these native PNGs as complete blocks; do not mirror them or add spacing. Each bush uses exactly four unique 8×8 tiles; the three together use eleven.

## Art rules followed

- Authored directly as integer pixels at 16×16, with small native leaf-cluster patterns. No concept downscaling, anti-aliasing, blur, image filtering or alpha blending.
- The exact 16-entry palette supplied by Malik is retained. Index 0 is transparent black; indices 1–15 are opaque. Every RGB channel is a multiple of 8.
- Small overlapping leaf clusters, upper-left light, sunlit tops using 7–9, a darker underside using 2–4, small creases using 1, and one glint pixel using 10 per bush. No trunk is needed.
- The foliage spans 16 pixels across and 15 rows high. A six-pixel contact shadow occupies the last row, making the complete opaque footprint including the shadow 16×16. Everything stays inside the block.
- All three use the same transparent silhouette. Their horizontal neighbours meet across seven rows; vertical neighbours meet across six columns at the base/top. Transparency remains in the outer rounded corners, so each shrub stays readable. There is no empty stripe between blocks.
- The variants were drawn separately, with different leaf-cluster positions. No variant is a mirror of another.
- No lawn pixels are baked into the shrubs. The lawn colours `(56,152,80)`, `(80,184,96)` and `(112,200,120)` are not used in the import art.

## Previews

Every scene below has a native 1× PNG and a `_4x.png` nearest-neighbour copy:

| Preview | Native size | Contents |
|---|---|---|
| `tree_player_scale` | 128×64 | One bush beside the actual v0.4 round tree and existing 16×26 player, bases aligned |
| `three_variants` | 96×32 | A, B and C individually on the lawn |
| `hedge_row_8` | 160×64 | Eight mixed bushes touching beneath a wooden fence |
| `column_4` | 48×96 | Four mixed bushes touching vertically |
| `l_run` | 112×96 | Five bushes across and four down, sharing the corner |
| `hedge_row_15` | 272×48 | Additional proof at the maximum requested row length |

`previews/before_after_8x.png` compares the previous and revised bushes at exact 8× for design review.

`previews/overview.png` is a labelled review sheet, with artwork shown at exact 4×. Preview lawn uses only the three lawn greens above. The tree, player and fence are context; preview images are not import graphics. The fence is a simple preview prop. The tree source is the approved v0.4 art, not v0.5.

## Validation and source

All nine ordered A/B/C neighbour pairs are checked horizontally and vertically. Pair checks cover any sequence of these blocks; the previews demonstrate the requested arrangements. Shape, palette, PNG format, glint count, tile counts and exact enlargements are also checked.

Editable pixel arrays, native drawing helpers and preview sources are included in `source/`. With Node.js and `sharp` available:

```sh
node source/build.cjs
node source/validate.cjs
```

The validation covers the exported graphics and previews. Collision must be marked solid in the target game; no game executable was supplied for a runtime test.

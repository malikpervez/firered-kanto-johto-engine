# Sunlit Field Rock Pack v0.1

**Design review — awaiting Malik's approval before upload to Pokemon Assets in Google Drive.**

Three small solid field rocks, with the chunky clusters and upper-left lighting used by the approved Sunlit Broadleaf trees v0.4 and bushes v0.2.

- **rock_a — Flat slab:** broad lit upper plane, a low dark front, one small fracture and moss at the left foot.
- **rock_b — Raised facet:** taller angular crown, sloping right face and a warm exposed base.
- **rock_c — Split and chipped:** an uneven stepped silhouette with two connected stone masses, an oblique fissure and a little moss at the foot.

## Import

Import `rocks/rock_a.png`, `rock_b.png` and `rock_c.png`. Each is an indexed **4-bit, 16×16 PNG**, with the exact supplied ground palette in the exact supplied order. Index 0 is fully transparent; indices 1–15 are fully opaque. `palettes/ground.gpl` contains all sixteen entries and named roles; GPL itself does not encode transparency.

Every asset occupies one solid map block. Set collision for the whole block in the game. Nothing extends outside it. Each rock has four unique 8×8 tiles; the complete set has twelve. There is no baked lawn. Greens appear only as tiny moss accents or the contact shadow.

Stone ends at row 14 and the short contact shadow occupies row 15. Including shadow, A occupies 14×10 pixels, B 13×12 and C 14×11. Stone uses indices 1, 11, 12 and 13. A has two cream glints; B and C have one each. Soil dark warms selected cracks or bases. All channels are multiples of 8.

The corresponding `_4x.png` files are exact nearest-neighbour 64×64 review copies. Import the native files, not the enlarged copies. No image was downscaled, blurred or antialiased. Each source character maps directly to one native pixel.

## Previews

Each scene has a native 1× PNG and an exact 4× nearest-neighbour copy:

| Name | Native size | Contents |
| --- | --- | --- |
| rock_a_scale | 96×48 | A beside approved bush A and 16×26 player |
| rock_b_scale | 96×48 | B beside approved bush B and player |
| rock_c_scale | 96×48 | C beside approved bush C and player |
| two_rocks | 80×40 | A and C in adjacent 16×16 map blocks |
| pathside | 112×64 | B beside a dirt path, bush and player |
| three_shapes | 96×32 | A, B and C side by side |

`previews/overview.png` labels the scenes at exact 4×. Lawn, bush and player are preview context; their palettes are not part of the imported rock PNGs. The bush pixels are unchanged from approved v0.2. The path is a preview-only soil-colour strip, not a new terrain asset. Only rocks and the requested ground palette are intended for import.

## Validation and editable source

`validation.json` records PNG dimensions, bit depth, palette order, alpha values, occupied bounds, cream counts, tile counts and checks. The six scene enlargements are checked pixel-for-pixel. The native art uses no mirrors, downscaling or semi-transparency.

`source/rocks.cjs` holds the native drawings; `source/build.cjs` exports and validates the pack. With Node.js and `sharp` installed:

```sh
node source/build.cjs
```

No game executable was provided. Technical checks cover exported art and previews; collision and in-game appearance still need importer/runtime review.

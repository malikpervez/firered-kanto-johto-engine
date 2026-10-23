# Pallet Houses Pack v0.5

**Design approved by Malik. Release v0.5 for Pokemon Assets in Google Drive.**

Red's and Blue's family homes, redrawn at native resolution to sit with approved Sunlit Broadleaf trees v0.4, bushes v0.2 and field rocks v0.1. The earlier Pallet house reference supplies the level of roof, window, wall and foundation detail.

## Changes in v0.5

Both main roofs have cleaner three-dimensional construction. The right planes are broad, continuous shadows without the broken diagonal squiggles. The hip edges now converge from the ridge ends to the actual eave corners, and the left planes carry broad sunlight with restrained straight course seams. The ridge caps, receding front shingles and thick eaves establish the depth. The soffit has a stronger dark edge.

Red's front-facing upper window and Blue's front-facing porch are retained. The 80×80 footprints, door blocks, collision and all 16 palette entries remain unchanged. Both door strips and every house pixel from row 48 down are identical to v0.4; the closed door frames still match the houses.

## Designs

- **Red's house:** a terracotta tiled roof with raised ridge caps and perspective-scaled courses, front-facing upper window with a centred gable, three-dimensional brick chimney, warm plaster, wooden shutters and a small red entrance canopy.
- **Blue's house:** a blue hip roof with broad lit and shaded side planes, capped stone chimney, closed attic shutter, horizontal siding and a flat front-facing gabled porch with fixed timber posts.

Both share cream trim, wooden window modules, a paneled front door, stone courses and the same upper-left lighting. Eaves cast a shadow on the wall. Door openings are 12×20 pixels and windows have frames, sills, crossbars and glass highlights. Chimneys and roofs stay inside the 80×80 asset bounds.

## Import files

| Asset | Native size | Review copy |
| --- | --- | --- |
| red_house.png | 80×80 | red_house_4x.png, 320×320 |
| blue_house.png | 80×80 | blue_house_4x.png, 320×320 |
| red_house_door.png | 48×32 | red_house_door_4x.png, 192×128 |
| blue_house_door.png | 48×32 | blue_house_door_4x.png, 192×128 |

All eight files are indexed **4-bit PNGs** with the identical ordered 16-entry palette. Index 0 alone is transparent; all other entries are opaque. Every RGB channel is divisible by eight. `palette.gpl` lists all entries and named roles. GPL does not itself encode alpha; the PNG transparency tables do.

Each house is exactly **5×5 blocks**, with its door at **[1,4]** in zero-based column,row order. The JSON files explicitly list all other 24 blocks as solid, even when a roof corner within a block is transparent. No grass, flowers, yard fences or signs are baked into the house art.

## Door animation

Frames are closed, half open, open from left to right. Each is 16×32. Replace the house rectangle beginning at pixel **[16,48]**, covering blocks **[1,3] and [1,4]**. Frame 0 equals this rectangle exactly. The only animated region is the 12×20 doorway at house pixels x=18..29 and y=56..75. Porch posts, roof, trim and threshold remain fixed. The open doorway has a dark interior.

Both homes use the same fixed map anchor. Do not center the door on the building or reposition its collision tile.

## Shared palette and tile budget

There is one palette for both homes. Its reds and blues also serve roof shadows and accents; the blue colours double as window glass shadows. Warm neutrals serve plaster, wood highlights and stone edges.

Exact unique 8×8 tile counts, including all three door states:

| Asset | Used | Limit |
| --- | ---: | ---: |
| Red | 94 | 100 |
| Blue | 96 | 100 |
| Combined, sharing identical tiles | 166 | 170 |

Counts include transparent tiles and do not rely on horizontal or vertical flips. `tile_pool/shared_8x8.png` and its JSON map provide the shared pool and reconstruction maps for both buildings and door sheets. Atlas padding is not counted. Allocating each house separately would discard the intended shared-tile savings.

## Previews

- `previews/roof_comparison_4x.png` — both houses before (v0.4) and after (v0.5), at exact 4×.

- `previews/yards.png` — native 288×160, both houses in fenced yards with a 16×26 player by Red's door; `_4x.png` is 1152×640.
- `previews/door_frames.png` — native 160×104, Red's three states on the top row and Blue's on the bottom; `_4x.png` is 640×416.
- `previews/doors_1x.gif` and `doors_4x.gif` — both door animations together, with 600/180/600 ms review timing.
- `previews/overview.png` — labelled sheet with all artwork at exact 4×.

Preview bushes and rocks use the approved artwork unchanged. Lawn, flower beds, fences, paths and signs are preview context only, and use additional palette entries outside the house palette. The 16×26 player is the same review-only scale stand-in used in the earlier packs. Preview images are not import tiles.

## Native source and checks

`source/art.cjs` draws directly to final-size integer pixel arrays. No image is downscaled, quantized, blurred or antialiased into the art. `source/native_pixels.json` contains the finished native palette indices. Rebuild with Node.js and `sharp` installed:

```sh
node source/build.cjs
```

`validation.json` records the saved PNG palette tables, binary alpha, sizes, door-patch equality, animation bounds, collision metadata, per-house and combined tile counts, exact tile-atlas reconstruction and nearest-neighbour previews. The GIF decoding checks were performed separately for this delivery. All checks pass. No ROM or game engine was supplied for an in-game test.

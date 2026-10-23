# Viridian Houses Roofs v0.1

Roof-only revision of the three original Viridian Stage 2 houses, using the roof language of the approved Pallet Houses v0.5 and Pokemon Center / Poke Mart v0.1.

## What changed

- Broad sunlit left roof planes with restrained straight course seams.
- Continuous, quiet shaded right planes, with no broken diagonal shingle marks.
- Hip boundaries project from the ridge ends to the actual front eave corners.
- Raised ridge caps, shingle courses that widen toward the front, and four-pixel eave stacks with dark soffit edges.
- The family house retains its central front gable/dormer and right chimney; the gardener retains its small dormer; the pond keeper retains its green roof, small dormer and left chimney.
- Chimneys have stone caps, dark flues, a lit left face and shaded right face. The pond chimney shifts one native pixel left within the roof to allow tile reuse.

## Preserved exactly

All pixels in rows 32–63 of each house are identical to the original indexed PNG, including walls, windows, shutters, awnings, porch, doors and the existing two-pixel eave shadow. No facade texture or window was moved to meet a tile budget. The original palette and its index order are unchanged.

The three door strips are regenerated from the new house crops. Because the revision stays above row 32, the finished strips are also pixel-identical to their originals. Every closed frame matches its house crop exactly; only the doorway interior changes in the half-open and open frames.

## Production assets

| Asset | Native size | Footprint | Door block | Unique 8x8 tiles including doors | Limit |
| --- | --- | --- | --- | --- | --- |
| house_family | 80x64 | 5x4 | [2,3] | 76 | 80 |
| house_gardener | 64x64 | 4x4 | [1,3] | 64 | 64 |
| house_pond_keeper | 64x64 | 4x4 | [1,3] | 64 | 64 |
| Shared pool | — | — | — | 157 | 180 |

Each house folder contains `<name>.png`, `<name>_door.png`, `<name>.json`, `<name>_4x.png` and `<name>_door_4x.png`.

- Production PNGs, door strips, their 4x copies and the shared tile atlas are PNG colour type 3, **4 bits per pixel**, with the same embedded 16-entry palette.
- Palette index 0 is transparent. Indices 1–15 are opaque; alpha is only 0 or 255.
- Every RGB channel is a multiple of 8. `palette.gpl` documents the index order; GPL itself does not store alpha, so transparency is in the PNG `tRNS` chunk.
- All drawing takes place directly on final-size integer palette-index grids. There is no downscaling, image tracing, resampling or colour quantization. The original editable pixel source was available, so the roof revision was made in that native source.
- 4x copies are exact nearest-neighbour enlargements. Import the 1x files into the game.
- All footprint blocks except the specified door block are solid, including partly transparent blocks. Metadata contains the explicit `solid_blocks` list and collision rows.
- Gardener and pond keeper metadata mark their doors as locked for now. Keep the existing game event locks; animation artwork does not unlock them.

## Door placement

Each 48x32 strip contains three 16x32 frames, left to right: **closed, half open, open**. Replace the entire 16x32 rectangle using its alpha. Place the strip at pixel [32,32] for the family house, or [16,32] for either small house. This covers the door block and the block directly above it.

Only frame-relative rectangle x=2..13, y=11..30 changes between states. The sill, threshold, surrounding facade, eave shadow and awning remain fixed. The door opening is decorative/animated art; collision and lock behaviour belong to the game logic.

## Previews

- `previews/before_after_1x.png` and `_4x.png`: each original house beside its roof revision on the approved lawn.
- `previews/town_lineup_1x.png` and `_4x.png`: all three new houses beside the unchanged approved Center v0.1 and Mart v0.1, with the original 16x26 scale-reference player at the family door.
- `previews/door_frames_1x.png` and `_4x.png`: all three door animations displayed on the lawn.
- `previews/player_16x26.png`: the existing preview player, retained at its native dimensions.

Lawn pixels are confined to previews. Comparison scenes use an 8-bit indexed union of the lawn, house, player and service-building palettes so the approved reference colours remain accurate. These scenes are review material, not importable production sprites.

## Validation and source

`validation.json` records embedded palettes, dimensions, binary alpha, facade preservation, door-frame matches and exact 8x8 tile counts. Counts include the transparent tile and every animation frame, with **no flip or rotation deduplication**. The shared tile atlas and maps are supplied under `tile_pool/`.

`source/` includes the native edit, original selected sprites, before/after pixel arrays, and preview inputs. `node source/build.cjs` rebuilds the pack (Node.js with `sharp`); `python source/validate.py` independently audits the exported PNG bytes using Pillow. The validator compares the preserved facade against the original PNG files and recounts tiles from the exported images.

The package has been checked as artwork and metadata. It has not been imported into or play-tested in the game engine.

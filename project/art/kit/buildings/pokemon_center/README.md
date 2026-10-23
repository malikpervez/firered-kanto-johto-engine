# Pokémon Center Pack v0.1

**Design approved by Malik. Release v0.1 for Pokemon Assets in Google Drive.**

Pallet v0.5-style terracotta hip roof; raised ridge, clean shaded return, thick eaves; front-facing pale entrance bay, large Poké Ball emblem, paired window bands and stone plinth.

## Fixed map anchors

- Building: 80×64 pixels, 5×4 blocks.
- Door block: [2,3], zero-based column,row. All 19 other blocks are solid, including blocks with transparent roof corners.
- Door sheet: 48×32 pixels; three 16×32 frames, closed → half open → open.
- Replace the rectangle starting at pixel [32,32], covering blocks [2,2] and [2,3]. Closed frame matches the building exactly.
- The 12×20 opening begins at pixel [34,42]. Only that opening animates. The open frame is a dark recess.

The Center retains the existing 80×64 footprint and door [2,3] from the matching Viridian asset. It is not forced into the Mart’s smaller footprint.

## Technical rules

The four import/review asset PNGs (pokemon_center.png, pokemon_center_door.png and their _4x copies) are indexed 4-bit PNGs with one identical ordered 16-entry palette. Index 0 alone is transparent, all other entries are fully opaque, and every RGB channel is divisible by eight. No lawn is embedded. The building is drawn directly at native size, with no downscaling or antialiasing. The 4× copies are nearest-neighbour only.

There are **68 unique 8×8 static tiles** and **80 including all door states** (internal target: 88). Counts include transparent tiles and use no mirrored or rotated reuse. tile_pool/ provides the exact indexed tile atlas and reconstruction maps.

## Previews

- center_and_mart_1x.png / _4x.png: redesigned pair on lawn with the 16×26 scale player at the Center’s door, approved Sunlit bushes and field rocks.
- mart_beside_current_center_1x.png / _4x.png: the redesigned Mart beside today’s unchanged Center, as originally requested.
- current_pair_1x.png / _4x.png: existing buildings for comparison.
- comparison_4x.png: labelled before and after.
- door_frames_1x.png / _4x.png: this building’s closed, half-open and open patches from left to right.
- doors_1x.gif / doors_4x.gif: the redesigned pair’s door animations, 600/180/600 ms review timing. In-game door opening should be one-shot, not looping.

Preview images use additional palettes for scenery and the other building, and are not import tiles. The player is a review-only scale stand-in. The unchanged reference Center and Mart use their existing native Viridian sources matching IMG_4949.png; the screenshot is not downscaled into any new art.

## Source and validation

source/art.cjs extends the native service-building construction and the approved Pallet Houses v0.5 roof treatment. Roofs have lit left planes, quiet shaded right planes, raised ridge caps, receding shingle courses, thick eaves and wall shadows. Entrance signs and lower facades face straight forward.

Rebuild with Node.js and sharp installed: run node source/build.cjs from this pack. source/native_pixels.json records the exact final indices. Shared source/reference arrays also include the other service building solely to reproduce the pair previews; import only pokemon_center.png and pokemon_center_door.png. The _4x copies are for review only.

validation.json records PNG formats, palette entries, sizes, binary alpha, fixed anchors, door patch equality, animation bounds and tile counts. These are file-level checks; no emulator or engine was supplied for an in-game test.

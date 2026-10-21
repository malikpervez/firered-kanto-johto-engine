(In the kit: only the 18 strips are kept, as sea/<piece>.png, with this README, palette.gpl and
rock_footprints.json. kit/water.py puts each sea block together from them; the rocks are sea#15+rock_a and
sea#15+rock_b, q and Q in the maps' grids.)

SEA / OCEAN — B — Staggered Swells / Reworked Rocks
Native pixel-art tiles for a 16x16 GBA-style overworld

CONTENTS
18 animated pieces: 16 core pieces plus rock_a and rock_b.
Each piece has 8 distinct 16x16 frames, synchronized at 160 ms/frame.
Play 0,1,2,3,4,5,6,7 and repeat. One cycle is 1.28 seconds.

strips/<piece>.png          128x16; frames 0–7 from left to right.
strips_8x/<piece>_8x.png    1024x128; exact nearest-neighbour enlargement.
frames/<piece>/frame_0k.png Individual 16x16 frames.
atlas/all_pieces_128x288.png All 18 strips stacked in the order below.
atlas/all_pieces_8x.png     Enlarged atlas for review.
previews/bay_96x64.gif      6x4-block bay, 8 frames, native resolution.
previews/bay_4x.gif         Same animation at 384x256.
previews/bay_frame0_4x.png  Still preview at 4x.
previews/*_repeat_4x.gif    3x3 repeats of each water variant and a mixed repeat.
palette.gpl / palette.json Exact palette and explicit index/alpha mapping.
animation.json             Frame timing, filenames, atlas rectangles and rock flags.
preview_layout.json        Tile names and positions used in the bay.
rock_footprints.json        Rock/surf footprints and intended blocking flags.
VALIDATION.txt / validation.json  Human-readable and detailed validation.
source/pixels.json         All native frames as editable palette-index arrays.
source/build_sea.cjs       Reproducible native pixel authoring and verification.
STYLE.txt                 Pattern description.

PIECES / ATLAS ROW ORDER
center, center_b, center_c, N, NE, E, SE, S, SW, W, NW,
in_NE, in_SE, in_SW, in_NW, single, rock_a, rock_b.

IMPORT
PNG files are indexed, 4 bits per pixel, with the exact 16-entry palette.
Index 0 is transparent. Indices 1–15 are opaque. Disable filtering.
GPL palettes do not encode alpha: its first named entry is the transparent
slot; PNG tRNS and palette.json specify the actual transparency.
The RGB bytes of index 0 duplicate #101828; its alpha is 0.

The frame rectangles in animation.json are ATLAS coordinates. For an
individual strip, use x = frame * 16, y = 0, width = height = 16.
Use one shared frame clock for every animated tile.

N means land north of the tile, E land east, and so on. N exposes a stone
face with earth seams and foot boulders; W/E show a narrower edge; S shows
the rocky lip. Land is transparent, including in previews. Place a lawn
layer beneath it in the game.

Side shores occupy only their outer 6-pixel bands; inside corners occupy
only their named outer 6x6 square. Their remaining pixels exactly match
center for the current frame. All 16 core pieces preserve the inner 4x4.
To build a narrow channel, copy the desired shore bands over center.

Open-water variants share a 2-pixel boundary band in all frames. Secondary
reflection placements vary while preserving the shared center 4x4. Swells move
right by 2 native pixels per frame and wrap after one 16-pixel wavelength.
Foam travels along the cliff. Whitecaps and small sparkles briefly flash.

rock_a and rock_b have central rock silhouettes and animated surf at their feet.
Outside the supplied footprints their water exactly matches center.
Their intended collision flags are in the metadata; assign your engine's
blocking collision behavior when importing them.

REBUILD
Requires Node.js and the sharp package. Run:
  node source/build_sea.cjs
Artwork is drawn directly into 16x16 integer palette-index grids. The PNG
and GIF encoders preserve those indices; sharp only verifies the outputs.
No generated-image reduction, raster downscaling or colour quantization is
used. Enlargement duplicates pixels.

The bay preview has north and west cliffs, an in_NW inside corner, and
open water continuing east and south.

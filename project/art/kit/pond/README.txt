(In the kit: only the 16 strips are kept, as pond/<piece>.png, with this README and palette.gpl. kit/pond.py
puts each pond block together from them.)

OPTION C — GENTLE RIPPLES
Complete synchronized pond-water asset pack

This is the native-pixel implementation of the selected third visual option:
clear blue water, sparse curved crests, quieter trailing reflections, brighter
cyan shallows, and a warm earth bank. The selected concept image is included
under reference/. It is a style reference, not an import-ready tileset.

REQUIRED ASSETS
strips/: 16 PNGs, each 128x16. Eight 16x16 frames, left to right, 0–7.
strips_8x/: 16 matching PNGs, each 1024x128, nearest-neighbour enlargement.

Piece order:
center, center_b, center_c, N, NE, E, SE, S, SW, W, NW,
in_NE, in_SE, in_SW, in_NW, single.

ADDITIONAL IMPORT FILES
frames/: all 128 individual 16x16 frame PNGs, grouped by piece name.
atlas/all_pieces_128x256.png: one piece per row, eight frames per row.
atlas/all_pieces_8x.png: 1024x2048 nearest-neighbour atlas enlargement.
example_composites/: three inlet/junction strips and their 8x versions.
palette.gpl: the supplied 15-color palette, suitable for pixel editors.
animation.json: timing, atlas order, frame rectangles and looping settings.
source/pixels.json: indexed pixel arrays for every piece and frame.
source/build_pond.cjs: reproducible exporter and validation checks; uses Node
and the sharp package. Run from any directory with node source/build_pond.cjs.

PREVIEWS
pond_96x64.gif: exact 6x4-block example, eight frames.
pond_4x.gif: the same animation at 384x256, nearest neighbour.
pond_frame0_4x.png: 384x256 still of frame 0.
center_repeat_3x3.gif: repeated open water for checking the spatial loop.
pieces_frame0.png: top row is the first eight pieces; bottom row is the last
eight, in the order above. Green is a preview backdrop, not part of the assets.

ANIMATION
Use the same frame index for every piece: 160 ms/frame, eight frames,
1.28 seconds per loop, repeating forever. Frame 8 is frame 0 again.
Use nearest-neighbour/point filtering when displaying the assets.
The crests gently sway by two pixels and bob by one; trailing reflections
move slightly out of phase. Foam gaps and shallow highlights move around
the fixed shore. Sparkles flash once bright, then once dim at a fixed spot.

COMPOSITION
Land is transparent, including between the outer image boundary and bank.
The north bank shows its darker earth face; other sides show a thin lit rim.
The inner 4x4 at x=6..9, y=6..9 is identical to center in all pieces/frames.
All shore modifications stay in the appropriate outer six-pixel band.
Inside corner modifications stay in their corresponding outer 6x6 square.

A horizontal one-block-wide channel combines N rows 0–5 and S rows 10–15
over center. A vertical channel can similarly combine W and E columns.
The example includes exactly one inside notch and a one-block-wide inlet:
  junction_N_in_SE: N with the bottom-right 6x6 from in_SE.
  channel_NS: N with the bottom six rows from S.
  cap_NES: top eight rows of NE and bottom eight rows of SE.
preview_layout.json records the 6x4-block placement.

VALIDATION
Read VALIDATION.txt for the human-readable results and validation.json for
per-piece dimensions, colors, and pixel comparison counts.
All asset pixels use the supplied palette, with alpha exclusively 0 or 255.

ART PROCESS
Original artwork following the supplied FireRed/LeafGreen-style brief.
The approved option-C reference used built-in image_gen. Final assets are
native-grid pixel finishing and integer animation exports of that direction.
No CLI image-generation fallback was used. The source prompt is included.

TALL GRASS — A / B / C

A: Alternating-leaflet sprig.
B: Two fronds leaning apart from one root.
C: A with exactly two small cream flowers; all other tile pixels unchanged.

Each variant folder contains:
  *_tile_16x16.png                  Native tile.
  *_tile_128x128.png                Nearest-neighbour 8x enlargement.
  *_repeat_48x48.png                Exact 3x3 repeat.
  *_repeat_384x384.png              Nearest-neighbour 8x repeat proof.
  *_feet_80x16.png                  Five 16x16 frames, left to right, 0–4.
  *_feet_640x128.png                Nearest-neighbour 8x strip enlargement.
  *_feet_leaves_only_80x16.png       Overlay with lawn pixels removed.
  *_feet_leaves_only_640x128.png     Enlarged leaf-only overlay.
  *_pixels.json                    Editable pixel/color maps.

PIXEL RULES
Assets are 4-bit indexed PNGs with a shared palette. A/B use the supplied
10 colors; C uses those plus cream and gold. Alpha is only 0 or 255.
No antialiasing, blur, gradients, semitransparency or dithering.
Exposed lawn: A 35.2%, B 35.9%, C 34.8%.
Edge-crossing leaf motifs wrap to the opposite side of the 16x16 tile.
Tall_Grass_ABC_Preview.png is a labeled preview, not a tileset asset.

FRAME 0 AND TRANSPARENCY
The main feet strip follows the exact-row requirement literally: frame 0
has transparent rows 0–8 and an unchanged opaque copy of tile rows 9–15,
including lawn pixels. For transparent lawn gaps, use the leaf-only strip.
That strip preserves all foliage pixels and removes the two lawn colors.

ANIMATION
0: Resting lower foliage.
1: Each half moves 2 px outward and 1 px down.
2: Settle to 1 px outward and 1 px down; two two-pixel leaf bits rise.
3: Settle to 1 px outward at original height; bits rise and darken.
4: Original foliage; two bits shrink to one pixel each.
Return to 0 to remove the last bits. Fading uses palette changes/shrinking,
without fractional alpha. Motion is clipped inside each 16x16 frame.
C flowers are above row 9, so C's foot strip equals A's.
Suggested durations (ms): 120, 70, 90, 100, 110.

VALIDATION
validation.json records dimensions, visible colors, exposed ground, frame 0
equality, binary alpha, and C/A equality outside the two flowers.
Every exported PNG was decoded and checked against its intended pixel map.

ART PROCESS
Original art following the supplied FireRed/LeafGreen-style brief.
Design references used built-in image_gen, with no CLI/API fallback.
The final assets were reduced and finished on a true 16x16 indexed grid,
with native-pixel corrections to leaf/stem continuity and periodic edges.
Zooms, repeats, and animation displacements use integer pixel operations.
Generation prompt notes are included in generation_notes.txt.

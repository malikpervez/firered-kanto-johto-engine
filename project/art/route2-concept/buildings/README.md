# Route 2 Stage 2 Assets v0.3 — tile-budget export

The approved v0.2 designs are preserved, with repeating pixel detail rearranged on the 8×8 grid. The four placed building sprites use **220 unique resident tiles with H/V flips merged**. With the supplied allowance of 160 other Route 2 tiles, the estimated total is **380/384**, leaving **4 tiles**.

| Budget group | v0.2 | v0.3 | Limit |
| --- | ---: | ---: | ---: |
| Both forest gates together | 177* | 120* | 140 |
| Full Diglett's Cave assembly | 87 | 59 | 60 |
| East gatehouse | 41 | 41 | 41 |
| Combined resident building pool | 305 | 220 | 224 available after reserving 160 |

*The forest totals include one used transparent blank. Excluding that blank: 176 before, 119 after. The blank counts in the actual 220-tile resident budget. All numbers merge H, V and combined H/V flips; rotations do not merge. Door-animation frame storage is excluded as requested. A base building's visible door still counts as part of that building. See tile_report.md and tile_report.json.

## What changed

- Forest front-slope shingle interiors reuse approved 8×8 tiles. Broad sunlit left planes, continuous shaded right planes, hip edges, raised ridges, thick eaves and upper-left lighting remain.
- Six clerestory panes repeat on a 16-pixel module. Masonry repeats a 24-pixel-wide approved motif, retaining the original 12×6 brick proportions and staggered courses. Both module widths align to the 8-pixel grid.
- Foundation blocks repeat on an 8-pixel rhythm. Piers, doorway surrounds, corners, silhouettes and the north entrance glow retain their defining detail.
- Cave top, straight rims and selected face strips repeat exact 8×8 crops from Route 22 Rock and Cliff Pack v3.2. The entire 32×32 tile region around its mouth and broken-rock lip is unchanged. cliff_tile_provenance.json identifies the source of every non-mouth tile.
- The east gate is entirely pixel-identical to v0.2 and remains at 41 tiles.

## Preserved exactly

Footprints, door blocks, solid blocks, collision rows and per-pixel transparency masks match v0.2. All five door strips, their 4× copies and all three used palettes are byte-identical to v0.2. Every default frame matches its building crop exactly.

The south forest gate remains closed in its base sprite. The north forest entrance and cave are static open. The east gate's approved base sprite remains **open**, frame 2 of its south strip; its closed alternative has identical surrounding pixels and changes only the doorway. Its north cutaway is unchanged.

| Building | Footprint / pixels | Route origin | Local door blocks | World door blocks |
| --- | --- | --- | --- | --- |
| Forest south | 8×6 / 128×96 | [4,46] | [3,5], [4,5] | [7,51], [8,51] |
| Forest north | 8×6 / 128×96 | [4,20] | [3,0], [4,0] | [7,20], [8,20] |
| East gatehouse | 4×4 / 64×64 | [20,44] | north [1,0], south [1,3] | north [21,44], south [21,47] |
| Diglett's Cave | 6×5 / 96×80 | [20,8] | [2,4] | [22,12] |

Coordinates are zero-based [column,row]. Every footprint block except its listed doors is solid. Both halves of a wide forest door share one destination. No map cells or warp destinations changed. The 30×80 plan and metadata are byte-identical to v0.2; all eight Cut-tree scenarios still pass.

The trade house remains the external approved Viridian family-house asset. Its PNG, door strip, palette and native pixel source are **not included or modified**. Its existing placement and warp remain in the unchanged route contracts.

## Files and review

- assets/name/: indexed native PNG, unchanged door strips, 4× nearest-neighbour copies and JSON metadata.
- previews/before_after_4x.png: all four buildings, before v0.2 on the top row and after v0.3 on the bottom row, on the same lawn and at the same scale. Includes a 1× copy and individual building comparisons.
- previews/overview_4x.png, door_frames_4x.png and opening GIFs: current assets and unchanged animation states.
- palettes/: unchanged palettes as GPL, index/RGBA JSON and 32-byte little-endian GBA BGR555.
- tile_pool/: resident binaries, per-palette atlas/subset files and pool index.
- globals/cliff_cave_entrance/: unchanged optional mouth overlay, separate tile pool and reuse notes.
- route2/: unchanged plan/metadata, updated asset references and route validation.
- integration/: flip-map/animation import rules and unchanged symbolic warp destinations.
- source/: exact v0.2 before-state for these assets, approved cliff source, editable scripts, original file hashes and independent validator.
- validation.json, tile_report.json, tile_report.md, cliff_tile_provenance.json and checksums.sha256.

Production PNGs are embedded-palette **4-bit indexed PNGs**. Index 0 is transparent; entries 1–15 are opaque. RGB channels are divisible by 8. Lawn is not baked into the sprites. Review composites and GIFs are not production tile/palette inputs.

## Importing the tile pool

Use tile_pool/route2_buildings_4bpp.bin as the permanent building pool: **220 tiles / 7,040 bytes**. Every tile is stored in its canonical flip orientation. Metadata schema 3 references each tile as:

    {"tile": 0, "hflip": false, "vflip": false, "pool": "resident"}

base_map_8x8 and base_metatiles_16x16 reconstruct the original pixels with those flags. Metatile quadrant order is top-left, top-right, bottom-left, bottom-right. gba_bg_words_8x8 contains tile index | H-flip bit 10 | V-flip bit 11 | logical palette bank bits 12–15. Indices are pack-relative; assign a real tile offset and remap palette slots during import.

Logical palettes remain forest=0, east=1, cliff=3. Slot 2 belongs to the external Viridian house palette and is not supplied. Per-palette binaries/atlases are alternative subsets of the resident pool; do not append them again. Each atlas includes an atlas_tile_ids mapping to shared tile IDs.

The separate animation pool contains **62 unique stored tiles / 1,984 bytes**. Upload frame replacements through the engine's door-animation mechanism; do not append the entire animation pool permanently to the base tileset. Use dedicated animation destinations or remap the animated metatiles so shared tiles elsewhere are not overwritten. Wide 32×32 frames replace both door columns together.

The optional cave overlay contains 14 tiles / 448 bytes. It is for composing other caves, **not additional resident art for Route 2**: the full 6×5 cave already includes its mouth. Use either the full assembly or an appropriately budgeted cliff-plus-overlay composition.

The 380/384 total uses the supplied **160-tile estimate** for other route pieces. Check their final combined project count during import. No engine import or runtime playtest was performed.

## Rebuild and validation

Requires Python 3 with Pillow and Node.js with sharp. From this folder:

    python3 source/layout.py
    node source/build.cjs
    python3 source/validate.py

The layout script copies native indices directly, without scaling or quantization. The validator independently reads PNG/binary data, merges flips, reconstructs every image/frame, checks palettes and binary alpha, compares 25 fixed-file hashes, verifies collision/doors, checks exact cliff-tile provenance, decodes animation GIFs and reruns the route graph.

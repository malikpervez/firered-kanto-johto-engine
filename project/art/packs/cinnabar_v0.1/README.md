# Kanto Cinnabar Island v0.1

Native 16px blocks and 8px tiles, authored directly as palette indices at 1x. The new art has no resampling, tracing, quantization, antialiasing or dithering. Enlarged review images use nearest neighbour only. Light comes from the upper left.

## Review and integration status

This is an asset pack and a reconstructed placement preview, not an edited game map. The text plan defines the exact 96x44 layout, doors, encounters and reserved scene areas. The supplied chat image is a visual reference only. The unmarked 1x PNG and close-up reference PNGs were not in the brief folder. Consequently the previews rebuild context from the text plan and approved kit assets; they do not claim pixel-identical preservation of the original map. Actors, signs, flower clusters and offshore rocks are omitted from context rather than newly redrawn. Keep all of them in the actual map.

The town's text plan uses a 6x5 Mansion. Its context image is the earlier approved native footprint, not the later 13x9 remake, which cannot fit those fixed coordinates. The new pack does not change either building. Resolve that separate map/building scale mismatch during map integration. No buildings are import assets in this pack.

## Lawn reduction requested after first preview

The volcano island now extends its existing ash across most interior lawn. A one-block green shoreline buffer and small pockets at tree roots, flower beds, the hot spring and the Friends camp remain. The camp/Giratina clearing stays lawn and unobstructed. Town lawns remain unchanged. This is an intentional placement revision to the original E zone, using the same assets and adding no tiles. The updated placement_plan.json records every ash block; the original reference text remains unchanged for comparison.

## Where each material belongs

- **Paving:** dark, warm basalt setts in 16px repeating courses. Use in both town streets and the east lane. Walkable. The same lawn/joint/rim stack wraps every exposed side and inside corner. Do not use it on the volcano.
- **Cliff:** rough cooled basalt above a 32px columnar face. Solid and never climbable. Use the four fixed phases, with origin (0,0) in this preview. No stairs or general rock props are included. The muted red `S_ember` variants are only for the cap immediately above the crater, never outer cliffs.
- **Crater:** two fills with dark cooling crust and orange fissures. Solid. These have no independent border and belong inside a closed cliff pit. They are static so the much quieter steam carries the animation.
- **Ash:** two subdued fill arrangements with cinders and pale pumice. Walkable. Extends beneath the cliff and the existing field-rock positions, with the same edge on every lawn boundary. Keep the central rock and crater solid despite the ash underneath.
- **Steam vent:** a fixed fissure with two frames of pale steam, 24 game frames each at 60Hz, 0.8 seconds per loop. Solid. Keep clear of wandering Pokemon, doors and scene paths.
- **Lava rock:** a porous, faceted boulder with an internal dark base and no external cast shadow. Solid. Replace only field rocks on the ash, not town or sea rocks.
- **Hot-spring steam:** optional two-frame plume, 24 frames per image. Solid. Place beside the kit pond on lawn, not over its water or on the player's route. The kit pond itself is unchanged.

Every new piece has `over_rows: 0`. Nothing overlays the player. This stone, ash, vent and lava-rock language can be reused at Mt. Ember or Johto volcanoes; town paving remains optional there.

## Cliff placement, following Rock & Cliff revision 3.2

The reference pack's README, face_junctions and CHANGES_3_2 were inspected. This is freshly drawn basalt using those topology rules, not recoloured or traced pink cliff art.

1. In every contiguous vertical rock run, reserve its bottom two blocks for a face. The top cap sits immediately above them. A pit creates another face at the bottom of the rock run north of the pit.
2. Phase = `1 + 2*((y-origin_y)%2) + ((x-origin_x)%2)`. Do not restart phases at corners. The four centres reproduce `cliff/top_texture_32x32.png` exactly. All ordinary boundary changes stay in the outer six pixels; inside-corner changes stay in their six-pixel square. The middle cross remains unchanged.
3. Select all 256 outside masks for each phase from `cliff/autotile_recipes.json`. N means ground outside to the north. Bit order is N,E,S,W,NE,SE,SW,NW; inside-corner listing order is NE,SE,SW,NW. Recipes specify source quadrants, canonical tile IDs and flips.
4. South caps continue into the face with no transparent horizontal seam. SW is above outer_W and SE above outer_E. A middle column is 16x32; keep its upper and lower halves paired.
5. Where a top touches a neighbouring face, use `side_W_face_start` or `side_E_face_start` beside its upper block; use `side_W_face` or `side_E_face` beside its lower block. Immediately above that contact use `in_SW_face` or `in_SE_face`. These override ordinary lawn edges. Copy only the affected quadrants when a tile also has another boundary.
6. W/E are separately lit. The tile report merges flips for storage only; do not mirror complete columns to create the other side. Use inner returns against adjacent top, outer returns against outside ground. The one-pixel outside inset is shared by cap and face.

`previews/placement_plan.json` records the actual placed cliff blocks, masks, phases, overrides and tile IDs, plus the ground and detail placements. Paving and ash have all 256 recipes as in the Fuchsia surface schema. Recipe composition can require a block assembled from four PNG quadrants; the listed edge PNGs alone are not every possible combined mask.

## Palettes

All six supplied GPL files are unchanged. Two new palettes are supplied, both exact 16-entry palettes:

- **cinnabar_volcano, bank 11:** charcoal ramp, muted ember/orange, steam highlights and exact kit ground greens at indices 11-13. This replaces the kit rock bank on Cinnabar. The supplied `kit_rock_cliff.gpl` is reference only, not an extra loaded bank.
- **cinnabar_town, bank 12:** shares the volcano palette except for two warmer basalt shades. Needed because the Gym palette has no lawn greens for a single 8x8 edge tile. It avoids mixing palette banks within a tile or replacing kit lawn colours.

Each PNG has one palette, every 8x8 tile therefore has exactly one palette. Index 0 is transparent, all other entries opaque. All colours used by new art are multiples of eight. Supplied kit_water entries 9-11 contain channels not divisible by eight; they are preserved as requested and are not used by new art. This inherited exception is explicit in validation, not silently rounded. Preview context retains the kit's existing water colours.

## Counts and files

Tile counts merge horizontal, vertical and both flips of index graphics; rotations remain distinct. All animation frames count. The map can bind identical index patterns to different palette banks without duplicating their graphics. Palette names and transforms are explicit in JSON.

Paving 7/16; ash 8/14; placed cliff 63/64; whole cliff set 65; crater 4/8; steam vent 6/6; lava rock 4/4; optional spring steam 3/4. The island union is 91/116, leaving 53 of the 144 available tiles. The whole supplied set is reported separately in tile_report.json. Load only the cliff variants the map uses.

`tiles_4bpp.bin` contains canonical graphics, low nibble = left pixel. `tile_pool.json` and per-piece `tiles_8x8`/`flips_8x8` reconstruct the art. The JSON `palettes_8x8`, `solid_blocks`, `walkable_blocks`, `footprint_blocks` and `over_rows` are authoritative for each piece. Animated groups provide full-size PNGs and explicit timing.

## Reserved map areas

The preview places vents at (56,10), (80,17), (54,26), (74,27), spring steam at (63,31), (69,30), and lava rocks at the existing ash-rock positions. These avoid the listed people, door approaches, signs' reading blocks, camp, Giratina and the Pokemon's two-block wandering neighbourhoods. In particular no new prop is placed on row 12's town route or column 21's boat approach. The textual brief remains included verbatim in source/reference.

## Rebuild

Python 3 with Pillow and NumPy: run source/previews.py, source/finish.py, source/validate.py, then source/package.py. Context PNGs are preview-only. No emulator or game project was supplied, so validation covers files and composition, not in-engine collision or palette-bank allocation.

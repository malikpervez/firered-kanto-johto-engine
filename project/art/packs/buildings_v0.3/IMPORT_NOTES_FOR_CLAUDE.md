# Import notes for Claude

## v0.3 requires two map layout changes

The owner requested that Pokémon Mansion and the Power Plant be much bigger. Mansion is now **13×9 blocks (208×144px), door (6,8)**. Power Plant is now **15×8 (240×128px), door (7,7)**. These supersede the original size constraints for those two assets only. **Do not import either into its old footprint.** Read `SCALE_CHANGE_IMPORT.md` for the exact migration and placement offsets. The other 25 buildings and all their animation pixels are identical to v0.2.

Native sources are palette-index pixels, authored at 1×. There is no image generation, enlarged source pixel art, downsampling, tracing or quantization. Broad repeated window, stone and roof modules make the larger buildings fit the same tile budgets.

## Native format and metadata

Each `<id>/<id>.json` is schema 2. Images are 4-bit indexed PNGs with exactly 16 embedded entries, index 0 transparent, binary alpha and RGB channels divisible by eight. No ground is baked in. Each folder contains matching palette, JSON, native image and exact nearest-neighbour 4× copies. New doors use three 16×32 frames in a 48×32 strip. Closed frames match their own building crops; only the declared opening animates. Fixed rooflines stay flush; projecting exit details remain limited to genuine passages.

All palettes and index order are unchanged from v0.2. Cinnabar’s Mansion/Gym share the volcanic palette; Lab has its own. Power Plant continues to use the existing Pewter stone palette. `palette_migration.json` compares the current palette to the original supplied stand-ins, not to v0.2. None of those historical palette corrections are new in this revision.

## Existing entrance and event rules

- Use `door_instances` for every animated anchor. The Department Store has two anchors sharing one strip. Double-width Saffron and Route 12 gate doors retain 96×32 strips.
- League Front Gate retains the original approved Route 22 animation. Genuine roof/back passages and cycling entrances remain intact, with their previous directions.
- Pokémon Tower retains its corrected fixed roof background in all frames from v0.2; this revision does not change it.
- Pond garden stays locked under the existing event flag; its rear (1,0) doorway is walkable in the corrected metadata. Route 1 arch keeps its central pass-through and over-player top row.
- The new Power Plant rolling shutter is sealed scenery. It is not an additional entrance. There is still one animated personnel doorway.
- Mansion and Plant keep the same intended interior destinations, events and unlock rules. Their exterior placement/collision and warp coordinates must be reviewed for their larger footprints. Preserve unrelated map and story data.

## GBA graphics pools

`tile_report.json` merges horizontal/vertical mirrors and includes transparency plus every door-animation frame. Cinnabar’s three-building union remains within 290; the Plant remains within 149. The other maps keep their v0.2 graphic pools. The actual counts are in the report.

The master bundle includes `tile_pools/<map>/tiles.4bpp`, reversible `assemblies.json` and BGR555 palettes. A tile is 32 bytes, lower nibble left pixel. Screen entries encode local tile ID in bits0–9, H/V in bits10/11 and suggested bank in bits12–15. Relocate the suggested building banks 7/9 to match the existing importer. These are **building-only** pools, not full-map metatiles or collision maps.

## Validation and pending project work

The native format, doors, tile counts, exact 4bpp reconstruction and preservation of the other 25 assets are validated. No ROM import, terrain expansion, map re-layout, warp edit, replay or story test was performed. After design review, implement the two site changes in the game project, measure each full 384-tile map bank and run the existing gameplay tests.

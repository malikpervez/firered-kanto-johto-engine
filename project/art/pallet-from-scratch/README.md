# Pallet Town from scratch

Pallet Town drawn with no tile from the base game, with pae. The story, people and events are the game's; every
tile, palette and metatile is new. The interiors still use their old tilesets.

`before_after.png`: the old town (left) and the new one (right), as pae renders them. `in_game_*.png`: the game.

## How it is made

`build.sh` runs the whole pipeline from the repository root:

1. `make_art.py` draws everything pixel by pixel:
   - grass, paths with grass edges (16 edge variants), the pond (16 variants), flowers, fences, signs and trees;
   - the two houses and Oak's lab.

   It writes the sheets, the build spec (`spec.json`), the town (`grid.txt`, one character per block) and the
   legend.
2. `pae tileset build spec.json` turns them into two new tilesets:
   - `gTileset_PalletScratch_General` (primary): 139 tiles, 43 metatiles;
   - `gTileset_PalletScratch` (secondary): 105 tiles, 60 metatiles.

   Tiles 434–441 stay free for the door animation.
3. `pae map paint` writes the blocks: `engine/data/layouts/PalletTown_Scratch/`. The map points at them and at
   the new tilesets through its `firered_geometry` (`pae map geometry`).
4. `pae seam build PalletTown_Frlg`: Route 1 and Route 21 still use the old tilesets. Pallet gets their edge strips
   as adapter metatiles, and they get Pallet's: `engine/src/data/pae_seams.{json,h}`.
5. `pae door add`: the houses' door and the lab's open with their own animation: `engine/src/data/pae_doors.{json,h}`.

Change the art in `make_art.py` (or `grid.txt` for the layout), run `build.sh`, build, then `pae test run`.

## Palettes

From Route 1 or Route 21, only one palette slot is free to show Pallet's strip. So:
- **Palette A** covers everything in the top seven rows: greens, path, wood, white and grey, the roof reds, the
  window blue and yellow.
- **Palette B** covers everything in the bottom seven rows: the same first ten colours, plus water and flowers.
- **Palette C** is the lab's, except its bottom row, which uses B.

`pae seam build` reports an error if a strip ever needs more slots than are free.

## Events

The layout keeps every event where the story expects it:
- the doors at (6,7), (15,7) and (16,13);
- the five signs;
- Oak's trigger at the north exit;
- the people's positions, all on walkable blocks.

Replay tests (`engine/pae_tests/pallet *`):
- walk into Route 1 and back;
- Route 1's view of Pallet;
- both doors;
- Oak stopping a new player.

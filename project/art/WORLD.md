# The world as maps are rebuilt

Towns and routes are rebuilt one by one from the kit (`kit/`). They may grow or shrink, and every map they join
has to keep lining up with them. This page tracks that: each rebuilt map's size, where its roads meet its
neighbours', and what else depends on its shape. Update it with every map.

![Viridian City, Route 1, Pallet Town and Route 21 North, joined as the game joins them](world_pallet_viridian.png)

(From the top: Viridian City and Route 21 North are still the old maps; Route 1 and Pallet Town are rebuilt.
Make the picture again with `pae map render` for each map, placed by the offsets below.)

## Rebuilt maps

| Map | Size (blocks) | Was | Tilesets | Joins |
|---|---|---|---|---|
| Pallet Town | 32×28 | 24×20 | kit + `gTileset_PalletConcept` | up: Route 1 (offset −10), down: Route 21 North (offset 11) |
| Route 1 | 50×40 | 50×40 | kit + `gTileset_Route1Concept` | up: Viridian City (offset −2), down: Pallet Town (offset 10) |

## Where the roads meet

A join lines up one column (or row) of each map, `pae map connect A up B --align a,b`. The roads have to meet:

| Join | Columns | Notes |
|---|---|---|
| Pallet ↔ Route 1 | Pallet 14–15 = Route 1 24–25 | Pallet's road north; Route 1's road under its arch |
| Route 1 ↔ Viridian | Route 1 22–25 = Viridian 24–27 | Route 1's road widens to meet Viridian's |
| Pallet ↔ Route 21 North | Pallet 18–21 = Route 21 7–10 | the water channel south (surf) |

When a map changes size, keep these columns where they meet (move the map's road, or change the offset), and if a
map grows to the left or top, its neighbours' offsets change with it.

## Seams

Maps on different tilesets need connection seams (`pae seam build`) so each shows its neighbour's edge right.

| Map | Shows across its edges | How |
|---|---|---|
| Pallet Town | Route 1, Route 21 North | pae |
| Route 1 | Pallet Town, Viridian City | pae |
| Viridian City | Route 1 (pae), Route 22 (hand-made) | pae's beside the hand-made one |
| Route 21 North | Pallet Town | pae |

Maps built from the kit share the primary tileset, so between them the seams only copy secondary tiles. When both
neighbours are rebuilt from the kit with the same secondary tileset, the seam isn't needed at all.

A seam needs a palette slot in the viewing map for every palette of the strip it shows (the 7 rows or columns
beside the join) that the viewing map doesn't have. Old maps have few free: Viridian's hand-made seam for Route 22
leaves it three. So near a join with a map that isn't rebuilt yet, keep pieces with palettes of their own out of
those 7 rows: Route 1's tall grass (bank 4) starts at row 7.

## What else depends on a map's shape

Check these whenever a map is rebuilt, moved or resized:

- **Events**: people, signs, warps, triggers (`pae map place`); cutscene walks (`pae map path`).
- **Scripts with coordinates**: `setobjectxyperm`, `opendoor`/`closedoor`, `setmetatile`.
- **Heal location** (`src/data/heal_locations.json`), where you wake up after blacking out or flying in.
- **Warps into the map** from its houses, and from other maps that lead to it, such as New Bark's warp to Pallet.
- **Special scenes placed by coordinates**, such as the Friends camp in `src/data/friends_scene_locations.h`.
- **The town map** (`pae world region`): a much bigger town may need a bigger rectangle, and its fly spot.
- **Replay tests** that start or end on the map (`pae test run`).
- **Wild encounters** are per map, not per tile: the grass you draw is where they happen.

## Log

- Pallet Town rebuilt larger: 32×28 instead of 24×20. Its joins were re-aligned to Route 1's road and Route 21's
  water, and the heal spot, Friends camp and New Bark warp moved.
- Route 1 rebuilt at the same size, so Viridian's and Pallet's joins didn't change. Viridian got a pae seam for
  Route 1 beside its hand-made one for Route 22.

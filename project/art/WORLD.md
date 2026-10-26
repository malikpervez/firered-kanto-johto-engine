# The world as maps are rebuilt

Towns and routes are rebuilt one by one from the kit (`kit/`). They may grow or shrink, and every map they join
has to keep lining up with them. This page tracks that: each rebuilt map's size, where its roads meet its
neighbours', and what else depends on its shape. Update it with every map.

![Viridian City, Route 1, Pallet Town and Route 21 North, joined as the game joins them](world_pallet_viridian.png)

(From the top: Viridian City, Route 1 and Pallet Town are rebuilt; Route 21 North is still the old map. Make the
picture again with `pae map render` for each map, placed by the offsets below.)

## Rebuilt maps

| Map | Size (blocks) | Was | Tilesets | Joins |
|---|---|---|---|---|
| Pallet Town | 32×28 | 24×20 | kit + `gTileset_PalletConcept` | up: Route 1 (offset −10), down: Route 21 North (offset 11) |
| Route 1 | 50×40 | 50×40 | kit + `gTileset_Route1Concept` | up: Viridian City (offset −2), down: Pallet Town (offset 10) |
| Viridian City | 60×52 | 56×50 | kit + `gTileset_ViridianConcept` | up: Route 2 (offset 16), left: Route 22 (offset 22), down: Route 1 (offset 2) |
| Route 22 | 52×28 | 52×28 | kit + `gTileset_Route22Concept` | right: Viridian City (offset −22); not joined to Route 23 (below) |
| Route 2 | 30×80 | 30×80 | kit + `gTileset_Route2Concept` | up: Pewter City (offset −14), down: Viridian City (offset −16) |
| Pewter City | 52×44 | 52×44 | kit + `gTileset_PewterConcept` | down: Route 2 (offset 14), right: Route 3 (offset 15) |
| Route 3 | 84×20 | 84×20 | kit + `gTileset_Route3Concept` | left: Pewter City (offset −15), up: Route 4 (offset 60) |
| Route 4 | 108×20 | 108×20 | kit + `gTileset_Route4Concept` | down: Route 3 (offset −60), right: Cerulean City (offset −7) |
| Cerulean City | 58×51 | 58×51 | kit + `gTileset_CeruleanConcept` | up: Route 24 (offset 25), down: Route 5 (offset −8), left: Route 4 (offset 7), right: Route 9 (offset 20) |
| Route 24 | 30×22 | 30×22 | kit (and an empty `gTileset_Route24Concept`) | down: Cerulean City (offset −25), up: Route 25 (offset 0) |
| Route 25 | 70×24 | 112×35 | kit + `gTileset_Route25Concept` | down: Route 24 (offset 0) |
| Route 5 | 50×36 | 68×46 | kit + `gTileset_Route5Concept` | up: Cerulean City (offset 8), down: Saffron City's twin `SaffronCity_Connection` (offset −4) |
| Route 6 | 56×32 | 63×36 | kit + `gTileset_Route6Concept` | up: `SaffronCity_Connection` (offset 12), down: Vermilion City (offset 8) |
| Vermilion City | 60×42 | 71×78 | kit + `gTileset_VermilionConcept` | up: Route 6 (offset −8), right: Route 11 (offset −3) |
| Route 11 | 60×32 | 72×40 | kit + `gTileset_Route11Concept` | left: Vermilion City (offset 3), right: Route 12 (offset −27) |
| Route 9 | 60×28 | 65×60 | kit + `gTileset_Route9Concept` | left: Cerulean City (offset −20), right: Route 10 (offset 0) |
| Route 10 | 38×60 | 38×90 | kit + `gTileset_Route10Concept` | left: Route 9 (offset 0), down: Lavender Town (offset 4) |
| Lavender Town | 38×32 | 38×31 | kit + `gTileset_LavenderConcept` | up: Route 10 (offset −4), left: Route 8 (offset −4), down: Route 12 (offset 2) |
| Route 8 | 60×30 | 68×40 | kit + `gTileset_Route8Concept` | left: Saffron City's twin `SaffronCity_Connection` (offset −15), right: Lavender Town (offset 4) |
| Route 7 | 30×24 | 20×28 | kit + `gTileset_Route7Concept` | left: Celadon City (offset −2), right: Saffron City's twin `SaffronCity_Connection` (offset −18) |
| Viridian Forest | 48×60 | 74×79 | kit + `gTileset_ViridianForestConcept` | none: its exits are warps to Route 2's two gates |

## Where the roads meet

A join lines up one column (or row) of each map, `pae map connect A up B --align a,b`. The roads have to meet:

| Join | Columns | Notes |
|---|---|---|
| Pallet ↔ Route 1 | Pallet 14–15 = Route 1 24–25 | Pallet's road north; Route 1's road under its arch |
| Route 1 ↔ Viridian | Route 1 22–25 = Viridian 24–27 | Route 1's road widens to meet Viridian's |
| Pallet ↔ Route 21 North | Pallet 18–21 = Route 21 7–10 | the water channel south (surf) |
| Viridian ↔ Route 2 | Viridian 22–27 = Route 2 6–11 | Viridian's one-block road north (the old man's) widens at the edge to meet Route 2's path |
| Viridian ↔ Route 22 | Viridian rows 28–31 = Route 22 rows 6–9 | the road west |
| Route 2 ↔ Pewter | Route 2 8–11 = Pewter 22–25 | the road north becomes Pewter's main street |
| Pewter ↔ Route 3 | Pewter rows 24–27 = Route 3 rows 9–12 | the road east |
| Route 3 ↔ Route 4 | Route 3 68–75 = Route 4 8–15 | the pass north becomes the road up to Mt. Moon |
| Route 4 ↔ Cerulean | Route 4 rows 10–13 = Cerulean rows 17–20 | the road east into town |
| Cerulean ↔ Route 24 | Cerulean 41–44 = Route 24 16–19 | Nugget Bridge |
| Route 24 ↔ Route 25 | Route 24 7–10, 16–19, 24–25 = Route 25 the same | the west path, the bridge and the east path (Route 25's bottom row, 23) |
| Cerulean ↔ Route 9 | Cerulean rows 28–30 = Route 9 rows 8–10 | the road east into Route 9's forest neck |
| Route 9 ↔ Route 10 | Route 9 rows 17–19 = Route 10 rows 17–19 | the road out into Route 10's clearing |
| Route 10 ↔ Lavender | Route 10 16–20 = Lavender 12–16 | the valley road down into Lavender's north road |
| Lavender ↔ Route 8 | Lavender rows 9–11 = Route 8 rows 13–15 | the street west onto Route 8's road |
| Route 8 ↔ Saffron | Route 8 row 12 = Saffron row 27 | not walked across: the gate's doors on Route 8 (10–11,12) lead through the gatehouse to Saffron's own east gate door (62,27). Old Saffron draws its own half of the gatehouse, and no neighbour (KR-53) |
| Route 7 ↔ Celadon | Route 7 rows 10–13 = Celadon rows 12–15 | the road west out of the trees into Celadon's east street (Celadon isn't rebuilt) |
| Route 7 ↔ Saffron | Route 7 row 9 = Saffron row 27 | not walked across: the gate's doors on Route 7 (18–19,9) lead through the gatehouse to Saffron's own west gate door |
| Lavender ↔ Route 12 | Lavender 13–15 = Route 12 11–13 | the road south from the square onto Route 12's sandy path (Route 12 isn't rebuilt; KR-50, KR-51) |
| Cerulean ↔ Route 5 | Cerulean 21–24 = Route 5 29–32 | the road south, past the neck |
| Route 5 ↔ Saffron | Route 5 24–25 = Saffron 28–29 | not walked across: the gate's top door on Route 5 (24–25,30) leads through the gatehouse to Saffron's own gate door below it (28–29,5). Old Saffron draws its own copy of the gatehouse at its top |
| Saffron ↔ Route 6 | Saffron 28–29 = Route 6 40–41 | not walked across: Saffron's south gate door (28–29,46) leads through the gatehouse to its door on Route 6 (40–41,5) |
| Route 6 ↔ Vermilion | Route 6 40–42 = Vermilion 32–34 | the road down into Vermilion's plaza |
| Vermilion ↔ Route 11 | Vermilion rows 11–14 = Route 11 rows 14–17 | the main street east onto Route 11's road |
| Route 11 ↔ Route 12 | Route 11 rows 17–19 = Route 12 rows 44–46 | the road east past the gatehouse (Route 12 isn't rebuilt; Snorlax sleeps on its side, reached through the gatehouse) |

When a map changes size, keep these columns where they meet (move the map's road, or change the offset), and if a
map grows to the left or top, its neighbours' offsets change with it.

## Seams

Maps on different tilesets need connection seams (`pae seam build`) so each shows its neighbour's edge right.

| Map | Shows across its edges | How |
|---|---|---|
| Pallet Town | Route 1, Route 21 North | pae |
| Route 1 | Pallet Town, Viridian City | pae |
| Viridian City | Route 1, Route 2, Route 22 | pae (its hand-made seam for the old Viridian is gone) |
| Route 2 | Viridian City, Pewter City | pae |
| Pewter City | Route 2, Route 3 | pae |
| Route 3 | Pewter City, Route 4 | pae |
| Route 4 | Route 3, Cerulean City | pae |
| Cerulean City | Route 4, Route 5, Route 9, Route 24 | pae: 137 adapters, palette slots 10, 11, 12 (since Route 24 is from the kit, every colour fits). Its hand-made seam for the old Cerulean is gone |
| Route 5 | Cerulean City | pae (both from the kit: no palettes). None with old Saffron: it has no tile slot left for Route 5's strip, and neither can see the other (`--skip`, KR-34). Its hand-made seam is gone |
| Route 6 | Vermilion City | pae (both from the kit: Vermilion's own palettes fit in Route 6's banks 10–12, exactly). None with old Saffron (KR-34) |
| Vermilion City | Route 6, Route 11 | pae (both from the kit: their seams fit exactly). Old Vermilion's hand-made seam is gone |
| Route 11 | Vermilion City, Route 12 | pae: Route 12's palettes fit in banks 10–11. Old Route 12 has no room for two of Route 11's palettes and draws them in its nearest colours (KR-39). Old Route 11's hand-made seam is gone |
| Route 9 | Cerulean City, Route 10 | pae (all three from the kit: only each other's own tiles, no palettes). Old Route 9's hand-made seam is gone |
| Route 10 | Route 9, Lavender Town | pae (all three from the kit: their seams fit exactly) |
| Lavender Town | Route 10, Route 8, Route 12 | pae: old Route 12's palettes fit in banks 10–12 (Routes 10 and 8 are the kit's) |
| Route 8 | Lavender Town | pae (both from the kit: no palettes). None with old Saffron, as for Routes 5 and 6 (KR-34): no block of Route 8 is in view of it, and old Saffron draws no neighbour (KR-53) |
| Route 7 | Celadon City | pae: Celadon's palettes fit in Route 7's banks 10–11; old Celadon has room for Route 7's strip only as forest and road, two palettes in its nearest colours (KR-54). None with old Saffron (KR-34, KR-53). Old Route 7's hand-made seam is gone |
| Route 24 | Cerulean City, Route 25 | pae |
| Route 25 | Route 24 | pae (both from the kit: only each other's own tiles, no palettes) |
| Route 21 North | Pallet Town | pae |
| Route 22 | Viridian City | pae (both from the kit: only each other's own tiles); its hand-made seam is gone |
| Route 23 | Indigo Plateau | hand-made (its pieces for the old Route 22 are gone) |

Maps built from the kit share the primary tileset, so between them the seams only copy secondary tiles. When both
neighbours are rebuilt from the kit with the same secondary tileset, the seam isn't needed at all.

A seam needs a palette slot in the viewing map for every palette of the strip it shows (the 7 rows or columns
beside the join) that the viewing map doesn't have. Old maps have few free: Viridian's hand-made seam for Route 22
leaves it three. So near a join with a map that isn't rebuilt yet, keep pieces with palettes of their own out of
those 7 rows: Route 1's tall grass (bank 4) starts at row 7. Between maps from the kit, the seams use each other's
palettes and need no slots. A strip of an old map takes slots: its tiles are copied, so pae packs their colours into
as few slots as they fit. Old Route 3's strip takes one slot of Pewter (11, of the two it keeps free).

**Route 23 isn't joined to Route 22.** The join was only seen across Route 22's top (both edges are solid: you go
through the League gate), and Route 23's strip needs seven palettes, more than Route 22 has free. So each shows its
own border there. Join them again (`pae map connect Route22_Frlg up Route23_Frlg --offset 0`) when Route 23 is
rebuilt from the kit.

## Planned

- **Pallet's sea → Cinnabar.** The sea east of Pallet will lead to Cinnabar Island (the old Route 21 ran south of
  Pallet), so it becomes surfable then: the kit's sea is solid for now (scenery under the cliff), and its rocks stay
  solid. That needs a join off Pallet's east edge (or the sea to meet Route 21's water) and the sea's surf rules
  checked in game (surfing off the cliff top, into a rock).

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
- Viridian City rebuilt larger: 60×52 instead of 56×50 (four columns east, two rows south). Its exits kept their
  columns and rows, so no join's offset changed; Route 1 now enters it at row 51. Its heal spot, the Friends camp and
  Route 2's copy of its old tree to cut moved or went; its hand-made seam went too.
- Route 22 rebuilt at the same size, so Viridian's join didn't change; now both are from the kit, they show each other
  (Route 22's strip was missing while it was the old map). Its hand-made seam and Route 23's pieces for it went; it's
  no longer joined to Route 23 (above).
- Route 22's cliffs redone from a rock and cliff pack (tops in nine phases, two-block faces, stairs, rocks): its
  forecourt's edge is a face with stairs now, the rest of the route (and its joins) as it was.
- The kit's trees are the Sunlit Broadleaf pack's (broadleaf trees instead of pines) on every kit map. The forest
  keeps its cells, so no map's layout, walls or joins changed.
- Route 2 rebuilt at the same size, so Viridian's and Pewter's joins didn't change. Its warps (the forest's gates,
  the east building, the trade house, Diglett's Cave), the trees to cut (three now), items, signs and the Friends
  camp moved; the camp's anchor and first local id in `src/data/friends_scene_locations.h` changed with it. Pewter
  got a pae seam for it. The kit reserves tiles 434–449 for doors now (double doors' frames), and gained three
  forest corners.
- Viridian Forest rebuilt smaller: 48×60 instead of 74×79. It joins nothing (its exits are warps to Route 2's gates,
  which keep their numbers), so no other map changed. Its trainers, people, items, signs, hidden items and Pokémon
  moved; Rick, Sammy, Anthony and Charlie face another way, every trainer but Charlie sees a different distance, and
  four of its Pokémon are other species.
  The kit gained three forest corners, so every kit map was rebuilt (no layout, wall or join changed).
- Pewter City rebuilt at the same size, so Route 2's and Route 3's joins didn't change. Its warps, people, signs and
  hidden item moved (each warp kept its number); the heal spot moved to the new Center (29,33,
  `src/data/heal_locations.json`). The Gym guide's and the Museum guide's walks were worked out again for the new
  town (`pewter-concept/escort.py`). Route 3 (still the old map) got a pae seam for it. The kit gained cliffs for
  every map (`kit/cliffs.py`).
- Route 3 rebuilt at the same size, so Pewter's and Route 4's joins didn't change. Its trainers, Pokémon, sign and
  hidden item moved (the trainers keep their scripts and the way they face). Route 4 (still the old map) got a pae
  seam for it.
- Route 4 and Cerulean City rebuilt at the same sizes, so none of their joins moved (Cerulean's east road is three
  rows, as Route 9's edge opens). One pull request: old Cerulean had no room for a seam to the new Route 4. Every
  warp kept its number; people, signs and hidden items moved, the heal spots moved to the new Centers (Route 4 6,9;
  Cerulean 28,29), the Friends' Cerulean camp to 34,32 (`src/data/friends_scene_locations.h`), the lass and her
  Slowbro's place in the neck to 22–23,45 (`CeruleanCity_EventScript_BlockExits`), and Route 4's copy of Cerulean
  Cave's guard to 114,0. Old Cerulean's hand-made seam was removed from `kanto_connection_seam.c`. Routes 5, 9 and 24
  (still old) got pae seams for the new town.
- Route 24 rebuilt at the same size, so Cerulean's and Route 25's joins didn't change. Its people moved (the bridge's
  five trainers now see three blocks: `build.sh` sets it); the Rocket and his triggers stayed. Old Route 24's border
  entry was removed from `firered_geometry_payload_aliases.json`. Route 25 (still the old map) got a pae seam for it.
- Route 25 rebuilt smaller (70×24, was 112×35); its join with Route 24 stayed (offset 0: Route 24's three ways in
  meet its bottom at the same columns). Its one warp (the Sea Cottage's door) kept its number; people, the sign and
  the hidden items moved; Wayne faces down and Chad walks left and right (`build.sh` sets them). Nothing else in the
  game uses its coordinates but the credits' view of it (25,6), which hasn't been looked at (KR-31).
- Route 5 rebuilt smaller (50×36, was 68×46) with its x the same, so Cerulean's and Saffron's offsets didn't change
  (Cerulean's neck meets it at 29–32; its gate's top door, 24–25, is over Saffron's gate door). Every warp kept its
  number: the gate's four (2–5) are on its two door blocks. Its mons and sign moved; Spinda is at the ground's
  elevation. Old Route 5's hand-made seam was removed from `kanto_connection_seam.c`; old Saffron gets no seam for
  it yet (KR-34).
- Route 6 rebuilt smaller (56×32, was 63×36) with its x the same, so Saffron's and Vermilion's offsets didn't
  change (its gate's door, 40–41, under Saffron's south gate door; its road onto Vermilion's stairs at 40–42). Every
  warp kept its number; its trainers, Pokémon, sign and hidden items moved (`build.sh` sets the trainers' facings
  and sights). Old Vermilion got a pae seam for it, its colours nearest-matched (KR-35).
- Vermilion rebuilt smaller (60×42, was 71×78) with its joins where they were (Route 6's road in at 32–34, Route
  11's at rows 11–14). Every warp kept its number: the S.S. Anne's three are its gangway at the pier's end, which
  warps you as you step on it (`MB_DEEP_SOUTH_WARP`), with the ferry sailor and his ticket check where they were
  relative to it. The heal spot moved with the Center (28,7, `src/data/heal_locations.json`, its old-map override
  dropped); the Friends' camp stayed at 30,19. Old Vermilion's hand-made seam was removed from
  `kanto_connection_seam.c`; Route 11 (still the old map) got a pae seam for it.
- Route 11 rebuilt smaller (60×32, was 72×40) with its joins where they were (Vermilion's main street in at
  rows 14–17, Route 12's road out at 17–19). Every warp kept its number: Diglett's Cave's mouth (16,6) and the
  gatehouse's two doors (53–54,15). Its trainers, items, Pokémon, sign and hidden item moved; the trainers keep
  their facings and sights, and the walkers keep near their places (`build.sh`). The Friends' clearing stayed
  round 25,7. Old Route 11's hand-made seam was removed from `kanto_connection_seam.c`; old Route 12 got a pae
  seam for it, two of its palettes nearest-matched (KR-39).
- Routes 9 and 10 rebuilt together (old Route 10 had no tile slot for a seam to the new Route 9). Route 9 is smaller
  (60×28, was 65×60, its top half mountain) and its rows moved: Cerulean's offset to it is now 20 (was −6), and the
  road out at rows 17–19 meets Route 10's 17–19 (offset 0, was 26). Its tree to cut moved 9 blocks in (KR-45), and
  Cerulean's clone of it with it (67,29). Route 10 is shorter (38×60, was 38×90), as wide, so Lavender's offset (4)
  didn't change. Every warp kept its number: Rock Tunnel's two mouths, the Center, the Power Plant's door; its back
  door's way out is on the island (KR-46). Route 10's heal spot moved with its Center (14,16, its old-map override
  dropped). Old Route 9's hand-made seam was removed from `kanto_connection_seam.c` (Route 10 had none).
- Lavender Town rebuilt (38×32, was 38×31) round a square where its three roads meet. Route 10's join (offset −4) and
  Route 8's (−10) stayed; its road south leaves from under the square, so Route 12 moved 4 blocks east under it
  (offset 2, was −2; KR-50). Every warp kept its number: Pokémon Tower, the Center, the Volunteer House, the two
  houses, the Mart. The people kept their order (the stranger by the Volunteer House is removed by local id): the
  girl, the worker, the boy (his old spot is inside a house now) and four of the night ghosts moved, the rest kept
  their places. The heal spot
  moved with the Center (7,7, its old-map override dropped); the Friends' camp stayed round 13,13. Old Lavender had
  no hand-made seam.
- Route 8 rebuilt smaller (60×30, was 68×40, half of it mountain) and its rows moved: Lavender's street meets it at
  rows 13–15 (Lavender's offset −4, was −10), and its gate door is at row 12, level with Saffron's own east gate door
  as before (offset −15, was −6; old Saffron's offset to it set to match, though Saffron's joins aren't compiled:
  KR-53). Every warp kept its number: the Underground Path's hut (18,12) and the gate (10,12), whose right door block
  is a new warp 2 to the same door inside (KR-52). The trainers, trees, Pokémon, sign and hidden berries moved;
  Rich turned to the track and the bikers ride its loop (`build.sh`). Old Route 8 had no hand-made seam.
- Route 7 rebuilt (30×24, was 20×28) and its rows moved: Celadon's street meets it at rows 10–13 (Celadon's offset 2,
  was 8), its gate door at row 9, level with Saffron's own west gate door as before (offset −18, was −15; old
  Saffron's offset set to match). Every warp kept its number: the Underground Path's hut (9,9) and the gate (18,9),
  whose right door block is a new warp 2. Celadon's border tree clone moved with the join (−7,19). Old Route 7's
  hand-made seam was removed from `kanto_connection_seam.c`.

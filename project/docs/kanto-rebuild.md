# Rebuilding Kanto, town by town

The goal: every Kanto town and route rebuilt from the kit (`project/art/kit`), one map at a time, in the order the
story reaches them. Each map gets its own concept (a block plan and the reasoning for it), is built with pae, and goes
in its own pull request with its replay tests and its story check steps. This page tracks the order, where each map
stands, and the issues found on the way, so they can be reviewed later. Update it in the same pull request as the map.

Caves and buildings' insides (Mt. Moon, Rock Tunnel, Diglett's Cave, the Gyms, houses) are not part of it: the kit is
outdoor art. They stay the old maps; their doors and warps keep working.

## How each map is done

1. **Concept**: a block plan (`plan_stage1.txt`, one letter per block, the kit's legend) and a README saying what the
   map is for, what changed from the old one and why. Keep the old map's joins where its neighbours meet it, or move
   them and fix the neighbour's offset; keep every warp's number (the maps behind it point at it).
2. **Art**: the kit, the kit's buildings, and buildings from earlier maps, recoloured where a town should look its own.
3. **Build**: `make_art.py` (checks the plan's rules on the map it builds) and `build.sh`, added to
   `project/art/build_all.sh`.
4. **Events and scripts**: every event placed; scripts that walk people round the map by fixed steps redone for the
   new map (`pae map path` writes the steps).
5. **Tests**: `pae test run`, a replay test for every new or changed event; the story check from the first step the map
   changes, and new steps through it.
6. **Pull request**, then merge once its tests pass; the next map starts from it.

## The maps

| # | Map | Was (blocks) | Now | Pull request | Notes |
|---|---|---|---|---|---|
| – | Pallet Town, Route 1, Viridian City, Route 22, Route 2, Viridian Forest | | done | #(earlier), #36 | Rebuilt before this plan. |
| 1 | Pewter City | 52×44 | 52×44 | #38 | The grey-stone town under the mountains; the guides' walks worked out on the map (`escort.py`). |
| 2 | Route 3 | 84×20 | 84×20 | #39 | The mountain road: a high path with a ledge, a field of grass you can't walk round, the pass north. |
| 3 | Route 4 | 108×20 | 108×20 | this PR | Round Mt. Moon: the foot of the mountain with the Center, the high shelf where the cave comes out, its ledge down to the road to Cerulean. |
| 4 | Cerulean City | 58×51 | 58×51 | this PR | The lake town: the bridge road, the cave's island, the robbed house's backyard, the neck south. With Route 4: old Cerulean had no room for the seam between them. |
| 5 | Route 24 | 30×22 | | | Nugget Bridge. |
| 6 | Route 25 | 112×35 | | | Bill's cottage. |
| 7 | Route 5 | 68×46 | | | Day Care, the Underground Path's gate. |
| 8 | Route 6 | 63×36 | | | |
| 9 | Vermilion City | 71×78 | | | Harbour (the S.S. Anne), Fan Club, Cut tree to the Gym. |
| 10 | Route 11 | 72×40 | | | Diglett's Cave's south mouth, the east gate. |
| 11 | Route 9 | 65×60 | | | |
| 12 | Route 10 | 38×90 | | | Rock Tunnel's mouths, the Power Plant by water. |
| 13 | Lavender Town | 38×31 | | | Pokémon Tower. |
| 14 | Route 8 | 68×40 | | | Underground Path's east gate. |
| 15 | Route 7 | 20×28 | | | |
| 16 | Celadon City | 60×40 | | | Department Store, Game Corner, Mansion. |
| 17 | Saffron City (and its twin `SaffronCity_Connection`) | 66×55 | | | Silph Co.; the guards at its four gates. |
| 18 | Route 16 | 64×52 | | | Snorlax, Cycling Road's gate. |
| 19 | Route 17 | 33×158 | | | Cycling Road (slopes). |
| 20 | Route 18 | 60×20 | | | |
| 21 | Fuchsia City | 48×40 | | | Safari Zone gate, the Warden. |
| 22 | Route 15 | 96×32 | | | |
| 23 | Route 14 | 26×62 | | | |
| 24 | Route 13 | 104×32 | | | |
| 25 | Route 12 | 38×90 | | | Snorlax, the fishing house. |
| 26 | Route 19 | 24×60 | | | Sea route. |
| 27 | Route 20 | 120×20 | | | Sea route, Seafoam Islands. |
| 28 | Cinnabar Island | 96×44 | | | Mansion, Lab, Gym. |
| 29 | Route 21 (North and South) | 24×50 each | | | Sea route to Pallet. |
| 30 | Route 23 | | | | Victory Road's mouth, the badge gates. |
| 31 | Indigo Plateau | 24×20 | | | The League's front. |

## Issues to review

Found while rebuilding; nothing here is fixed unless it says so. Newest last within each kind.

### Tools (pae)

| Id | Issue | Seen | State |
|---|---|---|---|
| KR-1 | `pae map geometry --blockdata` keeps the layout's `blockdata_overrides`, which point at the old block file; a map that had them fails to build (`Sparse blockdata edit is outside its geometry/word bounds`). Viridian Forest clears them by hand (`"blockdata_overrides": null`). | Viridian Forest | fixed in pae PR #22 (a new block file drops them) |
| KR-2 | Every pae command indexed the whole project on start (6 s), so a map's build took minutes and rebuilding every kit map 22 minutes. | Viridian Forest | fixed in pae PR #21 (the index is made when first needed) |
| KR-16 | A seam took a neighbour's colours only exactly, so a town between three old routes (Cerulean: Routes 5, 9, 24) ran out of palette banks. | Cerulean | fixed in pae PR #23: a palette with no room is drawn in its nearest colours, and `pae seam build` says so (Route 5's strip in Cerulean: 5 colours, at most 54 RGB steps off, until Route 5 is rebuilt) |
| KR-17 | Old maps whose tilesets fill all 1024 metatile ids (old Cerulean, Route 24) had no room for a seam's adapters, so a new neighbour couldn't be joined to them. | Route 4, Cerulean | fixed in pae PR #23: adapters take the top ids the map never shows (its blocks, border, scripts, and same-tileset neighbours' strips) |

### Build and process

| Id | Issue | Seen | State |
|---|---|---|---|
| KR-3 | A map's `build.sh` can drift from its `map.json`: Viridian's still placed the Friends at their old camp after PR #34 moved them, so a rebuild undid it. | Viridian Forest | fixed in #36; check each map's build script against its events when a scene moves people |
| KR-8 | A map's own tileset holds 384 tiles, and big buildings take most of it (Pewter's Museum 98, its Gym 66, the cliffs about 90, the seam to an old neighbour 39): Pewter's three houses had to be one kind. Towns with several big buildings (Celadon, Saffron) will need fewer kinds or smaller buildings. | Pewter | watch |
| KR-9 | Scenes that walk people round a town by fixed steps (Pewter's guides) break when the town is rebuilt. Pewter's are worked out on the built map by `pewter-concept/escort.py`; other towns' (Vermilion's, Celadon's) will need the same. | Pewter | done for Pewter |
| KR-12 | When a story-check walk is stopped by a trainer who sees you, pae reports "the map did not finish loading" or that checkpoints can only be saved in the overworld, not that a trainer started a battle. | Route 3 (Pewter's Gym) | open |
| KR-13 | After `CLEAR_TEAM` and a new Pokémon in a test's or step's state, the Pokémon following you stays the old one (a Pikachu followed a team of one Wartortle). Harmless for the tests; a player can't do it. | Route 3 (Pewter's Gym) | watch |
| KR-4 | Adding a forest corner (or any kit piece) renumbers the kit's later metatiles, so every kit map is rebuilt and repainted. Nothing broke so far (the review checked the blocks are the same), but scripts that set metatiles by number on kit maps would break. | Viridian Forest | watch |
| KR-18 | Old Cerulean had a hand-made seam in `kanto_connection_seam.c` (a fix for its two tilesets) that took two palette banks and ids 954–1022 on the new town; it is removed. Route 5's and Route 9's hand-made seams still have 17 entries for old Cerulean's ids, which the new town never uses (dead data, harmless). | Cerulean | Cerulean's removed; the others go when Routes 5 and 9 are rebuilt |

### Story and gameplay

| Id | Issue | Seen | State |
|---|---|---|---|
| KR-10 | Pewter's cobbled main street meets Route 2's dirt road at the join with no edge between them (both are drawn right; it's a hard line). | Pewter | cosmetic, open |
| KR-5 | The story check's steps 1–33 haven't been run since the kit maps were rebuilt for the forest (their replay tests pass). | Viridian Forest | open |
| KR-6 | The Friends' scenes 2 (Route 2) and 12 (Pallet) are on rebuilt maps and haven't been played since (see `friends-story-triggers.md`). | before this plan | open |
| KR-7 | The forest's pond (like every kit pond) can be surfed and fished once you have Surf; the concept wanted it for looking at only. Harmless (it leads nowhere). | Viridian Forest | decided: keep |
| KR-14 | The kit's cliff tops are wide plain stretches on mountain maps (Pewter, Route 3): the pack's texture repeats every three blocks with nothing on it. Rocks or a second texture on the tops would break it up. | Route 3 | cosmetic, open |
| KR-15 | Route 3's Robin wanders, so her line of sight has no replay test (the seven other trainers have one each). | Route 3 | open |
| KR-11 | Pewter's heal spot moved with its Center (29,33); flying there and blacking out were not played. | Pewter | open |
| KR-19 | Cerulean's robbed house has no hole drawn in its back wall, and the badge house no back door: both are lawn you stand on and walk south from into the house (an arrow warp). A drawn hole and door would say where they are. | Cerulean | cosmetic, open |
| KR-20 | Cerulean Cave's mouth is Route 2's, drawn in the houses' palette (the two colours they don't use are its own, the rest each the nearest): its rock is a little greener and greyer than Route 2's. | Cerulean | cosmetic, open |
| KR-21 | Cerulean's Friends' camp moved to 34,32 (their fourth scene) and Route 4's stayed; neither scene has been played since (see KR-6). Cerulean's heal spot (28,29) was not played either (as KR-11). | Cerulean | open |
| KR-22 | The tree to cut in Cerulean now closes a fenced garden with nothing in it yet; the old one stood by the lass and her Slowbro. Something to find in the garden would make cutting it worth it. | Cerulean | open (an idea) |

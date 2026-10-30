# Story sanity check

This is a play-through of the story from a new game, through every map rebuilt so far. It is run after each route
or town change, to check that the story still plays to the end of the rebuilt maps. This page records the last
point that passed, so the next check carries on from there instead of starting again.

The replay tests (`pae test run`) each check one event, starting from story state the test sets up. This check
plays the events one after another, each starting where the last one left the game, with no story state set up.

## Last validated point

| | |
|---|---|
| Date | 2026-10-28 |
| Game | branch `claude/saffron-city-blocks` (Saffron paved, with offices and shops without doors: KR-88), on `v2-main` `717d454b` |
| ROM | `make -j4` with the default settings. SHA-1 `cdcb1e5be5707021b69293990c00ff9594057bc0` |
| pae | `3b4aad4` (pae PR #36, `"dedupe"`, on `main` after PR #35) |
| Last step passed | 399 `indigo-center`, the end of the check. **Steps 247 (`saffron`) to 399 pass in one run** (3346 s) from step 246's checkpoint; steps 1-246 don't enter Saffron and passed on `v2-main` (`claude/buildings-v0.3`: all 399 from the top) |
| Replay tests | `pae test run`: 550 tests, on the build just before an unused palette (bank 12) was put back as it was: 529 passed, 21 Saffron ones changed only their screen (the city paved, the new buildings). Saffron's 38 again on this ROM: the same; the 21 looked at and accepted |

## How to run it

From the repository root, with pae installed:

```sh
project/scripts/story_check.py                  # build, then every step
project/scripts/story_check.py --list           # the steps
project/scripts/story_check.py --from route22   # carry on from a step
project/scripts/story_check.py --to dex         # stop after a step
```

The script needs pae with `pae play --show-flag` (pae PR #17), and pae PR #19 (its walks keep off sideways stairs,
which the old Viridian Forest had). Past Celadon it needs pae PR #32 (pae reads FireRed's own tile behaviours, so its walks keep off water, one-way edges and the Rocket Hideout's spin tiles), and to run a `pae play` beside it in the same project, pae PR #33 (each play has its own scratch save). A run from the top takes about 135 minutes; a run `--from` a later step takes less.

* Each step saves a checkpoint, `story-NN-name`, in `engine/.pae/checkpoints/`. The next step starts from it.
  `--from STEP` needs the checkpoint of the step before it. A fresh clone has no checkpoints, so start from the
  top there. The emulator gives the same result every time, so the checkpoints come out the same too.
* Screenshots of every play go to `engine/.pae/story-check/`, named after the step: `-at` is where it started,
  `-walk0`, `-walk1`… are the walk and its retries, the step's name alone is its inputs, and `-check` is the
  checkpoint as it loads.
* Checkpoints and screenshots are git-ignored (`/engine/.pae/*`). Checkpoints are game saves: never commit them.
* Every play has a Repel on (`VAR_REPEL_STEP_COUNT`), so wild Pokémon don't break up the walks.
* A walk to a block is planned with `pae map path`. If someone is in the way, it waits a little longer and plans
  again from where the player stopped, up to six times.
* A step passes when it ends on the expected map and block, and the story flags and variables it checks have the
  expected values. The first failure stops the run, and the script exits with 1.

### Carrying on after a change

Checkpoints are game saves, so they still load after a map change, as long as the save layout hasn't changed.

* **A route or town was changed**: run `--from` the first step that starts on or walks through that map.
  For example, after a Viridian change, run `--from viridian`. Steps before it are still valid.
* **The save layout changed, or the story before the rebuilt maps changed**: run from the top.
* **No checkpoints** (a fresh clone, or a different machine): run from the top.

## The steps

| # | Step | What it checks | Ends at | Story state it checks |
|---|---|---|---|---|
| 1 | `oak` | A new game: out of the house. Oak stops you at the north exit and walks you to his lab | Oak's lab 6,4 | `VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB` 2 |
| 2 | `pikachu` | Pikachu joins you; Blue takes his starter | Oak's lab 7,4 | `FLAG_SYS_POKEMON_GET` set, `VAR_STARTER_MON` 0 |
| 3 | `lab-battle` | Blue's first battle, with Oak's lessons (the first tutorial battle); Blue leaves | Oak's lab 7,8 | `FLAG_BEAT_RIVAL_IN_OAKS_LAB` set, `VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB` 4 |
| 4 | `leave-lab` | Out of the lab, from the middle of its mat | Pallet Town 21,16 | |
| 5 | `route1` | The sign lady's trainer tips at the route entrance, then into Route 1 (Ho-Oh waits for the Pokédex) | Route 1 25,39 | `FLAG_OPENED_START_MENU` set, `FLAG_RB_OPENING_SEEN` not set, `VAR_MAP_SCENE_PALLET_TOWN_SIGN_LADY` 1 |
| 6 | `potion` | Route 1's Mart clerk gives a Potion | Route 1 23,21 | `FLAG_GOT_POTION_ON_ROUTE_1` set |
| 7 | `viridian` | North into Viridian | Viridian City 25,51 | |
| 8 | `parcel` | Viridian's Poké Mart: the clerk gives Oak's Parcel | Viridian Mart 4,3 | `VAR_MAP_SCENE_VIRIDIAN_CITY_MART` 1, `VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB` 5 |
| 9 | `leave-mart` | Out of the Mart | Viridian City 31,28 | |
| 10 | `south-route1` | South into Route 1 | Route 1 23,0 | |
| 11 | `south-pallet` | Down Route 1, over its ledges, into Pallet | Pallet Town (the walk carries on a block or two) | |
| 12 | `into-lab` | Into Oak's lab | Oak's lab 6,12 | |
| 13 | `dex` | The parcel to Oak: the Pokédex; Blue leaves | Oak's lab 6,4 | `FLAG_SYS_POKEDEX_GET` set; `VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB` 6, `…_VIRIDIAN_CITY_OLD_MAN` 1, `…_ROUTE22` 1, `…_PALLET_TOWN_RIVALS_HOUSE` 1, `…_VIRIDIAN_CITY_MART` 2 |
| 14 | `leave-lab-2` | Out of the lab | Pallet Town 21,16 | |
| 15 | `rivals-house` | Into Blue's house | Blue's house 4,8 | |
| 16 | `town-map` | Daisy gives the Town Map | Blue's house 4,4 | `VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE` 2 |
| 17 | `leave-rivals-house` | Out of Blue's house | Pallet Town 18,8 | |
| 18 | `north-route1` | North into Route 1: Ho-Oh flies over, then the stranger and the Pokédex with no entry | Route 1 25,39 | `FLAG_RB_OPENING_SEEN`, `FLAG_MW01_SEEN` set |
| 19 | `north-viridian` | Up Route 1 into Viridian: Giratina drops the Friends on the road | Viridian City 25,48 | `FLAG_FRIENDS_ARRIVED_IN_VIRIDIAN` set |
| 20 | `old-man` | The old man's catching demonstration (the second tutorial battle) | Viridian City 25,13 | `VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN` 2 |
| 21 | `route2` | The road north is open: into Route 2 | Route 2 9,79 | |
| 22 | `back-viridian` | Back into Viridian | Viridian City 25,0 | |
| 23 | `center` | Into Viridian's Pokémon Center | Viridian Center 7,8 | |
| 24 | `heal` | The nurse heals the team (the Center becomes where you wake after a blackout) | Viridian Center 7,4 | |
| 25 | `leave-center` | Out of the Center | Viridian City 20,28 | |
| 26 | `route22` | West into Route 22 | Route 22 51,7 | |
| 27 | `blue-lose` | Blue meets you on the road and wins: you wake in Viridian's Center | Viridian Center 7,4 | `VAR_MAP_SCENE_ROUTE22` 1 |
| 28 | `blue-win` | The same, from step 26, with a stronger Pikachu: Blue loses and leaves east | Route 22 44,7 | `VAR_MAP_SCENE_ROUTE22` 2 |
| 29 | `league-gate` | Up the stairs in the cliff, across the forecourt, into the League Front Gate | League Front Gate 7,10 | |
| 30 | `leave-league-gate` | Back out of the League Front Gate | Route 22 12,14 | |
| 31 | `east-viridian` | Down the stairs and east along the road into Viridian | Viridian City 0,29 | |
| 32 | `north-route2` | North out of Viridian into Route 2 | Route 2 9,79 | |
| 33 | `forest-gate` | Up Route 2's south meadow into Viridian Forest's south gate (its double door) | the south gatehouse 7,9 | |
| 34 | `forest` | Through the gatehouse into Viridian Forest (its south exit) | Viridian Forest 23,59 | |
| 35 | `forest-rick` | Up the trail and west: Rick sees you across it and battles (you can't walk round him) | Viridian Forest 20,50 | |
| 36 | `forest-doug` | West through the tall grass, north, east, then north: Doug sees you across the trail and battles | Viridian Forest 31,29 | |
| 37 | `forest-north` | On north through the last tall grass to the forest's north exit and its gate | the north gatehouse 7,9 | |
| 38 | `route2-north` | Out of the forest's north gate onto Route 2 (its doorway in the roof, walking north) | Route 2 7,20 | |
| 39 | `pewter` | Up Route 2's north meadow into Pewter City | Pewter City 23,43 | |
| 40 | `pewter-guide` | Up Pewter's main street and east along the road out: the Gym guide stops you and walks you to the Gym | Pewter City 9,21 | |
| 41 | `pewter-gym` | Into Pewter's Gym (a Wartortle now, for its rock types) | Pewter Gym 6,14 | |
| 42 | `gym-liam` | Up the Gym: the camper Liam sees you across it and battles | Pewter Gym 6,8 | |
| 43 | `brock` | On up to Brock and beat him: the Boulder Badge | Pewter Gym 6,6 | `FLAG_BADGE01_GET`, `VAR_MAP_SCENE_PEWTER_CITY` 1 |
| 44 | `leave-gym` | Back out of Pewter's Gym | Pewter City 9,21 | |
| 45 | `running-shoes` | East along the road out: Oak's aide stops you and gives you the Running Shoes | Pewter City 47,26 | `FLAG_SYS_B_DASH`, `VAR_MAP_SCENE_PEWTER_CITY` 2 |
| 46 | `route3` | On east out of Pewter onto Route 3 | Route 3 0,10 | |
| 47 | `route3-north` | Across Route 3 (below the trainers' lines of sight) and up the pass onto Route 4 | Route 4 11,19 | |
| 48 | `mt-moon` | Up Route 4's road past the Pokémon Center into Mt. Moon's near mouth | Mt. Moon 1F 18,37 | |
| 49 | `mt-moon-1f` | Across the first floor, round its trainers' lines of sight and its other ladders, down the north-west ladder | Mt. Moon B1F 3,3 | |
| 50 | `mt-moon-b1f` | Along the first basement's passage and down to the second | Mt. Moon B2F 25,21 | |
| 51 | `mt-moon-grunt4` | The Rocket who looks about the east passage is in the way: step beside him and beat him | Mt. Moon B2F 36,21 | |
| 52 | `mt-moon-grunt1` | Round the rest of the basement to the Rocket in the way north; step into his line of sight and beat him | Mt. Moon B2F 12,22 | |
| 53 | `mt-moon-miguel` | On north to the fossils: Miguel stops you and battles | Mt. Moon B2F 14,11 | `VAR_MAP_SCENE_MT_MOON_B2F` 1 |
| 54 | `mt-moon-fossil` | Take the Helix Fossil; Miguel takes the Dome Fossil and steps aside | Mt. Moon B2F 14,8 | `FLAG_GOT_HELIX_FOSSIL` |
| 55 | `mt-moon-b2f` | North past the fossils and round to the ladder up | Mt. Moon B1F 39,4 | |
| 56 | `mt-moon-out` | Out of Mt. Moon's far mouth onto Route 4's high shelf | Route 4 36,7 | |
| 57 | `route4-ledge` | East along the shelf and down its ledge (one way) | Route 4 50,10 | |
| 58 | `cerulean` | East along Route 4's road into Cerulean City | Cerulean City 0,18 | |
| 59 | `cerulean-rival` | Round the square (the fence along the Center's north side and the policeman in the robbed house's door close the street past it) and up the bridge road: Blue comes down off Nugget Bridge; beat him | Cerulean City 42,7 | `VAR_MAP_SCENE_CERULEAN_CITY_RIVAL` 1 |
| 60 | `cerulean-center` | Into Cerulean's Pokémon Center | Cerulean Center 7,8 | |
| 61 | `cerulean-heal` | Up to the counter and heal | Cerulean Center 7,4 | |
| 62 | `cerulean-leave-center` | Back out to the street | Cerulean City 28,29 | |
| 63 | `nugget-bridge` | Up the bridge road onto Nugget Bridge (Route 24) | Route 24 17,21 | |
| 64 | `bridge-cale` | Up the bridge to its first trainer; beat him | Route 24 17,19 | |
| 65 | `bridge-ali` | The second | Route 24 17,17 | |
| 66 | `bridge-timmy` | The third | Route 24 17,15 | |
| 67 | `bridge-reli` | The fourth | Route 24 17,13 | |
| 68 | `bridge-ethan` | The fifth | Route 24 17,11 | |
| 69 | `bridge-rocket` | At the north end the Rocket steps over, gives you the Nugget and battles (the Wartortle evolves) | Route 24 17,8 | `VAR_MAP_SCENE_ROUTE24` 1 |
| 70 | `route25` | Off the bridge's north end onto Route 25 | Route 25 17,23 | |
| 71 | `route25-joey` | Up off the bridge and east along the cape road into the first neck: Joey sees you; beat him | Route 25 28,9 | |
| 72 | `route25-wayne` | On past the couple and Nob (round the north of their sight) into the second neck: Wayne; beat him | Route 25 47,9 | |
| 73 | `sea-cottage` | Along the headland into Bill's Sea Cottage | Sea Cottage 7,9 | |
| 74 | `bill` | Help the Clefairy (Bill) into his teleporter, then run the cell separator on his PC (one step: see below) | Sea Cottage 4,6 | `FLAG_HELPED_BILL_IN_SEA_COTTAGE` set |
| 75 | `ss-ticket` | Talk to Bill: the S.S. Ticket | Sea Cottage 7,6 | `FLAG_GOT_SS_TICKET` set |
| 76 | `leave-cottage` | Back out onto the headland | Route 25 51,8 | |
| 77 | `back-to-bridge` | Back west along the cape road, round the north of Nob's and Flint's sight, onto the bridge | Route 24 17,0 | |
| 78 | `back-over-bridge` | Back over Nugget Bridge into Cerulean | Cerulean City 42,0 | |
| 79 | `route5` | Through Cerulean and its neck (the lass and her Slowbro gone) onto Route 5 | Route 5 30,0 | |
| 80 | `underground-path` | Down Route 5 into the Underground Path's hut | Underground Path north entrance 13,12 | |
| 81 | `tunnel` | Down the hut's stairs (stand on them, walk east) into the tunnel | Underground Path tunnel 3,4 | |
| 82 | `tunnel-south` | Along the tunnel and up its south stairs | Underground Path south entrance 14,8 | |
| 83 | `route6` | Out of the south hut onto Route 6 | Route 6 46,12 | |
| 84 | `vermilion` | Down Route 6's road (in no trainer's sight) into Vermilion | Vermilion City 33,0 | |
| 85 | `vermilion-center` | Down the road into Vermilion's Pokémon Center | Vermilion Center 7,8 | |
| 86 | `vermilion-heal` | Up to the counter and heal | Vermilion Center 7,4 | |
| 87 | `vermilion-leave-center` | Back out to the plaza | Vermilion City 28,7 | |
| 88 | `route11` | East along Vermilion's main street onto Route 11 | Route 11 0,15 | |
| 89 | `route11-gatehouse` | Along Route 11's road (in no trainer's sight) into the gatehouse | Route 11 gatehouse 1,6 | |
| 90 | `route11-leave-gatehouse` | Out by its west door (stand on it, walk west) | Route 11 53,16 | |
| 91 | `back-to-vermilion` | Back west along the road into Vermilion | Vermilion City 59,12 | |
| 92 | `ss-anne` | Down the pier: the ferry sailor checks the S.S. Ticket; onto the gangway | S.S. Anne outside 32,5 | |
| 93 | `ss-anne-board` | Down the gangway into the ship (its end is an arrow: press down on it) | S.S. Anne 1F 19,2 | |
| 94 | `ss-anne-2f` | West along the corridor, round the worker and off the cabin doors, up the stairs (walk west onto them) | S.S. Anne 2F 2,2 | |
| 95 | `ss-anne-rival` | East along 2F, off the stairs to 3F and the cabin doors, towards the captain's door: Blue battles | S.S. Anne 2F 31,6 | |
| 96 | `captains-office` | Up the stairs to the captain's office (walk east off their foot) | Captain's office 3,7 | |
| 97 | `hm01` | Rub the seasick captain's back: HM01 (Cut) | Captain's office 5,5 | |
| 98 | `leave-office` | Back down the office's stairs (walk west onto them) | S.S. Anne 2F 30,2 | |
| 99 | `ss-anne-down` | Back west along 2F (up the passage's east side, away from the sailor) and down the stairs (east off them) | S.S. Anne 1F 3,8 | |
| 100 | `leave-ss-anne` | East along 1F and out: the ship sails, and you walk onto Vermilion's pier | Vermilion City 38,38 | |
| 101 | `back-to-route6` | Up the pier and the plaza's middle onto Route 6 | Route 6 41,31 | |
| 102 | `route6-hut` | Up Route 6's road into the Underground Path's hut | Underground Path south entrance 13,12 | |
| 103 | `tunnel-back` | Down the hut's stairs (walk west off them) | Underground Path tunnel 2,38 | |
| 104 | `tunnel-north` | Along the tunnel and up its north stairs (west off them) | Underground Path north entrance 12,8 | |
| 105 | `route5-back` | Out of the north hut onto Route 5 | Route 5 35,25 | |
| 106 | `cerulean-back` | Up Route 5 through the neck into Cerulean | Cerulean City 22,50 | |
| 107 | `cerulean-gym` | Into Misty's Gym | Cerulean Gym 7,18 | |
| 108 | `gym-diana` | Round the Gym guy and Luis's sight, round the walkways into Diana's line: she battles | Cerulean Gym 8,7 | |
| 109 | `misty` | Face Misty and beat her: the Cascade Badge | Cerulean Gym 8,7 | |
| 110 | `leave-cerulean-gym` | Back out of the Gym (its mat: press down on it) | Cerulean City 47,37 | |
| 111 | `route9` | East out of Cerulean onto Route 9 | Route 9 0,9 | |
| 112 | `route9-alicia` | Cut the tree in the neck (one Kingler at level 65 with Surf and Cut is the team from here) and on along the gorge: Alicia battles | Route 9 13,9 | |
| 113 | `route9-chris` | On along the gorge: Chris battles | Route 9 19,9 | |
| 114 | `route10` | Along Route 9's road round the outcrop onto Route 10 | Route 10 0,18 | |
| 115 | `route10-center` | Up to Route 10's Pokémon Center | Route 10 Center 7,8 | |
| 116 | `route10-heal` | Up to the counter and heal | Route 10 Center 7,4 | |
| 117 | `route10-leave-center` | Back out to the clearing | Route 10 14,16 | |
| 118 | `rock-tunnel` | Into Rock Tunnel's north mouth | Rock Tunnel 1F 17,2 | |
| 119 | `rt-ashton` | Rock Tunnel 1F, dark: Ashton's line can't be gone round; he battles | Rock Tunnel 1F 24,10 | |
| 120 | `rt-b1f` | Along the south passage to the ladder down | Rock Tunnel B1F 38,38 | |
| 121 | `rt-winston` | Down B1F's east side and west: Winston battles | Rock Tunnel B1F 29,46 | |
| 122 | `rt-martha` | On west and north: Martha battles | Rock Tunnel B1F 17,43 | |
| 123 | `rt-allen` | Round B1F's middle to the hall below the ladder: Allen battles | Rock Tunnel B1F 36,24 | |
| 124 | `rt-1f-west` | Up the ladder to 1F's west side (the Kingler given again, its Surf full) | Rock Tunnel 1F 4,2 | |
| 125 | `rt-lenny` | Down the west side: Lenny battles | Rock Tunnel 1F 7,9 | |
| 126 | `rt-b1f-west` | To the ladder down to B1F's west part | Rock Tunnel B1F 27,22 | |
| 127 | `rt-sofia` | West along B1F's middle: Sofia battles | Rock Tunnel B1F 11,26 | |
| 128 | `rt-dudley` | On west: Dudley battles | Rock Tunnel B1F 5,25 | |
| 129 | `rt-cooper` | North to Cooper, who looks about: face him and battle | Rock Tunnel B1F 3,16 | |
| 130 | `rt-1f-east` | Up the ladder to 1F's east part (the Kingler given again) | Rock Tunnel 1F 45,21 | |
| 131 | `rt-dana` | Round the east part and west along the south passage: Dana battles | Rock Tunnel 1F 26,31 | |
| 132 | `rt-out` | Out of the south mouth onto Route 10 | Route 10 10,46 | |
| 133 | `lavender` | Down Route 10's valley road into Lavender | Lavender Town 14,0 | |
| 134 | `lavender-center` | Down the north road into Lavender's Pokémon Center | Lavender Center 1F 7,8 | |
| 135 | `lavender-heal` | The nurse heals the team | Lavender Center 1F 7,4 | |
| 136 | `lavender-leave-center` | Back out to the street | Lavender Town 7,7 | |
| 137 | `route8` | West along Lavender's street onto Route 8 (the way on is its underground path to Celadon) | Route 8 59,14 | |
| 138 | `route8-underground` | West along Route 8's road (in no trainer's sight) into the Underground Path's hut | Underground Path east hut 13,12 | |
| 139 | `ew-tunnel` | Down the hut's stairs (walk west off them) | Underground Path tunnel 76,4 | |
| 140 | `ew-tunnel-west` | Along the tunnel under Saffron and up its west stairs (west off them) | Underground Path west hut 12,8 | |
| 141 | `route7` | Out of the west hut onto Route 7 | Route 7 9,10 | |
| 142 | `celadon` | West along Route 7's road into Celadon | Celadon City 59,21 | |
| 143 | `celadon-center` | West along the boulevard into Celadon's Pokémon Center | Celadon Center 1F 7,8 | |
| 144 | `celadon-heal` | The nurse heals the team | Celadon Center 1F 7,4 | |
| 145 | `celadon-leave-center` | Back out to the boulevard | Celadon City 49,19 | |
| 146 | `celadon-gym-tree` | Cut the tree in the hedge round Erika's garden and walk through to the Gym's door. The team is set here: one Alakazam at level 100 that knows Psychic, Surf, Cut and Strength | Celadon City Gym 6,18 |  |
| 147 | `erika` | Cut the middle tree of the Gym's hedge and walk up the middle of the garden (in nobody's line of sight) to Erika; face her and beat her: the Rainbow Badge | Celadon City Gym 6,5 | `FLAG_BADGE04_GET` set |
| 148 | `leave-celadon-gym` | Back down the garden, cut the tree again (it grew back) and out of the Gym | Celadon City 12,35 |  |
| 149 | `celadon-garden-out` | Out of Erika's garden: cut the tree in the hedge again (it grew back) and walk through | Celadon City 12,24 |  |
| 150 | `game-corner` | Across Celadon (round the old man by the hedge) into the Game Corner | Celadon City Game Corner |  |
| 151 | `game-corner-grunt` | Up to the Rocket grunt standing at the poster at the back; talk to him and beat him (he runs off) | Celadon City Game Corner 11,3 |  |
| 152 | `rocket-hideout` | Press the switch behind the poster (stairs open in the corner) and take them down into the Rocket Hideout | Rocket Hideout B1F | `FLAG_OPENED_ROCKET_HIDEOUT` set |
| 153 | `hideout-b2f` | Along B1F's top corridor and down its stairs to B2F | Rocket Hideout B2F 28,2 |  |
| 154 | `hideout-b3f` | Round B2F's east rooms (out of the grunt's sight) and down the stairs to B3F | Rocket Hideout B3F 18,2 |  |
| 155 | `hideout-b4f` | Across B3F's spin tiles (three slides) and down the stairs to B4F | Rocket Hideout B4F 11,15 |  |
| 156 | `hideout-lift-key-grunt` | Up B4F's west rooms to the grunt by the Lift Key; talk to him from the side and beat him (he drops the key) | Rocket Hideout B4F 5,2 |  |
| 157 | `hideout-lift-key` | Round him and pick up the Lift Key | Rocket Hideout B4F 3,3 | `FLAG_CAN_USE_ROCKET_HIDEOUT_LIFT` set |
| 158 | `hideout-back-b3f` | Back down the rooms and up the stairs to B3F | Rocket Hideout B3F |  |
| 159 | `hideout-back-b2f` | Back across B3F (two slides) and up its stairs to B2F | Rocket Hideout B2F 21,2 |  |
| 160 | `hideout-moon-stone` | Slide along B2F's top row (out of the grunt's sight) to its west end and pick up the Moon Stone that blocks the way down | Rocket Hideout B2F 2,4 |  |
| 161 | `hideout-elevator` | Down through B2F's spin maze (five slides) to the lift and into it | Rocket Hideout Elevator |  |
| 162 | `hideout-lift-b4f` | Up to the lift's panel, choose B4F (the Lift Key works it) and walk out (the mat's east half) | Rocket Hideout B4F |  |
| 163 | `hideout-door-grunt-west` | Talk to the west grunt guarding Giovanni's door and beat him | Rocket Hideout B4F 16,15 |  |
| 164 | `hideout-door-grunt-east` | Then the east one: with both beaten the barrier between them goes | Rocket Hideout B4F 19,15 |  |
| 165 | `giovanni-hideout` | Through the open door up to Giovanni; face him and beat him (he leaves the Silph Scope behind) | Rocket Hideout B4F 19,5 | `FLAG_HIDE_CELADON_ROCKETS` set |
| 166 | `silph-scope` | Pick up the Silph Scope beside where he stood | Rocket Hideout B4F 19,5 | `FLAG_HIDE_SILPH_SCOPE` set |
| 167 | `hideout-lift-up` | Back down to the lift and up to B1F | Rocket Hideout B1F |  |
| 168 | `hideout-b1f-grunt-lift` | West from the lift into the line of the grunt who watches it: he battles | Rocket Hideout B1F 21,26 |  |
| 169 | `hideout-b1f-grunt-east` | Up the corridor to the east room and into the line of the grunt at its door: he battles | Rocket Hideout B1F 22,12 |  |
| 170 | `hideout-out` | Up through the middle room and the stairs back up into the Game Corner | Celadon City Game Corner |  |
| 171 | `game-corner-out` | Down past the slot machines and out to Celadon | Celadon City 28,30 |  |
| 172 | `celadon-mansion` | Into Celadon Mansion | Celadon City Condominiums 1F |  |
| 173 | `tea` | Up to the old woman with the Meowth: she gives you Tea (Saffron's thirsty guards will let you by for it) | Celadon City Condominiums 1F | `FLAG_GOT_TEA` set |
| 174 | `celadon-mansion-out` | Back out to the boulevard | Celadon City |  |
| 175 | `route7-back` | East along the boulevard onto Route 7 | Route 7 |  |
| 176 | `route7-hut` | Into the Underground Path's west hut | Underground Path West Entrance |  |
| 177 | `ew-tunnel-back` | Down the hut's stairs into the tunnel | Underground Path East West Tunnel |  |
| 178 | `ew-tunnel-east` | Along the tunnel to its east stairs and up into the east hut | Underground Path East Entrance |  |
| 179 | `route8-back` | Out of the east hut onto Route 8 | Route 8 18,13 |  |
| 180 | `lavender-back` | East along Route 8's road into Lavender | Lavender Town 0,10 |  |
| 181 | `pokemon-tower` | Across Lavender into the Pokémon Tower | Pokémon Tower 1F |  |
| 182 | `tower-2f` | Up the hall to the stairs and up to 2F | Pokémon Tower 2F 18,10 |  |
| 183 | `tower-rival` | Up 2F's east side and west under the rival: he turns, battles, and leaves | Pokémon Tower 2F 16,6 | `VAR_MAP_SCENE_POKEMON_TOWER_2F` 1 |
| 184 | `tower-3f` | West along 2F's north hall and down to the stairs up to 3F | Pokémon Tower 3F 4,10 |  |
| 185 | `tower-4f` | Round 3F's west room, up its middle and east along the north hall (in no channeler's sight) to the stairs up to 4F | Pokémon Tower 4F 18,10 |  |
| 186 | `tower-5f` | Through 4F's rooms (in no channeler's sight) to the stairs up to 5F | Pokémon Tower 5F 4,10 |  |
| 187 | `tower-ruth` | Up 5F's west side and east along its north hall into the channeler Ruth's line (every way east crosses it): she battles | Pokémon Tower 5F 11,6 |  |
| 188 | `tower-purified` | Down into the middle room's purified zone: the team is healed | Pokémon Tower 5F 12,9 |  |
| 189 | `tower-karina` | West out of the zone and down into the channeler Karina's line (the way to the east stairs runs past her): she battles | Pokémon Tower 5F 8,12 |  |
| 190 | `tower-6f` | East along 5F's south rooms (in no channeler's sight) to the stairs up to 6F | Pokémon Tower 6F 18,10 |  |
| 191 | `tower-jennifer` | Up 6F's east side into the channeler Jennifer's line (the way west crosses it): she battles | Pokémon Tower 6F 16,6 |  |
| 192 | `tower-emilia` | Round the north hall and down the middle room into the channeler Emilia's line (the way on to the west rooms crosses it): she battles | Pokémon Tower 6F 9,7 |  |
| 193 | `marowak-ghost` | Round the west rooms to the stairs up; the ghost blocks them: with the Silph Scope it's Cubone's mother, Marowak; beat it and its spirit is calmed | Pokémon Tower 6F 11,15 | `VAR_MAP_SCENE_POKEMON_TOWER_6F` 1 |
| 194 | `tower-7f` | Up the stairs to the top floor | Pokémon Tower 7F 11,16 |  |
| 195 | `tower-grunt1` | Up the hall into the first Rocket's line: he battles, then runs off | Pokémon Tower 7F 11,10 |  |
| 196 | `tower-grunt2` | On up into the second one's: he battles, then runs off | Pokémon Tower 7F 11,8 |  |
| 197 | `tower-grunt3` | And the third one's: he battles, then runs off | Pokémon Tower 7F 11,6 |  |
| 198 | `mr-fuji` | Up to Mr. Fuji: he thanks you and goes home, and you with him | Lavender Town Volunteer Pokémon House | `FLAG_RESCUED_MR_FUJI` set |
| 199 | `poke-flute` | Up to Mr. Fuji in his house: he gives you the Poké Flute | Lavender Town Volunteer Pokémon House | `FLAG_GOT_POKE_FLUTE` set |
| 200 | `fuji-house-out` | Out of Mr. Fuji's house | Lavender Town |  |
| 201 | `route12` | Down Lavender's south road onto Route 12 | Route 12 |  |
| 202 | `route12-gate` | Down Route 12's lane into its gatehouse | Route 12 North Entrance 1F 5,2 |  |
| 203 | `route12-bridge` | Through the gatehouse and out of its south door onto the bridge | Route 12 11,14 |  |
| 204 | `snorlax` | Down the Silence Bridge (its middle lane, past the fishers' lines) to the sleeping Snorlax; play the Poké Flute: it wakes and battles, and is gone | Route 12 17,47 | `FLAG_WOKE_UP_ROUTE_12_SNORLAX` set |
| 205 | `route13` | On down Route 12 (past where Snorlax slept, by the fishing house) onto Route 13 | Route 13 89,1 |  |
| 206 | `route14` | Down Route 13's coast road and west along it (round the birdkeepers and the beauties) onto Route 14 | Route 14 18,1 |  |
| 207 | `route14-tree` | Down Route 14 to the tree across its east lane; cut it and walk through | Route 14 19,17 |  |
| 208 | `route14-ledge` | On down the lane and west to the long ledge; hop it | Route 14 11,34 |  |
| 209 | `route15` | Down Route 14's south fields and west onto Route 15 | Route 15 78,15 |  |
| 210 | `route15-gate` | West along Route 15 (round the bikers' and beauties' lines) into its west gatehouse (along the south lane: the road's Volbeat and Illumise patrol it, and its Hoppip wander anywhere) | Route 15 West Entrance 1F |  |
| 211 | `route15-gate-out` | Through the gatehouse and out of its west door | Route 15 9,5 |  |
| 212 | `fuchsia` | West along the lane into Fuchsia | Fuchsia City 46,21 |  |
| 213 | `fuchsia-gym` | Across Fuchsia into Koga's Gym | Fuchsia City Gym |  |
| 214 | `koga` | Up the middle of the Gym (between the two jugglers' lines, along the invisible walls) into Koga's room; face him and beat him: the Soul Badge (Surf can be used outside battle) | Fuchsia City Gym 7,14 | `FLAG_BADGE05_GET` set |
| 215 | `leave-fuchsia-gym` | Back down and out of the Gym | Fuchsia City 5,32 |  |
| 216 | `safari-entrance` | Up Fuchsia's west lane (a tree to cut closes the middle one) and into the Safari Zone's gate | Fuchsia City Safari Zone Entrance |  |
| 217 | `safari-zone` | Up to the counter: pay ₽500 for 30 Safari Balls and go in | Safari Zone Center 26,30 |  |
| 218 | `safari-east` | Up the Centre's east side and out of its east gate into the East area | Safari Zone East 8,27 |  |
| 219 | `safari-north` | Round the East area's meadows and out of its north-west gate into the North area | Safari Zone North |  |
| 220 | `safari-west` | Across the North area (round its ponds) and down its south-west gate into the West area | Safari Zone West |  |
| 221 | `gold-teeth` | Down the West area to the item by the rocks: the Warden's Gold Teeth | Safari Zone West 28,15 | `FLAG_HIDE_SAFARI_ZONE_WEST_GOLD_TEETH` set |
| 222 | `secret-house` | West to the secret house in the corner | Safari Zone Secret House |  |
| 223 | `hm03` | Up to the man inside: for reaching it, HM03 (Surf) | Safari Zone Secret House | `FLAG_GOT_HM03` set |
| 224 | `secret-house-out` | Out of the secret house | Safari Zone West |  |
| 225 | `safari-back-north` | Back up the West area and out of its north gate into the North area | Safari Zone North |  |
| 226 | `safari-back-east` | Across the North area to its east gate and into the East area | Safari Zone East |  |
| 227 | `safari-back-centre` | Round the East area to its south-west gate and back into the Centre | Safari Zone Center |  |
| 228 | `safari-out` | Down the Centre and out to the gate | Fuchsia City Safari Zone Entrance |  |
| 229 | `safari-gate-out` | Down past the counter and out to Fuchsia (a reload in the Zone ended Safari mode, so the counter thinks you're coming in and asks again: no thanks) | Fuchsia City 23,7 |  |
| 230 | `wardens-house` | Down Fuchsia's west lane and along the south road into the Warden's house | Fuchsia City Wardens House |  |
| 231 | `hm04` | Give the Warden his Gold Teeth: he can talk again, and gives HM04 (Strength) | Fuchsia City Wardens House | `FLAG_GOT_HM04` set |
| 232 | `wardens-house-out` | Out of the Warden's house | Fuchsia City 31,32 |  |
| 233 | `fuchsia-east` | Up Fuchsia's east lane onto Route 15 | Route 15 |  |
| 234 | `route15-gate-east` | Into Route 15's west gatehouse | Route 15 West Entrance 1F |  |
| 235 | `route15-east` | Through it and out of its east door | Route 15 |  |
| 236 | `route14-back` | East along Route 15's south lane (off the road the Volbeat and Illumise patrol) onto Route 14 | Route 14 |  |
| 237 | `route14-tree-back` | Up Route 14's fields (round the ledges) to the tree on the east lane; cut it and walk through | Route 14 19,15 |  |
| 238 | `route13-back` | On up Route 14 onto Route 13 | Route 13 |  |
| 239 | `route12-back` | East along Route 13 (off every trainer's line) and up onto Route 12 | Route 12 |  |
| 240 | `route12-snorlax-spot` | Up Route 12 to where Snorlax slept, through it and west along the bank (the rocker Luca walks round there and may see you: then he battles) | Route 12 |  |
| 241 | `route12-north` | Up the Silence Bridge (its middle lane) to the gatehouse | Route 12 North Entrance 1F |  |
| 242 | `route12-gate-back` | Through the gatehouse and out of its north door | Route 12 |  |
| 243 | `lavender-again` | Up the lane into Lavender | Lavender Town |  |
| 244 | `route8-again` | West along Lavender's street onto Route 8 | Route 8 |  |
| 245 | `route8-gate` | West along Route 8 to Saffron's east gate | Route 8 West Entrance |  |
| 246 | `saffron-guard` | Past the guard: he's thirsty; give him the Tea and he lets you by | Route 8 West Entrance | `VAR_MAP_SCENE_ROUTE5_ROUTE6_ROUTE7_ROUTE8_GATES` 1 |
| 247 | `saffron` | On through the gate into Saffron (its exit mat's lower half) | Saffron City |  |
| 248 | `silph-co` | Across Saffron (the Rocket at Silph's door is asleep now Mr. Fuji is safe) into Silph Co. | Silph Co 1F |  |
| 249 | `silph-2f` | Up the hall to the stairs and up to 2F | Silph Co 2F 30,2 |  |
| 250 | `silph-3f` | Along to the next stairs and up to 3F | Silph Co 3F 28,2 |  |
| 251 | `silph-4f` | And up to 4F | Silph Co 4F 30,2 |  |
| 252 | `silph-5f` | And up to 5F | Silph Co 5F 28,2 |  |
| 253 | `silph-beau` | West along 5F's north hall past the scientist Beau, who walks about there (a door shuts the middle way and a Rocket the east one): if he sees you he battles | Silph Co 5F |  |
| 254 | `silph-9f-pad` | Down the west rooms to the pad by the bottom hall's door: it takes you up to 9F (a walk must never end on a pad: its checkpoint is saved before the pad takes you) | Silph Co 9F 22,18 |  |
| 255 | `silph-5f-grunt` | Off the pad and back on: it brings you down into 5F's bottom hall; step on into the Rocket's line by its door: he battles | Silph Co 5F 10,21 |  |
| 256 | `card-key` | East along the bottom hall to the Card Key | Silph Co 5F 21,21 | `FLAG_HIDE_SILPH_CO_5F_CARD_KEY` set |
| 257 | `silph-back-9f` | Back along the hall and up the pad to 9F | Silph Co 9F 22,18 |  |
| 258 | `silph-9f-door4` | Up to 9F's first locked door; the Card Key opens it | Silph Co 9F | `FLAG_SILPH_9F_DOOR_4` set |
| 259 | `silph-9f-door3` | Through it and up to the next; the Card Key opens it too | Silph Co 9F | `FLAG_SILPH_9F_DOOR_3` set |
| 260 | `silph-9f-grunt` | Round the north hall and down the west corridor into a Rocket's line: he battles | Silph Co 9F 15,15 |  |
| 261 | `silph-9f-door2` | The door to the west rooms: the Card Key opens it | Silph Co 9F | `FLAG_SILPH_9F_DOOR_2` set |
| 262 | `silph-9f-door1` | Through the west rooms to the last door: the Card Key opens it | Silph Co 9F | `FLAG_SILPH_9F_DOOR_1` set |
| 263 | `silph-9f-grunt2` | Through it into the line of the Rocket guarding the pad: he battles | Silph Co 9F |  |
| 264 | `silph-3f-pad` | Up the west side to the pad in the corner: it takes you down to 3F | Silph Co 3F 2,14 |  |
| 265 | `silph-3f-door` | East to 3F's locked door; the Card Key opens it | Silph Co 3F | `FLAG_SILPH_3F_DOOR_1` set |
| 266 | `silph-7f` | Through it to the pad in the middle room: it takes you up to 7F | Silph Co 7F 5,4 |  |
| 267 | `silph-rival` | West off the pad: the rival is waiting there; he battles, then leaves | Silph Co 7F 2,4 | `VAR_MAP_SCENE_SILPH_CO_7F` 1 |
| 268 | `silph-11f` | Round to the other pad: it takes you up to 11F | Silph Co 11F 2,5 |  |
| 269 | `silph-11f-grunt` | Down 11F's west side and east into the line of the Rocket at its foot: he battles | Silph Co 11F 2,18 |  |
| 270 | `silph-11f-door` | East to the locked door below the boardroom; the Card Key opens it | Silph Co 11F | `FLAG_SILPH_11F_DOOR` set |
| 271 | `giovanni-silph` | Up through it to Giovanni, who stops you: he battles, and Team Rocket leaves Silph Co. | Silph Co 11F 5,15 | `FLAG_HIDE_SAFFRON_ROCKETS` set, `VAR_MAP_SCENE_SILPH_CO_11F` 1 |
| 272 | `silph-back-7f` | Back up the west side to the pad: down to 7F (the boardroom side of 11F has no other way out) | Silph Co 7F 5,8 |  |
| 273 | `silph-back-3f` | Over to the other pad: down to 3F | Silph Co 3F 13,14 |  |
| 274 | `silph-3f-door2` | East to 3F's other locked door; the Card Key opens it | Silph Co 3F | `FLAG_SILPH_3F_DOOR_2` set |
| 275 | `silph-3f-grunt` | Through it and up the corridor into the line of the Rocket across it: he battles | Silph Co 3F 22,9 |  |
| 276 | `silph-down-2f` | Up to the north hall and down the stairs to 2F | Silph Co 2F |  |
| 277 | `silph-down-1f` | Down again to the lobby | Silph Co 1F |  |
| 278 | `silph-out` | Out of Silph Co. into Saffron, free of Rockets now | Saffron City |  |
| 279 | `saffron-gym` | Across Saffron to Sabrina's Gym | Saffron City Gym 14,23 |  |
| 280 | `gym-pad-se` | The Gym is nine rooms joined by teleport pads. The entrance room's pad goes to the south-east room | Saffron City Gym 28,23 |  |
| 281 | `gym-pad-ne` | Under the psychic's line to the room's west pad: to the north-east room | Saffron City Gym 28,4 |  |
| 282 | `gym-pad-nw` | Under that room's psychic to its south-west pad: to the north-west room | Saffron City Gym 0,4 |  |
| 283 | `gym-pad-centre` | Down the west wall to that room's south-west pad: into Sabrina's room | Saffron City Gym 18,15 |  |
| 284 | `sabrina` | Face Sabrina and beat her: the Marsh Badge and TM04 | Saffron City Gym 14,12 | `FLAG_BADGE06_GET` set, `FLAG_GOT_TM04_FROM_SABRINA` set |
| 285 | `gym-back-nw` | The pads back out: Sabrina's room's pad to the north-west room | Saffron City Gym 0,7 |  |
| 286 | `gym-back-ne` | Its north-west pad: to the north-east room | Saffron City Gym 20,7 |  |
| 287 | `gym-back-se` | Along under the psychic to the north-east pad: to the south-east room | Saffron City Gym 20,20 |  |
| 288 | `gym-back-entrance` | Under the psychic to the south-east pad: back to the entrance | Saffron City Gym 18,20 |  |
| 289 | `leave-saffron-gym` | Out of the Gym | Saffron City 17,18 |  |
| 290 | `saffron-south` | Down Saffron to its south gate (its guard drank the Tea too) | Route 6 North Entrance |  |
| 291 | `route6-again` | Through the gate and out onto Route 6 | Route 6 |  |
| 292 | `vermilion-again` | Down Route 6 into Vermilion | Vermilion City |  |
| 293 | `fan-club` | Up Vermilion's street into the Pokémon Fan Club | Vermilion City Pokémon Fan Club |  |
| 294 | `bike-voucher` | Round the table to the chairman; yes, you'd like to hear about his Pokémon: the Bike Voucher (he's talked to from his side: his chair is at another height from the floor behind him, so from above he doesn't answer) | Vermilion City Pokémon Fan Club | `FLAG_GOT_BIKE_VOUCHER` set |
| 295 | `leave-fan-club` | Back out of the Fan Club | Vermilion City 16,10 |  |
| 296 | `vermilion-tree` | Across Vermilion to the tree in front of the Gym's yard; cut it and walk through (in one step: a checkpoint's reload brings a cut tree back) | Vermilion City 15,16 |  |
| 297 | `vermilion-gym` | Through the yard into Lt. Surge's Gym | Vermilion City Gym |  |
| 298 | `surge-switches` | Along the bottom and up the west wall to trash can 6: the first switch. Up into Baily's line (he battles) to can 1: the second; the electric locks open | Vermilion City Gym 0,10 | `FLAG_FOUND_BOTH_VERMILION_GYM_SWITCHES` set |
| 299 | `lt-surge` | Along the top row into Tucker's line (he battles) and up through the opened beams to Lt. Surge; beat him: the Thunder Badge | Vermilion City Gym 5,3 | `FLAG_BADGE03_GET` set |
| 300 | `leave-vermilion-gym` | Back down through the beams and the west aisle and out of the Gym | Vermilion City 10,21 |  |
| 301 | `vermilion-tree-out` | Round the yard to the tree (grown back); cut it and walk out | Vermilion City 15,14 |  |
| 302 | `route6-north` | Up Vermilion's plaza onto Route 6 | Route 6 41,31 |  |
| 303 | `route6-hut-again` | Up Route 6's road into the Underground Path's hut | Underground Path South Entrance 13,12 |  |
| 304 | `tunnel-again` | Down the hut's stairs into the tunnel | Underground Path North South Tunnel 2,38 |  |
| 305 | `tunnel-north-again` | Along the tunnel and up its north stairs | Underground Path North Entrance 12,8 |  |
| 306 | `route5-again` | Out of the north hut onto Route 5 | Route 5 35,25 |  |
| 307 | `cerulean-again` | Up Route 5's road and through the neck into Cerulean | Cerulean City 22,50 |  |
| 308 | `bike-shop` | Into the Bike Shop | Cerulean City Bike Shop |  |
| 309 | `bicycle` | Up to the counter: the clerk takes the Bike Voucher for a Bicycle | Cerulean City Bike Shop | `FLAG_GOT_BICYCLE` set |
| 310 | `leave-bike-shop` | Back out of the Bike Shop (round the woman) | Cerulean City |  |
| 311 | `route5-south` | Back down through Cerulean's neck onto Route 5 | Route 5 |  |
| 312 | `saffron-north-gate` | Down Route 5's road into Saffron's north gate | Route 5 South Entrance |  |
| 313 | `saffron-from-north` | Through the gate into Saffron (its mat's east half: backlog #6) | Saffron City |  |
| 314 | `saffron-west-gate` | Down Saffron's avenue and up into its west gate (its doors face south) | Route 7 East Entrance |  |
| 315 | `route7-west` | Through the gate onto Route 7 | Route 7 |  |
| 316 | `celadon-west` | West along Route 7 into Celadon | Celadon City |  |
| 317 | `route16` | West along Celadon's boulevard onto Route 16 | Route 16 |  |
| 318 | `route16-snorlax` | West to the sleeping Snorlax in the gap; play the Poké Flute: it wakes and battles, and is gone | Route 16 45,24 | `FLAG_HIDE_ROUTE_16_SNORLAX` set |
| 319 | `cycling-road` | Get on the Bicycle, ride west through the Cycling Road gatehouse's lower hall (the guard lets bikes by) and out of its west door onto Cycling Road (in one step: indoors, a checkpoint's reload puts you back on foot) | Route 16 28,24 | `VAR_MAP_SCENE_ROUTE16` 1 |
| 320 | `route17` | Down Route 16's west side between the bikers' lines onto Route 17 | Route 17 |  |
| 321 | `route18` | Down the whole of Cycling Road onto Route 18: its slope carries you down; Jamal sees you on the way and battles (only A while you ride: a key held when a battle starts moves its menu) | Route 18 |  |
| 322 | `route18-gate` | Ride up the shore and east along Route 18's road into its gatehouse, through it and out of its east door, and on into Fuchsia | Fuchsia City |  |
| 323 | `route19` | Down through Fuchsia's west walks and south road onto Route 19 | Route 19 12,1 |  |
| 324 | `route19-surf` | Down between the swimmers' lines to the beach; Surf from it (the Soul Badge lets Surf be used outside battle) | Route 19 11,16 |  |
| 325 | `route20` | Surf south-west round the swimmers' lines onto Route 20 | Route 20 |  |
| 326 | `cinnabar` | West along Route 20, over the top of the Seafoam Islands, to Cinnabar Island | Cinnabar Island |  |
| 327 | `cinnabar-shore` | Round the north of the island's east half to the town's shore, and ashore | Cinnabar Island 22,6 |  |
| 328 | `mansion` | Along the top street into the Pokémon Mansion (the Gym next door is locked) | Pokémon Mansion 1F |  |
| 329 | `mansion-2f` | Up the hall to the stairs and up to 2F | Pokémon Mansion 2F 6,14 |  |
| 330 | `mansion-3f` | Round 2F's halls (off Arnie's line) to the north stairs and up to 3F | Pokémon Mansion 3F 8,3 |  |
| 331 | `mansion-3f-statue` | Down to the statue in 3F's west room; press its secret switch: the barriers change on every floor | Pokémon Mansion 3F | `FLAG_POKEMON_MANSION_SWITCH_STATE` set |
| 332 | `mansion-hole` | Through the opened way east and down through the hole in the floor to 1F | Pokémon Mansion 1F |  |
| 333 | `mansion-b1f` | Round 1F's south rooms to the stairs down to the basement | Pokémon Mansion B1F 34,29 |  |
| 334 | `mansion-lewis` | Up B1F's east side and west along the north hall, then down through the way the switch opened, where the burglar Lewis wanders: if he sees you he battles | Pokémon Mansion B1F |  |
| 335 | `mansion-b1f-statue` | Round the table to the statue below it; press its switch: back as it was | Pokémon Mansion B1F 24,30 | `FLAG_POKEMON_MANSION_SWITCH_STATE` not set |
| 336 | `mansion-b1f-statue2` | West, up the west hall, east along the middle and up the east side to the statue in the north-east room; press its switch again | Pokémon Mansion B1F 27,6 | `FLAG_POKEMON_MANSION_SWITCH_STATE` set |
| 337 | `secret-key` | Back along the middle hall and through the opened way into the west room: the Secret Key | Pokémon Mansion B1F 5,6 | `FLAG_HIDE_POKEMON_MANSION_B1F_SECRET_KEY` set |
| 338 | `mansion-west-out` | Out of the west room the way you came | Pokémon Mansion B1F 13,10 |  |
| 339 | `mansion-out-statue` | Back to the north-east statue; press the switch | Pokémon Mansion B1F | `FLAG_POKEMON_MANSION_SWITCH_STATE` not set |
| 340 | `mansion-out-statue2` | Down the east side (beside Ivan's line) and round to the statue below the table; press it again | Pokémon Mansion B1F 24,30 | `FLAG_POKEMON_MANSION_SWITCH_STATE` set |
| 341 | `mansion-out-lewis` | Up past the table and through the opened way, where Lewis wanders: if he sees you he battles | Pokémon Mansion B1F |  |
| 342 | `mansion-up` | East along the north hall and down to the stairs; up to 1F | Pokémon Mansion 1F |  |
| 343 | `mansion-out` | Through 1F's east rooms (the switch has their barriers open) and out of the back door | Cinnabar Island |  |
| 344 | `cinnabar-gym` | Along to the Gym: the Secret Key opens its door | Cinnabar Island Gym |  |
| 345 | `gym-quiz1` | Up into the east room to its quiz machine: Caterpie evolves into Metapod? Yes | Cinnabar Island Gym 22,11 | `FLAG_CINNABAR_GYM_QUIZ_1` set |
| 346 | `gym-door1` | Round Quinn and up through the opened door into the north-east room | Cinnabar Island Gym 26,7 |  |
| 347 | `gym-quiz2` | Along the room's north side to its machine: there are nine certified League Badges? No | Cinnabar Island Gym 15,3 | `FLAG_CINNABAR_GYM_QUIZ_2` set |
| 348 | `gym-door2` | Down past Avery and through the door into the middle room | Cinnabar Island Gym 17,11 |  |
| 349 | `gym-quiz3` | Round Ramon to the room's machine: Poliwag evolves three times? No | Cinnabar Island Gym 13,11 | `FLAG_CINNABAR_GYM_QUIZ_3` set |
| 350 | `gym-door3` | Through the door south into the south room | Cinnabar Island Gym 17,18 |  |
| 351 | `gym-quiz4` | Round Derek to the machine: are electric moves effective against ground types? No | Cinnabar Island Gym 14,18 | `FLAG_CINNABAR_GYM_QUIZ_4` set |
| 352 | `gym-door4` | Through the door west into the south-west room | Cinnabar Island Gym 10,22 |  |
| 353 | `gym-quiz5` | Round Dusty to the machine: Pokémon of the same kind and level are not identical? Yes | Cinnabar Island Gym 2,19 | `FLAG_CINNABAR_GYM_QUIZ_5` set |
| 354 | `gym-door5` | Below Dusty and up through the door into the west room | Cinnabar Island Gym 5,15 |  |
| 355 | `gym-quiz6` | Up the room's west side to the machine: TM28 contains Tombstony? No | Cinnabar Island Gym 2,11 | `FLAG_CINNABAR_GYM_QUIZ_6` set |
| 356 | `gym-door6` | Below Zac and up through the last door into Blaine's room | Cinnabar Island Gym 5,7 |  |
| 357 | `blaine` | Up to Blaine; beat him: the Volcano Badge and TM38 | Cinnabar Island Gym 5,5 | `FLAG_BADGE07_GET` set, `FLAG_GOT_TM38_FROM_BLAINE` set |
| 358 | `gym-out` | Back out through the opened doors: down the west side and east along the south rooms, then up the middle (past Derek and Ramon) into the north room | Cinnabar Island Gym 17,7 |  |
| 359 | `gym-out2` | Round Avery and Erik and down the east side through the first door to the entrance | Cinnabar Island Gym 26,22 |  |
| 360 | `bill-cinnabar` | Out of the Gym: Bill is waiting and asks you to come to One Island with him. Say no (the Sevii Islands aren't part of this check): he waits in the Pokémon Center | Cinnabar Island | `VAR_MAP_SCENE_CINNABAR_ISLAND` 2 |
| 361 | `cinnabar-surf` | West along the top street to the shore; Surf | Cinnabar Island 2,5 |  |
| 362 | `route21-south` | North up the island's west side onto Route 21 | Route 21 South |  |
| 363 | `route21-north` | Straight up the west side of Route 21 (off the swimmers' lines) | Route 21 North |  |
| 364 | `pallet-again` | On up, then east into the channel between the fields and up it into Pallet Town | Pallet Town |  |
| 365 | `pallet-shore` | Up Pallet's pond and ashore by the lab | Pallet Town 15,20 |  |
| 366 | `route1-again` | Up through Pallet onto Route 1 | Route 1 |  |
| 367 | `viridian-again` | Up Route 1 into Viridian | Viridian City |  |
| 368 | `viridian-gym` | Across Viridian to the Gym: with seven badges its door is open now (the walk stops a block short: the block before the door runs the locked-door scene, which a checkpoint would cut off) | Viridian City Gym | `VAR_MAP_SCENE_VIRIDIAN_CITY_GYM_DOOR` 1 |
| 369 | `viridian-gym-warren` | Across the spin tiles to the north-east and up into Warren's line: he battles | Viridian City Gym 15,7 |  |
| 370 | `viridian-gym-takashi` | Round Warren and west along the hall into Takashi's line: he battles | Viridian City Gym 10,5 |  |
| 371 | `giovanni` | Round to Giovanni in the north-west room; beat him: the Earth Badge, and Team Rocket is finished | Viridian City Gym 2,3 | `FLAG_BADGE08_GET` set, `VAR_MAP_SCENE_ROUTE22` 3 |
| 372 | `leave-viridian-gym` | Back across the spin tiles and out of the Gym (no tap to turn first: a checkpoint's reload leaves you facing down already, and a tap that way is a step) | Viridian City 44,21 |  |
| 373 | `route22-again` | West along Viridian's street onto Route 22 | Route 22 51,7 |  |
| 374 | `route22-rival` | West along the road: the rival comes after you for one last battle before the League | Route 22 | `VAR_MAP_SCENE_ROUTE22` 4 |
| 375 | `league-gate-again` | Round Route 22's ponds to the League Front Gate | Route 22 North Entrance |  |
| 376 | `boulder-badge-gate` | Up the gatehouse: the guard checks the Boulder Badge; on out of its north door onto Route 23 | Route 23 | `VAR_MAP_SCENE_ROUTE23` 1 |
| 377 | `cascade-badge-gate` | Up the road to the Cascade Badge's gate: the guard checks it and lets you by | Route 23 | `VAR_MAP_SCENE_ROUTE23` 2 |
| 378 | `thunder-badge-gate` | Up the road to the Thunder Badge's gate: the guard checks it and lets you by | Route 23 | `VAR_MAP_SCENE_ROUTE23` 3 |
| 379 | `rainbow-badge-gate` | Up the road to the Rainbow Badge's gate: the guard checks it and lets you by | Route 23 | `VAR_MAP_SCENE_ROUTE23` 4 |
| 380 | `soul-badge-gate` | Up the road to the Soul Badge's gate: the guard checks it and lets you by | Route 23 | `VAR_MAP_SCENE_ROUTE23` 5 |
| 381 | `route23-lake` | Up to the lake's shore; Surf | Route 23 9,79 |  |
| 382 | `route23-lake-north` | Across the lake and ashore | Route 23 9,65 |  |
| 383 | `marsh-badge-gate` | Up the road to the Marsh Badge's gate: the guard checks it and lets you by | Route 23 | `VAR_MAP_SCENE_ROUTE23` 6 |
| 384 | `volcano-badge-gate` | Up the road to the Volcano Badge's gate: the guard checks it and lets you by | Route 23 | `VAR_MAP_SCENE_ROUTE23` 7 |
| 385 | `earth-badge-gate` | Up the road to the Earth Badge's gate: the guard checks it and lets you by | Route 23 | `VAR_MAP_SCENE_ROUTE23` 8 |
| 386 | `victory-road` | Into the yard under the cliff and into Victory Road | Victory Road 1F |  |
| 387 | `vr1f-boulder` | Victory Road 1F: round the first boulder to stand above it | Victory Road 1F 7,17 |  |
| 388 | `vr1f-switch` | Strength: the boulder down, along and up onto the floor switch; the rock barrier opens | Victory Road 1F | `VAR_MAP_SCENE_VICTORY_ROAD_1F` 100 |
| 389 | `vr2f` | Round the boulder (back where it started: the switch stays down) and through the opened barrier, under Naomi's and Rolando's lines and up the ladder | Victory Road 2F 1,10 |  |
| 390 | `vr2f-switch` | 2F: Strength, the boulder down onto the west floor switch; its barrier opens | Victory Road 2F | `VAR_MAP_SCENE_VICTORY_ROAD_2F_BOULDER1` 100 |
| 391 | `vr3f` | Round the boulder (back where it started) through the barrier, east across 2F under Daisuke and behind Nelson, and up the ladder to 3F | Victory Road 3F 34,10 |  |
| 392 | `vr3f-switch` | 3F: Strength, the north boulder up, west along the top and down onto the floor switch; the barrier on the west side opens | Victory Road 3F | `VAR_MAP_SCENE_VICTORY_ROAD_3F` 100 |
| 393 | `vr3f-hole` | Round the top and the west side through the opened barrier, east along the south (under Colby's and Caroline's lines) to the boulder by the hole; Strength, and it falls in, to 2F | Victory Road 3F | `FLAG_HIDE_VICTORY_ROAD_2F_BOULDER` not set, `FLAG_HIDE_VICTORY_ROAD_3F_BOULDER` set |
| 394 | `vr2f-switch2` | Down the hole after it, then Strength and the boulder 19 blocks west onto the second switch; the barrier by the east ladder opens | Victory Road 2F | `VAR_MAP_SCENE_VICTORY_ROAD_2F_BOULDER2` 100 |
| 395 | `vr3f-east` | Round the wandering Pokémon and the boulder (back by the hole's foot), through the second barrier behind Nelson and up the east ladder to 3F | Victory Road 3F 39,16 |  |
| 396 | `vr2f-east` | Across 3F's east side under Tyra's line and down the ladder to 2F's far side | Victory Road 2F 38,10 |  |
| 397 | `victory-road-out` | Out of Victory Road onto Route 23's top yard | Route 23 |  |
| 398 | `indigo-plateau` | Up Route 23's last stretch to the Indigo Plateau | Indigo Plateau Exterior |  |
| 399 | `indigo-center` | Into the Indigo Plateau's Pokémon Center (the League's doors: the end of the check) | Indigo Plateau Pokémon Center 1F |  |

## What it doesn't cover

* **Two things are set up, not played.** Every play has a Repel on. For step 28 the team is replaced with a
  level 40 Pikachu that knows Thunderbolt, so Blue can be beaten without training first.
* **Battles other than the story ones.** There are no wild battles (the Repel), and trainers the walk can go round
  aren't fought.
* **People.** Only the story's people are checked. The second run of 2026-10-22 also talked to ten others on
  Pallet, Route 1, Viridian and Route 22. Nine answered; the tenth is hidden in the game on purpose. The script
  doesn't do that.
* **Places off the story's path**: houses, the Trainer School, the Gym (locked), Route 2's eastern detour (it needs
  Cut: the replay tests cut a tree and go through its buildings' doors), surfing.
* **Mt. Moon's other trainers**: the walk goes round the first floor's seven and two of the second basement's Rockets
  (it fights the two in its way, and Miguel). The Dome Fossil (it takes the Helix), the items and Mt. Moon's other
  ladders aren't played.
* **Cerulean's other events**: the Rocket in the robbed house's backyard, its hole, the badge house, the Bike Shop,
  the Gym, the lass and her Slowbro in the neck, the tree to cut, the cave on its island: the replay tests play them.
  The walk heals in the Center and goes on up Nugget Bridge.
* **Route 24 off the bridge**: the west shore (the TM, the hidden berry, Shane, the Abra grass) and the east meadow
  (the shelter's traveler and his Charmander) are reached from Route 25; the replay tests play them. The traveler's
  gift isn't checked: it needs the Friends' story state.
* **Route 25 off the road**: its seven other trainers (the walk keeps out of their sight), the garden behind the tree
  to cut (TM43, the hidden Ether), the trail below and its ledges, the lookout, the other hidden items: the replay
  tests play them.
* **Route 5's Day Care and Saffron's gate**: the walk goes past them; the replay tests go in at their doors. The
  gate's guard wants a drink, which comes later in the story.
* **Route 6's trainers**: the road is in no one's sight; their battles are in the replay tests.
* **Vermilion's other events**: the Gym behind its tree to cut, the Fan Club, the houses, the signs, Officer Jenny and
  the Squirtles, the old man's Machop, Oak's aide, the hidden Max Ether, the ticket check without a ticket: the
  replay tests play them. The Friends' camp (30,19) isn't played (see KR-6). The S.S. Anne itself is next.
* **Route 3's trainers.** The walk keeps below their lines of sight (they're optional); their battles are in the replay
  tests.
* **Viridian Forest's other trainers.** Rick and Doug can't be walked round, so their battles are played (with the
  Pikachu from `blue-win`); Sammy, Anthony and Charlie are on the item branches, which the walk doesn't take.
* **Past Celadon the team is set again, not trained.** From `celadon-gym-tree` it is one Alakazam at level 100 that
  knows Psychic, Surf, Cut and Strength, and every step with a battle sets it again first (healed, its moves' PP
  back: Psychic's ten ran out in the Rocket Hideout). The check past Celadon is about the maps and the scenes. The
  walks there were planned on the maps, off every trainer's line of sight and off anywhere a wandering one can
  stand and see, sliding on the Hideout's spin tiles and hopping ledges; trainers who can't be walked round are
  fought (the Hideout's grunts in the way, the Tower's channelers in the way and its 7F Rockets).
* **The Safari Zone's ticket.** A checkpoint's reload ends Safari mode, as loading a save does (the game clears it
  then), so past the gate the steps check the paths, not the 600 steps or the balls (the walk is about 270 steps,
  inside one ticket). On the way out the counter thinks you're coming in and asks again; the step says no.
* **Off the story's path past Celadon**: the Celadon Department Store and the other houses; the Hideout's and the
  Tower's items (but the Hideout's Moon Stone, which stands in the way down to the lift); the Hideout's other
  grunts where the walk goes round them; Route 12's fishing house and the trees to cut beside it; Routes 13–15's
  trainers (the walks keep out of their sight); Fuchsia's houses, the Safari Zone's Rest Houses and items (but the
  Gold Teeth); the Warden's boulder.
* **Silph Co. off the story's path**: the walk takes the floors the Card Key and the pads need (1F–5F by the stairs,
  then 9F, 3F, 7F and 11F by pads). Its other floors (6F, 8F, 10F), the lift, the Lapras on 7F, the items, the
  Master Ball from the president and the trainers the walk goes round aren't played. Saffron's Dojo isn't played.
* **Sabrina's Gym's trainers**: the walk takes the four pads that lead to Sabrina and back, under every psychic's
  line of sight.
* **The way to Cinnabar.** Without Fly the check goes there by sea: from Saffron down Routes 6 and 11 and round by
  Routes 12–15 to Fuchsia (the walks over Routes 13–15 are the ones from before), Surf down Route 19 and along Route
  20, and back north by Route 21 to Pallet. The Seafoam Islands, the Pokémon Lab and its fossils, Cinnabar's
  Center and Mart, and the Friends' place on the island's east half aren't played.
* **The Pokémon Mansion off the story's path**: its items (but the Secret Key), its diaries, and its trainers but
  Lewis, whose corridor can't be walked round (he wanders, so he may or may not battle). The walks keep off every
  other line of sight.
* **Blaine's Gym's trainers**: every quiz is answered right, so none of them battles.
* **The Sevii Islands.** Bill asks you to come to One Island; the check says no.
* **Lt. Surge on the way back.** The check first leaves Vermilion on the S.S. Anne's errand and comes back for the
  Thunder Badge after Saffron (Viridian's Gym door wants all seven). The Fan Club's other members, the Bike Shop's
  others and the Vermilion Gym's trainers other than Baily and Tucker (in the walk's way) aren't played.
* **Back to Fuchsia by Cycling Road**: the check takes the Bicycle from Cerulean and rides Routes 16 to 18. Route 16's
  house (HM02 Fly: the check never flies) and north side, and Routes 17's and 18's trainers but Jamal (he sees the
  ride) aren't played. Routes 11–15 are played once, on the way to Fuchsia the first time.
* **The Viridian Gym's other trainers**: the walk takes the arrow tiles to Warren and Takashi, who are in its way, and
  Giovanni. Route 22's second rival battle is played.
* **Victory Road off the story's path**: its trainers (the walks keep off their lines), items, the Double-Edge tutor
  and its boulders the switches don't need. Its four floor switches are played (1F, 2F's two, 3F's: the 3F one opens
  the way to the boulder that drops through to 2F).
* **The League.** The check ends in the Indigo Plateau's Pokémon Center: the Elite Four's rooms are FireRed's own
  and aren't part of the rebuild. League West Pass (Johto's way) isn't played.
* **The menus** (bag, Pokédex, Town Map, saving): only opened where the story opens them.
* **Real play**: sound, real-time play, real hardware.

## Adding to it when a map is rebuilt

1. Run it from the first step the change affects (see "Carrying on after a change").
2. Add steps for the new map's story events to `STEPS` in `project/scripts/story_check.py`. Each step has a
   `walk` target, `inputs` and an `expect`: the map, block, and flags and variables. To find them:
   * `pae map events MAP` lists the triggers and people.
   * The map's `scripts.inc` shows which flags and variables a scene sets.
   * `pae play --from CHECKPOINT --inputs ... --show-flag F --show-var V` tries a step out before you add it.
   * A walk that must keep off some blocks (a trainer's line of sight) gives them `via`: blocks to walk to first, in
     order. `pae map path` keeps off sideways stairs (they move you diagonally), so a step that crosses them walks
     to their foot and crosses them in its inputs.
   * A trainer you can't walk round: walk to the block before their line of sight, then step in and fight in the
     inputs (A through the battle, then B to close the trainer's words if an A talked to them again:
     `forest-rick`).
   * In inputs, text advances with B (A talks to the person again). Leaving through a door mat needs one more press
     toward the exit while standing on it.
   * A walk must never end on a warp pad, stairs or a door: the checkpoint is saved before the warp fires, so the next
     step would start somewhere the game never puts you. Walk to the block before it and step on in the inputs.
     Stairs inside buildings need one more press sideways (Silph Co.: 1F and 3F up are RIGHT, 2F and 4F up LEFT).
   * A step with `surf` walks on water: the walk holds 8 frames a block (surfing is twice as fast) and taps first
     to turn (on water a short press only turns you; a play starts facing down). Surf from the shore in the inputs
     (face the water, then A through the question).
   * `pae map path` plans on a map as it was built. Where a script has opened a way since (the Mansion's switch, the
     Cinnabar Gym's doors), walk inside the open part and hold the keys through the opened blocks in the inputs.
   * Step names must differ: `--from` and the checkpoints go by name, and the script stops if two are the same.
   * A walk must never end on a coord trigger (a scene's block) either: the checkpoint is saved as the scene starts
     and its reload drops the scene, so the next step plays on as if it never happened (a walk that ended on the
     Viridian Gym's lock walked straight past it). Walk to the block before and step on in the inputs.
   * A checkpoint's reload is like flying in: you face down, and it drops temporary flags, Strength, scripts under way
     and the Bicycle (indoors, or when the step sets any `state`); cut trees and Strength boulders are back where the
     map puts them (a boulder on a floor switch too: the switch stays down). So cutting and walking through, getting on
     the Bicycle and riding, and a whole boulder puzzle are each one step. Ridden steps set `repel=False` (no state at
     all, not even the Repel) and `bike=True` (6 frames a block). Cycling Road slopes down: idle on it, you slide
     south; and a key held when a battle starts moves the battle menu's cursor, so the ride presses only A.
   * The Vermilion Gym's trash cans are shuffled each time the Gym loads (a reload, and each `state` reloads it
     again), so its step has no walk: it plays from its own checkpoint with its own state, and the cans it opens
     (6, then 1) are the ones that shuffle gives.
   * A trainer who wanders can see a walk and battle: the game can't be saved in a battle, so the walk is played on
     through it (A, then B) and planned again from where it left you.
   * Strength: `pushes("D! D L ...", waits)` turns a plan into inputs (`!` is a push; a push moves only the boulder,
     you stay where you are). It uses Strength before the first push. Plan the moves on the map (each push needs the
     block beyond the boulder free and off every trainer's line). Pokémon that wander can stand in the way:
     `project/scripts/strength_waits.py` plays the plan from the step's checkpoint a move at a time and finds the
     waits it needs, `{move number: frames}`. They depend on the checkpoint: after a change to any earlier step, run
     it again for each boulder step.
   * The script's walks plan with plain `pae map path`, which goes through people, boulders and trainers' lines of
     sight. Where a walk goes past one, give it vias round them (a boulder is back where the map puts it after a
     reload). To find the vias, `pae map path MAP X,Y X,Y --avoid-objects --avoid-sight` (pae PR #35) plans round
     them all; its turns are the vias.
3. When every step passes, update "Last validated point" and the step table on this page. Do it in the same pull
   request as the map change.
4. A failed step is a finding. Fix it if it stops the story. If it doesn't, add it to
   [the quality-of-life backlog](quality-of-life-backlog.md).

## History

| Date | Game | Result |
|---|---|---|
| 2026-10-22 | `v2-main` after PR #19 | **Stopped at step 3.** The lab battle reset the game, and so did the old man's demonstration. Fixed in PR #21 (a larger heap). |
| 2026-10-22 | `v2-main` `a74a9989` | **All 29 steps pass**, first by hand with the same inputs, then with `story_check.py`: from the top in one run (19 minutes), and resumed `--from south-pallet`. |
| 2026-10-22 | the broadleaf trees on every kit map | **All 29 steps pass** from the top (1098 s). |
| 2026-10-22 | the standalone trees' crowns walkable | **All 29 steps pass**: 1–11 from the top, then (after the machine restarted) `--from into-lab` (705 s). |
| 2026-10-22 | the broadleaf bushes | **All 29 steps pass** from the top (1089 s). |
| 2026-10-22 | the field rocks | **All 29 steps pass** from the top (1081 s). |
| 2026-10-23 | Pallet's new houses | **All 29 steps pass** from the top (1078 s). |
| 2026-10-23 | the new Pokémon Center and Poké Mart | **All 29 steps pass** from the top (1078 s). |
| 2026-10-23 | Viridian's houses' new roofs | **All 29 steps pass** from the top (1073 s). |
| 2026-10-23 | Route 2 rebuilt; nine new steps through it and Viridian Forest to Pewter | **All 38 steps pass** from the top (2068 s). The first try of the forest stopped at its sideways stairs: pae's walks crossed them, and the game doesn't (fixed in pae PR #19; the step crosses them in its inputs). |
| 2026-10-25 | the Viridian stranger fix (`4f402853`) | **Steps 7–38 pass** `--from viridian`, resumed from step 6's checkpoint (1800 s); steps 1–6 don't reach Viridian. |
| 2026-10-25 | the faster map crossings (seam lookups by table) | First run from the top: steps 1–21 passed, step 22 walked a block too far. With crossings no longer freezing and no frame lost per block, the old holds (`16 * n + 2` frames) walked one block more; `story_check.py` now holds `16 * (n - 1) + 12`. With step 22's hold fixed, **steps 22–38 pass** `--from back-viridian` (1136 s; steps 1–21 took 836 s). |
| 2026-10-25 | the one-frame graphics switch at crossings | **All 38 steps pass** from the top (1914 s). |
| 2026-10-25 | Viridian Forest rebuilt from the concept (48×60); the forest's three steps become four | **Steps 34–39 pass** `--from forest`, resumed from step 33's checkpoint (395 s). Rick and Doug can't be walked round now, so the walk battles them. Steps 1–33 weren't run on this build (the kit maps were rebuilt with the same blocks; their replay tests pass). |
| 2026-10-26 | Pewter City rebuilt (its own concept); two new steps, the Gym guide's walk to the Gym and into it | **Steps 39–41 pass** `--from pewter`, resumed from step 38's checkpoint (26 s). Steps 1–38 weren't run on this build (Pewter changes nothing before step 39). |
| 2026-10-26 | Route 3 rebuilt (its own concept); six new steps: Liam and Brock in Pewter's Gym, the Running Shoes, across Route 3 to Route 4 | **Steps 41–47 pass** `--from pewter-gym`, resumed from step 40's checkpoint (about 2 min). The first try stopped in the Gym: Liam saw the walk up its middle; the steps now fight him, then Brock, with a Wartortle given on entering the Gym (Pikachu's Thunderbolt doesn't touch rock types). |
| 2026-10-26 | Route 4 and Cerulean City rebuilt (their own concepts); twelve new steps: Mt. Moon's three floors, out onto Route 4's shelf, down into Cerulean, Blue | **Steps 47–59 pass**, `--from route3-north` and resumed from each failed step's predecessor (about 12 min in all). First tries stopped: on Mt. Moon 1F a lass saw the walk (the walk now goes round every line of sight, by via blocks worked out on the map), it stepped over another ladder, and the checkpoint was saved before a ladder's fade (the steps now walk to the block before the ladder and step on); on B2F pae read the map without its block fixes and planned through rock and up a one-way edge (pae PR #24 fixes both), two Rockets can't be walked round (the steps fight them), Miguel's and Blue's battles needed more presses, and the policeman stood in the street's top row (the walk takes the other). |
| 2026-10-26 | Route 24 rebuilt (its own concept); eleven new steps: a heal in Cerulean's Center, Nugget Bridge's five trainers and the Rocket, Route 25 | **Steps 60–70 pass**, `--from cerulean-rival` and resumed from each failed step's predecessor. First tries stopped: the trainers' battles needed more presses, the Wartortle blacked out against the fifth (the steps now heal in Cerulean first), and the Rocket's battle ends with the Wartortle evolving, which the step now waits out before his last message sets the scene. |
| 2026-10-26 | Route 25 rebuilt (its own concept); six new steps: Joey's and Wayne's necks, the Sea Cottage, Bill and his PC, the S.S. Ticket, out again | **Steps 70–76 pass**, `--from route25` on the final build. First tries stopped: pae couldn't plan a walk in the cottage (its block fixes use metatiles the game makes itself: pae PR #27), the checkpoint between helping Bill and his PC forgot that he was in his teleporter (a temporary flag: the two are one step now), Bill stands at 7,5 after a checkpoint (the step talks to him from below), and the cottage's mat needs a second press to leave. |
| 2026-10-26 | Route 5 rebuilt (its own concept); four new steps: back from Bill over the bridge, through Cerulean's neck, down Route 5 into the Underground Path's hut | **Steps 77–80 pass**, `--from back-to-bridge` on this build. The first try stopped on Route 25: going back along the road, Nob saw the walk (the walk now goes round the north of his and Flint's sight, as it came). |
| 2026-10-26 | Route 6 rebuilt (its own concept); four new steps: the Underground Path's tunnel, Route 6, Vermilion | **Steps 81–84 pass**, `--from tunnel` on this build. The first try stood on the hut's stairs without going down: they are arrow warps you walk east off (the steps do now, and at the tunnel's south end). |
| 2026-10-26 | Vermilion City rebuilt (its own concept); four new steps: its Center (in, heal, out) and the pier onto the S.S. Anne | **Steps 85–88 pass**, `--from vermilion-center` on this build, first try. |
| 2026-10-26 | Route 11 rebuilt (its own concept); four new steps before the S.S. Anne: east onto Route 11, into its gatehouse, out again, back to Vermilion | **Steps 88–92 pass**, `--from route11` and resumed from the failed step's predecessor. The first try stood inside the gatehouse: its doors inside are on its west and east walls, which you walk west or east off (the step now walks west). |
| 2026-10-26 | No map changes: eighteen new steps through the S.S. Anne (Blue, HM01), off the ship, back to Cerulean and through Misty's Gym, so the check can reach Route 9 with Cut | **Steps 93–110 pass**, `--from ss-anne-board` and resumed from each failed step's predecessor (93–97 on the Route 11 build, 98–110 on #47's). First tries stopped: on arrow warps and stairs entered by the wrong key (the gangway's end, the office's stairs, both ends of the ship's and the tunnel's stairs, the Gym's mat); in the ship's corridors, where a worker and a wandering sailor stood in the walk (vias go round them); in Vermilion, where the walk went into the Mart (pae plans across door blocks: KR-43; a via keeps to the plaza's middle); after Misty, before her scenes had finished (more presses). The ship's sailing landed you below the map until #47 fixed it. |
| 2026-10-26 | Routes 9 and 10 rebuilt (their own concepts); eight new steps: onto Route 9, the tree cut and the gorge's two trainers, Route 10, its Center, into Rock Tunnel | **Steps 111–118 pass**, `--from route9` and resumed from the failed step's predecessor. First tries stopped on Route 9: the tree to cut was gone (the game hides one within 8 blocks of the edge you come in by: KR-45, so it moved further in), then Alicia's battle never ended: the Blastoise's Water Gun had run down, and with the Bulbasaur given for Cut, A presses answered YES to "change Pokémon?" and went round the party menu (KR-48; one Kingler with Surf and Cut is the team now). |
| 2026-10-26 | No map changes: fifteen new steps through Rock Tunnel (its two floors, nine trainers) and down Route 10 into Lavender, so Lavender's rebuild can carry on from it | **Steps 112–133 pass**, `--from route9-alicia` and resumed from each failed step's predecessor. First tries stopped in battles that never ended: a Slowpoke Disabled the Kingler's only attack (A presses then go round the move menu; the Kingler is now level 65, so it knocks out what it meets first), and Surf's 15 PP ran out twice in the tunnel, which has no Center (the Kingler is given again at its two ladders up). The tunnel's walks were planned with the fewest battles their trainers' lines allow (KR-48). |
| 2026-10-26 | Lavender Town rebuilt (its own concept); four new steps: its Center (in, heal, out) and west onto Route 8 | **Steps 133–137 pass**, `--from lavender` on this build, first try. |
| 2026-10-26 | Route 8 rebuilt (its own concept); step 137 lands at its new edge, and four new steps: its road into the Underground Path's hut, the tunnel under Saffron, out onto Route 7 | **Steps 137–141 pass**, `--from route8` on this build. First tries stood on the tunnel's stairs: both are walked west off (the north-south tunnel's are walked east off). |
| 2026-10-26 | Route 7 rebuilt (its own concept); step 141 lands at the hut's door on the new map, and one new step west into Celadon | **Steps 141–142 pass**, `--from route7` on this build, first try. |
| 2026-10-26 | Celadon rebuilt (its own concept); step 142 lands on the new boulevard, and three new steps: its Center (in, heal, out) | **Steps 142–145 pass**, `--from celadon` on this build, first try. |
| 2026-10-27 | `v2-main` `c13b5ab1`, every Kanto map rebuilt; no map changes: a hundred and two new steps from Celadon to Saffron's gate (Erika, the Game Corner and the Rocket Hideout, Giovanni and the Silph Scope, the Pokémon Tower and Mr. Fuji, the Poké Flute, the Tea, Snorlax, Routes 12–15, Fuchsia and Koga, the Safari Zone and HM03, the Warden and HM04, back north the long way to Saffron's east gate) | Steps 1–145 pass from the top (2756 s, pae `2838353`); **steps 1–196 pass from the top** on pae `ea6b4bb` (3323 s), and 172–247 on from there. First tries stopped where the walks met FireRed's own interiors: pae read their tiles as having no behaviour, so its walks crossed the Hideout's spin tiles (pae PR #32); a `pae play` beside the running check loaded its scratch save (pae PR #33); Psychic's PP ran out in the Hideout (the team is set again before each battle); stairs, gate and lift mats that leave from one block only, or by a key sideways (backlog #6); a Hoppip and the Volbeat on Route 15's road (backlog #4: range-0 wanderers); Luca's walk on Route 12; a full disk. |
| 2026-10-27 | `v2-main` `87d5db02`; no map changes: forty-two new steps, Silph Co. (the Card Key, the pads, the rival, Giovanni), out through 3F's other door, and Sabrina's Gym's pads | **Steps 248–289 pass**, from step 247's checkpoint in parts as they were added. A first try ended a walk on 5F's pad, which a checkpoint can't hold: the steps go round by 9F's pad instead. The way out of 11F is back by the pads (7F's west side has no other way out) and 3F's second door. |
| 2026-10-27 | `v2-main` `1ca40047`; no map changes: fifty-six new steps, back to Fuchsia by Routes 6, 11 and 12, Surf down Routes 19 and 20 to Cinnabar, the Pokémon Mansion's switches and the Secret Key, Blaine's quiz, and up Route 21 to Pallet | **Steps 290–345 pass**, from step 289's checkpoint in parts as they were added. First tries: the walks couldn't surf (the script's walks gained `surf`, with surfing's 8-frame blocks and the turn a short press makes); a surf walk overshot into a swimmer's line; the Mansion's holes land on plain floor (my planner first took them for ways back up); its stairs and Saffron's south gate need one more press; pae plans with the Mansion's barriers and the Gym's doors as built, so walks through them are held in the inputs; the statue's and Bill's words needed more presses. Two step names were the same (`route11`): the script now stops on that. A `pae play --show-flag` with a trainer's name read some other flag: pae fix to come. |
| 2026-10-27 | `v2-main` `a550f77f`; no map changes: the check reaches the Indigo Plateau. Lt. Surge, the Fan Club's Bike Voucher and the Bicycle, Route 16's Snorlax and Cycling Road back to Fuchsia (instead of Routes 11–15 again), Giovanni's Gym, Route 22's last rival battle, Route 23's badge gates, Victory Road's four Strength switches, the Indigo Plateau's Center | **All 399 steps pass from the top** in one run (7991 s). First tries: a walk ended on the Viridian Gym's door trigger, so the checkpoint dropped the lock's scene and the walk went into the Gym without the Thunder Badge (Lt. Surge had been skipped: he is played now); the Vermilion Gym's trash cans are shuffled each time the Gym loads (its step plays from its own checkpoint); a reload indoors or with a `state` drops the Bicycle, so the mount and the ride are one step with no state; on Cycling Road a held key moved the battle menu; a cut tree grows back on reload; Lewis's battle outran the presses (a walk that meets a battle now plays through it). In Victory Road: a push moves only the boulder (the plans first moved the player too); boulders go back on a reload (the walks go round them); the 3F switch is needed to reach the hole; wandering Pokémon stood in the pushes, and the Golem on 1F stays boxed in by the switch, so waiting there never helps: `strength_waits.py` finds the waits, starting earlier when a Pokémon is stuck (backlog #4). `pae map path` walked through trainers' lines (pae PR #35 adds `--avoid-sight` to plan the vias). Cerulean's Bike Shop door has three warps (backlog #7). |
| 2026-10-28 | `claude/saffron-city-blocks`: Saffron paved, with 13 offices and shops without doors (KR-88) | **Steps 247–399 pass** in one run (3346 s). A first try stopped at step 290: its walk to the south gate went through the park's south side, where a brick office stands now; it goes down the pavement beside the avenue instead. |
| 2026-10-29 | `claude/kit-streets-v0.3`: the kit's city streets (KR-89); every kit map rebuilt (the water's tiles moved), seams reusing each map's own tiles (pae PR #37) | **All 399 steps pass from the top** in one run (8719 s), first try. |
| 2026-10-29 | `claude/saffron-streets`: Saffron's streets are the kit's (asphalt, kerbed pavements, zebra crossings), its plazas granite (KR-90) | **Steps 247–399 pass** in one run (3432 s), resumed from step 246's checkpoint (made 2026-10-27; the check stands at Saffron's east gate, which hasn't changed), first try. |
| 2026-10-29 | `claude/celadon-streets`: Celadon's boulevard asphalt with kerbed pavements and zebra crossings, Lucky Lane brick (KR-91) | **Steps 142–399 pass** in one run (5871 s), resumed from step 141's checkpoint (made 2026-10-27, outside Route 7's hut, which hasn't changed), first try. |
| 2026-10-29 | `claude/pewter-detail`: Pewter more of a mountain town (KR-92): a higher tier on each cliff, the west side paved, brick sidewalks and paths, three cottages without doors; the guides' walks worked out again | **Steps 38–47 pass** `--from route2-north` and `--from pewter` (11 s and 154 s), resumed from steps 37's and 38's checkpoints: Route 2's north end, the Gym guide's new walk, Brock, the Running Shoes and across Route 3 (its seam changed) to Route 4. Steps 1–37 and 48 on don't reach Pewter. `pae test run`: all 555 pass (three new; six screens accepted, five of them Pewter's and Route 15's name popup a frame later). |
| 2026-10-30 | `claude/cerulean-detail`: Cerulean paved, its blue brick, canals, fences, cottages and the Town Props (the fountain, benches, footbridges; KR-93) | **Steps 57–79, 106–111 and 307–311 pass**, every step that reaches Cerulean, resumed from steps 56's, 105's and 306's checkpoints. The first try stopped at step 59: its walk went along the street's lower row, now the fence along the Center's north side, and the policeman stands in the upper one; the walk goes round the square now. `pae test run`: 555 passed, 9 screens changed and accepted; two new tests. |
| 2026-10-30 | `claude/town-props`: the Town Props in ten more towns (KR-94): Viridian, Vermilion, Lavender, Fuchsia, Pallet, the Indigo Plateau, Saffron, Celadon, Cinnabar and Pewter | **All 399 steps pass from the top**: steps 1–391 in one run (8364 s), then 392–399 `--from vr3f-switch` (313 s). First tries: step 1 stopped at (14, 3), as its walk up to the road north went through Pallet's new fingerpost at (13, 2–3); it turns onto the road at row 4 now. Step 392 stopped with the 3F switch not pressed: a wandering Pokémon stood in the boulder's way at pushes 34, 36 and 38. The checkpoint the step starts from changes with every step before it, and no run since 2026-10-29 had reached it (Pewter's and Cerulean's checks stopped at their own steps). `strength_waits.py` from step 391's checkpoint found `{34: 75, 36: 45, 38: 75}`. `pae test run`: all 560 pass (three new; 29 screens accepted, the props in view). |
| 2026-10-30 | `claude/vermilion-harbour` (with `claude/town-props` merged in): Vermilion's harbour (KR-95): the square and the park in fan setts, the main street asphalt with setts bands each side, the promenade in quay flags, the quay wall round it, the pier and the dock | **All 399 steps pass from the top**: steps 1–391 in one run (8400 s), then 392–399 `--from vr3f-switch` (314 s). The first try stopped at step 392, as the Town Props run did, and passes with the same waits (`strength_waits.py` from this ROM's step 391 found the same `{34: 75, 36: 45, 38: 75}`). Every step through Vermilion passed first time: steps 84–100 (into town, the Center, east to Route 11 and back, the S.S. Anne) and 292–301 (the Fan Club's Bike Voucher, the Cut tree into the Gym's yard, Lt. Surge). `pae test run`: 562 tests, 545 passed, 17 screens changed and accepted (Vermilion's ground in view, and Route 11's two that look into it), then those 17 pass; two new tests. |

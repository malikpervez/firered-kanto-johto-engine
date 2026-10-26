# Story sanity check

This is a play-through of the story from a new game, through every map rebuilt so far. It is run after each route
or town change, to check that the story still plays to the end of the rebuilt maps. This page records the last
point that passed, so the next check carries on from there instead of starting again.

The replay tests (`pae test run`) each check one event, starting from story state the test sets up. This check
plays the events one after another, each starting where the last one left the game, with no story state set up.

## Last validated point

| | |
|---|---|
| Date | 2026-10-26 |
| Game | branch `claude/story-ss-anne-misty` (story check only, on `v2-main` at `03dc1a9d`) |
| ROM | `make -j8` with the default settings. SHA-1 `473af5ff345ea3ea9dc878a3c2999c957b2e2723`, SHA-256 `f55f676aafbb9963ba897f223202f86a0edb4d3f8277b2e47aa15b24cd2f1a53` |
| pae | `69213f1` (pae PR #23) for the replay tests and steps 47–50; `06115c8` (pae PR #24: blocks and walks as the game has them) for steps 51–59; `95025b1` (pae PR #26) for steps 60–69; `fe38af0` (pae PR #27: walks know the metatiles the game makes) for steps 70–76; `77c66ac` (pae `main` after PR #27) for steps 77–110 and the replay tests |
| Last step passed | 110 `leave-cerulean-gym`: on through the S.S. Anne (Blue, the captain's HM01), off the ship as it sails, back through the Underground Path to Cerulean, and Misty's Gym (Diana, then Misty: the Cascade Badge). Steps 98–110 were run on this build, from step 97's checkpoint; steps 93–97 on the Route 11 build (SHA-1 `757bd085…`), from step 92's checkpoint. #47 changed none of what 93–97 play; the ship's landing it fixed is step 100, run on this build |
| Replay tests | 219 of 219 pass (on this ROM, for #47; this change adds none) |

## How to run it

From the repository root, with pae installed:

```sh
project/scripts/story_check.py                  # build, then every step
project/scripts/story_check.py --list           # the steps
project/scripts/story_check.py --from route22   # carry on from a step
project/scripts/story_check.py --to dex         # stop after a step
```

The script needs pae with `pae play --show-flag` (pae PR #17), and pae PR #19 (its walks keep off sideways stairs,
which the old Viridian Forest had). A run from the top takes about 35 minutes; a run `--from` a later step takes less.

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
| 59 | `cerulean-rival` | Along the street past the robbed house (its policeman in the door) and up the bridge road: Blue comes down off Nugget Bridge; beat him | Cerulean City 42,7 | `VAR_MAP_SCENE_CERULEAN_CITY_RIVAL` 1 |
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

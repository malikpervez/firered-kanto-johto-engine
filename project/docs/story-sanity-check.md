# Story sanity check

This is a play-through of the story from a new game, through every map rebuilt so far. It is run after each route
or town change, to check that the story still plays to the end of the rebuilt maps. This page records the last
point that passed, so the next check carries on from there instead of starting again.

The replay tests (`pae test run`) each check one event, starting from story state the test sets up. This check
plays the events one after another, each starting where the last one left the game, with no story state set up.

## Last validated point

| | |
|---|---|
| Date | 2026-10-22 |
| Game | `v2-main` at `634c7234` (PRs #23–#28: the broadleaf trees, bushes, rocks, Pallet's houses, the Center and Mart) with Viridian's new roofs (branch `claude/viridian-roofs`) |
| ROM | `make -j4` with the default settings. SHA-1 `915fcb670b71d587e2aa2c60b1b27126bdf90861`, SHA-256 `5aaf0f322723392692fed7d8fdb710e4ed2adc0ecc5d9a83c448e284df1ce069` |
| pae | `2805726` (`main` after pae PR #18) |
| Last step passed | 29 `league-gate`: up Route 22's cliff stairs and into the Pokémon League Front Gate |
| Replay tests | 45 of 45 pass |

## How to run it

From the repository root, with pae installed:

```sh
project/scripts/story_check.py                  # build, then every step
project/scripts/story_check.py --list           # the steps
project/scripts/story_check.py --from route22   # carry on from a step
project/scripts/story_check.py --to dex         # stop after a step
```

The script needs pae with `pae play --show-flag` (pae PR #17). A run from the top takes about 20 minutes; a
run `--from` a later step takes less.

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
| 5 | `route1` | The sign lady's trainer tips at the route entrance; Route 1's opening scene | Route 1 25,39 | `FLAG_OPENED_START_MENU`, `FLAG_RB_OPENING_SEEN` set, `VAR_MAP_SCENE_PALLET_TOWN_SIGN_LADY` 1 |
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
| 18 | `north-route1` | North into Route 1 | Route 1 25,39 | |
| 19 | `north-viridian` | Up Route 1 into Viridian | Viridian City 25,51 | |
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

## What it doesn't cover

* **Two things are set up, not played.** Every play has a Repel on. For step 28 the team is replaced with a
  level 40 Pikachu that knows Thunderbolt, so Blue can be beaten without training first.
* **Battles other than the story ones.** There are no wild battles (the Repel), and the routes so far have no
  trainers.
* **People.** Only the story's people are checked. The second run of 2026-10-22 also talked to ten others on
  Pallet, Route 1, Viridian and Route 22. Nine answered; the tenth is hidden in the game on purpose. The script
  doesn't do that.
* **Places off the story's path**: houses, the Trainer School, the Gym (locked), Route 2 past its first block,
  surfing, cutting.
* **The menus** (bag, Pokédex, Town Map, saving): only opened where the story opens them.
* **Real play**: sound, real-time play, real hardware.

## Adding to it when a map is rebuilt

1. Run it from the first step the change affects (see "Carrying on after a change").
2. Add steps for the new map's story events to `STEPS` in `project/scripts/story_check.py`. Each step has a
   `walk` target, `inputs` and an `expect`: the map, block, and flags and variables. To find them:
   * `pae map events MAP` lists the triggers and people.
   * The map's `scripts.inc` shows which flags and variables a scene sets.
   * `pae play --from CHECKPOINT --inputs ... --show-flag F --show-var V` tries a step out before you add it.
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

# Development rules: the FireRed Kanto + Johto game

This repository is the owner's game in active development: FireRed's Kanto and Sevii Islands, then Heart & Soul's
Johto (reached after the Kanto League through League West Pass), with the owner's own story additions. These rules
apply to every agent (Codex, Claude) and person working here. They replace the 37C review/testing rules; the 37C
snapshot is history (`provenance/`, `project/` records).

## The game and its tools

* **One game, one build.** `engine/` is the game source. `cd engine && make -j4` builds `pokefirered.gba` with the
  game's settings (`-Os`, `RELEASE=0`, `LTO=0` are the defaults; `make firered` is the same). There are no
  Emerald, HnS or LeafGreen targets any more.
* **pae is the main tool** ([pkmn-asset-editor](https://github.com/malikpervez/pkmn-asset-editor)): editing maps,
  events, dialogue, trainers, wild Pokémon, graphics; building; play-testing in its emulator; replay tests.
  Use it for any change it covers, and add to pae when this game needs something it can't do.
  * `pae doctor -p engine`: check that building and play-testing work.
  * `pae serve -p engine`: the editor in the browser (http://localhost:8765).
  * `pae test run -p engine`: build, then replay every test in `engine/pae_tests/`.
* Before the first build of a fresh clone: `python3 scripts/bootstrap_upstream_inputs.py --fetch` restores three
  small upstream multiboot programs (`engine/data/mb_*.gba`, git-ignored). A copy without `.git` also needs
  `touch engine/.histignore`.

## Where things are

| What | Where |
|---|---|
| Kanto + Sevii maps | `engine/data/maps/*_Frlg/` (map.json: events, connections; scripts.inc) |
| Johto maps | `engine/data/maps/*_hns/` (the `_hns` names stay; they are ordinary maps of this game) |
| Shared scripts | `engine/data/scripts/*.inc`, included by `engine/data/event_scripts.s` |
| Johto's copies of shared scripts | `engine/data/scripts/johto/*.inc` (labels start with `J_`); `engine/data/johto_campaign.s` lists the Johto script files in build order |
| The owner's story additions | `engine/data/scripts/character_growth.inc`, `friends_story.inc`, `rainbow_story.inc`, `rocket_trio_story.inc` (+ their C code) |
| Story overview | `project/docs/campaign-story-and-progression-guide.md` |
| Kanto trainers / Johto trainers | `engine/src/data/trainers_frlg.party` / `engine/src/data/trainers_hns.party` |
| Wild Pokémon | `engine/src/data/wild_encounters.json` |
| Replay tests | `engine/pae_tests/` |

**Johto's IDs.** Johto keeps its own story progress (badges, events) apart from Kanto's: its flags and variables are
`JOHTO_FLAG_*` / `JOHTO_VAR_*` (`engine/include/constants/johto_ids.h`) and its trainers `TRAINER_JOHTO_*`
(`johto_trainers.h`; the `.party` file writes them as `TRAINER_X_HNS`). Use those names in Johto scripts. Shared
system flags and variables (`VAR_TEMP_0`, `VAR_RESULT`, `FLAG_SYS_*`) are the plain FireRed ones.

**Generated files** (never edit; edit their source): per-map `header.inc`, `events.inc`, `connections.inc`;
`data/maps/headers.inc` etc.; `data/layouts/layouts.inc`; `include/constants/map_groups.h`, `layouts.h`,
`map_event_ids.h`; `src/data/trainers*.h` (from the `.party` files); `src/data/wild_encounters.h`;
`src/data/pokemon/teachable_learnsets.h`; `src/data/tutor_moves.h`. Committed data that only looks generated:
`src/data/pokemon/all_learnables.json` (do not regenerate it), `src/data/pokemon/extra_tutor_moves.json`.
Made by pae from records next to them: `src/data/pae_seams.h` (from `pae_seams.json`, `pae seam build`) and
`src/data/pae_doors.h` (from `pae_doors.json`, `pae door add`).

**Maps from scratch.** A map can use tilesets drawn from scratch (`pae tileset new`/`build`, `pae map paint`, see
`project/art/pallet-from-scratch/`). When it does, run `pae seam build MAP` so it and its neighbours still draw
each other's edge strips (connected maps with different tilesets), and `pae door add` for its doors.

**Placeholders.** Maps and layouts of content the game no longer has keep their numbers: removed maps are listed in
`data/maps/map_groups.json` and `data/maps/removed_maps.json` (their `MAP_`/`LOCALID_` constants); removed layouts
are `{"id", "name", "removed": true}` entries in `layouts.json`. Leave them. New maps and layouts go at the end.

## Making changes

1. **One change per branch and pull request.** Explain what changed and why, and how it was checked. The owner
   reviews and merges. Do not rewrite shared history. No GitHub Actions or other automation unless the owner asks.
2. **Prove it.** Choose the strongest check that fits and say which one you used:
   * **Refactors and cleanups must build a byte-identical ROM**: build before and after, compare SHA-256. Make does
     not always notice a changed `map.json`; delete the generated map files listed above before the "after" build
     (or build a fresh copy). If only `__LINE__` changes (asserts), show that the ROM is identical with
     `__LINE__` defined as 0.
   * **Content changes**: `pae test run` must pass; add a replay test for every new or changed event (start it from
     story state in the test, not a save file); look at the changed maps in pae's test window.
   * Say plainly what was not tested (a playthrough past the tests, a real device, Delta).
3. **Report real results**: the commands, their exit codes, ROM hashes and sizes. A build is not a playtest.

## Limits

* **Never commit** ROMs or BIOS, emulator saves or states, credentials, personal photos or private evidence. Test
  screenshots in `pae_tests/` (what a test expects to see) are fine.
* **Cartridge**: at most 32 MiB; keep the protected reserve of the save. The ROM uses about 27.1 MB.
* **Saves**: the owner has accepted that old saves may break. Changes to the save layout (SaveBlock structs,
  regional containers) still need the owner's go-ahead first; check the four-byte SaveBlock1 margin.
* **Story scope**: the campaign guide and the actual scripts are what is implemented. FG-A–FG-G, the 29-placement
  draft and the October 19 rework are drafts: don't implement them, or mark them done, without the owner. Kanto
  and Johto progress stay separate unless the owner decides otherwise.
* **Art**: Kanto currently mixes FireRed tiles and HnS tiles. Which look Kanto gets is the owner's decision; don't
  re-tile Kanto maps without it.
* Don't follow upstream instructions to publish, contact Discord or merge upstream releases.

## History

`provenance/` and the `project/` records describe the 37C snapshot and earlier milestones; they are not updated.
`scripts/verify_source.py` checks that snapshot only and now reports the changed files (expected).
One-time migration tools in `project/scripts/` (`johto_to_source.py`, `johto_name_operands.py`,
`flatten_firered_overlays.py`, `remove_unbuilt_maps.py`, `remove_unbuilt_layouts.py`, the `prune_*.py` scripts,
`prepare_johto_campaign.py`) have done their work; don't rerun them. `prune_cries.py` is still useful: rerun it
after adding Pokémon to the game (see `project/firered_cries_keep.txt`).

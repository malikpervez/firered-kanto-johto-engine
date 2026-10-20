# Indigo Plateau western pass

Status: **candidate26 implemented, compiled and narrowly tested in desktop mGBA0.10.5**. GO for local development evaluation; HOLD for player release. The previously tested candidate25b remains preserved. This change implements the owner's post-Kanto Championship westbound journey and isolated test-checkpoint direction.

The intended sequence is Kanto Champion → Oak's Hall-of-Fame referral → Indigo Plateau's western entrance → League pass officer → New Bark Town → Professor Elm's existing adapted introduction. Original credits/Pallet return remain; the player can return to Indigo when ready. Oak's lab and the Pallet guide provide recoverable directions.

The pass checks the existing native Kanto game-clear flag. A valid first visit initializes the existing Johto container once; repeat visits preserve its story, badges, rival and collection. Initialization failure returns to Indigo without entering Johto. No new save fields, story flags, HM grants or resource resets are introduced.

One map is appended to the existing Indigo indoor group. It reuses the selected HnS east/west gate layout and graphics. Two small FireRed-only outdoor entrance adaptations supply a dry walking route. Existing map/layout identities, earlier warp indices and the Route26/27/Tohjo/Johto League geography remain intact.

## Executed bounded checks

| Check | Current result |
| --- | --- |
| Source branch/lock/idempotence review | PASS — source reviewed; the native gate/re-entry cases below executed |
| Actual map generation, destinations, stable IDs and peer exclusions | PASS — FireRed/HnS/LeafGreen generation; new pass only selected by FireRed; existing IDs and warp prefixes preserved |
| Frozen source, build logs, real exits and ROM/RAM budget | Compilation0, original wrapper2, separate qualification0 — exact generated debug map-count change explained below |
| Staged pre-Champion entry remains closed | PASS — walk from Indigo into pass, officer refusal, safe return to Indigo11,8 with controls restored and Johto unseeded |
| Staged post-Kanto Champion walks west into New Bark | PASS — physical dry route from Indigo, officer welcome, first-visit initializer, pass crossing and New Bark24,9 arrival |
| Existing Elm introduction retains the Kanto trainer and party | PASS — normal lab entrance/Elm approach/research errand; original RED/GARY and Bulbasaur retained, independent SILVER; Pokégear/contact and aide Potion1 recorded, no second starter |
| Ordinary save/full quit/fresh-process Continue | PASS — game's Save menu/overwrite, both native banks valid, counter3; cold Continue restores New Bark24,10, party/Dex/names/resources/story |
| Silent repeat entry and physical return to Indigo | PASS — New Bark cave to pass1,5 with no repeated welcome/reseed, east exit to Indigo3,10 unlocked; separate round-trip byte review below |
| Natural Hall-of-Fame/Oak referral and initialization-error branch | NOT RUN in native26 — source/build qualified only; original credits/Pallet return retained |
| Third staged unseeded-border fixture | CREATED AND VALIDATED; NOT LOADED in native tests |

The test saves are explicitly labelled **STAGED NOT NATURAL** diagnostic checkpoints. All native checks above started with staged native Kanto badge/game-clear bits, not a naturally completed League. Full Kanto/Sevii/Johto playthrough, every-map visual qualification, release readiness, old-save migration and arbitrary endgame story correctness are outside these bounded claims. Existing roamer fidelity, Hall-of-Fame atomicity, four-byte main-save margin and graphics read-span/budget limitations remain open in the [repair audit]([LOCAL_WORKSPACE]/docs/candidate23-repair-and-tooling-audit.md).

Workstream A/C repositories and services, NAS/networking, remote publication, commits and hosted automation remain untouched. Source, ROMs, saves, map previews and raw evidence stay local under ignored `_local/` paths.

## Play the new travel slice

Open [Test Johto Journey.command](<[LOCAL_WORKSPACE]/_local/saves/firered/johto-full-26-owner-postchampion-01/Test Johto Journey.command>) and choose **Continue**. This separate diagnostic copy starts at Indigo11,8. Walk west to the cave entrance at3,9, speak through the officer's welcome, and leave through the pass's western door. New Bark's normal lab entrance leads to Elm. The cave east of town returns to Indigo.

This checkpoint stages all eight native Kanto badges and native Champion-clear, but retains a level6 Bulbasaur; it is a travel/quest fixture, not a battle-ready endgame team. For a separate fresh game, use [Play Kanto and Johto.command](<[LOCAL_WORKSPACE]/_local/saves/firered/johto-full-26-owner-fresh-01/Play Kanto and Johto.command>). Both owner launch folders were prepared and hash-checked but **NOT LAUNCHED** by the tests. Their saves do not share the native test directories or previous owner play folders.

## Native evidence and preservation

The [final candidate26 evidence index]([LOCAL_WORKSPACE]/_local/evidence/indigo-west-pass-01/final-results26-01.json) binds build, source, fixture, executed native and local-launcher evidence. It supersedes pending-test wording inside earlier immutable receipts without rewriting those receipts.

The [pre-Champion result]([LOCAL_WORKSPACE]/_local/evidence/indigo-west-pass-01/native26-prechampion-01/results.json), [first-entry seed review]([LOCAL_WORKSPACE]/_local/evidence/indigo-west-pass-01/native26-champion-01/championseed-review01.json), [Elm/aide review]([LOCAL_WORKSPACE]/_local/evidence/indigo-west-pass-01/native26-champion-01/elm-entry-review01.json), [normal-save review]([LOCAL_WORKSPACE]/_local/evidence/indigo-west-pass-01/native26-champion-01/normal-save-review01.json), [cold-reload review]([LOCAL_WORKSPACE]/_local/evidence/indigo-west-pass-01/native26-cold-01/cold-save-review01.json), and [round-trip review]([LOCAL_WORKSPACE]/_local/evidence/indigo-west-pass-01/native26-cold-01/roundtrip-review01.json) bind the actual26 ROM, snapshots, save and private screenshots. Tests used bounded ordinary emulator button inputs and read-only RAM observers. There were no live RAM/story edits, cheats or save states.

The actual normal save is [normal-save26-01.sav]([LOCAL_WORKSPACE]/_local/evidence/indigo-west-pass-01/native26-champion-01/normal-save26-01.sav), SHA-256 `2c72491a2df102cf92701f58513d92c678785e97d2923a73afe5b6850a21b738`. Both banks validate; selected counter3. Cold Continue restored Town3/Lab3, zero Johto badges, RED/GARY/SILVER, one original Pokémon, full party/Pokédex/native flags/variables, money3080/coins0 and Potion1. Full four-byte trainer-ID reads match stored/source `21f237b4`; older numeric snapshot reads have an unaligned low16 limitation and are not the full-ID proof. Ordinary Continue/map loads shift the existing roamer history; reviews model those exact changes rather than claiming raw regional byte equality.

After the physical return, mGBA was fully quit and independently confirmed absent. No second Save was requested on the return leg: the stored save remains exactly the counter3 New Bark checkpoint, while read-only snapshots and a screenshot prove the unlocked Indigo arrival. [Closed-process receipt]([LOCAL_WORKSPACE]/_local/evidence/indigo-west-pass-01/native26-cold-01/cold-closed01.json).

## Isolated diagnostic checkpoints

[`scripts/create_firered_checkpoint.py`](../scripts/create_firered_checkpoint.py) accepts a selected `--map MAP_… --x … --y …` and creates a fresh, separately named test copy. `location-only` preserves progression; `pre-champion` stages all eight native Kanto badge bits and clears native game-clear; `post-kanto-champion` stages those badges and native game-clear. These are **STAGED NOT NATURAL** checkpoints. Johto story state, trainer/rival names, party, PC, items, money and Pokédex remain unchanged. Placing the trainer on a late map still requires an appropriate reviewed story checkpoint.

The current source is the immutable fresh25b normal save below, with a level6 Bulbasaur. The tool supplies no battle-ready party or claim of a naturally completed League. It requires the exact source hash, two valid native6 banks, a successful build manifest, matching ROM/ELF and frozen source, freshly measured ARM/APCS fields, and an actual ROM map cell within bounds with no collision. Terrain, actor and quest suitability still require focused review. Output directories must be new; omitting `--write` produces a plan without emitting a save.

This example stages the post-Kanto gate test at Indigo. Change the map/coordinates and preset for another reviewed checkpoint, and select a new output directory for every run. Candidate26 uses its separately qualified manifest: compilation exited0; the original wrapper exit2 and the bound one-byte debug map-count qualification exit0 remain explicit.

```sh
python3 scripts/create_firered_checkpoint.py \
  --source _local/saves/firered/native25b-cold-01/normal-save25b-01.sav \
  --source-sha256 327cc75c411fb596bc7e1b07611be08ed2a56c2d8c1a2da355cc42998732270f \
  --build-manifest _local/artifacts/johto-full-26-firered/manifest.qualified.json \
  --map MAP_INDIGO_PLATEAU_EXTERIOR --x 11 --y 8 \
  --preset post-kanto-champion \
  --out _local/saves/firered/indigo26-example-01 --write
```

The tool preserves the source's current map/cache/saved actors and stages the existing native Continue request. On Continue, the normal warp loader reconstructs the destination view, actors and templates and clears map temporaries before input. Every changed byte is checked against the narrow request/badge/clear/checksum/digest allowlist; the backup bank, special sectors and trailer remain intact.

Three candidate26 fixture copies were created and independently reparsed with valid banks and unchanged protected byte domains. All retain blank, unseeded content3 Johto state. Their creation is recorded in [`fixture-helper-created26-01/results.json`](../_local/evidence/indigo-west-pass-01/fixture-helper-created26-01/results.json), SHA-256 `f6a2e2b48beb32865660f42839466912a122e01626fb99f91b44f8a7ba963f80`. Native execution is recorded separately in the bounded-checks table above.

| Staged checkpoint | Destination | Private save |
| --- | --- | --- |
| Pre-Champion | Indigo11,8; native clear false | [`checkpoint.sav`](../_local/saves/firered/indigo-west-pass26-pre-champion-01/checkpoint.sav) |
| Post-Kanto Champion | Indigo11,8; native clear true | [`checkpoint.sav`](../_local/saves/firered/indigo-west-pass26-post-champion-01/checkpoint.sav) |
| Unseeded post-Champion border | League pass4,5; native clear true | [`checkpoint.sav`](../_local/saves/firered/indigo-west-pass26-unseeded-border-01/checkpoint.sav) |

## Candidate26 build record

**Build, linked and bounded native checks executed, with their distinct scopes recorded above.** The frozen source contains775 modified/added text inputs against upstream commit `167aa6d537b109bb229c231ddce4616974c4da71`, with exactly nine source changes from25b. The target is `FIRERED` / `MAP_VERSION=firered` / game code `BPRE`; configuration is unchanged from25b. The complete patch SHA-256 is `4e998a3c399801ac349b23d06b918a88d6a1ed79016b493566b8c1f366c6a8fe`.

This was one two-job incremental build in a new isolated, byte-verified copy of successful25b, whose parent is clean24. **Actual make exited0; the original wrapper exited2; separate qualification exited0.** The original failure remains preserved: its zero-C-object-change check caught the generated `debug.o` map-count byte changing2→3 for the new pass. The qualification proves that single byte and every other C object unchanged; no compilation was repeated. [Qualified manifest]([LOCAL_WORKSPACE]/_local/artifacts/johto-full-26-firered/manifest.qualified.json) and [full build/linked ledger]([LOCAL_WORKSPACE]/_local/evidence/candidate23-independent-review/build-validation-01/incremental26-prepared-02/final-build-validation-summary.json) preserve source/configuration, real exits, logs and artifact hashes.

The local [FireRed ROM]([LOCAL_WORKSPACE]/_local/artifacts/johto-full-26-firered/pokefirered.gba) has SHA-256 `c705c297ca34e86ec45d061ae9291073dcbfc3e545a3290b6d85a7816068ff13` and CRC32 `bd429377`. ROM used33,531,236 bytes;23,196 bytes remain. EWRAM255,016 bytes, IWRAM25,948 bytes and heap115,968 bytes match25b. All254 literal aliases and the retained inherited backing spans were checked against the actual26 ELF/ROM. Old map IDs remain stable.

Save-defining sources and ARM/APCS layouts are unchanged: native6 / FRJS1 / content3 / layout1, four-byte main-save margin,256-byte regional reserve. This build record makes no gameplay, campaign completion, roamer repair or general save-compatibility claim. The [local B-to-C notice]([LOCAL_WORKSPACE]/_local/evidence/indigo-west-pass-01/b-to-c-candidate26-local-notice-01/notice.json) limits C’s affected assumptions to the travel entrances/new pass and Oak/Pallet direction text; unrelated art work and unchanged tests do not restart.

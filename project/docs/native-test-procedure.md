# B0 desktop mGBA procedure

**Owner update — October 9, 2026:** Audio is **PASS — OWNER-REPORTED** for the current B0 evaluation. See the [owner audio confirmation](decisions/2026-10-09-b0-owner-audio.md) for attribution and scope. This later confirmation supersedes earlier audio-pending statements below; Codex did not perform a new listening test. The prior frozen audit and native reports remain historical evidence. B0 remains HOLD for review of the four-byte save margin and FireRed roamer fidelity defect.

This is an execution procedure, **not a report of passes**. Read `docs/test-results.md` and the selected build's manifest before beginning. A target with no successful ROM is **BLOCKED**. Future human execution must identify Malik or another named tester; it must not be attributed to Codex.

Source pin: `167aa6d537b109bb229c231ddce4616974c4da71`. Natural opening steps below were inspected in that source; runtime reachability remains a separate test. Historical pristine runs are `baseline-01` and `baseline-02`. The current reviewed runs are `repair-10-firered` / `repair-10-hns`, with separate `repair-10-repeat-firered` / `repair-10-repeat-hns` trees. Use a distinct native-test Run ID so evidence cannot be confused with a rebuild.

## One fresh session for each target

1. Select a successful target manifest. Record its absolute ROM path, full SHA-256, source SHA, command/configuration and patch/generated-file fingerprints. Never use a ROM merely because its filename looks correct. FireRed's source output name is `pokefirered.gba`; HnS's is `pokehns.gba`.
2. Create a **new**, empty directory at `[LOCAL_WORKSPACE]/_local/saves/firered/<test-run-id>/` or `[LOCAL_WORKSPACE]/_local/saves/hns/<test-run-id>/`. If the proposed directory exists, choose a new Run ID; do not delete or overwrite it.
3. Copy only the manifest's ROM into that session, using a unique basename such as `firered-owner-01.gba` or `hns-owner-01.gba`. Hash the copy and verify that it equals the manifest's hash. Keep the manifest reference with this session. Do not import an existing `.sav` or any save state.
4. Use the project-local official mGBA **0.10.5** application: `[LOCAL_WORKSPACE]/_local/tools/mGBA.app`. Its executable is `Contents/MacOS/mGBA`. Start a separate test instance, then use File → Load ROM to open the session copy. Do not close another emulator running a personal game.
5. In mGBA settings, record the actual Paths/Save games location and point native saves to this session (or use the ROM directory if that is the effective default). Confirm the native save actually appears there after saving. Keep FireRed and HnS save paths independent.
6. Disable **Load last state** before gameplay and both cold reloads. Do not load/save emulator states during acceptance. Record cheats, patches and peripherals; use no cheats, no debug grants/warps, no externally supplied BIOS, normal speed and frameskip 0. Record the input mappings visible in the settings; controls below refer to GBA buttons, not assumed keyboard mappings.

The initial mGBA settings inspection found frameskip 0, OpenGL display, SDL audio at 44,100 Hz/buffer 1536, **Load last state enabled**, and periodic save-state autosave disabled. These are configuration observations only. Correct last-state loading for test execution and record the final settings; inspection does not establish audio, input or gameplay quality.

Store private notes/screenshots/logs in `[LOCAL_WORKSPACE]/_local/evidence/<test-run-id>/<target>/`. Record date/time/timezone, tester, host, mGBA version, speed/settings, active-play start/end times, ROM/save paths and hashes. Never embed the protected game images or saves into tracked reports.

## FireRed: natural opening

| IDs | Procedure and expected observation |
| --- | --- |
| FR-01 | Start New Game, complete the Oak identity introduction, choose trainer/name and rival name. Enter the player's upstairs bedroom in Pallet Town. Go downstairs, talk to Mom and enter the town. Confirm the actual Pallet opening and controllable world; the title alone is insufficient. |
| FR-02 | Walk toward the northern town exit. Oak should stop the player and escort them to the lab. Finish the dialogue; choose one of the three starter balls naturally and inspect the received starter. Record its species, level and moves. |
| FR-03 | Attempt to leave the lab after selecting the starter. Complete the initial rival battle using ordinary commands. Verify the battle returns to the lab, dialogue ends and movement resumes. Record outcome and any tutorial differences. |
| FR-04 | Traverse Pallet ↔ Route 1 ↔ Viridian and enter/leave buildings. Talk to at least one ordinary NPC in each town and on the route. Inspect visible collision/warps/graphics. Use these same transitions during the delivery and healing steps. |
| FR-05 | Enter Viridian's Poké Mart, receive Oak's Parcel, then return to the Pallet lab and speak to Oak. Finish the delivery/Dex scene naturally. Verify the parcel is removed and the Pokédex and initial five Poké Balls are received once. |
| FR-06 | Fight a wild Pokémon on Route 1. After legitimate balls are available, capture one. Heal at Mom or Viridian's Pokémon Center and inspect the party for correct HP/status, species, levels and moves. No debug gifts count as captures. |
| FR-07 | Open/close Bag, Party and the available Pokédex; inspect trainer identity/money. Record changed/missing interfaces and return to the field without a crash. |
| FR-08 | Perform save/cold-reload cycle 1 below after the parcel/Dex progression, with a captured Pokémon when possible. |
| FR-09 | Continue playing after reload, make a visible change (different location and a legitimate item/money/party change), then perform cycle 2. Verify starter/parcel/balls/Dex events are not replayed or rewarded again. |
| FR-10 | Accumulate at least ten minutes of active play across the above. Record actual speed display, inputs, visible artifacts, audible results and freezes. Setup, paused time and stationary menu-reading/tool-idle time do not count. Measured actual interactions with gameplay menus, battles, running dialogue/animations and movement may count; do not substitute the whole wall-clock session for observed active play. |

Pinned sources: [initial warp](https://github.com/PokemonHnS-Development/pokehns-expansion/blob/167aa6d537b109bb229c231ddce4616974c4da71/src/new_game.c#L189), [Oak approach](https://github.com/PokemonHnS-Development/pokehns-expansion/blob/167aa6d537b109bb229c231ddce4616974c4da71/data/maps/PalletTown_Frlg/scripts.inc#L180), [lab events](https://github.com/PokemonHnS-Development/pokehns-expansion/blob/167aa6d537b109bb229c231ddce4616974c4da71/data/maps/PalletTown_ProfessorOaksLab_Frlg/scripts.inc), [Viridian parcel](https://github.com/PokemonHnS-Development/pokehns-expansion/blob/167aa6d537b109bb229c231ddce4616974c4da71/data/maps/ViridianCity_Mart_Frlg/scripts.inc).

## Heart & Soul: natural opening

| IDs | Procedure and expected observation |
| --- | --- |
| HNS-01 | Start New Game, complete identity setup and record all initial campaign choices. Use the Recommended/default campaign; leave randomizer, Nuzlocke and additional challenges off. Enter the New Bark upstairs bedroom, finish the wall-clock prompt, go downstairs and complete Mom's scene (PokéGear/running shoes). Confirm New Bark Town and normal movement. |
| HNS-02 | Enter Elm's lab, accept the initial request and choose a Johto starter ball naturally (Chikorita/Cyndaquil/Totodile). Record the level-5 starter and moves. **Speak to Elm again after choosing** to obtain task directions and his number; exit through the aide's potion scene. |
| HNS-03 | Travel west through Route 29 to Cherrygrove. Finish the Guide Gent interaction (take the tour to exercise movements), then go north through Route 30 to Mr Pokémon's house. Finish the Mystery Egg/Oak/Pokédex scene. Return through Cherrygrove for the first Silver battle. Return to Elm's lab for the police/rival-name scene and egg handover; leave through the aide's scene granting five Poké Balls. Verify the intended event order without warps/skips. |
| HNS-04 | During the errand, enter/leave several early interiors, cross town/route boundaries and talk to ordinary NPCs. New Bark houses/lab, Cherrygrove Center/Mart and Mr Pokémon's house are examples; record which were actually entered. Check collision, warps, rendering and control. The normative checklist requires representative transitions, not every early interior. |
| HNS-05 | Fight a wild Pokémon on Route 29/30. Once the aide has legitimately granted Poké Balls, capture one. Heal at Elm's machine, Mom (when available), or Cherrygrove Center. Inspect HP/status and party species/levels/moves. |
| HNS-06 | Open/close relevant Bag/Party/Pokédex/PokéGear and clock/settings interfaces. Record the selected **RTC vs FAKE RTC** mode, clock value and how it changes during observed play. Record any changed/missing interfaces. Do not alter the host clock to accelerate events. |
| HNS-07 | Perform save/cold-reload cycle 1 below after the opening errand/rival/egg progression. |
| HNS-08 | Continue after reload, make a visible legitimate state change, then perform cycle 2. Verify starter, potion, Mystery Egg, Dex and Poké Ball scenes/rewards do not repeat. |
| HNS-09 | Accumulate at least ten minutes of active gameplay and record speed, inputs, visible artifacts, audible results and hangs as for FireRed. |

Pinned sources: [bedroom clock](https://github.com/PokemonHnS-Development/pokehns-expansion/blob/167aa6d537b109bb229c231ddce4616974c4da71/data/maps/NewBarkTown_PlayersHouse_2F_hns/scripts.inc), [Mom](https://github.com/PokemonHnS-Development/pokehns-expansion/blob/167aa6d537b109bb229c231ddce4616974c4da71/data/maps/NewBarkTown_PlayersHouse_1F_hns/scripts.inc), [Elm/starter/aide/police](https://github.com/PokemonHnS-Development/pokehns-expansion/blob/167aa6d537b109bb229c231ddce4616974c4da71/data/maps/NewBarkTown_Lab_hns/scripts.inc), [Mr Pokémon](https://github.com/PokemonHnS-Development/pokehns-expansion/blob/167aa6d537b109bb229c231ddce4616974c4da71/data/maps/Route30_MrPokemonsHouse_hns/scripts.inc), [Cherrygrove/Silver](https://github.com/PokemonHnS-Development/pokehns-expansion/blob/167aa6d537b109bb229c231ddce4616974c4da71/data/maps/CherrygroveCity_hns/scripts.inc).

## Two genuine save/cold-reload cycles per target

Perform this full procedure twice; a soft reset, pause/resume or restored emulator state is insufficient.

1. Before saving, record trainer name/gender/visible trainer ID, rival name, Pokédex seen/caught counts and inspected owned entries, party species/levels/HP/status/moves, money and important items/quantities, current map/building/location, and completed opening events. Include clock/mode for HnS. Screenshots are optional private supporting evidence; written observations must be specific. For the approved FireRed layout experiment, a read-only decoder bound to the successful build's ARM offsets may supplement rival-name/Dex evidence; it cannot replace either GUI cold reload.
2. Use the game's Start → Save command, confirm, and wait for its completion message and restored control. Record any save error. Do not select mGBA's Save State command.
3. Fully quit that test mGBA instance with the application's Quit command. Confirm the process for that instance ended. Locate the resulting native save under the intended private session path, record its exact name/size/SHA-256, and make a new private copy named for cycle 1 or 2. Leave the active native save intact.
4. Relaunch mGBA and reopen the **same session ROM/hash**, with Load last state disabled. Observe a cold title/menu boot and use the game's **Continue** entry. Do not use emulator-state loading.
5. Compare every recorded field with the pre-save record. Verify the saved location and meaningful event progression, then revisit the relevant starter/reward NPCs or exits to confirm completed scenes do not replay and rewards are not duplicated.
6. For cycle 2, continue normally and record a new location plus a legitimate item/money/party change. Save, fully quit, preserve the second native save and cold-reload again. Report both cycles independently, including each actual save hash.

Do not import FireRed saves into HnS, or use `baseline-02` to claim cross-build save compatibility. These checks establish only persistence in the exact tested ROM/configuration.

## Evidence limits and failure handling

The pinned default build enables an overworld debug menu at **R + Start**, a battle debug menu at **Select**, and a sprite debug view at **Select** in the summary screen. Avoid those commands and all grants/warps/flag editing. If accidentally activated, record it and restart a fresh acceptance session rather than counting debug-assisted progress.

Observe emulation speed during field movement and battles with normal speed/frame limiting; if a percentage/FPS display is unavailable, record that limitation and describe measured elapsed play time without inventing performance figures. UI screenshots alone do not prove audio was heard. A tester who cannot hear output must mark the audio observation unresolved; an emulator audio setting is not an audio-quality test. Ten minutes is a smoke threshold, not full-campaign stability.

HnS source documents FAKE RTC as one real hour per in-game day. Brief observation cannot certify all day/night encounters, events or clock persistence across long shutdowns. Record the selected mode, wall-clock values and observations, and leave broader RTC regression outside B0.

Use `PASS — EXECUTED`, `FAIL — EXECUTED`, `NOT RUN`, `NEEDS OWNER TEST`, or `BLOCKED` per checklist ID. If an early defect prevents later steps, record the actual failing ID and mark dependent checks BLOCKED. For a failure include ROM hash, last successful step, exact symptoms, reproducibility, mGBA/campaign settings and private evidence paths. Do not change gameplay or use a prepared save to bypass it. Report deviations from intended FireRed/HnS behavior even if play continues.

After both target reports, return to the **B0 review gate**. This procedure does not authorize B1, region merging, multiplayer or publication.

## Outstanding human audio observation for both final experimental targets

The owner explicitly requested sound remain off while Codex tests. Codex preserves that mute preference; GUI tools provide no audible output. Audio remains NEEDS OWNER TEST for both exact ROMs below. Both dedicated native runs are complete, their two normal-save/cold-reload comparisons passed, and Codex fully quit mGBA. The confirmed isolated saves can be used for the listening steps below. Do not load the preserved failed 009 FireRed session as a successful test. Audio settings/FPS are not a listening test. These instructions are for the owner after reading the final reports; they do not imply a human observation was executed.

| Exact dedicated native-session ROM | SHA-256 |
|---|---|
| `[LOCAL_WORKSPACE]/_local/saves/firered/repair-10-native-01/firered-repair-10-native-01.gba` | `3e504731d9dd3c02ec273dc257c86f557caaf8c9b933d2f0ff73558c2e121a39` |
| `[LOCAL_WORKSPACE]/_local/saves/hns/repair-09-native-01/hns-repair-09-native-01.gba` | `4bb58fe3c06bc0b60146aa946cbc34f087efa607f525f68e0a1e99c0db9cde75` |

The HnS path deliberately retains the fresh 009 session, copy and manifest: actual 010 ROM bytes are identical to that tested 09 ROM. Its metadata must not be rebound or its saved progress imported into a different session. The FireRed path is the separate fresh 010 session.

1. When ready to listen, open `[LOCAL_WORKSPACE]/_local/tools/mGBA.app` (0.10.5), then File → Load ROM with one exact path above. Keep Load last state/cheats/periodic states off, frameskip 0 and normal speed. Select an audible output and unmute deliberately for this human test; do not overwrite the preserved cycle backups or import states.
2. Listen to title music, then use the game's Continue. Walk through a town/route transition and enter an ordinary wild battle. Listen for music, dialogue/menu effects and battle effects, noting cutouts, crackle or abnormal speed. Inspected keyboard mapping: X = A, Z = B, arrows = movement, Return = Start. Avoid R+Start/Select debug commands. No additional normal save is required; fully quit afterward. Repeat independently for the other ROM.
3. Report named tester, date/time, exact ROM hash, mGBA/audio output settings, steps actually exercised, and PASS — EXECUTED or FAIL — EXECUTED with symptoms for each target. Until that report, audio stays NEEDS OWNER TEST.

Both final 010 build ROMs exist; native procedures must use the successful exact-manifest FireRed 010 session and the byte-identical, preserved HnS 009 session, never a failed-link map, HnS substituted for FireRed, or a downloaded replacement. Broader RTC/day-night, full campaigns and old/cross-build save compatibility remain unqualified.

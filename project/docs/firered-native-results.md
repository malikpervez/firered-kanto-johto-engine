# Final repair09 FireRed native test

**Tester:** Codex, October 8, 2026 EDT / October 9 UTC. **Result:** FR-01 passed; FR-02 failed. The naturally granted starter was absent from the party. Subsequent acceptance checks are blocked. This is a patched ROM, not a pristine baseline or whole-campaign qualification.

## Exact run

- Source: `167aa6d537b109bb229c231ddce4616974c4da71`, PokemonHnS-Development/pokehns-expansion.
- Build manifest: `[LOCAL_WORKSPACE]/_local/artifacts/repair-09-firered/manifest.json`; manifest SHA-256 `d76577e2d3f93b97b1c8f29d44f2623c84a784e9cc108205f478e7a05e28e949`.
- Target: `FIRERED`, maps `firered`, title `POKEMON FIRE`, `MODERN=1`, `TESTING=0`, ordinary O2 build. Build/wrapper exit codes both 0.
- Patch/config fingerprint: `656b49ab221989a12362bb1bbc9e24303e833274e33c7bde2ec9822056a97b44`; cumulative patch 0009 SHA-256 `bea352da2bf5aa726084e4b418933c82287101abd1621af7b58e49e8d6de6c82`.
- Tested fresh ROM: `[LOCAL_WORKSPACE]/_local/saves/firered/repair-09-native-01/firered-repair-09-native-01.gba`, 33,554,432 bytes; SHA-256 `74f90c6d019442adfb72d251720f749713e264b44066b6363de14c77b2ddaa40`.
- Session metadata: same directory, `session.json`. Private chronological evidence: `[LOCAL_WORKSPACE]/_local/evidence/native/repair-09-firered-native-01/observations.md`.
- Host: macOS 27.0 / Darwin 27.0.0 arm64; project-local official desktop mGBA 0.10.5. ARM GCC 14.2.1 build identity comes from the manifest.

## Emulator and observation limits

Native save location was inspected as the ROM directory. Load last state, Load cheats and periodic state autosave were all off. Normal target speed was 59.7275 FPS, audio sync on, video sync off, frameskip 0 and OpenGL display. Keyboard mappings were X=A, Z=B, Return=Start and arrows=movement. No BIOS, cheats, save states, debug grants/warps, prior saves or progress were imported.

Audio was muted at the owner's explicit request; both regular and fast-forward Mute were observed as 1, with SDL 44,100 Hz / buffer 1536. Codex did not unmute. Audio is **NEEDS OWNER TEST**. Viewed CUA images support the written observations; this report does not claim screenshot files exist on disk.

During setup, AX text clicks did not select settings panes; two coordinate attempts returned `noWindowsAvailable`, while refreshed keyboard navigation worked. ROM Open returned `timeoutReached`, but read-only refresh confirmed the exact owned ROM booted. Short title inputs initially did not reach the menu; ordinary Return held for 1,000 ms after cancelling settings reached the fresh New Game menu. These recovered tool/input observations are not attributed to an unknown actor or established as engine defects.

## Executed checklist

| ID | Result | Actual observation |
|---|---|---|
| FR-01 | PASS — EXECUTED | FireRed/Charizard title, fresh New Game-only menu, Oak identity intro, male CODEX, custom rival PATCH and actual Pallet player bedroom. Oak visibly confirmed “His name is PATCH!” Normal stairs, Mom dialogue and front-door exit to Pallet executed. |
| FR-02 | FAIL — EXECUTED | Oak naturally intercepted north departure, warned about tall grass and escorted the player into Oak's lab. The left ball displayed Bulbasaur; its normal confirmation/grant sequence executed. The visible message said CODEX received BULBASAUR from PROF.OAK, and the ball disappeared. The nickname screen then showed a question-mark species/name and ? icon. Empty OK retained the default name. PATCH received CHARMANDER normally. Start → POKéMON subsequently displayed “You have no POKéMON,” confirmed in two successive views. |
| FR-03 | BLOCKED | First rival battle was not attempted after the absent-starter failure. |
| FR-04 | BLOCKED | Bedroom/house/Pallet/lab transitions and Mom dialogue executed, but the required early route/Viridian/NPC coverage was not completed. |
| FR-05 | BLOCKED | Parcel/Dex progression was not executed. |
| FR-06 | BLOCKED | Wild battle, legitimate capture/healing and valid-party inspection depend on a starter. |
| FR-07 | BLOCKED | Start menu, trainer card, empty Party and initial Bag interface were observed; available Pokédex and valid-party coverage remain blocked. |
| FR-08 | BLOCKED | No normal save or cold Continue cycle was executed in the malformed state. |
| FR-09 | BLOCKED | No second save/cold reload or reward-persistence qualification. |
| FR-10 | BLOCKED | No conservative 600-second active-play qualification. Setup and displayed playtime do not establish it. Audio remains NEEDS OWNER TEST. |

## Failure state and stop

The last successful story step was the intended Oak escort and starter/rival grant dialogue. The actual party contained no Pokémon. The visible trainer card showed CODEX male, ID 54868, money 3,000, zero badges and playtime 0:06. Start showed 8:24 PM and later 8:25 PM. The initial Bag ITEMS pocket contained only CLOSE BAG. Pallet's exterior had a dark nighttime tint; no clock/campaign choice interface appeared before entering the world. These observations do not qualify broader day/night behavior.

The empty Party was confirmed twice in this one fresh session. A second fresh-session reproduction was not performed; source diagnosis is separate. No repair or workaround was applied by the GUI tester. On the parent's instruction, no normal save was made in the malformed state. The owned mGBA instance was fully quit with CmdQ; `pgrep -fl mGBA` returned exit 1 with no output, confirming process absence. Any emulator-created native file in this session is not evidence of a completed in-game save.

The FireRed native gate is **HOLD** on this exact ROM. Preserve this failure when evaluating any reviewed repair; successful compilation and campaign identity do not pass starter acquisition or persistence. Later target bytes require fresh qualification.

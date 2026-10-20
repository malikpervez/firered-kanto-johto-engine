# Repaired FireRed native smoke test — exact repair10 ROM

Codex executed a fresh desktop mGBA run on 2026-10-08/09, with UTC chronology and host timezone America/New_York. FR-01–09 passed the executed early-game checks, including two normal saves and cold Continue cycles. FR-10 remains **NEEDS OWNER TEST** for audible output because the owner requested muted sound; its input, visual and ten-minute active-play subchecks were executed. This run does not certify gyms, Sevii, later Kanto, a vanilla ruleset or compatibility with older saves.

## Exact run identity and settings

- Source: [PokemonHnS-Development/pokehns-expansion](https://github.com/PokemonHnS-Development/pokehns-expansion), commit `167aa6d537b109bb229c231ddce4616974c4da71`; repaired source, not pristine.
- Executed run: `firered/repair-10-native-01`, fresh New Game with no imported progress. Host macOS 27/Darwin 27, arm64; desktop mGBA 0.10.5.
- [Build manifest]([LOCAL_WORKSPACE]/_local/artifacts/repair-10-firered/manifest.json), SHA-256 `fbf75c3a47c21c88ad6633b0f6a176b131b797897ff8bdd19f4161966f0f671e`; GNU Arm 14.2.rel1/14.2.1, actual `make firered -j2`, make/wrapper exit0. Build evidence and the separate clean-repeat comparison are maintained by the build reports.
- [Session metadata]([LOCAL_WORKSPACE]/_local/saves/firered/repair-10-native-01/session.json), SHA-256 `d8209206fff966e14d554c0c15a744f61894e98ef2506570ccfb21d94fa36c11`.
- [Executed ROM]([LOCAL_WORKSPACE]/_local/saves/firered/repair-10-native-01/firered-repair-10-native-01.gba), 33,554,432 bytes, SHA-256 `3e504731d9dd3c02ec273dc257c86f557caaf8c9b933d2f0ff73558c2e121a39`.
- Patch/config fingerprint `32faeccdf41db77505858cd2981a070c7f835f0eee3180fe1563cb4c0e343f00`; cumulative [repair10 patch]([LOCAL_WORKSPACE]/patches/0010-firered-fresh-monotype-default.patch), SHA-256 `3e9b6b003557cbfacff59706ad04e4f7f2fdd58bc6162be995f91dc09742d5f3`.

The preserved [repair09 failure report]([LOCAL_WORKSPACE]/docs/firered-native-results.md) remains separate. That ROM entered Pallet but failed to retain its starter; no party/progression/save pass was transferred from it. This repair10 fresh run actually retained Bulbasaur and executed the downstream checks.

mGBA settings inspected in the preceding owned test session and retained here: SDL audio 44,100 Hz/buffer1536/volume256; normal and fast-forward Mute=1; OpenGL, frameskip0, native FPS target59.7275, audio sync on/video sync off. Load last state, load cheats and periodic save-state autosave were off; native saves used the ROM directory; no BIOS supplied. The owner's mute preference was preserved. Normal X/A, Z/B, Return/Start and arrows were used, without states, cheats, debug grants or warps. The FireRed game Options were inspected without changes: Fast text, battle scene ON, Shift, normal button mode, follower ON. This opening did not display the HnS challenge-options menu.

## Executed checks

| ID | Result | Actual observation |
|---|---|---|
| FR-01 | PASS — EXECUTED | Cold FireRed Charizard title/New Game; Oak/Nidoran introduction; male CODEX and rival PATCH named through normal grids and confirmations; actual Pallet bedroom/home/outside opening. |
| FR-02 | PASS — EXECUTED | Pallet north Oak trigger/escort/front lab; left Bulbasaur preview/Yes, ball removed, normal nickname screen and species name retained. Actual male BulbasaurLv5 HP19/19 in party; control returned. |
| FR-03 | PASS — EXECUTED | Initial PATCH battle entered naturally at lab exit. Bulbasaur5 versus Charmander5; actual loss after Tackle/Growl/Scratch. Rival victory dialogue/normal lab aftermath completed, rival left, field/exit resumed without retrigger or reset. A win was not asserted. |
| FR-04 | PASS — EXECUTED | Ordinary home2F↔1F↔Pallet, lab, Route1↔Viridian, Mart and Center transitions; NPC dialogue and normal ledge-gap/grass traversal. Navigation timing corrections used ordinary controls; no map defect established. |
| FR-05 | PASS — EXECUTED | Viridian Mart clerk gave Parcel; normal return/Oak handover/rival dialogue unlocked Dex and5 Balls. GUI Key Items empty afterward, Dex seen4/owned1 initially and Ball5. |
| FR-06 | PASS — EXECUTED | Natural Route1 Rattata/Pidgey battles and escape; weakened male Pidgey4 captured with one Ball, registered owned016;28EXP raised Bulbasaur6. Viridian nurse and later Mom normal-heal scripts executed; full party HP verified. |
| FR-07 | PASS — EXECUTED | Bag pockets, party/summary/skills/moves, trainer card, Options and available Kanto Dex opened without crash. Both owned entries and recorded interface deviations are below. |
| FR-08 | PASS — EXECUTED | Normal SAVE→Yes→saving→field; full CmdQ/process absence; cold same-ROM copyright/title/native Continue restored home checkpoint and compared identity/party/moves/inventory/money/Dex/event state. Oak revisit gave ordinary appraisal without opening replay. |
| FR-09 | PASS — EXECUTED | Continuing naturally obtained Route1 clerk Potion and changed location. Second normal save/full quit/cold Continue restored Route1/Potion and requested fields. Clerk revisit did not repeat the item award; Potion remained1. |
| FR-10 | NEEDS OWNER TEST | Audio remained muted/unheard. Active-play/input/visual subchecks PASS — EXECUTED: conservative600.9s measured actual ordinary play, responsive movement and no observed hang. FPS variation recorded below. |

The first wild Rattata battle returned to the field, but its individual faint/EXP text was not captured; this report does not invent that result. The Pidgey capture,28EXP/level6, party membership, Dex registration and later healing were individually observed. A Rattata3 encountered between saves was escaped normally, with Bulbasaur still21/21.

## Normal native save persistence

| Compared field | Cycle1 checkpoint/cold Continue | Cycle2 checkpoint/cold Continue |
|---|---|---|
| Identity | CODEX, male, ID12830, money3000, zero badges; PATCH named naturally and verified in preserved native backup | Same CODEX12830/money3000/zero badges/PATCH stored |
| Location/progression | PlayersHouse1F north of Mom; Parcel handed over/Dex/Balls completed. Saved home tile restored; Oak lab revisit had ordinary Dex appraisal, rival absent, exit without battle/reward sequence | Route1 north of clerk, beneath tree band; exact saved field position restored. One-time Potion event completed; clerk's postreward invitation only, no receipt replay |
| Party | Male Bulbasaur6 HP21/21; male Pidgey4 HP17/17 | Same species/levels/HP |
| Moves/PP | Bulbasaur Tackle35/35, Growl40/40; Pidgey Tackle35/35, Peck35/35 | Same moves/PP |
| Held items | Both NONE recorded before save1; Bulbasaur NONE explicitly viewed after cold1 | Both NONE explicitly viewed after cold2 |
| Inventory | Ball4; Medicine/Items/Key Items empty; Parcel absent | Potion1, Ball4; Items/Key Items empty/Parcel absent |
| Dex | GUI seen4/owned2;001Bulbasaur and016Pidgey owned markers retained | GUI seen4/owned2; both owned markers retained |
| Native Continue summary | CODEX/Dex2/time0:45/badges00 | CODEX/Dex2/time1:21/badges00 |

Only two normal persistence saves were made. Both cycles started from a fully quit emulator (`pgrep -x mGBA` exit1), a newly launched empty mGBA, the same dedicated ROM's copyright/Charizard title, and the game's native Continue. No auto-loaded state supplied the checkpoint. The second save used the normal overwrite confirmation for this dedicated test save. The Potion was acquired through the clerk's normal dialogue, not injected or imported. No additional normal save was made after the final cold reload.

Preserved backups, each131,088 bytes and mode0444:

- [cycle-01.sav]([LOCAL_WORKSPACE]/_local/saves/firered/repair-10-native-01/cycle-01.sav): `e33cb49c49ffcfba6571df8af084d8161f94338cbf0659b3bb8e9ea4454b8c27`.
- [cycle-02.sav]([LOCAL_WORKSPACE]/_local/saves/firered/repair-10-native-01/cycle-02.sav): `f1be6de058c04645a32ead45328ae5ecace9dfc038b45fb56880c6e614f06895`.
- Final active [native save]([LOCAL_WORKSPACE]/_local/saves/firered/repair-10-native-01/firered-repair-10-native-01.sav) after final CmdQ/process absence was whole-file equal to cycle02, same hash, zero differing bytes. Both backup hashes remained unchanged.

Independent read-only strict/raw inspections accepted each preserved backup using the actual compiled repair10 field map/manifest. Cycle1 selected bank1/counter1/rotation1; cycle2 selected bank0/counter2/rotation2, with the previous bank still valid. All14 selected native payload checksums were valid. Stored CODEX/visibleID12830/PATCH at FireRed SaveBlock1 offset15720, Dex4/2 (caught National1/16) and party count2 persisted. Native inspection supplements rival-name/Dex evidence; it does not replace GUI health/moves/location/progression or infer fields it did not decode.

## Active play, deviations and limitations

After build jobs were idle,13 bounded Pallet movement blocks executed180 alternating directional holds of3500ms on the observed clear row14 lane. Excluding200ms turning/settling allowance per hold yields594s. Earlier individually measured movement/command actions add6.9s, for600.9s total. West flowerbed-side/east lab-side endpoints were viewed; short endpoint alignment was excluded. A measured Up attempt against the lab wall was wholly excluded. Setup, paused time, stationary reading, model/tool/API waits and all unmeasured past gameplay were excluded; neither wall-clock duration nor the game's accumulated playtime is presented as active time. Timing stopped at the required threshold.

Active-block AX FPS snapshots ranged50.8–60.6, generally around59–60; an earlier menu snapshot reached44.6. Movement remained responsive with no observed hang. These readings do not establish constant60FPS or explain a cause; no tuning was attempted. CUA occasionally captured fades or short inputs before transitions completed; fresh snapshots and normal controls resolved those observations. An accidental normal Mom-heal interaction while closing menus was excluded from timing; HP had already restored before that interaction. No actor identity was inferred from external-change guards.

Observed departures from vanilla FireRed include the visible clock/night-blue outdoor palette, Bulbasaur follower, expanded Bag Medicine/Berries pockets and expanded summary stats/EV/IV controls. Pidgey's early moves included Peck; its party context offered Fly, which was not invoked or qualified. This is an Expansion-based FireRed campaign smoke run, not vanilla mechanical fidelity certification. Later maps, gyms, Sevii, all time-dependent events and cross-version/native-save migration remain untested here.

Private evidence: [chronological observations]([LOCAL_WORKSPACE]/_local/evidence/native/repair-10-firered-native-01/observations.md), [active-input ledger]([LOCAL_WORKSPACE]/_local/evidence/native/repair-10-firered-native-01/active-inputs.json), [cycle1 record]([LOCAL_WORKSPACE]/_local/evidence/native/repair-10-firered-native-01/cycle-01-backup.json), [cycle2 record]([LOCAL_WORKSPACE]/_local/evidence/native/repair-10-firered-native-01/cycle-02-backup.json), [final save comparison]([LOCAL_WORKSPACE]/_local/evidence/native/repair-10-firered-native-01/final-save-comparison.json), and [native inspection directory]([LOCAL_WORKSPACE]/_local/evidence/native/repair-10-backup-inspections). Screenshots were viewed in CUA tool results; no disk screenshot files are claimed.

mGBA was fully quit at completion. Owner audible-output observation is the remaining FR-10 component. No further native gameplay or later milestone was started.

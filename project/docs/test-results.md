# B0 test results — approved save experiment

**Owner update — October 9, 2026:** Audio is **PASS — OWNER-REPORTED** for the current B0 evaluation. See the [owner audio confirmation](decisions/2026-10-09-b0-owner-audio.md) for attribution and scope. This later confirmation supersedes earlier audio-pending statements below; Codex did not perform a new listening test. The prior frozen audit and native reports remain historical evidence. B0 remains HOLD for review of the four-byte save margin and FireRed roamer fidelity defect.

Tester: Codex, October 8–9, 2026 (America/New_York; evidence timestamps UTC), native arm64 macOS 27.0. Source pin `167aa6d537b109bb229c231ddce4616974c4da71`; latest complete experimental patch 0010 SHA-256 `3e9b6b003557cbfacff59706ad04e4f7f2fdd58bc6162be995f91dc09742d5f3`; patch/config fingerprint `32faeccdf41db77505858cd2981a070c7f835f0eee3180fe1563cb4c0e343f00`. Build evidence is in `docs/build-report.md`, experimental ABI/stop analysis in `docs/firered-save-experiment.md`.

## Environment/build acceptance

| ID | Result | Evidence / limit |
|---|---|---|
| ENV-01 | PASS — EXECUTED | Independent B control Git/root inspected; no Workstream A changes. |
| ENV-02 | PASS — EXECUTED | Actual host/tools recorded; local locked dependencies, no global installation. |
| SRC-01 | PASS — EXECUTED | Required instructions and pinned upstream guidance read; exact source retained pristine. |
| SRC-02 | PASS — EXECUTED — review only | Notices/credits/publication boundaries reviewed; unresolved rights remain open. |
| BUILD-FR | PASS — EXECUTED: compilation only | Final clean 010 make/wrapper 0, actual FireRed ROM/ELF/map preserved. Earlier failures unchanged. |
| BUILD-HNS | PASS — EXECUTED: compilation only | Final clean 010 make/wrapper 0, actual HnS ROM/ELF/map preserved. |
| BUILD-REPEAT | PASS — EXECUTED | Both 010 fresh repeats reproduce ROM/ELF/map/config/env/source/generated records; all make/wrapper 0. |
| BUILD-MANIFEST | PASS — EXECUTED | Actual source/config/patch/tool/log/exit/output hashes preserved for every attempt. |
| CAPACITY-01 | PASS — EXECUTED — measurement only | Actual 010 ARM FireRed 15,868/15,872 (4 free); all measured other-target members match 009/approved 004. Successful linker allocations recorded. |
| GIT-01 | PASS — EXECUTED — preliminary boundary audit | 762/762 checks, real exit 0; no staged/tracked/remotes; listed control files are text and private paths ignored. Frozen final inventory result is recorded separately below. |

Independent preliminary boundary evidence: `_local/evidence/repair-analysis/final-audit-preparation/preliminary-02.json`, SHA-256 `7070ea1de9494acc7388f73dd9b52b2a6559be2cdfef980572fde901e8d2bf5e`. All 37 control and 443 private records passed. Both final active native saves matched cycle 2 byte for byte, with stable hashes/metadata and targeted mGBA absence before and after comparison. The first failed audit and heading trace remain preserved; restoring only the historical FireRed report's original heading resolved its sole mismatch without changing test results. The [frozen final boundary inventory/result](../_local/evidence/b0-save-experiment-final-boundary-audit.json) records the completed pre-audio-confirmation snapshot; later owner-audio documentation updates are outside that frozen inventory. Pre-update reports are preserved under `_local/evidence/reports/pre-owner-audio-confirmation/`.

## Current FireRed 010 native checklist

Actual successful ROM: `[LOCAL_WORKSPACE]/_local/artifacts/repair-10-firered/pokefirered.gba`, SHA-256 `3e504731d9dd3c02ec273dc257c86f557caaf8c9b933d2f0ff73558c2e121a39`. The separate fresh session at `_local/saves/firered/repair-10-native-01/` cold-booted this exact ROM through the FireRed Charizard title/New Game-only menu, then naturally completed male CODEX/PATCH identity, Pallet home and Oak escort. FR-01 and FR-02 are PASS — EXECUTED: natural left-ball Bulbasaur selection showed the correct BULBASAUR nickname grid and an actual male level-5 party member HP 19/19. The historical empty-party failure did not recur. FR-03 passed through an ordinary rival loss, normal aftermath and lab exit without replay. Route 1/Viridian, Mart and Center transitions/healing executed; Parcel delivery unlocked the Dex (seen 4/owned 1) and five Balls, with Parcel removed. A male level-4 Pidgey was naturally captured using one Ball; capture experience raised Bulbasaur to level 6. Full-party healing and checkpoint menus executed. Save 1 and its full cold-restoration comparison passed. The second normal-save/cold-reload comparison also passed. The measured visual/input check reached 600.9 active seconds; audio is now PASS — OWNER-REPORTED. No 009 progress/save was carried over. Full executed checks are recorded in `docs/firered-repaired-native-results.md`.

| ID | Current result | Executed observation / limit |
|---|---|---|
| FR-01 | PASS — EXECUTED | FireRed/Charizard/Oak opening, CODEX/PATCH naming and Pallet world. |
| FR-02 | PASS — EXECUTED | Oak escort, natural Bulbasaur choice and actual party member. |
| FR-03 | PASS — EXECUTED | Ordinary initial rival loss, normal aftermath and lab exit without replay. |
| FR-04 | PASS — EXECUTED | Home/lab/Mart/Center interiors, Pallet/Route 1/Viridian transitions and ordinary NPC dialogue. |
| FR-05 | PASS — EXECUTED | Parcel delivery, Dex unlock and five Balls; Parcel removed. |
| FR-06 | PASS — EXECUTED | Wild battle, natural Pidgey capture, experience level-up, Mother full-party healing and party inspection. |
| FR-07 | PASS — EXECUTED | Trainer card, party summaries/moves, Bag and Dex owned entries inspected without crash. |
| FR-08 | PASS — EXECUTED | Normal Save 1/full quit/cold Continue restored the checkpoint. Oak revisit gave ordinary Dex appraisal; no rival/starter/reward replay. |
| FR-09 | PASS — EXECUTED | Changed Potion/location checkpoint retained through normal Save 2/full quit/cold Continue. Clerk revisit gave no duplicate Potion. |
| FR-10 | PASS — visual/input executed; audio owner-reported | Visual/input subcheck PASS — EXECUTED: 600.9 conservative measured active seconds, responsive/no visible hang. Timed FPS snapshots 50.8–60.6; earlier menu 44.6 separately observed. Audio was muted/unheard by Codex; later owner confirmation supplies the audio result. |

Save 1 checkpoint: male CODEX, visible ID 12830, money 3,000, zero badges; male Bulbasaur level 6 HP 21/21 (Tackle 35/35, Growl 40/40) and male Pidgey level 4 HP 17/17 (Tackle 35/35, Peck 35/35), both held NONE. Dex seen 4/owned 2 with owned 001/016; four Balls, empty Medicine/Key Items, Parcel removed. Location: player's house 1F north of Mother at (8,3). Immutable backup `cycle-01.sav` is 131,088 bytes, SHA-256 `e33cb49c49ffcfba6571df8af084d8161f94338cbf0659b3bb8e9ea4454b8c27`. Strict/raw inspections exited 0, selected bank 1/counter 1/rotation 1, all 14 signatures/IDs/payload checksums valid, stored CODEX/12830/PATCH/Dex 4/2/party count 2 agreed. Rival PATCH uses actual shifted SaveBlock1 offset 15,720. Inspections supplement rather than substitute for full GUI restoration; raw position/location/flags/vars are not semantic progression decoding. The first unused bank is uninitialized. Actual cold Continue restored the requested visible checkpoint. Oak revisit gave an ordinary four-seen/two-owned appraisal; rival absent and lab exit passed without starter/battle/reward replay. Held-item comparison granularity: both NONE before Save 1, Bulbasaur NONE explicitly viewed after cold 1, and both NONE explicitly viewed after cold 2; no separate Pidgey held-item view after cold 1 is claimed. The second cycle is separately recorded below.

Save 2 was written normally after the Route 1 clerk's legitimate Potion gift, at the tile immediately north of the clerk. Potion 1 replaced an empty Medicine pocket; trainer/money/party/Dex remained unchanged. Immutable `cycle-02.sav` is 131,088 bytes, SHA-256 `f1be6de058c04645a32ead45328ae5ecace9dfc038b45fb56880c6e614f06895`. Strict/raw inspections exited 0 with unchanged inputs, selected bank 0/counter 2/rotation 2 and all 14 payload checksums valid; the prior bank 1/counter 1 is also valid. Stored CODEX/12830/PATCH/Dex 4/2/party count 2 remained unchanged. Actual cold Continue restored the Route 1 tile and all recorded identity/money/party/moves/PP/held-item/Dex/Bag fields. The clerk gave only postreward dialogue; Potion stayed 1 with no receipt replay. Codex then fully quit mGBA, with process absence confirmed and no third normal save. The tester's final active save exactly equals cycle 2, including its complete 128 KiB native flash and retained 16-byte suffix; backups stayed unchanged. Independent V4 preliminary comparison executed and confirmed full-file identity, zero differing offsets and stable inputs with mGBA absent. SaveBlock3 extra/footer and the suffix are outside payload checksums; no suffix decoding/cause or old-save compatibility is claimed.

Preserved 009 runtime: FR-01 PASS — EXECUTED; FR-02 FAIL — EXECUTED, natural Bulbasaur grant text followed by question-mark nickname/icon and empty party, confirmed twice. FR-03–FR-10 BLOCKED. No normal save or persistence pass. Exact 009 ROM `74f90c6d019442adfb72d251720f749713e264b44066b6363de14c77b2ddaa40`, failure report `docs/firered-native-results.md`; untouched private session/evidence retained. 010 initializes existing FireRed fresh-default OFF 31 without changing the filter, starter scripts or layout. Source diagnosis and successful build do not pass native tests.

## Final patched HnS native results

Actual final HnS ROM: `[LOCAL_WORKSPACE]/_local/artifacts/repair-10-hns/pokehns.gba`, SHA-256 `4bb58fe3c06bc0b60146aa946cbc34f087efa607f525f68e0a1e99c0db9cde75`. The separately completed fresh 009 session tested these exact bytes: the executed 009→010 comparison found zero differing ROM bytes, with identical ELF/map. Its original 09 session/manifest remains intact; no save was imported or metadata rebound. Full native report: `docs/hns-patched-native-results.md`.

| ID | Result | Executed observation / limit |
|---|---|---|
| HNS-01 | PASS — EXECUTED | CODEX/New Bark opening, default Recommended choices and clock setup. |
| HNS-02 | PASS — EXECUTED | Natural Cyndaquil starter, Elm task/contact and aide Potion. |
| HNS-03 | PASS — EXECUTED | Mr Pokémon/Oak errand, Silver battle/aftermath, police PATCH name, Egg handover, five Balls and departure. Two legitimate losses/recovery preceded normal training and the successful third battle. |
| HNS-04 | PASS — EXECUTED | New Bark/Route 29/Cherrygrove/Route 30 transitions; home/lab/Center/Mr Pokémon interiors and NPCs. Cherrygrove Mart interior specifically NOT RUN. |
| HNS-05 | PASS — EXECUTED | Wild battles, natural female Rattata capture and full-party healing. |
| HNS-06 | PASS — EXECUTED | Bag/party/Dex/identity and observable clock/settings inspected. Broader RTC/day-night regression NOT RUN. |
| HNS-07 | PASS — EXECUTED | Normal Save 1 → full quit/absence → cold title/native Continue; requested checkpoint retained. |
| HNS-08 | PASS — EXECUTED | Natural Potion pickup at a different map → normal Save 2 → full quit → cold Continue; changed checkpoint retained without duplicate pickup. |
| HNS-09 | PASS — visual/input executed; audio owner-reported | Visual/input subcheck PASS — EXECUTED: 601.2 conservative active seconds (668 held-control seconds), responsive/no visible hang. Displayed FPS snapshots 33.6–60.4; cause unestablished, constant full speed not claimed. Audio was muted/unheard by Codex; later owner confirmation supplies the audio result. |

Both cold cycles retained CODEX/visible ID 42606/money 3,220; male Cyndaquil level 7 HP 23/23 (Tackle/Leer) and female Rattata level 3 HP 15/15 (Tackle/Tail Whip), moves/PP/held items; Dex seen 5/owned 2 with both owned entries; four Balls, EXP. SHARE/GB PLAYER and absent Mystery Egg. Rival PATCH was naturally named and independently confirmed in both immutable native backups. First reload restored the Elm healing-machine tile and normal lab exit did not replay police/aide rewards. Second restored the Route 29 Potion-clearing tile and Potion 1 rather than an empty Medicine pocket; the collected ball stayed absent. The first moves were observed directly; no runtime Smokescreen acquisition is inferred from a source learnset aid.

| Immutable native backup | Bytes | SHA-256 | Selected bank/counter/rotation |
|---|---:|---|---|
| `_local/saves/hns/repair-09-native-01/cycle-01.sav` | 131,088 | `9c340868da9bcfd3c9f10032284e74a4e2497d70b186bfd48e224460a2a373b0` | 1 / 1 / 1 |
| `_local/saves/hns/repair-09-native-01/cycle-02.sav` | 131,088 | `a3a590c19b4215fc4f98cb23e7e808d0995a5b50fc68e16c43285417f2354822` | 0 / 2 / 2 |

Read-only strict/raw inspections of each backup exited 0 with unchanged inputs; all 14 selected signatures/IDs/rotation/parity/payload checksums were valid. Stored CODEX/ID 42606/PATCH, Dex seen 5/caught 2 and party count 2 agree with these early GUI observations; raw Dex counts are not generally identical to filtered regional UI counts. Raw position/location/map-layout and flags/vars are supplemental bytes, not semantic story decoding. SaveBlock3 extra/footer and the retained optional 16-byte emulator suffix are outside those payload checksums; no suffix interpretation is claimed. Evidence: `_local/evidence/native/repair-09-hns-native-01/` and `repair-09-backup-inspections/`. After the second comparison the GUI tester fully quit mGBA and reported the final active save whole-file hash equals cycle 2. Independent V4 preliminary comparison executed and confirmed full-file identity, zero differing offsets and stable inputs with mGBA absent. Official local mGBA 0.10.5; human audio instructions remain in `docs/native-test-procedure.md`.

## Historical pristine/partial runs

Pristine HnS ROM `7ffd0c7572f0542f60381ec776d99f4e826ae2859d56403e56bcc82effcd88df` passed HNS-01 through HNS-08, two normal saves/cold reloads and 607.4 seconds measured movement; audio NEEDS OWNER TEST. Full original results remain in `docs/hns-native-results.md`, with unchanged baseline backups. These passes do not qualify patched 008. Patched 003's partial campaign-menu session was stopped before world entry and normal saves; it does not pass the checklist.

B0 recommendation remains HOLD. Compiled-caller review narrowed the initial shared-TM stop; final 009 preserves selected FireRed/shared behavior and both clean targets now compile. FireRed 009 native acceptance failed at the starter and remains preserved. Both 009 clean repeats passed. The reviewed narrow FireRed fresh-default correction 010 compiled successfully; both 010 clean repeats passed. The separate exact-ROM HnS regression passed its early-game and two-save checks; audio is covered by the owner-reported confirmation. Fresh FireRed 010 passed FR-01–09, including both normal-save/full-quit/cold-Continue cycles. FR-10 visual/input passed at 600.9 measured active seconds; its audio is PASS — OWNER-REPORTED. Four-byte headroom and the FireRed roamer fidelity defect remain open. No B1/merge/production-save/remote work is authorized.

Patched 008 partial natural play reached Elm return/police PATCH entry/aide Ball event but was stopped before normal saves, cold cycles and dedicated active timing when final 009 produced a different ROM hash. Its private observations remain preserved and do not qualify final 009.

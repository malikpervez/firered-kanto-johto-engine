# B1 browser results — partial at owner stop

**B1 is ready for review. Browser qualification remains partial.** The owner stopped extended testing to prioritize implementation. No further gameplay testing is scheduled or running. [Owner direction](decisions/2026-10-09-b1-owner-test-stop.md).

## Exact candidate and environment

Executed `@thenick775/mgba-wasm` **2.5.1**, acquired from the npm registry with package integrity and registry signature verification. Published package Git head is `e974b288bd7e5cfc7c7b96f8b4d32b673ddfb68c`, distinct from the earlier assessed source `d5e226c63725f79bc96c7f75e2c8cbf07af9f2cd`. The runtime reports `v2.5.0-7-ge974b288bd7e5cfc7c7b96f8b4d32b673ddfb68c`, branch `feature/wasm`, project version `v2.5.1`. Package verification does not establish a reproducible source build or build attestation.

| File | SHA-256 |
|---|---|
| Published package archive | `d35eeb76eabea7fea39a943641eef1db708f523041ee55016b1cf3fdec6b8203` |
| `dist/mgba.js` | `98e6f460fa2f95846bf79c3b1c42ecf3acca0ce11937ba0d4aa693438402a473` |
| `dist/mgba.wasm` | `c4c647d455840df684396b0a03833c1c2332793b73fabbba37d64323ad0c4c8d` |
| Final private harness JS | `adfe9002fb75abe880bad4f147efc11596f8529de498175158d3d95ffa6e1e7c` |

Chrome reported `154.0.0.0` on macOS arm64. The private server bound only `127.0.0.1:52477`, supplied cross-origin isolation headers, and served an explicit harness/runtime allowlist. ROMs and saves were selected locally and never served by HTTP. No A repository or service was inspected or changed. No production browser wrapper was implemented.

The harness requested rewind, state autosave and automatic state restoration **off** before loading. The API has no general settings getter; this is a requested-setting record, supported by empty cheat/patch/state/autosave directories and zero observed automatic-state callbacks. Fast-forward multiplier was 1, frame skip 0 and FPS target 60. No cheats, states, debug grants, host-clock changes or byte conversions were used.

## Executed scope

These were copies of B0's disposable native fixtures, not personal saves or a new browser opening/starter playthrough. Both prepared ROMs match final 010. Only FireRed was executed in the browser before the owner stopped testing.

| Check | FireRed | HnS |
|---|---|---|
| Runtime boot, target title, native import and Continue | PASS — EXECUTED | NOT RUN — owner deferred |
| Restored party, Pokédex, items, trainer ID, money, badges | PASS — EXECUTED for the recorded fixture | NOT RUN — owner deferred |
| Movement, menus, map transition and early wild battle | PASS — EXECUTED | NOT RUN — owner deferred |
| First normal save and cold tab reopening | PASS — EXECUTED | NOT RUN — owner deferred |
| Second normal save/export | PASS — EXECUTED; second cold reopening NOT RUN | NOT RUN — owner deferred |
| Refresh persistence | NOT RUN — owner deferred | NOT RUN — owner deferred |
| Native → browser → native desktop round trip | PARTIAL: native → browser executed; desktop return NOT RUN | NOT RUN — owner deferred |
| Measured ordinary speed | Executed samples approximately 60 FPS; limits below | NOT RUN — owner deferred |
| Audio output and listening | PASS — EXECUTED PCM capture; PASS — OWNER-REPORTED for that sample | NOT RUN — owner deferred |
| Effective focus/blur release test | NOT RUN: attempted app switch recorded no browser focus event | NOT RUN — owner deferred |
| RTC/night palette | Limited observation executed; broader qualification NOT RUN | NOT RUN — owner deferred |

FireRed restored CODEX, trainer ID 12830, money 3000, zero badges, Bulbasaur level 6 HP 21/21 and Pidgey level 4 HP 17/17, Potion ×1 and Poké Balls ×4. Pokédex showed four seen/two owned. Rival `PATCH` and story flags were verified by read-only save inspection; the rival was not encountered again in this browser session.

The trainer walked Route 1 → Pallet Town → Route 1, encountered and defeated a level-3 Rattata through ordinary battle menus, and saved with Bulbasaur HP 18/21. A fresh tab at the same origin initialized a fresh runtime, loaded persisted files without reimport, selected Continue, and displayed that saved health. The second cycle used the Potion normally: the game reported three HP restored and showed 21/21. A second normal Save was executed and exported after quit/sync. Both exports passed strict bank, sector and checksum inspection.

This cold reopening terminated and recreated the test tab/core, **not the user's entire Chrome process**. No browser-process restart is claimed. Two saves and one cold reopening must not be reported as two save/reload cycles.

## Save evidence

All files are 131,088 bytes: the full 128 KiB flash plus 16-byte emulator RTC trailer. Bytes were preserved without truncation/conversion. The trailer changed naturally on export and remains outside ordinary payload checksums.

| File | Selected counter | SHA-256 |
|---|---:|---|
| FireRed `native-input.sav` | 2 | `f1be6de058c04645a32ead45328ae5ecace9dfc038b45fb56880c6e614f06895` |
| FireRed `browser-export-01.sav` | 3 | `d191a97ecfb52a08d63134a4fcaae6021102e2c21e5240c45d044516ad079b0f` |
| FireRed `browser-export-02.sav` | 4 | `d5edcbb4b3a1fcc47ae295e35901b87f69c1e60eeeff2a47eed4e014ee5c1f13` |
| HnS `native-input.sav`, prepared only | 2 | `a3a590c19b4215fc4f98cb23e7e808d0995a5b50fc68e16c43285417f2354822` |

Both exported FireRed banks had all 14 payload checksums valid with coherent IDs/generation. Identity, rival, Pokédex and party count were retained. First-save position/party/variable changes correspond to gameplay. Between exports, flags, variables, location/position/layout, roamer, storage and existing SaveBlock3 records matched; party and encrypted bag/money bytes changed. Encryption rotation makes raw ciphertext equality unsuitable for money/item acceptance; the GUI observations above supply that evidence. Original B0 ROMs/saves and copied inputs were verified unchanged. No native-return save was created.

## Speed, audio, RTC and defects

After correcting excessive private harness logging, the first measured session had 382 complete sample seconds averaging 60.000 FPS (58.983–61.030); the cold-reopened session had 386 complete seconds averaging 59.9999 FPS (59.768–60.194). Initialization boundary samples are retained separately. These periods include menus, input gaps and gameplay, not an uninterrupted active-play or long-session qualification. Both recorded one save callback each and zero crash/automatic-state callbacks. No focus transition was captured, so focus behavior remains unqualified.

Actual output PCM was captured upstream of the runtime-local muted speaker gain, preserving the original audio callback. The WAV contains 5.056 seconds, stereo PCM16 at 16 kHz, nonzero samples and no samples at the clipping rails. The owner listened and reported “Sounds normal.” This does not qualify HnS or long-session audio. FireRed's Start clock was observed at 10:41 PM and later 10:48/10:51/10:52 PM with a night palette; day boundaries, daily events, encounter schedules, timezone changes and all reload clock behavior remain untested.

Emulator `GAME ERROR` logs were retained, including invalid startup DMA/video register accesses, BIOS loads, unsupported serial writes and a flash-reset write. The first measured session recorded 57 such entries; the reopened session recorded 36. No visible crash or invalid inspected save resulted. Their cause/impact is unresolved; this is not an error-free runtime claim.

Two harness evidence problems were corrected without changing game/runtime binaries: verbose per-frame logs distorted instrumentation, and `canvas.toBlob` exported blank images. Original JS, complete diffs and syntax exits are preserved. The documented core screenshot API produced a valid party image, visually inspected locally. Blank exports are retained and excluded as visual proof.

The four-byte FireRed main-save margin, roamer fidelity defect, disabled original interfaces, full campaigns, crowded-map support and save-format compatibility remain open. The 010 baseline and frozen C handoff were not altered.

## Exact local paths and repeat instructions

Workspace root: `[LOCAL_WORKSPACE]`.

- Runtime: `_local/browser/b1-browser-01/runtime/`; acquisition report: `_local/evidence/b1/browser-01/runtime/ACQUISITION_REPORT.md`.
- Harness and manifest: `_local/browser/b1-browser-01/harness/`.
- Server request/start log: `_local/evidence/b1/browser-01/server.log`; stopped-session receipt: `_local/evidence/b1/browser-01/stop-receipt.json`.
- Save inputs/exports: `_local/saves/firered/b1-browser-01/`; HnS prepared inputs: `_local/saves/hns/b1-browser-01/`.
- Downloads/screenshots/WAV/session evidence: `_local/evidence/b1/browser-01/downloads/`.
- Save inspections/comparisons and unchanged-input verification: `_local/evidence/b1/browser-01/saves/`.
- Runtime analysis: `_local/evidence/b1/browser-01/firered-cycle01-runtime-analysis.json` and `firered-cycle02-runtime-analysis.json`; audio: `firered-audio-analysis.json`.

Testing is stopped. If separately resumed, start the saved loopback harness with `python3 -u _local/browser/b1-browser-01/harness/server.py --port 0`, open its printed URL, select the exact 010 ROM and a newly named copy of the intended native save, and record the new origin. A newly assigned port creates a new storage origin; old persistence results cannot transfer to it. Follow the remaining procedure in [the runtime assessment](b1-browser-runtime-assessment.md), without overwriting preserved fixtures. Do not restart these tests automatically.

**Recommendation:** retain the candidate for local development evaluation. Defer unfinished browser qualification at the owner's direction and review the bounded implementation proposal. No player-release, A-integration or full browser-compatibility approval is implied.

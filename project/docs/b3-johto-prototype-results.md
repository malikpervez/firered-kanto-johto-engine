# Playable Johto quest — build and native results

**October 13, 2026. Status: final build PASS; native quest, reward, cold reload and return to Kanto PASS — EXECUTED.** The [bounded requirements](b3-johto-prototype-requirements.md) and [owner direction](decisions/2026-10-13-playable-johto-direction.md) govern this development slice. The journey began on `0021` and continued on final `0022` after the exact two-file map-display repair; bindings below keep those executions distinct.

The implementation retains the existing FireRed trainer and Kanto/Sevii campaign and adds Elm's lab, Route29, Cherrygrove and basic town interiors. Elm requests a Guide visit, then awards one Potion after the trainer returns. Johto quest state uses content2 inside the unchanged native6/FRJS1/layout1 save foundation. HnS's eight-gym story is not imported by this small quest.

## Candidate and reproducibility

Current source is complete [0022](../patches/0022-firered-johto-map-labels.patch), applied alone to upstream commit `167aa6d537b109bb229c231ddce4616974c4da71`. SHA-256: `a22ab3754f92763e97c724ccd918c6fc34af200d38afbd7f89eb378220745e84`. The patch includes the approved foundation and B2 changes; do not stack complete patches. [Source freeze03](../_local/evidence/b3-johto-01/source-freeze-03.json), SHA-256 `4e1b9dfb5b2476664226d59f6152b1e735278c01ce25b8b2e60bafb9ee8f3b4d`, binds all 96 patched source files: 91 tracked modifications and five new code files.

The prior successful `0021` candidate remains preserved: complete patch SHA-256 `468007f14ceffa9683a4b9ea277803ab97527d74337751524b018239ed4ad442`, [source freeze02](../_local/evidence/b3-johto-01/source-freeze-02.json) SHA-256 `419c5a67c39686e3aa82a8ac2459eb493ad510b270cb40172fb9fbca29be852f`, ROM SHA-256 `e6904e926c72c9e39a9c1f6560c03745c2570d247e46c905da29031cdc1abc1e`.

The first fresh attempt used complete [0020](../patches/0020-firered-johto-errand-prototype.patch), SHA-256 `35f8f369ec975bd0b1bd4d5bd31f36e56f3e5d23163a612ce2c92dc370e5bd89`. Its [source freeze01](../_local/evidence/b3-johto-01/source-freeze-01.json), logs and [failed manifest](../_local/artifacts/b3-01-firered-firered/manifest.json) are retained. Make/build and wrapper exited **2** on undefined `OBJ_EVENT_GFX_POKEMART_CLERK`. `0021` changes only the FireRed Mart map actor identifier to existing `OBJ_EVENT_GFX_CLERK` (290); no graphics bytes were added or altered.

Executed first fresh build invocation:

```sh
source _local/tools/activate.sh
python3 scripts/build.py --target firered --run-id b3-01-firered --jobs 2 --patch patches/0020-firered-johto-errand-prototype.patch
```

The wrapper created `_local/artifacts/b3-01-firered-firered/` and `_local/evidence/builds/b3-01-firered-firered/`, preserving configuration, source, stdout/stderr and actual failure exits. After the single JSON correction, the same isolated target tree resumed with the same command, environment and retained outputs; b3-02 / `0021` exited **0**. The subsequent b3-03 / `0022` resumed command also exited **0**, with wrapper exit **0**. These are executed successful corrected builds, **not second clean builds or clean-repeat qualifications**.

The retained [b3-02 manifest](../_local/artifacts/b3-02-firered/manifest.json), SHA-256 `3fc40df886ff93b974aea18d374f77259d83b301db47c777b0e9f67c01c51ae1`, binds the clerk repair and original failed attempt. The final [b3-03 manifest](../_local/artifacts/b3-03-firered/manifest.json), SHA-256 `99c720a30954e8ecaa716d9d4afa8d1e5286a1c68a0a26856b461aa8857dcfd2`, binds `0022`, exact source hashes before/after the repair and after build, actual exits, sanitized environment and artifacts. Its [build log](../_local/evidence/builds/b3-03-firered/build.log) SHA-256 is `1a3acc456db6d69c9b838ed47020f92c21e895e66cb57c3d577d1a697bbdd848`. The actual command remained identical for both resumed builds:

```sh
# Executed in _local/worktrees/b3-01-firered-firered/
[LOCAL_WORKSPACE]/_local/tools/host/bin/make firered -j2 TOOLCHAIN=[LOCAL_WORKSPACE]/_local/tools/arm-gnu-toolchain-14.2.rel1-darwin-arm64-arm-none-eabi
```

Configuration remains `BUILD=firered`, `GAME_VERSION=FIRERED`, `MAP_VERSION=firered`, title `POKEMON FIRE`, game code `BPRE`, `MODERN=1`, `TESTING=0`, `-DFIRERED`, ARM GNU 14.2.1, optimization `-O2`; test/debug/release/LTO remain 0. No flags were invented or errors suppressed for this correction.

`0022` changes only `src/region_map.c` and `src/map_name_popup.c` relative to `0021`. It admits existing Route 29 / Cherrygrove IDs to FireRed's map-name lookup and routes all three appended Johto sections through the existing wood popup theme. This corrects `???????` names and avoids indexing beyond the legacy popup-theme table. The [two-file correction freeze](../_local/evidence/b3/map-name-popup-repair-01/source-freeze.json) and b3-03 preflight preserve the before/after hashes. Complete-patch pristine-pin check and two-file delta check/apply all exited 0. All other `0021` source hashes match, including quest, codec, save-layout/coordinator, map-order and asset dependencies. The frozen `0019` native structure/coordinator files remain byte-identical. No asset bytes or persistent content identity changed.

| Final b3-03 / `0022` output | Bytes | SHA-256 |
|---|---:|---|
| [pokefirered.gba](../_local/artifacts/b3-03-firered/pokefirered.gba) | 33,554,432 | `39b023532a1cd657633970777ca108b74382b1239d197756a36a32c8fcd1bd91` |
| [pokefirered.elf](../_local/artifacts/b3-03-firered/pokefirered.elf) | 41,240,768 | `8f67a13d2f3352f07594708ce18783b9646076fcbe45a36a411a84e7d5d29e00` |
| [pokefirered.map](../_local/artifacts/b3-03-firered/pokefirered.map) | 4,992,358 | `bc8dbe30c04cd87c8745dbd32f3301041428f4bcfd75e4b97658713cc0faacc8` |

| Linked region | Final05 foundation | b3-02 / `0021` | Final b3-03 / `0022` | Change from final05 |
|---|---:|---:|---:|---:|
| EWRAM | 254,488 | 254,488 | 254,488 | 0; 7,656 bytes of linker-region headroom |
| IWRAM | 25,940 | 25,940 | 25,940 | 0 |
| Linked ROM content | 29,946,932 | 29,995,268 | 29,995,300 | +48,368 bytes; map-label correction adds 32 |

These are actual linker totals, not runtime peaks or a measured B3 save interval. The GBA output remains padded to 32 MiB. Save allocations and stored reserve are unchanged.

The following independent clean `0022` reproduction command is prepared, **NOT RUN**. It uses a new isolated run ID and the normal logging wrapper; it is not an additional scheduled acceptance test. The earlier clean `0021` reproduction also remains NOT RUN:

```sh
source _local/tools/activate.sh
python3 scripts/build.py --target firered --run-id b3-clean-0022 --jobs 2 --patch patches/0022-firered-johto-map-labels.patch
```

No full B3 HnS build or additional clean repeat has been executed.

## Focused checks

| Check | Actual status |
|---|---|
| Patch applies to the clean pin | PASS — EXECUTED, exit0 |
| Source layout/coordinator/order/heal preservation | PASS — EXECUTED, seven baseline files byte identical; [private comparison](../_local/evidence/b3-johto-01/layout-source-preservation.json) |
| Real C codec | PASS — EXECUTED, 39 focused assertions with ASAN/UBSAN; [result02](../_local/evidence/b3-johto-01/codec/result-02.json). Initial harness include-order compile failure retained; corrected harness, no engine change. |
| Real quest C plus codec | PASS — EXECUTED, 39 focused assertions with ASAN/UBSAN, including unsuccessful item insertion leaving state2 and repeat acceptance/visit/claim; [quest report](b3-johto-quest-state.md). Initial harness effect-count expectation failure retained and corrected without engine changes. |
| HnS encounter selection | PASS — EXECUTED, generated preprocessed encounter tables byte identical; [comparison02](../_local/evidence/b3-johto-01/hns-wild-selection-02.json). First comparison used an unbuilt baseline path and is retained as a tooling failure. |
| HnS quest/script and display guards | PASS — EXECUTED scoped checks: original lab/Guide/specials preprocessed bytes unchanged, 694 original specials retained, real ARM quest object has no emitted code/data/globals for HnS; [quest guard result](../_local/evidence/b3-johto-01/quest-runtime/hns-branch-audit-02/result.json). Display logic unchanged; region-map allocator diagnostic line alone moves by two source lines, explicitly reconciled in [display proof](../_local/evidence/b3-johto-01/quest-runtime/hns-display-guard-01/guarded-result.json). No full B3 HnS ROM/native qualification is claimed. |
| First fresh FireRed `0020` attempt | FAIL — EXECUTED, make/build and wrapper exit2; undefined clerk graphics identifier, complete failure evidence retained |
| Corrected FireRed `0021` build and linked totals | PASS — EXECUTED, resumed command exit0; EWRAM254,488 / IWRAM25,940 / linked ROM29,995,268. Retained fresh outputs; not a second clean build. |
| Final FireRed `0022` build and linked totals | PASS — EXECUTED, actual make/build and wrapper exit0; EWRAM254,488 / IWRAM25,940 / linked ROM29,995,300; exact two-file repair, other source hashes retained; not a new clean build. |
| Independent clean `0021` / `0022` reproduction | NOT RUN; current exact manual command above |
| Actual generated IDs and bounded world metadata | PASS — EXECUTED generator/static audit; existing map/layout ID headers byte equal, reciprocal selected connections/valid interior destinations, original HnS metadata and asset bytes preserved; [audit](../_local/evidence/b3/world-integration-01/metadata-audit.json). No gameplay claim. |
| Actual quest walk, reward, repeat interaction | PASS — EXECUTED. `0021`: Elm acceptance and outbound Route 29. Final `0022`: Guide visit, return to Elm, native one-Potion message and completed repeat dialogue. Four natural wild encounters ended with normal Run. |
| Normal Save/full quit/cold Continue | PASS — EXECUTED. Accepted state saved on `0021` and cold loaded on `0022`; rewarded state saved and full-process cold loaded on final `0022`. After reload Elm remained completed and the Medicine pocket visibly contained exactly two Potions, initial one plus reward one. |
| Return to Kanto and preserved native progress | PASS — EXECUTED native return through the existing New Bark travel NPC; Pallet save prompt displayed RED/zero badges. Party menu showed original male Bulbasaur level6, HP21/21. Stored reward comparison preserves trainer, rival, PC, native Kanto flags and progression; final returned checkpoint evidence below. |
| Full-bag reward / decline / pre-acceptance Guide branches | Targeted real-C/source checks only; NOT RUN in GUI. No fabricated native pass. |
| Cherrygrove Center/Mart services and other interiors | NOT RUN in GUI; selected metadata/actors checked. Johto healing/respawn policy remains unimplemented. |
| Broad campaign, cable/browser/hardware tests | NOT RUN; cable/browser deferred by owner |

## Executed native journey and durable evidence

Stable desktop mGBA **0.10.5**, ordinary game controls, normal in-game Save and whole-process quit were used. No emulator save states, cheats, granted flags, forced position/warp APIs or second starter were used. A bounded position-only Lua observer loaded through mGBA's Scripting UI read RAM to aid navigation and wrote private position logs; it did not mutate game data or send controls. GUI observations are recorded in [the native chronology](../_local/evidence/b3-johto-01/native/gui-events.jsonl).

The starting save is a **copy** of final05's ordinary New Bark checkpoint, SHA-256 `5a632325cbbff5d42c0c1f6c865cf17ebc181c094ccbffddab7da4d67b44ac76`, generation5/content1. Trainer RED, rival BLUE, visible ID25928/full ID4088816968, one male Bulbasaur level6/HP21, Potion1, money3080, coins0, zero badges; before the Parcel/Pokédex unlock. Original source remains immutable. No personal saves or additional version5 conversion.

| Native checkpoint | Actual candidate and result | Immutable local snapshot |
|---|---|---|
| Accepted, Route 29(1,15) | `0021`, ROM `e6904e926c72c9e39a9c1f6560c03745c2570d247e46c905da29031cdc1abc1e`. Normal Save to field, full quit/process absent; final `0022` cold Continue restored acceptance and location. Selected generation6/content2, state1/events1. | [accepted save](../_local/saves/firered/b3-native-01/accepted-route29-normal-save.sav), SHA-256 `c90d8d876e360acbdc81451bbcfd5741c762f07701f33a36516cecd9f821a1e0` |
| Rewarded, Elm's lab(6,4) | Final `0022`, ROM `39b023532a1cd657633970777ca108b74382b1239d197756a36a32c8fcd1bd91`. Normal Save/full quit/process absent, cold Continue RED1:10/zero badges restored lab; repeat Elm dialogue gave no new reward, Medicine pocket Potion×2. Selected generation7/content2, state3/events7/revisions1. | [rewarded save](../_local/saves/firered/b3-native-02/rewarded-lab-normal-save.sav), SHA-256 `cf6e6f05627089cd5b4e6b2998477260339234905c9ce47c2fe0a5c89a0263fa` |
| Returned, Pallet(10,13) | Final `0022`, existing outside New Bark travel NPC/visible YES, native Pallet arrival and party menu. Normal Save RED1:12/zero badges to field, full quit/process absent. Selected generation8/content2, both banks valid, state3/events7 preserved. No additional Pallet cold cycle executed. | [returned save](../_local/saves/firered/b3-native-02/returned-pallet-normal-save.sav), SHA-256 `7f10f43739e4790e6d28abf6c2e640fc395e21d4d2f021c925b52a2a144dbbc7` |

Final `0022` visibly displayed the corrected **CHERRYGROVE CITY** and **ROUTE 29** wood map popups. The earlier blank `0021` Route 29 name and statically proven Cherrygrove popup-table overrun are retained defects repaired by `0022`; no observed crash is claimed. The trainer walked the selected route and returned to Elm. Three female Sentret level3 and one male Pidgey level3 encounters ended with ordinary successful Run, without catches, EXP or HP loss. On final `0022`, the outside New Bark travel NPC's visible YES prompt returned the trainer to Pallet; no House1 entry was required.

The [original-to-reward stored-field reconciliation](../_local/evidence/b3-johto-01/native/rewarded-native-field-reconciliation.json) and [accepted-to-reward comparison](../_local/evidence/b3-johto-01/native/accepted-to-rewarded-native-field-comparison.json) each pass 22 bounded checks. Both banks validate; trainer/rival, party count/EXP/HP, PC, native flags, caught Pokédex, roamer bytes and Kanto metadata retain their prior values. Potion1→2 is the sole inventory change; money3080/coins0 remain. Seen species16/161 reflect the recorded Pidgey/Sentret encounters. Party differs from the original only in walking friendship77→78 and its valid checksum; accepted-to-reward party bytes are identical.

Recorded runtime variables also change through ordinary walking/encounters: friendship-step `0x402A`1→7, poison-step `0x402B`0→1 and daily-wild `0x40E7`1→5. The poison counter increments modulo4 in the selected shared walking behavior even without poison or HP damage. An initial strict two-counter comparison flagged that third counter; its report and exact diffs remain preserved. The source-backed reconciliation adds only that known bounded counter, without engine or save changes. These are stored-field checks, not proof of every future campaign or save family.

The [original-to-returned](../_local/evidence/b3-johto-01/native/original-to-returned-native-field-comparison.json) and [rewarded-to-returned](../_local/evidence/b3-johto-01/native/rewarded-to-returned-native-field-comparison.json) comparisons each pass 22 bounded checks. The [exact location/member proof](../_local/evidence/b3-johto-01/native/returned-stored-member-diffs-and-position.json) confirms actual `MAP_PALLET_TOWN` group68/map0/layout487 and position/warp(10,13). Reward→return party and Pokédex bytes are identical, as is the entire regional body116–1331. Potion2, money3080, coins0, all native flags, rival, PC and completed Johto state remain. Only ordinary step counters change from reward: `0x402A`7→33 and `0x402B`1→3; daily-wild stays5.

The [final fingerprint check](../_local/evidence/b3-johto-01/closeout-fingerprints.json) confirms all 96 frozen source records in both development and actual build trees, final ROM/ELF/map hashes and the immutable original save. The private upstream checkout remains clean at the exact pin. These are closeout identity checks, not new gameplay/build repetitions.

The writable final ROM/save pair is [_local/saves/firered/b3-native-02/b3-johto-final.gba](../_local/saves/firered/b3-native-02/b3-johto-final.gba) and its `.sav`. Keep this pair separate from frozen foundation ROMs. A freshly corrected independent clean `0022` build remains **NOT RUN**; the original fresh attempt failed and the final retained-tree build passed, as recorded above. Broad testing was deferred in accordance with the owner's latest priority.

## Limits and review

The four-byte main-block margin, FireRed roamer fidelity defect, separate HOF/special-sector atomicity and approximately9.63-second observed foundation full-save interval remain open. Stored reserve256 and outside-format292 remain unused. Existing native offsets and save transaction are unchanged. Old foundation ROMs reject content2, so use separate ROM/save directories and immutable originals.

Map selections and source dependencies are described in the [targeted C notice](b3-c-dependency-notice.md). C's010 package and unrelated art work stay unchanged. Workstream A/C repositories, services, dependencies, plans, credentials, networking/NAS and all remote publication boundaries remain untouched. No commits or pushes.

Recommendation: **GO for review and continued bounded development**, with the playable quest and native save/cold reload executed. **HOLD for player release or full-campaign claims.** This is a small original Elm errand alongside FireRed, not the imported eight-gym HnS campaign. Stop at this prototype review gate before extending Johto progression.

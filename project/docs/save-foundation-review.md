# FireRed save foundation — review

**October 13, 2026, America/New_York. Foundation closeout complete: GO for a bounded development prototype.** The approved FireRed-only foundation and copy conversion of exactly three B2 saves are implemented, with reproducible builds, actual-C/ARM checks and the native/runtime evidence below. Native cable qualification and browser requalification remain **NOT RUN — OWNER DEFERRED**. This closes the foundation for further prototype work with its recorded limits; it does not qualify a player release or complete save compatibility.

Later on October 13, the owner directed less testing and faster progress toward a workable merged game. That steering supersedes the earlier stop-before-Johto instruction for the bounded first playable Johto quest slice described in [the B3 prototype requirements](b3-johto-prototype-requirements.md). B3 is the project's internal label for that next slice, not a milestone name supplied by the owner. Frozen patch 0019/final05 remains the foundation baseline; new progression work is separate and must retain its exact source, format and evidence boundaries.

The foundation gives later Johto state a bounded, versioned location and prevents a save from mixing generations across the native main payload and extension. Existing trainer, party, inventory, FireRed progression and PC fields keep their offsets. It does not enlarge the original main block's four-byte margin.

## Exact review candidate

Apply [complete patch 0019](../patches/0019-firered-save-caller-completion.patch) alone to upstream commit `167aa6d537b109bb229c231ddce4616974c4da71`. Patch SHA-256: `b398435b7ca39164a0bcc935579fcccb3fd465db1d4d28418b418fc6be612b46`.

| Local output | SHA-256 |
|---|---|
| [FireRed ROM](../_local/artifacts/save-foundation-05-firered/pokefirered.gba) | `97eb56f51e542eea6a324d59c0c33d4e3b6b91858714174c23ce2db490004f76` |
| [FireRed configuration/build manifest](../_local/artifacts/save-foundation-05-firered/manifest.json) | `d390054ca75497a773b51e4a9a49f708d452ccd0e1d828468edfc2b0f971800a` |
| [HnS ROM](../_local/artifacts/save-foundation-05-hns/pokehns.gba) | `0cfac50a9db64c0a0a5cc87fbc667b16d9bfd42446fe14a1cf86badfa6608959` |
| [HnS configuration/build manifest](../_local/artifacts/save-foundation-05-hns/manifest.json) | `3057926fda0570c1737bfb33d0b875aa2966dce876800e875304b7a097859269` |

The manifests preserve the real commands, locked compiler/configuration, complete source differences, stdout/stderr, make and wrapper exit codes and every output hash. Both final05 clean builds passed with exit **0**. Separate repeat06 trees reproduced both ROMs, ELF and map files byte-for-byte; source, effective configuration and toolchain records match. [Actual layouts, budgets and repeat results](save-foundation-layout-and-budget-results.md).

The full natural opening/starter/fresh-save tests were executed on final04/0018, ROM `87cbe649615e1aa71a75b604b78c2db2e0ca0fd621371f9df96e8a4ff7c296f9`. Final05 adds two FireRed caller error/completion guards; its core serializer/coordinator/layout/opening/assets are unchanged. Final04 tests are kept under that identity. Final05 native acceptance is separately bound; its hash change is not hidden.

## Changes and allocation

FireRed uses native version **6**, extension **FRJS schema1**, content/layout **1/1**. SaveBlock3 grows from 52 to **1,332 bytes** in its existing 1,624-byte chunks. Preserve its original 52-byte prefix; append a 64-byte header, fixed regional records, 2,048 event bits, 1,024 trainer bits, 240 u16 variables, a blank future travel slot and **256 zero reserve bytes**. The **292 outside-format bytes** remain uncommitted. The Johto record is uninitialized and every new gameplay container remains blank.

All FireRed main-save families use one coherent alternating-bank transaction, retaining the previous bank through body writes, prepared logical ID0 and final signature commit. Preserve existing sector payload checksums; add extension CRC32 and a SHA-256 binding the exact native encrypted payload and generation. Former partial saves retain the previous validated durable PC. Load validation selects one whole compatible bank, rejects ambiguous or unsupported saves, and reports failure without silently replacing the file with New Game. [Implementation and caller contract](save-foundation-implementation.md); [exact registered format](save-format-registry.md).

Actual ARM sizes are **15,868 / 3,892 / 1,332 bytes** for SaveBlock1/2/3; PC storage is **34,144 bytes**. Every original main/party/PC field offset and sector checksum length is unchanged. HnS, LeafGreen and Emerald retain their old measured layouts and version5. LeafGreen's original capacity failure remains unresolved; no full build/pass for it is claimed.

New EWRAM is **6,756 bytes**, comprising 1,280 of extension growth plus **5,476** scratch. This is within the approved combined **6,784** and scratch **5,504** ceilings, by 28 bytes. Total linked EWRAM is **254,488 / 262,144**, leaving **7,656 bytes**. IWRAM is **25,940**, linked ROM content **29,946,932**, and the existing **115,968-byte heap** is unchanged. Linked headroom and compiler frames are distinct from runtime peaks.

## Executed qualification

| Check | Status and evidence |
|---|---|
| Clean FireRed/HnS and repeat builds | **PASS — EXECUTED**, real exits0 and byte-identical repeats |
| Actual ARM field maps, prefix/append, checksum tables, other targets, scratch/linked budgets | **PASS — EXECUTED**; [layout/budget results](save-foundation-layout-and-budget-results.md). Original interrupted checker omission preserved and corrected in a separate checker copy. |
| Real C codec versus independent CRC/SHA/framing | **PASS — EXECUTED**, 170 checks |
| Real C bank selection/load and malformed/recovery cases | **PASS — EXECUTED**, 92 cases |
| Real C coordinator/write families/occupied durable PC/interruption | **PASS — EXECUTED**, 1,190 assertions, including 300 host flash-interruption scenarios; 24 additional cancellation checks. Counts overlap and are not summed into one total. |
| Copy converter and independent preservation | **PASS — EXECUTED**, exactly the three allowlisted fixtures, all originals unchanged; [conversion/host report](save-foundation-conversion-and-host-tests.md). Empty-PC fixtures do not qualify occupied-PC legacy migration. |
| Caller completion/error propagation | **PASS — EXECUTED**, 24 FireRed and 24 unchanged HnS traces plus eight actual ARM pipeline compilations; [caller review](save-foundation-caller-regression-results.md). |
| Fresh natural FireRed opening/starter/first save and two region save/cold cycles | **PASS — EXECUTED on final04**, [fresh native results](save-foundation-fresh-native-results.md); ordinary controls, actual whole-process exits, no save states/cheats |
| Converted returned-Kanto character on final05 | **PASS — EXECUTED**, normal save/full-process exit/cold Continue in Pallet, then B2 travel/New Bark save/full exit/cold Continue; counters4/5; protected raw fields/decoded inventory and blank regional state preserved; [final05 native report](save-foundation-final05-native-results.md) |
| Other two converted baselines on final05 | **PASS — EXECUTED**, direct native Continue/field/party in Pallet and New Bark; session save bytes unchanged. No additional save-cycle claim. |
| Separate final05 HnS regression | **PASS — EXECUTED**, exact HnS ROM, owned copy, field connection/two normal wild Runs, normal Save/full quit/cold Continue. Party and semantic inventory retained; source-correlated daily/field changes distinguished in the [native report](save-foundation-final05-native-results.md). |
| Runtime save/heap/stack | **PASS — EXECUTED for one bounded full-save case**, [runtime report](save-foundation-runtime-results.md). Generation 4 → 5 committed in **575 frames / 161,584,143 emulated cycles, approximately 9.63 seconds**; 4,220 matched SHA spans account for **49.19%**, including interrupts. Logged stable heap maximum is 16,400 bytes including headers; the lowest watched write is 0x030079B0, 5,212 bytes above the linked IWRAM end. These are captured observations, not an accepted latency threshold, instruction-SP minimum, complete transient heap peak or physical/campaign guarantee. |
| Native incremental peer save | **NOT RUN — OWNER DEFERRED** at the October 13 priority change. One trainer completed ordinary Parcel/Dex/staging Save; the second only loaded its isolated native save. No paired session, battle, peer save or peer timing ran. [Exact peer closeout](save-foundation-native-peer-status.md). Same-FireRed Trade Center readiness requires existing Sevii network progression; the source audit is not a native trade pass. |
| Browser requalification | **NOT RUN — OWNER DEFERRED**; earlier B1 browser evidence remains separately recorded, and Workstream A is unchanged |
| Physical power loss, hardware IRQ/flash timing, full campaign, arbitrary old saves | **NOT RUN / outside this package** |

Host tests execute actual engine C against pinned-size private dependencies and byte-backed flash. ASAN/UBSAN diagnostics were empty and test/compile exits0. They do not simulate the actual hardware interrupt scheduler, physical cartridge power failure or natural campaign reachability. GUI tests and read-only stored-byte validation remain separate evidence.

## Copies and retained state

Immutable converted outputs are in [_local/saves/firered/save-foundation-converted-01/](../_local/saves/firered/save-foundation-converted-01/):

| Copy-only output | SHA-256 |
|---|---|
| [Kanto before travel](../_local/saves/firered/save-foundation-converted-01/kanto-before-travel-frjs1.sav) | `0829e6fbd5dfe393d0bdade062af4c9ced69c45fda76100ee9f3cb324d450dbc` |
| [Johto checkpoint](../_local/saves/firered/save-foundation-converted-01/johto-cycle-01-frjs1.sav) | `c129f8e6feeb4aabe8e28d283b72fec19534972d0dfd732a335d4fcab1814385` |
| [Returned Kanto](../_local/saves/firered/save-foundation-converted-01/kanto-cycle-02-frjs1.sav) | `0d41eacb54e6046f9c7f8b5164f91d9dedd95ff9cfaefd6ca486ada7b9e5ae60` |

Each preserves exact original party/creature bytes, trainer/rival/Dex/story/PC/prefix, specials and opaque emulator trailer, changing only approved native version/integrity/blank extension. Normal gameplay encryption keys may change during a later save; semantic inventory/money comparisons therefore decode them correctly. RED/BLUE, trainerID25928, male Bulbasaur6HP21/21, Potion1, money3080 and no badges remain on the converted test character. Its two final05 native cycles retain all protected party, flags/variables, Dex, rival, PC and regional blank/reserve bytes; only the expected location and normal native save housekeeping change.

All active testing uses additional writable session copies. Original inputs and converted outputs remain read-only. Fresh trainerID40767 has its naturally different Bulbasaur HP22/22; it is not mistaken for the converted character.

## Open limits and review boundary

The **four-byte original main-block margin**, FireRed **roamer fidelity defect**, separate HOF/special-sector atomicity, and old-ROM downgrade limitations remain open. Final05's measured ordinary full save takes **approximately 9.63 emulated seconds** in the captured case; final04 separately recorded an approximately 9.61-second sampled busy interval. The owner has not explicitly accepted a release latency threshold, and no speed improvement is claimed. Frozen final05's Johto progression remains uninitialized with blank records; the next slice must introduce its own durable mappings without changing this frozen evidence. This package does not claim campaign completeness or a player-release save guarantee.

Native same-FireRed trade readiness is an unchanged upstream campaign guard: the linked 0x10 progress bit comes from FireRed's existing Sevii network flag. Early Parcel/Dex/capture alone does not allow Trade Center. No champion/network flag was granted, no guard removed and no campaign repair added to obtain a save test. Full incremental post-trade timing remains unqualified unless naturally reachable evidence is later approved.

C's frozen010 package remains unchanged. C's asset inventory/replacement work need not restart. B owns saves, campaign behavior, runtime clock/palette systems, budgets and integration; C owns its isolated asset packages and validation. The [targeted dependency notice](save-foundation-c-dependency-notice.md) identifies the later save identity and measured RAM budget. No Workstream A/C repository, service, protocol, dependency, credential, NAS/network, CI, automation or remote write was changed. Nothing is staged or committed.

**Recommendation: GO for the bounded development prototype, with the limits above retained.** The October 13 owner direction moves active work to the first playable Johto quest slice in [the B3 requirements](b3-johto-prototype-requirements.md). The earlier foundation gate is closed for that development purpose; this is not a release recommendation or a claim that deferred checks passed. The new slice defines its event/trainer/variable mappings, initialization, rival/starter policy, rewards and unlock rules, then ends at its own review gate. Broad scheduling/link restructuring, moved live fields, more allocation, reduced reserve, feature removal or wider legacy conversion still requires review first. Workstream A and all C ownership, local-artifact and remote-write boundaries remain intact.

# Save foundation — bounded runtime observations

**October 13, 2026, America/New_York. PASS — EXECUTED for one ordinary full-save diagnostic case.** The frozen final05 FireRed ROM committed generation 4 → 5, and an independent host decoder validated both resulting banks. The measured save interval was **161,584,143 emulated cycles / 575 frames**, equivalent to **9.631165 seconds of emulated time**. SHA-transform entry-to-return spans accounted for **49.19%** of that interval. No engine or ROM change was made for this measurement.

This report qualifies the captured case and its observations. Primary gameplay/save acceptance in stable mGBA 0.10.5 remains in the [final05 native results](save-foundation-final05-native-results.md). This development-tool run does not add a cold-reload pass, campaign-wide memory guarantee, physical flash timing result or real two-peer exchange result. It does not authorize Johto progression.

## Exact candidate and diagnostic method

The complete [patch 0019](../patches/0019-firered-save-caller-completion.patch), SHA-256 `b398435b7ca39164a0bcc935579fcccb3fd465db1d4d28418b418fc6be612b46`, applies to upstream `167aa6d537b109bb229c231ddce4616974c4da71`. The measured ROM is [final05 FireRed](../_local/artifacts/save-foundation-05-firered/pokefirered.gba), SHA-256 `97eb56f51e542eea6a324d59c0c33d4e3b6b91858714174c23ce2db490004f76`, CRC32 `e9540980`. Its ELF/map/configuration and unchanged linked allocation are documented in the [ARM layout and budget report](save-foundation-layout-and-budget-results.md). An independent clean repeat reproduced the ROM, ELF and map exactly.

The GUI operator executed an ordinary menu Save/overwrite on a disposable copy of the converted returned-Kanto trainer, with two existing valid banks. Diagnostic mGBA was the official development build **0.11-9155-143adf5aa**, source commit `143adf5aa2a60c6036810b0cd72445e13d74b0e6`, executable SHA-256 `6d692ccab2b621ea0decc97753e944b41aab6ef89a49a0b8c7b7b0ae1f8ad9ec`. It was installed only under ignored `_local/tools/diagnostic-mgba/`. Its private portable profile and process working directory were verified before use. This is a development snapshot, not a claimed stable 0.11 release.

The exact [read-only observer](../_local/evidence/save-foundation-resume-01/readonly-final05-one-save-profile.lua), SHA-256 `7f45d82c301c00bcdb48616a8cf97e342f72d79a38f59e5d41504f2e5f7fc29e`, installed actual positive WRITE watchpoint IDs **1 and 2** and hardware breakpoints. It checked the ROM CRC, bounded raw RAM reads, exact ELF addresses and ARM-measured structure offsets. Dynamic return observations matched normalized LR, original SP, CPU mode and return instruction-set bit. These APIs and their automatic resume behavior were reviewed against the [exact mGBA source](https://github.com/mgba-emu/mgba/blob/143adf5aa2a60c6036810b0cd72445e13d74b0e6/src/core/scripting.c).

The observer wrote private host logs only; it injected no input, game memory/register writes, state/reset operations, ROM patches or networking. The save itself was performed through normal GUI controls. The preserved preparation manifests retain their historical NOT RUN status; the executed results are in the log and this separate qualification.

## Save and hashing measurements

The captured case began at cycle **2,227,730,815**, frame **7,931**, and completed at cycle **2,389,314,958**, frame **8,506**. Phase writes followed VALIDATING → PREPARING → FROZEN → BODY → HEADER → PREPARED → COMMITTING → IDLE. The commit function returned success with result **1**, loaded **1** and generation **5**. Measuring the commit return avoids treating the earlier IDLE assignment alone as completion proof.

| SHA-transform work in captured case | Calls | Entry-to-return cycles |
|---|---:|---:|
| Validate two prior banks | 1,688 | 31,712,638 |
| Hash frozen new snapshot | 844 | 15,728,711 |
| Verify body before header preparation | 844 | 15,909,483 |
| Validate newly committed bank | 844 | 16,132,609 |
| Total | **4,220** | **79,483,441** |

All **4,220 started calls completed**; phase totals equal the recorded aggregate. Each 53,996-byte framed main digest requires 844 SHA blocks including padding, so these counts match the five actual digest passes in the selected source path. The largest recorded single transform span was **85,467 cycles**. These intervals include interrupts; they are not exclusive crypto CPU time. Per-call spans were aggregated rather than logged individually, so the independent analysis can verify counts, phase sums and bounds but cannot reconstruct every individual span.

At the emulator's 16,777,216-Hz clock, the aggregate SHA spans equal **4.737582 seconds**. The remaining **82,100,702 cycles / 4.893583 seconds** are unattributed by this observer; they must not all be labelled flash cost. Host debugger/log overhead can increase wall-clock duration, so no wall-clock performance result is claimed.

The independently decoded source checkpoint had valid generations **3 and 4**. The saved checkpoint has valid generations **4 and 5**, selects generation **5**, and retains the prior generation-4 bank byte-for-byte. Native checksums, sector IDs/rotation/parity, extension CRC and main SHA binding all validate. Thirteen protected native fields — trainer/rival names, trainer ID, party/count, flags/vars, Pokédex seen/caught, roamer, position/location/layout — compare byte-for-byte with the source checkpoint. Decoded inventory/currency and PC storage also match; unimplemented regional records and reserve remain blank. These are actual saved-byte checks, not a further GUI cold-reload result.

## Memory observations and coverage

The fixed linked heap is **115,968 bytes**. All six logged stable snapshots conserve that complete arena and satisfy the pinned allocator's header/link decoding. Stable allocation/free return observations occurred before the case; the save had no allocator return event and its begin/commit snapshots agree.

| Observation scope | Maximum allocated payload | Maximum used arena, including headers | Smallest observed largest free block | Valid snapshots |
|---|---:|---:|---:|---:|
| Full observer window | 16,256 | 16,400 | 99,568 | 6 |
| Captured save case | 15,616 | 15,744 | 100,224 | 2 |

These maxima describe logged stable boundaries. They do not prove every transient allocation state or all campaign workloads. No rejected heap snapshot was logged.

The WRITE range was **[0x03006554, 0x03008000)**, from the actual linked IWRAM end to physical IWRAM end. Across **3,885,021** callbacks, lower-address records show:

| Scope | Lowest recorded write address | Separation above linked end | Written extent below system-stack start 0x03007E40 | Lowest SP on a new lower-address record |
|---|---|---:|---:|---|
| Captured save case | `0x03007A44` | **5,360 bytes** | 1,020 bytes | `0x03007A48` |
| Full window, including earlier menu activity | `0x030079B0` | **5,212 bytes** | 1,168 bytes | `0x030079B4` |

All 74 recorded writes lie within the watched range. Their sequences strictly decrease: 48 case records and 26 global records, all observed in system mode. SP/mode were read only when a new global or case lowest address was reached. Higher IRQ writes can be skipped after an existing lower record, so this does not establish complete per-mode or IRQ extrema. The watcher receives WRITE notifications under the selected API, but its log omits values; it does not separately prove a particular zero/same-value write occurred.

The measured separation is a bounded write-footprint observation. It is not a guaranteed free stack allowance, minimum SP after every instruction, maximum reservation of unwritten stack, or coverage of writes below the linked end. No instruction-level stack guarantee or campaign-wide heap/stack peak is claimed.

## Qualification, stop and preserved evidence

The independent read-only analysis exited **0** after **50 checks**. It parsed all **95** complete records, recomputed monotonic cycle/frame arithmetic and heap/write extrema, rechecked actual ROM/ELF/map/patch/tool hashes and ELF hook bindings, and independently decoded the before/after save bytes. It found no error, rejected snapshot, unqualified SHA argument, reset, shutdown, abort or cap-stop event. Final pending return count is **0**. Captured 575 frames, total-window 1,455 frames, 4,220 SHA calls, three allocator entries and 3,885,021 WRITE callbacks stay below their explicit bounds. Peak pending-return/return-site counts were not logged; no claim of their exact maxima is made.

The observer automatically became inert after the single case and attempted hardware-hook retirement at the next frame. The operator then quit the whole diagnostic process; the recorded process probe returned **1**, confirming absence. Optional external subscription cleanup was **NOT EXECUTED** because reopening Scripting produced an empty console. Source-driven retirement and process exit are documented; successful return of every protected retirement call was not separately logged.

The operator's [quit/isolation proof](../_local/evidence/save-foundation-resume-01/diagnostic-quit-and-isolation-01.json) records stable mGBA configuration bytes unchanged from immutable prelaunch snapshots at that instant. Stable mGBA was subsequently reopened for separately authorized peer preparation, so later preference hashes can differ. The first analysis attempt incorrectly compared those later current files with the earlier quit snapshot; its script/log/exit **1** remain preserved. A second attempt treated the inspector's stored little-endian CRC bytes as formatted integer text; that script/log/exit **1** is also preserved. The final copy corrects these checker assumptions explicitly, retaining all engine/layout/ROM validation checks.

All private evidence and saves remain local and ignored:

- [Independent qualification](../_local/evidence/save-foundation-resume-01/runtime-qualification-03/qualification.json), SHA-256 `58f0070697edc93da8f769ce53a5d8cfd7df5907e6a4e75fa1067db2015a1d73`, plus its exact script, execution record and exit-0 log.
- [Actual observer log](../_local/evidence/save-foundation-resume-01/diagnostic-observer-logs/20261013T193527Z-1980363539.jsonl), SHA-256 `b51b82a74fbdd4dbfb2b82b5d11eaeaf7074e66a45252ece98688cf68db51986`.
- [Actual saved checkpoint](../_local/saves/firered/save-foundation-diagnostic-01/after-profile-normal-save.sav), SHA-256 `e2635be438e7c9db7ddd45fc8fb0feb8aeb8a9bb6ddf4bb1afa61cc8150fb2fe`.
- [Stored-bank inspection](../_local/evidence/save-foundation-resume-01/diagnostic-profile-saved-bank-inspection.json) and [protected-state comparison](../_local/evidence/save-foundation-resume-01/diagnostic-profile-protected-state-comparison.json).

## Performance implication and remaining gate

The measured 49.19% SHA span share gives a concrete reason to consider a separate pure-transform instruction-set optimization experiment using the existing `ARM_FUNC` facility. No such code change, compilation or speed measurement is included here; frozen patch 0019 remains unchanged. A bounded experiment would have to preserve every validation pass, exact digest/output/save format, interworking ABI and approved allocation, with actual layout/build/digest/runtime evidence before acceptance. Moving code to IWRAM or adding storage would broaden that experiment and must not be assumed authorized.

Even the arithmetic limit of eliminating all measured SHA spans leaves **4.893583 emulated seconds** of this same recorded interval. That is an attribution bound, not a predicted speedup or future save duration. Campaign completeness, save compatibility beyond the expressly supported development fixtures, physical flash/power-loss behavior and real peer behavior remain outside this one diagnostic case. The four-byte main-block headroom limitation and FireRed roamer fidelity defect remain open. Workstream A and all remote/publication boundaries remain unchanged; stop at the save-foundation review gate before Johto progression.

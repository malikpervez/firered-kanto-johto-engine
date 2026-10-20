# FireRed save foundation — implementation contract

**October 10, 2026.** This implements the owner's [bounded save-foundation approval](decisions/2026-10-10-save-foundation-implementation.md) against B2 candidate 014. The foundation adds protected storage for later regional state and makes every FireRed main-save path commit a coherent bank. It does not add Johto progression or establish a player-release save policy.

The exact layout and conversion scope remain those of the [approved proposal](save-foundation-change-proposal.md) and [format registry](save-format-registry.md). Qualification results, clean ROM manifests, native tests, measured runtime limits and the final review recommendation belong in the separate save-foundation report. This document describes the code and its caller contract; implementation alone is not an acceptance pass.

## Source and target identity

The engine source is local and ignored, rooted at `_local/worktrees/save-foundation-dev-firered`, with upstream commit `167aa6d537b109bb229c231ddce4616974c4da71` and the complete B2 014 patch as its starting point. Clean qualification candidates use separate local target trees and manifests. The definitive coordinator source fingerprint is:

| File | SHA-256 |
|---|---|
| `src/save.c` | `0f67df0b8e9b45d2431fdd9889d1c9681e6144d71228693da82423042daad7de` |
| `include/save.h` | `cd83c11343d3765bc1c178b16630d527d3b78c61fc09f12e7aa900496e185da6` |
| `include/firered_save.h` | `1eeac16d41f7f0e8d172c6a6f12c4abd68c61f0ac3ac3df450253212ecb7caed` |

**Selector correction:** upstream's actual preprocessor selector is `FIRERED`. The implementation uses `#ifdef FIRERED` and an ordinary C assertion that `GAME_VERSION == VERSION_FIRE_RED`. The proposal's `VERSION_FIRERED` spelling is absent upstream, and enum-valued `GAME_VERSION` comparisons cannot safely be used in `#if`: unknown enum identifiers become zero during preprocessing. This correction preserves the approved exact FireRed scope. HnS, Emerald and LeafGreen retain native version 5, their 52-byte SaveBlock3 and their old save paths.

## Storage and integrity

FireRed's native save version is 6. SaveBlock1 remains **15,868 bytes**, SaveBlock2 **3,892 bytes**, and Pokémon storage **34,144 bytes**, with their existing offsets and original payload-checksum lengths. The main block's capacity assertion remains active at 15,868 / 15,872 bytes.

SaveBlock3 grows from 52 to **1,332 bytes** within its existing 1,624-byte sector-tail allocation. Bytes 50–51 become explicit legacy padding so the append starts at byte 52 without moving any old field. The existing RTC, DexNav, challenge settings and registered-item prefix stays in bytes 0–51.

| Serialized bytes | Purpose |
|---|---|
| 52–115 | FRJS schema-1 header, generation, content/layout identity, CRC and main-bank digest |
| 116–147 | Kanto metadata; existing native story fields remain authoritative |
| 148–179 | Uninitialized Johto fixed record |
| 180–1043 | 2,048 event bits, 1,024 trainer bits and 240 little-endian variables |
| 1044–1075 | Blank future travel slot; native B2 location and return behavior remain authoritative |
| 1076–1331 | 256-byte stored reserve, zero-filled and protected |

Content/layout entry 1 requires all new Johto, travel and reserve containers to remain blank. The bounded regional buffer accessors allocate no story meaning and are not connected to FireRed's `FlagGet`, `VarGet`, badge, rival, starter or reward writers. New Game preserves the native RTC/challenge prefix policy, initializes the extension, and clears the prior loaded-session descriptor.

`src/regional_save.c` supplies explicit byte encoding, identity checks, CRC32/ISO-HDLC and streaming SHA-256. The extension CRC covers all 1,332 bytes, treating only bytes 80–83 as zero. The main digest is exactly:

```text
ASCII FRJSMAIN (8 bytes, no terminator)
SB3 bytes 52..79 (28 bytes)
for logical IDs 1,2,...,13,0:
    LE16(ID) || LE16(used payload length) || exact persisted payload
```

This hashes 53,904 native payload bytes in a 53,996-byte framed stream. The saved encrypted bytes and their saved key are included. These are corruption and mixed-generation checks, not authentication.

## One coordinator for every main-save family

`src/save.c` routes normal, overwrite, HOF main-state, `SAVE_LINK`, `SAVE_EREADER`, task-based partial and full incremental native-link saves through the same FireRed coordinator. It retains both fourteen-sector banks, sector rotation, native footers and original payload checksums.

1. Validate the existing banks and select the coherent source. Prepare party/object state once. For HOF, hold the prior encrypted HOF-count field before incrementing it.
2. Snapshot all **3,892 SaveBlock2 bytes and 1,332 SaveBlock3 bytes** under a brief interrupt-masked copy, preserving the prior interrupt state. The snapshot includes the encryption key, play time, continue-warp flag, RTC prefix and format header.
3. Choose the next counter/rotation and alternate bank. Full saves use current PC RAM. Former partial saves stream PC bytes from the previously validated durable bank, preserving the original skip-PC meaning. A partial save without an existing source, or for a newly selected different trainer file, fails; the first save must be full.
4. Compute the expected digest from those sources before writing. Encode the held header and CRC. Write logical IDs **1–13**, using the existing 4,096-byte sector buffer.
5. Re-read the target body. Check its footers, checksums and extension chunks, hash the actual written payloads plus held ID 0, and compare with the expected digest. A source drift or competing writer aborts; the coordinator never recomputes a header to legitimize mixed-time bytes.
6. Prepare logical **ID 0 last** with its signature's first byte still `FF`. Re-read and verify that prepared sector. After required native-link synchronization, program the signature byte, validate the complete new bank, then publish successful counters and completion.

The selected source bank is retained throughout. A late interruption can leave either the old complete bank or a fully committed new bank; unfinished state never supplies partial progression. A flash call already underway may finish after cancellation, but the cancelled coordinator cannot publish success.

HOF sectors are written after main-state commit. Their failure reports an error while retaining committed main state. Special sectors 28–31 keep their original format/owners and remain outside the main-bank atomicity promise.

## Persistent writers and bounded memory lifetime

The coordinator's frozen phase protects SaveBlock1, live PC for full saves, saved party/object state, encryption/ASLR moves, heap reset, reload and shared flash-buffer operations. Relevant callers notify before persistent mutations. A required mutation aborts the transaction first, then proceeds; permitted once-only save preparation is exempt while the coordinator is in `PREPARING`.

The existing Trainer Hill/Tower VBlank timer pointer is held null through async work and restored on every exit. Independent SaveBlock2 clocks and the RTC prefix can continue because their serialized images are held. Clearing the live continue-warp flag during the link handshake does not alter the staged bytes. Successful commit updates only the new SaveBlock3 tail in live RAM, preserving ongoing prefix ticks.

The phase byte is volatile. Short interrupt-masked sections with compiler memory barriers protect state transitions, bounded load copies and final publication. Each transition checks its expected phase; HOF special work also requires a retained OK result. An interrupt cancellation cannot be overwritten by later hash, header or HOF completion.

Actual ARM coordinator scratch is **5,476 bytes**, including the 5,224-byte held images, 108-byte SHA context, 64-byte rolling schedule, descriptors, counters, timer pointer and HOF rollback field. It is 28 bytes below the asserted 5,504-byte ceiling. Together with SaveBlock3 growth of 1,280 bytes, added EWRAM is **6,756 bytes**, below the approved 6,784-byte ceiling. The original sector buffer is reused; no whole-bank copy, heap expansion or moved gameplay field is introduced. Linked totals and runtime peaks must be measured separately.

## Load, recovery and error contracts

The validator checks bounded IDs before indexing, exactly one of each ID, all fourteen sectors, native signatures/checksums, uniform counter/rotation, bank parity, version/magic, exact FRJS header, blank foundation, full extension CRC and the canonical main digest before authoritative RAM loading.

Two valid banks must have adjacent modulo-2^32 generations; `FFFFFFFF → 0` is accepted and non-adjacent forks block. One compatible complete bank can recover. A recognized unsupported newer/non-adjacent bank blocks downgrade; an immediately older unsupported bank can coexist with a valid supported successor. Occupied unusable flash is not treated as an empty new file.

Startup `FireRedSave_Probe()` caches the selected bank/generation/rotation and held trainer-ID bytes for pointer offset selection. Actual loading revalidates that exact descriptor before copying, uses exclusive flash access and checks cancellation around each bounded RAM copy. Party/object decoding runs only after a coherent bank is loaded. HOF-only reads load only their special data and run no main-format migration.

| API or status | Caller meaning |
|---|---|
| `FireRedSave_IsBusy()` | Coordinator owns pending validation, frozen/write/load or special-sector work |
| `FireRedSave_LastResult()` | OK during an initialized valid async transaction; **OK plus not busy** is durable main completion |
| `FireRedSave_IsLoaded()` | A complete compatible bank was actually loaded or committed |
| `FireRedSave_NotifyPersistentWrite()` | Abort frozen work before a required persistent mutation |
| `FireRedSave_Abort()` | Release ownership, restore timer/counters and pre-commit HOF preparation, return a real error |
| `FireRedSave_ResetSession()` | Clear the idle loaded/probed descriptor for an explicit fresh session; a busy call aborts and returns |
| OK / RECOVERED | Compatible coherent data loaded; Continue may proceed |
| EMPTY | Both banks erased; New Game may proceed |
| UNSUPPORTED / CORRUPT | Blocked retained file; neither Continue nor implicit New Game overwrite is exposed |

Full-link body-write TRUE retains the original task convention of body-ready-or-error; callers must check the result between body, prepared-header and final-signature stages. Incremental partial TRUE similarly means done-or-error. Their jobs now span fourteen sectors rather than five. Native trade, record mixing, berry/minigame, Frontier and start-menu completion gates require verified commit before success or link acknowledgements.

`gSaveAttemptStatus` remains ERROR until successful main commit. A pre-main HOF failure restores the exact prior encrypted HOF-count field so a direct retry does not increment twice. After main commit, a special-sector failure retains the committed count. The FireRed failure screen returns to title with the good bank retained; it does not automatically wipe sectors, redispatch preparation or replay a save. Existing explicit delete and deliberately selected Hardcore Nuzlocke erasure remain separate.

## Three-fixture offline converter

[`scripts/convert_b2_saves.py`](../scripts/convert_b2_saves.py) and its [reference codec](../scripts/firered_save_codec.py) accept only the three immutable hash-allowlisted B2 fixtures named in the approval. The converter requires read-only originals and distinct outputs, validates legacy banks, retains original gameplay/PC/prefix bytes, changes the native version scalar/checksum, adds the blank extension and emits one valid bank at its original counter/rotation with an erased alternate. Special sectors and any opaque mGBA trailer are preserved.

Outputs and manifests stay under ignored `_local/` paths. An existing identical output can be retained; a different output is never overwritten. A format-6 input is rejected as already converted. The runtime loader performs no automatic version-5 import. The three approved inputs have empty PC storage, so their conversion does not establish occupied-PC legacy migration; new-format occupied-PC behavior is qualified separately.

Keep old ROMs, new ROMs and their saves in separate directories with immutable originals. An old ROM cannot be forced to reject future-format saves. Personal, retail, arbitrary experimental, HnS, Emerald and LeafGreen inputs remain outside this conversion promise.

## Executed checks and remaining gates

The [actual codec verification](../_local/evidence/save-foundation-implementation/codec/codec-verification.json) executed **170 host checks** against the C implementation, independent CRC/SHA references and exact framing. Codec ARM compilation executed separately; its host vectors do not claim ARM gameplay or transaction acceptance.

The [definitive coordinator ARM commands](../_local/evidence/save-foundation-implementation/transaction-arm-final/commands.json) compile actual `src/save.c` with the pinned GCC 14.2.1 and upstream warnings-as-errors settings. FireRed, HnS and Emerald each exited **0**. The compiler retained every applicable capacity assertion and measured the 5,476-byte scratch symbol. These narrow checks use the frozen B2 generated constants as syntax context; they are not clean ROM builds. LeafGreen's independently recorded baseline capacity failure remains outside this package; no success is claimed and no assertion is suppressed.

The [final actual-C host qualification](../_local/evidence/save-foundation-01/c-engine-harness-final/RESULTS.md) is bound to the definitive coordinator hash above. It executed **92 bank probe/load cases, 1,190 coordinator assertions and 24 separately labelled cancellation checks**, with compiler/test exit codes 0 and no ASAN/UBSAN diagnostics. Actual engine save/codec C executes against private host dependencies and byte-backed saved types preserving measured ARM sizes/required offsets. The cases cover malformed/recovery/wrap banks, main/extension integrity, normal/partial/incremental routing, occupied-PC preservation, staged clocks/warp state, interruption at flash writes and HOF retry/error handling. Callback wrapper injections execute the actual codec but do not simulate hardware IRQ timing. They do not establish native story reachability, real game preparation, desktop gameplay or physical power-loss behavior.

Copy-converter preservation, definitive clean builds, native opening/starter/save/cold-reload and performance evidence are reported separately with their source and ROM fingerprints. Host flash/IRQ-boundary injections must be labelled as host tests, not desktop mGBA power-loss execution. A successful compile or codec vector is never substituted for native gameplay.

The FireRed roamer fidelity defect, SaveBlock1's **four-byte margin**, special-sector atomicity and old-ROM downgrade limit remain open. This foundation neither claims campaign completeness nor general save compatibility. Browser qualification remains owner-deferred. Stop at the save-foundation review gate before any Johto story, regional mapping, production unlock or wider migration.

B retains ownership of saves, campaign behavior, time/palette runtime, engine budgets and integration. C's existing isolated asset handoff remains unchanged; its [dependency notice](save-foundation-c-dependency-notice.md) reports relevant memory/test changes without restarting unrelated art. No Workstream A/C repository changes, multiplayer/Discord work, NAS/network changes, CI/automation, commit, push or remote writes are part of this implementation.

# Save foundation — exact proposed changes before Johto progression

**Historical proposal, approved October 10 and resumed October 13.** The original proposal text below is preserved; its pre-approval and NOT RUN statements describe that date. The immutable approved copy remains in private evidence. Current implementation and executed qualification are in the [save-foundation review](save-foundation-review.md). The upstream selector correction is documented in the [implementation contract](save-foundation-implementation.md).

**October 10, 2026, America/New_York. Version 1.0. Proposal ready for owner review; implementation is not approved or started.** The owner accepted B2 and requested this exact change plan. [Decision record](decisions/2026-10-10-b2-acceptance-and-save-design.md).

Recommend a **FireRed-only protected, versioned SaveBlock3 extension**, with every save path writing a coherent alternating-bank transaction. Keep trainer, Pokémon, inventory and Kanto/Sevii progression in their existing locations. Add empty Johto containers now; adapt Johto story only after the save foundation is approved, implemented and qualified.

This avoids putting Johto state into the almost-full main block. It **does not increase that block's four-byte margin**, reclaim further roamer/Dex reservations or repair the roamer defect. If a later feature needs more main-block space, it needs a separate allocation decision.

## 1. Frozen starting point and authorization

Use final B2 candidate 014 against upstream `167aa6d537b109bb229c231ddce4616974c4da71`:

| Existing evidence | Identity |
|---|---|
| [Complete 014 patch](../patches/0014-firered-b2-travel-slice.patch) | SHA-256 `4260edec61faf85a04e62744f9d5424dbc25cfa37d3bacda54e65d4df69684d1` |
| [Tested ROM](../_local/artifacts/b2-04-firered/pokefirered.gba) | SHA-256 `8980ba9dced4586dda2450ea102789a4ac8bf4da731f3a8c07db18a0a41ab9f2` |
| [Build/configuration manifest](../_local/artifacts/b2-04-firered/manifest.json) | SHA-256 `385a5330782851a65c43683fe01d86743fc79180e9d442ea52705ed5200c614b` |
| [Actual ARM layout comparison](../_local/evidence/b2/save-audit/compiled-b2-04/actual-b2-abi-comparison.json) | Existing measured Save1/2/3 sizes 15,868 / 3,892 / 52 bytes; PC storage 34,144 bytes |

The B1 [save audit](b1-save-and-capacity-audit.md), B2 [build report](b2-build-report.md) and [native results](b2-native-results.md) remain the evidence for the existing format. This proposal is a new design, not a new test pass. Source inspection, byte arithmetic and independent design review were performed. **New-format ARM compilation, gameplay, migration, fault/recovery and performance tests are NOT RUN.**

The implementation approval requested below would cover only this local B-owned save foundation and exact fixture conversion. It would not authorize Johto quests, a production unlock, full campaign import, roamer repair, engine replacement or player release. Workstream A's repository, platform, protocol, database, dependencies, credentials, services and plan remain untouched.

## 2. Exact allocation

Retain SaveBlock1 at **15,868 / 15,872 bytes**, SaveBlock2 at **3,892 bytes**, and PC storage at **34,144 bytes**, with all existing field offsets and payload checksum lengths unchanged. Keep both fourteen-sector banks, 4,096-byte sectors, rotation and existing footer/checksum rules. Special sectors 28–31 keep their current owners.

Only FireRed's SaveBlock3 would grow from **52 to 1,332 bytes** inside its existing **1,624-byte** chunk allocation:

| Absolute SB3 bytes, inclusive | Bytes | Proposed use |
|---|---:|---|
| 0–51 | 52 | Existing RTC, DexNav chain, ChallengeSettings and registered-item prefix, unchanged |
| 52–115 | 64 | Format, version, generation, compatibility and integrity header |
| 116–147 | 32 | Kanto/Sevii metadata; original story fields remain canonical |
| 148–179 | 32 | Johto fixed record: identity/schema, initialized state, badges, starter/rival and mapping revisions |
| 180–435 | 256 | 2,048 stable Johto event bits |
| 436–563 | 128 | 1,024 stable Johto trainer-completion bits |
| 564–1043 | 480 | 240 stable Johto variables, each an explicit little-endian u16 |
| 1044–1075 | 32 | Blank future travel/return slot; existing native location remains authoritative |
| 1076–1331 | **256** | Stored, zero-filled growth reserve, covered by integrity checks |
| 1332–1623 | **292** | Uncommitted capacity; no subsystem is promised these bytes |

The 256-byte reserve is an exact proposed allocation requiring approval, not an estimate of free bytes. These counts accommodate the audited source ranges but do not establish that every imported event or future feature fits semantically.

**ARM alignment correction required:** `registeredItemHold` occupies bytes 48–49; the current structure reaches 52 through trailing padding. In the exact FireRed branch, retain bytes 50–51 as explicit legacy padding, then append `u8` serialized storage at offset 52. Blindly appending an array after the last field would start at 50. Preserve every original prefix member and both original padding bytes during supported conversion. Assert the append offset, 1,332-byte total, four-byte alignment, existing prefix offsets and existing capacity/ChallengeSettings limits using the actual ARM compiler.

Use the existing exact FireRed selector (`GAME_VERSION == VERSION_FIRERED`), not the shared FRLG map selector. HnS, LeafGreen and Emerald retain their 52-byte SaveBlock3, native version 5 and current save paths.

## 3. Exact format and initialization

Propose **native FireRed `SAVE_VERSION=6`**, keeping its existing field offset and `SAVE_VERSION_MAGIC=0xE8F828BC`. Introduce independent **`FRJS` extension schema 1**. These are proposed identifiers; candidate 014 has native version 5 and no FRJS header.

All new integer fields are explicitly little-endian; new bitsets use low bit first. Do not serialize new C bitfields or rely on host/compiler packing. Existing prefix encoding stays unchanged.

| Header offset | Bytes | Exact proposed value/rule |
|---:|---:|---|
| 52 | 4 | Magic `46 52 4A 53`, ASCII `FRJS` |
| 56 | 2 | Extension schema 1 |
| 58 | 2 | Header length 64 |
| 60 | 2 | Total serialized SB3 length 1,332 |
| 62 | 2 | Format flags 0; reject unknown flags |
| 64 | 4 | Generation equal to the native counter in every sector of this bank |
| 68 | 4 | Registered content revision; proposed first entry 1 |
| 72 | 4 | Registered layout/codec identity; proposed first entry 1 |
| 76 | 2 | Region-record count 2 |
| 78 | 2 | Reserved 0 |
| 80 | 4 | CRC32 of serialized SB3, with these four CRC bytes treated as zero |
| 84 | 32 | SHA-256 binding this header's identity/generation to the exact main payload of its bank |

The local format registry must bind content/layout entry 1 to the actual approved serializer, native field map, target/configuration and source/patch/build fingerprints before the first candidate is accepted. It is not a truncated ROM hash. Initially accept only that registered pair; later compatibility requires an explicit registry/mapping decision.

Initialize Kanto metadata as LE16 region ID 1, LE16 record schema 1, then 28 zero bytes. Keep Kanto flags, variables, badges, rival and trainer defeats in their existing canonical native fields.

Initialize Johto's fixed record as follows:

| Offset | Bytes | Foundation value |
|---:|---:|---|
| 148 / 150 | 2 each | Region ID 2 / record schema 1 |
| 152 | 4 | State flags 0: **uninitialized** |
| 156 / 157 | 1 each | Badge bits 0 / starter state 0 |
| 158 | 2 | Stable starter species ID 0: unset |
| 160 | 8 | Rival slot zero, ignored while uninitialized |
| 168 / 172 / 176 | 4 each | Event/trainer/variable mapping revision 0: unassigned |

Event/trainer/variable containers, future travel slot and growth reserve begin zero. No Elm initialization, starter, badge, reward or story flag is set. This reserves rival/starter storage without deciding a second starter or replacing BLUE. Original RTC/settings values and New Game challenge-selection behavior are preserved.

Add bounded regional accessors with explicit region and stable index parameters. Existing FireRed/shared accessors stay canonical; do not globally redirect `FlagGet`/`VarGet` merely because the player is standing in Johto. No native HnS numeric ID is automatically allocated a durable Johto meaning. Actual mappings, aliases, daily clearing, paired variables, reward idempotence, field permissions and rival/starter rules belong to the separately approved progression slice.

## 4. Integrity coverage

Retain the original native payload checksums and add two checks:

1. **Extension CRC:** CRC32/ISO-HDLC over bytes 0–1331, with bytes 80–83 zero during calculation. It covers the original 52-byte prefix, header/digest, all regional slots and the full 256-byte reserve. Reflected polynomial `0xEDB88320`, initial/final XOR `0xFFFFFFFF`; check vector `123456789` gives `0xCBF43926`. Store the result LE32. The host reference is the documented [zlib CRC32 interface](https://zlib.net/manual.html#Checksum).
2. **Main-bank binding:** standard [SHA-256](https://csrc.nist.gov/pubs/fips/180-4/upd1/final), stored as its 32 digest bytes. Hash the exact concatenation below; exclude unused payload slack, other SB3 chunks, footer bytes and emulator trailers.

```text
ASCII "FRJSMAIN"                              (8 bytes, no terminator)
SB3 header bytes 52..79                       (28 bytes)
for logical sector IDs 1,2,...,13,0:
    LE16(logical ID) || LE16(used payload length) || exact persisted payload
```

Used payload lengths are 3,892 for ID 0; 3,968 for IDs 1–3; 3,964 for ID 4; 3,968 for IDs 5–12; and 2,400 for ID 13. Total main payload is **53,904 bytes**; framed SHA input is **53,996 bytes**. Hash the exact encrypted/native bytes being persisted, including the saved key and the durable PC image selected for that save mode. This specifies one digest format, superseding alternatives in working notes.

Compute the main digest first, then the SB3 CRC. The hash input includes generation/content/layout through the header but excludes its CRC/digest, avoiding a circular calculation. These checks detect accidental corruption and mismatched/torn save generations; they are not account authentication or protection against deliberately forged files.

## 5. Change every main-save write into one complete transaction

The current `SAVE_LINK`/`SAVE_EREADER` and `WriteSaveBlock2`/`WriteSaveBlock1Sector` paths update only IDs 0–4. That refreshes just 580 extension bytes; the proposed 1,332-byte block extends through ID 11. A larger struct alone would therefore leave stale Johto data.

For the new FireRed format, use one coordinator for normal, overwrite, HOF main state, direct partial saves, task-based partial saves and full incremental trade/link saves:

1. Validate the existing committed bank; acquire exclusive transaction and shared flash-buffer ownership. Run required party/object/stat/warp preparation once. Snapshot **3,892 SaveBlock2 bytes and all 1,332 SB3 bytes** in a brief interrupt-safe copy; preserve the prior interrupt state. Keep normal clock/audio/link operation afterward. Save2's timer/key/continue-warp bytes and SB3's ticking RTC must not drift in the serialized image.
2. Set next counter and rotation, target the alternate bank, retain the old bank. Exclude/defer persistent Save1 producers, live PC mutation in full-save mode, ASLR/encryption moves, heap reset, reload and competing flash/buffer operations until completion. Individually audit callbacks; a control lock alone is insufficient.
3. Normal/full modes select current PC RAM. Formerly partial modes stream **the previous validated persisted PC payload**, preserving their existing skip-PC meaning. Recheck source-sector identity/counter/checksum. A partial request with no committed source fails cleanly; the first save must be a normal full save.
4. Precompute the expected digest from these stable sources in IDs 1–13,0 order; finish the held header/CRC. Reuse the existing 4,096-byte sector buffer to write/verify IDs **1–13** with matching extension chunks and next-generation footers.
5. Re-read the target body and validate its IDs, rotation, counter, checksums and extension chunks. Append the held ID 0 payload to the digest and compare with the precomputed value. If any producer escaped the exclusion, **abort rather than recomputing a header over mixed-time data**.
6. Prepare logical **ID 0 last**, including its entire 52-byte prefix and 64-byte header, with the first signature byte still uncommitted. Verify its prepared bytes; preserve required native-link synchronization; then write/verify that final signature byte. Validate the whole committed bank before publishing success/counter/rotation.

Never overwrite the selected old bank during this transaction. An interrupted save can recover the old complete bank or, if commit finished before interruption, the complete new bank. An unfinished bank never supplies partial progress. Retry must not replay HOF statistics/reward preparation, falsely clear an overwrite flag, or report success on abort.

Adapt asynchronous completion/handshake contracts deliberately: formerly five-sector jobs now span fourteen sectors; callers must finish only after a verified commit. Preserve the saved-party and warp semantics used by Frontier/trade callers. Flash write cost and link timing increase and require measurement. This is native game-engine link behavior, with no change to Workstream A.

HOF special sectors are written only after successful main-state commit. Report their own failure separately; do not claim atomicity across main state and special sectors 28–31. Do not run main-state migrations after an HOF-only read.

## 6. Validate before loading, and recover without a reset

For each physical bank independently, before any array lookup/shift or authoritative RAM copy, require:

- IDs bounded to 0–13, exactly one of each, consistent rotation, correct signatures and existing payload checksums;
- a common native counter, correct bank parity and matching header generation;
- native version 6/magic, FRJS schema/lengths, accepted content/layout identities and zero defined reserved fields;
- complete SB3 CRC and main-payload digest agreement within that same bank.

If both compatible banks are valid, require adjacent u32 generations; select the successor, including `FFFFFFFF → 0`. Block ambiguous non-adjacent forks. A single valid compatible bank can be recovered. First New Game save produces generation 1 in bank 1 with the alternate erased. Never combine one bank's main state with another's extension. A recognized incompatible newer format/content is blocked rather than silently downgraded to an older bank.

Use the same validated descriptor for startup trainer-ID/ASLR offset selection and actual copying. Perform validation followed by bounded copying under exclusive flash access; no gameplay, party/object decoding or semantic migration runs on incomplete/unvalidated blocks. HOF-only reads do not run main-version upgrades.

Propagate distinct **loaded**, **recovered**, **empty**, **unsupported** and **unrecoverable** outcomes through boot, reload, main menu and every save caller. Only an actually loaded coherent bank enables Continue. Unsupported/corrupt files must not become an apparently empty New Game that can later overwrite them; show a blocked-save result with backup/original-build instructions. Fresh erased flash and the existing explicit erase/New Game path remain separate.

For FRJS transaction failures, bypass automatic damaged-sector wiping and redispatch in the current failure screen. Preserve the good bank and return a real failure/retry result. This does not remove the owner's deliberately selected hardcore-Nuzlocke death behavior or explicit delete-save feature.

## 7. Supported input saves and exact conversion scope

Support fresh new-format saves after qualification. Do not automatically import native version 5: that scalar cannot distinguish the earlier layouts, targets or changed defaults. Recommend a separate offline converter for **only these three immutable, known B2 fixture hashes**, writing new filenames and preserving the originals:

| Allowed fixture | SHA-256 |
|---|---|
| [Kanto before travel](../_local/saves/firered/b2-native-01/kanto-before-travel.sav) | `6fac3f465bfc8fea83dfee6a5fdd73002c879286d35069ac4c4e5de547a6c074` |
| [Johto cycle](../_local/saves/firered/b2-native-01/johto-cycle-01.sav) | `ba7aefef473f237f7eff6d220920348c16c09861b1b1fe74faa0e9d2f43edccd` |
| [Returned Kanto](../_local/saves/firered/b2-native-01/kanto-cycle-02.sav) | `7ba5fda5ca885fdc87f208a8dd0b48a60fcbc4471640003dbfb06c83cf4dd10e` |

The returned-Kanto fixture preserves RED's tested trainer as the starting character for later development. The first fixture originated on 013; its exact two-NPC-only transition to 014 and unchanged save ABI are already recorded. Neither that evidence nor an arbitrary sidecar identifies every version-5 save safely.

Converter procedure: enforce the hash/provenance allowlist; strictly validate the legacy banks; select the newest complete one; retain all original gameplay/PC/prefix bytes; change only the native version scalar to 6, recalculate its affected original checksum, add blank regional containers and integrity header; emit **one valid bank at its original counter/rotation with an erased alternate** in a new 128-KiB flash image. Preserve special-sector bytes and any opaque 16-byte mGBA trailer without interpreting it. Validate the output independently before marking it usable. Original input hashes must remain unchanged. Repeated conversion cannot duplicate state; a format-6 input receives an already-converted/rejected outcome, never a second initialization.

These fixtures have **empty PC storage**. Their conversion cannot establish occupied-PC legacy migration. New-format occupied-PC behavior is tested separately; widening the legacy allowlist needs explicit provenance and qualification. Personal, retail, unknown, HnS, LeafGreen/Emerald and other experiments are unsupported by this initial proposal.

Unmodified old ROMs cannot be forced to reject future saves. Use separate ROM/save names/directories and immutable backups; no universal downgrade guarantee. The new loader rejects an older-build rewrite that removes/damages FRJS rather than resetting Johto data.

## 8. Exact RAM budget and implementation files

| Planned additional EWRAM | Bytes |
|---|---:|
| SaveBlock3 growth | 1,280 |
| Held Save2 + complete SB3 transaction images | 5,224 |
| Streaming SHA context (108), rolling schedule (64), phase-exclusive metadata (at most 108) | At most 280 |
| **Total additional allocation ceiling** | **6,784** |

Scratch must fit an ARM-asserted **5,504-byte ceiling**, outside the movable/reset heap. Reuse the existing 4,096-byte sector buffer already counted in B2. No second 53,904-byte main-state/PC buffer or heap expansion is proposed. Actual serializer/reader/transaction descriptors must fit the bound; stop for review if they do not.

B2 EWRAM 247,732 + 6,784 gives a projected **254,516 / 262,144**, leaving **7,628 bytes**, before any extra globals/alignment. This is a ceiling calculation, not a measured new build or runtime peak. Measure actual ARM/linker output, heap/stack high-water and save timing before acceptance. B2 IWRAM 25,944/32,768 and its existing stacks remain a separate constraint.

| Planned file changes | Exact purpose |
|---|---|
| `include/global.h`, `include/save.h` | Exact FireRed-only append/prefix assertions, native version/format constants and explicit load/transaction outcomes |
| New `include/regional_save.h`, `src/regional_save.c` | Explicit byte codec, bounded regional containers, registry checks, CRC/SHA streaming and transaction state; proposed names, not existing files |
| `src/save.c`, `src/load_save.c`, `src/new_game.c` | All write/load/chunk/initialization paths, validated startup selection, memory-lifetime/exclusion hooks and unchanged existing-field semantics |
| `src/intro.c`, `src/reload_save.c`, `src/main_menu.c`, `src/save_failed_screen.c`, relevant strings | Loaded/recovered/blocked status gates and non-destructive transaction-failure handling |
| Save callers in start menu, HOF FRLG, trade, record mixing, berry blender, Frontier/Pike/Pyramid, contest and link tasks | Actual error/completion propagation, thirteen-body-plus-header task timing, once-only preparation and skip-PC semantics; change only callers whose contracts require adaptation |
| New local format registry and manual codec/converter/qualification tools | Pin source/layout/content identities, exact fixture allowlist, copy-only migration and implementation-backed fault checks; no hosted jobs |

Source-anchor/caller inventory is preserved in the [transaction analysis](../_local/evidence/save-foundation-proposal/transaction-design.md); [layout analysis](../_local/evidence/save-foundation-proposal/layout-design.md) and [independent review](../_local/evidence/save-foundation-proposal/independent-critical-review.md) record the bounded design findings. This consolidated document defines the selected digest/layout/migration proposal where working alternatives differ.

Planning estimates separate adaptation from qualification; they describe relative engineering effort, not a promised turnaround:

| Bounded package | Adaptation estimate | Qualification estimate |
|---|---|---|
| Extension, codec, registry and ARM assertions | Medium | Medium: independent vectors and actual layout/budget checks |
| Save coordinator and synchronous/incremental caller contracts | High | High: every write family, interruption, callbacks and timing |
| Startup/load/reload/recovery and failure UI | Medium | High: malformed-bank, unsupported and recovery cases |
| Three-fixture copy converter | Medium | Medium: byte preservation, idempotence and native loading |
| Complete patch, manifests and dependency notice | Low | Low: reproducible clean outputs and boundary checks |

The transaction's writer/buffer lifetime audit drives the largest effort. If it needs broad scheduling/link restructuring, stop rather than expanding this package. Qualification uses the finite tests below; it does not restart unrelated campaign or art work.

## 9. Finite qualification before any Johto progression

| Check | Required evidence after implementation approval |
|---|---|
| Actual layouts and unchanged targets | ARM prefix/total/field assertions; old Save1/2/PC offsets/checksum lengths; non-FireRed preprocessing/ABI equivalence; appropriate separate HnS clean regression. No LeafGreen build success assumed. |
| Codec and identity | Real implementation versus independent CRC/SHA/framing vectors; lengths/IDs/unsupported-version rejection; no host-model-only pass |
| Write paths | Normal/full, HOF main state, formerly partial and both incremental task families; correct error/handshake completion and no repeated preparation |
| Main/extension atomicity | On newly created disposable copies, interruption after each logical body sector and during ID0 prepare/erase/program/signature commit; old complete bank or complete new bank, never mixed state |
| Malformed/recovery cases | Duplicate/out-of-range/missing IDs, bad rotation/parity, mixed/non-adjacent counters, wrap, native/extension corruption, digest mismatch, bad lengths/content/layout, one valid bank, two unusable banks, first-save interruption |
| Concurrent writers | Timer/RTC ticks and continue-warp callback during incremental save; controlled forbidden producer/ASLR/shared-buffer attempt aborts safely; no unbounded scheduler rewrite |
| Copies of the three B2 fixtures | Trainer/rival/Dex, complete party identity/stats/moves/ownership, inventory/money/coins, Kanto flags/vars, location and prefix retained; blank Johto; original hashes unchanged; repeated conversion nonduplicating |
| Occupied PC in the new format | Full save persists live storage; partial mode retains the previously persisted PC even if diagnostic live PC differs; preserve full boxed Pokémon data, names/items and fusion slots |
| Minimal native acceptance | One fresh natural FireRed opening/starter/first save; two normal Save/full quit/cold Continue cycles with that fresh character, once in each B2 region; converted B2 character also loads with visible and read-only full-state comparison |
| Capacity/performance | Actual ROM/EWRAM/IWRAM deltas, bounded scratch, stack/heap peaks and save/link timing; no capacity claim based on arithmetic alone |

All rows are currently **NOT RUN**. No repeated B0 soak, ten-trip repeat or full campaign run is requested solely for this save change. Diagnostic/fault fixtures do not prove natural story reachability. Browser requalification remains owner-deferred; it is a separate later runtime gate, without A changes.

## 10. Review decision and stop boundaries

**GO to implementation approval of this proposal; HOLD implementation until approved, and HOLD Johto progression until the foundation passes.** The exact approval package is: FireRed-only version 6/FRJS1, 1,332-byte SB3 with stored 256-byte reserve, all-write-path alternating transactions with durable-PC partial semantics, pre-copy validation/recovery/blocked-file behavior, 6,784-byte additional EWRAM ceiling and the three-hash copy-only converter. Approval would remain development qualification, not a production save guarantee.

Stop for review if the implementation needs moved live fields, more allocation/scratch, reduced reserve, another capacity change, broad scheduler/link restructuring, feature removal or a larger legacy-input promise. Keep the existing main-block margin, roamer fidelity, special-sector atomicity and old-ROM downgrade limits explicit.

B owns saves, campaign behavior, RTC/palette runtime, budgets and final integration. C's frozen 010 handoff remains unchanged; give C the measured memory-budget delta when available, with no unrelated art restart. No Workstream A/C repository edits, multiplayer/Discord integration, NAS/network changes, global installations, CI/automation, commit, push or remote writes are included. Stop after the save-foundation review/qualification; a named Johto progression slice needs its own approval.

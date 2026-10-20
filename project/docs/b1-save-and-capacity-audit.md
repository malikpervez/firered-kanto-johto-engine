# B1 save and capacity audit

Owner-authorized audit, October 9–10, 2026. **Recommendation: HOLD before save implementation or a 25-trainer engine commitment.** Continue the separately authorized B1 content/browser audit. The existing extension is a plausible allocation for independent Johto records, but its integrity, save-path coherence, legacy recognition and runtime budget need an approved design and executed qualification. No save format, source, configuration, roamer, ROM or native save changed in this audit.

`VERIFIED IN SOURCE` below means a static finding. Existing ARM/linker measurements are reused executed B0 evidence. All proposed extension, corruption, interruption, migration, crowded-map and runtime-watermark tests are **NOT RUN**. B0 normal-save/cold-reload results remain bound to their original ROMs and sessions; they do not establish those new properties.

## Identity and evidence

Pinned source `167aa6d537b109bb229c231ddce4616974c4da71`, `Release-v2.0.6`, plus complete patch `0010-firered-fresh-monotype-default.patch`, SHA-256 `3e9b6b003557cbfacff59706ad04e4f7f2fdd58bc6162be995f91dc09742d5f3`. Actual ARM ABI uses GCC14.2.1, ARMv4T Thumb and `-mabi=apcs-gnu`. Source comments containing old hexadecimal offsets are not the layout authority.

| Actual successful build | ROM SHA-256 | Manifest SHA-256 |
|---|---|---|
| FireRed010 | `3e504731d9dd3c02ec273dc257c86f557caaf8c9b933d2f0ff73558c2e121a39` | `fbf75c3a47c21c88ad6633b0f6a176b131b797897ff8bdd19f4161966f0f671e` |
| HnS010 | `4bb58fe3c06bc0b60146aa946cbc34f087efa607f525f68e0a1e99c0db9cde75` | `21ea87bf5c2343bf6a8e14815cea30a3ecb1500ac345d2ea1281045b88054edc` |

The HnS009 native session retains its009 binding; its ROM/ELF/map were measured byte identical to010. Source commit, patch/configuration fingerprint, ROM identity, content revision and a future native-format identifier are separate concepts. Current native `SAVE_VERSION=5` is not the proposed extension schema.

All private paths resolve under `[LOCAL_WORKSPACE]/`. New evidence is `_local/evidence/b1/save-capacity/`:

| Evidence | Contents |
|---|---|
| `field-inventory-complete.json` | Every existing compiler-measured addressable top-level member, size/offset/alignment, target and manifest binding; storage inventory corrected from the preserved draft |
| `conditional-and-bitfield-declarations.json` | Actual source declarations and preprocessor conditions for blocks, options, ChallengeSettings, Pokédex and WarpData |
| `field-callers.json` | All lexical direct save-member references and whole-block/pointer references in `src/include/data`;131 direct reference groups and42 other pointer references |
| `persistent-id-candidates.json`, target `effective-macros.txt`, `preprocessing.json` | Actual target macro selectors, alias resolution, candidate symbolic/literal references and real preprocessing exit0 |
| `capacity.json` | Exact successful010 linker log/map/manifest hashes, allocations and output sections |
| `content-and-render-capacity-v2.json` | Actual generated non-NULL maps/layouts, graphics/font/static limits and source hashes; includes the upstream `gMapGrouop_OutdoorAlola_Hns` spelling |
| `source-bindings-v2.json`, `audit-index-v2.json` | Source hashes, command/outcome inventory and new evidence hashes |

Existing immutable references: `_local/evidence/native/repair-10-full-abi/actual-final-abi-comparison.json` SHA-256 `6fd387e62af4478f65138a164b38480e946cd878819ae1541f1c474795845bbb`; `_local/evidence/native/repair-10-compiled-fields/native-field-map.json` SHA-256 `36147a9179cfcf16c545214df5d00550fff7a9760b882ab0830d6b52ef6b81c9`. No new compilation or native-save/ROM-byte read was needed. Macro preprocessing emits text only.

The caller index includes inactive target branches deliberately. It records every direct `gSaveBlockNPtr->member`, `gSaveblock3.member`, `gPokemonStoragePtr->member` mention and other pointer uses, rather than asserting that a lexical match is necessarily a read, write or selected caller. Generic flag/var/script access, computed indices, pointer aliases, encrypted Pokémon internals and whole-block copies need semantic review for any proposed change. Individual C bitfield offsets were not measured by the existing probe. Neither that limitation nor a missing direct caller grants permission to reuse storage.

## Native allocation and serialization

| Allocation | FireRed used/capacity/free | HnS used/capacity/free | Logical sector IDs |
|---|---:|---:|---|
| SaveBlock1 |15868 /15872 /4 |15760 /15872 /112 |1–4 |
| SaveBlock2 |3892 /3968 /76 |3892 /3968 /76 |0 |
| SaveBlock3 |52 /1624 /1572 |52 /1624 /1572 |116-byte extension chunk in each ID0–13 |
| Pokémon storage |34144 /35712 /1568 |34144 /35712 /1568 |5–13 |

All three blocks have measured4-byte ARM alignment. Storage contains14×30 boxed Pokémon plus four live fusion slots; its33600-byte boxes,126-byte names,14-byte wallpapers and400-byte fusion array are preserved. Spare storage payload belongs to this allocation, not SaveBlock1. Likewise76 bytes in SaveBlock2 cannot enlarge SaveBlock1 without a layout/serialization change.

LeafGreen and Emerald macro probes reused the actual FireRed generated-header context; they are **diagnostic types, not successful builds or runtime tests**. Save1 is15952 for LeafGreen (80 bytes over its allocation) and15752 for Emerald (120 bytes free); Save2/3 remain3892/52. All existing measured members match009 and the approved004 layout. No LeafGreen repair is approved.

Each bank uses14×4096-byte physical sectors:3968 payload bytes,116 extension bytes, then12 footer bytes. Measured offsets: ID4084/u16, checksum4086/u16, signature4088/u32 (`0x08012025`), counter4092/u32. Two banks occupy physical0–27;28–29 are Hall of Fame,30 Trainer Hill,31 recorded battle. They are not unused extra sectors. ID0 carries3892 checksum-covered payload bytes; FR ID4 carries3964; storage ID13 carries2400. Slack outside the selected payload size is excluded from that payload's checksum.

SaveBlock3 is one52-byte RAM structure distributed by **logical sector ID**, not52 bytes in every sector. Currently only ID0 copies52 bytes. The extension's nominal1572-byte headroom is64 remaining bytes in that chunk plus13×116 bytes. A future structure also costs EWRAM; it does not gain RAM from spare flash.

Source authority: [save header]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/include/save.h:6), [allocation/assertions]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/src/save.c:60), [save structs]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/include/global.h:1198), [storage]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/include/pokemon_storage_system.h:20).

## Write, load, version and recovery findings

| Path | VERIFIED IN SOURCE | Design consequence |
|---|---|---|
| Normal save/Hall of Fame | `WriteSaveSectorOrSlot` increments counter and rotation, selects counter-parity bank and writes all14 sectors. Failure restores RAM counter/rotation bookkeeping; already-written flash sectors remain. | Preserve the old bank and rotation model. Prove coherent recovery with interrupted writes; bookkeeping rollback is not a runtime fault test. |
| Sector payload checksums | `HandleWriteSector`/`HandleReplaceSector` copy SB3 chunks, then checksum only the selected payload size. The checksum sums little-endian u32 values with32-bit wrap and folds to16 bits. | SB3 and footer are outside ordinary checksum coverage. This is a corruption check, not authentication. |
| Bank validation | `GetSaveValidStatus` checks signature, payload checksum and presence of all logical-ID bits. It retains the counter from the last valid sector visited; it does not compare every sector counter or validate ID bounds before `locations[id]`. | Do not presume generation coherence or safe handling of malformed IDs. Source possibility of mixed generations is not an executed corruption result. |
| Bank selection/recovery | Both valid banks: choose greater retained counter, including special max-u32→0 wrap. One valid bank: choose its counter; error status if the other bank is damaged. Neither valid: EMPTY or CORRUPT and counter/rotation zero. | A future extension must be validated with its own bank's main payload, and fallback must select a coherent pair. Existing B0 strict inspector is stricter than this loader. |
| Copy from flash | `TryLoadSaveSlot` calls `CopySaveSlotData` even after EMPTY/CORRUPT status. Copy selects bank by counter parity, checks each payload, copies valid bytes and its SB3 chunk. It does not check that sector counter equals the selected counter or clear/reject an extension as a whole. | Stale or partly copied RAM must not become valid new progression. Future validation must finish before committing staged data or running migrations. |
| Partial link/Battle Frontier saves | `SAVE_LINK`/`SAVE_EREADER` and `WriteSaveBlock2`+`WriteSaveBlock1Sector` replace IDs0–4 in the current bank; signature bytes are committed separately. They retain the existing bank/counter. | Only the first580 extension bytes are refreshed. A longer extension can retain stale tail chunks. Even a shorter extension needs its integrity recalculated consistently with the actually persisted PC/main payload. |
| Incremental full link saves | `LinkFullSave_*` writes the full slot incrementally and replaces/commits the final signature. | Every write/commit path needs explicit extension transaction handling, without breaking link timing or recovery. |
| Existing version migration | After load/copy, wrong `saveVersionMagic` becomes version0 with magic `0xE8F828BC`; upgrades1/2/4/5 run, keeping common version bookkeeping and v4 rematch reset. HnS-specific actions are guarded. | This upgrades events after structural loading. It cannot safely recognize an old different struct/checksum layout or distinguish every target/ROM/content revision. |
| New game/ASLR | Whole Save1/2/Storage buffers are cleared/copied/moved through ASLR wrappers. `ClearSav3` clears its whole structure and resets fakeRTC. NewGame preserves selected ChallengeSettings across the clear. | Reuse must account for whole-block clear/copy, startup selection, snapshots and aliases. Keep every existing field meaning and offset unless separately approved. |

Exact source anchors: [full save/sector write]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/src/save.c:156), [load/copy/validation]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/src/save.c:484), [checksum and all save types]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/src/save.c:696), [incremental paths]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/src/save.c:810), [post-load migration]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/src/save.c:896), [logical SB3 chunks]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/src/save.c:1150), [RAM initialization/movement]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/src/load_save.c:33).

These paths have not been modified or fault-injected. Existing native saves established successful ordinary early saves/cold reloads only. They did not exercise occupied PC migration, corrupt headers, changed lengths, torn extensions, partial saves, counter wrap or interrupted conversion.

## Persistent IDs and reservation candidates

Both actual targets allocate304 flag bytes/2432 bit IDs and256 u16 variables at `0x4000–0x40FF`. These are allocated spans, not free counts. IDs0–31 are temporary flags; variables0x4000–0x400F are cleared on map load. Special flag/variable IDs are separate RAM-only storage. Daily clearing ranges differ: FR0x390–0x3CF, HnS0x920–0x95F. Trainer flag ranges are FR0x500–0x7FF/HnS0x500–0x85F. The common engine block is pinned at0x960–0x97F; the effective HnS `BUILD_FLAGS_END` is0x95F, so an earlier comment claiming69 spare HnS IDs is not an allocation authority.

`GetFlagPointer`/`GetVarPointer` choose a namespace without checking the complete persistent-array upper bound; future IDs need explicit bounds and alias tests. One flag cannot have unrelated Kanto and Johto meanings merely because it shares a number. Trainer completion, daily resets, map hide flags, challenge settings and generic scripts must be mapped deliberately.

| Candidate reviewed | Evidence | Disposition |
|---|---|---|
| `VAR_UNUSED_0x404E` | Effective alias `VAR_NATIONAL_DEX_FRLG`; `config/randomizer.h` selects the same variable for species mode. | **Do not allocate.** An unused-name label conceals other meanings. |
| `FLAG_UNUSED_0x4A7`, `0x4A8` | Same names/values in both effective targets; no symbolic caller or literal token outside constant declarations in the scanned source. Outside temp/daily/trainer/engine spans. | Candidates for individually reviewed small states; not allocated or proven free against computed access/imports. |
| Unnamed engine slot13 (`0x96D`) | No effective `FLAG_` alias or literal/source caller found; inside the pinned shared engine block. | Engine-owned reservation; do not consume for a regional story without an agreed allocation and update policy. |
| `VAR_UNUSED_0x40F7`, `0x40FF` | Multiple same-value FRLG/HnS aliases; no symbolic caller/literal token outside declarations found. Persistent, not daily/temp-cleared variables. | Candidates only; aliases, runtime-selected configuration and incoming story imports still require review. |

The scan also retains resolved aliases and literal matches, including inactive branches. Dynamic `FlagSet(id)`, trainer arithmetic, ranges and imported scripts make absence of a name insufficient. **Certified available persistent IDs: not established.** No count of purported unused IDs is granted to B or C.

Reservation source-only findings:

| Existing FR member | Bytes / offset | Findings and restriction |
|---|---:|---|
| `roamerPadding` |84 /14616 | No named direct consumer found; whole Save1 serialization copies it. Reserved for three extra roamers; future FireRed roamer repair is unresolved. Do not reclaim more under this audit. |
| `dexPadding1`, `dexPadding2` |55 /14836;55 /15027 | No named consumer found; reserved by source for future dex expansion. Preserve species/dex capacities and offsets; not C graphics space. |
| `unused_9C6` |2; exact measured offset in appendix | No direct named consumer found. Whole-block initialization/version/layout expectations remain relevant. Tiny in-place candidate only after a supported-format decision. |
| Save2 `filler_90` |8 /144 | No direct named consumer found. Legacy region/time offsets and whole-block copies remain relevant. |
| Implicit padding / ChallengeSettings spare bits |Compiler-dependent | Save2 options bits are live; ChallengeSettings remains exactly32 bytes by assertion. Individual spare bit offsets have not been measured. No allocation approved. |

Comments and lexical evidence support a shortlist, not a safe-reuse certificate. Replacing reservation bytes with a versioned union could preserve downstream offsets, but existing supported saves would need explicit initialization and identity/integrity rules. Existing `FREE_*` selections are part of010; toggling them to remove live gameplay is not a proposed capacity fix.

Source anchors: [persistent/reset accessors]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/src/event_data.c:52), [accessor namespaces]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/src/event_data.c:194), [pinned engine IDs]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/include/constants/flags.h:2476), [variable spans]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/include/constants/vars.h:280), [reservations and conditional fields]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/include/global.h:1283).

## Proposed field ownership and save policy

This table is a design proposal, not implemented behavior. B owns native field meanings, IDs, save transactions and engine resource allocation; C owns approved art assets within B's budget. C cannot repurpose bytes/flags, add save fields, change RTC policy or patch time/palette code. A's storage/account authority requires a later owner-approved contract; this audit does not inspect A.

| State | Proposed canonical owner/location | Decision still needed |
|---|---|---|
| Trainer name/ID/gender/ownership |Existing Save2, one trainer |No regional replacement or reset |
| Party/PC, OT/personality/species/forms/stats/experience/moves/PP/held items/egg state |Existing party/Storage and Pokémon representation |Supported migration coverage; retain full state, not a species-only profile |
| Money/bag/items/collection/dex |Existing shared state |Owner confirms shared resource and dex presentation policy; no invented regional resets |
| Kanto/Sevii story, rival, starter, trainer defeats |Existing FR Save1 flags/vars/rival and script meanings |Keep canonical writers; new metadata may reference them without creating conflicting mirrors |
| Johto story, badges, rival/starter/grant states, trainer defeats |New versioned regional record + stable-ID mapping |Johto starter entitlement, reward idempotence, imported-ID redirection and episode scope |
| Badge-based permissions/obedience/caps |Policy reads regional records; badge storage alone does not grant permissions |Current common badge consumers use capped8-entry tables; owner chooses cross-region field permissions/caps |
| Current map/position and return destinations |Existing current WarpData plus proposed stable travel record |Safe arrivals, map revisions, entry timing and final unlock rules |
| RTC/day/night/daily events |Existing shared fakeRTC/time fields and engine policy |Time reset/rollover/daily-event behavior across regions; no new RTC saved fields assumed |
| Online identity/transactions |Future joint A/B contract |Native trainer ID is not authenticated account identity |

Recommended later scope: **FireRed-derived combined target only**, with current HnS/LeafGreen/Emerald layouts and behavior unchanged. A shared engine save-code change would require target-specific regression even if gated to the new format.

| Input format | Proposed policy for a future combined build |
|---|---|
| Final FR010 experimental fixtures |Optional explicit migration from immutable copies with exact source/ROM/layout provenance; otherwise clearly reject as disposable B0 fixtures with owner approval. Not a production promise. |
| FR009 same measured layout |Do not silently import as equivalent fresh defaults: zero monotype setting changed semantics. Explicit owner-selected recovery/migration or rejection; existing native version cannot identify009 vs010 alone. |
| Earlier FR layout before the84-byte exception; unidentified forks/retail saves |Reject unless an exact legacy schema/fixture and explicit translator are separately qualified. Post-load version5 handling is insufficient. |
| HnS009/010 |Same-ROM native interoperability remains B0 evidence only. Cross-target import is rejected by default; any conversion needs separate product/ID policy and tests. |
| LeafGreen/Emerald/Ruby/Sapphire |Unsupported by this proposal; no inferred compatibility from shared structs or diagnostic macro probes. |
| Future supported player format |Migrate with field-preservation/idempotence/interruption tests, or block incompatible update clearly. Never silently reset a supported player save. |

Distinguish unsupported formats from corrupt supported inputs before loading altered structures. Sidecar provenance may select an explicitly authorized legacy translator, but cannot replace validation of native gameplay state. A valid old save with no new extension must not interpret old extension bytes as completed story. Conversion uses a copy, validates output, preserves original and commits only after qualification; test repeated conversion, interrupted conversion, downgrade rejection and backup restoration.

## Candidate designs and numerical proposal

| Option | Benefit | Cost/limitation |
|---|---|---|
| Existing persistent flags/variables |No extra block size or RAM for a few suitable states |No allocations proven yet; numeric/semantic collision risk, temp/daily reset rules, namespaces must remain stable |
| Audited reservations in place |Can preserve downstream offsets |Small/reserved capacity, unknown legacy bytes and future roamer/dex needs; initialization/integrity still required |
| **Versioned SB3 extension, preferred investigation** |Preserves every existing Save1/2/Storage field and bank geometry; nominal1572-byte room |Current extension unprotected; later transactional loader/partial-save design and additional EWRAM required |
| Move fields into Save2/Storage or explicit serialization |Could use76/1568-byte payload slack when the design no longer fits |Moves/checksum lengths/layout semantics and legacy decode; larger migration, RAM/scratch and regression costs |
| New larger format/sector allocation |Potential future capacity beyond current design |Not supported by this audit; special sectors are occupied, hardware flash and banks fixed. Requires separate format/recovery/engine approval. |

The following **concrete sizing proposal is NOT IMPLEMENTED or owner-approved**. Preserve all existing Kanto native story fields in place, and add one Johto namespace. The Johto limits deliberately cover the current source's whole non-temporary variable span and more than its trainer/non-trainer flag spans; they do not prove that future content meanings or full campaigns fit. Stable-ID translation tables live in versioned ROM content, not an unbounded per-save map list.

| Proposed SB3 allocation | Bytes | Meaning |
|---|---:|---|
| Existing prefix, unchanged offsets |52 |RTC, chain, ChallengeSettings, held registered item |
| New serialized format/integrity header |64 |Identifier/version/header+payload length/flags, generation, content+layout IDs, record count, extensionCRC,32-byte main-payload digest |
| Kanto/Sevii additional metadata |32 |Region-schema/one-time transition bookkeeping; native story/rival remain canonical, no duplicate full Kanto snapshot |
| Johto fixed record |32 |Regional ID/schema, badges, starter/grant state, rival8 bytes and bounded per-region metadata; exact semantics await product decisions |
| Johto event bitset |256 |2048 mapped non-trainer story/system states, mapping/clear rules audited before allocation |
| Johto trainer completion |128 |1024 stable trainer bits; current effective HnS trainer range864 |
| Johto variable records |480 |240 u16 IDs corresponding to current0x4010–0x40FF span; includes graphics vars conservatively, excludes cleared map-temp vars |
| Shared stable travel/return record |32 |Bounded region/map revision/arrival/return data; current WarpData retained |
| **Proposed growth reserve, owner must choose** |**256** |Numerical review starting point, not an approved allocation or guarantee |
| **Total proposed allocated** |**1332** |4-byte aligned serialized size including current prefix |
| **Uncommitted remainder** |**292** |1624−1332; not automatically promised to another feature |

Before reserve, total1076; new meaningful data1024 beyond the52-byte prefix. With a declared256-byte reserve the proposed RAM structure would grow1280 bytes. On unchanged FR linker totals that leaves13132 bytes to the EWRAM limit, before code globals, scratch and runtime allocations; this is arithmetic, **not a compiled or peak-tested candidate**. Implementing reserve as actual stored bytes versus an allocation allowance must be agreed explicitly. No bytes move/change meaning in the existing blocks under this proposal.

The header's64 bytes can be budgeted as4-byte format ID;2-byte version/header length/payload length/flags;4-byte generation/content revision/layout identity;2-byte record count/reserved;4-byte extension CRC;32-byte digest binding logical payloads. Serialization uses documented byte order/lengths, not compiler bitfield layout. The digest algorithm and exact coverage/commit protocol need review; it is not an authentication credential. None of these identifiers exist in010.

At1332 bytes SB3 spans12 logical chunks, including IDs5–11 skipped by partial Save1/2 writes. Therefore **fitting the byte budget does not make the proposal safe**. Before coding, select transaction semantics for every normal/HOF/incremental/partial path, validation bounds, coherent main+extension loading and fallback. A blanket uniform-counter check cannot be bolted onto existing behavior without accounting for legitimate same-counter partial saves and stored PC state. Stage/validate data before applying migrations; validate both banks independently; never mix one bank's extension with another's payload, accept a torn extension, or manufacture default/completed progression on corruption. Keep payload checksums, assertions, rotation and bank count; changes to recovery/commit behavior require explicit approval.

If required regional records plus agreed reserve exceed1624, first refine the audited story/variable needs rather than shrinking existing live state. Then evaluate explicit serialization/redistribution on exact schemas. No claim that the current proposal is the final full-game capacity requirement.

## ROM, RAM and C art limits

These are **actual successful010 linker allocations**, not ROM file length or runtime usage. Both padded ROM files are33554432 bytes.

| Target | ROM used / region remainder | EWRAM used / remainder | IWRAM used / remainder |
|---|---:|---:|---:|
| FR010 |29853828 /3700604 |247732 /14412 |25944 /6824 |
| HnS010 |31707908 /1846524 |248096 /14048 |25704 /7064 |

EWRAM includes the115968-byte `gHeap` allocation; that is not free heap at runtime. IWRAM remainder must cover descending system/IRQ stacks and other reserved activity: startup sets system SP at IWRAM_END−0x1C0 and IRQ SP at IWRAM_END−0x60. No stack depth, heap high-water/fragmentation, map-transition peak, frame time or browser peak was measured in B1. Adding the two separate targets' ROM sizes is not a valid merge estimate; shared assets may deduplicate, and importing selected maps still needs actual linker comparison.

| Engine/C constraint | VERIFIED IN SOURCE / generated output | Consequence |
|---|---|---|
| Active map objects |16 `ObjectEvent` slots; local player, NPCs/followers share them |25 trainers alone exceed this path by9, before NPCs/effects. **Ordinary object-event rendering cannot satisfy the crowded-map requirement as configured.** |
| Saved map templates |64 templates distinct from active slots |Raising active count changes saved `objectEvents[]` and RAM; cannot be an art-only edit or unapproved Save1 growth |
| Software sprite/OAM emit limits |64 sprite slots; default OAM emission limit64; hardware OAM128 entries |One sprite may emit several subsprites/reflections/effects;25 does not imply25 total OAM entries. No crowded-map execution. |
| OBJ palettes |16 banks of16 colors (color0 transparent); normal field reserves12, leaving4 for effects/UI |25 simultaneous unique palettes cannot be assumed. Existing player/special palette slots swap; shared palette cohorts need B-approved planning. No time/palette-code patch by C. |
| OBJ graphics tiles |1024×32-byte4bpp tile units =32768 bytes; reservations/fragmentation affect allocator |A16×32 frame is256 bytes/8 units;25 such independent display frames alone are6400 bytes/200 units. Animation sheets, variants, reflections/effects and actual shared-tag allocation remain unmeasured. |
| Existing FR avatar descriptor |RedNormal16×32; descriptor size512; frame tables specify2×4 tiles |Descriptor size and display-frame size differ. C must use an agreed format/frame table/OAM/animation contract, not infer total runtime allocation from one number. |
| Fonts/glyphs |14 font enum entries; source Latin width tables have512 entries; ordinary byte plus `CHAR_EXTRA_SYMBOL` accesses upper256 |Existing encoding/control codes/name limits apply (trainer name7+EOS). This is not512 free new symbols or arbitrary Unicode. New glyphs/names and25 visible labels require separate UI/VRAM tests. |
| Map groups/IDs |106 generated group slots; actual non-NULL maps FR417/HnS560; highest selected map index122/107 |WarpData stores signed8-bit group/num and uses sentinel values; do not treat256 arbitrary values as safe persistent IDs. Stable mapping owned by B, not C art files. |
| Layout IDs |1331 generated indexed slots; selected non-NULL FR344/HnS546; Save1 mapLayoutId u16 |NULL holes/compile-time selection are not valid destinations. Numeric IDs need versioned mapping and valid-arrival checks. |
| Flags/vars |304 flag bytes,256 u16 variables |No certified free allocation count. C cannot take unused-looking bits or story IDs. |

Sources: [object/saved-template counts]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/include/constants/global.h:98), [sprite limits/allocator]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/src/sprite.c:639), [palette ownership]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/include/event_object_movement.h:14), [graphics contract]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/include/global.fieldmap.h:322), [FR avatar]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/src/data/object_events/object_event_graphics_info.h:4472), [font rendering]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/src/text.c:1545), [WarpData]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/include/global.h:754), [linker regions]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/ld_script_modern.ld:7), [startup stacks]([LOCAL_WORKSPACE]/_local/worktrees/repair-10-firered/src/crt0.s:9).

A future dedicated transient remote-avatar renderer could avoid persistent ObjectEvent growth, with common palette cohorts, graphics sharing and measured OAM/tile/RAM budgets. Expanding ObjectEvent capacity instead touches Save1 and costs saved+RAM arrays, currently impossible to assume within4 bytes. Visibility limiting is a product tradeoff and cannot silently reduce the owner's25-trainer requirement. These alternatives are proposals only; no multiplayer or renderer was implemented/certified.

## Review gate and finite remaining work

AUDIT-01 has an exact top-level measured inventory, caller/alias index and source save-path review; semantic alias/bitfield qualification remains required **before any reuse**. AUDIT-02 has the numerical proposal above, but product fields, integrity transactions and growth reserve are unapproved. No later SAVE/REGRESS/TRAVEL implementation test is newly passed by this report.

The next owner decisions are: supported inputs (including whether disposable FR010 fixtures warrant migration), shared resources and regional starter/permission rules, agreed regional-record counts and numerical reserve, format/integrity/partial-save recovery design, exact FireRed-only target scope, and the25-trainer rendering strategy. The preferred later design keeps current Kanto payloads intact and investigates a protected/versioned SB3 record; it does not grant implementation approval.

Finite later work, with adaptation and testing separated: finish stable event/trainer/variable mappings and record meanings; specify/independently review serialization+all-save-path commit/recovery; implement only after approval with actual ARM offsets/linker checks; then qualify fresh normal saves, occupied PC fixtures, malformed/truncated/mixed-generation data, interrupted writes/conversions, repeated migration and downgrade/restore. Runtime memory/graphics budgets need dedicated peak fixtures and crowded-map stress, beyond C asset conversion. No guaranteed schedule is implied.

The FireRed roamer defect, natural Sevii/full-campaign reachability, broad RTC qualification, browser gate, complete content/fidelity matrices and rights remain separate B1/release concerns. This report neither repairs nor waives them.

## Measured member appendix

The following generated appendix lists actual FR010 addressable members (decimal bytes); HnS differences are explicit. Options bitfields remain live at Save2 bytes20–23; ChallengeSettings nested bitfields are recorded in private source declarations, not certified as spare bits. Full diagnostic LeafGreen/Emerald values and all field callers are in the private JSON inventory.


### SaveBlock1

Total15868 bytes.

| Member | Offset | Size | HnS010 difference |
|---|---:|---:|---|
| `saveVersion` |0 |2 |Same |
| `pos` |4 |4 |Same |
| `location` |8 |8 |Same |
| `continueGameWarp` |16 |8 |Same |
| `dynamicWarp` |24 |8 |Same |
| `lastHealLocation` |32 |8 |Same |
| `escapeWarp` |40 |8 |Same |
| `savedMusic` |48 |2 |Same |
| `weather` |50 |1 |Same |
| `weatherCycleStage` |51 |1 |Same |
| `flashLevel` |52 |1 |Same |
| `mapLayoutId` |54 |2 |Same |
| `mapView` |56 |512 |Same |
| `playerPartyCount` |568 |1 |Same |
| `playerParty` |572 |600 |Same |
| `money` |1172 |4 |Same |
| `coins` |1176 |2 |Same |
| `registeredItem` |1178 |2 |Same |
| `pcItems` |1180 |200 |Same |
| `bag` |1380 |2612 |Same |
| `pokeblocks` |3992 |320 |Same |
| `berryBlenderRecords` |4312 |6 |Same |
| `saveVersionMagic` |4320 |4 |Same |
| `unused_9C6` |4324 |2 |Same |
| `trainerRematchStepCounter` |4326 |2 |Same |
| `trainerRematches` |4328 |100 |Same |
| `objectEvents` |4428 |576 |Same |
| `objectEventTemplates` |5004 |1536 |Same |
| `flags` |6540 |304 |Same |
| `vars` |6844 |512 |Same |
| `gameStats` |7356 |256 |Same |
| `berryTrees` |7612 |1024 |Same |
| `secretBases` |8636 |3200 |Same |
| `playerRoomDecorations` |11836 |12 |Same |
| `playerRoomDecorationPositions` |11848 |12 |Same |
| `decorationDesks` |11860 |10 |Same |
| `decorationChairs` |11870 |10 |Same |
| `decorationPlants` |11880 |10 |Same |
| `decorationOrnaments` |11890 |30 |Same |
| `decorationMats` |11920 |30 |Same |
| `decorationPosters` |11950 |10 |Same |
| `decorationDolls` |11960 |40 |Same |
| `decorationCushions` |12000 |10 |Same |
| `tvShows` |12012 |900 |Same |
| `pokeNews` |12912 |64 |Same |
| `outbreakPokemonSpecies` |12976 |2 |Same |
| `outbreakLocationMapNum` |12978 |1 |Same |
| `outbreakLocationMapGroup` |12979 |1 |Same |
| `outbreakPokemonLevel` |12980 |1 |Same |
| `outbreakUnused1` |12981 |1 |Same |
| `outbreakUnused2` |12982 |2 |Same |
| `outbreakPokemonMoves` |12984 |8 |Same |
| `outbreakUnused3` |12992 |1 |Same |
| `outbreakPokemonProbability` |12993 |1 |Same |
| `outbreakDaysLeft` |12994 |2 |Same |
| `gabbyAndTyData` |12996 |12 |Same |
| `easyChatProfile` |13008 |12 |Same |
| `easyChatBattleStart` |13020 |12 |Same |
| `easyChatBattleWon` |13032 |12 |Same |
| `easyChatBattleLost` |13044 |12 |Same |
| `mail` |13056 |576 |Same |
| `unlockedTrendySayings` |13632 |5 |Same |
| `oldMan` |13640 |64 |Same |
| `dewfordTrends` |13704 |40 |Same |
| `contestWinners` |13744 |416 |Same |
| `daycare` |14160 |288 |Same |
| `linkBattleRecords` |14448 |88 |Same |
| `giftRibbons` |14536 |11 |Same |
| `externalEventData` |14547 |20 |Same |
| `externalEventFlags` |14567 |21 |Same |
| `roamer` |14588 |28 |offset14588, size112 |
| `roamerPadding` |14616 |84 |offset14700, size84 |
| `dexSeen` |14700 |136 |offset14784, size136 |
| `dexPadding1` |14836 |55 |offset14920, size55 |
| `dexCaught` |14891 |136 |offset14975, size136 |
| `dexPadding2` |15027 |55 |offset15111, size55 |
| `trainerHillTimes` |15084 |16 |offset15168, size16 |
| `recordMixingGift` |15100 |16 |offset15184, size16 |
| `lilycoveLady` |15116 |64 |offset15200, size64 |
| `trainerNameRecords` |15180 |240 |offset15264, size240 |
| `registeredTexts` |15420 |210 |offset15504, size210 |
| `trainerHill` |15632 |12 |offset15716, size12 |
| `waldaPhrase` |15644 |24 |offset15728, size24 |
| `towerChallengeId` |15668 |4 |Absent |
| `trainerTower` |15672 |48 |Absent |
| `rivalName` |15720 |8 |Absent |
| `route5DayCareMon` |15728 |140 |Absent |
| HnS-only `momSavings` |— |— |offset15752, size8 |

### SaveBlock2

Total3892 bytes.

| Member | Offset | Size | HnS010 difference |
|---|---:|---:|---|
| `playerName` |0 |8 |Same |
| `playerGender` |8 |1 |Same |
| `specialSaveWarpFlags` |9 |1 |Same |
| `playerTrainerId` |10 |4 |Same |
| `playTimeHours` |14 |2 |Same |
| `playTimeMinutes` |16 |1 |Same |
| `playTimeSeconds` |17 |1 |Same |
| `playTimeVBlanks` |18 |1 |Same |
| `optionsButtonMode` |19 |1 |Same |
| `pokedex` |24 |120 |Same |
| `filler_90` |144 |8 |Same |
| `localTimeOffset` |152 |8 |Same |
| `lastBerryTreeUpdate` |160 |8 |Same |
| `gcnLinkFlags` |168 |4 |Same |
| `encryptionKey` |172 |4 |Same |
| `playerApprentice` |176 |44 |Same |
| `apprentices` |220 |272 |Same |
| `berryCrush` |492 |16 |Same |
| `pokeJump` |508 |16 |Same |
| `berryPick` |524 |16 |Same |
| `hallRecords1P` |540 |864 |Same |
| `hallRecords2P` |1404 |168 |Same |
| `contestLinkResults` |1572 |40 |Same |
| `frontier` |1612 |2272 |Same |
| `rivalName` |3884 |8 |Same |

### SaveBlock3

Total52 bytes.

| Member | Offset | Size | HnS010 difference |
|---|---:|---:|---|
| `fakeRTC` |0 |12 |Same |
| `dexNavChain` |12 |1 |Same |
| `challengeSettings` |16 |32 |Same |
| `registeredItemHold` |48 |2 |Same |

### PokemonStorage

Total34144 bytes.

| Member | Offset | Size | HnS010 difference |
|---|---:|---:|---|
| `currentBox` |0 |1 |Same |
| `boxes` |4 |33600 |Same |
| `boxNames` |33604 |126 |Same |
| `boxWallpapers` |33730 |14 |Same |
| `fusions` |33744 |400 |Same |

# Save foundation — ARM layout and linked budgets

**October 13, 2026, America/New_York. Executed static qualification: PASS within the approved allocation.** The exact final05 FireRed build changes only the approved SaveBlock3 append and native save-version value. HnS, LeafGreen and Emerald retain their prior layouts and native version 5. A separately executed [bounded runtime observation](save-foundation-runtime-results.md) now covers one full save; campaign-wide heap/stack peaks, native IRQ timing and actual peer timing remain unproven. This report does not establish release readiness or authorize Johto progression.

The interrupted October 10 audit's `all_expected_layout_changes_only=false` was a checker defect: it expected the approved size change but omitted the equally explicit version-5-to-6 transition. Its preserved evidence showed exactly those two changes. No engine field discrepancy was concealed. A separate October 13 checker copy adds only that approved version transition and returns exit **0** against the frozen successful final05 manifests. The original checker and false result remain unchanged.

## Frozen identities

Candidate 0019/final05 adds two FireRed save-caller completion guards. Its save/coordinator/codec source and layout headers are byte-identical to final04. The final04 audit and prior report are preserved locally; fresh final05 probes, manifest checks and binary table inspection all return **0**, with the same linked budgets. Both final05 ROM hashes differ from final04, so native tests must bind to the appropriate artifact rather than assuming byte identity.

Both clean builds apply complete [patch 0019](../patches/0019-firered-save-caller-completion.patch) alone to upstream `167aa6d537b109bb229c231ddce4616974c4da71`. Patch SHA-256: `b398435b7ca39164a0bcc935579fcccb3fd465db1d4d28418b418fc6be612b46`. Both manifests record patch/configuration fingerprint `0a97c6703a1c9722defd49343e791df470adaa0fca5cc657023f103e30c56a3a`, make exit **0** and wrapper exit **0**. Source, effective target configuration, configuration-file hashes, toolchain, build log and all artifact identities remain in those manifests.

| Exact final artifact | SHA-256 |
|---|---|
| [FireRed ROM](../_local/artifacts/save-foundation-05-firered/pokefirered.gba) | `97eb56f51e542eea6a324d59c0c33d4e3b6b91858714174c23ce2db490004f76` |
| [FireRed manifest](../_local/artifacts/save-foundation-05-firered/manifest.json) | `d390054ca75497a773b51e4a9a49f708d452ccd0e1d828468edfc2b0f971800a` |
| [HnS ROM](../_local/artifacts/save-foundation-05-hns/pokehns.gba) | `0cfac50a9db64c0a0a5cc87fbc667b16d9bfd42446fe14a1cf86badfa6608959` |
| [HnS manifest](../_local/artifacts/save-foundation-05-hns/manifest.json) | `3057926fda0570c1737bfb33d0b875aa2966dce876800e875304b7a097859269` |

The audit verified artifact hashes, configuration-file hashes and recorded source-difference hashes before compiling the probes. The actual compiler is locked ARM GNU Toolchain 14.2.Rel1, SHA-256 `07bfe9e74cfe028af639bf38703b2259c608aedee6ff991752084a10b82da614`, using the build's ARM7TDMI/Thumb/APCS GNU ABI. The appended layout uses upstream's existing `FIRERED` selector, with a C assertion against `VERSION_FIRE_RED`; the proposal's enum expression was corrected before implementation. No invented target selector was introduced.

## Actual native layouts

Measurements come from the actual ARM compiler against final05 headers and the preserved B2-04 baseline. Existing full native ABI probes cover all enabled top-level SaveBlock1/2/3 fields, structure alignment and capacities; separate native probes cover PC storage, Pokédex, time and sector/footer fields. Additional preprocessor comparisons verify unchanged definitions, including the original prefix's RTC/settings types and boxed/party Pokémon types. Baseline and current scalar-name sets and values were inspected rather than accepting a size-only comparison.

| Target selector | SaveBlock1 | SaveBlock2 | SaveBlock3 | PC storage | Native version | Change from B2 |
|---|---:|---:|---:|---:|---:|---|
| `FIRERED` | 15,868 | 3,892 | **1,332** | 34,144 | **6** | Only approved SB3 52 → 1,332 and version 5 → 6 |
| `POKEMON_HNS` | 15,760 | 3,892 | 52 | 34,144 | 5 | All measured fields/offsets unchanged |
| `LEAFGREEN` | 15,952 | 3,892 | 52 | 34,144 | 5 | All measured fields/offsets unchanged |
| `EMERALD` | 15,752 | 3,892 | 52 | 34,144 | 5 | All measured fields/offsets unchanged |

LeafGreen/Emerald results are compiler-only header/layout probes. No complete build or gameplay pass for those targets is claimed. LeafGreen's existing 15,952-byte main block still exceeds its unchanged 15,872-byte capacity by 80 bytes; this FireRed foundation does not broaden the reservation change to fix it.

For FireRed, every existing SaveBlock1/2/PC field size and offset remains unchanged. Its SaveBlock3 prefix still has `fakeRTC` at 0 (12 bytes), `dexNavChain` at 12, `challengeSettings` at 16 (32 bytes) and `registeredItemHold` at 48 (2 bytes). Explicit legacy padding occupies 50–51, and the 1,280-byte serialized append starts at **52**. Total size is **1,332**, four-byte aligned; the existing capacity assertion remains enabled. The 256-byte stored reserve and 292-byte uncommitted chunk capacity remain as approved. Original padding and prefix bytes are preserved by the bounded converter.

The existing 4,096-byte sector and footer field offsets remain unchanged: 3,968-byte native payload, 116-byte SB3 chunk, 12-byte footer; ID/checksum/signature/counter at 4,084/4,086/4,088/4,092. The native checksum implementation is unchanged. ROM-binary inspection additionally confirmed that the linked native sector offset/length table is byte-identical to B2 in both FireRed and HnS. FireRed's new linked digest-length table matches that native table exactly:

| Logical ID | Native payload checksum / SHA length |
|---|---:|
| 0 | 3,892 |
| 1–3 | 3,968 each |
| 4 | 3,964 |
| 5–12 | 3,968 each |
| 13 | 2,400 |

Total native payload is **53,904 bytes**; the approved domain/header/ID/length framing yields **53,996 SHA input bytes**. Checksums retain their existing native lengths while the new CRC covers all 1,332 serialized SB3 bytes. The main block still has **four free bytes**, and the FireRed roamer fidelity defect remains open.

## Linked budget and exact allocation

These figures are read from the final linked ELF/map/build output, not a projected allocation. The ROM files are each padded to 32 MiB; “ROM used” below reports linked content.

| Region | B2-04 FireRed used | Final05 FireRed used | Delta | Capacity | Final unused |
|---|---:|---:|---:|---:|---:|
| ROM | 29,939,076 | 29,946,932 | +7,856 | 33,554,432 | 3,607,500 |
| EWRAM | 247,732 | 254,488 | **+6,756** | 262,144 | **7,656** |
| IWRAM | 25,944 | 25,940 | −4 | 32,768 | 6,828 |

The EWRAM increase is exactly **1,280 bytes of SB3 growth + 5,476 bytes of coordinator scratch = 6,756**. The scratch is below its 5,504-byte ceiling; the combined allocation is **28 bytes below** the approved 6,784-byte ceiling. The codec adds no mutable globals. The linked heap remains **115,968 bytes**, with no heap expansion. SaveBlock1/2/PC backing arrays retain their existing ASLR padding; that padding is distinct from serialized save sizes.

Final05 HnS uses ROM **31,707,908**, EWRAM **248,096** and IWRAM **25,704** bytes. It has a 52-byte SB3, the same 115,968-byte heap and no `sFireRedSave` scratch symbol. Its ROM differs from prior HnS candidates; unchanged save layout is not a substitute for the separately required native regression.

The FireRed EWRAM linked end is `0x0203E218`. Its IWRAM linked end is `0x03006554`, leaving **6,380 bytes before the existing system-stack start** at `0x03007E40`; the system-to-IRQ stack-start gap is 352 bytes and the final IRQ range is 96 bytes. These are linker boundaries, not measured stack high-water marks. Individual ARM compiler stack records include a largest observed save-coordinator frame of 64 bytes and codec SHA-transform frame of 96 bytes. They cannot be added or interpreted as a complete call-chain/interrupt worst-case proof.

Runtime heap/stack observations and save/link timing are outside this static audit. The [separate runtime report](save-foundation-runtime-results.md) records one executed full-save case using read-only diagnostic watchpoints and breakpoints. Those observations do not prove instruction-level SP extrema, campaign-wide peaks, actual peer timing or physical flash/power-loss timing. The native/fault qualification and final review report must retain that distinction.

## Independent clean-repeat qualification

**PASS — EXECUTED.** Both `save-foundation-06-repeat` clean builds completed in separate target trees with make/wrapper exit **0**. An independent read-only comparison recomputed the recorded hashes and compared actual file bytes: FireRed and HnS each reproduced final05's **ROM, ELF and map byte-for-byte**. Effective target configuration, configuration-file hashes, upstream source commit, patch-source difference hash, patch/configuration fingerprint and toolchain record also match. The final05 layout/budget evidence and artifact-bound native tests therefore describe these identical repeat binaries; the manifests themselves differ because they record distinct runs and output locations.

| Repeat build manifest | SHA-256 |
|---|---|
| [FireRed repeat06 manifest](../_local/artifacts/save-foundation-06-repeat-firered/manifest.json) | `7669213ece534fe5aad7eeb509641175a48eda942abd4206879784ab01d9f350` |
| [HnS repeat06 manifest](../_local/artifacts/save-foundation-06-repeat-hns/manifest.json) | `d2d5bdcdbeaac97bf65b062a69c6f01eb503570b54df91c473c1dba5b37f3071` |

The [independent comparison](../_local/evidence/save-foundation-resume-01/reproducibility-05-06-2026-10-13/comparison.json), SHA-256 `6054ea0ce635d4d0e58bff618df189e30615c078a864b5dc2939a354b6d25752`, preserves all ROM/ELF/map/configuration hashes, actual build commands, separate build paths, log hashes and exit codes. Reproducibility is an executed build result; it does not turn pending runtime/peer tests into passes.

## Preserved evidence and reproduction

Private evidence stays local and ignored:

- [Resumed ARM comparison](../_local/evidence/save-foundation-resume-01/arm-layout-final05-2026-10-13/actual-foundation-arm-comparison.json): `5af01fe0f93306fba82d6c69e64a78104d0ffb0ce4f4bd21b1be970f9191bf4b`, executed exit **0**, expected changes only **true**.
- [Independent structure/checksum invariants](../_local/evidence/save-foundation-resume-01/arm-layout-final05-2026-10-13/native-structure-and-checksum-invariants.json): `034f1c0a2c0117b0e538f8c5c2daa82a13b1ee9b961000b0aeea13dddaa62479`, executed exit **0**.
- [Additional non-FireRed native-field checks](../_local/evidence/save-foundation-resume-01/arm-layout-final05-2026-10-13/additional-non-firered-native-field-checks.json): `8b8617b20fd5f248746f41a2f02377b9c4a049f64edc948bb03da485525e5d7a`, executed exit **0**.
- [Original interrupted comparison](../_local/evidence/save-foundation-01/arm-layout/actual-foundation-arm-comparison.json): `d2d2bd07b3652801fe6e704b71803f12452327a5ba33e59dc6cd9b37d10e0ddc`, false result preserved unchanged.

The new private checker has only the approved version transition added to its expected differences and writes to a new dated directory. Command lists, exit codes, probe/source/compiler hashes, assembly, static stack records and linked symbol/section outputs are included in the evidence. The independent audit also preserves preprocessed definitions and exact binary table bytes. Re-running either checker into its existing directory intentionally refuses to replace evidence; use a new dated output directory for any subsequent qualification.

No engine source, frozen ROM, original save, Workstream A/C repository, configuration, service or network was changed during this audit. The audit inspected the completed isolated builds; it did not launch a further build, hosted job, commit or remote write. Static layout/budget and clean-repeat qualification are complete for this candidate; native acceptance and the save-foundation review gate remain separate.

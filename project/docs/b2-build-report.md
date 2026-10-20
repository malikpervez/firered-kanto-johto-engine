# B2 travel slice — build and structural verification

**Report updated October 10, 2026, America/New_York; retained build timestamps use UTC.** Final candidate **014** completed a clean FireRed build with exit **0**. An independently recorded incremental build produced byte-identical ROM, ELF and link-map files. This report qualifies compilation and the recorded structural checks only. Candidate 013 was superseded after native testing exposed missing Johto NPCs; final 014 native travel, normal saves and cold reloads are documented separately. No runtime PASS is claimed here.

The owner-approved scope is one FireRed trainer travelling between Pallet Town, New Bark Town and its named House1 interior. B2 preserves the existing save format and stops at its review gate. Workstream A, services, NAS/network configuration and hosted automation remain untouched. Source trees, ROMs, saves and private evidence remain under ignored local paths.

## Candidate and source identity

All recorded builds start from upstream commit `167aa6d537b109bb229c231ddce4616974c4da71` of [pokehns-expansion](https://github.com/PokemonHnS-Development/pokehns-expansion). Each numbered patch is a **complete patch against that commit**, including the prior 010 repairs; apply one patch rather than stacking 010–014.

| Candidate | Complete patch SHA-256 | Size | Role |
|---|---|---:|---|
| [010]([LOCAL_WORKSPACE]/patches/0010-firered-fresh-monotype-default.patch) | `3e9b6b003557cbfacff59706ad04e4f7f2fdd58bc6162be995f91dc09742d5f3` | 21,515 bytes | Frozen B1 foundation; preserved |
| [011]([LOCAL_WORKSPACE]/patches/0011-firered-b2-travel-slice.patch) | `08c64a583419b7573fb5d57129ba065f07732e2f4ac50ef597947d1923b7e104` | 59,298 bytes | Initial B2 candidate; FireRed compile failure retained |
| [012]([LOCAL_WORKSPACE]/patches/0012-firered-b2-travel-slice.patch) | `88d79236b9a8d88189f9d019b91113d7f8ed24c3b2ff4ef528897be3fa5aeddc` | 59,320 bytes | Corrected guide local-ID identifier; intermediate clean build |
| [013]([LOCAL_WORKSPACE]/patches/0013-firered-b2-travel-slice.patch) | `d2b18dce178d05b928966f4b6e45dfb9b65d2fa6bec7de414135b6c5762a5137` | 60,429 bytes | Successful builds; superseded after native travel blocker |
| [014]([LOCAL_WORKSPACE]/patches/0014-firered-b2-travel-slice.patch) | `4260edec61faf85a04e62744f9d5424dbc25cfa37d3bacda54e65d4df69684d1` | 60,431 bytes | Final B2 build candidate; two FireRed NPC graphics corrected |

Final clean source path: `[LOCAL_WORKSPACE]/_local/worktrees/b2-04-firered/`. Its [manifest]([LOCAL_WORKSPACE]/_local/artifacts/b2-04-firered/manifest.json) SHA-256 is `385a5330782851a65c43683fe01d86743fc79180e9d442ea52705ed5200c614b`; its patch/configuration fingerprint is `b00748064970a4f7d83e49a95cd937db4164538ff382601edd5dcb3f228db3a9`. The manifest preserves the applied patch, configuration records, generated tracked diff, source diff and reference/worktree states.

## Executed build record

| Run | Target / patch | Result and actual exit | Exact retained evidence |
|---|---|---|---|
| `b2-01-firered` | FireRed / 011 | **FAIL — EXECUTED**, make `2`, wrapper `2`; no accepted artifacts | [manifest]([LOCAL_WORKSPACE]/_local/artifacts/b2-01-firered/manifest.json), [build.log]([LOCAL_WORKSPACE]/_local/evidence/builds/b2-01-firered/build.log) |
| `b2-01-hns` | HnS / 011 | **PASS — EXECUTED: compilation only**, make `0`, wrapper `0` | [manifest]([LOCAL_WORKSPACE]/_local/artifacts/b2-01-hns/manifest.json), [build.log]([LOCAL_WORKSPACE]/_local/evidence/builds/b2-01-hns/build.log) |
| `b2-02-firered` | FireRed / 012 | **PASS — EXECUTED: compilation only**, make `0`, wrapper `0`; intermediate | [manifest]([LOCAL_WORKSPACE]/_local/artifacts/b2-02-firered/manifest.json), [build.log]([LOCAL_WORKSPACE]/_local/evidence/builds/b2-02-firered/build.log) |
| `b2-03-firered` | FireRed / 013 | **PASS — EXECUTED: compilation only**, make `0`, wrapper `0`; superseded | [manifest]([LOCAL_WORKSPACE]/_local/artifacts/b2-03-firered/manifest.json), [build.log]([LOCAL_WORKSPACE]/_local/evidence/builds/b2-03-firered/build.log) |
| `incremental-013` | FireRed / 012 tree updated to 013 | **PASS — EXECUTED: compilation only**, make `0`; clean artifacts identical | [build-result.json]([LOCAL_WORKSPACE]/_local/evidence/b2/incremental-013/build-result.json), [build.log]([LOCAL_WORKSPACE]/_local/evidence/b2/incremental-013/build.log), [clean-equivalence.json]([LOCAL_WORKSPACE]/_local/evidence/b2/incremental-013/clean-equivalence.json) |
| `b2-04-firered` | FireRed / 014 | **PASS — EXECUTED: compilation only**, make `0`, wrapper `0`; final clean | [manifest]([LOCAL_WORKSPACE]/_local/artifacts/b2-04-firered/manifest.json), [build.log]([LOCAL_WORKSPACE]/_local/evidence/builds/b2-04-firered/build.log) |
| `incremental-014` | FireRed / 013 tree updated to 014 | **PASS — EXECUTED: compilation only**, make `0`; clean artifacts identical | [result.json]([LOCAL_WORKSPACE]/_local/evidence/b2/incremental-014/result.json), [build.log]([LOCAL_WORKSPACE]/_local/evidence/b2/incremental-014/build.log), [clean-equivalence.json]([LOCAL_WORKSPACE]/_local/evidence/b2/incremental-014/clean-equivalence.json) |
| 013 and final 014 HnS | HnS / 013 or 014 | **NOT RUN** — no 013/014 HnS clean ROM build | Source-guard preservation and earlier executed checks are qualified below |
| B2 LeafGreen ROM | LeafGreen | **NOT RUN** — generation/preprocessing checks only | No LeafGreen ROM or gameplay qualification |

The 011 FireRed failure was `include/constants/map_event_ids.h:1135:9: error: macro names must be identifiers`: the added guide's numeric local ID generated `#define 4 4`. Candidate 012 uses `LOCALID_B2_PALLET_GUIDE`, retaining automatic object index 4. This corrects the identifier without removing gameplay. The failed source, patch, log and exit code remain preserved.

Candidate 013 adds only `FIRERED`-guarded bounds checks in three `src/nuzlocke.c` lookup callers relative to 012. The new map section has no allocated Nuzlocke encounter entry; the guards avoid indexing that missing entry and preserve valid existing entries. This allocates no persistent storage. The [caller audit]([LOCAL_WORKSPACE]/_local/evidence/b2/save-audit/appended-section-caller-audit.json) records the affected callers and remaining region-map assumptions.

Candidate 013's native travel test exposed absent New Bark and House1 NPCs: their HnS graphics IDs have NULL pointer-table entries in the FireRed target. Candidate 014 changes exactly two graphics fields in the FireRed-only map objects, selecting existing `OBJ_EVENT_GFX_FAT_MAN_FRLG` and `OBJ_EVENT_GFX_WOMAN_1_FRLG` instead. It imports no additional object graphics and retains the original HnS objects. The [014 fix record]([LOCAL_WORKSPACE]/_local/evidence/b2/travel-audit/014-npc-fix.json) preserves the source hashes and delta. The [013 native evidence directory]([LOCAL_WORKSPACE]/_local/evidence/native/b2-native-01/) remains retained; the blocker is an executed runtime finding, not a compilation failure or a passed travel test. A successful 014 build does not establish that the runtime repair passed.

The immutable 012 and 013 artifacts remain preserved. The live `[LOCAL_WORKSPACE]/_local/worktrees/b2-02-firered/` tree was updated and rebuilt to 013; the live `[LOCAL_WORKSPACE]/_local/worktrees/b2-03-firered/` tree was updated and rebuilt to 014. Their present outputs must not be described as their original clean candidate. The preserved 013 manifest SHA-256 is `4460f574aa6a2ff3957e629491b12ab4ea7fa8e13f506b79f8a2ba2473e30fcc`.

Retained log SHA-256 values:

| Log | SHA-256 |
|---|---|
| 011 FireRed | `a19cfe7267e7f0e5a034322ea5cb96f584a96a5dbe2c4699f33af6117fccf649` |
| 011 HnS | `a341b7d4583db474f95a1d3a0cba290cc09e7579130ffb1be75546b83749d65f` |
| 012 FireRed | `2dc5a0c7e049f1a2313459a2302111571a2031bf46bb7b5219f437414e804236` |
| 013 clean FireRed | `0b2abc98ec539352cbb745535e18964946f89eb4505f3210b04289ec28a5a43e` |
| 013 incremental FireRed | `a0f97a054dc8ff9f7e866614c142ea0eb3be27cc260294caaddcd174cb722961` |
| 014 clean FireRed | `9e7f77e9f69be61b4a9697cef417ec93c436a8dece9d70112f6952f920ac8bfe` |
| 014 incremental FireRed | `1a85ad211050b44e32fd298a2b75ca32dac2fbae6ccd10156d7c94248317f9b2` |

## Final 014 outputs and preserved 013 artifacts

| Exact local output | Bytes | SHA-256 |
|---|---:|---|
| [014 pokefirered.gba]([LOCAL_WORKSPACE]/_local/artifacts/b2-04-firered/pokefirered.gba) | 33,554,432 | `8980ba9dced4586dda2450ea102789a4ac8bf4da731f3a8c07db18a0a41ab9f2` |
| [014 pokefirered.elf]([LOCAL_WORKSPACE]/_local/artifacts/b2-04-firered/pokefirered.elf) | 41,176,612 | `f51161f8b3783248b03ad5d0271cb216140cb42a97105682cec8f5ea631917c0` |
| [014 pokefirered.map]([LOCAL_WORKSPACE]/_local/artifacts/b2-04-firered/pokefirered.map) | 4,977,627 | `4f535557ec5e9bc430900b896891d966b24d5a4b9d6acdf451c65d86f4b8f9e5` |
| [013 pokefirered.gba — superseded]([LOCAL_WORKSPACE]/_local/artifacts/b2-03-firered/pokefirered.gba) | 33,554,432 | `4989dadd96a19b3083d89722c25ed4ff48bd122edafe29221c76a84e0a921c9d` |
| [013 pokefirered.elf — superseded]([LOCAL_WORKSPACE]/_local/artifacts/b2-03-firered/pokefirered.elf) | 41,176,612 | `60657a133db2aa026f3c1f404599b2379ee6d3d02530526f041c9b45b7900000` |
| [013 pokefirered.map — superseded]([LOCAL_WORKSPACE]/_local/artifacts/b2-03-firered/pokefirered.map) | 4,977,627 | `4f535557ec5e9bc430900b896891d966b24d5a4b9d6acdf451c65d86f4b8f9e5` |

The final [014 clean/incremental comparison]([LOCAL_WORKSPACE]/_local/evidence/b2/incremental-014/clean-equivalence.json) reports `byte_equal: true` for all three files, with the 014 hashes above. It completes the earlier incremental record's pending-clean status. The earlier 013 equality evidence remains preserved. This demonstrates reproducibility for the recorded pairs of local builds with the pinned inputs and toolchain; it does not establish cross-platform reproducibility.

## Configuration, tools and reproduction

The executed host is macOS 27.0, Darwin 27.0.0, arm64, with Apple Clang 21.0.0 and Python 3.9.6. Builds use project-local GNU Make **4.4.1** and Arm GNU Toolchain **14.2.Rel1**, GCC **14.2.1**, binutils **2.43.1.20241119**. The [toolchain lock]([LOCAL_WORKSPACE]/toolchain.lock.json) preserves archive pins, local prerequisites and their original self-test limitations. No B2 global install or shell-profile change was made.

The actual ARM compiler SHA-256 is `07bfe9e74cfe028af639bf38703b2259c608aedee6ff991752084a10b82da614`. Private host dependencies are under `[LOCAL_WORKSPACE]/_local/tools/host/`; the ARM toolchain is under `[LOCAL_WORKSPACE]/_local/tools/arm-gnu-toolchain-14.2.rel1-darwin-arm64-arm-none-eabi/`.

Final effective configuration: `GAME_VERSION=FIRERED`, `MAP_VERSION=firered`, `MODERN=1`, `TEST=0`, `DEBUG=0`, `RELEASE=0`, `LTO=0`, `COMPARE=0`, `ANALYZE=0`, `O_LEVEL=2`, `TITLE=POKEMON FIRE`, `GAME_CODE=BPRE`. ARM compilation uses Thumb/ARM7TDMI/ARMv4T, `-mabi=apcs-gnu`, `-std=gnu17` and the recorded upstream warning configuration. No new warning suppression was added for B2. The [014 configuration log]([LOCAL_WORKSPACE]/_local/evidence/builds/b2-04-firered/configuration.log) SHA-256 is `cb29983579a4d9be540573675524e229a199d30e99e7c1e32d96bb751c1dd0c1`; the full flag strings and file pins are in the manifest. Recorded build environment uses `LANG=C`, `LC_ALL=C`, `TZ=UTC` and project-local dependency paths.

To reproduce into a **new** isolated run, choose an unused run ID. The wrapper rejects reuse, preserves stdout/stderr together, returns the real build exit and creates a fresh source tree with the pinned commit and complete patch:

```sh
source [LOCAL_WORKSPACE]/_local/tools/activate.sh
python3 [LOCAL_WORKSPACE]/scripts/build.py \
  --target firered --run-id b2-014-reproduce-01 --jobs 2 \
  --patch [LOCAL_WORKSPACE]/patches/0014-firered-b2-travel-slice.patch
```

The final clean build's recorded underlying command, run inside the final source path given above, was:

```sh
[LOCAL_WORKSPACE]/_local/tools/host/bin/make firered -j2 \
  TOOLCHAIN=[LOCAL_WORKSPACE]/_local/tools/arm-gnu-toolchain-14.2.rel1-darwin-arm64-arm-none-eabi
```

The reproduction example is an instruction, not an additional executed build. Reproducing the executed HnS regression requires `--target hns` and complete patch **011**; using 013 or 014 would be a new, currently unexecuted HnS build.

## Map selection and non-FireRed preservation

The executed [generation verification]([LOCAL_WORKSPACE]/_local/evidence/b2/map-audit/generation-verification/verification-v2.json) contains **23 host-tool commands, all exit 0, and 162 passed comparisons**. It is bound to candidate **012**. Candidate 013 changes only the exact FireRed Nuzlocke guards described above; candidate 014 then changes only the two selected FireRed NPC graphics fields. Applying the 012 group/layout/ID retention results to 014 is a source-delta inference, not a newly executed complete generator suite.

For the two changed map inputs, the executed [014 NPC generation verification]([LOCAL_WORKSPACE]/_local/evidence/b2/travel-audit/014-npc-generation/verification.json), SHA-256 `d1823f8acdebf566390d5610eaeacfb18adbfec0933a7d97d2aa7d2bc116eefb`, records **8 host-tool commands, all exit 0, and 14 passed comparisons**. It verifies the FireRed objects now select their existing FRLG graphics, while both maps' HnS/LeafGreen header, event and connection outputs remain byte-identical to 010. These are generated-data checks; final NPC appearance and interaction require native testing.

FireRed selection grows from **417 to 419 maps**, adding exactly `NewBarkTown_hns` (group 0/map 0) and `NewBarkTown_House1_hns` (group 1/map 2). Existing map/group/layout constants remain byte-identical. Only previously unselected layout slots **965 and 966** become selected; layout-table length and old IDs remain stable. The generator keeps Emerald per-map serialization and HnS version-2 layout encoding; actual `GAME_VERSION` is a separate explicit selection argument.

For the FireRed slice, New Bark has one guide, no route connections, one House1 warp and empty story callbacks. House1 has one harmless NPC and its exit returns to New Bark warp 0. Pallet's original objects/scripts are retained and its guide is appended. No Johto starter, story initializer, progression reset, reward or persistent regional field is introduced.

The same recorded suite compares HnS and LeafGreen generated groups, map/header/event/connection outputs, layouts/constants, map-local IDs and heal data with 010; unchanged results are recorded, with scratch-directory include paths normalized where required. Original non-FireRed map script branches were also reviewed as byte-exact. A separate [preprocessing comparison]([LOCAL_WORKSPACE]/_local/evidence/b2/map-audit/unaffected-target-preprocessing-v2.json) executed **10** comparisons over the five tileset/animation/door dependency files under existing HnS and LeafGreen defines, all exit 0 and byte-identical. The unsuccessful first attempt lacking generated headers is preserved separately. These are host generation/preprocessing checks, not LeafGreen gameplay tests.

Candidate 013's additional Nuzlocke guards are exact `#ifdef FIRERED` source guards; source review establishes that their other-target branches are retained. The final 014 graphics correction affects only the two FireRed slice objects and has the targeted generated-data evidence above. **No additional 013/014 HnS/LeafGreen C preprocessing comparison or ROM build was executed.**

The 011 HnS clean ROM differs from the 010 ROM in exactly **one byte at `0x42fa84`**: an ASSERT diagnostic string changes `src/region_map.c:2403` to `:2407` after four added FireRed-conditional source lines. The ELF differs and the link map is byte-identical. The [byte-difference evidence]([LOCAL_WORKSPACE]/_local/evidence/b2/hns-diagnostic-only-difference.json) supports a diagnostic-line difference; it does not establish native gameplay equivalence.

| Exact 011 HnS output | Bytes | SHA-256 |
|---|---:|---|
| [pokehns.gba]([LOCAL_WORKSPACE]/_local/artifacts/b2-01-hns/pokehns.gba) | 33,554,432 | `c9ee91bfd49b9ed3841124a56a38525bbabe79cb206fa2ff560ffe1d9a9ccc90` |
| [pokehns.elf]([LOCAL_WORKSPACE]/_local/artifacts/b2-01-hns/pokehns.elf) | 43,370,892 | `0fe2b8d6bb4276b49f643b17208ccd254c3f428bdd3b02de3c0daef09fd810b0` |
| [pokehns.map]([LOCAL_WORKSPACE]/_local/artifacts/b2-01-hns/pokehns.map) | 4,959,009 | `5a7fcf822ec78dfd8dd8fe4fffe29a5464c732902ba4c859a56216255198cf79` |

## Actual ARM layouts and engine budgets

The final [014 compiled ABI comparison]([LOCAL_WORKSPACE]/_local/evidence/b2/save-audit/compiled-b2-04/actual-b2-abi-comparison.json), SHA-256 `3be90ef9b82fa515d369056a66791e806e182053f5680d02184bf9c3b947031a`, uses the actual pinned ARM compiler and recorded target flags and is bound to the final **014** clean FireRed tree/manifest. Both ABI/field probes exited 0; all **249 ABI + 126 field measurements** match the 010 baseline. The preserved [013/011 comparison]([LOCAL_WORKSPACE]/_local/evidence/b2/save-audit/compiled-b2-03/actual-b2-abi-comparison.json), SHA-256 `8ee0950ba0ce983da13122699e24cd38019845a6c446e3963274680a10e8b03d`, binds HnS probes to its executed **011** tree/manifest, with **243 ABI + 124 field measurements**, both probe exits 0, all unchanged. These measurements include saved trainer/party/Pokédex/bag/location fields and affected offsets; no final 014 HnS build/probe is implied.

| ARM structure / invariant | FireRed 014 | HnS 011 | B2 change |
|---|---:|---:|---|
| SaveBlock1 size / capacity | 15,868 / 15,872 bytes | 15,760 / 15,872 bytes | None |
| SaveBlock2 size / sector capacity | 3,892 / 3,968 bytes | 3,892 / 3,968 bytes | None |
| SaveBlock3 structure size / reserved chunk capacity | 52 / 1,624 bytes | 52 / 1,624 bytes | None; integrity limitations remain open |
| Live roamer structure/count | 28 bytes / 1 | 28 bytes / 4 | None |
| Save version | 5 | 5 | None |
| Sector size / data bytes | 4,096 / 3,968 | 4,096 / 3,968 | None |
| Sectors per slot / total sectors | 14 / 32 | 14 / 32 | None |

For both audited targets, all **12 protected save/configuration/storage/flag/item/species/new-game source files** are byte-identical to 010, including `include/global.h`, `src/save.c`, `src/load_save.c` and `src/new_game.c`. Existing checksums, sector assignments and capacity assertion are retained. Travel uses the existing position/location/layout fields. No compatibility claim follows from matching layouts; retail, personal, earlier-experiment or later-candidate save migration has not been qualified.

| Static linked budget | FireRed 010 | FireRed 014 | Delta |
|---|---:|---:|---:|
| ROM used | 29,853,828 bytes | 29,939,076 bytes | **+85,248 bytes** |
| EWRAM used | 247,732 bytes | 247,732 bytes | **0** |
| IWRAM used | 25,944 bytes | 25,944 bytes | **0** |

FireRed linked-ROM headroom is **3,615,356 bytes** within the 32 MiB output. Static EWRAM/IWRAM headroom is 14,412/6,824 bytes. HnS 011 linked usage remains ROM 31,707,908, EWRAM 248,096 and IWRAM 25,704 bytes, all unchanged from 010. Runtime peak memory and transient allocation remain unmeasured; static headroom does not prove runtime capacity.

## Remaining limits and review boundary

The FireRed SaveBlock1 margin remains **four bytes**. Alignment or future field additions can exceed it; the existing capacity assertion remains active. The FireRed roamer fidelity defect and SaveBlock3 integrity limitations remain open. B2 neither repairs them nor creates a production save format.

`MAPSEC_NONE=219` is unchanged; FireRed appends `MAPSEC_NEW_BARK_TOWN=220`. No Johto Fly destination, heal location, world-map art, encounter allocation, badge set or independent regional progression is implemented. The appended-section caller audit records fallback/UI assumptions, including limits on future encounter metadata. The selected source graphics and original animation behavior are reused; no new art or placeholder was introduced. C's targeted dependency notice is [b2-c-dependency-notice.md]([LOCAL_WORKSPACE]/docs/b2-c-dependency-notice.md); the frozen 010 handoff remains preserved.

Build qualification is complete for final 014 FireRed within the stated limits. Native runtime acceptance and the owner-facing go/hold/no-go decision belong to the B2 test report and review gate. Candidate 013's executed NPC/travel blocker remains recorded rather than reclassified as a pass. There is no campaign-completeness, release, save-compatibility, browser-runtime or full Johto-integration claim in this build report. No later milestone, remote publication or Workstream A change is authorized by its compilation result.

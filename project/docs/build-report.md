# B0 build report

**Owner update — October 9, 2026:** Audio is **PASS — OWNER-REPORTED** for the current B0 evaluation. See the [owner audio confirmation](decisions/2026-10-09-b0-owner-audio.md) for attribution and scope. This later confirmation supersedes earlier audio-pending statements below; Codex did not perform a new listening test. The prior frozen audit and native reports remain historical evidence. B0 remains HOLD for review of the four-byte save margin and FireRed roamer fidelity defect.

Current experimental result: reviewed complete patch 010 **PASS — EXECUTED: separate clean compilation and clean repeats for FireRed and HnS**. ROM/ELF/map sizes and hashes, configurations, environment, source/generated diffs and actual map selections reproduce exactly within each target. HnS 010 outputs are byte identical 009, permitting association with the completed separate fresh 009 native test: early gameplay and both save/cold-reload cycles passed; audio remains NEEDS OWNER TEST. Full results are in `docs/hns-patched-native-results.md`. FireRed 010 completed its own fresh native test after 009 failed starter acquisition: FR-01–09 and both normal-save/cold-reload cycles passed; 600.9 measured active seconds passed the visual/input subcheck. Audio remains NEEDS OWNER TEST. Full repaired results are in `docs/firered-repaired-native-results.md`. Four-byte headroom and historical failures remain preserved.

Tester: Codex. Executed October 8, 2026, macOS 27.0 arm64; timestamps in manifests/logs are UTC (owner timezone America/New_York, UTC−04:00 on this date).

Source candidate: [pokehns-expansion](https://github.com/PokemonHnS-Development/pokehns-expansion/commit/167aa6d537b109bb229c231ddce4616974c4da71), full SHA `167aa6d537b109bb229c231ddce4616974c4da71`, observed tag `Release-v2.0.6`. Full Git history was retained with blob filtering. The reference clone stayed clean and was never repaired.

## Historical runs through patch 0003

The owner subsequently approved the bounded FireRed save-layout experiment. Current results are in `docs/firered-save-experiment.md`; the runs below preserve the earlier baseline and target-separation evidence. They do not describe the final experimental source state.

## Executed builds

| Run | Source state | Result | Real make exit | UTC wrapper start/end (includes preflight) |
|---|---|---|---|---|
| `baseline-01-firered` | unmodified source | FAIL — EXECUTED | 2 | `2026-10-08T19:59:24.949664+00:00` → `2026-10-08T19:59:36.951692+00:00` |
| `baseline-02-firered` | unmodified source | FAIL — EXECUTED | 2 | `2026-10-08T19:59:51.746953+00:00` → `2026-10-08T20:00:40.170122+00:00` |
| `repair-01-firered` | patched source | FAIL — EXECUTED | 2 | `2026-10-08T20:07:30.114004+00:00` → `2026-10-08T20:09:01.606580+00:00` |
| `repair-02-firered` | patched source, combined patch 0002 | FAIL — EXECUTED | 2 | `2026-10-08T22:03:53.541307+00:00` → `2026-10-08T22:05:15.436543+00:00` |
| `repair-03-firered` | patched source, combined patch 0003 | FAIL — EXECUTED | 2 | `2026-10-08T22:08:25.026949+00:00` → `2026-10-08T22:10:34.972578+00:00` |
| `baseline-01-hns` | unmodified source | PASS — EXECUTED: compilation only | 0 | `2026-10-08T20:02:00.487942+00:00` → `2026-10-08T20:07:13.743620+00:00` |
| `baseline-02-hns` | unmodified source | PASS — EXECUTED: compilation only | 0 | `2026-10-08T20:10:02.350767+00:00` → `2026-10-08T20:15:36.889825+00:00` |
| `repair-03-hns` | patched source, combined patch 0003 | PASS — EXECUTED: compilation only | 0 | `2026-10-08T22:18:40.433304+00:00` → `2026-10-08T22:24:16.113713+00:00` |

Each invocation created a fresh isolated target tree. Baseline commands were GNU Make 4.4.1 `<target> -j2 TOOLCHAIN=[LOCAL_WORKSPACE]/_local/tools/arm-gnu-toolchain-14.2.rel1-darwin-arm64-arm-none-eabi`. `scripts/build.py` records exact argv, sanitized environment, effective values and full logs. ARM GCC 14.2.1 / binutils 2.43.1, Apple clang 21, Python 3.9.6, pkgconf 2.5.1, libpng 1.6.59 and local zlib 1.3.2 are locked separately in `toolchain.lock.json`.

| Effective value | FireRed | HnS |
|---|---|---|
| Make selector | `firered` | `hns` |
| GAME_VERSION | `FIRERED` | `POKEMON_HNS` |
| MAP_VERSION / BUILD_NAME | `firered` | `hns` |
| CPP game define | `-DFIRERED` | `-DPOKEMON_HNS` |
| AS game define | `--defsym FIRERED=1` | `--defsym POKEMON_HNS=1` |
| Expected output | `pokefirered.gba/.elf/.map` | `pokehns.gba/.elf/.map` |
| TEST / DEBUG / RELEASE / LTO | `0 / 0 / 0 / 0` | `0 / 0 / 0 / 0` |

Both use MODERN=1, Thumb ARMv4T/ARM7TDMI, GNU C17, upstream optimization `-O2` and upstream warning policy. Configuration-file inventory SHA-256 is `f0e57724c34228154aa68dd82e12c36e4ea8a5f6d000046ca1883fd6ed622d06`; exact flags and file hashes are in each manifest. A matching configuration inventory does not equate the selected game defines. No debug grants or source content was removed to compile.

## Failures and the isolated limited repair

1. `baseline-01-firered`: host `gbagfx` linker could not find `-lpng`. Local pkgconf suppressed its prefix's library search flag. The wrapper environment was corrected with `PKG_CONFIG_ALLOW_SYSTEM_LIBS=1` and `PKG_CONFIG_ALLOW_SYSTEM_CFLAGS=1`; this changes local dependency discovery only. The original failing log is preserved.
2. `baseline-02-firered`: corrected host tools built, then pristine game compilation failed at `src/braille_puzzles.c:379`, `FLAG_RECEIVED_TOGEPI_EGG` undeclared. That flag exists only in `flags_hns.h`; the FireRed header deliberately selects different flags.
3. `repair-01-firered`: applied only `patches/0001-hns-togepi-target-guard.patch`, SHA-256 `e15e8f17b397947d504289b0c48d643a4b8cb045974f0f3cb4709db09aba3c1b`, on uncommitted local branch `b0/firered-repair-01`. It limits the egg-received condition to HnS and retains the real three-species predicate and special registration. The historical pre-gate implementation was inspected at parent of `61669584c088fbc983eacae5990420812a32a4bc`; HnS behavior remains equivalent by source review, not a runtime test. The exact applied diff and combined patch/config fingerprint are preserved in its manifest/evidence.
4. That repair advanced compilation to `src/mom_savings.c`, then failed on multiple uses of absent `SaveBlock1.momSavings` and HnS-only `FLAG_MOM_HAS_GIFT`. `include/global.h:1319–1321` deliberately includes the savings field only for HnS. The initial review gate stopped here without a second patch. The owner subsequently authorized bounded target separation; see `docs/decisions/2026-10-08-b0-firered-repair.md` and `docs/firered-repair-report.md`.
5. `repair-02-firered`: applied combined patch 0002 in a fresh tree. It includes patch 0001 and consistently guards the HnS Mom implementation, header, nine specials and script include; the four shared C callers were already HnS-only. Full make and wrapper both exited 2. The previous Mom compilation failure was passed, then `src/overworld.c:1792–1793` failed on HnS-only `FLAG_NIGHT_POKEMON` / `FLAG_DAY_POKEMON`. The existing runtime `if (IS_HNS)` does not prevent C parsing of absent symbols.
6. `repair-03-firered`: applied combined patch 0003 alone in another fresh tree. It includes patch 0002 and adds only a preprocessor guard around the existing HnS overworld-mon day/night flag block. Shared RTC, time classification, palette blending and encounter logic remain intact. Full make and wrapper both exited 2. Compilation passed that overworld failure and stopped at `src/save.c:96`, where `SaveBlock1FreeSpace` has a negative array size because the native save block exceeds its allocated sectors. The same compilation also reported five absent HnS migration flags at lines 938–976: `FLAG_ENABLE_CONDITION`, `FLAG_ITEM_ICEPATH4_TM_AVALANCHE`, `FLAG_ITEM_VICTORYROAD1_TM_EARTHQUAKE`, `FLAG_HIDE_VERMILION_CITY_SAMSON` and `FLAG_HIDE_ROUTE28_SCIENTIST`.

Neither historical target-separation patch changes native save structures, sector allocation, campaign maps/assets or game configuration. No fake flag, placeholder return, gameplay removal or added warning suppression was used. Patches 0002 and 0003 are each complete against pristine source; apply only the selected combined patch, without stacking earlier patches.

| Executed repair | Applied patch SHA-256 | Patch/config fingerprint |
|---|---|---|
| `repair-02-firered` / `0002-firered-target-separation.patch` | `05f82fb48f8619366e206df9cc167304f17608a07b70997fe37b103ef1dbb6d8` | `e9287cc5e30dd41efddcf9cf8a7dccb4816dd212977f62d15d30575ba0e33ea9` |
| `repair-03-firered` / `0003-firered-target-separation.patch` | `80f8c6d00dec00c715bd346e41c8e27e5e3f25168869b970324828d6f56fdf99` | `ec329f2729070b7de146ade4bcc5ffac4ce6059e6a40ff34b0c4f600a0db6238` |
| `repair-03-hns` / `0003-firered-target-separation.patch` | `80f8c6d00dec00c715bd346e41c8e27e5e3f25168869b970324828d6f56fdf99` | `ec329f2729070b7de146ade4bcc5ffac4ce6059e6a40ff34b0c4f600a0db6238` |

The full patched HnS build, `repair-03-hns`, completed in its own fresh tree with make/wrapper exits 0 and real ROM/ELF/map outputs. It used combined patch 0003 and the same patch/config fingerprint as `repair-03-firered`, while selecting `POKEMON_HNS` and map version `hns`. This is compilation acceptance only. For patch 0003, HnS opening/gameplay/native saves were **NOT RUN** at that gate; previous GUI passes remain tied to the pristine baseline ROM hash.

Source inspection also identifies the unguarded `FLAG_DEFEATED_RED` No-EVs predicates in battle gains and EV medicine. These are possible later blockers, **not executed compiler failures** in the preserved attempts. They were not patched. In particular, the repair-03 log has dependency scans but no compiler invocation for `pokemon.c` or `party_menu.c`; their absent errors do not establish that the predicates are inactive.

There is **no FireRed ROM, ELF or linker map** from these attempts. Empty artifact directories contain manifests only; expected filenames must not be mistaken for produced outputs. Pristine and repaired failures remain separate.

## Executed native save-capacity diagnostic

An isolated compiler probe measured the existing structures with locked ARM GCC 14.2.1, ARMv4T Thumb and the build's `-mabi=apcs-gnu`. Both diagnostic compiler invocations exited 0. This measures ABI sizes/offsets; it is not a game build or native save/reload test.

| Target | `sizeof(SaveBlock1)` | Allocated capacity | Result |
|---|---:|---:|---|
| FireRed | 15,952 bytes | 15,872 bytes | Exceeds capacity by **80 bytes** |
| HnS | 15,760 bytes | 15,872 bytes | 112 bytes headroom |

The native allocation is four sectors of 3,968 data bytes each (`save.h`, sectors 1–4). Both targets share a 15,752-byte prefix. FireRed appends the Trainer Tower challenge ID (4 bytes), four tower records (48), rival name (8) and Route 5 daycare Pokémon (140), totaling 200 bytes. HnS appends Mom savings (8 bytes). Existing roamer padding makes both targets' roamer reservation total 196 bytes, so differing active roamer counts do not explain the target size difference.

SHA-256 comparisons confirmed `include/global.h`, `include/save.h`, `include/config/save.h` and `src/save.c` are unchanged from pristine source. The failed assertion was preserved. Probe source, exact argv, assembly, offsets, stdout/stderr and analysis are private at `[LOCAL_WORKSPACE]/_local/evidence/save-abi-repair-03/` (`save-abi-results.json`, `save-capacity-analysis.json`).

**Historical patch-003 recommendation: HOLD.** At that gate no allocation, padding, save version or migration change had been attempted. The owner has since approved the bounded experiment recorded in `docs/decisions/2026-10-08-b0-save-layout-exception.md`; B1 remains unauthorized.

## Actual preserved outputs

| Run / file | Bytes | SHA-256 |
|---|---:|---|
| `baseline-01-hns` / pokehns.gba | 33,554,432 | `7ffd0c7572f0542f60381ec776d99f4e826ae2859d56403e56bcc82effcd88df` |
| `baseline-01-hns` / pokehns.elf | 43,370,892 | `2d8cfca1ec8ca0a054e171bf976641a3f79523b245213f9103063ec1a510e262` |
| `baseline-01-hns` / pokehns.map | 4,958,962 | `4c0476f32dc4c512f04266aa59ce0d460c7df08b9beff6631bcb672b5894a082` |
| `repair-03-hns` / pokehns.gba | 33,554,432 | `e8e75adb31cfb02119b4b3e390e089f701ebd72cf852b3dea1f0f47283721f32` |
| `repair-03-hns` / pokehns.elf | 43,370,892 | `b40934383653d2aad2bf7ebd9c3f1e818db2c6401768e3d1895ca98b9f8affa5` |
| `repair-03-hns` / pokehns.map | 4,959,009 | `5a7fcf822ec78dfd8dd8fe4fffe29a5464c732902ba4c859a56216255198cf79` |

Absolute artifact directory: `[LOCAL_WORKSPACE]/_local/artifacts/baseline-01-hns/`. The produced ROM is `pokehns.gba`; ELF and map are preserved beside it. `.sym` was not produced by the default target. HnS output header inspected as `POKEMON HNS` / `BPEE`; generated `.map_version` is `hns`. Native opening testing remains distinct from this header observation.

Patched HnS outputs and manifest are preserved separately:

- `[LOCAL_WORKSPACE]/_local/artifacts/repair-03-hns/pokehns.gba`
- `[LOCAL_WORKSPACE]/_local/artifacts/repair-03-hns/pokehns.elf`
- `[LOCAL_WORKSPACE]/_local/artifacts/repair-03-hns/pokehns.map`
- `[LOCAL_WORKSPACE]/_local/artifacts/repair-03-hns/manifest.json`

## Measured pristine HnS capacity

| Linker region | Used bytes | Region bytes | Nominal remainder |
|---|---:|---:|---:|
| EWRAM | 248,096 | 262,144 | 14,048 |
| IWRAM | 25,704 | 32,768 | 7,064 |
| ROM | 31,707,908 | 33,554,432 | 1,846,524 |

The ROM file is padded to 33,554,432 bytes. Linker allocation is 94.64% EWRAM, 78.44% IWRAM and 94.50% ROM; it is not measured runtime peak usage or evidence that Kanto/Sevii/Johto additions or 25 player rendering fit. FireRed linker capacity cannot be measured without a linked artifact; the native save-structure diagnostic is reported separately above. No combined-region, browser or multiplayer test was executed.

## Clean rebuild and evidence identity

The second pristine HnS build, `baseline-02-hns`, completed with real make exit 0 in another fresh detached tree. ROM, ELF and map are byte-identical by SHA-256 to `baseline-01-hns`; no nondeterminism was observed in these two runs. Both used the same locked configuration/toolchain. The comparison is preserved in `_local/evidence/hns-clean-rebuild-comparison.json`. FireRed has no successful artifact for a clean rebuild hash comparison; that acceptance item remains BLOCKED. Re-running a failed compile is not ROM reproducibility.

None of `repair-03-hns`'s ROM, ELF or map hashes matches either pristine HnS build. The pristine repeat-build PASS is retained; the patched build is a separate source state. Executed binary/object comparison found only `src/braille_puzzles.o` differs among 1,520 objects. `CheckTogepi` shrank from 84 to 80 bytes at the same start address; 9,958 subsequent sized ROM code symbols move four bytes earlier, explaining widespread code/pointer relocation differences. Mom, overworld and event-script objects are identical. Actual `FlagGet` source/disassembly returns only 0/1, supporting source/control-flow equivalence of the rewritten flag gate, not ROM byte identity or a runtime pass. Full byte intervals, object/symbol inventories, exact commands and disassembly are in `_local/evidence/repair-analysis/hns-repair03-byte-comparison/`. At the patch-0003 gate, no patched HnS repeat-build or native-save test had been executed.

For every run above (including the new FireRed and HnS repairs), exact absolute directories are:

- Worktree: `[LOCAL_WORKSPACE]/_local/worktrees/<run>/`.
- Manifest: `[LOCAL_WORKSPACE]/_local/artifacts/<run>/manifest.json`.
- Raw evidence: `[LOCAL_WORKSPACE]/_local/evidence/builds/<run>/` (`preflight.log`, `configuration.log`, `build.log`, `generated-tracked.diff`; repair also has `applied-repair.patch`, `patch-source-files.diff`).

Each manifest hashes its full combined build log and preserved outputs, records true process exit codes and UTC start/end, and retains before/after source state. Pristine runs have no tracked source changes after generation (the preserved tracked diffs are empty). Source inspection shows the generator rewrites heal-location JSON, but these executed baselines did not produce a tracked content difference. Repair diff includes only the reviewed patch at the tested source stage; generated final differences remain private.

Native tests and their limitations are in `docs/test-results.md`. Tools' self-test caveats are in `docs/environment.md`, `docs/toolchain-setup.md` and the lock; build success does not turn those checks or gameplay into passes. Publication rights remain unresolved; no game binaries or private evidence are staged/committed.

The second pristine successful artifact set is at `[LOCAL_WORKSPACE]/_local/artifacts/baseline-02-hns/`, with the same filenames/sizes/hashes as the first pristine build. Exact patch/config fingerprint for failed `repair-01-firered`: `1b634e225666a70bcf2a43dbc4419131c81161739b07c629931f18b0e29a6c44`.

## Approved save-layout experiment: actual clean builds

The owner authorization is in `docs/decisions/2026-10-08-b0-save-layout-exception.md`. All patches are complete against pristine and applied alone. Configuration inventory remains `f0e57724c34228154aa68dd82e12c36e4ea8a5f6d000046ca1883fd6ed622d06`; exact target values, stdout/stderr, real exits, complete patch/config fingerprints and generated diffs are in each run's manifest/evidence. Two jobs, unchanged pinned tools. Patches 0007/0008 were statically reviewed; no separate full 0007 build was executed.

| Run | Real make / wrapper exit | Actual make UTC start → end | Result |
|---|---|---|---|
| `repair-04-firered` | 2 / 2 | `2026-10-08T22:42:47.463378+00:00` → `2026-10-08T22:45:01.951100+00:00` | FAIL — EXECUTED |
| `repair-05-firered` | 2 / 2 | `2026-10-08T22:49:13.630414+00:00` → `2026-10-08T22:51:11.969465+00:00` | FAIL — EXECUTED |
| `repair-06-firered` | 2 / 2 | `2026-10-08T22:53:49.901246+00:00` → `2026-10-08T22:55:53.934849+00:00` | FAIL — EXECUTED |
| `repair-08-firered` | 2 / 2 | `2026-10-08T23:02:41.699658+00:00` → `2026-10-08T23:08:20.971116+00:00` | FAIL — EXECUTED |
| `repair-08-hns` | 0 / 0 | `2026-10-08T23:09:09.693060+00:00` → `2026-10-08T23:15:04.822469+00:00` | PASS — EXECUTED: compilation only |

Repairs 004/005/006 passed the preceding save/starter/shop boundary, then failed at the next compiler boundary. Repair 008 passed all those C errors and linked far enough to report 17 unresolved references (14 symbols). Individual reviews, the initial shared-TM stop and the subsequent compiled-caller correction are in `docs/firered-save-experiment.md`. At that intermediate stage candidate 009 was under source review and had no build result; subsequent executed 009 builds are recorded below. The separate incremental 006 keep-going diagnostic is explicitly not a clean-build acceptance run.

Historical 008 complete patch: `patches/0008-regional-map-target-boundaries.patch`, 11,356 bytes, SHA-256 `bcab26a7ccf880e37e7aae12ce12b719ed6c5df05c1dcd1739a8c98aebe6e562`; patch/config fingerprint `91e1544f19938fceae5288b7907fe332e9ea6b6614c9464108bfad2377b3af54`.

| Actual output | Bytes | SHA-256 | Qualification |
|---|---:|---|---|
| `repair-08-firered/pokefirered.map` | 4,977,612 | `b3ab6576554c5762b36afdfde8e8af1684162416bab729737e03edbf2449d4de` | Failed-link diagnostic only; no ROM/ELF |
| `repair-08-hns/pokehns.gba` | 33,554,432 | `c446291194e601bf0b5650afec899cb151458a51c5d44a9915df78fa8a1e7687` | Successful compilation output; native result separate |
| `repair-08-hns/pokehns.elf` | 43,370,892 | `ab6b79c0245d7343d759c673b5f172a5e08b4fb535f2bc8970e1ae3652847ff0` | Successful compilation output; native result separate |
| `repair-08-hns/pokehns.map` | 4,959,009 | `5a7fcf822ec78dfd8dd8fe4fffe29a5464c732902ba4c859a56216255198cf79` | Successful compilation output; native result separate |

Exact historical 008 output directories: `[LOCAL_WORKSPACE]/_local/artifacts/repair-08-firered/` and `[LOCAL_WORKSPACE]/_local/artifacts/repair-08-hns/`. Complete logs/configuration/applied diffs are at the corresponding directories beneath `_local/evidence/builds/`. The FireRed diagnostic map is not a successful linked game.

HnS's successful linker allocations remain EWRAM 248,096/262,144, IWRAM 25,704/32,768 and ROM 31,707,908/33,554,432 bytes. ROM is padded to 32 MiB. FireRed's failed linker printed 247,732 EWRAM, 25,944 IWRAM and 29,855,236 ROM bytes; these are failed-link diagnostics, not a qualified final image or runtime peak/capacity proof.

Actual ARM save sizes/offsets and protection checks are in `docs/firered-save-experiment.md`: FireRed 15,868 with four bytes free; LeafGreen unchanged 15,952; HnS unchanged 15,760; Emerald unchanged 15,752. Live fields retained, sector/checksum/capacity protection unchanged. No save compatibility or production format is claimed.

The separate fresh patched HnS `repair-08-repeat-hns` clean build **PASS — EXECUTED**, make/wrapper 0. Actual make UTC start/end: `2026-10-08T23:16:21.056297+00:00` / `2026-10-08T23:22:17.003667+00:00`. Independently rehashed ROM, ELF and map match the first 008 sizes/hashes exactly; source/configuration/patch fingerprints also match. Exact command/log/exit/hash comparison: `_local/evidence/repair-analysis/repair08-hns-clean-repeat/comparison.json` and `comparison.md`. Repeat artifacts/manifest: `[LOCAL_WORKSPACE]/_local/artifacts/repair-08-repeat-hns/`. No further build jobs remain.

At 008, fresh patched HnS native regression was underway on that exact ROM and FireRed repeat/native acceptance was BLOCKED. Later 009 successful outputs and their separate qualification are recorded below. Pristine repeat acceptance and patched repeat acceptance are separate; no cross-build save compatibility is claimed.

## Reviewed 009: successful separate clean targets

The actual compiled-caller review narrowed the initial shared-TM stop. The FireRed-only unused Mauville TM-prize block has no selected map or compiled object caller; other targets retain that block unchanged. Complete 009 adds that target boundary and individually reviewed HnS linker guards, preserving all previous save/configuration/shared logic. No new flag, stub, gameplay policy, capacity change or production-format claim. See the experimental report and independent 009 source review.

Complete patch `patches/0009-hns-linker-target-boundaries.patch`, 19,906 bytes, SHA-256 `bea352da2bf5aa726084e4b418933c82287101abd1621af7b58e49e8d6de6c82`; patch/config fingerprint `656b49ab221989a12362bb1bbc9e24303e833274e33c7bde2ec9822056a97b44`. Source/tool/configuration pins unchanged. Apply 009 alone against pristine.

| Run | Real make / wrapper | Actual make UTC start → end | Qualification |
|---|---|---|---|
| `repair-09-firered` | 0 / 0 | `2026-10-08T23:58:53.594432+00:00` → `2026-10-09T00:06:06.606341+00:00` | PASS — EXECUTED: compilation only |
| `repair-09-hns` | 0 / 0 | `2026-10-08T23:59:47.911295+00:00` → `2026-10-09T00:07:11.405115+00:00` | PASS — EXECUTED: compilation only |

| Actual successful output | Bytes | SHA-256 |
|---|---:|---|
| `repair-09-firered/pokefirered.gba` | 33,554,432 | `74f90c6d019442adfb72d251720f749713e264b44066b6363de14c77b2ddaa40` |
| `repair-09-firered/pokefirered.elf` | 41,086,876 | `1678c552923f5db66620807654dea4c84495b602cca42b05b3cf595475bc63e8` |
| `repair-09-firered/pokefirered.map` | 4,974,564 | `5d4bbe4d505caf89015c2577144852e139898130f85ba96fb0e74877f573bc4c` |
| `repair-09-hns/pokehns.gba` | 33,554,432 | `4bb58fe3c06bc0b60146aa946cbc34f087efa607f525f68e0a1e99c0db9cde75` |
| `repair-09-hns/pokehns.elf` | 43,370,892 | `874096c8eee38c4f0f1d242e8e840c324ca34a5ac7623a04848568b11fcf4a0b` |
| `repair-09-hns/pokehns.map` | 4,959,009 | `5a7fcf822ec78dfd8dd8fe4fffe29a5464c732902ba4c859a56216255198cf79` |

Exact successful artifacts/manifests are beneath `[LOCAL_WORKSPACE]/_local/artifacts/repair-09-firered/` and `repair-09-hns/`; full logs/configuration/applied/generated diffs are beneath the matching `_local/evidence/builds/` directories. The actual FireRed ROM header is `POKEMON FIRE` / `BPRE`; HnS is `POKEMON HNS` / `BPEE`. Header identity is separate from native opening acceptance.

| Final 009 linker region | FireRed used / capacity | HnS used / capacity |
|---|---:|---:|
| EWRAM | 247,732 / 262,144 | 248,096 / 262,144 |
| IWRAM | 25,944 / 32,768 | 25,704 / 32,768 |
| ROM | 29,853,828 / 33,554,432 | 31,707,908 / 33,554,432 |

These are successful static linker allocations, not runtime peaks or combined-region capacity. Both ROMs are padded to 32 MiB. HnS 009 differs from 008 by exactly 10 ROM bytes (allocation diagnostic line strings); ELF differs, map is identical. All actual configuration/tool/environment identities match. Private comparison: `_local/evidence/repair-analysis/repair09-hns-build-comparison/comparison.json`. Exact 008 native evidence does not qualify 009.

The separate final 009 clean repeats subsequently passed as recorded below. At that preserved 009 checkpoint, fresh native testing was starting. FireRed 009 subsequently failed starter acquisition and made no normal save; the HnS 009 regression is separately continuing on the byte-identical 010 ROM. Historical unmodified/003/008 results and failed baselines remain preserved separately.

## Preserved 009 reproducible clean repeats — executed

Both fresh repeat builds passed make/wrapper 0 in distinct clean target trees. Independently rehashed ROM/ELF/map sizes and hashes equal their first 009 artifacts exactly; source/patch/config/tool/environment/command identities and source/generated diffs also match.

| Repeat run | Actual make UTC start → end | Result |
|---|---|---|
| `repair-09-repeat-firered` | `2026-10-09T00:08:27.287919+00:00` → `2026-10-09T00:15:35.576018+00:00` | PASS — EXECUTED: clean repeat |
| `repair-09-repeat-hns` | `2026-10-09T00:09:27.440957+00:00` → `2026-10-09T00:16:56.654160+00:00` | PASS — EXECUTED: clean repeat |

Repeat artifacts/manifests are under `[LOCAL_WORKSPACE]/_local/artifacts/repair-09-repeat-firered/` and `repair-09-repeat-hns/`; complete logs at their matching build-evidence paths. Both independent comparisons and launcher/real exit evidence: `_local/evidence/repair-analysis/repair09-hns-clean-repeat/{firered-comparison.json,hns-comparison.json,both-target-summary.json}`. Historical 008 comparisons remain unchanged. No further builds are running or planned absent a new failure/change. Native exact-ROM qualification continues separately.

## Reviewed 010: FireRed missing-default correction

Complete `patches/0010-firered-fresh-monotype-default.patch`, 21,515 bytes, SHA-256 `3e9b6b003557cbfacff59706ad04e4f7f2fdd58bc6162be995f91dc09742d5f3`, applies alone against the pristine pin. Fingerprint `32faeccdf41db77505858cd2981a070c7f835f0eee3180fe1563cb4c0e343f00`. It retains 009 and assigns existing monotype-OFF 31 only in the existing FireRed fresh-default initializer; the source/scope reviews are in the experiment report. There is no new layout/capacity/policy/interface/flag or starter bypass.

First `repair-10-firered` **PASS — EXECUTED: compilation only**, make/wrapper 0, UTC `2026-10-09T00:35:24.361885+00:00` to `2026-10-09T00:43:55.104872+00:00`. Actual header `POKEMON FIRE`/`BPRE`; each generated map aggregate independently selects 417 FRLG maps and zero HnS maps. Manifest SHA-256 `fbf75c3a47c21c88ad6633b0f6a176b131b797897ff8bdd19f4161966f0f671e`. Private independent validation: `_local/evidence/repair-analysis/repair10-build-comparison/firered-first-validation.json`.

| First 010 FireRed artifact | Bytes | SHA-256 |
|---|---:|---|
| `[LOCAL_WORKSPACE]/_local/artifacts/repair-10-firered/pokefirered.gba` | 33,554,432 | `3e504731d9dd3c02ec273dc257c86f557caaf8c9b933d2f0ff73558c2e121a39` |
| `[LOCAL_WORKSPACE]/_local/artifacts/repair-10-firered/pokefirered.elf` | 41,086,876 | `f0409c5e872ad265d26f1a38660c8ecee6763e85ef2728a5ec7bd2951d483853` |
| `[LOCAL_WORKSPACE]/_local/artifacts/repair-10-firered/pokefirered.map` | 4,974,564 | `5d4bbe4d505caf89015c2577144852e139898130f85ba96fb0e74877f573bc4c` |

Successful linker allocation remains EWRAM 247,732/262,144, IWRAM 25,944/32,768 and ROM 29,853,828/33,554,432. These are static allocations, not runtime/combined-region capacity. Full make stdout/stderr/commands/real exits are preserved in the matching 010 build evidence. First HnS 010 and clean repeats were still running at this checkpoint; no completed result is inferred. Fresh FireRed 010 normal saves have not been executed.

First `repair-10-hns` **PASS — EXECUTED: compilation only**, make/wrapper 0, UTC `2026-10-09T00:35:44.543660+00:00` to `2026-10-09T00:44:17.656131+00:00`. Manifest SHA-256 `21ea87bf5c2343bf6a8e14815cea30a3ecb1500ac345d2ea1281045b88054edc`. Actual selector/header and 560 HnS maps independently verified. Actual 009→010 comparison found zero differing ROM bytes; ELF/map hashes and sizes also match. Exact evidence `_local/evidence/repair-analysis/repair10-build-comparison/hns009-to010.json`, SHA-256 `3e8d529c6cd43e62ad89b70a947fde83159bdc122050b53f50cb5f010354c61d`. This links the exact-ROM native evidence without claiming a second GUI run or importing any save.

| First 010 HnS artifact | Bytes | SHA-256 |
|---|---:|---|
| `[LOCAL_WORKSPACE]/_local/artifacts/repair-10-hns/pokehns.gba` | 33,554,432 | `4bb58fe3c06bc0b60146aa946cbc34f087efa607f525f68e0a1e99c0db9cde75` |
| `[LOCAL_WORKSPACE]/_local/artifacts/repair-10-hns/pokehns.elf` | 43,370,892 | `874096c8eee38c4f0f1d242e8e840c324ca34a5ac7623a04848568b11fcf4a0b` |
| `[LOCAL_WORKSPACE]/_local/artifacts/repair-10-hns/pokehns.map` | 4,959,009 | `5a7fcf822ec78dfd8dd8fe4fffe29a5464c732902ba4c859a56216255198cf79` |

At that first-build checkpoint, both 010 clean repeats were running in new independent trees; their completed results are below. Native qualification remains underway; no complete 010 FireRed/HnS gameplay/save pass is claimed.

### Executed 010 clean repeats — complete

All four 010 first/repeat make/wrapper exits are 0; build jobs are idle. Both per-target ROM/ELF/map hashes and sizes reproduce exactly. Effective configurations, sanitized environments, patch/config fingerprints, source/generated diffs, generated map inventories and locked installed-tool hashes match. Each repeat used a distinct fresh tree at the pin.

| Repeat | Actual make start UTC | Actual make end UTC | Make/wrapper |
|---|---|---|---|
| `repair-10-repeat-firered` | `2026-10-09T00:44:51.939533+00:00` | `2026-10-09T00:53:00.699681+00:00` | 0/0 |
| `repair-10-repeat-hns` | `2026-10-09T00:45:28.683371+00:00` | `2026-10-09T00:53:43.076957+00:00` | 0/0 |

Independent evidence `_local/evidence/repair-analysis/repair10-build-comparison/`: FireRed repeat comparison SHA-256 `3f8975282267dcf782ef895ee03e6b083017302d56c380dc71e671af4ab83992`; HnS `1c281aa061109ce55cce8558df897acbb8ea508cc8071fa476168c74971a9362`; both-target summary `6eda33d541f51307a5cd8130b87a1f74d12bb6e3178606c3cdc323d8b81a232c`. Repeat manifests: FireRed `e79bd86ba1c27fe3709c15037a976abff9017ebeb133c9ff35a540e86f4d4986`, HnS `8d93aff3f03e1968501abbeaf56f5779a910e1d822bb1a211438b3319c75f140`.

A private comparison-reader variable shadow omitted launcher attachment in the original repeat JSONs. Those original records remain unchanged; `launcher-verification.json` independently verifies all four full wrapper logs/hashes, true launcher exits and common activation/patch/environment metadata. No build was rerun to conceal the diagnostic-record issue. Main/preflight/configuration log verification and artifact comparisons already passed.

Compilation/reproducibility passes do not pass native gameplay or either normal-save/cold-reload cycle. No broader source repair or build follows without a relevant new failure; remaining work is native acceptance and the final boundary audit.

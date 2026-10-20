# Save foundation — conversion and host qualification

**October 10, 2026: EXECUTED PASS for the bounded offline conversion and host tests below.** Native opening, starter, gameplay, normal save/cold-reload and real PC interaction are **NOT RUN in this report at writing**; their acceptance status belongs in the separate clean-build/native review report. Host checks do not substitute for those tests.

The owner-approved scope is FireRed native version 6 / FRJS schema 1, content 1, layout 1, against upstream commit `167aa6d537b109bb229c231ddce4616974c4da71` and accepted B2/014. The [format registry](save-format-registry.md) and [implementation contract](save-foundation-implementation.md) describe the format and runtime policy. No Johto progression, general save import, Workstream A change or remote publication is included.

## Exact three-file conversion

Input directory: `[LOCAL_WORKSPACE]/_local/saves/firered/b2-native-01/`.

Output directory: `[LOCAL_WORKSPACE]/_local/saves/firered/save-foundation-converted-01/`.

Every file below is **131,088 bytes**: 128 KiB native flash plus its unchanged opaque 16-byte trailer. All originals and converted outputs are mode **0444**. These are the complete input allowlist; arbitrary development, personal, retail, HnS, Emerald and LeafGreen saves are excluded.

| Fixture/file | SHA-256 |
|---|---|
| Input [kanto-before-travel.sav](../_local/saves/firered/b2-native-01/kanto-before-travel.sav) | `6fac3f465bfc8fea83dfee6a5fdd73002c879286d35069ac4c4e5de547a6c074` |
| Output [kanto-before-travel-frjs1.sav](../_local/saves/firered/save-foundation-converted-01/kanto-before-travel-frjs1.sav) | `0829e6fbd5dfe393d0bdade062af4c9ced69c45fda76100ee9f3cb324d450dbc` |
| Input [johto-cycle-01.sav](../_local/saves/firered/b2-native-01/johto-cycle-01.sav) | `ba7aefef473f237f7eff6d220920348c16c09861b1b1fe74faa0e9d2f43edccd` |
| Output [johto-cycle-01-frjs1.sav](../_local/saves/firered/save-foundation-converted-01/johto-cycle-01-frjs1.sav) | `c129f8e6feeb4aabe8e28d283b72fec19534972d0dfd732a335d4fcab1814385` |
| Input [kanto-cycle-02.sav](../_local/saves/firered/b2-native-01/kanto-cycle-02.sav) | `7ba5fda5ca885fdc87f208a8dd0b48a60fcbc4471640003dbfb06c83cf4dd10e` |
| Output [kanto-cycle-02-frjs1.sav](../_local/saves/firered/save-foundation-converted-01/kanto-cycle-02-frjs1.sav) | `0d41eacb54e6046f9c7f8b5164f91d9dedd95ff9cfaefd6ca486ada7b9e5ae60` |

The converter validates the latest complete legacy bank, changes SaveBlock1's native-version scalar 5→6 and affected native checksum, then appends the blank protected extension. Every other used SaveBlock1 byte, all SaveBlock2/PC bytes, the complete 52-byte original prefix, special sectors 28–31 and opaque trailer remain identical. It retains the selected counter, rotation and parity bank: **1/1/bank 1**, **2/2/bank 0**, **3/3/bank 1**, respectively. The alternate bank is erased in each new copy. Johto containers and stored reserve are zero and uninitialized.

Original hashes/modes were verified before and after conversion and again after final host qualification. Existing identical converted outputs are retained; different outputs are rejected. Format 6 and unapproved hashes cannot be conversion inputs. The approved originals have empty PC storage, so these conversions do **not** qualify occupied-PC legacy migration.

Evidence: [conversion manifest](../_local/evidence/save-foundation-01/conversion-manifest.json), [commands and exit codes](../_local/evidence/save-foundation-01/converter-command-record.json), [41-check report](../_local/evidence/save-foundation-01/converter-qualification.json), and [final original immutability check](../_local/evidence/save-foundation-01/c-engine-harness-final/input-immutability.json). These paths are local and ignored.

## Executed checks and counting

These are different layers, with overlapping requirements. They are not added into one number of independent tests.

| Layer | Executed result | What ran |
|---|---|---|
| Python converter/reference codec | **41 checks PASS** | Repeat conversion, immutable source/output checks, independent byte/checksum/hash verification, roundtrip and malformed disposable images. This is host tooling, not engine execution. |
| Actual C regional codec | **170 checks PASS** | Actual `regional_save.c` through fixed-width host types: CRC/SHA reference vectors, streaming/framed digest, complete extension, bounds and blank-foundation rules. Separate C re-encoding of all 3 converted fixtures matched every 1,332-byte extension. |
| Actual C coordinator | **1,190 assertions PASS** | 238 assertions against each of the 3 converted fixtures, a generation-wrap fixture and an actual C-saved occupied-PC source. These include 60 interruption scenarios per source: **300 scenarios**, already included in 1,190. |
| Actual C bank probe/loader | **92 cases PASS** | Supported fixtures, all 14 rotations, adjacent/wrap selection, malformed IDs/checksums/counters/parity/header/CRC/digest/blank fields, whole-bank recovery, fork rejection and newer incompatible-format blocking. |
| Separately instrumented C cancellation | **24 checks PASS** | Private callback injection before/after actual SHA finalization, after validation/header SHA return and during special erase/write calls. The actual codec and coordinator execute; hardware IRQ timing does not. |
| Host driver/orchestration | **493 checks PASS** | Command exits, expected probe/load status and independent validation of C-generated output. These also summarize the coordinator/corpus results above; they are not 493 extra engine scenarios. |

Definitive coordinator SHA-256: `0f67df0b8e9b45d2431fdd9889d1c9681e6144d71228693da82423042daad7de`. Actual codec SHA-256: `96b3509d1df81c99ec47dd8c842fde4ee873cb2fcdef93d21cc91ec30961f599`. Both host compilations and every final qualification command exited 0. ASAN/UBSAN diagnostics were empty.

Actual transaction assertions verify logical IDs 1–13, header 0, then final signature-byte commit; preservation of the previous bank; coherent cold loads after interruption; full versus old-persisted-PC partial behavior; staged play-time/warp/RTC bytes; producer/shared-buffer/reentrant cancellation; first full save; HOF rollback/retry and failure after main commit. Rejected probe/load cases preserve live saved-RAM sentinels and do not publish loaded status. Independent Python parsing checks the actual C output checksums, CRC/SHA and protected bytes.

The conservative Python selector rejects any occupied unsupported bank. The runtime additionally permits an immediately older unsupported bank beside a valid supported successor, reporting recovery; an unsupported newer/nonadjacent bank blocks downgrade. Actual C tests qualify that runtime distinction. Converted outputs have erased alternate banks, so it does not change the three conversion results.

Evidence: [170-check C codec report](../_local/evidence/save-foundation-implementation/codec/codec-verification.json), [three C fixture comparisons](../_local/evidence/save-foundation-implementation/codec/converted-fixture-c-vectors.json), [final actual-C results](../_local/evidence/save-foundation-01/c-engine-harness-final/RESULTS.md), [exact compiler/test argv and logs](../_local/evidence/save-foundation-01/c-engine-harness-final/qualification-manifest.json), [cancellation instrumentation/commands](../_local/evidence/save-foundation-01/c-engine-harness-final/boundary-command-record.json), and [private file hashes](../_local/evidence/save-foundation-01/c-engine-harness-final/output-files-manifest.json). Earlier snapshots remain preserved, and are not counted again here.

## Local reproduction

The recorded converter/tool invocations below exited 0 from the workspace root. Their evidence filenames now exist and are exclusive-create; a replay must use new ignored evidence filenames. The converter can reuse an identical readonly output without rewriting it.

```sh
cd [LOCAL_WORKSPACE]
python3 -B scripts/convert_b2_saves.py --manifest _local/evidence/save-foundation-01/conversion-manifest.json
python3 -B scripts/qualify_firered_save_codec.py --report _local/evidence/save-foundation-01/converter-qualification.json
```

Exact replay of the same input/tool scope, with new evidence files:

```sh
python3 -B scripts/convert_b2_saves.py --manifest _local/evidence/save-foundation-01/conversion-manifest-replay-01.json
python3 -B scripts/qualify_firered_save_codec.py --report _local/evidence/save-foundation-01/converter-qualification-replay-01.json
```

The executed full coordinator driver invocation was:

```sh
python3 _local/evidence/save-foundation-01/c-engine-harness-final/run_qualification.py
```

That driver creates new corpus/output directories and records every exact Clang/test argv, real exit, stdout and stderr. Preserve the final evidence directory. To replay against the same pinned source in a fresh ignored directory, copy only the private harness inputs, then run the driver:

```sh
python3 - <<'PY'
from pathlib import Path
import shutil
root = Path('[LOCAL_WORKSPACE]')
source = root / '_local/evidence/save-foundation-01/c-engine-harness-final'
target = root / '_local/evidence/save-foundation-01/c-engine-harness-replay-01'
target.mkdir()
shutil.copytree(source / 'stubs', target / 'stubs')
for name in ('harness.c', 'harness-boundary.c', 'run_qualification.py'):
    shutil.copyfile(source / name, target / name)
PY
python3 _local/evidence/save-foundation-01/c-engine-harness-replay-01/run_qualification.py
```

The separately recorded cancellation executable can be rerun without changing any source or save input:

```sh
_local/evidence/save-foundation-01/c-engine-harness-final/harness-boundary boundary-cancellation _local/saves/firered/save-foundation-converted-01/kanto-cycle-02-frjs1.sav
```

Its precise compiler argv and actual source hash are in `boundary-command-record.json`; the 170-check codec report similarly records its exact compiler argv. Private harnesses and evidence are intentionally unavailable outside this local workspace. Replays against changed source need new fingerprints and evidence, rather than inheriting these results.

## Limits retained for review

Host dependencies simulate flash bytes, saved structures and selected game callbacks. Actual save/codec C executes, but GBA scheduling, electrical power removal, real game preparation, desktop gameplay and real PC UI were not exercised here. Host snapshots preserve measured saved-byte sizes/offsets; production ARM ABI and clean builds are separate checks. Host coordinator scratch is 5,480 bytes because host pointers are 64-bit; the separately measured ARM scratch is 5,476 bytes.

SaveBlock1 still occupies 15,868 of 15,872 bytes: its **four-byte margin** and the FireRed roamer fidelity defect remain open. Special-sector atomicity, old-ROM downgrade limitations, occupied-PC legacy migration and broad save compatibility remain outside these passes. No campaign completeness claim is made. Stop at the save-foundation review gate before Johto progression or wider conversion.

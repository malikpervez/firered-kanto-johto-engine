# Save foundation — caller and HnS regression analysis

**October 13, 2026, America/New_York. EXECUTED PASS for the bounded host and ARM checks below.** This is source and machine-code qualification; new-ROM desktop acceptance is reported separately. No Johto progression or Workstream A change is included.

## Two completion defects corrected

The resumed review of all main-save call families found two additional FireRed error paths in complete patch 0018:

| Caller | Executed failure trigger and correction |
|---|---|
| `contest_util.c:Task_ShowContestResults` | A failed link-contest save still cleared the live continue-warp flag, advanced the task and could enter result communication. The FireRed branch now restores the temporary contest variable and returns on every non-OK result. Successful behavior is preserved. |
| `hall_of_fame.c:Task_Hof_TrySaveData` | An error with no damaged-sector bits still played the save sound and advanced the shared HOF display. The existing FRLG entry had been guarded, but the compiled shared entry through `GameClear` also needed protection. The FireRed branch now uses the existing resource cleanup and returns through the failure path on every non-OK result. |

Both changes use the existing exact `FIRERED` selector. Their original non-FireRed branches are retained. There is no codec, coordinator, gameplay-field, allocation or progression change. Root froze them in the complete [0019 patch](../patches/0019-firered-save-caller-completion.patch), SHA-256 `b398435b7ca39164a0bcc935579fcccb3fd465db1d4d28418b418fc6be612b46`, applied alone to the same pinned upstream commit.

The definitive `src/save.c` remains SHA-256 `0f67df0b8e9b45d2431fdd9889d1c9681e6144d71228693da82423042daad7de`; the existing coordinator qualification is not rerun or transferred to unrelated caller bodies. Revised source fingerprints are:

| File | SHA-256 |
|---|---|
| `src/contest_util.c` | `617cd07f7de13bbd14001def3659c77ba1f08c46bfaad15b714032a023a0acfe` |
| `src/hall_of_fame.c` | `e1f4883d373472bb09f3922ba46c9d98ed8001e21961fcd295b3516fc8d89e4c` |

## Executed qualification and scope

The private host harness extracts the complete actual caller functions verbatim and compiles them with bounded dependency mocks. It reproduces the old false-completion behavior, then executes **24 revised FireRed cases** covering OK/error/corrupt/unsupported results, HOF damaged-sector states, and contest palette/wireless states. All pass; ASAN/UBSAN diagnostics are empty. A further **24 HnS control traces** match the original branches exactly. These are caller-contract checks, not actual save-coordinator, ARM IRQ or GUI execution.

Whole-file ARM qualification uses upstream's actual CPP → `preproc` → GCC `cc1` → assembler pipeline, pinned compiler and effective build flags. Both files compile for baseline/revised FireRed and HnS: **eight executed exit-0 compilations**. HnS instruction, relocation and other data sections are identical; object hashes differ only in diagnostic source-line strings. Generated constants/assets come from the successful target-specific final04 trees. This narrow pipeline takes C input on stdin, so its `__FILE__` diagnostics differ from a normal build; it is not a clean ROM reproducibility test. An earlier direct-GCC probe omitted upstream INCBIN preprocessing and failed on both baselines and revisions; that tool-use attempt is preserved and is not classified as an engine compiler defect.

Private evidence: [_local/evidence/save-foundation-resume-2026-10-13/regression-analysis/caller-contracts/manifest.json](../_local/evidence/save-foundation-resume-2026-10-13/regression-analysis/caller-contracts/manifest.json) and [ARM pipeline commands](../_local/evidence/save-foundation-resume-2026-10-13/regression-analysis/caller-arm-production-pipeline/commands.json).

The bounded inventory also reviewed normal/overwrite menu results, both HOF entries, gift/chat/RTC saves, Frontier/contest partial saves, the partial incremental family, both trade implementations, `Task_LinkFullSave` and all six parent waiters. Pike/Pyramid functions end immediately after their synchronous save and rely on the centrally selected failure screen; they have no subsequent C success acknowledgement requiring a new guard. The mystery-event occurrence is commented out; the link-debug occurrence is debug input. Existing stage/result checks remain necessary because body-ready TRUE is not durable completion. No further concrete callback/completion blocker was found in this scoped inventory; this is not an unrestricted future-feature audit.

## Exact final04 HnS comparison

The clean final04 HnS ROM, SHA-256 `9b228a6061a7aee72e80917fc6fa91d4eb72eb7a4c7c57c801c258476554ecb5`, differs from frozen010 by **1,793 bytes** and B2's HnS build by **1,792 bytes**. Every changed byte was classified:

| Change class | Against 010 | Against B2 HnS |
|---|---:|---:|
| Reordered linker veneers | 211 | 211 |
| Corresponding branches resolving to the same named targets | 1,434 | 1,434 |
| Existing assert/error numeric source-line constants | 89 | 89 |
| Existing `source:line` diagnostic strings | 59 | 58 |
| Unexplained changes | **0** | **0** |

Only 34 linker-veneer symbols change addresses. Every other recorded symbol retains its identity, address, size and type. The changed numeric diagnostic words match identical source diagnostics at their shifted lines; diagnostic string paths retain their text apart from line numbers. No new FireRed save logic is inferred to run in HnS. This comparison explains the different ROM hash; it does not transfer old desktop passes to this ROM or establish physical/runtime behavior.

Private evidence: [comparison summary](../_local/evidence/save-foundation-resume-2026-10-13/regression-analysis/hns-comparison-summary.json), with complete byte ranges, symbol tables, symbolic disassembly and diagnostic/source proofs in the same ignored directory.

The successful final05 HnS artifact is SHA-256 `0cfac50a9db64c0a0a5cc87fbc667b16d9bfd42446fe14a1cf86badfa6608959`. An executed whole-ROM comparison against final04 finds exactly **21 changed bytes**, all within ten existing `contest_util.c` / `hall_of_fame.c` diagnostic source-line strings. No further ROM byte differs. [Exact final04→final05 proof](../_local/evidence/save-foundation-resume-2026-10-13/regression-analysis/hns-final04-to-final05-source-proof.json). The artifact still needs its own native regression record.

The read-only HnS inspector also executed against the exact final05 manifest and its actual successful ARM field map. The immutable owned repair09 cycle02 fixture validates as native version 5, counter/rotation 2/2, CODEX/PATCH with money 3,220. The original SHA-256 remains `a3a590c19b4215fc4f98cb23e7e808d0995a5b50fc68e16c43285417f2354822`; no conversion occurs. This is a stored-state comparison under the new build's unchanged layout, not a new-ROM GUI load. [Bound inspection](../_local/evidence/save-foundation-resume-2026-10-13/regression-analysis/hns-baseline-final05-layout.json).

An appropriate bounded HnS native regression is: exact-ROM cold title/Continue on a writable isolated copy of the owned HnS fixture; check identity, party, inventory, rival/Dex and progression; execute one field transition and a normal game save; fully quit and cold Continue; compare the saved state. Existing opening/starter/campaign results retain their old artifact bindings. This document claims no new HnS GUI pass.

## Runtime observation boundary

Installed stable mGBA 0.10.5 supports read-only frame/register/heap observations, but the executed capability probe found no cycle clock or range watchpoint API. The prepared ROM-bound frame sampler may report sampled allocation/free bytes, observed SP and busy-frame intervals. It cannot establish instruction-level stack peaks, short-lived allocation peaks, exact save-cycle timing or native-link peer timing. A synchronous save that starts and ends between callbacks is untimed. The sampler must be rebound to the exact new ROM and linked addresses before use.

The separately coordinated private emulator diagnostic work may qualify finer observations without engine instrumentation. Its new capabilities and cases need their own executed evidence. Until then, rigorous peaks and link-peer timing remain unclaimed. Stop for save-foundation review before any Johto progression; the four-byte main-block margin, roamer defect, special-sector atomicity and old-ROM downgrade limits remain open.

# B0 approved FireRed target-separation repair

This report preserves the pre-exception investigation and review gate. The owner subsequently approved the bounded FireRed-only reservation exception in `docs/decisions/2026-10-08-b0-save-layout-exception.md`; current experimental measurements/builds/tests are recorded separately in `docs/firered-save-experiment.md`. Original failures, patches and limits below remain evidence, not an outstanding permission request.

Owner authorization and campaign-identity requirement: `docs/decisions/2026-10-08-b0-firered-repair.md`. Source remains pinned to `167aa6d537b109bb229c231ddce4616974c4da71`; the unmodified reference clone and every earlier failed build are preserved. This is a patched target evaluation, not a pristine success or a different engine selection.

## Repair scope and review

`patches/0002-firered-target-separation.patch` is a complete combined patch against pristine source. SHA-256: `05f82fb48f8619366e206df9cc167304f17608a07b70997fe37b103ef1dbb6d8`. Apply it alone; do not stack it with patch 0001, which it already includes.

The original failure arose because Mom's HnS savings implementation, specials and gift script were compiled for FireRed even though their save field and all four shared C callers were already HnS-only. Only the HnS New Bark mother script calls those savings specials. The repair applies the existing `IS_HNS` boundary consistently to the implementation, header declarations, nine special entries and shared script include. It retains the earlier target-specific Togepi condition guard.

No map, native save structure, game configuration, FireRed mother dialogue/healing, gameplay script or asset was changed. No dummy flag, placeholder special, stub return or warning suppression was added. Specials use the same generated symbolic IDs in the table and script operands for each selected target; HnS entries/order remain intact. Non-HnS special indices after the HnS-only block shift consistently rather than leaving dead placeholder entries.

Patch whitespace/application checks executed successfully. Focused ARM preprocessing checks found identical HnS Mom implementation/header/special tokens and no FireRed Mom savings symbols. These are static build-boundary checks, not runtime acceptance. Independent review agreed with the boundary. Private review evidence:

- `[LOCAL_WORKSPACE]/_local/evidence/repair-analysis/repair-authoring-02-firered/`
- `[LOCAL_WORKSPACE]/_local/evidence/b0-resumed-independent-review.json`

## Campaign identity

See `docs/firered-target-identity.md` for the exact source/generated-data evidence. The target is intended to select FireRed's Kanto/Sevii campaign inside the shared Emerald Expansion engine. It cannot be described as an original commercial-ROM byte match, the original `pret/pokefirered` engine, or complete vanilla feature parity. Runtime opening and normal saves still require the built artifact and B0 checklist.

## Executed build and native results

The first new full build, `repair-02-firered`, used the preserved manual wrapper, two jobs and the existing locked local tools. It **FAIL — EXECUTED**, real make/wrapper exit 2, after passing the previous Mom savings compilation errors. No ROM was produced. Its manifest/logs are under `_local/artifacts/repair-02-firered/` and `_local/evidence/builds/repair-02-firered/`.

The next actual failure was `src/overworld.c:1792–1793`: HnS-only `FLAG_NIGHT_POKEMON` and `FLAG_DAY_POKEMON` are referenced inside an existing runtime `if (IS_HNS)` block. A constant false runtime branch still must parse/type-check.

`patches/0003-firered-target-separation.patch` is a new complete combined patch against pristine source; it includes patches 0001/0002 and must be applied alone. SHA-256: `80f8c6d00dec00c715bd346e41c8e27e5e3f25168869b970324828d6f56fdf99`. Its only additional change surrounds that existing HnS visibility block with `#if IS_HNS`. Shared time-of-day and palette calculations remain intact. HnS preprocessing tokens in the entire `overworld.c` were identical using matching relative source paths. Application/whitespace checks passed; no FireRed day/night flag or encounter table was invented. These checks do not establish runtime day/night behavior or patched HnS ROM equivalence.

The second new full build, `repair-03-firered`, **FAIL — EXECUTED**, real make/wrapper exit 2. It passed the previous overworld errors and reached `src/save.c`. No ROM, ELF or linker map was produced. Manifest and complete logs are under `_local/artifacts/repair-03-firered/` and `_local/evidence/builds/repair-03-firered/`. All prior patches/builds remain preserved.

| Executed repair | Patch SHA-256 | Combined patch/configuration fingerprint |
|---|---|---|
| `repair-02-firered` | `05f82fb48f8619366e206df9cc167304f17608a07b70997fe37b103ef1dbb6d8` | `e9287cc5e30dd41efddcf9cf8a7dccb4816dd212977f62d15d30575ba0e33ea9` |
| `repair-03-firered` | `80f8c6d00dec00c715bd346e41c8e27e5e3f25168869b970324828d6f56fdf99` | `ec329f2729070b7de146ade4bcc5ffac4ce6059e6a40ff34b0c4f600a0db6238` |

The same combined patch was applied in another fresh tree for `repair-03-hns`. Full make/wrapper exited **0**, PASS — EXECUTED: compilation only, UTC `2026-10-08T22:18:40.433304+00:00` to `2026-10-08T22:24:16.113713+00:00`. Actual ROM: `[LOCAL_WORKSPACE]/_local/artifacts/repair-03-hns/pokehns.gba`, 33,554,432 bytes, SHA-256 `e8e75adb31cfb02119b4b3e390e089f701ebd72cf852b3dea1f0f47283721f32`. Manifest/ELF/map are beside it; logs are in `_local/evidence/builds/repair-03-hns/`. This hash differs from pristine HnS. The patch's HnS gameplay/source review is not byte identity or a native regression test. Patched HnS native checks are **NOT RUN**; all earlier HnS GUI/save results remain tied to pristine ROM `7ffd0c7572f0542f60381ec776d99f4e826ae2859d56403e56bcc82effcd88df`.

Executed object/disassembly comparison explains the changed hash: of 1,520 objects, only `src/braille_puzzles.o` differs. `CheckTogepi` is four bytes shorter (84 → 80), shifting 9,958 later sized ROM functions four bytes earlier and causing many pointer/instruction relocations. Mom, overworld and event-script objects are identical. `FlagGet` returns only 0/1 in actual source and ARM disassembly, so the original `== TRUE` gate and new early-return-on-zero gate are equivalent for that implementation. Evidence: `_local/evidence/repair-analysis/hns-repair03-byte-comparison/`. This is static source/compiled-code evidence; no native test or bit-identity claim is substituted.

## Actual save-capacity blocker

The existing `SaveBlock1FreeSpace` assertion at `src/save.c:96` fails. Two independent read-only ARM compiler probes used the locked compiler and upstream ARM/APCS ABI to measure the real configured structures, without changing source, save fields, allocation or assertions:

| Target | SaveBlock1 bytes | Four-sector capacity | Remaining bytes |
|---|---:|---:|---:|
| FireRed | 15,952 | 15,872 | **−80** |
| HnS | 15,760 | 15,872 | 112 |

The common prefix is 15,752 bytes. FireRed then needs its actual Trainer Tower fields (52 bytes), rival name (8 bytes) and Route 5 daycare Pokémon (140 bytes). HnS instead has an 8-byte Mom savings tail. This genuine regional data accounts for the 192-byte difference. Deleting these FireRed features or bypassing the assertion would not be an acceptable repair.

The same actual build reports five undeclared HnS-only flags in `LoadGameSave` migration branches: condition setup, Ice Path/Victory Road item fixes, Vermilion Samson and Route 28 scientist. They have not been guarded or changed. Source review also identified an HnS `FLAG_DEFEATED_RED` exception in shared No-EVs challenge predicates; the medicine expression remains in FireRed preprocessing, but those compilation steps were not reached in this build. It is a possible later blocker, not an executed compiler failure. Generic challenge behavior must be retained if that boundary is later repaired.

Private diagnostic evidence and exact commands/exit codes:

- `[LOCAL_WORKSPACE]/_local/evidence/save-abi-repair-03/`
- `[LOCAL_WORKSPACE]/_local/evidence/repair-analysis/firered-save-layout-diagnostic/`
- `[LOCAL_WORKSPACE]/_local/evidence/repair-analysis/repair-authoring-03-firered/`

## Historical pre-exception gate

**HOLD.** The approved compilation guards were executed and reviewed; a successful FireRed artifact and all FireRed desktop/native-save checks remain BLOCKED. Source identity confirms the intended Kanto/Sevii campaign selection, with 417 selected FRLG maps and zero selected HnS maps. An executed SHA-256 comparison found generated header/event/connection aggregates identical across baseline 02 and repairs 02/03 (`_local/evidence/source/firered-generated-map-repair-comparison.json`). It does not establish a playable ROM or whole-campaign fidelity.

The next capacity repair would change FireRed's serialized structure. `AGENTS.md` explicitly prohibits a “save-layout change” during B0, and the owner's bounded target-separation approval retained that boundary. No capacity repair, new save format, migration, feature removal or assertion suppression has been implemented. HnS layout and existing personal saves remain untouched. Day/night remains an accepted enhancement direction with existing shared code preserved and FireRed runtime behavior NOT RUN.

### Concrete proposal, not implemented

The declared `roamerPadding[7 - ROAMER_COUNT]` reserves future slots. Exact ARM measurements find FireRed has one live 28-byte roamer plus six reserved slots (168 bytes); HnS has four live roamers plus three reserved slots (84 bytes). Tracked-text searches find `roamerPadding` only at its declaration. Gameplay creation/arrays/loops use the live `ROAMER_COUNT`; save serialization still copies the whole structure, so padding is part of persisted layout. Search commands, history and ABI evidence are in `_local/evidence/repair-analysis/firered-save-layout-diagnostic/roamer-reservation-audit.json`.

Proposed bounded exception: retain the live FireRed slot and three future slots, reclaiming three unused slots (84 bytes) only for the selected FireRed configuration. Leave every other target's reservation, including HnS, unchanged and retain the native sector/checksum system and capacity assertion. Arithmetic predicts FireRed size 15,868 with **only 4 bytes free**. All FireRed fields after the reservation shift by 84 bytes; for example `dexSeen` would move from 14,784 to 14,700. This is an ABI/layout change even though it adds no save field or new format. These are measured baseline values and predicted results, not a compiled prototype.

If explicitly approved, verify actual new ARM offsets/size, HnS unchanged layout, all real FireRed fields, and target-specific migration boundaries; build in new isolated trees, retain exact patch hashes and use fresh dedicated FireRed saves for two full cold reloads. Do not import existing saves or claim compatibility. The 4-byte remainder is a B0 capacity fix, not headroom evidence for later features or merged regions. Any broader save redesign needs its own scope. An alternative owner decision is a separately pinned compatible-RHH diagnostic; it would not prove this candidate works.

### Additional source fidelity concern

The reservation audit also found an existing late-campaign FireRed roamer mismatch: shared `src/roamer.c` selects the non-HnS Hoenn route table and Latias/Latios initialization, while a selected FireRed One Island Pokémon Center script calls `InitRoamer`. The repair patches do not touch this. This is a **VERIFIED IN SOURCE** fidelity defect; its late-game trigger/visible effects are NOT RUN. Preserving the live roamer slot must not be presented as proof of correct FireRed legendary-beast behavior. The candidate still needs a later approved full-campaign fidelity audit beyond B0 opening tests.

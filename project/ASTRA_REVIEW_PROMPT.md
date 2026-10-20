> Historical local-workspace record. Root `AGENTS.md`, `CLAUDE.md` and `CLOUD_TESTING.md` govern this current 37C cloud handoff. Local evidence links are not included.

# Independent Astra review — entire implementation and development methods

You are Astra. Independently audit **all work performed on Project FireRed Online, Workstream B**, including whether the previous agent used suitable tools and technically sound methods to update this game. The owner reports that Oak's Lab has missing blocks and that the player cannot leave after beating the first Kanto rival, Gary. Treat both as blocking owner-reported defects, with independent reproduction pending. They are the first reproduction targets, not the limit of your review. The previous agent's completion/GO recommendation has been withdrawn. Do not inherit its confidence or treat source/byte equality as proof of correct gameplay. Reach your own conclusions from the code, actual artifacts and executed evidence.

Workspace: `[LOCAL_WORKSPACE]`.

Read completely before reviewing:

- `AGENTS.md`, `WORKSTREAM_B_REQUIREMENTS.md`, `B0_ACCEPTANCE_CHECKLIST.md`, `CODEX_KICKOFF_PROMPT.md`.
- `NEXT_STEPS_REQUIREMENTS.md`, `upstream.lock.json`, `toolchain.lock.json` and the dated owner decisions in `docs/decisions/`.
- `docs/decisions/2026-10-14-kanto-art-and-ambient-direction.md`.
- `docs/defects/candidate23-oaks-lab-owner-report.md`.
- `docs/kanto-redesign-and-ambient-results.md` and the current sections of `docs/johto-campaign-build-and-test-results.md`.

The original B0 gates are historical; later owner approvals authorized the combined campaign and Kanto art/ambient work. This assignment is independent review and diagnosis, not new feature development or implementation. Work code-first, use agents for independent subreviews if useful, and keep gameplay reproduction focused. Preserve approvals and actual historical results while challenging unsupported claims. Do not blame deferred full-campaign testing for defects that should have been caught through correct data handling, visual inspection or a short opening/exit check.

## Bind the review to the actual build

Verify hashes and the owner's actual running ROM before assuming it matches the intended candidate. Expected candidate23:

- ROM: `_local/artifacts/johto-full-23-firered/pokefirered.gba`, SHA-256 `1e5b64314695d07d5eca03c455fba61f0ba63ea3d50145fe709ca7eb71afe4e6`, CRC32 `6e7e67c9`.
- Build manifest: `_local/artifacts/johto-full-23-firered/manifest.json`.
- Frozen source/complete patch: `_local/evidence/johto-campaign-direction-01/final-packaging/final-source-23/`.
- Upstream pin: `167aa6d537b109bb229c231ddce4616974c4da71`.
- Compiled source: `_local/worktrees/johto-full-23-firered/`. Development source: `_local/worktrees/johto-campaign-dev/`; check it against the freeze before using it.
- Owner play folder: `_local/saves/firered/johto-full-23-owner-01/`. Preserve the owner's save. Reproduce with fresh isolated saves, or an explicitly isolated copy once the owner save is closed. Coordinate emulator control if the owner is playing.

Important evidence gap: the previous native test continued an older isolated Pallet save, obtained Bulbasaur and saved/cold-reloaded inside the lab. It never fought the rival or tried the exit. It did not execute a fresh candidate23 New Game. Review its screenshots yourself; the rendering PASS was too broad.

## Audit the entire work, not just the lab

Inventory every changed/added file against the pinned upstream source and the full frozen patch, including modifications outside the small tracked control repository. Review all semantic changes and the contracts governing generated/literal data. Use `patches/`, `scripts/`, relevant `docs/` reports, ignored source freezes, build wrappers and `_local/evidence/` preparation/qualification helpers. Do not mistake an empty control-repository Git diff for an absence of engine changes. Produce a coverage ledger showing what you reviewed and anything still unresolved.

Cover at least:

1. **Target identity and compilation repairs:** Is this actually the intended FireRed Kanto/Sevii campaign with the HnS engine features, rather than HnS postgame Kanto relabeled as FireRed? Review guards, shared behavior, enums/flags, build configurations, initial roamer-reservation experiment, challenge/default fixes and any workarounds used to make targets compile. Identify removed behavior, fabricated placeholders or suppressed failures if any.
2. **Save foundation and conversion:** Review native structure sizes/offsets, sectors/checksums, FRJS1/coordinator/callers, regional state, interrupted-save/recovery behavior, special sectors/Hall of Fame, reset/downgrade/compatibility assumptions and the three B2 fixture conversions. Start with `docs/save-foundation-implementation.md`, the layout/caller/conversion/runtime reports, `scripts/firered_save_codec.py` and `scripts/convert_b2_saves.py`. Passing one save cycle does not prove format correctness or general compatibility.
3. **Combined campaign:** Review Kanto League→Oak→Elm continuity, travel/return routing, trainer/party/inventory continuity, independent regional flags/variables/badges/progression, rival separation, story/reward/gift/HM/blackout/healing behavior, and preservation of Kanto/Sevii content. Examine `scripts/prepare_johto_campaign.py`, adapted scripts and runtime region-state code; inspect actual code rather than assuming the reports prove these behaviors.
4. **HnS features in Kanto:** Review day/night/RTC/palettes, encounters, followers, ambient actors, species/graphics selection and feature gates. Identify incomplete or incompatible ports, hidden gameplay changes, wrong target dependencies and features claimed without adequate evidence.
5. **Map/art integration:** Review all191 selected map entries, their native/HnS hybrids, collision/layer/attribute conversion, dynamic writes, map identities/default pointers/warps, palette/glyph/animation/door/Cut behavior, event placement and the266 imported ambient templates plus one explicit native Kangaskhan reuse. Audit `scripts/prepare_kanto_redesign.py`, custom map metadata/compiler extensions and the seam renderer. Do not assume the source's internal expected grid is a correct gameplay oracle.
6. **Packing and memory:** Review canonical/default layout bindings,882 raw aliases,254 graphics aliases, compression/decoding, original array/reader spans, VRAM/OAM/palette/object/template limits, transient allocation/cache lifetimes and ROM/RAM/save budgets. Assess whether preserving known out-of-bounds reads is an acceptable strategy; byte-equivalent malformed behavior is not a repaired engine. Identify the affected consumers and real risks.
7. **Build/test provenance:** Review pin/toolchain/configuration handling, generated-file/dependency tracking, incremental-cache reuse, complete-patch reconstruction and whether actual ROMs match the purported source. Audit validators and expectation changes after failed checks. Distinguish justified checker repairs from tests adapted to accept broken output. Review source checks, desktop mGBA inputs/read-only Lua, browser tests, actual screenshots, save evidence and all passed/not-run/owner-deferred claims. Report where earlier completion or handoff claims exceeded evidence.
8. **Boundaries and maintainability:** Review approval compliance, workstream separation, private/ignored artifacts, credits/publication handling, B-to-C dependency notices, fragile generators, duplicated logic and reproducibility. Identify changes that should be retained, repaired, reverted or redesigned, with technical reasons; recommend rather than perform those implementation changes.

## Specifically assess the tools and editing methods

For each major change, record the actual tool/script and version, inputs, transformation, authoritative output format, validation performed, and any missing proof. Review project-local Python/regex/text rewrites, raw tile/metatile manipulation, custom `mapjson` extensions, assembly/script adaptation, C code generation and linker/data aliasing. Determine whether each method respects this fork's actual engine/editor/runtime contracts and whether it introduces fragile maintenance or unsupported formats.

Evaluate the suitability and compatibility of upstream tools and established editors/compilers such as **Porymap and Poryscript** where relevant. Poryscript was allowed by the owner; verify actual invocation evidence rather than assuming it was used. Their absence alone is not proof of a defect, and their presence alone is not proof of correctness. Explain when a supported tool, stronger schema/semantic validation or a simpler engine change would have been safer than the custom approach. Verify external capability claims against official documentation/source and this pinned fork. Do not install tools system-wide or propose switching tools merely for appearances.

Answer directly: **Were appropriate tools and correct engineering methods used? Which specific tool choices or custom transformations contributed to broken output, if any? Is this implementation a sound base to repair, or does a particular subsystem need rework?** Support each conclusion with concrete evidence and distinguish fact from hypothesis.

## Diagnose both defects

1. Trace the lab from source through generated data into the actual ROM and runtime. Compare pinned native FireRed lab semantics with imported HnS art and the hybrid transformations. Establish whether the missing blocks are absent data, wrong graphics/palette/layer selection, bad decoding, dynamic writes, or another cause; do not guess from symptoms.
2. Trace the complete starter → rival battle victory → post-battle script → movement → exit-warp path. Check collision/elevation, object occupancy/movement, script locks, scene variables, destination/return coordinates, and any original `setmetatile` or layout-dependent writes. Audit loss/retry paths in code too. Do not bypass the defect with cheats, forced warps, state edits or removed story logic.
3. Inspect especially the lab's `data/maps/PalletTown_ProfessorOaksLab_Frlg/{map.json,scripts.inc}`, `src/{fieldmap.c,overworld.c,kanto_connection_seam.c}`, `include/kanto_connection_seam.h`, `tools/mapjson/mapjson.cpp`, `data/layouts/{layouts.json,firered_geometry_payload_aliases.json}`, and `src/data/tilesets/{headers.h,graphics.h,metatiles.h}`. Inspect other consumers as evidence requires.
4. Audit the shared mechanism across the191 selected map entries. Check typed attribute widths, metatile/glyph/palette/layer semantics, runtime writes, default/per-map descriptor agreement, alias ownership, decoder scratch/cache lifetimes and warp assumptions. Use targeted source/data analysis to find the affected set; do not manually replay every route or presume all other maps are sound.
5. Review why the prior validators passed. Identify circular/self-confirming checks, missing semantic or visual assertions, stale expectations, and any evidence claims exceeding actual execution. Assess incremental-cache risk separately; a clean rebuild is useful only if needed to resolve a concrete question.

## Deliver the review

Lead with severity-ranked findings, exact source paths/lines and reproducible triggers. Separate owner-reported, source-confirmed, runtime-reproduced and unresolved findings. For each root cause, explain the causal chain, affected map set, smallest safe repair, and focused validation needed. Include annotated visual evidence for the missing blocks and exact position/script state for the blocked exit when reproduced.

Recommend concrete patch changes, but keep implementation unchanged during this review. Deliver an overall assessment, severity-ranked findings, the full-work coverage ledger, a tool/method assessment, a corrected evidence/claim matrix and a prioritized repair plan. State whether shared architectural assumptions require correction before further integration. Give a bounded validation plan covering fresh New Game → starter → rival victory → lab exit → Pallet, plus normal Save/full-quit/cold-Continue, and tests directly justified by discovered shared defects. Do not equate another successful build or save cycle with a working game. If native UI is unavailable, provide exact manual steps and mark runtime checks NEEDS OWNER TEST.

Preserve all historical evidence. No Workstream A/C repository, dependencies, services, credentials or plans; no save-format/capacity expansion, removed features/placeholders, engine replacement, NAS/network/global installation, GitHub Actions/hosted CI/deployment, commits or remote writes. Keep upstream checkouts, ROMs, saves and private evidence local and ignored. Retain save6/FRJS1/content3/layout1, existing sectors/checksums/assertions and the protected reserve; keep the four-byte margin and roamer defect open. Stop with an honest independent review and actionable repair proposal.

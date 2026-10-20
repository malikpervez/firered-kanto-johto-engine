> Historical local-workspace record. Root `AGENTS.md`, `CLAUDE.md` and `CLOUD_TESTING.md` govern this current 37C cloud handoff. Local evidence links are not included.

# Claude: independent complete code review of Project FireRed Online — Workstream B

You are Claude, independently reviewing the complete local Workstream B implementation. This is a **code, data, architecture, build-provenance and engineering-method review. No gameplay.** Audit the actual implementation rather than accepting prior agent conclusions. Do not implement fixes, add features or rewrite the game during this review.

Workspace: `[LOCAL_WORKSPACE]`.

The intended game combines original FireRed Kanto and Sevii with the HnS Johto campaign, one trainer/collection and independent regional progress. Most players are expected to use **stock Delta**. Desktop mGBA and a separately evaluated browser runtime also exist. Workstream A's multiplayer/Discord project and Workstream C's separate art workspace remain outside this review's modification scope.

## 1. Nonnegotiable boundaries

- **Do not launch or operate mGBA, Delta, any browser emulator or any other game runtime, including headless gameplay.** Do not play through routes, battles or saves. Do not run Lua/input helpers that drive an emulator. Do not request fresh gameplay screenshots or ask the owner to play during this assignment.
- Existing logs, screenshots, manifests and B-owned fixture bytes may be inspected read-only to assess historical claims. Attribute them to their exact original build/tester. They are not new execution by you. Do not inspect or alter personal saves, launch an owner play copy, create gameplay fixtures or execute save conversions.
- Preserve all engine sources, source freezes, artifacts, asset packages, saves, control files and historical evidence. No fixes, code formatting, asset replacement, flag allocation, save-layout change, cartridge expansion, content removal, toolchain upgrade, engine replacement or dependency update.
- Do not edit or inspect unrelated Workstream A/C repositories, credentials, configurations, dependencies, services or development plans. No network/NAS/router/hosting changes, purchases, system installations, CI/automation, commits, pushes, PRs or publication. Do not message other user-owned tasks or contact anyone.
- Write only **new review outputs and necessary analysis scratch files** under a fresh ignored directory such as `[LOCAL_WORKSPACE]/_local/evidence/claude-complete-code-review-35a-01/`. If that directory exists, use the next unused suffix; never overwrite earlier evidence. No large or private material belongs in tracked control files.
- Use existing artifacts by default. Bounded host-side checks, source analysis and actual ARM layout probes are permitted in isolated review scratch paths. If source reconstruction or compilation is needed to resolve a concrete provenance question, use a separate local scratch source/build tree, the recorded configuration and at most two jobs; preserve commands/stdout/stderr/exits. Do not rebuild or regenerate files inside the frozen/current source tree. Do not install or upgrade tools. Compilation is not gameplay validation.
- Optional internal review agents may divide subsystems if your environment supports them. They inherit these same restrictions. You remain responsible for checking their findings and covering interfaces between subsystems.

If a referenced artifact is absent or mismatched, record the exact discrepancy and continue independent source work where possible. Do not guess a replacement baseline or repair evidence to make it agree.

## 2. Establish the actual baseline first

The starting candidate is **johto-full-35a**, not candidate23/26/30f/31e/32c. Verify the following against the files. If a newer candidate exists, inventory it and explain its relationship; do not silently switch away from this requested baseline.

| Binding | Expected identity |
|---|---|
| Upstream | PokemonHnS-Development/pokehns-expansion, commit `167aa6d537b109bb229c231ddce4616974c4da71` |
| Current source | `[LOCAL_WORKSPACE]/_local/worktrees/rom-space-35a-dev/` |
| Frozen artifacts | `[LOCAL_WORKSPACE]/_local/artifacts/johto-full-35a-firered/` |
| ROM SHA256 | `281906d23f03f4f5eb590b967e33b5badeff3d1c27502337a067988008bf4a49` |
| ROM CRC32 | `e5f56ba5` |
| ELF SHA256 | `f20bf9e9b7731b9680bbb628a539cb8e80a0c1fb8ff64c7ebfb2c522f6c7fc29` |
| MAP SHA256 | `13cd9efcdcb7f4ef200bde588b66fabe7b13694e1f8ff075fd5025234f532ea1` |
| Build manifest SHA256 | `a2baa3ae9d8e1b83a36f9341e8f07df688d35a4c5ca64eb4ae5d898b87ef0871` |
| Complete source freeze | `[LOCAL_WORKSPACE]/_local/evidence/rom-optimization-02/source-freeze-35a/manifest.json` |
| Freeze manifest SHA256 | `8b5ac8a8a75fc69d30cc87d3dcf87849ba0268affa1557a5fadc4b6f3ca15dad` |
| Full reconstruction fingerprint | `4ade3d421b45103fcebc36e78bd30477f10781ffa22a43ff4fd51742465ab375` |
| Complete cumulative patch | `[LOCAL_WORKSPACE]/_local/evidence/rom-optimization-02/source-freeze-35a/complete-source.patch` |
| Complete patch SHA256 | `a7e10a0c6536ca570ab1578792de9c3af4fd85718c9c11ba62d0172aafb20713` |
| Configuration fingerprint | `86edb23f2288f65c2e7eb853827ee16fd51b1985a9c03e04e00205624ccd7352` |

Verify the complete **838 added/modified source records** and the reported **36,815 pinned/additive input paths**. The 35a-versus-34b allowlist contains only four optimization files; that is **not the scope of this review**. Review the entire cumulative implementation against pinned upstream, plus project generators, build wrappers, converters, validators and relevant ignored helper scripts. A small or empty control-repository Git diff does not mean the engine has no changes. Inspect the host, repository/index state and actual paths first; preserve unrelated untracked files.

Recorded 35a build settings: pinned ARM GNU 14.2 toolchain, `make firered -j2`, `O_LEVEL=s RELEASE=0 LTO=0`. Verify actual per-object optimization exceptions, assembly flags, linker script and target guards rather than assuming all objects use the same flags. The last build was incremental from an isolated preserved clone; it was not a clean-repeat proof.

Recorded budgets, to verify independently:

- ROM used **32,536,260 / 33,554,432 bytes**; **1,018,172 bytes free**.
- EWRAM used **254,972 / 262,144 bytes**; IWRAM used **25,920 / 32,768 bytes**; heap reservation **115,968 bytes**. Allocation totals do not establish peak heap/VRAM availability.
- Actual SaveBlock1 structure **15,868 / 15,872 bytes**, four-byte margin; SaveBlock2 **3,892**, SaveBlock3 **1,332**, PC storage **34,144**; protected reserve **256 bytes**. Global allocation symbols may include padding—do not substitute their sizes for actual saved-structure sizes.
- Native save version **6**, FRJS schema **1**, content revision **3**, layout **1**. FireRed roamer fidelity remains an open issue.

## 3. Read the requirements and the current evidence chain

Read these foundational instructions completely before review:

- `[LOCAL_WORKSPACE]/AGENTS.md`
- `[LOCAL_WORKSPACE]/WORKSTREAM_B_REQUIREMENTS.md`
- `[LOCAL_WORKSPACE]/B0_ACCEPTANCE_CHECKLIST.md`
- `[LOCAL_WORKSPACE]/CODEX_KICKOFF_PROMPT.md`
- `[LOCAL_WORKSPACE]/NEXT_STEPS_REQUIREMENTS.md`
- `[LOCAL_WORKSPACE]/docs/johto-campaign-integration-requirements.md`
- `[LOCAL_WORKSPACE]/docs/save-format-registry.md`
- `[LOCAL_WORKSPACE]/docs/rainbow-story-state-registry.md`
- `[LOCAL_WORKSPACE]/docs/character-story-state-registry.md`
- Dated owner decisions under `[LOCAL_WORKSPACE]/docs/decisions/`; `[LOCAL_WORKSPACE]/upstream.lock.json` and `[LOCAL_WORKSPACE]/toolchain.lock.json`.

Read the story designs, respecting newer corrections and separating prose from implementation:

- `[LOCAL_WORKSPACE]/docs/kanto-johto-rainbow-story.md`
- `[LOCAL_WORKSPACE]/docs/kanto-johto-rainbow-event-handoff.md`
- `[LOCAL_WORKSPACE]/docs/johto-shadow-lugia-story.md`
- `[LOCAL_WORKSPACE]/docs/friends-from-the-other-side-story.md`

Use these reports as evidence indexes and claims to audit, not as unquestioned specifications:

- `[LOCAL_WORKSPACE]/docs/johto-campaign-build-and-test-results.md`
- `[LOCAL_WORKSPACE]/docs/kanto-redesign-and-ambient-results.md`
- `[LOCAL_WORKSPACE]/docs/candidate23-repair-and-tooling-audit.md`
- `[LOCAL_WORKSPACE]/docs/indigo-west-pass-results.md`
- `[LOCAL_WORKSPACE]/docs/rainbow-story-implementation-results.md`
- `[LOCAL_WORKSPACE]/docs/character-story-implementation-results.md`
- `[LOCAL_WORKSPACE]/docs/character-presentation-implementation-results.md`
- `[LOCAL_WORKSPACE]/docs/rom-optimization-results.md`
- `[LOCAL_WORKSPACE]/docs/b1-browser-runtime-assessment.md` and `[LOCAL_WORKSPACE]/docs/b1-browser-test-results.md`
- Save foundation implementation/layout/caller/conversion/review/runtime reports indexed under `[LOCAL_WORKSPACE]/docs/`.
- `[LOCAL_WORKSPACE]/_local/evidence/story-presentation-04/delivery-33b-01/README.md` and its linked build/review/source manifests.
- `[LOCAL_WORKSPACE]/_local/evidence/rom-optimization-01/delivery-34b-01/REPORT.md` and linked optimization evidence.
- `[LOCAL_WORKSPACE]/_local/evidence/rom-optimization-02/delivery-35a-01/REPORT.md`, `[LOCAL_WORKSPACE]/_local/evidence/rom-optimization-02/delivery-35a-01/manifest.json`, and `[LOCAL_WORKSPACE]/_local/evidence/rom-optimization-02/source-freeze-35a/summary.json`.
- Rocket asset package README/manifests/audits under `[LOCAL_WORKSPACE]/_local/art-handoffs/rocket-character-pack-01/`.

**Known chronology traps:**

- The controlled character-presentation report describes historical32c. Genuine James overworld art, separate Jessie/James portraits and the authorized optional Celadon duo battle were subsequently integrated in33b and retained by35a. Jenny has no battle. Do not report the historical missing James asset or generic Jenny as a current defect without checking35a.
- Candidate23's owner-reported missing Lab blocks and post-rival exit lock are historical defects with later repair evidence. Review whether their causes and shared affected mechanisms were actually fixed; do not presume they are still reproduced in35a, or presume the later reports close them without source evidence.
- The seven-friend Giratina gag has **22 draft FG events and proposed battles but is not implemented**. Its document now makes it active writing scope, superseding the earlier deferral; scripts/engine IDs/assets/build are not bound. Treat this as planned work, not a regression or completed feature. Giratina must remain nonobtainable when implemented. Additional Gen3+ legendary chapters remain deferred.
- Prior GO recommendations were bounded local-preview/review decisions, not player-release or full-campaign certification. Distinguish source equality, host models, staged checkpoints, owner reports and actual historical gameplay. Do not turn any into a new pass.

## 4. Review the complete implementation

Create an inventory and coverage ledger before diving into individual bugs. Follow data and control flow through producers, generated files, callers and unchanged consumers. Prioritize correctness, data loss, progression locks, wrong state, rendering/resource defects, portability and reproducibility over cosmetic style findings.

### A. Target identity, build configuration and compilation repairs

Verify that the selected target preserves original FireRed Kanto/Sevii rather than silently replacing it with HnS later-era Kanto. Review all local compilation guards and compatibility repairs, defaults/challenge handling, the original roamer-reservation exception and later foundation. Look for removed behavior, fake placeholders, assertion bypasses, error suppression, enum/ID misuse and unintended HnS/LeafGreen/shared-target changes.

### B. Native save foundation, coordinator and converters — highest priority

Audit actual ARM structures/offsets and every persistent writer/caller. Cover sectors/checksums, coherent-bank selection, FRJS digest/header/version handling, staging and commit order, interrupted writes and fallback, first save, rollover, corrupt/unsupported inputs, upgrades/downgrades, repeat conversions, reset paths, Hall of Fame/special-sector interactions and error recovery. Examine regional buffers, rival names, badges, roaming state, inventory, party/PC individual identity and state allocation/collisions. Preserve protected reserve and review supported older-save eligibility exactly; no general compatibility assumption.

Start with `[LOCAL_WORKSPACE]/scripts/firered_save_codec.py`, `[LOCAL_WORKSPACE]/scripts/convert_b2_saves.py` and `[LOCAL_WORKSPACE]/scripts/qualify_firered_save_codec.py`; inspect the corresponding C save/regional/coordinator implementations and all relevant callers in35a. Determine whether offline models represent real writer order and failure boundaries, rather than merely testing themselves. Review the four-byte main-block margin separately from already allocated flags/variables/regional capacity—do not assume every quest needs more structure bytes. Recommend repairs; do not run conversions or change formats.

### C. Combined campaigns, travel and regional state

Trace Kanto League → Oak referral → western Indigo outdoor/construction gate → Surf arrival → New Bark → Elm, including returns, repeated visits, supported older saves, death/blackout/heal/Fly and transitions during scripts/menus/saving. Verify one trainer/collection, no second Elm starter/reset, independent badges/flags/variables/rival name/partner/history, correct regional dispatch and preserved original Kanto/Sevii content. Audit gyms, Rocket gates, rival teams, League rewards, field moves, phone/rematches, savings and postgame entry by control flow and reference analysis. Compare generation rules in `[LOCAL_WORKSPACE]/scripts/prepare_johto_campaign.py` with their generated outputs and native consumers. Do not manually traverse maps.

Audit the HnS-to-Kanto feature ports and remaining gaps explicitly: RTC/day-night/time-based encounters and palettes, followers and their toggle, ambient Pokémon, individual Surf graphics/normal-shiny palettes, AutoRun/FastSurf, HM helper eligibility and badge/known-move/owned-HM rules, GB Player music mappings, Pokégear/radio/phone/rematches, Mom savings and regional resource dispatch. Distinguish existing shared systems from incomplete ports and intentionally retained native behavior; inspect the recorded Fly-helper eligibility concern against current source.

### D. Kanto maps, redesigned art, ambient actors and shared graphics

Review the full cumulative selected map set, its layouts/IDs/warps/connections, collision/elevation/layers/attribute widths, palettes/animations, object placements/hide flags and dynamic metatile writes. Include Oak's Lab victory/loss/exit paths, tree-cutoff/seam handling, doors and shared-layout/default-pointer semantics. Audit decoder spans, malformed/native assumptions, aliases, cache/scratch ownership/lifetimes and shared consumer protections. Find the affected sets programmatically where possible; no route-by-route gameplay.

Inspect `[LOCAL_WORKSPACE]/scripts/prepare_kanto_redesign.py`, the modified mapjson tool, source/generated map data, seam/fieldmap/overworld changes and original runtime interactions such as Cut, Rock Smash, Mart questionnaires/Mystery Gift and doors. Retaining a historical out-of-bounds read byte-for-byte is not by itself proof of safety or fidelity.

### E. Story scripts, encounters and battle outcomes

Review all current Rainbow/Nao/Ho-Oh, Mewtwo/Mew, Black Tide/Shadow Lugia, ST/JT/BL/SV and optional Rocket duo code. Build a source-level event/state graph with trigger, prerequisites, choice branches, success receipts, repeats, interruption/skip behavior, native dependencies and persistent ownership. Verify:

- Pikachu new-game eligibility; native grant/naming/recovery/Parcel/Dex flow; old saves keep actual starters and teams. Blue's approved Eevee→Umbreon cohort logic must not misuse a fourth starter index or alter Silver's independent partner/progression. Review every starter-dependent table/dialogue reference.
- Three optional Kanto starter gifts record **successful native delivery**, remain available after decline/failure, cannot repeat after successful receipt and do not use ownership/Dex/evolution/release as a receipt. Verify party/storage failure paths and Thunder Badge gating.
- Ho-Oh flyby timing and Nao continuity preserve native encounter/Baoba choice conditions. Optional Mewtwo/Mew scenes do not block native Mansion journals or Cerulean Cave/Mewtwo eligibility/battle.
- Original Articuno/Zapdos/Moltres encounters remain intact. Separate Johto corrupted replicas alone create objective credit on actual defeat **or capture**, in any order. Ownership/trades/Dex entries, flee/loss/interruption must not create success. Credits persist between visits and saving; final confrontation/restoration preserves actual caught individuals; the once-only crisis cannot restart on later native Lugia. Review both Gold/Ho-Oh and Silver/Lugia routes plus separate Navel Rock preservation.
- Jessie/James/Meowth disguises/reveals and the optional duo battle preserve native Rocket plot/rewards. Audit partner/party eligibility, trainer IDs, distinct defeat bits, whiteout/win/decline/retry and departure cleanup. Jenny has no battle. No forced Pikachu, theft or removed native encounter.
- Blue is content and enthusiastic about science after the first Kanto championship, retains his saved Kanto name and native competitive role/rematches, and is not made Viridian Gym Leader. Silver's optional growth scenes respect actual native milestone order, saved regional name/team and original actor visibility.

### F. Assets, renderer contracts and capacity

Audit the actual James/Jessie/Jenny/Meowth sheets, portraits, palettes, transparent indices, frame dimensions/order, feet alignment, right mirroring, sprite/graphics registrations, allocation/reveal/Continue refresh hooks and map transitions. Use source bytes, native binaries, converter records and existing captures; no fresh emulator images. Distinguish intentional disguises, optional Jessie comparison and pending aesthetic acceptance from actual rendering defects.

Verify ROM/RAM/heap/VRAM/OAM/palette/object budgets and lifetime contracts. Trace every optimization, including earlier map/tileset packing, normal/shiny Surf image sharing,35a battle environment/item/door aliases and the full sound waveform alias. Check full object/header sizes, alignment, linkage/symbol ownership, pointer-identity consumers, distinct palettes and read-only assumptions. Do not use mere hash equality to excuse wrong consumer meaning. Audit `-Os` configuration, target-specific exceptions, C undefined behavior/aliasing/alignment assumptions, assembly interfaces and whether incremental objects used matching flags.

For the **remaining seven-friend gag and larger visual updates**, produce a separate capacity forecast rather than pretending everything already fits. Distinguish measured packages, format-based estimates and unsized scope. Include seven OW sheets and battle portraits,22 events/dialogue/teams/receipts, portal/home-reflection/effects/sound dependencies, actor/palette staging and legal Pokémon data. Existing nine-frame formats suggest roughly31,668–47,796 bytes for seven OW characters plus seven raw static fronts and basic OW metadata, **before** scripts, trainer tables, effects, alignment and final encoding. Verify or replace this illustrative estimate; it is not a completed package or fit result. Do not allocate state or implement the gag. Identify further safe deduplication/compression opportunities and quantify only evidence-backed savings; preserve all content/gameplay/save semantics and the32MiB cartridge target.

### G. Delta and other runtime assumptions

Most intended players use stock Delta. Review portability against **Delta's actual GBA core**, not desktop mGBA alone. Verify current public primary sources if making external compatibility claims. Earlier research found Delta's GBADeltaCore pinned VBA-M with a32MiB buffer and address masking; mGBA's special64MiB Video mapper is not drop-in ordinary ROM expansion. Do not treat that research as an executed Delta test or claim current35a has been played on Delta. Inspect core-related save/RTC/timing/undefined-behavior assumptions and wrapper formats. Review B's isolated browser contract/evidence only; Workstream A's production runtime is not selected or modifiable here. Record exact source/version limitations and mark execution NOT RUN.

### H. Tool choices, reproducibility, tests and evidence quality

Assess whether the custom Python/regex/generator/raw map/tile transformations respect this fork's supported formats and runtime semantics. Compare appropriate uses of Porymap, Poryscript and native tools with actual invocation/version evidence. Neither a familiar tool name nor its absence proves correctness. Explain concrete cases where custom tooling caused or risks malformed output, brittle rewriting or maintenance failures; do not recommend wholesale replacement merely for appearances.

Review dependencies/generated outputs/stamps, complete-patch reconstruction including binary assets, provenance/rights records, private index handling, source and configuration hashing, cached/incremental build validity, real exit-code capture and source-to-ELF/ROM correspondence. Audit local test scripts, fixture staging, snapshot rebinding and reference oracles for circular expectations, wrong pointer/layout assumptions, overly permissive comparisons, ignored errors or post-failure expectation changes. Distinguish justified harness repairs from weakening tests to pass broken output. Coverage gaps alone are not proof of a code bug, and compiling is not proof of gameplay.

Review workstream/approval boundaries and B-to-C dependency notices. Identify stale reports that materially mislead the current handoff without rewriting them. Verify that changed dependencies are communicated without demanding unrelated art/tests restart.

## 5. Findings must be actionable and independently supported

For each finding provide:

1. ID and P0/P1/P2/P3 severity, with a short concrete title.
2. Exact **current** source file and line(s), script label/function and relevant caller/data producer.
3. Status: source-confirmed defect, confirmed by a host/static check, hypothesis needing runtime confirmation, known limitation, planned/unimplemented scope, or evidence/documentation gap.
4. Trigger/preconditions and complete causal chain to the wrong result; affected maps, targets, saves or builds.
5. Practical impact and any existing mitigation. Explain whether it is inherited or introduced locally.
6. Smallest safe repair or architectural alternative, including likely content/save/compatibility implications. **Recommend only; do not apply.**
7. Focused future validation needed. Describe gameplay checks if genuinely necessary, but **do not execute or request them during this review**.

Do not fill the report with speculative warnings, stylistic nits or many copies of one root cause. Do not silently dismiss an issue because it is already recorded, but identify its current status honestly. Do not claim historical owner-reported failures are currently reproduced. Clearly separate bugs, evidence gaps, design choices and future scope.

## 6. Required deliverables and completion standard

Produce one primary review report with appendices and a machine-readable coverage ledger in the fresh private output directory. Include:

- Overall engineering assessment and an explicit answer: **Is35a a sound foundation to finish and visually expand while preserving gameplay, saves and Delta compatibility? Which specific subsystem, if any, needs rework?** This is a static assessment, never a player-release/gameplay GO.
- Severity-ranked findings first, then a prioritized repair plan: immediate correctness/data-loss/progression risks, bounded fixes, architectural concerns and optional maintenance.
- Complete source/delta inventory and coverage ledger. Account for all838 frozen records, all project scripts involved, high-volume generated/binary data methods and affected unchanged consumers. Record manual semantic review versus automated/data checks. Do not label unreviewed files covered merely because a manifest hash matches.
- Requirement→implementation matrix for campaigns, features and every current story event; clearly separate22 unimplemented FG drafts and unsized visual work.
- Save/state safety assessment, original encounter/campaign preservation assessment, tool/method assessment and ROM/RAM/save/resource budget assessment with the remaining-content forecast.
- Build/source/configuration identity and provenance verdict; corrected claims/evidence matrix retaining original build labels and historical failures.
- Exact commands/checks actually executed with outputs/exits. Keep all emulation/gameplay cases **NOT RUN BY CLAUDE**; do not add an owner-test gate simply because gameplay is excluded from this assignment.
- Open decisions/blockers, concrete proposed patches and the shortest justified future validation plan. No unsolicited new features.

Do not stop after a few easy findings or only summarize existing reports. Continue across every subsystem and its interfaces. If you hit context limits, save a precise progress/coverage checkpoint and resume the same audit; do not restart from scratch or claim completion while material areas remain unreviewed. If truly blocked, explain exactly what evidence/access is missing and finish all independent work you can.

Finish with the review results and exact local report paths. Stop there. **No gameplay, no implementation, no commits or external actions.**

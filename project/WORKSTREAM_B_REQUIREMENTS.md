# Project FireRed Online
## Workstream B: Game Engine — Requirements and Codex Handoff

**Version:** 1.0  
**Prepared:** October 8, 2026  
**Owner:** Malik  
**Initial authorization:** B0 only, with an owner review before advancing  
**Execution environment:** Local development computer first; Windows is the planned baseline, but inspect the actual host  
**Repository:** Separate from Workstream A; no remote has been selected or created by this handoff

---

## 1. Mission and immediate outcome

Evaluate whether Pokémon Heart & Soul's Emerald Expansion fork is a viable foundation for one eventual game containing **FireRed's Kanto and Sevii Islands, followed by Heart & Soul's Johto adventure**.

The immediate deliverable is deliberately smaller: **two independently compiled baseline games, FireRed and Heart & Soul, with reproducible build instructions and evidence from desktop mGBA testing.** It is not a combined game, a multiplayer implementation, or a Discord release.

Malik reports that the separate multiplayer workstream is near the end of its Phase 1. Treat that as owner-provided status, not a result this session has verified. That workstream must continue without this session modifying its repository, services, credentials, dependencies, or project instructions.

The existing `PROJECT_FIRERED_ONLINE_CODEX_HANDOFF.md` remains Workstream A's specification. This document governs **Workstream B only**. It does not silently replace Workstream A's original engine-selection requirements or authorize integration changes there.

### Product direction to preserve

- FireRed's original Kanto campaign and Sevii content are the fidelity target. Document missing or altered behavior; do not quietly remove it to make a build pass.
- Johto is an additive future region, not a replacement for Sevii Islands or Kanto.
- The eventual combined game uses one trainer and collection, with independent regional story progress and badges.
- The eventual online platform targets 25 simultaneous players across a persistent shared world, with individual progression and opt-in cooperative story events. B0 does not implement or validate that capacity.
- Desktop emulator play comes before Discord integration. An early local browser compatibility check is a later, separately approved gate.

**An engine candidate is not selected merely because its repository has the right name or its Makefile contains two targets.**

## 2. Evidence and assumptions

### Source observations checked while preparing this handoff

The primary candidate's Makefile contains `firered`, `leafgreen`, and `hns` configurations with different game/map selections. Its README identifies an Emerald Expansion lineage, warns about pre-2.0 save incompatibility, and distinguishes its link functionality from compatibility with other projects. These are repository statements and source observations, **not builds or gameplay tests performed for this handoff**. [S1, S2]

The shared upstream's FRLG guide describes target switching, map-region/layout settings, and cross-group map integration constraints. That guide must be compared with the selected HnS commit; newer upstream instructions must not be applied blindly to an older fork. [S3, S4]

### Unproven assumptions to resolve

| Question | Initial status | Required evidence |
|---|---|---|
| Does FireRed compile in the selected HnS commit? | Unverified | Exact command, exit status, clean-build log and artifact manifest |
| Does that output actually play the intended FireRed opening? | Unverified | Native emulator gameplay evidence, not a title/header alone |
| Does HnS compile and pass the same basic checks? | Unverified | Separate build and gameplay report |
| Can both regional datasets coexist in one ROM? | Unverified | Later combined-build and round-trip travel tests |
| Are all original FireRed features preserved? | Unverified | Feature-parity inventory and later campaign regression |
| Will existing saves migrate safely? | Unverified | Schema audit and tested converters for explicitly supported versions |
| Is the same build usable in a browser runtime? | Unverified | Later same-ROM native/browser comparison |
| Can the engine display a crowded 25-player map? | Unverified | Later measured object, sprite, palette and memory tests |

Do not repeat previous conversational claims of completeness, compatibility, available capacity, or successful compilation as established facts. Inspect and measure.

## 3. Workstream boundaries and ownership

| Area | Owner | Workstream B boundary |
|---|---|---|
| Discord application, authentication and Activity wrapper | A | No configuration or code changes |
| World server, protocol transport, database and accounts | A | No duplicate service or replacement schema |
| Game source, map compilation, scripts, native game saves | B | Audit now; modify only within an approved milestone |
| Local engine build tooling and native emulator testing | B | B0 implementation scope |
| Browser emulator and engine-state adapter | Joint integration decision | B supplies requirements; no independent competing production adapter |
| Stable content IDs and persistent-save ownership | Joint integration decision | B documents mappings and constraints; A approves platform changes |
| Remote-player rendering and cooperative event hooks | B plus integration work | Future scope; not B0 |
| NAS deployment and public hosting | A / owner | No actions from this session |

Use a **separate directory and separate local repository**, not another branch in A's active working folder. Do not repurpose A's ports, stop its processes, alter global tool versions, or edit its `AGENTS.md`.

A missing link to A's repository does not block B0. Do not search the owner's other repositories or files for credentials. Request a read-only contract snapshot only when integration planning genuinely needs it.

## 4. Sources and selection policy

### Primary candidate

```text
https://github.com/PokemonHnS-Development/pokehns-expansion
```

Inspect its README, INSTALL, Makefile, configuration, credit notices, feature list and relevant source. Discover the current ref, then **pin a full immutable commit SHA** in the local project before building. Record the apparent upstream release/base version separately; a marketing version is not an immutable identifier.

### Reference and fallback candidate

```text
https://github.com/rh-hideout/pokeemerald-expansion
```

Use this to explain shared-engine behavior or diagnose fork-specific problems. If the HnS FireRed target is broken, propose testing a compatible RHH commit in a separate diagnostic checkout. Do not silently replace the candidate with the latest upstream or undertake a broad rebase.

### Fidelity reference only

```text
https://github.com/pret/pokefirered
```

Consult original behavior where needed. FRLG+ and unrelated Johto hacks are not selected dependencies in this workstream. Adding or switching foundations requires an explicit decision record and approval.

### Acquisition and publication policy

Read the applicable notices and record unresolved reuse questions. Preserve contributor attribution. Do not assume public source availability grants unrestricted rights to code, art, music, or game data.

Use Git clones with history for local upstream checkouts, consistent with HnS's development guidance. Do not start from a downloaded source ZIP or mix files from different unrecorded revisions. [S1]

**Default workspace model:** a small, original control repository containing our instructions, build wrappers, manifests, reports and reviewed patches; upstream source lives in an ignored local checkout. Do not vendor or push the whole upstream tree by default. This keeps inherited workflow files and unreviewed game materials out of our GitHub-bound repository. This layout is an operational safeguard, not a legal conclusion.

If a later source-fork model is preferable, propose it for review before changing repository structure or publication behavior.

## 5. Hard constraints

### HC-01 — No GitHub Actions or pipelines

Do not create, enable, execute, or publish GitHub Actions, hosted CI, automatic deployments, scheduled builds, or repository automation. Do not put `.github/workflows/` in our control repository.

Upstream may contain workflow files. They can remain inert within the ignored local upstream checkout for source fidelity, but must not be copied into our tracked project, activated, or pushed. Local test scripts invoked by a person are allowed.

### HC-02 — No unauthorized remote changes

No repository creation, forks, pushes, pull requests, releases, account-setting changes, force-pushes or upstream contributions without specific owner approval. Local read-only fetches and isolated local development are within B0. Do not request or print access tokens. Ask before committing local work if the owner's commit policy is not established; always ask before any remote push.

### HC-03 — Keep private and restricted materials local

Never commit compiled ROMs, BIOS files, personal saves, emulator save states, extracted Nintendo assets, private screenshots, credentials, tokens, or `.env` values. Review generated patches for copied protected content before publication. Do not fetch commercial ROM/BIOS downloads. Use required inputs only when the owner can supply authorized material; verify whether the build needs such inputs before asking.

### HC-04 — No destructive operations

Inspect Git state first. No `reset --hard`, broad `git clean`, deletion of unknown files, unapproved history rewriting, or modification of personal saves. Clean only disposable B-owned build outputs. Preserve an immutable baseline before repairs.

### HC-05 — Stay local

No NAS, router, firewall, Tailscale, Discord, public tunnel or cloud-service changes. No privileged installers or system-wide environment changes without approval. A later browser harness must bind to loopback by default.

### HC-06 — No fake fixes

Do not remove maps, blank out scripts, bypass assertions, disable substantial gameplay, substitute placeholder assets, or globally suppress meaningful errors just to produce a ROM. Record defects instead. No wholesale engine upgrade in B0.

### HC-07 — Honest reporting

Separate source inspection, compilation, booting, gameplay, normal save/reload, complete-campaign testing and multiplayer testing. Never imply one proves the next. Unrun tests remain `NOT RUN`; inaccessible GUI checks are `NEEDS OWNER TEST`. A failed test is not an approval waiver.

## 6. Workspace and reproducibility

Suggested **control-repository** layout:

```text
firered-online-engine/
  AGENTS.md
  START_HERE.md
  CODEX_KICKOFF_PROMPT.md
  WORKSTREAM_B_REQUIREMENTS.md
  B0_ACCEPTANCE_CHECKLIST.md
  README.md                       # Codex creates setup/run documentation
  .gitignore                      # Codex creates before cloning/building
  upstream.lock.json              # full SHA and source information, no invented values
  scripts/                        # only manual local tools actually implemented
  patches/                        # reviewed, ordered local changes; empty initially
  docs/
    environment.md
    sources-and-rights.md
    build-report.md
    test-results.md
    risks.md
    decisions/
  _local/                         # ignored by control Git
    upstream/                     # source clone with Git history
    worktrees/                    # separate disposable FRLG and HnS build trees
    artifacts/                    # ROM, ELF, linker map and symbol outputs
    saves/                        # separate native saves by target/build/test
    evidence/                     # private screenshots, logs and recordings
```

Create only B0-needed paths. `patches/` may be documented until a justified patch exists. No empty multiplayer architecture scaffolding.

Use separate target worktrees or separate clean build trees. If using one tree sequentially, verify its cleaning requirements; the FRLG upstream guide warns about target-switch contamination. Never run simultaneous cross-target builds in one mutable source tree. [S3]

### Required environment discovery

Identify the actual operating system, architecture, shell, free disk space, repository boundaries, Git status, existing compiler/toolchain versions and mGBA availability. On Windows, prefer an already available upstream-supported environment; WSL2 is an option, not an assumed prerequisite. Follow the selected commit's install guide. Do not install Linux-only tools directly into PowerShell. [S5]

If the session is on macOS/Linux rather than the planned Windows machine, use the source's supported host instructions where feasible and record the difference. Do not remotely configure another computer. Provide Windows reproduction notes, but mark them untested unless executed there.

If package installation or GUI access is unavailable, complete the safe inspection and tooling tasks, then report precisely what needs owner action. Never pretend a headless build ran a graphical playthrough.

### Reproducible artifact manifest

For every build, record source URL, full commit SHA, working-tree/patch status, target, effective configuration, build command, toolchain versions, host, start/end timestamps, exit code, output filenames, byte sizes and SHA-256 values. Include a patch/config fingerprint when applicable. Preserve the corresponding ELF/linker map if generated.

Distinguish the ROM hash from the engine commit and save format version. Do not invent a schema number for an unaudited native save.

## 7. B0 — Independent baseline builds and native emulator validation

**This is the only milestone authorized by the kickoff prompt.**

### B0 implementation requirements

| ID | Requirement | Acceptance evidence |
|---|---|---|
| B0-01 | Establish an isolated, non-destructive workspace | Resolved path, Git-state inspection and no writes to A |
| B0-02 | Read source instructions and pin the candidate | Source inventory, rights/credits notes and full SHA |
| B0-03 | Make builds repeatable | Manual commands or wrappers with dependency checks and real exit codes |
| B0-04 | Attempt unmodified FireRed and HnS builds separately | Full target-specific logs; both attempts reported |
| B0-05 | Verify actual target selection | Effective defines/map selection plus native opening behavior |
| B0-06 | Preserve baseline artifacts | Target-specific manifests and separate output/save directories |
| B0-07 | Test native gameplay and ordinary saves | Completed checklist with evidence or explicit owner-test status |
| B0-08 | Rebuild each target from clean inputs | Hash comparison and explanation of any nondeterminism |
| B0-09 | Collect initial capacity information | ROM size and available linker memory information; unknowns labeled |
| B0-10 | Deliver a decision, not an automatic merge | Go/hold/no-go report, known gaps and requested next gate |

Read the actual Makefile before choosing commands. Candidate target names include `firered` and `hns`; verify their prerequisites and options from the pinned tree. Use moderate configurable parallelism so A can continue running. [S2]

Do not guess that combining several make goals selects the intended variant. If a debug/test build is needed, determine the correct explicit build selector from the selected source. Record when debug and release configurations differ.

Capture failing stdout/stderr and return codes. Wrappers must not turn a compiler failure into a successful command because a logging pipeline succeeded. Scripts must quote paths, fail on missing dependencies, and document which shell executes them.

### B0 limited repair policy

Attempt pristine builds first. Clearly separate an upstream build defect from a missing local dependency.

Small, understood build-environment corrections or narrow compilation repairs may be proposed and tested in an isolated patch branch, with the original failure retained. Do not mix such repairs into the untouched reference checkout. The report must distinguish **unmodified success** from **success with patches**.

Stop for review if repair requires substantive gameplay changes, deleting content, changing native save structures, replacing the engine, importing another region, or resolving a large upstream merge. If two focused repair attempts do not clarify the failure, summarize the root-cause evidence and alternatives rather than continuing indefinitely.

A fallback RHH build, when approved, is a diagnostic comparison. Its success does not establish that FireRed works inside the HnS fork.

### Native testing procedure

Use a recorded desktop mGBA version obtained from the project's official distribution or an approved existing installation. Keep separate ROM filenames and save paths for the two targets. Document emulator configuration, including RTC and any automatic save-state loading. [S6]

The checklist in `B0_ACCEPTANCE_CHECKLIST.md` is normative. At minimum:

**FireRed:** new game and identity; intended Pallet Town opening; Oak introduction; starter selection; initial rival battle; outdoor/interior transitions; ordinary NPC dialogue; opening delivery/progression sequence where implemented; a wild battle and capture when legitimately available; healing and party/menu behavior; normal in-game save, full emulator exit, cold boot and continued progress.

**Heart & Soul:** new game and identity; intended New Bark Town opening; Elm/starter sequence; the opening Johto errand and first rival sequence appropriate to the pinned build; transitions and NPC dialogue; a wild battle and capture when available; healing and party/menu behavior; normal save, full exit, cold boot and continued progress.

Inspect the game's actual opening sequence instead of forcing assumed event ordering. Record any deviation from the intended campaign. Do not use debug shortcuts or a prepared save as proof that the natural opening is reachable.

For each target, perform two ordinary save/close/reload cycles and at least ten minutes of active gameplay observation. Record audio/visual/input problems, freezes and observed emulation speed. These are prototype acceptance thresholds chosen for this project, not proof of whole-game stability.

### Save verification at B0

Use fresh, dedicated test saves, never Malik's or another player's personal save. Record trainer identity, party, relevant moves/levels, money/items, current location and completed opening event. Confirm meaningful state survives cold reload and that rewards are not repeated.

A save state is not a replacement for the game's normal persistent save. Disable or bypass automatic state restoration for these tests. Preserve the native save with its exact ROM manifest. No cross-target imports or migrations are expected to work at this stage.

### B0 gate

**GO:** both baselines build, the required native gameplay/save checks pass, reproducibility evidence exists, and material limitations are documented. Any proposed tolerated defect needs owner acceptance.

**HOLD:** builds exist but gameplay needs human testing, a required tool is unavailable, fidelity is uncertain, or a narrow unresolved defect blocks a required test. Report useful deliverables but do not advance.

**NO-GO on this candidate:** evidence shows the intended target is missing, fundamentally broken or requires disproportionate repair. Provide the evidence and a limited fallback recommendation; do not silently replace the project.

Stop and request approval for B1. Do not merge regions during B0, even if both builds work immediately.

## 8. B1 — Compatibility and fidelity audit (approval required)

B1 produces an evidence-backed design and an early local browser compatibility result, not a full-region merge.

### B1.1 Engine and content audit

Inspect actual preprocessor branches, map-generation tools, version settings, registries and native save layout. Identify what is shared and what is selected exclusively at compile time.

Cover the following:

| Area | Required findings |
|---|---|
| Maps and layouts | Inclusion filters, map groups, layout formats, warp assumptions, connections and generated IDs |
| Scripts | Command compatibility, native specials, global callbacks, variable/flag reuse and script-lock behavior |
| Trainers and encounters | Identifier overlap, rematch tables, encounter configuration and reward assumptions |
| Story | FireRed Kanto versus HnS Kanto dependencies; which Johto events require the latter |
| Shared content | Species/forms, moves, items, abilities, graphics and generation settings actually enabled |
| Menus and field systems | FireRed UI coverage, navigation, Fly, field moves, registered items and RTC |
| Saves | Structs, save sectors/checksums, storage limits and version detection |
| Capacity | ROM/EWRAM/IWRAM use where measurable; graphics, palettes, object slots, map/flag capacities |
| Maintenance | Upstream divergence, local patches, compatibility assumptions and update strategy |

Do not conclude that all Pokémon or mechanics present somewhere in upstream are enabled in either tested build. Record effective configuration and actual content coverage.

### B1.2 Feature-parity and campaign inventory

Create a matrix with `present in source`, `runtime tested`, `missing`, `altered`, `unknown`, and `owner-accepted difference` as distinct concepts.

Inventory the opening; all eight Kanto gyms; major Team Rocket/rival sequences; field traversal; League/Champion progression; Sevii travel and postgame; Pokédex and storage; saving; relevant item interfaces; map/Fly UI; and optional original systems such as Fame Checker, Teachy TV and Quest Log.

These named features are **audit items**, not an assertion that this fork lacks them. Determine the facts from the pinned build. A required original feature cannot be reclassified as optional by Codex without owner approval.

For Johto, inventory its eight-gym story, major scripted events, League access, travel systems and dependencies on HnS's Kanto postgame. A source inventory is not an end-to-end playthrough. Estimate integration work separately from missing-feature restoration.

Produce a **reuse-versus-create matrix**: source path/commit, behavior observed, adaptation needed, ownership/rights status, tests and relative risk. Avoid unsupported calendar estimates.

### B1.3 Early local browser gate

After native B0 success and B1 approval, test a candidate browser GBA runtime with the **same baseline ROM hash**. First review its source, license, save API, RTC support and deployment assumptions. Coordinate runtime selection with A; do not build a second production wrapper.

Use a local test page and local file selection, not Discord or public hosting. Do not bundle ROM content into published browser code.

Check input, audio, native-speed behavior, focus changes, RTC, save export/import and refresh/restart persistence. Test native mGBA save -> browser -> native mGBA on copies, documenting exact save formats/conversion requirements. Never substitute emulator save states for native save interoperability.

No browser failure may be hidden by patching the game to bypass story logic. Report whether a runtime change, adapter change or engine fix is indicated. No claim that desktop mGBA behavior automatically proves browser compatibility.

## 9. B2 — Minimal unified-region prototype (approval required)

### Scope

One ROM, one trainer, one native save. Retain the FireRed opening and add the smallest viable Johto slice, such as New Bark Town and one necessary interior. This is not a literal plugin installation or a switch between two ROMs.

Use a clearly marked **development-only travel trigger**. It must not masquerade as the final ferry/train system or alter production story completion.

### Acceptance

1. Start naturally in FireRed Kanto and complete the opening through starter acquisition.
2. Travel into the selected Johto slice in the same running game.
3. Walk through a real Johto map/interior transition and execute a harmless native NPC interaction.
4. Return to the original Kanto location with trainer, party, inventory and progress intact.
5. Save in each region and cold-reload successfully.
6. Repeat the round trip ten times without invalid warps, broken collision, freezing or persistent-state corruption.
7. Show that Kanto and Sevii content were not overwritten or removed to make room.
8. Compare ROM and memory usage to B0 and account for major changes.

A harmless Elm dialogue interaction may be included. The full starter/reward script must wait until its assumptions and flags are deliberately adapted. Do not accidentally grant a second global starter or reset the Kanto story.

Passing B2 proves limited coexistence and persistence, not that all Johto quests, every FireRed feature, or online multiplayer works.

## 10. Unified-world design constraints

### One selected Kanto storyline

FireRed Kanto is the intended first campaign. HnS's later-era Kanto must not silently replace it. Audit dependencies before excluding duplicate HnS Kanto maps. Johto references to shared locations, League/Indigo Plateau content and return travel need explicit resolution.

### Namespaced stable identity

Define stable logical identifiers outside generated engine numbers. Proposed examples, not existing constants:

```text
kanto/pallet_town
sevii/one_island
johto/new_bark_town
kanto/oak_intro
johto/elm_intro
```

A versioned mapping binds these to the selected ROM's actual map/group/script IDs. Do not expose unversioned numeric indices as durable server identities. Do not renumber old flags or species blindly when importing content.

### Progression semantics

Specify independent regional badge/story records and deliberate rules for shared money, items, collection, party, Pokédex and field permissions. A Johto starter does not reset trainer identity or delete Kanto Pokémon. Regional caps or restricted parties are product decisions, not defaults to invent.

The game should support a future Kanto-only release followed by an additive Johto update. Reserve and map identifiers based on measured capacity, not speculative giant arrays. Do not require a player wipe merely to simplify development.

### Capacity and graphics

Measure the actual target's constraints using source and linker evidence. Account for adding maps, tilesets, scripts, music and data as well as future remote avatars. Do not assume browser emulation removes the target's hardware limits or that storage available on a PC expands the ROM address space.

The eventual server target of 25 players includes the possible case of all 25 in one map. Audit how 24 remote trainers, the local trainer, NPCs, effects and any followers compete for resources. If the renderer cannot display that case, report options and tradeoffs for approval rather than silently reducing supported visibility.

Preserve upstream deduplication where practical. No new rendering system, expanded cartridge format or major memory redesign without a measured need and a decision gate.

## 11. B3 — Progression slice and migration foundations (approval required)

Adapt a small contiguous Johto story segment after B2, then validate it with an existing Kanto character. Agree on the segment before coding. Do not attempt every Johto quest in one unreviewed task.

### Native saves remain primary evidence

B0-B2 use genuine engine saves. A proposed JSON profile or metadata sidecar is not a lossless substitute for native state. Workstream B owns engine decoding/encoding knowledge; Workstream A owns online storage and transaction policy. They must agree on authoritative state before integration.

A save metadata envelope may identify engine commit, patch/config fingerprint, ROM hash, content revision and actual supported save-layout version. That envelope does not itself implement migration.

### Migration requirements

- Inventory native fields, sector/checksum rules and format compatibility before writing converters.
- Preserve Pokémon identity and ownership, including relevant personality/original-trainer data, forms, stats, moves, held items, experience and evolution-related state. Preserve collection/storage, inventory, money, regional flags and recoverable location.
- Use stable-ID translation tables when internal identifiers differ. Do not load an old binary through new C structures and assume matching meaning.
- Keep source saves immutable. Convert a copy, validate it, load it in the target build, then commit or accept it. Reject unsupported/corrupt inputs clearly.
- Handle removed/changed maps through a documented safe-location policy that does not falsely complete story events.
- Test interrupted conversion, repeat invocation, downgrade rejection and backup restoration. A second migration must not duplicate items, rewards or Pokémon.
- Keep old build metadata and private test fixtures for each explicitly supported released format. Not every public hack save is automatically supported.

During iterative development, breaking changes to disposable test saves may be acceptable **only with explicit notice and approval**. After a supported player release, a migration or a blocked update is required; no unannounced progress reset.

A later full-campaign qualification must cover all intended FireRed/Sevii and Johto progression naturally. Debug warps are useful diagnostics, not proof of story reachability.

## 12. Future interface with Workstream A

Document, but do not implement during B0, a versioned adapter contract. A conceptual state snapshot should distinguish build/content versions, stable region/map identity, position/facing, movement mode, loading/cutscene/battle/menu state, local control lock and save-busy status. Names are proposals until agreed with A.

For later implementation:

- Generate symbols/offsets from the exact build or expose a small intentional bridge; never use guessed permanent RAM addresses.
- Define coherent read points and queued engine commands at safe update boundaries. No general-purpose server-supplied arbitrary memory writes.
- Keep external account credentials out of the ROM. Local trainer IDs are not authenticated Discord identity.
- Keep session/event-instance identity separate from canonical map identity so future opt-out and private story phases remain possible.
- Remote-player appearance must eventually be rendered safely inside the game engine, not claimed on the basis of browser overlays.
- Specify one owner and one commit path for each persistent field. A database and native save must not independently overwrite each other.
- Do not assume existing GBA link support provides 25-player networking, remote shared-world movement or cooperative script execution.

B supplies a sanitized compatibility report, manifest schema and proposed adapter capabilities to A. A's protocol or persistence changes require a joint review. Integration must not wait for all of Johto if a stable Kanto baseline and adapter can already be tested.

## 13. Testing and reporting standards

Allowed result labels:

- `PASS — EXECUTED`: reproducible evidence attached.
- `FAIL — EXECUTED`: actual result and reproduction documented.
- `NOT RUN`: no execution.
- `NEEDS OWNER TEST`: requires unavailable GUI/device/manual interaction.
- `BLOCKED`: prerequisite or defect prevents execution.

Use `VERIFIED IN SOURCE` separately for static observations. It is not a test pass. Attribute owner-performed tests as such; Codex must not claim to have operated controls it did not operate.

Every report includes environment, exact source/artifact identity, commands, actual outputs, test IDs, regressions, limitations and the requested next decision. Private raw evidence remains ignored; tracked reports may reference local paths/hashes without embedding saves or protected game media.

A local automated battle test suite can help detect engine regressions if the pinned project provides one. Verify how to invoke it; never present inherited badges or upstream CI results as local test results.

## 14. Milestones and release gates

| Milestone | Scope | Exit gate |
|---|---|---|
| **B0 — authorized now** | Separate baseline builds and desktop tests | Two real baseline build/gameplay/save results; owner review |
| B1 | Compatibility/fidelity audit and early local browser check | Evidence-based foundation and integration recommendation |
| B2 | One ROM with a small Kanto–Johto travel slice | Safe round-trip travel and cold reload in both regions |
| B3 | Agreed Johto progression slice and migration foundations | Independent story behavior plus tested supported-save preservation |
| B4 | Incremental content qualification and integration readiness | Campaign matrix, adapter agreement, remaining issues and supported builds |

Each gate requires explicit approval; a successful command is not authorization to begin the next milestone. Workstream A can proceed independently with its existing harness and platform tasks, subject to its own gates.

No guaranteed delivery date is implied. After B0/B1, estimate remaining work by concrete task and uncertainty, separating reusable content from conversion, new systems and testing effort.

## 15. Required B0 handoff outputs

| Output | Contents |
|---|---|
| `README.md` | How to build, locate local outputs, open each target and run tests |
| `upstream.lock.json` | Real source SHA, refs and provenance; no secrets or fabricated IDs |
| Manual local build tooling | Target isolation, diagnostics, error propagation and safe paths |
| `docs/environment.md` | Actual host/toolchain and any untested Windows reproduction notes |
| `docs/sources-and-rights.md` | Sources, credits, notices and unresolved publication questions |
| `docs/build-report.md` | Pristine vs patched results, commands, logs, sizes and hashes |
| `docs/test-results.md` | Checklist outcomes and private evidence references |
| `docs/risks.md` | Ranked blockers, fidelity gaps, capacity unknowns and fallback options |
| Local artifacts | Target-specific ROM/ELF/map outputs and private test saves, where produced |
| Gate summary | Go/hold/no-go, changed files and requested next approval |

A useful B0 result can be a documented failure that prevents a bad engine decision. Do not invent playable outputs just to fill this table.

## 16. Primary-source reference register

These were consulted on October 8, 2026. Links containing `master` are moving references, not pins. Codex must record commit-specific references for the actual build. This handoff was prepared from source/document inspection; **no game was compiled or playtested during its preparation**.

**S1 — HnS README: provenance, credits, save/link caveats**
```text
https://github.com/PokemonHnS-Development/pokehns-expansion
```

**S2 — HnS Makefile: candidate build and map selections**
```text
https://raw.githubusercontent.com/PokemonHnS-Development/pokehns-expansion/master/Makefile
```

**S3 — RHH FRLG guide: map/layout and build-switch considerations**
```text
https://raw.githubusercontent.com/rh-hideout/pokeemerald-expansion/master/docs/tutorials/how_to_frlg.md
```

**S4 — HnS fork's FRLG guide: compare with its pinned implementation**
```text
https://raw.githubusercontent.com/PokemonHnS-Development/pokehns-expansion/master/docs/tutorials/how_to_frlg.md
```

**S5 — HnS installation/build entry point**
```text
https://github.com/PokemonHnS-Development/pokehns-expansion/blob/master/INSTALL.md
```

**S6 — mGBA official project**
```text
https://mgba.io/
```

**S7 — HnS feature inventory; configuration still needs verification**
```text
https://raw.githubusercontent.com/PokemonHnS-Development/pokehns-expansion/master/FEATURES.md
```

**S8 — Codex repository instructions**
```text
https://developers.openai.com/codex/guides/agents-md
```

**Project reference — existing owner-supplied Workstream A handoff**
```text
PROJECT_FIRERED_ONLINE_CODEX_HANDOFF.md
Version 1.0, October 7, 2026
```
That document establishes PC-first development, no GitHub Actions, manual remote approval, separate client simulations, and the existing platform phases. It remains unchanged by this package.

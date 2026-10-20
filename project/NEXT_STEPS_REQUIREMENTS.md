# Project FireRed Online Next Stage Requirements

**Version:** 1.9
**Prepared:** October 9, 2026; updated October 13, 2026, America/New_York  
**Owner:** Malik  
**Workstream:** B, game engine  
**Status:** The owner selected Kanto League victory → Oak referral → Elm → the usual HnS Johto story, with necessary adaptations; [campaign integration requirements](docs/johto-campaign-integration-requirements.md) now record that direction. ROM0022 remains the tested first-quest baseline, with focused native gameplay/reward/repeat/save/cold-reload/Kanto-return checks passed. The new campaign handoff and full story integration are not yet implemented. **Baseline recommendation: GO for bounded development; HOLD for player release.** B2 and the FireRed-only save foundation with three fixture-copy conversions remain accepted/qualified for bounded development, with limits recorded. Cable/browser remain owner-deferred. [Historical slice requirements](docs/b3-johto-prototype-requirements.md) and [actual build/native results](docs/b3-johto-prototype-results.md) retain their precise artifact scope.

The owner has now selected the campaign handoff: **beat the Kanto Pokémon League → Oak refers the trainer to Elm in Johto → adapt necessary dialogue and follow the existing HnS Johto story.** See [the exact direction](docs/decisions/2026-10-13-kanto-league-to-elm.md) and [coherent campaign integration requirements](docs/johto-campaign-integration-requirements.md). This resolves Johto entry timing; Sevii completion and the National Dex's catch requirement are not extra entry prerequisites. One campaign integration replaces city-by-city gates. This is the selected next direction, not a claim that its code is already present in0022 or that a full campaign was executed.

The implemented save foundation supports that next integration. The game retains FireRed's Kanto and Sevii Islands followed by Johto, with one trainer and collection and independent regional story/badge progression. The current prototype covers Elm's request, a Route 29 trip to Cherrygrove's Guide and return for a one-time Potion; it does not implement HnS's eight-gym campaign. Preserve its tested source/artifacts as the baseline for the campaign adaptation.

The historical audit/foundation requirements below remain the evidence and later qualification contracts. They do not schedule another full B0/B2 run or make deferred cable/browser work a prerequisite for this first quest. Use the finite current B3 checks, retain unchanged evidence, and repeat tests only for relevant changes or actual blockers. Do not reopen settled approvals for work already covered by the dated owner direction.

The owner approved **B1 compatibility and fidelity audit** on October 9, 2026, as defined in [the original requirements](WORKSTREAM_B_REQUIREMENTS.md), accepting B0's recorded limitations for further evaluation. Its section 8.1 inventory covers effective shared content/settings, map generation, scripts/specials/callbacks/control locks, trainer/encounter/rematch assumptions, menus/field systems, saves, capacity and upstream divergence/update strategy. Preserve that audit contract and its findings. The approval also covered the frozen B-to-C handoff below; later save implementation and this quest have their own dated authorization. Roamer repair, engine replacement, final engine selection and a full campaign merge remain outside the B1 approval. See [the owner decision](docs/decisions/2026-10-09-b1-audit-and-c-handoff.md).

The owner subsequently approved [the bounded B2 two-map development travel slice](docs/b2-development-slice-requirements.md), preserving the existing save format and accepting deferred browser checks for this evaluation. See [the B2 decision](docs/decisions/2026-10-09-b2-travel-slice.md). Candidate 014 completed ten travel round trips and normal save/full-quit/cold-Continue in both regions; [the B2 gate](docs/b2-gate.md) and [native results](docs/b2-native-results.md) retain their exact evidence. After [accepting B2 on October 10](docs/decisions/2026-10-10-b2-acceptance-and-save-design.md), the owner separately approved [the exact save foundation and three fixture-copy conversions](docs/decisions/2026-10-10-save-foundation-implementation.md), then [resumed its qualification on October 13](docs/decisions/2026-10-13-save-foundation-resume.md). That foundation approval did not itself authorize Johto progression. The later [October13 playable-game direction](docs/decisions/2026-10-13-playable-johto-direction.md) now authorizes our bounded first quest; a full campaign merge remains outside this slice.

## Current foundation

The candidate is `https://github.com/PokemonHnS-Development/pokehns-expansion`, pinned to source commit `167aa6d537b109bb229c231ddce4616974c4da71`, tag `Release-v2.0.6`. The frozen B0/B1 complete experimental patch is `patches/0010-firered-fresh-monotype-default.patch`, SHA-256 `3e9b6b003557cbfacff59706ad04e4f7f2fdd58bc6162be995f91dc09742d5f3`; its C handoff remains immutable.

The accepted two-map B2 baseline uses complete patch `patches/0014-firered-b2-travel-slice.patch`, SHA-256 `4260edec61faf85a04e62744f9d5424dbc25cfa37d3bacda54e65d4df69684d1`, applied alone against that same commit. Its local ROM is `_local/artifacts/b2-04-firered/pokefirered.gba`, SHA-256 `8980ba9dced4586dda2450ea102789a4ac8bf4da731f3a8c07db18a0a41ab9f2`. The natural opening/starter was executed on B2 candidate 013; final 014 changes only two added NPC graphics selections and has its own travel/save evidence. See [the build report](docs/b2-build-report.md) and [targeted C notice](docs/b2-c-dependency-notice.md).

Current save-foundation qualification uses complete [0019](patches/0019-firered-save-caller-completion.patch), applied alone to the same source pin. The [implementation contract](docs/save-foundation-implementation.md), [format registry](docs/save-format-registry.md), [conversion/host results](docs/save-foundation-conversion-and-host-tests.md) and [caller regression results](docs/save-foundation-caller-regression-results.md) record the approved version-6/FRJS1 scope and executed evidence. The successful final05 FireRed/HnS builds have their own native qualification; prior gameplay passes do not automatically transfer to them.

The current quest build is complete [0022](patches/0022-firered-johto-map-labels.patch) on the same upstream pin. Local ROM: [b3-03-firered/pokefirered.gba](_local/artifacts/b3-03-firered/pokefirered.gba), SHA-256 `39b023532a1cd657633970777ca108b74382b1239d197756a36a32c8fcd1bd91`. Its resumed build and wrapper exited 0; independent clean reproduction is NOT RUN. Native version6/FRJS1/layout1 and the stored reserve stay unchanged; content2 records the small quest. Keep ROM/save pairs isolated, retain immutable older fixtures, and use only fresh saves or B-owned compatible copies. The [targeted C notice](docs/b3-c-dependency-notice.md) identifies the nine added maps and affected asset/test assumptions without restarting unrelated art work.

Both frozen 010 targets have reproducible clean builds and early native gameplay results, including two ordinary save/full-exit/cold-reload cycles. FireRed uses its own Kanto/Sevii campaign selection in the shared Emerald Expansion engine; it is not a retail FireRed binary. Audio is owner-confirmed for the B0 evaluation, with attribution and scope in [the audio record](docs/decisions/2026-10-09-b0-owner-audio.md).

| Tested target | Local build output | ROM SHA-256 |
|---|---|---|
| FireRed 010 | `_local/artifacts/repair-10-firered/pokefirered.gba` | `3e504731d9dd3c02ec273dc257c86f557caaf8c9b933d2f0ff73558c2e121a39` |
| HnS 010 | `_local/artifacts/repair-10-hns/pokehns.gba` | `4bb58fe3c06bc0b60146aa946cbc34f087efa607f525f68e0a1e99c0db9cde75` |

All relative local paths resolve under `[LOCAL_WORKSPACE]/`. HnS's fresh native session remains bound to its original 009 manifest; the measured 010 ROM is byte identical. Keep that association intact.

The **four-byte FireRed save margin** and **FireRed roamer fidelity defect** remain open. Full campaigns, natural Sevii/postgame reachability, broad RTC behavior and old/cross-build save compatibility remain unqualified. See [the B0 gate](docs/b0-gate.md), [test results](docs/test-results.md) and [risks](docs/risks.md).

## Work sequence and approval gates

| Stage | Required outcome | Approval boundary |
|---|---|---|
| B0 review | Evidence and limitations accepted for further evaluation on October 9, 2026 | No acceptance of defects for a player release |
| B1 audit | Recorded save/content/fidelity/capacity audit and frozen C handoff; partial browser results retained | Owner accepted deferred browser checks for bounded B2 evaluation only; no save implementation or roamer repair |
| Save foundation | Implement and qualify the exact FireRed-only design and three B2 fixture-copy conversions | Approved October10; qualified final05 builds/native/runtime, deferred cable/browser, limits retained; later playable quest authorized separately; no release approval |
| FireRed fidelity repair | Resolve the roaming legendary behavior and any other agreed blocking parity defects | Separately approve the repair scope and intended original behavior |
| B2 prototype | Complete final-014 two-map travel proof: ten round trips and native cold reload in both regions | Approved October 9, 2026; completed and owner-accepted October 10 |
| B3 first quest | Elm → Route 29 → Cherrygrove Guide → Elm, one trainer, one Potion once; focused native gameplay/save/reload/Kanto return executed | At prototype review gate under October 13 owner steering; GO for bounded development, HOLD for release; no campaign extension or broader save change yet |
| Johto campaign integration | Kanto League → Oak → Elm, coherent Johto map/story reuse with independent regional progress | Later October13 owner direction selects the flow; concrete integration requirements and source audits recorded; implementation/qualification still pending, no city-by-city gates |
| B4 qualification | Incrementally qualify intended Kanto, Sevii and Johto campaigns and integration readiness | Separate content and release gates |

B1 remains the audit and browser milestone in the original roadmap. The save foundation has its own explicit bounded approval; it does not move production migration or full Johto work into B1. Further save-policy or allocation changes require review. A postgame roamer repair need not block the accepted limited travel prototype, but it remains a release fidelity requirement.

## B1 save audit requirements

### Measured space and ownership

Produce a complete field inventory for every native save block. Record actual ARM sizes, offsets, alignment, conditional fields, sector allocation, checksum coverage, version detection and all read/write callers. Comments claiming a field is unused do not establish availability.

The preserved B1/B2 FireRed baseline measurements are below. The approved foundation retains SaveBlock1/2 and PC sizes, and grows FireRed-only SaveBlock3 to 1,332 bytes within 1,624 bytes: 256 bytes are a stored zero reserve and 292 remain uncommitted. Actual ARM and current build evidence are recorded in the foundation documents; this baseline table is not the new format's allocation table.

| Allocation | Used bytes | Capacity bytes | Unused bytes | Important limit |
|---|---:|---:|---:|---|
| Main state, SaveBlock1 | 15,868 | 15,872 | 4 | Almost no room for additional fields |
| Trainer/settings state, SaveBlock2 | 3,892 | 3,968 | 76 | Separate allocation; not extra SaveBlock1 capacity |
| Existing extension, SaveBlock3 | 52 | 1,624 | 1,572 | Extension chunks are outside ordinary payload checksums |
| Pokémon storage | 34,144 | 35,712 | 1,568 | Separate allocation with fixed sector mapping |

These are measured allocations, not a promise that all unused bytes can be used safely. References: [actual ARM layout comparison](_local/evidence/native/repair-10-full-abi/actual-final-abi-comparison.json) and [compiled field map](_local/evidence/native/repair-10-compiled-fields/native-field-map.json).

SaveBlock3 is distributed across fourteen 116-byte chunks in the existing save sectors. Determine whether it can hold the proposed regional data with suitable integrity and version handling. Its nominal free space must be reduced by metadata, integrity checks and actual ARM alignment before calculating usable capacity.

Audit unused persistent flag and variable IDs, reservations and padding separately. Prove that a proposed reuse has no conflicting caller, regional meaning or initialization dependency. Temporary variables must not be used for persistent progression. Preserve all live Pokémon, inventory, story, roamer and FireRed gameplay fields.

### Save options and budget

Compare at least these options: existing persistent flags/variables, audited reuse of reservations in place, a versioned SaveBlock3 extension, and redistribution or explicit serialization if the first options cannot meet the measured need.

The preferred option to investigate is existing flags for suitable small states plus a versioned extension for new regional records. Select it only after the audit establishes capacity, initialization, integrity and memory costs. Do not assume that changing a C structure automatically produces a safe on-disk format.

The design must include a byte budget for all agreed regional records, metadata and growth reserve; identify the remaining space in each affected block. The owner must approve a numerical reserve based on the planned content before implementation. Four bytes of main-block headroom must not be presented as adequate capacity for unspecified future features.

Retain the capacity assertions, alternating save banks, sector rotation, existing payload checksums and recovery behavior. Any change to these mechanisms requires a separately reviewed design. Record static and runtime memory constraints as well as flash capacity; spare flash is not spare working RAM.

### Required design outputs

Deliver a save allocation table, field ownership map, supported-format policy, proposed extension specification and integrity/recovery rules. Identify the exact fields that would move or change meaning, and provide an alternative if the recommended layout does not fit. Record the expected effect on FireRed, HnS, LeafGreen and Emerald; no other target change is implied by a FireRed proposal.

The design may propose format identifiers, but must not present a proposed identifier as an implemented schema version. Keep source commit, ROM hash, patch/configuration fingerprint, content revision and save-format identity distinct.

## Regional progression requirements

| State | Required behavior |
|---|---|
| Trainer identity | One trainer name, identity and ownership history across regions |
| Party and collection | Preserve Pokémon, PC storage and ownership when travelling or updating; no automatic wipe |
| Regional badges and story | Independent Kanto/Sevii and Johto records; completing an event in one region cannot complete an unrelated event in another |
| Rival and starter events | Independent regional rival records, explicit naming and starter-grant rules; revisits and reloads cannot duplicate Pokémon or rewards |
| Shared resources | Document whether money, inventory, Pokédex and healing resources are shared; do not invent regional resets or restrictions |
| Field permissions | Separate stored badges from permission policy; agree how Kanto and Johto badges affect field moves and travel |
| Location and return travel | Stable region/map identity, valid arrival locations and a recoverable return position |
| Time-dependent state | Explicit RTC/day-night and daily-event behavior across travel, normal saves and cold reloads |

Produce mappings from stable logical region, map, event and trainer identities to actual generated engine IDs. Audit numeric collisions and shared flag/variable assumptions before any content import.

FireRed's Kanto storyline and Sevii content remain the fidelity target. HnS's later-era Kanto must not replace them. Identify Johto dependencies on HnS Kanto, Indigo Plateau/League content, callbacks, encounter tables and travel systems; propose how each dependency is retained, adapted or excluded without deleting required FireRed content.

Product decisions requiring owner selection include Johto entry timing, final travel/unlock rules, regional starter policy, field permissions, regional caps or party restrictions, and supported legacy saves. B1 must present concrete alternatives and their consequences. The early prototype uses development-only travel; it does not decide final story order or unlock conditions.

**Later owner decision, October13:** the entry timing and story order are now selected by [Kanto League to Elm](docs/decisions/2026-10-13-kanto-league-to-elm.md). Use the actual FireRed game-clear event, not the similarly named post-Sevii champion flag. Existing Kanto trainer, collection, levels and resources carry forward; no new reset or restriction is authorized. Remaining starter/rival/permission and save-content mappings must be explicit when adapting the real HnS opening.

## FireRed fidelity and time systems

Create a parity matrix covering the opening, eight gyms, major Rocket/rival events, League/Champion, Sevii travel/postgame, roaming legendary, Pokédex/storage, field moves, Fly/map interfaces, important items and original systems such as Fame Checker, Teachy TV and Quest Log. Keep source presence, runtime execution, missing/altered behavior and owner-accepted differences distinct.

The current roaming implementation selects Hoenn routes and Latias/Latios in the non-HnS branch. Pin an exact FireRed fidelity reference before an approved repair. Establish original trigger conditions, all three starter-dependent legendary outcomes, eligible routes, movement/encounter behavior, flee/capture/defeat lifecycle, party/storage handling, persistence and event completion. Agree explicitly whether any original roaming bug is retained or corrected. Preserve HnS roaming behavior unless a separate change is approved. A source correction or an injected encounter does not establish natural postgame reachability. Keep that check open until a natural progression test is executed or the owner approves a clearly labelled diagnostic-only result.

Day/night is an accepted enhancement direction. Audit the existing shared implementation first, including palettes, RTC initialization, date/time changes, rollover, daily events, encounter selection and save/reload behavior. Retain shared behavior; do not add new saved fields or alter FireRed/HnS time policy without an agreed requirement. A night palette observation alone does not qualify the time system.

For Johto, inventory the eight-gym story, scripted events, League access and dependencies on HnS postgame. Produce a reuse-versus-create matrix with exact source paths, adaptation needs, tests, rights/credit status and relative risk.

## Approved save-foundation requirements and later compatibility policy

The approved implementation must preserve the complete B0 source, patches, ROMs, save fixtures and evidence as immutable references. Work in new isolated trees and save directories with a complete patch and explicit build identities.

The new regional extension must have documented initialization, format recognition, declared length, version, bounds and integrity validation, with an explicit binding to the supported save/content format. It must detect incomplete or mismatched extension data across sectors and save generations. Recovery must accept a coherent main-state/extension pair from a valid bank; it must not silently combine different save generations or convert corruption into completed or reset story state.

Legacy detection must distinguish unsupported formats from corrupt supported formats. Old uninitialized extension bytes must not be interpreted as valid new progression. Establish explicit migration, rejection and recovery behavior before loading old data through changed structures.

Choose a supported-save policy before coding. Its matrix must identify final experimental 010 saves, earlier layouts with different field offsets and other target saves as supported or explicitly rejected. B0 experimental saves are disposable evaluation fixtures, not a production compatibility promise. They may be unsupported with explicit notice and owner approval. Every later supported player format requires a tested migration or a clearly blocked incompatible update; no silent player reset is permitted.

Where migration is supported, preserve trainer and Pokémon identity, personality/original-trainer values, species/forms, stats, experience, moves/PP, held items, applicable friendship/egg/hatch/evolution state, party/storage, inventory/money, Pokédex, regional story/badges, rival names and a valid recoverable location. Include fixtures with occupied PC storage and applicable evolution-related state. Translate changed logical IDs using explicit versioned tables. A second migration must not duplicate rewards, items or Pokémon.

Use immutable source fixtures and convert copies. Document interrupted conversion, repeat invocation, downgrade rejection and backup restoration. A manifest or JSON sidecar may describe provenance, but cannot replace the native game save as authoritative gameplay evidence.

Keep any initial FireRed-specific change scoped explicitly. Confirm other targets' layouts and behavior remain unchanged unless a broader shared change is separately approved. Do not remove gameplay to obtain space or weaken an assertion to obtain a successful build.

## Acceptance tests

Current B3 acceptance is the focused first-quest walkthrough, reward/repeat behavior, normal save/full quit/cold Continue and Kanto return in [the slice requirements](docs/b3-johto-prototype-requirements.md). The build and these native gameplay checks passed; the [results report](docs/b3-johto-prototype-results.md) binds each executed step and stored comparison to its actual candidate. Independent clean `0022` reproduction, a new HnS native run, full-campaign and service tests are NOT RUN. The historical matrix below does not impose new ten-minute/ten-trip, cable, browser, full clean-repeat or campaign runs on this slice. Deferred and unexecuted checks remain labelled; this is not release qualification.

The table records the approved foundation's requirements, the accepted B2 slice and later gates. The bounded FireRed foundation, three fixture-copy conversions and host/ARM qualification have executed evidence in their linked reports; fresh final04 native execution retains its original binding. Final05 native checks and bounded runtime qualification are complete; cable/browser remain owner-deferred. General migration, roamer repair and broader time/browser qualification remain unqualified. B2's [native results](docs/b2-native-results.md) and [build report](docs/b2-build-report.md), and all B0 results, retain their exact artifact scope. Attribute human tests separately; audio confirmation does not qualify an untested future ROM.

| ID | Required evidence or test | Acceptance condition |
|---|---|---|
| AUDIT-01 | Field, sector, caller and flag/variable inventory | Exact allocation and every proposed reuse accounted for |
| AUDIT-02 | Candidate save designs and byte budget | Selected design fits measured limits, retains safeguards and has an owner-approved growth reserve |
| AUDIT-03 | Content, parity and ID/dependency matrices | Kanto/Sevii preserved; duplicate HnS Kanto and Johto dependencies have explicit resolutions |
| AUDIT-04 | Regional progression policy | Shared and regional fields, starter/reward rules and owner product choices recorded |
| SAVE-01 | Actual ARM compilation/layout probes and clean build | Approved sizes/offsets and all capacity checks pass; complete patch/logs/real exits preserved |
| SAVE-02 | Repeat clean build | Reproducible artifacts, or explained and accepted differences |
| SAVE-03 | Fresh FireRed natural opening and two normal save/cold-reload cycles | Trainer, party/storage, items/money, Pokédex, rival, location and progression retained; no duplicate grants |
| SAVE-04 | Sector-boundary, initialization and corruption fixtures | Valid extension data survives copying; invalid/truncated/mixed-generation data is detected; recovery follows the approved policy |
| SAVE-05 | Interrupted-save and bank-recovery fixtures on disposable copies | Main state and regional extension recover coherently; no invented progress or cross-generation mix |
| SAVE-06 | Every explicitly supported source-format migration | Preserved fields load in the target ROM; repeated/interrupted conversion, downgrade rejection and restore meet policy |
| REGRESS-01 | Other-target layout and artifact comparisons | No unintended changes; changed HnS artifacts receive separate native regression |
| FIDELITY-01 | Approved roamer repair and persistence tests | Intended FireRed behavior established, with natural postgame reachability reported separately from diagnostics |
| TIME-01 | Agreed RTC/day-night matrix | Time, palette, encounters/daily events and cold reload follow approved policy; limitations recorded |
| BROWSER-01 | Same-ROM native/browser/native round trip on copies | Native saves survive import/export and restart; RTC/suffix handling documented without assumed encoding |
| TRAVEL-01 | Approved B2 slice in one ROM | Natural FireRed start through starter acquisition, valid Johto map/interior/NPC interaction, return to the original Kanto location with original state intact |
| TRAVEL-02 | Ten B2 round trips and native saves in both regions | No invalid warps, collision failure, freeze, lost progress or duplicated reward; cold reload works in each region |
| TRAVEL-03 | Compiled content inventory and capacity comparison against 010 | Required Kanto/Sevii maps and scripts retained; ROM/EWRAM/IWRAM changes measured and major increases explained |

Use targeted fixtures for integrity and migration logic, followed by native gameplay. Test saves must be B-owned disposable copies; no personal saves or emulator states as persistence proof. Fault injection and debug diagnostics must be labelled and cannot prove natural story reachability.

Reuse proven unchanged artifact evidence where appropriate: if a new HnS ROM is measured byte identical to a previously tested ROM, retain its original report/binding and document the comparison. Changed ROMs require appropriate regression. Repeat or broaden tests only for a changed artifact, relevant failure or unresolved risk; do not restart all completed B0 playtests for documentation changes.

Each executed test report must record tester, date/time, exact source/configuration/ROM identity, environment, steps, expected/actual result and private evidence path. Use `PASS — EXECUTED`, `FAIL — EXECUTED`, `NOT RUN`, `BLOCKED` or `NEEDS OWNER TEST`; identify `PASS — OWNER-REPORTED` where the evidence is the owner's report. `VERIFIED IN SOURCE` is a separate static finding.

## Historical B1 browser and capacity requirements

Retain original B1 browser evidence and its owner-deferred checks; do not reopen that gate as a prerequisite to the current first quest. When browser qualification resumes within an approved scope, coordinate runtime selection with Workstream A through an owner-approved contract or runtime choice; do not inspect or modify A's repository or build a competing production wrapper. If that choice is unavailable, report the dependency and continue independent engine work.

Review runtime source/license, save API, RTC support and local execution assumptions. Use exact B0 ROM hashes, local file selection and a local test harness where needed, binding any test server to loopback by default. Test input, audio, focus, speed, save export/import and refresh/restart persistence. Keep native saves immutable and document any suffix or conversion handling. No ROM bundling, public hosting, Discord integration or network configuration changes.

Measure ROM/EWRAM/IWRAM and content/object/palette limits before selecting the B2 slice. Distinguish linker allocation from runtime peaks. Audit the future crowded-map requirement of 24 remote trainers plus the local trainer, NPCs, effects and followers as a capacity question; B1 does not implement or certify multiplayer.

## Required deliverables and review decision

The B1 handoff must include the save audit and budget, recommended design with alternatives, field/progression ownership table, parity and reuse matrices, stable-ID/dependency mappings, local browser report, capacity report, rights/credits notes, implementation estimate by concrete task and updated risks.

The save implementation proposal must name its exact target scope, layout/integrity/version changes, supported input formats, recovery/migration policy, acceptance tests and required owner choices. State whether it changes any approved B0 field offsets or bank/checksum behavior. Estimate adaptation and testing separately; no guaranteed date is implied.

Use a **GO / HOLD / NO-GO recommendation for the next specific gate**. A GO recommendation supports an owner decision; it does not automatically select the final engine or authorize the next stage. Keep tolerated defects and their expiry/release conditions explicit.

The completed B2 slice retains the natural FireRed opening and includes New Bark Town, House1 and a harmless native NPC interaction. Its development travel is visibly labelled and imports no Johto starter/reward or campaign initializer. The October 13 direction now covers the first Elm/Guide quest and its one-time reward using existing regional storage. Stop at that prototype's review gate before adapting additional story/reward logic.

## Boundaries carried forward

- Workstream A's repository, dependencies, credentials, Discord configuration, database, protocol, services and development plan remain unchanged.
- No NAS, router, firewall, Tailscale, public tunnel, deployment, hosted CI/CD, GitHub Actions, scheduling or remote write without explicit owner approval. No workflows in the control repository.
- No engine replacement, major rebase, species expansion, production multiplayer/browser adapter or full region merge under an audit approval.
- Keep upstream checkouts, ROMs, native saves, private evidence, assets and credentials in ignored `_local/` paths. Keep the control repository small and text based.
- Preserve required gameplay, checksums, assertions and credits. Resolve source/asset rights before publication; successful builds do not grant publication rights.
- No privileged/global installation, destructive Git operation, personal-save modification, commit or push without the applicable owner approval.

## B to C coordination

Provide C with a frozen, reproducible handoff of tested candidate 010 for its initial asset inventory. The complete patch, source commit/tree and file fingerprints, effective target configurations, generated-input identities, available build manifests, canonical local artifacts and known limits must be bound by an immutable hash manifest. Preserve the original build manifests; map frozen copies separately. Keep upstream history, artifacts, asset material and private evidence local and ignored.

| Responsibility | Owner |
|---|---|
| Native saves and compatibility policy | B |
| Campaign scripts, progression and content integration | B |
| Runtime RTC, day/night and palette scheduling/blending | B |
| ROM/RAM, sprite/object/tile/palette budgets and final integration | B |
| Isolated art inventory, source attribution and art packages | C |
| Replacement graphics/palette assets and their package validation | C, within B's documented runtime contracts |

C records each asset's source path/hash, target selection, format and dependencies against the frozen handoff. Its inventory and later replacements remain isolated; no C package directly edits the authoritative B baseline. Palette artwork belongs to C, while code controlling time selection, blending and bank allocation belongs to B. C reports any proposed replacement that requires a runtime or budget change for B review.

For each subsequent B baseline, provide a change notice identifying asset/dependency hashes, generated-ID mappings, formats/converters, target selection, runtime render/time/palette behavior and test assumptions affected. Identify the specific C packages and checks requiring review, with reasons. Preserve unrelated work and reuse unchanged evidence where its dependency and assumption fingerprints still match; a new ROM hash alone does not require all art work or unchanged tests to restart.

Detailed handoff, validation and change-notice requirements are in [B to C coordination](docs/b-to-c-coordination.md). This coordination does not authorize asset replacement integration, publication, messages to other tasks or changes to Workstream A.

## Owner review items

The B0 disposition, B1 audit/handoff, B2 travel proof and exact FireRed save foundation with three fixture-copy conversions are approved for evaluation. The historical [consolidated proposal](docs/save-foundation-change-proposal.md) specifies the selected layout, reserve, integrity, transaction, recovery and conversion rules; [implementation approval](docs/decisions/2026-10-10-save-foundation-implementation.md) supplies the later authorization. Broader compatibility, allocation, fidelity repair and regional product rules retain their own review boundaries.

**Current tested baseline: first playable Johto quest0022 — GO for bounded development, HOLD for player release.** Its prototype gate and evidence remain historical bindings. The owner's later [League→Oak→Elm direction](docs/decisions/2026-10-13-kanto-league-to-elm.md) now governs the next coherent campaign integration requirements, with one review of that integration rather than separate city/route gates. The new campaign is not implemented or qualified by recording this direction. Accepted B2 and save-foundation baselines stay frozen. Roamer repair, engine replacement, wider compatibility and allocation changes retain their separate boundaries. The four-byte margin, roamer defect and approximately9.63-second full-save interval measured on final05 remain open; no player release or general compatibility promise follows.


## Continuous merged-game authorization — October13,2026

The owner subsequently directed B to continue until a finished locally working game is available and to minimize repeated testing. This authorizes the League→Oak→Elm campaign implementation described in [campaign requirements](docs/johto-campaign-integration-requirements.md), including necessary local, reversible story and engine adapters. Earlier prototype/city review gates are historical; they do not require stopping this integration after each area. The finished local game still needs honest evidence before being described as working, and publication/deployment/save-capacity changes retain their separate boundaries.

Current execution status: ignored development tree `johto-campaign-dev`; original Johto campaign source/maps/trainers and contextual save, healing, phone, map/Fly/badge systems are being assembled. Dependency builds are in progress. No merged ROM/native campaign pass is claimed yet. The0022 tested candidate and accepted foundation remain frozen and available.

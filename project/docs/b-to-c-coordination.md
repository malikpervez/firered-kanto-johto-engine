# Workstream B to C coordination

**Current — repaired candidate25b.** Oak’s Lab’s missing tiles and blocked exit are fixed. Fresh opening/starter/rival victory/exit and two normal-save/full-quit/cold checks executed; the final25b lab save also reloads and exits correctly. GO for bounded fresh-game local evaluation; HOLD for release/full-campaign completion. [Audit, exact tests and remaining limits]([LOCAL_WORKSPACE]/docs/candidate23-repair-and-tooling-audit.md). Previous candidate23 completion/GO remains withdrawn.

[Frozen25b local dependency notice]([LOCAL_WORKSPACE]/_local/evidence/candidate23-independent-review/B-to-C-candidate25b-local-notice.json) binds complete patch/source/config/build/native evidence. Refresh OakLab/ThreeIslandHouse1 provider assumptions and one Celadon doorway dependency only. Unchanged art work and tests do not restart. B/C ownership is unchanged; no C repository or message was modified.

## Preserved historical records

These retain their original dates and executed scope. Earlier completion/GO and prepared-launcher wording is superseded by the current repair report above.

**Subsequent local baseline23 — October14:** [Frozen23 change notice]([LOCAL_WORKSPACE]/_local/evidence/johto-campaign-direction-01/final-packaging/B-to-C-candidate23-handoff-v2.json) and [completed art/ambient results]([LOCAL_WORKSPACE]/docs/kanto-redesign-and-ambient-results.md) bind the tested source/patch/configuration/build/ROM and known limits. Keep010 frozen; adopt23 only with targeted dependency rebinding. Unrelated art work and unchanged tests do not restart. B/C ownership and all repository/publication boundaries below remain. The original010 risk wording is historical; the later approved save foundation and current limits are recorded in23.

**Approved scope:** B1 audit and a frozen local handoff of tested candidate 010 for C's initial asset inventory, October 9, 2026. [Owner decision](decisions/2026-10-09-b1-audit-and-c-handoff.md).

C can inventory and validate art against a known engine baseline while B audits compatibility and fidelity. Neither workstream may silently change the other's authoritative inputs. C's work is retained across future B baselines unless a specific dependency or validation assumption changes.

## Ownership and interfaces

| Area | B responsibility | C responsibility |
|---|---|---|
| Saves and campaign behavior | Layout, compatibility, progression, scripts and gameplay | Identify visual dependencies; no save/story edits |
| Runtime time and palettes | RTC/time policy, palette scheduling/blending, banks/tags and render behavior | Palette artwork and visual variants that meet the supplied runtime contract |
| Engine budgets | ROM/RAM and sprite/object/tile/palette limits; resource allocation | Measure package sizes and resource use; flag over-budget replacements |
| Art inputs and packages | Supply frozen source/configuration and dependency information | Isolated inventory, attribution, replacements, packaging and validation |
| Final game integration | Review and integrate an explicitly approved C package, then qualify the affected build | Deliver a package and its evidence; do not overwrite B's baseline |

Workstream A remains responsible for its existing platform. No A repository, service, protocol, configuration, dependency, credential or plan change is part of B-to-C coordination.

## Frozen 010 handoff contract

The private handoff directory is `_local/handoffs/b-to-c/010-2026-10-09/` under `[LOCAL_WORKSPACE]/`. Its actual payload names, byte counts and hashes are recorded in the handoff manifest. The tracked summary in [the 010 handoff](b-to-c-010-handoff.md) identifies the final manifest and verification results once the freeze is complete.

The payload must contain:

- Source commit/tree identity, a self-contained pinned source snapshot with its declared history scope, and a file/blob inventory with target-specific source/generated fingerprints. The 010 package retains a depth-1 snapshot and its required shallow marker; original upstream history remains in B's preserved checkout.
- The complete 010 patch applied alone to the pristine source pin, with its hash and patch/configuration fingerprint. Earlier incremental patches are not stacked onto it.
- Source/toolchain lock files, manual build wrapper and invocation, activation/environment information, actual effective target definitions and configuration inventories.
- Original available final clean/repeat build manifests and supporting generated/applied diff and log evidence. Frozen-copy mappings are separate from original manifest paths.
- One canonical local ROM/ELF/map set for each target, with verified hashes; no duplicate repeat artifacts are necessary.
- Recorded build/native test scope and known limits, including the original HnS 009 session's association with byte-identical 010 output.
- A manual verification and reproduction procedure, its real verification result and a hash manifest covering every frozen payload file.

No native save, emulator state, credential or private media is needed for C's initial asset inventory. Keep those B-owned inputs outside this handoff. Upstream workflow files retained inside ignored source history remain inert; do not copy or activate them in a control repository.

Freeze only a verified package. Keep original inputs intact, preserve failed verification evidence and create a new handoff identity when corrections are needed. Read-only permissions protect the new package from routine edits; hashes remain the identity and verification criterion.

## C initial inventory requirements

C works from verified copies in its own isolated workspace. Record the handoff manifest hash and source/configuration identity before inventorying. Do not switch source revisions or use generated outputs from another target without recording a new dependency.

Each inventory entry records a stable logical asset identity, source path and hash, selected target(s), asset category, actual dimensions/format/bit depth, compression/conversion steps, palette/tile/sheet/animation dependencies, runtime references and relevant attribution/rights status. Separate source availability from actual target inclusion and runtime use. A global generated ID or an existing filename is not proof that the asset is present in either ROM.

Cover sprites and sheets, overworld characters/followers, battle graphics, tilesets/maps, UI/fonts/icons and palette variants as they apply to the selected targets. Catalogue duplicate/shared assets and conversion outputs so one replacement does not accidentally change unrelated consumers. Palette contracts include transparency, color count, tags/banks and time-dependent variants where applicable; B resolves any runtime uncertainty.

Initial inventory does not authorize removal of game content, changing map/collision behavior, new species, changing save formats, altering RTC/time policy or replacing the renderer. An art package requiring any such change is an integration proposal for separate review.

## C package and validation requirements

For later approved replacement work, a C package contains its source-baseline dependency manifest, original/replacement asset hashes, logical IDs and paths, conversion tools/versions/options, resource deltas, attribution/rights notes and a validation report. Binary assets and private visual evidence remain ignored and local until publication is explicitly approved.

Identify intended target(s), every shared consumer, relevant layout/animation/palette contract and any engine changes required. Validate package dimensions, format, palette limits, transparency, animation/frame order, conversion and resource use. Runtime rendering observations must name the exact built package and ROM; previews and source checks do not prove campaign behavior.

B may audit an integration proposal under B1, but neither B1 nor the handoff authorizes actual replacement integration. B owns final engine review, changed-artifact identification and engine/campaign regression; C owns art validation and corrective art packages.

## Subsequent B baseline change notices

Each new B baseline receives a new immutable identity and a comparison with the C baseline it supersedes. A notice must state:

1. Old/new source, complete patch, configuration, handoff and artifact identities.
2. Added, removed, renamed or changed asset inputs and shared dependency hashes.
3. Changed target selection, generated IDs, source-to-runtime mappings, formats, converters and build options.
4. Changed tile/palette/object limits, runtime drawing/time/palette behavior or other assumptions used by C tests.
5. Affected C inventory entries/packages and the specific checks to repeat, with the dependency or assumption that changed.
6. Unaffected work and evidence that remain reusable, plus unresolved impact questions for B or C.

Use dependency closure to assess impact. A changed shared palette can affect several consumers; a documentation-only change cannot invalidate sprite conversion. Changed generated IDs require mapping review even when art bytes match. A ROM hash change requires identifying its cause and affected assumptions, not resetting every C package.

If dependencies and assumptions are unchanged, retain the old C evidence and record the comparison binding it to the new baseline. If impact is uncertain, isolate the uncertainty and relevant package; do not order unrelated inventory or art work to restart. C need not adopt every intermediate B build.

## Handoff acceptance and limits

The handoff is ready for initial inventory when the source bundle, shallow boundary and payload hashes verify, canonical artifacts match the recorded tested candidate, configurations and original manifests are available, reproduction steps are explicit and known limits are attached. No new build or playthrough is required solely to copy and verify unchanged baseline bytes.

The four-byte FireRed save margin, unprotected SaveBlock3 extension, FireRed roaming legendary mismatch, uncertain full-campaign/Sevii fidelity, unqualified broad RTC behavior, unknown runtime memory peaks and unresolved publication rights remain visible. C inventory does not certify or repair them. Initial art inventory is not approval of the candidate for a player release.

Keep all artifacts/private evidence local and ignored. No GitHub Actions, hosted CI/CD, remote writes, deployment, NAS/network configuration, global installation, commit or push is implied. Do not read or modify another workstream's repository or send it a message without the applicable owner authorization.
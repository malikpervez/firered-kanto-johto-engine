# B1 review gate

**Historical closeout; current authorization update — October 13, 2026.** The B1 findings and artifact-bound test tables below are retained as recorded. The owner subsequently approved and accepted B2, then separately approved the [FireRed-only save foundation and three fixture-copy conversions](decisions/2026-10-10-save-foundation-implementation.md). Implementation, conversion and host/ARM checks are executed, with fresh final04 native evidence retained; final05 native checks and review closeout are ongoing. The earlier pending-B2/save-implementation statements below describe the B1 closeout date. Browser work remains owner-deferred. See the [current implementation contract](save-foundation-implementation.md), [caller regression results](save-foundation-caller-regression-results.md) and [resume decision](decisions/2026-10-13-save-foundation-resume.md). Stop for review before Johto progression.

**B1 ready for review; extended testing stopped at owner direction.** Source/save/capacity audits and the frozen C handoff are complete. The approved isolated browser candidate ran FireRed: gameplay, two normal saves and one cold tab reopening executed. The remaining browser matrix is deferred, not passed. Recommend the [bounded B2 development travel slice](b2-development-slice-requirements.md) as the next implementation approval. Save implementation and full region integration remain unapproved. C's initial inventory remains GO.

The later [browser authorization](decisions/2026-10-09-b1-browser-candidate.md) and [owner test-stop direction](decisions/2026-10-09-b1-owner-test-stop.md) govern this closeout. No further testing is scheduled or running.

The owner approved B1 audit and the C handoff on October 9, 2026, accepting B0 limitations for further evaluation. [Authorization](decisions/2026-10-09-b1-audit-and-c-handoff.md), [requirements](../NEXT_STEPS_REQUIREMENTS.md).

## Findings that affect the next decision

| Finding | Evidence and implication |
|---|---|
| FireRed is a separately selected campaign | 010 selects 417 FRLG maps and zero HnS maps; its native Pallet/Oak/starter/Parcel opening was tested in B0. It uses the shared Emerald Expansion engine and altered mechanics/UI; this is not a retail FireRed equivalence claim. |
| Main save block is still nearly full | Actual ARM FireRed SaveBlock1 is 15,868/15,872 bytes, with four bytes free. No new field or layout change was made in B1. |
| Spare extension storage needs integrity design | Existing SaveBlock3 chunks are outside ordinary payload checksums; some save paths update only logical sectors 0–4. Source recovery/generation assumptions need review before new records can safely use that capacity. Fault/corruption tests are NOT RUN. |
| Regional state cannot be copied wholesale | HnS and FireRed reuse numeric flags/variables; HnS travel scripts include Kanto progression reset behavior. A combined game needs an explicit mapping and initialization policy. No import or merge was performed. |
| Original FireRed systems have fidelity gaps | Fame Checker and Teachy TV dispatch to CannotUse; their presence as items does not prove functionality. Quest Log and other original interfaces require the report's qualified source assessment and later runtime coverage. No feature is silently reclassified as optional. |
| FireRed roamer fidelity remains open | The selected non-HnS code uses Hoenn routes/Latias–Latios instead of the starter-dependent beast. Postgame is NOT RUN; no repair was made. |
| Object budget cannot meet the crowded-map requirement unchanged | 16 active object events; 64 software sprites with palette/tile limits. Twenty-five trainers plus NPCs/effects/followers require a later design and executed resource validation. |
| Static memory is measurable; peaks are unknown | FireRed: ROM 29,853,828, EWRAM 247,732, IWRAM 25,944 bytes. HnS: 31,707,908 / 248,096 / 25,704. These are final 010 linker allocations, not runtime peaks or proof a region merge fits. |
| Browser qualification is partial | The approved isolated mGBA WASM candidate imported FireRed native bytes and ran gameplay. Two saves/one cold tab reopening executed; HnS browser, second reload/refresh, effective focus change and desktop return were deferred by the owner. A remains untouched. |
| Rights and attribution remain unresolved | Original source/credits inventory remains applicable; C records per-asset rights and inherited attribution. No publication is approved. |

## Reports and handoff

- [Save, capacity and proposed budget audit](b1-save-and-capacity-audit.md): actual fields/callers, sector/checksum/save-path analysis, alternatives, numerical proposal, supported-save policy and hardware limits.
- [Content and fidelity audit](b1-content-and-fidelity-audit.md): effective configuration, map/ID/dependency inventories, scripts/control assumptions, campaign parity, reuse and maintenance.
- [Browser source assessment](b1-browser-runtime-assessment.md) and [executed results](b1-browser-test-results.md): exact pins, partial FireRed results, save hashes and deferred checks.
- [Next implementation requirements](b2-development-slice-requirements.md): concrete two-map travel prototype for approval.
- [Next-gate proposal](b1-next-gate-proposal.md): regional product alternatives, state ownership, bounded B2 slice and estimates separating adaptation from validation.
- [Frozen 010 handoff](b-to-c-010-handoff.md) and [B/C coordination](b-to-c-coordination.md): local package identity, verification, reproduction, responsibilities and targeted future change notices.
- [Historical B0 gate](b0-gate.md) and [source/rights inventory](sources-and-rights.md): retained native/build evidence and limits.

## Executed versus pending

| Category | Status |
|---|---|
| Source/configuration/map/symbol audit | EXECUTED — static evidence; no new campaign pass |
| Save fields/callers/sector/recovery source audit | EXECUTED — existing final ARM evidence inspected; no new format |
| ROM/RAM and object/palette/tile capacity inventory | EXECUTED — static bounds; runtime peaks NOT RUN |
| Frozen-package/source/artifact verification | PASS — EXECUTED; 36,955 checks, no failures, real exit 0. Exact manifest and receipt hashes are in the handoff report |
| New game builds or desktop gameplay | NOT RUN in B1; unchanged B0 evidence retained |
| Browser launch/input/gameplay/speed | FireRed EXECUTED; HnS NOT RUN — owner deferred |
| Browser audio | FireRed PCM EXECUTED; sample listening PASS — OWNER-REPORTED; HnS NOT RUN |
| Browser save persistence | FireRed two saves/one cold tab reopening EXECUTED; second reload/refresh NOT RUN |
| Browser focus and RTC | Effective focus change NOT RUN; limited clock/night palette observed, broad RTC qualification NOT RUN |
| Native/browser/native save round trip | PARTIAL: FireRed native → browser executed; desktop return and HnS browser NOT RUN |
| Full Kanto/Sevii/Johto campaigns and corruption/recovery qualification | NOT RUN |
| C inventory/replacements | Package supplied; C work itself not executed by B |
| Save implementation, roamer repair, engine replacement, region merge | Not authorized and not performed |

## Decisions and stop point

**GO recommendation for C's initial inventory against the verified frozen 010 package only.** C owns its isolated inventory and art packages; B retains saves, campaign behavior, runtime time/palette systems, budgets and final integration. Future B changes identify specific affected asset dependencies or test assumptions. Unrelated art and unchanged validation do not restart merely because the ROM hash changes.

**Browser acceptance remains partial and owner-deferred.** The candidate decision was resolved. Do not resume extended tests automatically or transfer FireRed browser results to HnS. B0 native evidence retains its original scope.

**Await approval of the concrete B2 slice.** It proposes one-trainer Kanto–Johto development travel using existing persistent fields and accepts deferred browser checks for development only. New regional progression/save-format work is excluded. Stop if new allocation is required. The four-byte margin and roamer defects stay open; tolerated evaluation limits expire before release qualification.

No Workstream A or C repository changes, multiplayer/Discord, NAS/network changes, system installation, GitHub Actions, hosted automation, staging/commit, remote write or deployment were performed. Artifacts/source/private evidence remain under ignored `_local/`. Stop here for owner review; later scope needs explicit approval.

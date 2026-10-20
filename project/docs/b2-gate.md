# B2 review gate — one-trainer development travel

**Accepted B2 closeout — October 10, 2026, America/New_York.** B2 implementation and bounded native acceptance are complete and [accepted by the owner](decisions/2026-10-10-b2-acceptance-and-save-design.md). Its exact evidence below remains frozen.

**Later authorization update — October 13, 2026:** The owner separately approved the [FireRed-only save foundation and three fixture-copy conversions](decisions/2026-10-10-save-foundation-implementation.md), then [resumed qualification](decisions/2026-10-13-save-foundation-resume.md). Implementation, conversion and host/ARM checks are executed, with fresh final04 native evidence retained; final05 native checks and review closeout are ongoing. See the [implementation contract](save-foundation-implementation.md) and [caller regression results](save-foundation-caller-regression-results.md). Stop for review before independent Johto progression. The pre-foundation approval recommendations below are historical.

**Original B2 recommendation: GO for accepting the two-map development travel proof; HOLD player release, independent Johto progression and save implementation pending separate approval.** That later save-foundation approval is recorded above; this B2 recommendation itself authorizes no subsequent work. The four-byte main-block margin and roamer fidelity defect remain open, and the implemented foundation has its own qualification review.

The prototype starts with the FireRed trainer, preserves Kanto/Sevii selections and adds New Bark Town plus House1 in the same ROM. Labelled development guides travel from Pallet to New Bark and back. It grants no Johto starter or reward, initializes no Johto campaign, allocates no regional progression and changes no save format.

## Exact review candidate

Source pin: `167aa6d537b109bb229c231ddce4616974c4da71`, upstream `Release-v2.0.6`.

| Deliverable | Exact local path and identity |
|---|---|
| Final ROM | [pokefirered.gba]([LOCAL_WORKSPACE]/_local/artifacts/b2-04-firered/pokefirered.gba), SHA-256 `8980ba9dced4586dda2450ea102789a4ac8bf4da731f3a8c07db18a0a41ab9f2` |
| Complete patch against pinned upstream | [0014-firered-b2-travel-slice.patch]([LOCAL_WORKSPACE]/patches/0014-firered-b2-travel-slice.patch), SHA-256 `4260edec61faf85a04e62744f9d5424dbc25cfa37d3bacda54e65d4df69684d1`; apply alone, not stacked with earlier patches |
| Clean build/configuration manifest | [manifest.json]([LOCAL_WORKSPACE]/_local/artifacts/b2-04-firered/manifest.json), SHA-256 `385a5330782851a65c43683fe01d86743fc79180e9d442ea52705ed5200c614b` |
| Build, source deltas and reproduction | [B2 build report]([LOCAL_WORKSPACE]/docs/b2-build-report.md) |
| Executed native tests and owner access instructions | [B2 native results]([LOCAL_WORKSPACE]/docs/b2-native-results.md) |
| C dependencies and affected checks | [B2 C notice]([LOCAL_WORKSPACE]/docs/b2-c-dependency-notice.md) |

Outputs, source trees, saves and private evidence are local and ignored. The control repository has no remote or staged changes; no commit, push or publication was performed. Reproduction uses the locked local tools and the complete patch as described in the build report.

## Acceptance and retained evidence

| Required B2 outcome | Disposition |
|---|---|
| Natural FireRed opening and starter once | PASS — EXECUTED on unified candidate 013: RED/BLUE, Oak, Bulbasaur, original rival battle. Final 014 changes exactly two NPC graphics constants; its fresh opening was NOT RUN. Source evidence retains this distinction. |
| New Bark/House1, dialogue, return access and collision | PASS — EXECUTED on final 014. Original HnS tiles render; existing FireRed trainer/development NPC sprites are used. |
| Ten complete Pallet → New Bark → Pallet trips | PASS — EXECUTED on final 014, correct arrivals and usable controls at every leg. |
| Normal save, full exit and fresh-process Continue in Johto and returned Kanto | PASS — EXECUTED on final 014. No emulator state restoration; immutable native backups and valid native sectors/checksums retained. |
| State preservation | PASS — EXECUTED: visible party, Potion, trainer ID/money/badges; read-only backup comparison of rival, Dex and all story flags. Only normal walking counters changed among variables. |
| Existing save layout and live fields | PASS — EXECUTED ARM comparison: all 249 ABI and 126 field measurements equal 010, with protected save/configuration sources unchanged. SaveBlock1 remains 15,868 / 15,872 bytes. |
| Existing Kanto/Sevii selections and IDs | PASS — EXECUTED generator comparisons on 012 plus reviewed 013/014 deltas; old map/layout/group IDs retained, exactly two HnS maps added. |
| Separate HnS scope | Executed 011 clean build; one diagnostic-string byte differs from 010, link map/static budgets unchanged. Non-FireRed generated/preprocessed branches retain their recorded comparisons. Final 014 HnS clean build and new native HnS playthrough are NOT RUN; preservation is source/data evidence, not transferred runtime qualification. |
| C handoff | Frozen tested010 remains immutable. Only dependencies and test assumptions affected by this slice require C review; unrelated art work retains its evidence. |

The 011 compiler failure and 013 absent-NPC runtime failure are preserved. Final 014 fixes the latter by selecting two existing FireRed sprites, without importing extra art or removing gameplay. The natural 013 opening and own fresh B2 checkpoint are carried forward only across that exact correction; no personal, retail or 010 save was used and no general compatibility is claimed.

Final clean and incremental 014 ROM/ELF/map files are byte-identical. Static ROM use grows by 85,248 bytes to 29,939,076; EWRAM/IWRAM allocations are unchanged. Runtime peaks remain unmeasured.

## Open limits and next approval

This is a town-and-house travel prototype. It does not include independent Johto badges, story, trainers, rewards, routes, a production travel unlock or campaign completeness. World-map/Fly presentation and future Johto capture-location metadata are unqualified. Full day/night/RTC behavior, browser B2, campaigns/postgame, old-save migration and runtime memory peaks are NOT RUN. Source/asset publication rights remain unresolved; see [rights notes](sources-and-rights.md).

Before independent Johto progression, the next bounded decision is the save foundation: approve an exact protected, versioned regional-state allocation, reserve, supported-input policy and recovery/partial-save design. The B1 extension budget is a proposal, not an implemented or approved format. Roamer and other fidelity repairs retain their separate scopes. After those decisions, approve one contiguous Johto story segment rather than a full campaign import. [Next-step requirements](../NEXT_STEPS_REQUIREMENTS.md) retain those gates.

B continues to own saves, campaign behavior, time/palette systems, engine budgets and final integration; C owns its isolated art inventory/packages/replacements and validation. Workstream A, networking, NAS, dependencies and services remain untouched. No B3, save-layout change, further content merge or remote write proceeds until explicit owner approval.

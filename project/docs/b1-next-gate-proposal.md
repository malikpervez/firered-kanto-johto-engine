# B1 next-gate proposal

**Proposal only.** The owner stopped extended browser testing after partial FireRed execution. No implementation has begun. The concrete next approval is [the two-map B2 development travel slice](b2-development-slice-requirements.md), with existing saves and no new regional progression. Full campaigns, complete browser interoperability and crowded-map behavior remain unqualified. The wider alternatives below remain design references.

## Decisions before implementation

| Decision | Concrete alternatives and consequence | Audit recommendation |
|---|---|---|
| Browser runtime | Use A's existing read-only contract if available; otherwise accept the inspected third-party mGBA WASM core for B's isolated compatibility test. | Coordinate a candidate before executing the browser gate; do not change A or create a production wrapper. |
| Supported input saves | Fresh development saves only; a converter for exact 010 experimental saves; or converters for named older formats after separate identification. | Fresh development saves first. Do not promise retail, upstream HnS, personal or unidentified saves. Preserve 010 evidence without overwriting it. |
| Johto entry | After Kanto Champion plus a specified Sevii milestone preserves the requested campaign order; Champion-only is simpler but changes Sevii ordering; earlier travel changes progression substantially. | For eventual production, name the required Kanto/Sevii endpoint. B2 uses visibly labelled development travel and chooses no production unlock. |
| Starter policy | Carry the original trainer/party with no second grant; add an optional one-time Johto regional gift with its own claimed flag; force a regional party reset, requiring broader product/save rules. | Carry the same trainer and party for the small prototype; decide a second starter separately. No automatic rerun of a New Game routine. |
| Regional field permissions | Separate regional badge permissions; shared permanent permission after first unlock; or explicit travel-time restrictions. | Track regional badges and field permissions independently while keeping trainer identity and owned Pokémon global. Audit each field script rather than copying badge checks. |
| Levels and party rules | No extra caps; configurable regional caps with obedience rules; or forced local party/storage restrictions. | Keep the audit neutral: additional restrictions need explicit product selection and persistence budget. |
| Travel | A minimal labelled development link; later two-way production port/transport with separate unlocks and valid return points. | Prototype only the agreed safe endpoints; do not import all HnS transport scripts or their Kanto reset behavior. |
| Fidelity gaps | Restore required original systems under a separate scope, or explicitly accept named differences for evaluation/prototype only. | No original feature is silently made optional. Decide Fame Checker, Teachy TV, Quest Log, modern mechanics/UI and roamer scope before a release plan. |
| Save design and reserve | Existing audited flags for suitable small states; a validated/versioned extension; or larger redistribution/serialization after a separate design. | Review the save audit's numerical proposal and integrity requirements before approving any implementation. |

## State ownership proposed for a combined game

This describes the requested product, not a new native format. Every category needs a field/caller mapping before implementation.

| State | Proposed ownership | Required integration rule |
|---|---|---|
| Trainer identity, rival identity, settings, Pokédex, owned Pokémon, party/storage | One global trainer record, with any named regional rival handled explicitly | Do not reinitialize when entering Johto. A differing HnS rival identity needs an owner choice. |
| Inventory, money and shared item ownership | Global unless a named story item explicitly needs regional state | Audit reward/currency assumptions and prevent repeated gifts. |
| Badges, campaign flags/variables, League/Champion milestones | Independent regional progression | Map overlapping numeric IDs; no bulk reset on region entry. |
| Current location, return point and travel access | Global active region/location plus regional unlocked destinations | Validate IDs and fallback points against actual compiled selections. |
| Field permissions, regional events and one-time starters/gifts | Regional policy and persistent ownership | Separate region checks and idempotent claims; no new flags invented during this audit. |
| RTC and day/night palette scheduling | Shared B runtime policy | C supplies compatible art variants; C does not change clock policy or save layout. |
| C replacement art | Isolated C package | B reviews dependency/budget changes and performs any separately approved final integration. |

## Work estimate by bounded task

Effort is relative engineering scope, not a calendar promise. Implementation and validation are separate work. Browser results, rights questions and actual content conversion can change these estimates.

| Task | Adaptation estimate | Validation needed / completion evidence | Gate |
|---|---|---|---|
| Isolated browser compatibility harness | Small–moderate once runtime is coordinated | Exact runtime/ROM hashes; input/audio/focus/RTC/speed; two restarts; native/browser/native copies | Complete pending B1 browser gate |
| Save format design and reserve selection | Moderate; integrity/recovery findings prevent treating spare bytes as ready | Field/caller inventory, exact byte budget, ARM alignment, every save path, version/recovery policy | Owner design review |
| Approved save implementation | High with fault/recovery validation; migration adds scope | Actual ARM offsets and RAM deltas; normal saves, partial writes, corruption/recovery and named conversion cases | Separate implementation approval |
| Two-region ID/script adaptation for a tiny slice | Moderate for New Bark plus one interior/NPC; full Johto is high | Collision map for flags/variables/trainers/encounters/maps; no existing-state reset | B2 scope approval |
| B2 map generation/travel | Moderate after state and ID decisions | Natural FireRed opening, safe travel/return, ten round trips, cold saves in both regions, retained Kanto/Sevii selection | B2 approval |
| Original-system restoration | Separate investigations per feature; interface/script dependencies can make this high | Named item/UI/campaign acceptance, native save/progression regression | Separate fidelity repair approval |
| FireRed roamer fidelity repair | Moderate source adaptation plus high postgame test cost | Starter-dependent beast, region routes, persistent HP/status, ordinary save/reload | Separate roamer approval |
| C initial asset inventory | C-owned, separable from B implementation | Frozen manifest binding, source/runtime selection, formats, dependencies, rights notes | Frozen handoff ready for inventory |
| C replacement integration | Per-package estimate after resource/dependency review | Changed asset hashes, converter output, render and affected campaign checks | Separate integration approval |
| Crowded-map support | High engine work; current active object limit is 16 | 25 trainers plus NPC/effect/follower resource design and measured runtime behavior | Later engine/platform gate, no multiplayer implementation now |

## Proposed B2 slice and stop conditions

If later approved, retain the natural FireRed opening and compiled Kanto/Sevii content, add New Bark Town and one necessary interior with a harmless native NPC interaction, and use explicitly labelled development travel. The same trainer and owned party persist. This slice does not grant Johto campaign rewards, initialize the entire HnS campaign or decide production unlock rules.

Before import, agree the exact maps, variable/flag mapping, save design needed, budget delta and travel endpoints. Validate compiled map/layout selection, specials/callbacks, control locks and legitimate return behavior. Preserve old baseline and compare affected C dependencies; do not restart unrelated art or unchanged tests.

Stop for review if the slice requires broader engine restructuring, required-feature removal, a larger save allocation, engine replacement or an unapproved asset/right change. The current 16-object limit and four-byte main-save margin are evidence-backed constraints, not authorization to raise constants or remove content.

**Current recommendation: approve the bounded B2 development slice with the documented B1 browser gaps explicitly accepted for evaluation.** Browser candidate coordination was resolved and further tests were stopped by the owner. Implementation remains unstarted pending this concrete approval. Separate save-format, fidelity-repair and regional-story gates remain; C can continue unchanged inventory against the frozen 010 handoff.

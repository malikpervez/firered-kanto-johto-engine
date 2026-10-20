# Rainbow / Quiet Stranger / Black Tide state registry

**Current review binding: candidate30f.** The allocation below is unchanged across the frozen story candidates. Artifact-specific native results, including ordinary save/cold cycles, are in the [implementation report](rainbow-story-implementation-results.md). Historical source-verification statements below do not erase those later observations. No native save layout, protected reserve, schema or content identifier was expanded.

October15,2026. This registers the locally authorized story additions against candidate30a, using qualified candidate29 as the preserved baseline. Implementation is additive to native FireRed save6 / FRJS schema1 / content3 / layout1. It establishes no player-release or arbitrary-save compatibility policy.

The [30a manifest](../_local/artifacts/johto-full-30a-firered/manifest.json) binds upstream`167aa6d537b109bb229c231ddce4616974c4da71`, the complete799-file source freeze and patch, actual FireRed configuration, make0/wrapper0 and ROM SHA-256`a6f12fbc444cc4dfb77a5a3c25a76f4f244b0cdbdeb7775f02e2d4b91d667152`. Compilation is executed; native story/save/battle checks remain pending in this registry and belong in the separate runtime report.

The later [30c manifest](../_local/artifacts/johto-full-30c-firered/manifest.json) retains this exact state allocation and physical format. Its ROM SHA-256 is`9b6f58c5f3b16626b750209e4d9cb4e895cb035815b0a8ee12e7f9139f034815`; the800-input source freeze has SHA-256`80a9b04816b5f971f4310c87bbbf8a4642fc908829ed55f2b2d0a1edaba14c3c`. Actual make0/wrapper0 links33,548,996 ROM bytes with5,436 free; EWRAM/IWRAM remain unchanged. A pure read-only readiness helper supports the repaired field-return palette hook and adds no state. The [implementation/runtime record](rainbow-story-implementation-results.md) preserves separate artifact-bound observations and remaining native cases. The historical30a binding above is not replaced.

The final compiled [30e manifest](../_local/artifacts/johto-full-30e-firered/manifest.json) preserves the same30 native meanings and physical save format. Its ROM SHA-256 is`9c8bc6d14dde7c3db64d7c84903ac3a938c5852766f051af88b52f802425c211`; the800-input source freeze SHA-256 is`1397777dce2c4dfa2a72eb3aeee0262bd0f8a64820717aa63aa636f98f63e530`, and cumulative patch SHA-256 is`8a0a2c6899c2cb239cc01a06a22d33e2616c84f7bc684d91373174834ddbd10f`. Actual build08 make0/wrapper0 links33,549,012 ROM bytes with5,420 free; EWRAM255,016/IWRAM25,948 and all save sizes remain unchanged. The configuration fingerprint remains`86edb23f2288f65c2e7eb853827ee16fd51b1985a9c03e04e00205624ccd7352`, identical to qualified29.30d adds only the bounded Mewtwo single-actor presentation repair;30e changes only the Whirl post-battle field-recolor timing and generated packet. The [final source/static binding check](../_local/evidence/rainbow-story-01/state-audit-01/final30e-01/binding-results.json) found no source drift and retains the actual build/packet/freeze references. Native30e qualification remains pending in the runtime record; historical30a/30c bindings remain frozen.

The later [30f manifest](../_local/artifacts/johto-full-30f-firered/manifest.json) also preserves all30 native meanings, adoption rules, content identifiers and physical save sizes. ROM SHA-256 is`7cb09228e5b089c06ea33d6dbac116c501d3c17cf08e6da60536fe45bb3fc3d0`; the800-input source freeze SHA-256 is`b366ad1f8b01e24d2685731e7b763c7dfd13ce7eb39d2b24ab3a7080ec595dcf`, and cumulative patch SHA-256 is`c536750104e4647f95ccfcb4f8cb8eac792427d4a63887551fd7c3b1fef1c683`. Actual build09 make0/wrapper0 links33,549,316 ROM bytes with5,116 free, EWRAM255,016 and IWRAM25,948. Configuration fingerprint is unchanged. Compared with30e, exactly three files add/refactor the bounded FireRed-only Whirl actor-spawn presentation hook: `include/rainbow_visuals.h`, `src/event_object_movement.c` and `src/rainbow_visuals.c`. It reads existing eligibility/outcome facts and applies transient palettes; it does not adopt, allocate persistent IDs, create receipts or change script scratch/save data. The [30f binding/static audit](../_local/evidence/rainbow-story-01/state-audit-01/final30f-01/binding-results.json) found no source drift. Native30f acceptance remains pending in the separate runtime report. These later receipts do not rewrite historical artifact/test bindings.

## Existing storage, new native meanings

Thirty previously unused native flags,`0x900..0x91D`, receive explicit meanings below. They occupy four already allocated SaveBlock1 bytes,6828..6831; they do not add four bytes to the save. The source audit found no nonzero FireRed flag alias, constant flag operand or selected generated actor flag using this range. These IDs are independent of the explicit imported Johto namespace`0x2000..0x2FFF`.

| Flag | Constant / registered meaning |
| --- | --- |
| `0x900` | `FLAG_RB_OPENING_SEEN` — completed opening flyby |
| `0x901` | `FLAG_RB_NAO_INTRODUCED` — introduction actually completed |
| `0x902` | `FLAG_RB_FUJI_SCENE_SEEN` |
| `0x903` | `FLAG_RB_NOTEBOOK_SCENE_SEEN` |
| `0x904` | `FLAG_RB_ECRUTEAK_TRUTH_SEEN` |
| `0x905` | `FLAG_RB_RECORDING_STOPPED` |
| `0x906` | `FLAG_RB_WELCOME_SEEN` |
| `0x907` | `FLAG_RB_LETTER_READ` |
| `0x908` | `FLAG_RB_EPILOGUE_SEEN` |
| `0x909..0x90F` | `FLAG_MW01_SEEN..FLAG_MW07_SEEN`, respectively; MW06 is the Cinnabar reveal |
| `0x910` | `FLAG_MW09_SEEN` — neutral later cave reflection |
| `0x911` | `FLAG_LG_ATTACK_SEEN` — actual attack scene complete |
| `0x912 / 0x913` | `FLAG_LG_ARTICUNO_DEFEATED / CAUGHT` — replica outcome, separate from original Articuno |
| `0x914 / 0x915` | `FLAG_LG_ZAPDOS_DEFEATED / CAUGHT` — replica outcome, separate from original Zapdos |
| `0x916 / 0x917` | `FLAG_LG_MOLTRES_DEFEATED / CAUGHT` — replica outcome, separate from original Moltres |
| `0x918` | `FLAG_LG_LINKS_OFF_SEEN` |
| `0x919` | `FLAG_LG_FINAL_RESOLVED` — crisis closure after actual final success |
| `0x91A` | `FLAG_LG_LEGACY_EXEMPT` — explicit retrospective exception, never interpreted as played battles |
| `0x91B` | `FLAG_RAINBOW_STORY_ADOPTED` — known story allocation accepted |
| `0x91C` | `FLAG_RB_FRESH_COHORT` — initialized by this implementation's New Game; enables opening eligibility |
| `0x91D` | `FLAG_LG_LEGACY_CLASSIFIED` — old Whirl state classified once, before future progression |
| `0x91E..0x91F` | Unallocated; remain zero |

Each replica's two-bit value is0 unresolved,1 defeated,2 caught;3 is invalid. All three valid nonzero results are required regardless of order. Only actual native player victory`B_OUTCOME_WON=1` or successful capture`B_OUTCOME_CAUGHT=7` creates the corresponding receipt. Loss, fleeing, teleport, interrupted/unknown results and repeat attempts do not create a new success. Original encounter flags, species ownership, traded Pokémon and Pokédex bits do not satisfy these objectives. Caught individuals remain owned by the normal party/PC delivery path.

The map's temporary hide flags are derived presentation, not objectives. They clear/recompute on map transition. No durable outcome is inferred from a hidden actor, a scene-local variable, the native Lugia branch-suppression value, or a restored palette. No automatic save is added by this allocation.

## Physical format and ownership remain fixed

Actual ARM evidence remains SaveBlock1=15,868 bytes, SaveBlock2=3,892 and SaveBlock3=1,332. Native flags remain at6540 with304 bytes; variables remain at6844 with512 bytes. The main capacity assertion is15,868/15,872: four bytes of headroom remain. The protected256-byte stored reserve, original prefix, regional containers, metadata and existing serializer/coherent-bank/checksum/digest ownership are unchanged. No spare regional variable, padding, protected reserve or new species slot is borrowed.

Kanto scenes can write these native flags before Johto initialization. They neither seed Johto nor occupy its required blank pre-initialization body. `JohtoCampaign_Initialize` writes its existing extension/mapped state without resetting native story receipts. Persistent setters use the native Flag API and existing save coordinator. A completed scene survives only after the player performs a normal Save; reloading an earlier unsaved moment may replay it normally.

This is an additive native-flag registration within the current content3 implementation. Existing content1/2 handling and the same three hash-allowlisted offline version5 conversions are unchanged. No new personal, retail, LeafGreen, HnS or arbitrary development save conversion is authorized or implemented. Older ROMs cannot reject these future native meanings, so distinct ROM/save folders and immutable originals remain required.

## Existing trainer adoption

New Game clears native event state through its original initialization and then sets ADOPTED/FRESH/CLASSIFIED. It records no completed story scene. The opening still needs its original starter/rival completion, an existing party and the safe Route1 hook. Ordinary returning trainers never acquire a false opening memory from empty bits.

A supported older native6 save with the known allocation entirely zero is adopted at a safe story hook. It gains ADOPTED and CLASSIFIED while FRESH remains false; optional scenes use their honest catch-up alternatives. Occupied unmarked allocations, unknown reserved bits or impossible replica pairs are declined without erasing/relabeling them and require review. Unknown save versions remain subject to the existing rejection policy.

Whirl history is classified once during adoption:

| Existing evidence | Policy |
| --- | --- |
| Johto not initialized | No previous Whirl encounter exists; no exception or early seeding |
| Native Whirl caught-Lugia receipt | Retrospective exception; preserve the actual caught Pokémon and original encounter state |
| Silver selection1, theater>=8 and Lugia state3/4 | Reliable old story resolution: retrospective exception |
| Gold selection2 and Lugia state3 alone | Native suppression is not an encounter; no exception inferred |
| Legacy Gold selection2 and Lugia state4 | Old defeat cannot be distinguished reliably; conservatively exempt without claiming a previous meeting or played new objectives |

The exception never fabricates replica outcomes, final victory/capture, rewards or a missing Pokémon. Classification runs before future progression, so later legitimate Gold access does not newly become exempt. After the new crisis actually resolves, its durable final flag prevents Hall-of-Fame encounter resets from restarting it. Separate Navel Rock state is not merged into Whirl history.

## Evidence and test limits

Private [state audit and report](../_local/evidence/rainbow-story-01/state-audit-01/REPORT.md) bind the source-wide flag scan, actual ARM layout probe and helper compilation. The new state helper's ARM object has896 bytes of text and no data/BSS. [Host C tests](../_local/evidence/rainbow-story-01/state-audit-01/state-helper-test-results.json) exercise all six replica orders, all win/capture mixtures, unsuccessful outcomes, repeat guards, adoption and byte preservation with explicit engine API stubs. They do not execute emulator battles or normal-save/cold cycles.

The [source predicate checks](../_local/evidence/rainbow-story-01/state-audit-01/source-gate-test-results.json) and [prefix/text checks](../_local/evidence/rainbow-story-01/state-audit-01/story-static-results.json) cover the recorded source snapshot only. Diagnostic checkpoint manifests explicitly identify staged flags/variables; a staged success receipt is not an executed battle result. The final runtime report must bind actual triggers, both branches, outcomes, presentation and ordinary Save/full quit/fresh Continue to their exact ROM and saves.

Candidate30a links33,548,468 ROM bytes with5,964 free; EWRAM255,016 and IWRAM25,948 are unchanged from29. These are linked totals, not proof of dynamic actor/palette peaks or complete campaign coverage. Native story tests, remaining asset work and untested cases are reported separately. The four-byte save margin, roamer fidelity, HOF atomicity, inherited graphics-span and release/full-campaign limits remain open.

## B-to-C coordination

Current source/build handoff: [frozen candidate30f notice](../_local/evidence/rainbow-story-01/b-to-c-candidate30f-local-notice-01/notice.json), with an additive [qualification receipt index](../_local/evidence/rainbow-story-01/b-to-c-candidate30f-local-notice-01/qualification-addendum.json). The notice's original pending status is historical; later native results do not change its source, configuration, asset providers or dependency scope. The [runtime report](rainbow-story-implementation-results.md) distinguishes executed passes from remaining cases. No other workstream or user task was messaged.

The [private local candidate30a notice](../_local/evidence/rainbow-story-01/b-to-c-candidate30a-local-notice-01/notice.json) freezes the complete patch, configuration, fingerprints and available manifests for this story baseline. It scopes C rebinding to the new actors, reused Ho-Oh/Mew/Mewtwo resources, corrupted bird/Lugia palettes and Lugia wing-band presentation assumptions. It does not restart unrelated C inventory/replacement work or unchanged tests. B retains saves, campaign behavior, time/palettes, budgets and final integration; C retains its isolated art packages and validation. No C workspace or task was modified or messaged.

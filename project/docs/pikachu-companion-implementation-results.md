# Permanent Pikachu companion — local implementation

October 18, 2026. The owner authorized a Yellow-style interactive Pikachu companion independent of party membership. The isolated **36O** candidate preserves frozen 36M and pre-fix 36N. No actual Pokémon is created, replaced, renamed, removed or locked in the party.

## Behavior

After the existing first-Pokémon milestone, Pikachu becomes the default FireRed walking companion, including for supported older trainers. Boxing, trading, releasing, fainting or evolving a battle Pokémon does not change this visible companion. Interaction uses Pikachu's cry and one of three brief authored reactions. It reads no party nickname, HP, status or friendship.

Pikachu uses the existing follower slot and native artwork. Scripted hides, NPC escorts, Surf/bike and geometry safety rules remain. The companion returns through the native follower lifecycle when safe. It is not an additional battle Pokémon, field-move user or portal/transport service. Existing party fishing and first-slot evolution rules remain unchanged.

The Options row is fixed to `PIKACHU`. The old follower-OFF bit is retained; it does not disable the permanent companion. The misleading first-party-member follower toggle is omitted. There is no new setting, save flag, variable or reserve allocation. The existing native `FLAG_SYS_POKEMON_GET` compiles to **0x828** in the actual FireRed configuration.

## Exact local identity

| Item | Value |
| --- | --- |
| Candidate | `johto-full-36o` |
| ROM SHA-256 | `db1f78b99d386b9cbbc69493d18c6c3ee14d210ad91ed4ed8607c1c4419c6042` |
| CRC32 | `16ae6f08` |
| Source fingerprint | `52836389b462537127da7c899066b28463afc2c2afc58a9fbbcdcacba29e6e09` |
| ROM path | [_local/artifacts/johto-full-36o-firered/pokefirered.gba](../_local/artifacts/johto-full-36o-firered/pokefirered.gba) |
| Build manifest | [36O build manifest](../_local/artifacts/johto-full-36o-firered/manifest.json) |
| Complete source/patch | [36O source freeze](../_local/evidence/pikachu-companion-01/source-freeze-36o-01/manifest.json) |

Both actual make and wrapper exit 0. The recorded build uses the pinned ARM toolchain, FireRed target, `-j2`, `O_LEVEL=s`, `RELEASE=0`, `LTO=0`; stdout, stderr, effective configuration and artifact hashes are retained. Compilation is separate from the native evidence below.

36N implements seven source-file changes from 36M. Its blank fixed-option value was found in native rendering and remains a recorded defect in that candidate. 36O adds only a FireRed one-choice rendering case inside `OptionMenu_ItemPrintFunc`. The [36,861-path dependency comparison](../_local/evidence/pikachu-companion-01/host-tests/options-render-fix/36n-to36o-source-reuse.json) proves all other source inputs unchanged. Reused 36N tests and images retain their original build labels.

## Resource and save impact

| Measurement | 36M | 36O |
| --- | ---: | ---: |
| ROM size | 33,554,432 | 33,554,432 |
| ROM headroom | 857,244 | 856,876 |
| EWRAM headroom | 7,100 | 7,100 |
| IWRAM headroom | 6,848 | 6,848 |

The change consumes **368 ROM bytes**. All 397 actual ARM/save-layout facts and 40 artwork/provenance pins match. The 256-byte protected reserve and existing native6/FRJS1/content3/layout1 format are unchanged. Both complete source patches apply to the pristine pinned upstream; all earlier source/build/evidence remains preserved. The four-byte main-save margin and original roamer-fidelity limitation remain open.

## Validation scope

Actual 36N checks cover an older trainer with Lugia/Bulbasaur/Lapras and no party Pikachu; movement, the Happy interaction, ordinary Save, full emulator quit and fresh Continue executed. All collection, items, Pokédex, names, settings and campaign state persisted. The strict cold comparison retains one regional mismatch: a separate exact source-qualified check proves all four changed bytes are the existing native two-dog history shift, with every other extension byte equal.

Actual 36N also covers a genuinely caught Pikachu staged into Box1/slot0 while five other owned Pokémon remain in the party. The original follower option was already OFF. Indoor movement, Ready interaction, Options visit and native Save executed; the exact encrypted boxed Pokémon, party, storage and old option bit were preserved. 36O loads a byte-for-byte copy of that completed native save.

**36O focused native closeout PASSED — executed.** Actual Options images show `FOLLOWER PIKACHU`; visiting Options retains the old OFF bit and the complete original options structure. The boxed Pikachu stays intact, and the walking companion appears outside the Center after its native map transition. Happy and Curious interaction text was captured on 36O; the unchanged Ready outcome retains its original 36N capture label.

36O's own ordinary Save advanced generation 4→5. After fully quitting mGBA, a new process loaded that exact save and continued into Pewter with Pikachu visible. All 25 compared preservation domains matched before Save, settled memory, the disk save and fresh Continue without exceptions. This includes all five party Pokémon, complete PC storage and boxed Pikachu, names, Pokédex, inventory, native options, flags/variables, regional state and protected reserve. The [strict cold-reload comparison](../_local/evidence/pikachu-companion-01/native-execution-36o-01/offline-save11-cold12-preservation-01.json) and [direct settled-to-cold comparison](../_local/evidence/pikachu-companion-01/native-execution-36o-01/offline-save11-settled-to-cold12-direct-01.json) retain the evidence. This is a disclosed staged fixture, not a natural campaign playthrough. The [owner review](../_local/evidence/pikachu-companion-01/owner-review-36o/REVIEW.md) binds exact scripts, dialogue, outcomes and current native images. mGBA is fully closed.

Focused code checks separately pass: 162 actual-C ASan/UBSan policy assertions, 17 preservation checks and the corrected Options callback fixture. Other-target ARM comparisons preserve the original LeafGreen/HnS/Emerald machine-code sections; complete objects differ only in narrowly accounted diagnostic source-line strings. Their follower scripts preprocess identically. No whole other-target build or playthrough is claimed.

Fresh opening/rival battles, active Surf/bike/NPC escort, actual battle/field-move return, cross-region traversal on this new candidate, Delta/iPhone and full campaigns remain **NOT RUN** in this pass. Source checks and prior-build evidence do not become new native passes. Audio listening is not separately qualified here.

## Reproduction and review

Use the frozen 36O complete patch and pinned source/configuration in its manifest. The private [build wrapper](../_local/evidence/pikachu-companion-01/build-36o.py) records the exact incremental build from preserved 36N. Run it only in a separately prepared isolated source tree with a fresh attempt directory; no new clean rebuild is claimed.

The [offline HTML review room](../_local/owner-review/index.html) is the owner-facing presentation. Its PC01 review includes exact script labels, dialogue order, all random outcomes, original build labels and actual native screenshots. All fixtures are isolated B-owned diagnostics, with staged conditions disclosed. Personal saves and other workstreams are untouched; no commit, push, publication, services or networking changes occurred.

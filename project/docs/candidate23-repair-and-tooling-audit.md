# Candidate23 repair and tooling audit

Current decision: **GO for bounded local fresh-game evaluation of repaired candidate25b; HOLD for player release and whole-campaign completion.** The reported Lab blockers are repaired and verified. Candidate23's earlier completion/GO remains withdrawn. The owner authorized this session to handle the review and repairs and explicitly released mGBA for isolated testing. Workstream A is untouched.

## Findings and exact repairs

| Finding | Evidence and repair | Status |
| --- | --- | --- |
| Oak's Lab replaced furniture and its exit with blank tiles | The conversion selected HnS's surrounding void as floor and misread the native attribute format.27 cells were redirected through14 blank seam records. The exit lost `MB_SOUTH_ARROW_WARP` (`0x65`). Bind the existing historical native `u32` Lab provider, remove the erroneous overrides/seam records and the incorrect special reader. Native floor pixels already match HnS's true floor. | PASS — EXECUTED fresh opening/rival victory/exit on clean24; final25b cold entry/save/reload/exit; independent native-reference data checks |
| Same malformed Lab provider used by a Sevii interior | The actual compiled-header census found Three Island House1 also using the provider in FRLG format. A FireRed-only layout overlay selects the same native provider. Geometry, events, scripts and warp identity are retained. Sinjoh's HnS-format consumer is unchanged. | Host/actual linked checks executed; native Three Island visit NOT RUN |
| Celadon House1 entrance was placed on a window | The relocated original House1 warp at40,29 lay on a solid normal tile. No city/house script unlocks it. Replace exactly that selected geometry word with the authentic existing HnS apartment door, preserving all events, IDs, destinations and scripts. | Eight real mapjson calls and two independent actual-ROM checks executed; native Celadon visit NOT RUN |
| Johto daily flags never reset on date rollover | Native daily reset omitted the11 imported regional daily flags. Clear exactly their existing range when Johto has been initialized. Existing native range, peer targets and saved layout remain unchanged. | Source/body checks and actual ARM compilation executed; date-rollover gameplay NOT RUN |
| Native script-variable writes omitted save-transaction notification |12 existing direct script writers already called a hook, but it notified only regional variables. Extend the hook to the actual native variable range, preserving effect-analysis behavior. No ordinary concurrent gameplay corruption was reproduced. | Exhaustive bounded hook checks and actual ARM compilation executed; broader persistent-writer review remains open |
| Missing map-generation prerequisites | The generator consumed registry/tool/raw geometry inputs absent from Make dependencies. Add those dependencies without changing output semantics or positional generator arguments. This was a maintenance defect; current candidate23 Lab output was reproduced exactly, so stale generation was not its cause. |72 bounded dependency cases, clean24 build and isolated incremental25b build executed |
| Completion/rendering claims exceeded evidence | Earlier native testing stopped after starter selection and save/reload, before rival battle and exit. Existing screenshots already showed missing patches. Same-recipe generated-byte equality proved transmission, not correct artwork or behavior. | Previous completion GO withdrawn; focused fresh opening/win/exit and two normal-save/full-quit/cold cycles now executed. Whole campaign remains unverified. |

The reviewed candidate24 delta is seven files. The other765 paths in the772-file candidate23 source inventory are unchanged. The complete candidate24 patch is frozen against upstream `167aa6d537b109bb229c231ddce4616974c4da71`; the exact source manifest is `_local/evidence/johto-campaign-direction-01/final-packaging/final-source-24/manifest.json`, SHA-256 `83e6764574b70b8400e0a298e900900ae4515ea7300c15580e0e689d65aea754`.

Candidate25 adds only `data/maps/CeladonCity_Frlg/map.json` to that delta. Its complete source manifest is `_local/evidence/johto-campaign-direction-01/final-packaging/final-source-25/manifest.json`, SHA-256 `51f77cc5428b397aff9bccdbfcee62b216c33f41bcb7dd0f586d08c35819b601`. Static triage scanned786 warp events across191 selected maps; Oak and Celadon were the two introduced ordinary-portal mismatches. Sixteen unchanged native landing/closed-door roles remain source-classified, without a new gameplay pass.

Final source fingerprint: `d1f893af424e96735530da5f19df7d1b00973b812ecb672784561d459fbb5546`. Complete18,948,746-byte patch SHA-256: `4074758e273fc330633720d91b7187cae6d4c572e9281936018958e04b693e2b`. Configuration-files fingerprint: `86edb23f2288f65c2e7eb853827ee16fd51b1985a9c03e04e00205624ccd7352`; combined patch/config fingerprint: `ad71ad69b883fa5c1d9e49d3ed72cb887383b506b136453f22a35d492589725a`.

Executed on Darwin27.0.0/arm64 with the B-local pinned GNU ARM14.2.1/APCS toolchain and official mGBA0.10.5. Effective target is FIRERED/firered, TEST0/DEBUG0/RELEASE0/LTO0; the fresh native opening is FireRed's Pallet campaign. Existing save6/FRJS1/content3/layout1, native sectors/checksums/capacity assertions, four-byte main margin and256-byte reserve are unchanged. HnS/LeafGreen/Emerald preprocessing/generated peers and targeted C compiles were checked; their native games were not replayed during this repair.

## What the broader review establishes

Three parallel reviews covered map/graphics semantics, save/campaign behavior, and build/provenance/tooling. All772 source fingerprints were independently checked against the compiled candidate23 tree. All254 literal aliases were independently refreshed against actual ELF/ROM addresses and byte spans. An independent native-reference comparison checked89 same-dimension native-base maps /46,692 cells; Oak's Lab was the only attribute mismatch. These are bounded source/artifact checks, not complete gameplay qualification or a semantic review of every changed line.

Pinned Make, GNU ARM, the project's map/script compilers and normal mGBA controls were appropriate tools. The failure was in the custom map conversion and its oracle: checking generated bytes against the same recipe could validate an incorrect recipe. Poryscript was optional and its absence did not cause the map defect. A correctly configured, fork-compatible Porymap workflow could help visual review, but must understand the custom overlays and mixed per-layout formats before round-trip editing. Do not open and resave the authoritative tree with stock settings blindly. The old majority-floor/schema-inference preparation is retained only as historical evidence and must not be reused to regenerate this repair; the frozen complete patch is the reproducible source authority.

Exact sharing, target separation and source provenance should be retained. They do not need a wholesale engine replacement. Existing out-of-array door/actor/follower reads, the four-byte native-save margin, roamer fidelity, Hall of Fame atomicity and tightly modeled graphics budgets remain open. This repair does not establish campaign completeness, release readiness or general save compatibility.

**Candidate23 Lab-save limitation:** the normal saved map-view cache physically contains removed virtual Lab tile IDs. Read-only inspection of our candidate23 test save found22 such cached words. Keeping save version6/layout1 does not make those cached Lab views correct under the repaired ROM. Do not replace the ROM beside an existing candidate23 save or describe that as a supported migration. Use the separate fresh-game folder; preserve the owner's old save. The fresh24→25 test has unchanged Lab data and is a separate, explicitly identified copy test.

## Reproduction and verification

Candidate23 ROM SHA-256: `1e5b64314695d07d5eca03c455fba61f0ba63ea3d50145fe709ca7eb71afe4e6`. Root's isolated reproduction is `_local/evidence/candidate23-independent-review/native23-reproduction-01/`; it uses a copy of our pre-rival test save. The owner's save is preserved and is not loaded or modified by these tests.

Candidate23 reproduction **FAIL — EXECUTED**: won the rival battle, returned to unlocked field control with scene4 and the rival-defeated flag, then ordinary movement stopped atLab69,3/6,12 without the Pallet warp. Missing artwork is visible. Evidence `_local/evidence/candidate23-independent-review/native23-reproduction-01/results.json`, SHA-256 `26ebdeb20e566dc4b794b1bfd258fb9363c478dd274b475b0f12d92484a4db1f`.

Candidate24 clean build **PASS — EXECUTED**, make/wrapper exit0. ROM SHA-256 `ebd44f9cfe68c6c01138993455a6c6eb9c3475d9fe0cf8b23c88f4027541e487`;27,916 ROM bytes free. All37 actual ARM fields,254 aliases,27 recorded backing spans and RAM sizes are unchanged. Independent actual-ROM checks found zero native attribute mismatches across89 native-base maps /46,692 cells. All281 Lab/ThreeIsland grid cells, graphic words and native attributes match the historical reference. The center Lab exit is now `0x65`/SouthArrowWarp. These are build/linked-data results, not native gameplay results.

Fresh native regression **PASS — EXECUTED** within the following exact scope. No cheats, RAM writes, warps or emulator save states were used.

| Actual ROM / check | Result and evidence |
| --- | --- |
| Clean24 fresh opening | New Game with absent save; trainer RED/rival GARY entered through normal UI; bedroom→Pallet→Oak→Lab→Bulbasaur. Furniture/floor/mat visible. |
| Clean24 rival and exit | Normal Bulbasaur/Charmander battle won; level6, healed party, scene4 and defeated-rival flag. Walked through Lab6,12 to Pallet68,0/16,14. |
| Cycle1,24→25b | Normal24 Save/full quit, strict counter1 bank valid. Copied only this fresh test save into isolated final25b folder; fresh process/title/Continue preserved exact trainer/rival/party/Dex/full flags/full variables/map/layout/position. Decoded bag/money/coins and PC retained. |
| Cycle2,25b→25b | Re-entered final25b Lab without repeated rival/starter, saved normally at6,8, full quit; strict counter2 bank valid. Fresh process/Continue retained the same complete fields, correct artwork/cache and resources. Walked out into Pallet again. |
| Final shutdown | Inputs released, helpers removed, mGBA fully closed; independent process check found none. Owner23 save hash unchanged; owner25b folder still has no save and has not been launched. |

The party is one Bulbasaur at level6; caught state includes Bulbasaur, bag is empty, money3080/coins0. This verifies that actual empty inventory state and the occupied party survived; it is not an occupied-bag or all-Pokémon compatibility claim. Native load rekeys encrypted values; inventory comparison uses decoded quantities/resources, rather than expecting ciphertext to remain identical. The initial pre-Start versus post-Save flag equality check correctly found the ordinary `FLAG_OPENED_START_MENU` transition; its source owner was verified. Both cold comparisons use exact complete post-Save flags without masking unexplained changes. Initial boot-button timings and that checker correction remain preserved.

Private native results:

- `_local/evidence/candidate23-independent-review/native24-fresh-01/results.json`, SHA-256 `178191b6b373f1d8c76d4d9d35b47f72a5e6f7099fbd7deb78da696cfba428d8`.
- `_local/evidence/candidate23-independent-review/native25b-cold-01/results.json`, SHA-256 `870c47e0851209c8059ec058e0925afb83b2dbe2b41dd25e68043f1a5a227b77`.
- `_local/evidence/candidate23-independent-review/native25b-cold-02/results.json`, SHA-256 `377abdf445a30dc5fe89782d450a253a4558b04e302ceb0c42090c53df727272`.

Candidate25b build **PASS — EXECUTED**, make/wrapper exit0. This is a verified isolated incremental follow-on from the successful clean24 tree, with exactly one reviewed JSON source delta and no changed C/header/object/configuration inputs. The earlier25 attempt was blocked before building by an overly narrow wrapper path guard; its failure is preserved. The corrected wrapper admits only the exact private patch folder, uses new25b paths and keeps all source/artifact pins. ROM SHA-256 `e5771e03db8107e11ab1f48bf3c9504c47aeb0060380b2a4c8f4794b50f7e80e`; build-manifest SHA-256 `affad2d9653739a5586059726c0adaf5f523f32a4b7852814a6f899abcd434ed`.

Two independent actual-ROM comparisons confirm that25b differs from clean24 at exactly two bytes: Celadon40,29 changes word1785→1085, a supported animated door (`0x69`). Every other ROM byte is identical. The actual126-field ARM/APCS native probe is unchanged, including money, bag, key, party and Dex offsets. No clean25b repeat or native Celadon entry is claimed.

## Play and reproduce

Use the [new fresh-game launcher](<[LOCAL_WORKSPACE]/_local/saves/firered/johto-full-25b-owner-01/Play FireRed Kanto Johto.command>) and choose **New Game**. It verifies the copied ROM before opening the pinned mGBA app. The old23 folder/save is preserved; do not copy its inside-Lab save here.

Final [ROM]([LOCAL_WORKSPACE]/_local/artifacts/johto-full-25b-firered/pokefirered.gba), [ELF]([LOCAL_WORKSPACE]/_local/artifacts/johto-full-25b-firered/pokefirered.elf), [linker map]([LOCAL_WORKSPACE]/_local/artifacts/johto-full-25b-firered/pokefirered.map), [build manifest]([LOCAL_WORKSPACE]/_local/artifacts/johto-full-25b-firered/manifest.json), [complete source patch]([LOCAL_WORKSPACE]/_local/evidence/johto-campaign-direction-01/final-packaging/final-source-25/complete-source.patch), and [source manifest]([LOCAL_WORKSPACE]/_local/evidence/johto-campaign-direction-01/final-packaging/final-source-25/manifest.json) are local and ignored. Exact commands, configuration, source/tool hashes and real stdout/stderr/exit codes are in the manifests and `_local/evidence/builds/johto-full-{24,25b}-firered/`. The final wrapper command is preserved in `_local/evidence/candidate23-independent-review/build-validation-01/incremental25-prepared-01/ready25b.json`.

To reproduce from a clean tree, the complete source25 patch applies alone to the pinned upstream; the existing `build-clean.py` accepts that patch and source25 manifest with a new unused run ID. This clean25 repeat is **NOT RUN**. Executed evidence is the clean24 build plus the verified isolated one-file25b follow-on, whose only final ROM difference is the two door bytes.

## B-to-C coordination

Candidate23 remains a withdrawn historical baseline. Candidate24 changes Oak's Lab's geometry binding and removes its14 blank seam records; Three Island House1 changes its attribute-provider binding. Candidate25 changes one Celadon doorway word. C should refresh dependencies and visual assumptions for these consumers. Unchanged maps, art packages and unrelated tests do not restart. Daily reset, script-write notification and Make prerequisite changes belong to B. All frozen sources, ROMs, private evidence and saves remain local and ignored; no C repository or service is changed.

The [frozen local25b notice]([LOCAL_WORKSPACE]/_local/evidence/candidate23-independent-review/B-to-C-candidate25b-local-notice.json) includes the complete source/patch/configuration/build bindings, available clean24/follow-on25b manifests, native evidence, affected dependencies and known limits. No message was sent to C. B retains saves/campaign/runtime palette-time systems/budgets/integration; C retains isolated inventory/art packages/replacements/validation.

## Evidence ledger

- `_local/evidence/candidate23-independent-review/source24-reviewed-delta.json`: exact seven-file delta and unchanged-parent-source check.
- `_local/evidence/candidate23-independent-review/root-apply-{maps,daily,dependencies,script-guard}-01/receipt.json`: guarded before/after source copies, patch identities, real application exits.
- `_local/evidence/candidate23-independent-review/maps-tools-01/`: historical native attributes, actual compiled consumers, pixel comparisons, semantic oracle and staged repair provenance.
- `_local/evidence/candidate23-independent-review/maps-tools-01/review-findings02.md` and `coverage-ledger-final02.json`: corrected final map/tool review. The initial cache proof used a stale source comment for offset52; actual23/25b ARM probes measure mapView56/512 and mapLayoutId54. Corrected old-save count remains22; the new25b Lab checkpoint has zero obsolete IDs. Old evidence is preserved and superseded, without a game/source change.
- `_local/evidence/candidate23-independent-review/save-campaign-01/`: converters, daily reset, direct-writer review, host and ARM checks, including failed reviewer probes.
- `_local/evidence/candidate23-independent-review/build-validation-01/review.md`: severity findings, tool assessment and honest coverage ledger.

No Workstream A changes, save-layout/capacity changes, remote writes, commits, pipelines, deployments, NAS or network changes are part of this repair.

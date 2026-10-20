# Character presentation implementation results —32c partial preview

October15,2026. **Jenny’s bounded native presentation and normal-save checks pass; owner visual acceptance remains pending. Jessie’s executed32c scene subsets are scoped below; full walking and unexecuted alternatives remain NOT RUN. James artwork and the optional Jessie/James battle are not implemented. HOLD for player release.** This is a local presentation preview, separate from the preserved [31e story results]([LOCAL_WORKSPACE]/docs/character-story-implementation-results.md).

## Exact local candidate

| Binding | Frozen32c value |
|---|---|
| Build/configuration | [FireRed manifest]([LOCAL_WORKSPACE]/_local/artifacts/johto-full-32c-firered/manifest.json); upstream `167aa6d537b109bb229c231ddce4616974c4da71`, ARM GNU14.2, isolated32c source/build; make and wrapper exit0 |
| ROM | [pokefirered.gba]([LOCAL_WORKSPACE]/_local/artifacts/johto-full-32c-firered/pokefirered.gba); SHA-256 `3185fb1d0cb94ce2e23e2598ed9ac424cdff81ee5f77bb63c43ab65825716e3b`; CRC32 `1ffad473` |
| Source | [823-input freeze]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-03/source-freeze-32c/manifest.json), SHA-256 `a519483d025e41236bf3aa7642005008a3b7a890959b0b1ecc15b9d0b342146f` |
| Reconstruction fingerprint | `4c95372d4b5f3c19efc9a73b164471b0a99300d820c8a49c86b2ddd39139375a` |
| Complete local patch | [complete-source.patch]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-03/source-freeze-32c/complete-source.patch), SHA-256 `813f8d5edfd233a90d42604d18d620d9d4d3145890d258c7784bd021db8bc8ca`; upstream apply-check exit0 |
| Configuration fingerprint | `86edb23f2288f65c2e7eb853827ee16fd51b1985a9c03e04e00205624ccd7352` |
| Build log | [Preserved32c log]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-03/build-attempt-32c-01/combined.log); compilation is not gameplay acceptance |
| Review | [Current screenshots beside exact scripts/dialogue]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-03/owner-review-32c-03/REVIEW.md); [review manifest]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-03/owner-review-32c-03/manifest.json) |

## Implemented scope

Jenny uses a new native-style16×32 overworld sheet, graphics567. Jessie’s existing generated source is converted proportionally on a32×32 canvas, graphics565, replacing the previous horizontal squash. Native animation tables retain the usual standing/walking frames; a full runtime walking cycle is not yet established by this preview. Both sheets remain native uncompressed graphics. There is no new species, actor, quest flag, trainer ID, battle or save allocation.

The narrow FireRed Jessie allocation fix recognizes the16×32→32×32 shape change even when both OAM size fields are2. Explicit first-frame upload follows Jessie’s scripted reveal. The saved-object spawn hook refreshes only ready, active Vermilion local11 using the old policeman286 into Jenny567, including supported normal-save Continue reconstruction. Other objects are excluded.

Actual olderSave10 retained a completed face-down held movement; the original `faceplayer` could refuse the new direction. Only ST04 entry now uses native `lock`, existing `Common_Movement_FacePlayer` and `waitmovement0`. The native movement system clears the completed action before facing and again before finishing. Every subsequent script instruction, gift path, shared release, dialogue string and outcome remains unchanged. [40-check offline audit]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-03/st04-entry32c-audit-01/results.json), [exact linked-ROM proof]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-03/st04-entry32c-audit-01/postlink32c.json). The replacement adds nine script bytes and reuses existing movement data.

All trio dialogue, triggers, choices, receipts and campaign gates remain unchanged from31e. The [source-complete review]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-03/owner-review-32c-01/REVIEW.md) includes ST04 and JT01–04,35 exact dialogue entries including native obtained/nickname/PC outcomes, and their frozen labels/lines. The current preview adds only actual32c images; historical images retain their original labels.

## Executed evidence and pending cases

[Immutable32c ledger005]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-03/native-execution-32c-01/ledger-revisions/ledger-005.json), SHA-256 `022a6a3836d9e3a3ff173581dbe69ce4ed78299c541010aa7b30c7508871cc04`, binds 16 original PNGs personally viewed by the visual curator. Root executed native desktop mGBA through ordinary controls; the verifier and this report do not claim to have executed those GUI actions themselves.

| Case | Recorded status and limit |
|---|---|
| Jenny from actual prior normalSave10 | EXECUTED PASS: new art appears on Continue; no offline save alteration for32c. Its older staged diagnostic location/milestone history remains explicit. |
| Four facings and repeat | EXECUTED PASS: valid south/east/north/west approaches upload the expected native poses and repeat dialogue. Invalid west approach excluded. No second gift. |
| Party-menu return | EXECUTED PASS: new Jenny remains visible after the recorded menu-return sequence. |
| Normal saving/full quit/fresh Continue | EXECUTED PASS: ordinary save advances10→11, both disk banks valid, anchored full-process quit and fresh Continue.117 integrity/preservation checks pass with zero mismatches. |
| Save preservation | Exact bounded party/PC/Bag/Dex/names/native progress/regional/protected-reserve/roamer comparisons across pre-save/post-save/disk/cold; existing ST02/03/04 receipts retained, ST01 remains0. No broad compatibility claim. |
| Jenny art acceptance | PENDING owner review; technical appearance is not visual approval. |
| Full walking/new Squirtle delivery with revised art | NOT RUN. Historical31e delivery remains31e evidence. |
| JT01 | EXECUTED PARTIAL — direct Jessie placement and first dialogue page only See the exact per-case executed/NOT RUN limits in the current ledger and image review. |
| JT02 | EXECUTED PASS — bounded disguise-to-Jessie reveal, exact upload, receipt and exit See the exact per-case executed/NOT RUN limits in the current ledger and image review. |
| JT03 | EXECUTED PASS — bounded known-branch nurse-to-Jessie reveal, exact upload, receipt and exit See the exact per-case executed/NOT RUN limits in the current ledger and image review. |
| JT04 | EXECUTED PASS — bounded presentation, scene completion, receipt and exit; dialogue image coverage PARTIAL See the exact per-case executed/NOT RUN limits in the current ledger and image review. |
| James overworld art and proper duo battle portraits/battle | BLOCKED/NOT IMPLEMENTED. No ordinary substitute or constant is represented as completed content. |

The Saving-message PNG contains native “SAVING… DON’T TURN OFF THE POWER.” The after-save field PNG demonstrates returned control, not a printed Saved message. [Normal-save/cold117-check evidence]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-03/native-execution-32c-01/save-full-cold-01.json) and [full-quit receipt]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-03/jenny32c-full-quit-01/result.json) supply the separate persistence proof. Human aesthetics, other choices and full campaigns are not inferred.

## Preserved failures and asset limits

The [32a diagnostic ledger]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-03/native-execution-32a-01/ledger.json) retains its generic-officer Continue and missing-Jessie-frame failures. [32b review]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-03/owner-review-32b-01/REVIEW.md) retains the owner’s rejection of its Jenny art style and its uncompleted Save/cold scope;32c is a separate native-style revision, not retroactive acceptance. Historical32b facing observations and the completed-held-action cause remain in the [saved-object proof]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-03/st04-facing-audit-01/saved-object-proof.json).

The earlier James-art generation attempts and the later Jessie front-portrait attempt received explicit image-tool safety rejections with no output. No genuine new James asset or complete required duo-portrait set is available. No retry or bypass is used. Usable artwork sources are still needed to finish the blocked assets; the owner is not expected to personally supply artwork they do not have. The optional two-trainer Celadon challenge remains a [private reviewable draft]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-03/battle-draft-01/README.md), not integrated trainer IDs, encounters or runtime gameplay. Jenny has no battle. James’s existing offscreen/disguise role, Meowth, net narration and harbor rescue effects retain their disclosed31e presentation limits.

## Budgets and boundaries

| Resource | Actual32c value |
|---|---|
| ROM |33,549,732/33,554,432 bytes;4,700 free |
| EWRAM |255,016/262,144 bytes;7,128 free |
| IWRAM |25,948/32,768 bytes;6,820 free |
| SaveBlock1 |15,868/15,872 bytes;four-byte headroom unchanged |
| SaveBlock2/3 |3,892/1,332 bytes; protected256-byte reserve unchanged |
| New persistent state |None; no flag/var/trainer-ID allocation or save-format change |

Native version6/FRJS schema1/content3/layout1, sector/checksum/coherent-bank/digest rules, original Pokémon/inventory/regional state and the capacity assertion remain intact. Four-byte save headroom and FireRed roamer fidelity remain open. Linked totals are not measured heap/VRAM peaks; Jessie’s allocation and appearance require their separately recorded native observations.

B retains save/campaign/runtime/palette/budget/integration ownership. C’s affected dependencies are the Jenny567 and Jessie565 sheets/palettes, Jessie32×32 frame/OBJ dimensions, the guarded saved-object refresh and ST04 facing/repeat scenario; unrelated art and unchanged tests need not restart. Workstream A, personal saves, services, NAS/network, remote repositories, commits, publishing, CI and automation remain untouched.

### Current32c Jessie evidence limits

**JT01:** EXECUTED PARTIAL — direct Jessie placement and first dialogue page only

Executed: Visible565 body, exact512-byte frame2, all16 tiles and palette119D; Jessie/Meowth placement and first dialogue page.

Not run / scope limits: Completion, receipt, exit, repeat or Save/cold on32c; Native walking cycle; James canonical art or duo battle.

**JT02:** EXECUTED PASS — bounded disguise-to-Jessie reveal, exact upload, receipt and exit

Executed: Researcherdisguises withMeowth; OrdinaryYES branch; James21removedfirst; Jessie56532×32/all16tileallocation/exactnativeframe2uploaded; Actualsprite visiblebesidefullrevealtext; OnlyJT02receipt9270→1 amongobservedstoryflags; party/nativelegendary/regional/storysnapshotfields unchanged; Trio exits afterdialogue.

Not run / scope limits: JT02 normalSave/fullquit/cold on32c; Nativefullwalkingcycle; Jamescanonicalartoroptionalduobattle.

**JT03:** EXECUTED PASS — bounded known-branch nurse-to-Jessie reveal, exact upload, receipt and exit

Executed: Native nurse/disguises thenJessie565 appears; James42 leavesbeforeJessie16tileallocation; no sampledactiveoverlap; Eightread-onlysamples match actualnativeframe0/palette119D; Only9280→1 amongobservedcharacterreceipts; observedparty/nativelegendary/regional/storyfacts unchanged; Trio exits.

Not run / scope limits: JT03 firstmeetingbranch on32c; JT03 normalSave/fullquit/cold; Nativewalkingcycle; Jamescanonicalartoroptionalduobattle.

**JT04:** EXECUTED PASS — bounded presentation, scene completion, receipt and exit; dialogue image coverage PARTIAL

Executed: Jessie565 visible with exact frame2/all16 tiles/palette119D; Freed Seel first textbox captured; Parent advanced ordinary dialogue to completion; Only9290→1 among observed receipts; other observed party/native/regional/story facts unchanged; Trio49/50/51 absent afterward; native Tentacool remains.

Not run / scope limits: Later dialogue-page images after capture expired; Repeat, Save/cold, new legendary battle or full collection comparison; James canonical art or duo battle.

JT02/JT03 observed story/party/native-legendary/regional fields and their own receipts are scoped per reader. Jenny’s117-check whole-collection/save result is not inherited by Jessie. Original32a failures,32b rejected art and earlier31e campaign evidence remain unchanged. No unrelated tests were restarted.

The Jessie runs use isolated staged checkpoints. JT03’s prior-meeting known-branch prerequisite was explicitly staged, not naturally earned during this run. JT04 live palette119D differs from its linked base; its exact frame/allocation/visible-image check does not establish unmodified-base palette equality. Later JT04 pages were advanced after image capture expired and have no current screenshot.

The [post-native frozen-source/artifact integrity check]([LOCAL_WORKSPACE]/_local/evidence/story-presentation-03/final-freeze-integrity32c-01/result.json) confirms all823 implementation inputs and the exact ROM/ELF/MAP remain unchanged after the bounded native tests.

# Friends presentation repair and native execution — 36M

October 18, 2026. Current local review candidate **36M** preserves frozen 36D and every intervening build, failed attempt and private save. The owner authorized fixing Lugia overlap, livelier staging, and completing the remaining Friends event and battle tests. This is bounded desktop-mGBA qualification with explicitly staged prerequisites, not a natural campaign playthrough or a player release.

## Implementation

- Spread the seven friends into map-specific formations across the existing twenty maps. Added speaker turns, reactions and bounded story movements while retaining all 827 dialogue blocks, original choices, campaign gates, trainer teams and state allocation.
- Retain and hide the existing large follower allocation during locked scenes and menus, restoring the same follower before field control, battles and Save. This avoids the actual native graphics fragmentation found when removing and recreating Lugia. No Pokémon, collision data, follower option or save field is replaced.
- During ordinary field movement, hide only a large follower's rendered sprite when it overlaps a visible, registered Friend on the current camp map. The native object, position, graphics allocation and Pokémon remain intact. It reappears on the next clear frame. The conservative rectangle boundary can visibly pop; that remains a presentation limitation for owner review.
- Repair FG08's native warp handoff using a bounded, one-shot RAM phase and audited map callbacks. Its full sixteen dialogue blocks now continue inside Fuji's house and return to the exact outdoor origin. A direct indoor interaction completes without an unnecessary warp. The final House-only camera focus also fixes the actually observed eight-pixel clipping of Fuji's head.

The [28-file presentation inventory](../_local/evidence/friends-story-01/presentation-36m/EVENT-LOCATIONS-AND-CHANGE-INVENTORY-36M.md) links actual source files, labels and map coordinates. Native map geometry, unrelated actors/warps, art payloads, save layouts and existing campaigns are unchanged. The [complete local source freeze](../_local/evidence/friends-story-01/source-freeze-36m-01/manifest.json) includes the full private patch against the pinned upstream commit. Workstreams A/C and the native-port project were not changed.

## Exact candidate and resources

ROM: [pokefirered.gba](../_local/artifacts/johto-full-36m-firered/pokefirered.gba), SHA-256 `8cda75eb36d9fb578b4771f678557fe838fa7ca132cf3c56800fd98f6db5650d`, CRC32 `55b42dcb`.

[Build manifest](../_local/artifacts/johto-full-36m-firered/manifest.json) SHA-256 `0d23ea529fda3bfcd50156d023522cdc8f014a96ddcc90cb383047df44cc9748`; freeze SHA-256 `ae5dfc92278e36a98e06b23a92b07d2aa0b50ba87edc20799177020262656275`. The actual FireRed target uses upstream `167aa6d537b109bb229c231ddce4616974c4da71`, ARM GCC 14.2.rel1, `O_LEVEL=s RELEASE=0 LTO=0`, and `-j2`. Make and wrapper exit codes are both zero. This final build is incremental; no separate clean 36M reconstruction is claimed.

| Resource | Actual linked result |
|---|---:|
| Unchanged cartridge | 33,554,432 bytes |
| ROM used / free | 32,697,188 / **857,244 bytes** |
| EWRAM used / static free | 255,044 / 7,100 bytes |
| IWRAM used / static free | 25,920 / 6,848 bytes |
| SaveBlock1 size / capacity | 15,868 / 15,872 bytes |
| Protected reserve | 256 bytes, unchanged |

All 397 compiled ARM save-layout facts and forty registered art pins match the preserved baseline. The four-byte main-save margin and original FireRed roamer fidelity defect remain open. Static RAM free space is not a maximum runtime heap or stack measurement. See the [measured resource report](../_local/evidence/friends-story-01/asset-integration-36m/RESOURCE-ART-INTEGRATION-36M.md). Other-target checks are bounded source/compiler comparisons, not a new whole-HnS build or gameplay claim.

## Executed native scope

Evidence retains each test's original ROM label. Unchanged non-Fuji checks from I/J/G/L are reused only under the explicit [M dependency equality proof](../_local/evidence/friends-story-01/non-house-source-reuse36m-01/report.json). Earlier Fuji images are excluded from current M framing acceptance.

| Check | Executed status |
|---|---|
| FG01–FG22 full primary conversations | PASS, all 22; disclosed staged prerequisites and original build labels |
| Source-derived owned event menus, choices and B cancellation | PASS, 51/51 distinct selections |
| Seven early plus seven final opponents, real win and real loss each | PASS, 28/28 staged combat branches; actual native outcomes, victory bits, blackout/healing and field return |
| All fourteen owned victory conversations | PASS |
| All fourteen later loss conversations | PASS; thirteen staged pending-loss fixtures, Ham's seventh tied to an actual loss, native Save/cold, ordinary walk back and interaction |
| Seven final invitations declined and explicit grid Back | PASS; no combat or automatic departure |
| FG21 actual last-battle victory and loss | PASS; neither departs automatically; later invitation works |
| FG22 rematches and all seven reunion battle endings | PASS; Brian rematches a genuine earlier saved victory; six other native wins execute their distinct reunion endings |
| Stay, farewell cancellation, Safe travels and later distinct reunion | PASS in recorded cases; all fourteen partners leave in successive groups |
| Johto League / Clair / takeover / same-map-departure negative gates | PASS, six source-qualified absence cases |
| Native Kanto→Johto→Kanto boundary roundtrip with actual Friends history | PASS, location-staged checkpoint; 47 scoped persistence checks |
| Largest native Lugia, scene, menu and ordinary field visibility | PASS within measured cases; current M hide→show→hide walk preserves the same follower allocation |
| Current M FG08 outside and direct-inside paths, repeat, ordinary Fuji service and door | PASS; all sixteen dialogue blocks, correct origins and clean camera/phase release |
| Actual Ham loss→Save/full quit/Continue→ordinary return→retry victory→Save/full quit/Continue | PASS; final retry-save reload strict 88/88 |
| Supported older native6 donor adoption and native Save/full quit/fresh Continue | PASS for the one actual donor; no starter replacement, gifts or fabricated Friends history |
| Current M FG08 normal Save/full quit/fresh Continue | PASS, strict 86/86; repeat-only conversation after fresh Continue |

The [28-outcome audit](../_local/evidence/friends-story-01/state-audit/actual-native-battle-audit-03/report.json) and [82-check final-context audit](../_local/evidence/friends-story-01/state-audit/actual-final-context-audit-36l-m-02/report.json) bind actual native battle evidence. The [current M Fuji cold-load report](../_local/evidence/friends-story-01/native-execution-36m-01/results/FG08-actual-native-completed-save-cold-01/strict-report.json) passes all 86 checks. The [actual choreography report](../_local/evidence/friends-story-01/executed-choreography-I-J-L-M-01/ACTUAL-CHOREOGRAPHY-I-J-L-M.md) records facing changes in all 22 events and native out-and-return movement for all eleven short walks.

The [nine-cycle normal-save matrix](../_local/evidence/friends-story-01/state-audit/final-normal-save-cycle-matrix36m-01/RESULT.md) preserves every original build label: three strict passes and six separately source-correlated native-history passes. The [root execution closeout](../_local/evidence/friends-story-01/native-execution-36m-01/results/ROOT-FRIENDS-NATIVE-CLOSEOUT-36M-01.json) binds current artifacts, actual process exits, preserved failed attempts and remaining limits.

Normal-save comparisons distinguish strict failures from separately proved native housekeeping. The older donor's strict regional comparison retains a dog-history mismatch; its separate source-correlated 87-check report allows only the exact predicted map-history shift. That is not blanket save compatibility. Actual Save files, GUI-selected paths, process exits, hashes and typed collection/region snapshots remain local under the exact execution/result folders.

## Owner review and remaining limits

The [event-by-event owner review](../_local/evidence/friends-story-01/owner-review-36m/REVIEW.md) contains actual map/trigger, engine receipt IDs, clickable source and labels, exact implemented text in textbox order, choices/outcomes, original build identities, execution status and actual emulator images. Missing or excluded captures are labeled. Separate [current Lugia images and state proof](../_local/evidence/friends-story-01/native-execution-36m-01/independent-largest-follower-audit-01/ACTUAL-36M-LARGEST-FOLLOWER-BOUNDARY.md) and [current Fuji images](../_local/evidence/friends-story-01/native-execution-36m-01/independent-fuji-audit-01/ACTUAL-36M-FUJI-CONTINUATION-AND-RENDER.md) show the affected presentation.

Owner visual acceptance of the seven battle portrait candidates, conservative follower pop, remaining prop/cinematic polish, Delta/hardware acceptance and a full natural Kanto/Sevii/Johto playthrough remain outside this bounded qualification. Fault-injection, arbitrary cheat/external executable-event acquisition and all possible save histories are not certified. No new permanent shadow system, legendary chapter, save format, cartridge expansion, publication or other-workstream change is included.

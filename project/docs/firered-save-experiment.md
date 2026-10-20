# B0 experimental FireRed save reservation evaluation

**Owner update — October 9, 2026:** Audio is **PASS — OWNER-REPORTED** for the current B0 evaluation. See the [owner audio confirmation](decisions/2026-10-09-b0-owner-audio.md) for attribution and scope. This later confirmation supersedes earlier audio-pending statements below; Codex did not perform a new listening test. The prior frozen audit and native reports remain historical evidence. B0 remains HOLD for review of the four-byte save margin and FireRed roamer fidelity defect.

Authorization: `docs/decisions/2026-10-08-b0-save-layout-exception.md`. Source pin remains `167aa6d537b109bb229c231ddce4616974c4da71`. This experiment evaluates the current target; it does not select the final engine, define production save compatibility or approve B1/Johto merging.

**Current checkpoint:** reviewed complete 010 builds and clean repeats passed for both targets. Actual 010 ARM probes preserve every measured approved size/offset; FireRed remains 15,868 bytes with four bytes free. Fresh HnS 009 native regression on the measured byte-identical 010 ROM completed the early-game checks and both normal save/cold-reload cycles; audio remains NEEDS OWNER TEST. Fresh FireRed 010 passed FR-01–09, including both normal-save/full-quit/cold-Continue cycles and requested shifted Pokédex/rival fields; its visual/input observation reached 600.9 measured active seconds. Audio remains NEEDS OWNER TEST for both games. B0 recommendation: **HOLD**. The preserved 009 starter failure and narrowly reviewed 010 default correction are documented below; no production/campaign/compatibility pass is claimed.

## Preserved patch and actual ABI checks

Combined patch 0004, applied alone against pristine source: `patches/0004-firered-save-reservation-experiment.patch`, 6,813 bytes, SHA-256 `2dd52a09f2ade09a457bcb7c6e35a78c90c1025f519348159200410f28b412cb`. It includes patch 0003 and adds only:

- `#ifdef FIRERED` reservation of four total roamer slots (one live, three reserved), rather than seven. All other target reservations stay unchanged.
- Individual HnS guards around migration versions 1/2/5's regional flag/variable actions. Common magic/version bookkeeping and the complete existing version-4 rematch reset are retained.
- HnS-only Red exceptions in two No-EVs challenge predicates. The common challenge restriction and default settings-off EV behavior remain; no replacement FireRed milestone is invented.

Two reviewers inspected the source/ownership boundaries and preserved apply/whitespace checks and preprocessing diagnostics. HnS gameplay function tokens remain identical for the migration, EV-gain and medicine behavior; whole Pokémon/party files have diagnostic `__LINE__` literal changes after inserted guard lines. Do not infer HnS ROM byte identity or transfer old native passes.

Independent ARM GCC 14.2.1 probes used the build's ARMv4T Thumb/APCS ABI. Four target probes exited 0:

| Target | Original SaveBlock1 | Experimental SaveBlock1 | Capacity / remaining |
|---|---:|---:|---|
| FireRed | 15,952 | **15,868** | 15,872 / **4 bytes free** |
| LeafGreen | 15,952 | 15,952 | Original 80-byte overflow unchanged; no build success claimed |
| HnS | 15,760 | 15,760 | 112 bytes free |
| Emerald | 15,752 | 15,752 | 120 bytes free |

Every measured non-FireRed value is unchanged. SaveBlock2/3 remain 3,892/52 bytes for all four configurations. The sector header/configuration, chunk table, checksum function and all protective assertions are unchanged. Initial missing-generated-header probe failures are preserved alongside successful fallback-header probes; subsequent FireRed/HnS native-field probes used actual generated build headers with no fallback.

Only the reserved padding size and 15 following FireRed member offsets change. Live roamer count remains 1, size 28 and offset 14,588. Reserved padding at 14,616 shrinks from 168 to 84 bytes. Every live member retains its original size. Examples:

| FireRed member | Original offset | Experimental offset | Size |
|---|---:|---:|---:|
| dexSeen | 14,784 | 14,700 | 136 |
| dexCaught | 14,975 | 14,891 | 136 |
| towerChallengeId | 15,752 | 15,668 | 4 |
| trainerTower | 15,756 | 15,672 | 48 |
| rivalName | 15,804 | 15,720 | 8 |
| route5DayCareMon | 15,812 | 15,728 | 140 |

Full exact field comparisons, compiler commands/exit codes and source-preservation evidence are under `[LOCAL_WORKSPACE]/_local/evidence/repair-analysis/independent-004-abi/`. Patch authoring/review is under `_local/evidence/repair-analysis/repair-authoring-04-firered/`. These are executed source/ABI checks, not native persistence or old-save compatibility passes.

Final FireRed 008 compiler-only probes used that actual build tree's generated headers, with no fallback, and exited 0. Every measured SaveBlock1/2/3 member size/offset equals approved patch 004; SaveBlock1 remains 15,868 with four bytes free. Evidence: `_local/evidence/native/repair-08-firered-compiled-abi/actual-firered08-abi.json`. Its build manifest still records linking failure/no ROM or ELF; a diagnostic map exists. Final HnS native offsets were compiled separately against its successful 008 tree, exit 0/no fallback, at `_local/evidence/native/repair-08-compiled-fields/native-field-map.json`, bound to its actual manifest and ROM hash.

## Preserved build and individual repair history

`repair-04-firered` **FAIL — EXECUTED**, make/wrapper exit 2; UTC `2026-10-08T22:42:39.962763+00:00` to `2026-10-08T22:45:03.358162+00:00`. Patch/config fingerprint: `43eb3dbd1f986913296978cf38ef468e9021641bbfc859a929b8673717276274`. Save compilation and its capacity assertion passed. The next actual failure is six HnS-only shiny-starter preview flags in `src/scrcmd.c:2660–2671`. No ROM/ELF/map was produced.

Manifest: `[LOCAL_WORKSPACE]/_local/artifacts/repair-04-firered/manifest.json`. Full logs/configuration/applied diff: `_local/evidence/builds/repair-04-firered/`. Baselines and patches 0001–0004 remain unchanged. The next guard was then reviewed individually: preserve the shared pre-starter randomizer/type substitutions and ordinary Pokémon-picture behavior, while isolating only HnS's flag-based shiny preview. No new flag or additional capacity change is authorized.

### Reviewed starter-preview guard

Combined patch 0005 is preserved separately at `patches/0005-hns-starter-preview-guard.patch`, 7,693 bytes, SHA-256 `759b05c0e939539963ac1051626112fe09e242e524c0aaccf5c2bc0b01cac9e4`. It includes patch 0004; apply it alone against pristine source. Its only added delta is two preprocessor directives around the HnS flag/RNG/shiny-preview subblock inside `ScrCmd_showmonpic`. The shared outer `!FLAG_SYS_POKEMON_GET` condition, randomizer species substitution/VarSet, one-type starter handling, normal picture dispatcher and script-effect request remain.

The six aliases are declared only in `flags_hns.h`; Elm's HnS script consumes them to select the gift's shiny mode. FireRed's Oak script uses ordinary `showmonpic`/`givemon` without those aliases. The full HnS `scrcmd.c` preprocessed token stream is identical to patch 0004. FireRed preprocessing exits 0 with those aliases absent and shared substitutions/normal picture behavior present. Save/layout headers, migration/EV guards and campaign scripts are unchanged from patch 0004. These are source/preprocessing checks, not native starter tests. Evidence: `_local/evidence/repair-analysis/repair-authoring-05-firered/` and `_local/evidence/repair-analysis/independent-005-authored-review.json`.

The clean `repair-05-firered` build **FAIL — EXECUTED**, make/wrapper exit 2, UTC `2026-10-08T22:49:04.394520+00:00` to `2026-10-08T22:51:13.503019+00:00`. Fingerprint `8b60cb0da9e93d3c73b2825bdbecaa20838054eddfb35459439f71fe4387fedf`. It passed the starter-preview compilation failure, then `src/shop.c` failed on common script-variable declarations `gSpecialVar_Result`, `gSpecialVar_0x8004` and `gSpecialVar_0x8005`. Those declarations exist in `event_data.h`, whose shop include is incorrectly limited to HnS while the shared shop code uses them. No ROM/ELF/map was produced. Manifest/logs remain under `_local/artifacts/repair-05-firered/` and `_local/evidence/builds/repair-05-firered/`.

The next reviewed correction exposed that legitimate common header to the already-compiled shop code, retaining every shop handler and the separate HnS flags include. It must not add dummy declarations/flags, remove shop behavior or alter native capacity.

### Reviewed common shop declarations

Combined patch 0006: `patches/0006-shop-shared-event-declarations.patch`, 8,078 bytes, SHA-256 `85f2f7388139fd79396eb1b0334df3f715140e411ddfdfa652347c2b0d9ebf90`. It includes patch 0005 and must be applied alone. Its only additional delta moves the existing `#endif` immediately before `#include "event_data.h"`. The legitimate common extern declarations now reach the shared shop code. The explicit HnS flags include stays conditional, HnS include order is retained, and the full shop body is byte-identical to patch 0005. Source definitions of the affected variables are common EWRAM variables; none is newly declared or invented by this patch.

Independent review confirms every prior source/config/save change is retained without broadening. Exact evidence is under `_local/evidence/repair-analysis/repair-authoring-06-firered/` and `_local/evidence/repair-analysis/independent-006-declaration-review.json`.

The clean `repair-06-firered` build **FAIL — EXECUTED**, make/wrapper exit 2. Actual make UTC start/end: `2026-10-08T22:53:49.901246+00:00` / `2026-10-08T22:55:53.934849+00:00`. Fingerprint `48027bff0badd4cecf0d70a075ecd961f6d5345ab73d277056a832fd3cbb5d44`. The shop compilation passed; the next error was `MAPSEC_MT_SILVER` in `HideStartMenu`. No ROM/ELF/map was produced. Original clean logs/manifests remain unchanged.

### Reviewed Mt. Silver menu hook

Combined patch 0007: `patches/0007-hns-mt-silver-menu-guard.patch`, 9,027 bytes, SHA-256 `50b6c11000be723167f3942b4e1a728e906a17e676c7e2694e256c43487822bf`. Apply alone against pristine source. Its only added delta is two `IS_HNS` directives around the Mt. Silver summit blizzard-resume hook. The map section, layouts and variable alias belong to HnS; its summit script consumes the temporary variable to restart sound. Shared selection sound, menu closing, window clearing, unfreezing and unlocking remain outside the guard. All previous source/configuration/layout edits are retained exactly.

A keep-going build in the preserved failed 006 tree inventoried additional actual diagnostics. It exited 2, UTC `2026-10-08T22:56:54.580586+00:00` / `2026-10-08T23:01:04.237197+00:00`, log SHA-256 `3b388e115c2e5657562dc978681361655912a26c614009642218e222b6a7319b`. It found only the Mt. Silver hook plus Rocket Hideout identifiers in `map_preview_screen.c:154` / `region_map.c:713` and New Sinjoh in `region_map.c:2912`. This is an incremental diagnostic, not a clean build or acceptance pass. Its separate command, log and real exit code are under `_local/evidence/builds/repair-06-firered/incremental-keep-going-diagnostic/`.

### Reviewed regional map boundaries

Combined patch 0008: `patches/0008-regional-map-target-boundaries.patch`, 11,356 bytes, SHA-256 `bcab26a7ccf880e37e7aae12ce12b719ed6c5df05c1dcd1739a8c98aebe6e562`. Apply alone against pristine source. All earlier combined files are retained exactly. Three additional sites were individually reviewed:

- The entire map-preview implementation is already FRLG-only. Restore its existing real `MAPSEC_ROCKET_HIDEOUT` identifier, as used by all five selected FireRed Rocket Hideout maps and the prior source revision. Preserve every preview asset/flag/type/dispatcher; do not remove the preview to compile.
- Keep the shared heal table's existing HnS Rocket Hideout key under `IS_HNS`, using the existing generic Rocket Hideout key otherwise. Retain the original table value in both branches.
- Restrict only the New Sinjoh/Melemele color-selection expression to HnS, matching the destination array's existing HnS guards. The common Battle Frontier destination, sprite creation and complete loop/size/callback/animation behavior remain.

Pristine apply/whitespace checks and independent exact-delta review passed. HnS map-preview tokens and both edited region-map blocks are unchanged. Whole HnS region-map preprocessing differs only in an allocation diagnostic line literal (2399 to 2403); the initial strict identity assertion and complete comparison remain preserved. These changes add no flag, field, map, placeholder or capacity adjustment. Private authoring/source-history/preprocessing evidence is under `_local/evidence/repair-analysis/repair-authoring-08-firered/`; independent review is `_local/evidence/repair-analysis/independent-008-authored-review.json`.

### Preserved 008 clean failure and initial stop review

`repair-08-firered` **FAIL — EXECUTED**, make/wrapper exit 2. Actual make UTC start/end: `2026-10-08T23:02:41.699658+00:00` / `2026-10-08T23:08:20.971116+00:00`; fingerprint `91e1544f19938fceae5288b7907fe332e9ea6b6614c9464108bfad2377b3af54`. All previous C compilation failures, including the protective save-capacity assertion, passed. Linking then reported **17 unresolved references (14 distinct symbols)**. No ROM or ELF was produced. A failed-link diagnostic map is preserved: 4,977,612 bytes, SHA-256 `b3ab6576554c5762b36afdfde8e8af1684162416bab729737e03edbf2449d4de`. This map is not a playable artifact or successful linker-capacity qualification.

Manifest/map: `[LOCAL_WORKSPACE]/_local/artifacts/repair-08-firered/`. Exact log/configuration/complete applied diff: `_local/evidence/builds/repair-08-firered/`.

Read-only individual linker review found narrow HnS ownership boundaries for the Petrel sound exclusion, Alola door/grass overrides, Buena special registrations, HnS debug entries/scripts, Bug Contest whiteout dispatch, HnS Safari helpers and Ilex Forest tutor. None was patched after the stop boundary. Shared sounds/doors/grass, ordinary whiteout/Safari/tutors and the FireRed roamer debug entry must remain. Do not invent missing symbols or empty debug scripts.

The initial review considered changing the shared Mauville TM-prize flag dispatch itself and concluded that guarding that flag alone would not preserve its behavior. It tests HnS-only `FLAG_FINITE_TMS`, but `new_game.c:148` defaults the common `challengeSettings.tx_Mode_InfiniteTMs` to 1 and `item.c:877` uses that setting. Omitting the flag branch selects finite purchase logic while items remain reusable. Its rejection message also borrows a Goldenrod-only label. A correct shared setting/interface and message decision is a substantive gameplay repair; no fake flag, unconditional branch, missing-message placeholder, gameplay deletion or new script interface was introduced. At this initial review FireRed repairs were stopped, and no patch 0009 had been authored. The subsequent compiled-caller review below narrows that conclusion.

Private reviews: `_local/evidence/repair-analysis/repair08-linker-assigned-symbols/`, `_local/evidence/source/repair-08-link-owned-symbols.md` and `_local/evidence/repair-analysis/independent-008-link-flag-classification.json`. Exact history commit `457647a6c2c7dc316d37ad89275999bc902d5cc6` introduced the shared finite-flag jump, infinite purchase paths and Goldenrod text dependency. No existing registered script/special getter was found. A future approved repair could query the existing selected-TM importance/settings and bind a correct shared message, without a new flag or save field; choosing a different TM purchase policy also needs explicit review. The separate patched HnS 008 native observations remained tied to that ROM and cannot qualify FireRed or later 009.

| Actual unresolved symbol(s) | Reviewed callsite / ownership | Initial disposition at stop (superseded by later reachability review) |
|---|---|---|
| GoldenrodCity_RadioTower_5F_EventScript_Petrel | Shared interaction sound exclusion; script defined only in HnS campaign | A narrow conjunct guard could retain all ordinary sound/script handling; not patched |
| gTileset_AlolaIsland (3 references) | Two door overrides and tall-grass template branch; tileset/all seven layouts HnS-only | Narrow override guards could retain ordinary doors/grass; not patched |
| Special_BuenaPasswordShowMultichoice / Special_BuenaCheckAnswer / Special_BuenaRollReward | Three special registrations; implementation/callers HnS-only | Guard registrations consistently with generated IDs; no stubs; not patched |
| FLAG_FINITE_TMS | Shared Mauville TM-prize dispatch; generic setting now elsewhere | Substantive shared behavior/interface review required; stop |
| GoldenrodCity_GameCorner_PrizeRoom_Text_YouAlreadyHaveThis | Shared Mauville reusable-TM rejection borrows HnS-only message | Preserve real rejection/message behavior; no blank placeholder; stop |
| UnionCave_B2F_EventScript_Lapras / SinjohRuins_EventScript_StevenBattle / SinjohRuins_Lab_Text_StevenCall3Plates / SinjohRuins_Lab_Text_StevenCall6Plates | Shared debug slots point to HnS-only scripts/text | Corresponding script bodies and C menu entries need consistent HnS guards; preserve shared slots/FireRed roamer debug entry; not patched |
| FLAG_SYS_BUG_CONTEST_MODE | First dispatch in shared field whiteout; contest implementation HnS-only | Preserve complete ordinary whiteout; narrow contest dispatch guard only; not patched |
| FLAG_IN_KANTO_SAFARI_ZONE (2 references) | HnS helper labels called only inside existing HnS branches; FRLG already selects real Fuchsia entrance | Preserve FRLG/common Safari flow; guard only HnS helpers; not patched |
| FLAG_GET_HEADBUTT | Ilex Forest tutor/unlock; sole map caller HnS-only | Preserve other shared tutors; isolate only HnS addition; not patched |

## Preserved 008 native status and open limits

At the 008 stage FireRed native checks were BLOCKED because linking failed. No FireRed ROM/native saves existed at that stage, and neither cycle was executed. Patched HnS 003 was stopped at the campaign menu after inspection showed the final patch can change diagnostic ROM bytes; that partial fresh session is preserved and does not pass the complete checklist or either normal-save cycle. HnS 008 compiled successfully, make/wrapper 0, with ROM SHA-256 `c446291194e601bf0b5650afec899cb151458a51c5d44a9915df78fa8a1e7687`. Its separate clean repeat passed with identical ROM/ELF/map/config hashes; that fresh 008 regression was subsequently stopped before normal saves/cold cycles/active timing when 009 produced a different exact ROM.

Compare visible Pokédex/party/inventory/location/progression and rival name across two normal-save/full-quit/cold-Continue cycles. A read-only inventory of dedicated backups may supplement GUI name/Dex evidence using compiled offsets and the existing sector/checksum definitions. It must not modify or import saves, advance game state or stand in for executed cold reloads.

Four-byte save-block headroom and the existing FireRed Hoenn/Latias–Latios roamer fidelity mismatch remain open. Complete campaigns, natural Sevii access and save compatibility are unqualified. Stop at B0 review, or earlier if another blocker requires broader restructuring, gameplay removal or another capacity change.

## Subsequent FireRed TM reachability review

Read-only inspection materially narrowed the initial stop rationale. The 25 labels in the contiguous Mauville TM-prize block (`scripts.inc:452–687`) have only two external lexical callers: the Mauville map and HnS Celadon map. Neither is selected in actual generated FireRed 008 headers/events/groups. An executed symbol scan of all 1,520 compiled FireRed objects found no imports of these labels; all 60 named event-script references lie inside this block. Scripts immediately before and at its end terminate explicitly, preventing boundary fallthrough. The selected FireRed Celadon prize room uses separate prize-clerk scripts.

Evidence: `_local/evidence/repair-analysis/independent-008-firered-tm-reachability-challenge.json` and `independent-008-firered-tm-compiled-callers.json`. These are source/compiled-caller findings, not runtime passes. A narrowly `#ifndef FIRERED` exclusion of this unused block can be evaluated without repairing shared TM settings/messages or changing any other target's TM code. No selected FireRed gameplay is proposed for deletion. At that stage a combined 009 candidate was being authored and independently reviewed with the other individually classified HnS linker guards; subsequent 009 build/native results are recorded below. Any broader restructuring, feature removal or capacity change still requires stopping for owner review.

HnS 008's separate native test later stopped as a preserved partial run. A final candidate's HnS artifact must be rebuilt and hashed: only measured byte identity permits the same exact-ROM native evidence to apply; any changed ROM needs its own fresh native qualification. Four-byte FireRed headroom, roamer fidelity and compatibility limits remain open.

## Reviewed combined 009 and fresh builds

Complete candidate: `patches/0009-hns-linker-target-boundaries.patch`, 19,906 bytes, SHA-256 `bea352da2bf5aa726084e4b418933c82287101abd1621af7b58e49e8d6de6c82`. Apply it alone against pristine. It retains every 008 edit and adds only the ten individually reviewed file boundaries: the unused FireRed-only Mauville block, HnS Petrel interaction conjunct, Alola door/grass overrides, Buena special registrations, corresponding HnS debug declaration/menu/script bodies, Bug Contest whiteout dispatch, HnS Safari helper bodies and Ilex Headbutt script. Real FireRed Oak/Celadon scripts, shared fallback behavior, all save/layout/configuration headers and sector/checksum/assertion code remain identical to 008.

Pristine apply/whitespace checks passed. Author and independent preprocessing checks confirm whole HnS interaction/door/grass token identity and HnS event-script aggregate identity to 008; Mauville code is identical for HnS/LeafGreen/Emerald. HnS debug preprocessing differs only in five existing allocation diagnostic strings (+8 line numbers). The corrected complete compiler pipelines exited 0 for all four new C source files for both targets. Initial missing-generated-header/INCBIN harness failures are preserved; source diagnostics retaining assembler `.if 0` text are not falsely claimed to be compiled failures or runtime evidence.

Exact source/preprocessing evidence: `_local/evidence/repair-analysis/repair-authoring-09-firered/` and `independent-009-review/`. Both fresh target builds were launched with two jobs each and the same locked tools/configuration. New patch/config fingerprint: `656b49ab221989a12362bb1bbc9e24303e833274e33c7bde2ec9822056a97b44`. The subsequent executed 009 build/repeat results are recorded below; native checks remain tied to actual exact-ROM evidence. The approved capacity experiment is unchanged; any new substantive blocker still requires stopping.

## Historical 009 compilation/layout checkpoint

Both separate clean 009 targets passed, make/wrapper 0, with actual ROM/ELF/map artifacts. FireRed ROM SHA-256 `74f90c6d019442adfb72d251720f749713e264b44066b6363de14c77b2ddaa40`; HnS ROM `4bb58fe3c06bc0b60146aa946cbc34f087efa607f525f68e0a1e99c0db9cde75`. Full exits/times/configuration/hashes are in the build report and successful manifests. Initial failed 008 remains preserved, rather than relabeled successful.

Final successful-target field probes exited 0 without header fallback, bound to actual 009 manifest/ROM/header hashes: `_local/evidence/native/repair-09-compiled-fields/native-field-map.json`. Full member comparison `_local/evidence/native/repair-09-full-abi/actual-009-abi-comparison.json` confirms all approved 004 sizes/offsets and actual 008 FireRed values. FireRed 15,868 / four free, HnS 15,760 / 112 free, SaveBlock2/3=3,892/52. Four-macro ARM probes preserve every measured LeafGreen/HnS/Emerald member; LeafGreen/Emerald are explicitly type-layout diagnostics using actual FireRed 09 generated-map context, not successful target builds. Save/config/storage headers and save.c are byte-identical to 008.

Both final 009 clean repeats passed with identical per-target ROM/ELF/map/configuration hashes. Fresh FireRed 009 passed the Pallet/CODEX/PATCH opening but failed natural starter acquisition; dependent gameplay/two-save qualification is blocked. HnS 009 differs from 008 by exactly 10 diagnostic ROM bytes; fresh 009 HnS testing is executing separately. The dedicated-backup inspector accepts only authorized immutable cycle files and successful exact-manifest bindings; it may supplement fields but cannot replace executed cold reloads. No final native/old-save/full-campaign pass is claimed here yet.

## Executed 009 starter failure and narrowly bounded default correction

The exact FireRed 009 runtime failure is preserved in `docs/firered-native-results.md`: natural Bulbasaur confirmation/grant text, then a question-mark nickname screen and empty party, confirmed twice. FR-01 passed; FR-02 failed; FR-03–FR-10 are blocked. No normal save was made in this malformed state and no persistence pass is claimed.

Two independent source reviews identified an omitted existing default. `ONE_TYPE_OFF` is 31, while cleared `tx_Challenges_OneTypeChallenge` is `TYPE_NONE` 0. The runtime predicate treats every value except 31 as active. HnS's existing initial challenge menu recognizes 0 as UI OFF and writes 31 when confirmed; FireRed goes directly from Oak speech to New Game. The common empty-save startup already calls `SetDefaultChallengeSettings`, but that function omits this field. New Game snapshots and restores incoming challenge settings, so another initializer call alone would not fix it. Party limit 0 still means the ordinary six slots.

The existing type filter in `GiveScriptedMonToPlayer` can send a rejected gift to storage; Oak ignores its result and names party slot 0. This is consistent with the observed empty party, but no live RAM or storage box was inspected. Private source/history reviews: `_local/evidence/repair-analysis/firered-09-starter-default-review.json` and `independent-009-firered-starter-failure/review.json`. The pinned upstream history changed the active predicate to the 31 sentinel without filling the common default.

Root classifies assigning this existing OFF value only for FireRed in the existing fresh-default initializer as a routine omitted-default correction within B0. This preserves filtering, starter scripts, incoming deliberate challenge choices and all other defaults. No additional menu, policy, flag, field, save migration, feature removal, layout or capacity change is authorized. At that preserved pre-build checkpoint, complete 010 was being authored and independently reviewed; subsequent build results are below and native verification remains required. No old/malformed-save compatibility is claimed. Any next blocker requiring broader restructuring, feature removal or another capacity change still stops for owner review.

### Reviewed 010 source identity — preserved pre-build checkpoint

Complete 010 is frozen at `patches/0010-firered-fresh-monotype-default.patch`, 21,515 bytes, SHA-256 `3e9b6b003557cbfacff59706ad04e4f7f2fdd58bc6162be995f91dc09742d5f3`; apply it alone against the pristine pin. It retains every 009 change byte exactly and adds only three file changes: expose the existing `ONE_TYPE_OFF` 31 macro in `challenge_menu.h`, replace its old local definition with a blank line to preserve source line numbers, and initialize the existing field only under `FIRERED` in `SetDefaultChallengeSettings`.

Independent source/full-preprocessing/ARM syntax review completed 54 checks with exit 0. Challenge-menu output is byte identical for all four target macros; new-game output is byte identical for LeafGreen/HnS/Emerald. FireRed adds the intended default and declarations only. `NewGameInitData` remains source-byte identical, including incoming-choice snapshot/restore. These syntax checks used read-only 009 generated resources and are not successful 010 builds or layout/runtime checks. Exact evidence: `_local/evidence/repair-analysis/independent-010-review/review.json`, SHA-256 `4a6b91aca920de2de2afef0574aef8395cf437111ea3bea2203905ed47ea79c1`.

Root accepted this routine correction for bounded B0 clean builds. Fresh `repair-10-firered`/`repair-10-hns` compilation and repeats have been dispatched. Actual HnS 009→010 ROM byte identity must be measured before associating the ongoing fresh 009 regression with 010 outputs. Fresh FireRed 010 native checks will use a new isolated session. No 010 successful compile, starter or save result is claimed at this checkpoint.

Author 010 separately completed 16 full compiler preprocessing commands and 16 pinned text/INCBIN preprocessing plus ARM syntax stages, all exit 0. Full non-FireRed new-game output and all four challenge-menu outputs remain byte identical 009, including HnS allocation diagnostic line strings. Corrected helper path-comparison caveats are retained; this is source/syntax qualification only. Evidence: `_local/evidence/repair-analysis/repair-authoring-10-firered/authoring-review-ready.json`. Actual clean builds use fingerprint `32faeccdf41db77505858cd2981a070c7f835f0eee3180fe1563cb4c0e343f00`; first FireRed/HnS make started UTC 00:35:24.361885/00:35:44.543660. No final exit or hash result was available at this checkpoint.

### Executed 010 clean outputs and final actual ARM layouts

Both first 010 targets passed, make/wrapper 0. FireRed ROM `3e504731d9dd3c02ec273dc257c86f557caaf8c9b933d2f0ff73558c2e121a39`; HnS `4bb58fe3c06bc0b60146aa946cbc34f087efa607f525f68e0a1e99c0db9cde75`. Actual HnS 009→010 comparison found zero differing ROM bytes, with identical ELF/map, so the ongoing fresh 009 native evidence can associate with 010 without claiming a new GUI run or importing old saves. At that first-build checkpoint, both 010 clean repeats were running; both subsequently passed as recorded below.

Actual successful 010 target field probes have no generated-header fallback: `_local/evidence/native/repair-10-compiled-fields/native-field-map.json`, SHA-256 `36147a9179cfcf16c545214df5d00550fff7a9760b882ab0830d6b52ef6b81c9`. Four-macro ARM full-member comparison: `_local/evidence/native/repair-10-full-abi/actual-final-abi-comparison.json`, SHA-256 `6fd387e62af4478f65138a164b38480e946cd878819ae1541f1c474795845bbb`. All compiler/dependency commands exited 0; every measured size/offset equals actual 009 and approved 004. FireRed 15,868/4 free; HnS 15,760/112 free; LeafGreen 15,952/−80; Emerald 15,752/120 free; SaveBlock2/3 remain 3,892/52. LG/Emerald use actual FireRed generated-map context for type-layout diagnostics only; no target build/native pass. Bitfields are not individually addressable; complete structure sizes/alignment and dependency/header hashes are retained. No save compatibility inference.

Fresh FireRed 010 runtime/two native cycles remain NOT RUN at this checkpoint. The dedicated inspector is being bound to successful 010 manifests and only reserved immutable FR10 cycle backups; it cannot replace executed cold reloads. HnS 09 native session retains its exact 09 binding. Four-byte headroom and roamer fidelity remain open.

### Executed 010 reproducibility — preserved pre-native checkpoint

Both clean target repeats passed with real make/wrapper 0 and identical ROM/ELF/map sizes/hashes, configurations/environment, patch/source/generated records, map selections and locked tool hashes. Both-target independent summary SHA-256 `6eda33d541f51307a5cd8130b87a1f74d12bb6e3178606c3cdc323d8b81a232c`; exact times/manifests and separately corrected launcher attachment evidence are in the build report. All build jobs are idle. Native regression remains separate; no completed FireRed 010 two-cycle or full patched-HnS two-cycle pass is claimed at this checkpoint.


### Completed native B0 evaluation

FireRed 010's separate fresh session completed FR-01–09: actual Pallet/Oak/Bulbasaur opening, ordinary rival loss/normal continuation, Parcel/Dex progression, wild capture/healing/menus and both native save/full-quit/cold-Continue cycles. Both retained CODEX/ID 12830, stored PATCH, Dex seen 4/owned 2, male Bulbasaur level 6 HP 21/21 and male Pidgey level 4 HP 17/17 with observed moves/PP, money 3,000 and four Balls. Held NONE was recorded for both before Save 1, explicitly viewed for Bulbasaur after cold 1 and both after cold 2; a separate Pidgey held-item view after cold 1 is not claimed. Save 1 restored the home checkpoint; Oak appraisal did not replay opening rewards. Save 2 restored the Route 1 clerk checkpoint and Potion 1 instead of an empty Medicine pocket; ordinary clerk revisit did not give another Potion. FR-10 visual/input passed at 600.9 measured active seconds, with timed FPS snapshots 50.8–60.6 and earlier menu 44.6 separately recorded. Audio remains NEEDS OWNER TEST.

Read-only immutable backup inspections accepted bank 1/counter 1/rotation 1, then bank 0/counter 2/rotation 2, with all 14 selected payload checksums/IDs/signatures valid and inputs unchanged. Actual shifted SaveBlock1 rival offset 15,720 stored PATCH in both saves; seen/caught arrays at 14,700/14,891 stored 4/2, agreeing with this early GUI. Raw party count 2 also agreed. Raw position/location/flags/vars supplement rather than decode semantic progression; party/moves/items/progression remain actual GUI observations. Native payload checksums do not cover SaveBlock3 extra/footer or the retained optional 16-byte emulator suffix.

The 131,088-byte FireRed backups are `cycle-01.sav` SHA-256 `e33cb49c49ffcfba6571df8af084d8161f94338cbf0659b3bb8e9ea4454b8c27` and `cycle-02.sav` SHA-256 `f1be6de058c04645a32ead45328ae5ecace9dfc038b45fb56880c6e614f06895`, under `_local/saves/firered/repair-10-native-01/`. After final cold comparison mGBA was fully quit, no third normal save was made, and the tester recorded the active file exactly equal to cycle 2; independent final boundary comparison is separate. Fresh patched HnS 009, on exact byte-identical final 010 ROM bytes, separately completed HNS-01–08/two cold cycles and 601.2 active seconds; audio needs owner testing. Its session stays bound to 009, with no imported save or extra GUI run claimed.

Full native reports: `docs/firered-repaired-native-results.md` and `docs/hns-patched-native-results.md`. B0 recommendation remains HOLD for human audio observation and owner review of the four-byte limitation/fidelity defect. This evidence evaluates only these fresh early-game saves. Four-byte headroom and FireRed roamer fidelity stay open; no full campaign, natural Sevii, original/cross-build save compatibility, production format or engine selection is certified. B0 stops here; B1/Johto merging remains unauthorized.

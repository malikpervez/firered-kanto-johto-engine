# B2 native travel results

**October 9–10, 2026, America/New_York — bounded B2 validation complete; awaiting owner review.** Tester: Codex through desktop mGBA 0.10.5 on the recorded native arm64 Mac. The session ran approximately 23:20–00:08 EDT (03:20–04:08 UTC). This report distinguishes the executed natural opening on candidate 013 from the narrow two-NPC correction in candidate 014. A compilation result does not pass a runtime check.

## Candidate and session binding

Upstream commit: `167aa6d537b109bb229c231ddce4616974c4da71`. Candidate 013 ROM SHA-256: `4989dadd96a19b3083d89722c25ed4ff48bd122edafe29221c76a84e0a921c9d`. Its clean output matched the incremental ROM/ELF/map exactly before native play. Candidate 014 changes only the two FireRed slice NPC graphics IDs to existing FireRed graphics; the original opening, starter, rival battle, save code, scripts and HnS event branches are unchanged.

The disposable session is [b2-native-01](../_local/saves/firered/b2-native-01/); [chronological observations](../_local/evidence/native/b2-native-01/gui-events.jsonl) bind the actual actions and candidate. No personal/retail/010 save was loaded, and no cheat, debug grant, emulator save state or save editor was used. The session began with a fresh New Game on 013; its first normally produced Kanto save is retained for the exact two-graphics-ID correction. This does not establish compatibility with other saves or production formats.

Final 014 ROM SHA-256 is `8980ba9dced4586dda2450ea102789a4ac8bf4da731f3a8c07db18a0a41ab9f2`, bound to the successful [clean 004 manifest](../_local/artifacts/b2-04-firered/manifest.json), SHA-256 `385a5330782851a65c43683fe01d86743fc79180e9d442ea52705ed5200c614b`. Its clean and incremental ROM/ELF/map files match exactly. The session ROM copy initially came from incremental 014; this equality was checked before final acceptance and the session record was bound to clean 004. The original 013 session record and save inspection remain preserved in [candidate provenance](../_local/evidence/native/b2-native-01/candidate-013-preservation-and-004-provenance.json). A fresh opening on final 014 was **NOT RUN**; the already executed opening is retained with the exact two-field source delta and unchanged save/opening code, rather than described as a new final-ROM playthrough.

Observed emulator settings: native 59.7275 FPS target, audio muted at the owner's existing preference, 44,100 Hz/1,536-sample buffer, Load Last State off, Load Cheats off, periodic state saves off, native saves/screenshots beside the dedicated ROM, Discord presence off. Initial gameplay snapshots were around 59–60 FPS, with lower transient snapshots during map loads; no constant-performance claim. In-game text speed was set to FASTER in this fresh disposable save. Audio was not listened to again for B2.

## Executed opening and defect

| Check | Actual observation | Result |
|---|---|---|
| Natural FireRed opening on 013 | FireRed/Charizard title, New Game only, original controls/Oak introduction, male RED and rival BLUE, bedroom/stairs/front door/Pallet, Oak grass interception and lab escort | PASS — EXECUTED |
| Natural starter and battle on 013 | RED received Bulbasaur; BLUE selected Charmander; original rival battle completed, Bulbasaur gained 68 experience and reached level 6 | PASS — EXECUTED |
| Baseline collection on 013 | One male Bulbasaur level 6, 21/21 HP, five empty party slots; Route 1 clerk's Potion ×1 in Medicine pocket | PASS — EXECUTED |
| First Kanto normal save on 013 | Save → Yes, SAVING screen, return to field; full process quit; immutable native backup; fresh launch and Continue restored Pallet (10,13) | PASS — EXECUTED |
| Development travel decline on 013 | No closed the dialog; Right moved the player one tile | PASS — EXECUTED |
| First New Bark arrival on 013 | Correct town layout and NEW BARK TOWN popup; return guide absent, allowing the player onto its intended tile | FAIL — EXECUTED |
| Defect diagnosis and bounded correction | Actual 013 ROM encoded the correct object/script but its HnS graphics pointer was NULL in FireRed. 014 selects real existing FRLG FatMan/Woman1 sprites only in the slice overrides; both NPCs appeared and their interactions passed below | VERIFIED IN SOURCE / ROM; corrected runtime PASS — EXECUTED |

The failed candidate and [private defect screenshot](../_local/saves/firered/b2-native-01/firered-b2-native-01-0.png) remain preserved. The game was fully quit without saving that failed Johto visit; the original Kanto checkpoint was not edited. An incidental Route 1 Rattata encounter was left through normal Run, visibly reporting “You got away safely.”

## Candidate 014 travel acceptance

All checks below were operated through the native desktop UI on final 014. Travel scripts visibly label the visit as DEVELOPMENT TRAVEL. The first trip includes the house visit and Johto save/reload; trips 2–10 immediately use the two guides. Arrival screenshots were observed after every leg. No reward or starter was granted in Johto.

| Check | Actual observation | Result |
|---|---|---|
| New Bark return guide appears and works | Guide at (5,22), player arrives south at (5,23); labelled Return to PALLET TOWN? dialog; No returns control, Yes travels | PASS — EXECUTED |
| House1 doorway/interior/harmless NPC/exit | Blue door animates; real interior; from entry (4,8), north to (4,4), face right to visitor (5,4); welcome/development dialogue; exit returns to the same New Bark door | PASS — EXECUTED |
| Ten complete Pallet → New Bark → Pallet round trips | Trips 1–10 all reach New Bark (5,23) and return to Pallet (10,13) in the same running ROM | PASS — EXECUTED |
| Collision and control release at arrivals | Holding Up is blocked by each guide; A opens the correct conversation; declining permits walking and menus; every return guide remains accessible | PASS — EXECUTED |
| Normal Johto Save/full quit/cold Continue | Save → Yes → overwrite own isolated file → SAVING → field; full process quit verified absent; fresh process/Continue restores New Bark (5,23) | PASS — EXECUTED |
| Normal returned Kanto Save/full quit/cold Continue | After trip 10, Save → Yes → overwrite → SAVING → explicit RED saved the game → field; process quit verified absent; fresh process/Continue restores Pallet (10,13), time 0:24, badges 00 | PASS — EXECUTED |
| Visible collection and identity after both reloads | Male Bulbasaur level 6, HP 21/21, five empty party slots; Potion ×1 in Medicine; RED, ID 25928, money 3,080, zero Kanto badges | PASS — EXECUTED |
| Rival/Dex/story retention | Read-only inspection of the normal saves: BLUE, actual Dex seen/caught flags and every story flag unchanged; no new Johto progression | PASS — EXECUTED — checkpoint inspection |

The original HnS town/building/interior tiles are selected unchanged; RED and the two development NPCs use existing FireRed sprites. The existing night palette tint was visible. This observation does not qualify a full day/night cycle. [House conversation screenshot](../_local/saves/firered/b2-native-01/firered-b2-native-01-1.png) and [final New Bark town screenshot](../_local/saves/firered/b2-native-01/firered-b2-native-01-2.png) are local and ignored. Remaining menu/arrival screenshots are displayed in the CUA conversation; the observation log identifies these without inventing local image files.

## Read-only persistence evidence

The first immutable checkpoint, [kanto-before-travel.sav](../_local/saves/firered/b2-native-01/kanto-before-travel.sav), is 131,088 bytes, SHA-256 `6fac3f465bfc8fea83dfee6a5fdd73002c879286d35069ac4c4e5de547a6c074`. Read-only inspection selected bank 1/counter 1 and verified all fourteen sector IDs, rotations, signatures and original payload checksums. Bank 0 was erased, as expected for the first save. It stored RED, BLUE, trainer ID 25928 and party count 1. Raw Dex seen IDs were `[1,4,19]`, caught `[1]`; the Pokédex menu had not yet been unlocked through Oak's Parcel quest. This checks preservation of the actual state, not completion of that quest or a full Pokédex UI regression.

The two final-014 checkpoints are also 131,088 bytes and retained read-only:

| Checkpoint | SHA-256 | Selected normal bank/counter |
|---|---|---|
| [johto-cycle-01.sav](../_local/saves/firered/b2-native-01/johto-cycle-01.sav) | `ba7aefef473f237f7eff6d220920348c16c09861b1b1fe74faa0e9d2f43edccd` | 0 / 2; both banks valid |
| [kanto-cycle-02.sav](../_local/saves/firered/b2-native-01/kanto-cycle-02.sav) | `7ba5fda5ca885fdc87f208a8dd0b48a60fcbc4471640003dbfb06c83cf4dd10e` | 1 / 3; both banks valid |

[Consolidated read-only evidence](../_local/evidence/native/b2-native-01/save-evidence-summary.json), SHA-256 `e73d3833fe08397d10ccd5b81dc9961acab0e67bf6d50936648b3426c11064fe`, binds inspections and all three pairwise comparisons to the actual successful candidate's ARM field map. Save version, trainer/rival, Dex seen `[1,4,19]`/caught `[1]`, party count, every story flag, roamer bytes, PC storage and SaveBlock3 remain unchanged. Baseline-to-return variables differ only in existing friendship-step counter 115 → 1 and poison-step counter 2 → 0; Johto-to-return variables and party bytes are identical. Returned position/layout match baseline; the location structure now retains explicit return coordinates where baseline had unset warp coordinates. Exact raw location changes `4400ff00ffffffff` → `4400ff000a000d00` are preserved in the report, alongside the executed correct Pallet arrival.

All selected banks have fourteen unique sector IDs, valid rotations/signatures and original payload checksums. The first bank's erased alternative is retained, not misreported as valid. Inspections left every backup hash unchanged. Normal bank checksums do not protect SaveBlock3; B2 neither changes nor solves that limitation. Raw bag/money/coins inequalities are recorded without treating them alone as gameplay failure or success; party/Bag/trainer checks above provide the visible confirmation. Coins were not independently checked in a GUI; no new coin-reward logic is present. This is preservation of the actual pre-Parcel state, not new campaign qualification.

## Limits and manual access

The prototype contains New Bark Town and one house, without Johto routes, starter/story initialization, rewards or independent regional progression. The world map/Fly presentation and future Johto capture-location strings are unqualified. Browser B2, full campaigns, postgame roamers, old-save migration, runtime resource peaks and release qualification are NOT RUN. The four-byte FireRed save margin and roamer fidelity defect remain open.

To try the final reviewed prototype, use its exact ROM in a new isolated mGBA save folder. Arrows move; X is A, Z is B and Return is Start. Receive Oak's starter naturally, then speak to the development guide west of Oak's lab at (10,12), standing south at (10,13). Yes visits New Bark (5,23). House1 is one tile west and two north, at door (4,21). The return guide is directly north of the arrival at (5,22); Yes returns to Pallet (10,13). Use the game's Save and cold Continue, with state restoration disabled.

Inside House1, walk north along x=4 from (4,8) to (4,4), then face right to speak to the visitor at (5,4). Return south to the same (4,8) doorway. New Bark is a development destination: no route exits, Johto starter, story, rewards or production travel unlock are implemented.

Stop at the B2 review gate. No B3, save allocation, campaign expansion or Workstream A change is authorized by these results.

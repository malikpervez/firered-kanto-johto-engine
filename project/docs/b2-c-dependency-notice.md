# B2 candidate 014 — asset dependency and validation notice for C

**Updated October 10, 2026, America/New_York.** Candidate 014 adds two Johto maps to the tested FireRed foundation, with one trainer and development travel to Pallet and back. It corrects two development NPC graphics selections after 013 reached New Bark but its return guide was absent. The final clean FireRed build passed with make/wrapper exit **0/0**; its ROM, ELF and link map match the independently recorded incremental build byte for byte. [Build report](b2-build-report.md).

The bounded native travel/save checks are complete: ten final-014 round trips, the house visitor interaction, and normal save/full-quit/cold-Continue cycles in New Bark and returned Pallet passed. The [native results](b2-native-results.md) own the executed outcomes and saved-state comparisons; the [B2 gate](b2-gate.md) stops further work for owner review. The natural FireRed opening was executed on 013 before the two NPC graphics corrections, rather than repeated on 014. This asset notice does not treat compilation or retained opening source as a new gameplay test.

The [frozen 010 handoff](b-to-c-010-handoff.md) remains unchanged. C should retain that inventory and identify 014 as a separate candidate. This notice requests a targeted dependency update, not a restart of unrelated art work or unchanged tests.

## Candidate identity

| Item | Exact local identity |
|---|---|
| Source commit | `167aa6d537b109bb229c231ddce4616974c4da71` |
| Complete local patch | [0014-firered-b2-travel-slice.patch](../patches/0014-firered-b2-travel-slice.patch) |
| Patch SHA-256 | `4260edec61faf85a04e62744f9d5424dbc25cfa37d3bacda54e65d4df69684d1` |
| ROM | [_local/artifacts/b2-04-firered/pokefirered.gba](../_local/artifacts/b2-04-firered/pokefirered.gba), 33,554,432 bytes |
| ROM SHA-256 | `8980ba9dced4586dda2450ea102789a4ac8bf4da731f3a8c07db18a0a41ab9f2` |
| Build/configuration manifest | [_local/artifacts/b2-04-firered/manifest.json](../_local/artifacts/b2-04-firered/manifest.json), SHA-256 `385a5330782851a65c43683fe01d86743fc79180e9d442ea52705ed5200c614b` |
| Patch/configuration fingerprint | `b00748064970a4f7d83e49a95cd937db4164538ff382601edd5dcb3f228db3a9` |
| Effective configuration | `GAME_VERSION=FIRERED`, `MAP_VERSION=firered`, `MODERN=1`, `TEST=0`, `DEBUG=0`, `RELEASE=0`, `LTO=0`, `O_LEVEL=2`; full flags and configuration-file hashes are retained in the manifest. |
| Source authoring tree | `_local/worktrees/b2-slice-dev-firered/` |
| Final clean build source | `_local/worktrees/b2-04-firered/` |
| Build result | **PASS — EXECUTED: compilation only**, make/wrapper exit `0/0`; native acceptance is reported separately. |

Patch 014 is complete against the pinned upstream commit and includes the prior 010 repairs. Apply it alone, rather than stacking the numbered patches. The manifest retains source/configuration fingerprints, the applied patch, generated/source diffs, toolchain identity and actual commands. Source art remains in ignored local checkouts; this notice does not copy or publish those inputs.

The preserved 013 [build manifest](../_local/artifacts/b2-03-firered/manifest.json) records ROM SHA-256 `4989dadd96a19b3083d89722c25ed4ff48bd122edafe29221c76a84e0a921c9d`. Its missing-guide defect is documented in the private [actual-ROM diagnosis](../_local/evidence/b2/travel-audit/013-missing-npc-diagnosis.json): both selected HnS NPC graphics slots were NULL in the FireRed target. Candidate 014 changes only those two new FireRed event selections to existing functional FRLG guide/visitor art; original HnS events are retained. The failed 013 is not the candidate for C qualification.

Artifacts, source checkouts, native saves and private evidence remain local and ignored. No publication or remote write is authorized.

## Map and event dependencies

The generated 013 constants establish these IDs; 014 changes only two FireRed NPC graphic selections and preserves the map/layout selection:

| Selected map | Group / map | Layout | Dimensions |
|---|---|---|---|
| `PalletTown_Frlg` | 68 / 0 | Existing Pallet layout | 24 × 20 |
| `NewBarkTown_hns` | 0 / 0 | `LAYOUT_NEW_BARK_TOWN_HNS = 965` | 30 × 39 |
| `NewBarkTown_House1_hns` | 1 / 2 | `LAYOUT_NEW_BARK_TOWN_HOUSE1_HNS = 966` | 13 × 10 |

Only the two named HnS maps/layouts join the FireRed selection. Their original block/border inputs and HnS layout format are retained. Kanto/Sevii ordering is preserved by the generator; the B2 build report owns its full retention and budget evidence.

Pallet gains object 4, `LOCALID_B2_PALLET_GUIDE`, at (10,12), elevation 3. Its original three objects, opening callbacks and Oak/starter scripts remain. The FireRed-only guide reads existing `FLAG_SYS_POKEMON_GET`, presents `DEVELOPMENT TRAVEL / Visit NEW BARK TOWN?`, and on Yes warps to (5,23). Declining or lacking a starter releases control without travel.

For FireRed, New Bark has an empty callback table, one return guide at (5,22), and one House1 entrance at (4,21). HnS campaign triggers, route connections, other buildings/test warps and rewards are excluded from this selected slice. The return guide asks `DEVELOPMENT TRAVEL / Return to PALLET TOWN?` and warps to Pallet (10,13). House1 has an empty callback table, one unflagged visitor at (5,4) with harmless dialogue, and exit (4,8) to New Bark's selected warp 0. Original HnS event/script branches are retained.

FireRed appends `MAPSEC_NEW_BARK_TOWN = 220` after unchanged `MAPSEC_NONE = 219`. Existing section IDs remain stable. The popup uses an existing theme. Johto world-map artwork, graphical placement and a Fly destination remain outside this slice; C must not infer them from the new name entry.

## Exact art dependencies affected

Paths below are relative to the candidate source directory.

| Dependency | Source inputs / symbols | C impact |
|---|---|---|
| New Bark blocks/border | `data/layouts/NewBarkTown_hns/` | Inventory retained HnS layout format, collision and palette relationships. |
| House1 blocks/border | `data/layouts/NewBarkTown_House1_hns/` | Inventory interior and door relationship. |
| Town primary tileset | `data/tilesets/primary/johto_general_hns/`; `gTileset_Johto_General_Hns` | Tiles, palettes, metatiles, attributes and animation overlays. |
| Town secondary tileset | `data/tilesets/secondary/new_bark_town_hns/`; `gTileset_NewBarkTown_Hns` | Tiles, palettes, metatiles, attributes and blue-door metatile. |
| Interior primary tileset | `data/tilesets/primary/johto_building_hns/`; `gTileset_Johto_Building_Hns` | Tiles, palettes, metatiles and attributes. |
| Interior secondary tileset | `data/tilesets/secondary/house_lab_hns/`; `gTileset_House_Lab_Hns` | Tiles, palettes, metatiles and attributes. |
| Guide/visitor sprites | `OBJ_EVENT_GFX_FAT_MAN_FRLG`, `OBJ_EVENT_GFX_WOMAN_1_FRLG` | Both guides reuse existing FRLG Fat Man art; the visitor reuses existing FRLG Woman 1 art. No HnS NPC graphics import or replacement art requested. |
| One animated blue door | `METATILE_NewBarkTown_Door_Blue_Hns`; `graphics/door_anims/cerulean_hns.4bpp` | Eight palette-index entries use palette 7; frame selection follows HnS layout format. |
| Actual town animation | `InitTilesetAnim_JohtoGeneral`; `src/tileset_anims.c`; `johto_general_hns/anim/` | Flower has five frames; sand/water edge eight; water-current/land-water-edge five source frames including the waterfall slice. |

The original animation callback/frame data is retained. Its upstream land-water-edge queue is empty; B2 does not claim that every original animation effect is active or repaired. Door appearance and animation overlays need validation against the selected runtime. No new art package or placeholder asset is introduced.

New Bark's ground, trees, buildings and the House1 interior use these HnS tilesets. The player remains FireRed's trainer, and the development guides/visitor use the existing FRLG sprites listed above. Runtime time/palette treatment can change their displayed colours; that system remains B's responsibility and is not an art replacement.

## Targeted validation and ownership

C may extend its isolated inventory for these two layouts, four tilesets, two reused FRLG NPC graphics and one animated door. Relevant art checks are town/interior rendering, tile and palette references, animation overlays, the house door, and return rendering in Pallet. Shared object-graphics replacements should be checked only against their actual uses and proposed changes. This dependency notice itself authorizes no replacements.

For candidate 014, the [targeted generated-data check](../_local/evidence/b2/travel-audit/014-npc-generation/verification.json) executed eight tool commands and fourteen comparisons: the selected FireRed NPC graphics are valid and the two maps' HnS/LeafGreen header, event and connection outputs match the 010 baseline. The broader map/layout/ID-retention suite was executed on 012; carrying that evidence to 014 follows the recorded narrow 012→013→014 source deltas. Final 014 HnS/LeafGreen ROM builds and their new native playthroughs are **NOT RUN**; the build report qualifies the retained earlier HnS evidence. No asset regression is inferred to have passed from these source/generation checks.

B retains save integrity/layout, campaign behavior, runtime time/palette systems, engine budgets and final integration. C retains its isolated inventory, art packages, replacements and art validation. Broader runtime/save acceptance is B's work. Unrelated maps/assets and unchanged tests need no restart; future notices must identify the exact changed dependencies or assumptions.

The prototype adds no persistent fields, regional badges, quests, second starter, one-time rewards or campaign initializer. It uses existing location and trainer/collection fields. The [final ARM ABI comparison](../_local/evidence/b2/save-audit/compiled-b2-04/actual-b2-abi-comparison.json) records unchanged save sizes/offsets against 010; the sector/checksum system and capacity assertion remain unchanged. The four-byte FireRed margin, roamer fidelity defect and SaveBlock3 integrity limitations remain open. Static linked ROM grows by 85,248 bytes against 010; EWRAM/IWRAM usage is unchanged, while runtime peak memory remains unmeasured. No retail, 010 or personal-save migration compatibility is claimed. Independent Johto progression, production unlocks, multiplayer and Discord remain outside B2. Workstream A is untouched.

## Prototype access instructions — not a test result

Use the final 014 ROM identified above in desktop mGBA **0.10.5**, with a fresh isolated save directory and automatic save-state restoration disabled. Controls in B's recorded setup: arrows move, **X = A**, **Z = B**, **Return = Start**.

1. Start naturally in FireRed and receive Oak's starter. Find the added guide west of Oak's lab at (10,12); stand south at (10,13), face up and press X. Select Yes for development travel.
2. Arrival in New Bark is (5,23). Move left to (4,23), up to (4,22), then up through the House1 door at (4,21).
3. House entry is (4,8). Walk north along x=4 to (4,4), face right and press X to speak to the visitor at (5,4). The chair at (5,5) blocks the earlier south-side approach. Walk south along x=4 and exit through (4,8).
4. Stand at New Bark (5,23), face up and speak to the guide at (5,22). Select Yes to return to Pallet (10,13).

These instructions do not substitute for executed gameplay or normal save/cold-reload evidence. B stops at the B2 review gate; no automatic B3 or further content import follows this notice.

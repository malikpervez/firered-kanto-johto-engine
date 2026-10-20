# Workstream C dependency notice — first Johto quest prototype

**October 13, 2026: final `0022` B3 build PASS; bounded native quest, reward, normal Save/cold Continue and return to Kanto PASS — EXECUTED.** Source/generated metadata inspection is complete. The first fresh `0020` build failed with exit 2 on an undefined clerk graphics symbol. Frozen `0021` corrected that identifier and built successfully. `0022` fixes the displayed Johto map names and popup-theme bounds; its make/build and wrapper both exited 0 using the retained isolated target tree. These are resumed builds, not new clean builds. Separate clean `0021` and `0022` reproductions have not run. The owner's latest direction prioritizes a small playable merged-game step. The bounded outcome is Elm → Route 29 → Cherrygrove guide → Elm, with the same FireRed trainer and a one-time Potion reward. See [the prototype requirements](b3-johto-prototype-requirements.md), [build/results record](b3-johto-prototype-results.md) and [quest state contract](b3-johto-quest-state.md). Other selected interiors, services and broad art checks have not been played through.

C's [frozen 010 handoff](b-to-c-010-handoff.md) remains unchanged and remains its initial inventory baseline. This notice does not replace that package, request unrelated art work, or require unchanged tests to restart. It extends [the B2 map dependency notice](b2-c-dependency-notice.md) and [the save-foundation notice](save-foundation-c-dependency-notice.md). B/C ownership remains governed by [the coordination contract](b-to-c-coordination.md). No C workspace was opened or modified, and no message was sent to C.

## Source and configuration identities

All three candidates use upstream commit `167aa6d537b109bb229c231ddce4616974c4da71`, source Git tree `894cb396da56fbf8054a95ebf864dc74b7b6b4c6`.

| Candidate | Complete patch / exact identity | FireRed output or qualification |
|---|---|---|
| C's frozen 010 | `0010-firered-fresh-monotype-default.patch`; SHA-256 `3e9b6b003557cbfacff59706ad04e4f7f2fdd58bc6162be995f91dc09742d5f3` | ROM SHA-256 `3e504731d9dd3c02ec273dc257c86f557caaf8c9b933d2f0ff73558c2e121a39`; handoff manifest `7114ef93633999129770b056a2dacccb26bd351e3f4abb4d13e82f0a24eac9e8` |
| Frozen save foundation final05 | `0019-firered-save-caller-completion.patch`; SHA-256 `b398435b7ca39164a0bcc935579fcccb3fd465db1d4d28418b418fc6be612b46` | ROM SHA-256 `97eb56f51e542eea6a324d59c0c33d4e3b6b91858714174c23ce2db490004f76`; manifest `d390054ca75497a773b51e4a9a49f708d452ccd0e1d828468edfc2b0f971800a` |
| First B3 source freeze | [Complete `0020` patch](../patches/0020-firered-johto-errand-prototype.patch), 204,428 bytes; SHA-256 `35f8f369ec975bd0b1bd4d5bd31f36e56f3e5d23163a612ce2c92dc370e5bd89` | Source apply-check exit 0; fresh build exit 2, retained failure evidence |
| Clerk-corrected B3 freeze | [Complete `0021` patch](../patches/0021-firered-johto-errand-clerk.patch), 204,419 bytes; SHA-256 `468007f14ceffa9683a4b9ea277803ab97527d74337751524b018239ed4ad442` | Source apply-check exit 0; resumed build exit 0; ROM SHA-256 `e6904e926c72c9e39a9c1f6560c03745c2570d247e46c905da29031cdc1abc1e`; retained historical candidate |
| Final current B3 freeze | [Complete `0022` patch](../patches/0022-firered-johto-map-labels.patch), 204,619 bytes; SHA-256 `a22ab3754f92763e97c724ccd918c6fc34af200d38afbd7f89eb378220745e84` | Source apply-check exit 0; resumed make/build and wrapper exit 0; ROM SHA-256 `39b023532a1cd657633970777ca108b74382b1239d197756a36a32c8fcd1bd91`; bounded native qualification in the results record |

The [first B3 source freeze](../_local/evidence/b3-johto-01/source-freeze-01.json) has SHA-256 `1a69fcd23dcd9f28e9d6b4e4eb3194279bd7a084e9ffdfe5b18a0a7a44f0d111`. The [clerk-corrected freeze02](../_local/evidence/b3-johto-01/source-freeze-02.json) has SHA-256 `419c5a67c39686e3aa82a8ac2459eb493ad510b270cb40172fb9fbca29be852f`; its only `0020` → `0021` source difference is `data/maps/CherrygroveCity_Mart_hns/map.json`, now SHA-256 `1b0ce8358d0852dd2f39df8ac17292a678d9a590823965905b90fb23e5321e93`. The [final freeze03](../_local/evidence/b3-johto-01/source-freeze-03.json), SHA-256 `4e1b9dfb5b2476664226d59f6152b1e735278c01ce25b8b2e60bafb9ee8f3b4d`, binds all 96 current source hashes and proves only `src/region_map.c` and `src/map_name_popup.c` changed from `0021`. Apply the current complete patch alone to the pristine commit; do not stack complete patches. Final05 and 010 remain frozen historical candidates.

The retained [b3-02 manifest](../_local/artifacts/b3-02-firered/manifest.json), SHA-256 `3fc40df886ff93b974aea18d374f77259d83b301db47c777b0e9f67c01c51ae1`, binds the clerk repair. The final [b3-03 manifest](../_local/artifacts/b3-03-firered/manifest.json), SHA-256 `99c720a30954e8ecaa716d9d4afa8d1e5286a1c68a0a26856b461aa8857dcfd2`, binds both retained earlier attempts, the exact two-file correction, configuration and real exits. Local final outputs are [_local/artifacts/b3-03-firered/pokefirered.gba](../_local/artifacts/b3-03-firered/pokefirered.gba), [ELF](../_local/artifacts/b3-03-firered/pokefirered.elf) (SHA-256 `8f67a13d2f3352f07594708ce18783b9646076fcbe45a36a411a84e7d5d29e00`) and [linker map](../_local/artifacts/b3-03-firered/pokefirered.map) (SHA-256 `bc8dbe30c04cd87c8745dbd32f3301041428f4bcfd75e4b97658713cc0faacc8`). The independent clean `0022` reproduction command in B's build/results record is prepared, **NOT RUN**.

The [executed B3 configuration query](../_local/evidence/builds/b3-01-firered-firered/configuration.log) exited 0 and selects `BUILD=firered`, `GAME_VERSION=FIRERED`, `MAP_VERSION=firered`, title `POKEMON FIRE`, code `BPRE`, and output `pokefirered.gba`. It uses locked ARM GNU 14.2.1, `MODERN=1`, `TESTING=0`, `-DFIRERED`, optimization `-O2`, with debug/test/release/LTO all 0. `Makefile` and `map_data_rules.mk` are byte-identical to final05. The successful resumed build uses this same effective configuration, recorded in its final manifest.

## Maps and existing asset bytes

The FireRed-only selection in `tools/mapjson/mapjson.cpp` now contains **11 HnS maps in total**: the two B2 destinations plus **nine newly selected maps**. The [executed generator/static metadata audit](../_local/evidence/b3/world-integration-01/metadata-audit.json) passed; map/layout ID headers are byte-identical to the existing baseline, selected connections are reciprocal and interior destinations remain within the bounded world. Original HnS map properties and layout binary inputs are preserved. The following table records actual B3 source JSON and generated constants. Native gameplay covered the town/lab/Route29/Cherrygrove quest path and Kanto return, not every listed interior.

| Selected map directory under `data/maps/` | Change from final05 | Group / map | Layout ID | Tiles across / down | Primary / secondary key below |
|---|---|---:|---:|---:|---|
| `NewBarkTown_hns` | Existing map; adds lab warp, Route 29 connection and lab sign | 0 / 0 | 965 | 30 / 39 | General / NewBark |
| `NewBarkTown_House1_hns` | Existing B2 destination | 1 / 2 | 966 | 13 / 10 | Building / HouseLab |
| `NewBarkTown_Lab_hns` | Newly selected | 1 / 0 | 968 | 40 / 14 | Building / HouseLab |
| `Route29_hns` | Newly selected | 0 / 11 | 1010 | 70 / 32 | General / NewBark |
| `CherrygroveCity_hns` | Newly selected | 0 / 1 | 826 | 65 / 42 | General / Cherrygrove |
| `CherrygroveCity_PokemonCenter_hns` | Newly selected | 2 / 0 | 831 | 16 / 10 | Building / Center |
| `CherrygroveCity_Mart_hns` | Newly selected | 2 / 1 | 830 | 14 / 9 | Building / Mart |
| `CherrygroveCity_House1_hns` | Newly selected | 2 / 2 | 827 | 13 / 10 | Building / HouseLab |
| `CherrygroveCity_House2_hns` | Newly selected | 2 / 3 | 828 | 13 / 10 | Building / HouseLab |
| `CherrygroveCity_House3_hns` | Newly selected | 2 / 4 | 829 | 13 / 10 | Building / HouseLab |
| `Gate_Route29_Route46_hns` | Newly selected; returns to Route 29 | 22 / 0 | 879 | 15 / 12 | Building / Gate |

These are existing upstream HnS background assets, including a center tileset whose upstream name contains `Kanto`. The name does not make the center background FireRed art. Selected layouts retain `layout_version=hns` / runtime layout version 2. No new map blockdata, border, graphics, palette or tileset asset bytes appear in either complete B3 patch. `data/layouts/layouts.json` and `data/maps/map_groups.json` are byte-identical to final05; the patch changes selection, bindings and FireRed-specific event/script definitions.

Eight existing tilesets are used: **two primary and six secondary**. Four were already selected by B2/final05; four secondary sets become FireRed dependencies here.

| Key | Upstream tileset source directory | Exact tileset symbol | FireRed dependency change |
|---|---|---|---|
| General | `data/tilesets/primary/johto_general_hns/` | `gTileset_Johto_General_Hns` | Existing; now also used along Route 29 and in Cherrygrove |
| Building | `data/tilesets/primary/johto_building_hns/` | `gTileset_Johto_Building_Hns` | Existing; additional interiors |
| NewBark | `data/tilesets/secondary/new_bark_town_hns/` | `gTileset_NewBarkTown_Hns` | Existing; also Route 29 |
| HouseLab | `data/tilesets/secondary/house_lab_hns/` | `gTileset_House_Lab_Hns` | Existing; lab and Cherrygrove houses |
| Cherrygrove | `data/tilesets/secondary/cherrygrove_city_hns/` | `gTileset_CherrygroveCity_Hns` | Newly selected in FireRed |
| Center | `data/tilesets/secondary/kanto_pokemon_center_hns/` | `gTileset_Kanto_PokemonCenter_Hns` | Newly selected in FireRed |
| Mart | `data/tilesets/secondary/johto_mart_hns/` | `gTileset_JohtoMart_Hns` | Newly selected in FireRed |
| Gate | `data/tilesets/secondary/gate_standard_hns/` | `gTileset_Gate_Standard_Hns` | Newly selected in FireRed |

The new bindings are FireRed-only blocks in `src/data/tilesets/{graphics,headers,metatiles}.h`. They use existing compressed tile inputs, metatile/attribute binaries and palettes. The Center binding references palettes 00–15; the other newly selected secondary bindings reference 00–12. These selections are dependency facts, not a claim that every palette/animation renders correctly in the new FireRed maps.

## Actors and runtime assumptions affecting art validation

This prototype uses existing FRLG/shared actor art on the HnS backgrounds. Elm is represented by `OBJ_EVENT_GFX_SCIENTIST`, not an imported HnS Elm sprite. No HnS NPC graphics were newly imported.

| Role / map | Selected graphics identity | Placement or art assumption |
|---|---|---|
| Elm, lab | `OBJ_EVENT_GFX_SCIENTIST` (282) | (6,3), local ID `LOCALID_B3_ELM`; existing `graphics/object_events/pics/people/scientist.4bpp` |
| Guide, Cherrygrove | `OBJ_EVENT_GFX_GENTLEMAN_FRLG` (331) | (57,8), `LOCALID_B3_GUIDE`; also a Route 29 directions actor and Center visitor |
| Northern road actors | `OBJ_EVENT_GFX_HIKER_FRLG` | Cherrygrove (33–35,1); gate (7,1); text explains the bounded route |
| Travelers / house visitors | `OBJ_EVENT_GFX_YOUNGSTER_FRLG`, `OBJ_EVENT_GFX_FAT_MAN_FRLG`, `OBJ_EVENT_GFX_WOMAN_1_FRLG` | Existing actor art; new event locations and dialogue in Route 29, Mart and houses |
| Center nurse | `OBJ_EVENT_GFX_NURSE_FRLG` (333) | (7,2); invokes existing FireRed nurse script |
| Mart clerk | `OBJ_EVENT_GFX_CLERK` (290) in corrected `0021` | (2,3); existing FRLG clerk art. Initial `0020` used an undefined `OBJ_EVENT_GFX_POKEMART_CLERK`; the corrected identifier uses the existing graphics contract without adding art bytes. |

The actors above use existing 16×32 object frames and standard animation tables. Their existing palette contracts remain: white NPC palette / `PALSLOT_NPC_4` for scientist, gentleman, hiker, fat man and clerk; green / `PALSLOT_NPC_3` for woman; blue / `PALSLOT_NPC_1` for youngster; pink / `PALSLOT_NPC_2` for nurse. These are the existing slot symbols. The 16-active-object engine limit remains. Map JSON currently declares at most four NPC objects in one selected slice map; that count is not a measured runtime object/palette peak.

The FireRed branches select empty campaign callbacks and explicit safe event sets, while retaining upstream HnS definitions for the HnS target. New Bark ↔ Route 29 ↔ Cherrygrove has explicit reciprocal connections. Interior exits return to the selected town/route; Route 30 and Route 46 connections/exit warps are absent from the FireRed selection. Cherrygrove's guide interaction is a short request checkpoint, not the original HnS guided tour. Elm does not grant a second starter or start the original HnS opening.

Route 29's existing encounter table gains a FireRed selection guard. Time-specific HnS opening/callback behavior is not thereby imported. New display sections append Route 29 and Cherrygrove after B2's New Bark name; this does not establish a Johto world map, Fly network or final travel unlocks. In final `0022`, FireRed's map-name lookup admits the Route 29 and Cherrygrove IDs, and all three appended Johto sections use the existing Littleroot wood popup theme instead of legacy out-of-range theme indexes. That two-file runtime display correction adds no popup graphics, palettes, map IDs, save/content revisions or quest changes. Only the affected map names and popup presentation need a targeted check when adopting `0022`; source-art inventory and unrelated checks remain reusable. C should use B's current script/region assumptions for this slice, rather than assuming that selecting an HnS background imports its original campaign.

`src/field_door.c` and `src/tileset_anims.c` are byte-identical to final05. The existing B2 blue-door dependency (`graphics/door_anims/cerulean_hns.4bpp`, palette 7) and Johto General animation hook continue to apply. The four added secondary tileset headers have `callback = NULL`. No new door hook, animation repair, day/night implementation or palette-system redesign is included. Check the actual new doors and transitions before integrating replacements; do not infer animation support from a matching-looking tile.

## Save fixtures, budgets and targeted C work

B3 writes content ID 2 using the existing native version 6, `FRJS` schema 1 and layout 1. Strictly blank content-1 final05 saves are accepted as inputs; a normal compatible write advances the content identity. Quest state uses already allocated Johto event bits 0–2 and variable 0. Old ROMs may reject progressed content-2 saves, so C must keep ROM/save pairs isolated and use only B-provided copies for this slice. No C save migration or implementation is requested.

The save-format allocation remains unchanged: FireRed SaveBlock1 15,868 bytes with **four bytes of capacity headroom**, SaveBlock2 3,892, SaveBlock3 1,332, and a **256-byte in-format reserve kept zero**. The 292 bytes outside the allocated format are uncommitted. The [source-preservation record](../_local/evidence/b3-johto-01/layout-source-preservation.json) binds unchanged native structure/save-coordinator sources to final05.

The actual final B3 link uses **254,488 EWRAM bytes and 25,940 IWRAM bytes**, identical to final05; linked EWRAM headroom remains 7,656 bytes. Linked ROM content is **29,995,300 bytes**, an increase of **48,368 bytes** over final05's 29,946,932 and **32 bytes** over `0021`; the output stays padded to 32 MiB. These are linker totals, not runtime memory peaks. Runtime quest/save observations now cover the single native journey and rewarded cold reload described above. Final05's measured 9.63-second full save is not a B3 measurement. Four-byte headroom, roamer fidelity, Hall-of-Fame special-sector behavior and release compatibility remain open.

For C's later adoption of this B baseline, only the changed dependency closure needs work:

- Extend the inventory mapping for the nine newly selected layouts and four newly selected secondary tilesets. Existing source-asset inventories from the frozen 010 HnS target may be reused when their exact input hashes match.
- Check tile attributes/collision, layer priority, palettes, water/edge animations, actor frames/palette sharing, door appearance and enter/exit placement in these maps. Preserve earlier unchanged Kanto, New Bark and House1 evidence; repeat a check only where the new dependency or test setup affects it.
- Use the Elm/guide positions and short quest phases as new visual fixtures. The prototype actors are current engine dependencies, not a request that C redraw Elm or any unrelated character.
- Bind any candidate replacement package to the current `0022` source freeze, b3-03 build manifest, generated IDs and ROM hash above, or to an explicitly supplied later baseline and its impact notice. New code bindings and different compressed output addresses do not invalidate unchanged source-art hashes.

C's isolated packages and unrelated art work continue. B owns saves, quest/campaign behavior, runtime time/palette systems, engine budgets and integration. This notice grants no asset integration or publication, C repository modification, remote write, CI, NAS/network change or Workstream A change. B stops at the bounded playable prototype review gate.

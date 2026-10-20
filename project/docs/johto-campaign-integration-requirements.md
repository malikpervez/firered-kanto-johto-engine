# Kanto Champion to Johto campaign

## Story review images, scripts and dialogue — October 15, 2026

The owner requires images of story events alongside their associated scripts and dialogue in future story updates. Each added or meaningfully changed event must have a readable review entry containing:

- Event ID/name, map/location and trigger prerequisites.
- Actual in-game screenshots of the relevant staging, dialogue, reveal or encounter. Use a short sequence when a single image cannot show the event, including restoration/aftermath where applicable.
- A clickable source-file reference with the relevant script label, plus the exact implemented dialogue in textbox order. Show player choices and their resulting dialogue/behavior, distinguishing implemented text from earlier writing drafts.
- Exact build identity and executed check status. Identify staged diagnostic prerequisites and retain the original build label when reusing unchanged evidence. If a scene or branch has not been executed or captured, mark it `NOT RUN`/image pending and provide its script/dialogue without implying visual acceptance.

Present images directly in the owner-facing review, grouped with the corresponding event text and script references. Store screenshots, clips and private review pages under ignored `_local/` paths; use absolute local paths for embedded images and do not commit or publish them. Source previews/mockups may be supplementary if explicitly labelled; they do not replace actual gameplay captures. Capture the changed events efficiently without restarting unrelated campaign tests. This presentation requirement adds no authorization for game changes, other-workstream access or publication.

## Natural outdoor journey — current owner direction

The owner now requests that the post-Champion journey be part of the story, using New Bark's original waterfront and Surf approach. Retain Oak's actual Hall-of-Fame invitation, repeatable lab directions, the native Kanto game-clear gate and Elm's established visiting-Champion introduction. Credits and the original Pallet return remain intact. Construction workers block the western Indigo road before the Kanto Championship and finish afterward. The player then follows the signed outdoor road west and downhill to Route27's western shore, Surfs west across its original water connection and lands in New Bark.

Reuse the existing western-pass map identity as an outdoor road, with a separate appended FireRed-only layout and original pinned terrain art. Replace the two cave entrances/warps with an open trail and a dry coastal descent; preserve all earlier map/layout IDs and unrelated warp/event prefixes. New Bark's geometry and original eight warps are restored; its original eastward water connection supplies the actual arrival. Workers use the existing native game-clear flag as their hide condition. The officer's first-visit scene initializes the existing Johto state once and gives directions. Repeat trips retain progress. The Pallet guide's optional quick return is available only after Elm's introductory errand has been accepted. No new persistent field, flag, item, HM grant, capacity change or party reset is required.

Route27 receives only a guarded western dry descent and reciprocal north connection; its water, existing connections, warps and actors remain. Routes26, Tohjo Falls and Johto's later League approach retain their current geography and quest/HM gates. Route27's late FirstSteps/Baoba scripts defer until Johto's eighth badge; early arrival must not run their later story effects. Surf uses the trainer's earned native Soul Badge and existing known-move/owned-HM learner rules. Shared path art and incoming connection buffers must be qualified using actual provider/frame/attribute bounds. Corresponding regional foliage may change art at the boundary; do not claim identical glyphs or palettes where they differ.

Use isolated checkpoints to test the closed gate, actual Oak referral scene, outdoor connections, first Elm handoff, repeat travel and an ordinary save/cold reload. These are staged entry points into real scripts; they do not establish natural League victory or full campaigns. Results belong in `docs/natural-johto-journey-results.md`. Existing save and Workstream A/C/publication boundaries remain unchanged.

## Preserved candidate26 western-pass direction

The owner requests a scripted post-Kanto Championship journey west from Indigo Plateau into New Bark Town. Oak's Hall-of-Fame referral and repeatable lab directions must identify this route. First Johto entry uses a new short, walkable League pass; the Pallet guide gives directions before that entry and retains optional quick return travel afterward.

Use the native Kanto `FLAG_SYS_GAME_CLEAR` as the entry gate. Initialize the existing Johto campaign container once before loading New Bark, then let the original adapted Elm research introduction run. Preserve trainer, party, collection, resources, Kanto/Sevii progress, separate rivals and independent regional badges. Entry failure returns safely to Indigo without entering Johto. Repeated travel and cold reload must retain the existing Johto state.

Append one FireRed-only map using an already compiled east/west gate layout, with small explicit, authentic cave entrances and dry approaches in the two existing outdoor maps. Preserve all prior map/layout IDs, original warps, actors and connections. Routes26/27, Tohjo Falls and the separate Johto League approach retain their existing geography and story gates; the new route does not grant Surf, Waterfall or late Johto progress.

The owner also explicitly authorizes isolated diagnostic saves that place test characters at selected maps and story checkpoints. Use immutable B-owned source saves, exact-build offsets/map bindings, valid ordinary-save checksums and manifests declaring every staged change. These checkpoints support targeted native tests; they do not establish natural campaign reachability or a full playthrough. Personal saves remain untouched.

Implementation/build/native results for this change belong in `docs/indigo-west-pass-results.md`. Physical save6/FRJS1/content3/layout1, protected reserve, capacity assertions and all Workstream A/C/publication boundaries remain unchanged.

## October 14 follow-on authorization

The latest priority is full integration of HnS's redesigned Kanto maps and ambient Pokémon. There is one playable Kanto before and after Johto. Reuse the pinned HnS visual layouts/resources in native FireRed maps while retaining FireRed's campaign, map identities, Sevii content and independent Johto progression. HnS's later-Kanto story/world changes do not create a second Kanto or replace Giovanni, Pokémon Tower, Silph's Rocket sequence, Cinnabar's original content or the SS Anne.

Completion for this priority requires:

- A disposition for every157 HnS Kanto map and21 shared border/League maps, with explicit native counterparts and adaptations for renamed, merged, uncertain or story-conflicting areas. The initial inventory listed20 shared maps; the subsequent source correction adds the actual Johto-tagged HnS Route23 donor. Preserve that original inventory and its correction evidence. A matching name is not evidence of compatible geometry.
- Actual redesigned geometry/resources in the applicable native maps, plus all appropriate cosmetic ambient actors. Preserve native story actor order/IDs, scripts, flags, rewards, trainer identities and warp destinations. Original HnS battles and item rewards are separate from cosmetic ambient imports.
- Correct collision/elevation, doors/stairs, reciprocal connections, movement paths, event triggers, hidden-item/sign positions and external Fly/healing/return destinations. Connected-map tile namespaces must agree; a partial layout swap cannot leave a broken seam.
- The existing physical save6/FRJS1/content3/layout1, sector/checksum system, capacity assertions and protected256-byte reserve remain unchanged. Test fresh isolated saves for redesigned builds: stable IDs alone do not establish compatibility with older saved coordinates, actor templates or map-view data. No personal-save conversion is included.
- Reproducible frozen source/build/configuration fingerprints, linked budgets, asset provenance and a local B-to-C change notice. Reuse pinned resources; do not modify C's workspace or restart unrelated art validation.
- Source-wide deterministic map/event/topology checks and focused native rendering, interaction, boundary and normal-save/cold-reload checks. The extended campaign playthrough remains deferred. Compilation/source previews do not count as executed gameplay.

The first implemented batch uses the HnS layouts for the player's two Pallet house floors and the rival's house, through FireRed-only geometry overlays that retain the original layout IDs/table order. Their native Mom, PC/NES/help, Daisy/Town Map and grooming scripts remain intact. Three original NULL/flag0 ambient Pokémon are appended to native Pallet's existing actor list; its outdoor redesign is still pending the connected-map batch. This is initial progress, not completion of the whole map priority.

Shared native layout IDs must not spread an intended Kanto room change to excluded rooms or Sevii. Subsequent map-specific visual geometry uses the static map header's default pointer while keeping the original saved layout ID and global layout table. Cold Continue resolves an explicitly saved dynamic layout through the existing table; restoring the default restores the selected map's own header geometry. Preserve native metatile interactions that grant features, including Mart questionnaires/Mystery Gift; physical actor/door checks alone do not establish those interactions.

The current prototype retains separate Kanto and Johto League approach/scenes for their independent battles/progression, including the selected HnS Route22/Route23/Indigo chain. It does not select a second complete HnS Kanto town network or later-Kanto campaign. Preserve those explicit shared-border dependencies while adapting the one native Kanto; do not confuse duplicate source datasets with runtime map-ID collisions. Terrain collision, roof-layer occlusion and connection tile namespaces require their own content adaptations.

Full catalog asset copying currently exceeds the linked ROM margin: the source-only15 estimate is461,372 additional bytes before map/script/alignment overhead against207,644 free. First qualify lossless byte reuse and replacement of superseded geometry with stable IDs and explicit shared-consumer protection. Do not cut gameplay/art/species or expand cartridge/save capacities to evade this budget. This estimate does not establish an executed final link failure. Candidate16 adds only320 ROM bytes and retains the RAM/save budgets.

Latest owner steering stops extended campaign gameplay and asks for the remaining HnS-to-Kanto feature inventory. Continue code-first integration with short, targeted feature checks; full natural campaign coverage is deferred, not passed. Preserve the actual completed normal-save/cold-reload evidence and all existing workstream/save/publication boundaries.

Confirmed Kanto feature gaps from the current source audit:

| HnS feature | Current Kanto gap |
| --- | --- |
| Phone contacts and trainer rematches | The retained40-row HnS table includes12 later-Kanto contacts tied to omitted HnS maps/trainers. They are not registrations for native FireRed trainers; native VS Seeker remains. |
| 16 Gym leader Dojo rematches | The HnS Saffron Dojo/VIP venues are not compiled into the merged world, and native Saffron does not offer their rematch entry scripts. |
| Kanto radio expansion and Hoenn Sound encounters | The radio upgrade still depends on the omitted Machine Part quest/director grant. Hoenn Sound encounter bias is also still HnS-only; native encounter content has not been expanded to its rare Hoenn distribution. The Pokégear itself is retained and can be opened in Kanto after its Johto registration. |
| Headbutt encounters on Kanto trees | The existing interaction explicitly requires an imported Johto map; native Kanto tree hooks have not been added. |
| Voltorb Flip access in Kanto | Goldenrod retains the original game; native Celadon still offers its original slot machines. |
| Broader time-specific encounters | Seven native routes have added Night tables. Other native routes/areas and morning/evening encounters retain the original daytime fallback. |

Already shared/source-enabled systems include followers, day/night lighting and clock, AutoRun/FastSurf, individual Surf sprites, HM learner assistance, quick run/catching, the modern battle/options systems and shiny indicators. The feature pass also adds the post-League GB Player gift/music mappings and initialized Johto Mom-account carry-over. These source facts do not turn unexecuted runtime cases into passes. Johto's Kurt berry-ball crafting, Bug Contest and bedroom decorations remain Johto activities; HnS uses berries instead of apricorns. A separate source-confirmed Fly-helper eligibility bug remains open: the ordinary Party shortcut can offer Fly from learnability before the player owns HM02 or knows the move. It is a repair issue, not an absent Fly feature.

After the candidate 05 local handoff, the owner authorized HnS features in Kanto, followed by end-to-end campaign testing and continuation through available usage resets. This supersedes the earlier deferral of extra Kanto features. Workstream A/C, local-only publication rules, physical save-layout/capacity limits and protected baseline evidence remain unchanged.

The first implementation adds conservative HnS-derived night encounters to seven native Kanto routes, retaining every original daytime table, encounter rate and slot level. Existing day/night lighting, clock, followers, AutoRun/FastSurf and HM learner support are inventoried as already active. A follower-toggle write notice and option-confirmation notice preserve the approved save coordinator's handling of existing settings; they add no field or option. The native Celadon programmer supplies the original GB Player only after League completion, with 13 existing Gen 2 music mappings. A foreign-species registration-number fallback covers the active HnS Pokédex before National unlock, without granting that unlock. An existing seeded/initialized Johto Mom account carries into native Kanto/Sevii, with the original savings opt-in, money and gift rules; no phone banking menu or early account is added. These additions are frozen and compiled as candidate 10. Their later runtime conditions must be reached naturally.

Candidate11 repairs carried earned Cut/Rock Smash in imported Johto obstacle scripts and recognizes their existing obstacle graphics from the FireRed Party menu. Keep native badge permissions, regional badge/receipt writers and known-move/owned-HM eligibility intact. Do not synthesize regional receipts or grant an unknown/unowned HM through a badge alone. Source/build qualification does not establish actual obstacle use; reach and test it naturally. No physical save change is included.

Candidate12 adds a FireRed-only missing-object bounds check before the field graphics lookup. Preserve valid object behavior, existing permissions, graphics and coordinates; an empty tile must return FALSE without indexing beyond the existing16-entry actor array. The compiled check has separate source/linked qualification; runtime obstacle checks remain pending. The existing save format, reserve and peer-effective source remain unchanged.

The previous end-to-end run used fresh isolated saves and ordinary emulator inputs; it is now paused under the latest owner steering. Future focused native checks retain those ordinary-input and save-isolation rules. Original campaign gates remain unchanged, including the National Dex’s60-caught prerequisite for later Sevii; no playthrough grant or fixture is substituted for natural progress. Usage is measured through the app’s account-limit tool; an available free reset may be used at the authorized10% remaining threshold. No paid credit purchase, external account change or scheduled automation is included.

October 14, 2026. **Continuous campaign implementation authorized.** The owner selected FireRed's Kanto League victory → Oak referral → Elm → the original HnS Johto story, then directed B to continue until a locally working merged game is finished. The tested0022 Elm/Guide prototype remains a frozen historical baseline. The first complete core candidate built cleanly from its frozen source; later frozen candidate 05 built incrementally and passed a short native normal-save/cold-reload check. Earlier artifact-bound opening, wild battle, healing and Mr. Pokémon/Silver/police progression have executed. The postgame unlocks connect to retained FireRed Kanto. The [current build/test record]([LOCAL_WORKSPACE]/docs/johto-campaign-build-and-test-results.md) distinguishes each candidate and pending checks. No full natural campaign playthrough is claimed.

## Player progression

1. Play the existing FireRed Kanto campaign and defeat the League/Champion normally.
2. Oak refers the trainer to Professor Elm in New Bark Town, Johto. This referral becomes available after the actual Kanto game-clear event and remains recoverable if the first conversation is interrupted or the player returns later.
3. Unlock ordinary travel to Johto after Oak's referral. The existing starter-only development travel is not the final campaign unlock.
4. Elm recognizes the visiting Kanto Champion and Oak's recommendation. Adapt the real HnS opening and its Mr. Pokémon/rival events, then continue its gym, Rocket and League progression in the usual order.
5. Keep one trainer and collection, shared party/PC/items/money/Pokédex, and independent Johto story, defeated trainers, badges and rival state. Kanto and Sevii remain playable on return.

Johto entry requires the Kanto League victory and Oak's referral. It does not require finishing Sevii, catching60 species or already receiving the National Dex. Oak's original National Dex and Sevii branches remain available under their original conditions. Referral dialogue must not replace those branches or prematurely grant their rewards.

The source-confirmed gate is **`FLAG_SYS_GAME_CLEAR` (`0x82C`)**, set by `EnterHallOfFame` in `src/post_battle_event_funcs.c` before the normal Hall-of-Fame save. **`FLAG_IS_CHAMPION` (`0x844`) is a different later-Sevii event**, set when Celio receives the Sapphire; using it would impose an unintended Sevii prerequisite. Add the referral to Oak's existing Hall-of-Fame congratulations and provide a repeatable reminder through normal Oak lab dialogue, preserving its National Dex dispatch. Do not repurpose the existing Oak scene variables that own that dispatch.

Preserve existing Pokémon levels, moves, ownership, friendship and stored collection. Do not introduce party resets, level reductions, regional caps, resource wipes or trainer recreation to make the story fit. Keep existing field permissions while defining Johto's separate badge record; any changed permission or balance policy needs an explicit product decision.

## Necessary story and dialogue adaptations

Use the existing HnS story rather than extending the custom0022 Guide errand into a new campaign. Adapt dialogue that assumes the player is a novice New Bark resident, has never met Oak, lacks a Pokédex or has no Pokémon. Keep required quest dependencies and rewards coherent. Elm's starter/research Pokémon and Silver's stolen Pokémon require a deliberate regional choice/grant rule; existing Kanto starter data cannot be reused as Johto's saved choice or silently overwritten. Shared money and the New Bark mother/phone story also need explicit adaptation that preserves the player's established identity and resources.

Draft Oak referral, for implementation after the existing post-League event's safe dialogue point:

> Congratulations, {PLAYER}! Your journey has made you a remarkable trainer. My colleague, Professor Elm, studies Pokémon in Johto. I'd like you to meet him at his laboratory in New Bark Town. I think your experience could be a great help to his research.

Draft Elm greeting:

> You must be {PLAYER}! Professor Oak told me about your victory at the Kanto League. Welcome to Johto. There is something I'd like your help investigating.

These drafts explain the intended direction. The compiled implementation uses the matching Oak referral and Elm recognition in the actual HnS research errand. Elm's Kanto-League recognition and subsequent original briefing have executed in desktop mGBA; the initial Hall-of-Fame referral has not been qualified by a natural full Kanto playthrough in this combined candidate.

## One coherent content integration

Select the Johto map network, interiors and required shared dependencies together. Preserve current generated map/layout ordering and all FireRed Kanto/Sevii selections. HnS's later-era Kanto must resolve to the chosen FireRed campaign where appropriate; importing all `game_version=hns` maps would also select duplicate Kanto and unrelated regions.

Map and script selection is only one part of the integration. Coordinate actors, tilesets, doors, encounter tables, trainer parties/rematches, callbacks, menus, regional map names, healing/blackout destinations and field permissions with the selected story. Retain the existing asset bytes and attribution where reused. Provide C a targeted dependency notice when a new baseline is frozen; its010 inventory and unchanged art work do not restart.

Adapt League approaches/Indigo, ship and Goldenrod train dependencies without clearing completed FireRed state. Verify regional classification for every newly selected map, not only New Bark. HnS's S.S. Aqua later-Kanto initializer must not run against the FireRed campaign.

## Persistent state and implementation boundaries

Use the approved native6/FRJS1/layout1 foundation and its allocated regional containers. Keep native offsets, sector/checksum/coherent-bank transaction, capacity assertions and stored reserve intact. The four-byte main-block margin remains a limit; this direction does not authorize another capacity change.

The implemented content3 mapping uses the existing allocations: 1,536 non-temporary/non-trainer event positions plus the prototype's3 bits fit2,048; 864 trainer bits plus120 rematch-readiness bits and8 step-counter bits fit1,024. The mapped239 persistent HnS variables plus the preserved prototype variable fit240 positions. Explicit shared engine/resource aliases remain native. Actual ARM measurements of the frozen clean core confirm unchanged native structures and offsets; static capacity does not establish every runtime peak or full campaign behavior.

Produce an exact logical-to-engine mapping for the reused HnS persistent flags, variables, trainer IDs, badges, rival and starter values. Separate regional story state from shared engine/Pokédex/item/temporary state. HnS and FireRed reuse numeric IDs, so a blanket redirect of every flag or variable based on map location is not sufficient. Validate each persistent mapping and every direct pointer caller before enabling it.

The0022 content2 registry accepts only its small errand states. Register and implement any broader campaign content meaning explicitly; do not make occupied prototype fields imply completed HnS events. Preserve compatible trainer/gameplay data and immutable test originals. Do not silently reset unsupported saves or broaden the three-fixture version5 conversion policy.

Keep work local and ignored where required. Workstream A and C repositories, services, dependencies, plans and credentials remain untouched. No remote writes, commits, Actions/hosted CI, deployments, automation, NAS/network changes, engine replacement, species expansion or global installation are included.

## Focused qualification

- Automated source/generated checks: selected-map and warp/connection closure, valid destinations/actors/scripts, stable IDs, regional mappings, reward/starter idempotence and asset dependencies. Run these across the integrated content rather than manually inspecting each city.
- Build: preserve the actual configuration, command, logs, exit codes, complete patch, source fingerprints and ROM/RAM totals. Resolve substantive capacity or restructuring blockers before proceeding.
- Native checkpoints: pre-League travel remains locked, post-League Oak referral, Elm's adapted opening, early rival/quest, representative gym/Rocket milestones, Johto League and return to FireRed. Test normal saves/cold reload at changed persistence boundaries and inspect retained trainer/party/PC/Dex/rival/regional state.
- Label prepared or injected diagnostic fixtures separately from natural progression. Do not call an unexecuted campaign complete. Reuse unchanged B0/B2/foundation evidence; no separate city approval gates or repeated full opening runs for unchanged code.

This is one campaign integration review, followed by later release qualification. Stop for a necessary broader save allocation, engine restructuring or loss of required FireRed gameplay; do not conceal such a change with dialogue edits or disabled errors.

## Source audit record

The initial read-only source audit used pinned commit `167aa6d537b109bb229c231ddce4616974c4da71` plus the frozen0022 source tree. It reused the B1 content inventory and produced ignored evidence in `_local/evidence/johto-campaign-direction-01/`. The following original audit records describe that initial stage; subsequent implementation, frozen sources, builds and native observations are recorded separately in the current build/test report.

The [world audit](../_local/evidence/johto-campaign-direction-01/world-audit.json), SHA-256 `fbc7a41bb0b3bc9f7445bdcc04cd1cb5840212190157de117c1de6a74f93e718`, inventories261 Johto-labelled maps, all417 selected FireRed maps to preserve, seven primary/67 secondary tileset dependencies,17 Johto heal records and152 Johto wild records. Region labels alone are not the complete selection policy: tests/outliers and dependencies need review, and duplicate later-Kanto/other-region content must not be bulk-selected accidentally. These are static inventories, not campaign or capacity passes.

The [Kanto hook audit](../_local/evidence/johto-campaign-direction-01/kanto-audit.json), SHA-256 `db07f04f6907ac3d619b44581f91f5d15287553533ba42ea10170d794062a26b`, binds19 inspected files to frozen0022. It identifies Oak's Hall-of-Fame text as the initial referral hook. The repeatable lab referral must be a conditional message-only call immediately after `faceplayer`, before the existing scene8/scene9 and National Dex branches, then return to their unchanged dispatch. Existing game-clear state supplies eligibility; this hook needs no new native flag, variable or capacity allocation. Preserve the Hall-of-Fame save/error, credits, restart and Pallet return sequence.

The [story/state audit](../_local/evidence/johto-campaign-direction-01/story-state-audit.json), SHA-256 `4da46f74bdbc70ae9cbffe4cae451a41352285803f7994be6aefa293f287658d`, binds31 source inputs. It identified the carried-party Elm/nickname path, Oak's existing-Pokédex dialogue, Silver's independent starter/name dispatch, badge/trainer/map-trigger adapters and shared challenge-setting preservation. At that initial audit stage, the documented unused variable0x40FF was a candidate for fitting the raw domain plus preserved prototype state, subject to dynamic/literal caller inspection; the later implementation selected the compact persistent-variable mapping described above. That initial read-only audit implemented no runtime mapping. HnS's mother-savings and Raikou/Entei roaming systems are genuine retained dependencies, not placeholders or removed features.


## Selected implementation decisions

The visiting Champion carries the existing party. Elm grants no second starter or Pokédex, and no nickname routine targets party slot0. Johto's independent story choice defaults to Chikorita so Silver steals Cyndaquil; its independent rival name starts as SILVER and uses the normal police naming scene. The guest-house host retains optional original savings and phone setup. Existing challenge preferences stay unchanged.

Johto state uses content revision3 inside the previously allocated regional foundation. This does not change native save version6, any ARM structure size, sector/checksum protocol, the256-byte reserve, or the native capacity assertion. Mapped story flags, trainer defeats, variables, eight badges, rival name, optional savings, two Johto dogs and40 rematch readiness values are isolated from Kanto. Legacy known content1/2 upgrades preserve the B3 state; broader compatibility is not promised.

The normal implementation path now imports the campaign in bulk, with shared helper labels and persistent operands explicitly separated from the native FireRed versions. Essential healing, phone/rematches, map/Fly and display callbacks are adapted by their actual source contracts. Small local reversible implementation choices continue without separate city gates. Workstream A/C, remote publication, physical capacity changes and privileged/network changes retain the existing boundaries.

Private source, generation and build evidence is under `_local/evidence/johto-campaign-direction-01/`. The mutable development diagnostics remain preserved separately from each complete patch, source freeze and isolated build. Candidate 05 is bound to its exact source, configuration, build and native save/cold-reload evidence. Its staged Whitney/Radio Tower reward callbacks and original Hall-of-Fame automatic-save/cold-Continue callback executed successfully; they cannot establish naturally reaching those milestones. The core is handed off for local development play, with unexecuted full campaigns, browser qualification, side-area defects, the four-byte native margin and FireRed roamer fidelity defect explicit. Extra HnS feature ports into Kanto were not included. Poryscript is owner-authorized as an optional tool; the current integration retains the existing compiled script pipeline.

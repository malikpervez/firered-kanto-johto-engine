# Kanto Buildings Remakes v0.3

**Pokémon Mansion and Power Plant rebuilt at a substantially larger architectural scale.** Mansion grows from 6×5 to 13×9 blocks (208×144px); Power Plant grows from 7×5 to 15×8 (240×128px). Their footprint areas are 3.9× and approximately 3.43× the previous versions. Windows, doors, masonry and pixels stay at the native game scale. The other 25 buildings and their animations are exactly v0.2.

**These two are not drop-in footprint replacements.** New local door blocks are (6,8) and (7,7). Their maps need space reserved, exterior collision rebuilt, approaches connected and warp placement checked. `SCALE_CHANGE_IMPORT.md` gives the full migration. Original interior destinations and story flags should stay the same. No game-project maps or Drive originals were modified.

## What to review

- `previews/scale_revision_comparison_4x.png`: v0.2 versus v0.3 at identical pixel scale and aligned ground level.
- `previews/scale_context_1x.png` and `_4x.png`: the larger buildings beside the approved Center and Mart on the lawn.
- `previews/<id>_blocks_4x.png`: footprint grid and new door position.
- `previews/all_27_remakes_2x.png`: full current collection.

## Contents

`packs/` has six complete set ZIPs, all at v0.3. `buildings/` contains the same 27 asset folders together. Each has native 4-bit indexed PNG, matching animated strip where applicable, schema-2 JSON, palette and nearest-neighbour 4× copies. `tile_pools/` supplies thirteen lossless building-only GBA pools. `source/` contains editable native drawing, export and validation code, original briefs, and the v0.2 baseline. `kit/` holds historical material swatches; the continuous-roofline rule overrides any old protruding ridge shown there.

Rebuild with Python 3, Pillow and NumPy: run `source/remake.py`, `source/export_tiles.py`, `source/previews.py`, `source/validate.py`, then `source/package.py`. No downsampling, tracing, quantization, antialiasing or baked ground enters the game assets. All palettes remain exactly v0.2, in the same order.

## Checks and building tile allowances

**737 / 737 checks PASS.** This covers the files, new size specification, matching doors, palette/alpha rules, exact GBA reconstruction and the other 25 assets remaining unchanged. Full-map placement, bank capacity after import, replay and story tests remain pending.

| Map | Building tiles | Allowance | Palette groups |
|---|---:|---:|---|
| pallet | 153 | 170 | houses, lab |
| route1 | 45 | 250 | houses |
| celadon | 307 | 384 | celadon |
| saffron | 319 | 344 | saffron |
| fuchsia | 233 | 310 | houses, saffron |
| lavender | 81 | 189 | lavender |
| cinnabar | 288 | 290 | cinnabar, lab |
| indigo | 175 | 373 | league |
| pewter | 84 | 86 | pewter_stone |
| route10 | 148 | 149 | pewter_stone |
| route22 | 162 | 197 | pewter_stone |
| route12_route23 | 64 | 137 | saffron |
| route16_route18_route15 | 55 | 300 | saffron |

## Complete inventory

| Asset | Blocks | Door blocks | Tiles incl. frames | Palette |
|---|---|---|---:|---|
| pallet_windmill | 5×6 | [] | 56 | houses |
| pokemon_lab | 9×5 | [[3, 4]] | 98 | lab |
| route1_rest_shelter | 3×3 | [] | 26 | houses |
| route1_arch | 4×2 | [] | 21 | houses |
| department_store | 10×7 | [[2, 6], [7, 6]] | 79 | celadon |
| celadon_mansion | 8×8 | [[3, 7], [3, 0]] | 86 | celadon |
| celadon_hotel | 6×5 | [[2, 4]] | 70 | celadon |
| game_corner | 9×5 | [[4, 4]] | 85 | celadon |
| celadon_gym | 7×5 | [[3, 4]] | 77 | celadon |
| silph_co | 9×12 | [[4, 11]] | 89 | saffron |
| saffron_gym | 7×5 | [[3, 4]] | 89 | saffron |
| fighting_dojo | 7×5 | [[3, 4]] | 87 | saffron |
| saffron_gate | 4×3 | [[1, 2], [2, 2]] | 53 | saffron |
| saffron_gate_back | 4×3 | [[1, 0], [2, 0]] | 31 | saffron |
| magnet_train_station | 8×4 | [] | 62 | saffron |
| route12_gate | 4×4 | [[1, 3], [2, 3], [1, 0], [2, 0]] | 64 | saffron |
| cycling_gate | 8×4 | [[0, 3], [7, 3]] | 55 | saffron |
| safari_gate | 7×5 | [[3, 4]] | 94 | saffron |
| fuchsia_gym | 7×5 | [[3, 4]] | 89 | saffron |
| house_pond_garden | 4×4 | [[1, 3], [1, 0]] | 62 | houses |
| pokemon_tower | 5×7 | [[2, 6]] | 81 | lavender |
| pokemon_league | 9×12 | [[4, 11]] | 175 | league |
| pokemon_mansion | 13×9 | [[6, 8]] | 139 | cinnabar |
| cinnabar_gym | 7×5 | [[3, 4]] | 90 | cinnabar |
| pewter_gym | 7×5 | [[3, 4]] | 84 | pewter_stone |
| power_plant | 15×8 | [[7, 7]] | 148 | pewter_stone |
| league_front_gate_tall | 15×10 | [[7, 9]] | 162 | pewter_stone |

## Design tour

- **pewter_gym**: Rock Gym in rough-cut limestone with a broad slate hip, raised stone gable and faceted rock relief, deep window reveals and low buttresses.
- **saffron_gym**: Purple hipped Psychic Gym with a projecting crystal gable, calm stonework, cyan recesses and a bright faceted psychic emblem.
- **fuchsia_gym**: Two layered purple tiled roofs, a shadowed upper clerestory, timber posts and shoji panels; a ninja compound rather than a civic recolour.
- **cinnabar_gym**: Blaine’s Gym uses dark volcanic stone, a metal hip with paired heat vents, a flame relief and warm entrance lamps.
- **pokemon_league**: Grand limestone hall with setback roof terraces, lower wings, a tall arched recess, crimson banners, Poké Ball relief, classical portico and illuminated entrance. No corporate-tower recolour.
- **fighting_dojo**: Traditional gable-front dojo: visible timber braces, layered plum-grey courses shared with the city roof bank, recessed shoji, broad bargeboards and heavy entrance posts.
- **safari_gate**: Thatched gable and broad hip over log courses, round-ended posts, shaded windows, timber signboard and lanterns.
- **pokemon_tower**: Solemn lavender memorial tower with three layered roofs, quiet stone courses, narrow recessed windows and a dark framed entrance.
- **celadon_gym**: Approved Buildings v0.2 glasshouse with the protruding ridge lip removed; the flush ridge stays within the roof. Facade, doors and glazing below the ridge remain unchanged.
- **department_store**: Large limestone department store with a recessed flat rooftop, ventilation units, projecting shop cornices, two matching glass doors and a raised store board.
- **celadon_mansion**: Mansard apartment building with three window tiers, projecting string courses, entry canopy and a lit north-facing rear threshold in the roof edge.
- **celadon_hotel**: Warm terracotta mansard hotel with pale masonry, repeated recessed windows, a projecting brass nameboard and an intimate lantern-lit entry.
- **game_corner**: Slot parlour with a deep red hipped roof, recessed cyan shop glazing, raised illuminated marquee, coin medallions and glass double leaves.
- **silph_co**: Corporate tower with repeated glass bays and vertical piers, a deeply recessed roof terrace, paired HVAC units and a projecting company crest. Glass lobby below.
- **saffron_gate**: Compact civic guardhouse with a steel hipped roof, broad stone framing and a two-block threshold; north-facing threshold uses a pale luminous edge, with no arrow.
- **saffron_gate_back**: Compact civic guardhouse with a steel hipped roof, broad stone framing and a two-block threshold; north-facing threshold uses a pale luminous edge, with no arrow.
- **route12_gate**: Compact civic guardhouse with a steel hipped roof, broad stone framing and a two-block threshold; north-facing threshold uses a pale luminous edge, with no arrow.
- **cycling_gate**: Reusable east-west civic gate: deep steel hip, clerestory windows and paired dark side passage mouths at the original left/right warp blocks.
- **magnet_train_station**: Glazed station roof with deep steel returns, stone side bays and a visibly shuttered, padlocked central entrance. No new warp or animated door.
- **pokemon_lab**: Clean metal-roofed research lab with a projecting gable entrance, ventilation unit and a separate glazed greenhouse wing containing native plant/pot clusters.
- **pallet_windmill**: Tapered white masonry windmill, terracotta cap, four framed lattice sails and a shaded stone foot. Scenery only, with no new doorway.
- **route1_rest_shelter**: Open timber rest shelter with a deep shingled hip, projecting front eave, four grounded post edges and a shaded bench; transparent openings.
- **route1_arch**: Wooden route arch with a small capped roof, layered beam and knee braces. Central two blocks stay walkable; top row retains over-player priority.
- **pokemon_mansion**: Expanded 13×9-block burned estate: two full storeys, long boarded window bays, a broad broken mansard, exposed rafters, chimney remains and a projecting columned entrance. Native window and masonry scale retained.
- **power_plant**: Expanded 15×8-block industrial complex: four sawtooth factory halls with clerestory glazing, a boiler annex, twin tall stacks, a sealed loading shutter, pipework and a recessed personnel entrance. Native detail scale retained.
- **league_front_gate_tall**: Two-storey League gateway with a broad slate hip, repeated limestone bays, deep string course and full-height central pavilion. Approved Route 22 door art preserved exactly.
- **house_pond_garden**: Approved pond keeper v0.2 front facade and green roof, adapted with a luminous north-facing rear dormer threshold. Existing lock stays bound to the game event.

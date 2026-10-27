# Building style guide v0.2

**Style approved by the owner on 2026-10-27.** Native GBA three-quarter view; front walls face the viewer, roofs are seen from above. Use the approved Pallet/Center/Mart roof language as the baseline. No generated-image tracing, downsampling, quantization, antialiasing or dithering. Author integer palette indices directly at 1×.

## Light, form and depth

Sunlight comes from upper left. Keep roof/front/return planes at visibly different values. Small fixtures cast a **1–2 px down-right shadow**; porch roofs and eaves cast **2–4 px**. Retain a bright left corner board and a shaded right return. Avoid a flat front elevation or an isometric rotation.

- **Recess:** 1px dark lintel, 1px shaded right jamb and a lit lower sill. The door is the facade's strongest contrast.
- **Projection:** lit top/left edge, darker face, dark underside, then a separate down-right shadow. Use this stack for sills, boxes, lamps and signs.
- **Overlap:** put porch canopy in front of the door; dormer and chimney in front of the roof. Do not let a window overlap the doorway.
- **Eave:** four native rows: lit lip → fascia → dark soffit → cast shadow. Extra wall shade can continue below. Use existing 1× geometry, not an outline enlarged after drawing.
- **Ground:** darker foundation course, lit step, dark contact line. Keep every pixel inside the footprint and leave index 0 around the structure.

Actual-pixel diagrams, each enlarged 12× with nearest-neighbour:

![Four-row eave and wall shade](previews/eave_stack_pixels.png)
![Recessed window and projecting sill](previews/window_reveal_pixels.png)

The complete seven-rule annotated example is `previews/house_depth_rules_6x.png`.

## Palette roles

The houses keep all original RGB values and index order. Celadon uses its supplied palette with **index 14 green corrected from 212 to 208**, satisfying the multiple-of-eight rule. Apply that shared-palette correction to the other Celadon buildings when importing this version. No second palette per building is needed in this review pack.

| Index | Houses shared | Celadon shared |
|---|---|---|
| 0 | Transparent | Transparent |
| 1 | Outline / deepest recess | Outline / deepest recess |
| 2 | Timber dark / red roof deepest | Deep recess / soffit |
| 3 | Green roof shade | Burgundy accent shade |
| 4 | Terracotta body | Steel / right roof return |
| 5 | Terracotta sunlight | Red accent |
| 6 | Foliage / green roof body | Pink accent light |
| 7 | Timber highlight / brass | Dark glass / interior |
| 8 | Green sunlight | Sky reflection / pale glass |
| 9 | Stone dark / fixture shadow | Stone shade |
| 10 | Plaster shade / stone | Stone face / frame |
| 11 | Plaster face | Warm edge / glint |
| 12 | Warm highlight / glass glint | Wood / bronze shade |
| 13 | Timber body / red roof shade | Gold / bronze face |
| 14 | Glass shadow | Gold highlight, corrected |
| 15 | Glass light | Plant green |

House ramps: red roof **2→13→4→5**; green roof **1→3→6→8**; plaster/stone **9→10→11→12**; timber **2→13→7**; glass **1→14→15→12**. Celadon ramps: framing **2→4→9→10→11**; glass **2→7→8→11**; bronze **12→13→14**; plants use **7/15/8** with restrained reflections.

## Material and detail recipes

Siding uses a lit board edge and shaded underlap; brick uses staggered courses; stone has restrained cracks and varied course joints; timber posts stand in front of pale infill. Put weathering beneath sills and at the base. Keep repeated middle-wall tiles quiet.

Glass panes have a dark interior and one upper-left reflection. Mullions are structural, not decorative stripes. Keep window design consistent within a building. Plants in Erika's Gym sit behind glazing bars, with pot rims, stems and foliage as separate clusters.

Panel doors have raised top-left panel edges, dark lower/right edges, a small handle glint and a fixed frame. Shop/lobby doors use wider glass; double doors have matched leaf widths. Opening animations change only the panel rectangle, never trim, signs, roof or steps. Store all three frames and verify the closed crop byte-for-byte.

Roofs retain broad sunlit planes, quiet shaded returns, hips ending at actual eave corners and a ridge shaded within the continuous roof silhouette. Courses widen toward the front. Shade courses across the right return with straight restrained seams, not diagonal squiggles. Use a dormer/cross-gable to break 7–10-block roofs. For a glasshouse, glazing ribs replace shingles; do not add a tile texture over the glass.

## Spending tiles and using the kit

Use `kit/index.json` for the **23 swatches**, their palette, tile counts and individual scale notes. Every swatch is at least 4×3 blocks. Select only the pieces a map needs; the whole kit is not one map tileset.

Repeat calm material, glazing, window and foundation modules on 8/16px boundaries. Spend unique tiles on roof hips, dormers, corners, the entrance and the sign. Count 8×8 tiles with H/V/HV mirrors merged, **including transparency and all door frames**. Shared house tiles count once across the three houses. Recheck the actual map after import, especially Pallet, Cinnabar and Pewter.

Review budgets: family **73/80**, gardener **62/64**, pond keeper **60/64**, houses together **153/180**, Erika **82/110**. Preserve each future building's footprint and door coordinates. Palette banks belong to the map, not to each building independently.

## Kanto remake application

See `IMPORT_NOTES_FOR_CLAUDE.md`, `palette_migration.json` and `tile_report.json` for the 26 follow-on remakes. The plum roof modules are shared by Sabrina’s Gym, the Dojo and Koga’s Gym; their silhouettes and wall structures differ. Large surfaces repeat on the 8/16px grid. Entrances, roof corners, structural returns and signs retain bespoke detail. Actual full-map import remains a game-project check.

## Roof silhouette correction v0.2

The owner rejected the extra raised rectangular notch/lip above ordinary sloped roofs. Keep their top outline continuous, with ridge highlights and shadow rows inside the roof surface. Reserve separate exit features for actual passages. Gate artwork and genuine rear-door thresholds retain their geometry. Historical kit swatches remain material/colour references only; this silhouette rule takes precedence over any protruding cap shown in an older swatch.

## Scale revision v0.3

Mansion and Power Plant deliberately exceed their former footprints at the owner’s request: 13×9 and 15×8 blocks. Repeat native-sized wall and window bays to communicate larger buildings. Never enlarge an old bitmap to fill the new area. Ordinary ridge caps stay within a continuous roofline.

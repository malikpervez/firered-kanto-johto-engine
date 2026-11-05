# Kanto Terraces v0.2

A side-wall revision of the approved Kanto Terraces v0.1. Uses the updated 5 November brief from the attached ZIP; the linked Drive first draft is marked superseded.

## What changed

- West and east side walls now fill their entire 8px half with rock. West facets catch the upper-left light; east facets match the tall face's shaded body. Each has an inward lit rim and an outward dark outline.
- Ordinary W/E walls have two variants. Alternate `W_wall` / `W_wall_2` and `E_wall` / `E_wall_2` by global row: first on even y, second on odd y. Their end rows match, so long walls repeat without horizontal seams. Keep directional art; do not mirror west into east.
- NW/NE caps turn into the original north lip. SW/SE bands meet the outer face headers without a change in tone or width.
- `outer_W/E_step_wall` and `tall_outer_W/E` now have square ends. Use them for exposed upper-tier ends, including where the lower tier continues beside them. Do not substitute the legacy rounded `outer_W/E` step pieces. Recessed `inner_W/E` and `tall_inner_W/E` remain unchanged.
- `outer_W/E_wall_side` joins the new band to level 1's face and retains the original rounded bottom half against the lawn.
- `side_W/E_step` uses the matching wider rock band. Its opposite phase half remains unchanged. Other junctions are untouched.

## Preserved

All atlas IDs **0-374** remain byte-identical. Revised pieces point to appended IDs **375-390**; older maps can still use their existing recipes and IDs. Every unlisted piece's PNG and JSON is byte-identical to v0.1. The palette, nine-phase top, height profile, step/tall face middles, recessed ends and layering rules are preserved. The base wall's ordinary middle art is unchanged. Both new wall variants are 16x16; face end columns retain their 16x16 or 16x32 dimensions.

The supplied v2 Route 3 level plan is used exactly, with no further proposed layout changes. All non-cliff ground in its reference render is preserved. Palette index 0 is transparent, alpha is binary, all import PNGs are 4-bit indexed, and all pieces remain solid with over_rows 0. The transparent half of a wall is a recipe placeholder for that tier's top phase, not a gap in the rock. Exterior transparency still reveals lower-tier rock. No lawn is baked into import art.

## Tile cost

| Category | New unique 8x8 tiles | Limit |
|---|---:|---:|
| Side walls, both variants and ends | 10 | 16 |
| Revised outer ends | 6 | 12 |
| Matching side junctions | 4 | Shared with the side walls |
| Whole revision, union | **16** | **28**, ideal 20 |
| Route 3 v2 plan, union | **16** | 28 |

Horizontal, vertical and combined flips count as one tile; rotations remain distinct. Counts are additional to v0.1. Categories overlap, so do not add them. Route 10's stated 32 free tiles leave 16 after importing the complete revision. The master atlas has 391 allocated tiles; maps import their required subset, not the entire catalogue. Old graphics stay in the atlas for compatibility.

## Placement

Keep v0.1's global phase formula `1 + 3*((y-origin_y)%3) + ((x-origin_x)%3)` and lower-to-upper tier composition. Height profile: level 1 uses the original two-block face, level 2 a one-block step, levels 3-5 a two-block face. The piece immediately above an upper face has no additional S cap. The ordinary side variant is selected independently of the nine-phase top. Use fixed N/S end pieces at terminal side cells.

All changed wall/contact JSONs provide explicit composites for each of the nine top phases. The opposite half is copied from the matching original top. Newly square outer ends use the same placement role as v0.1's outer ends; there is no new layer or height rule. Level 1 keeps rounded feet where it meets the lawn.

## Previews

- `route3_1x.png` / `route3_3x.png`: full 84x20 route, from the v2 plan.
- `route3_rest_stop_1x.png` / `_3x.png`: 240x160 GBA crop, columns 55-69 and rows 2-11. The brief's inclusive rows 2-12 span 176 pixels, so `route3_rest_stop_rows_2_to_12` additionally includes that full 11-row context. Neither is resized to force a different aspect ratio.
- `route3_west`: columns 0-14, rows 0-9, 240x160.
- `route3_mountain_context`: the full rest-stop mountain and nearby ground.
- `four_step_test` and `tall_profile_test`: exact v0.1 test grids, rendered with revised walls and square upper outer ends. Their 240x160 crops exercise no shelves and one-block shelves.
- `changed_pieces_before_after_4x.png`: each changed/added piece beside its v0.1 source. Phase placeholders are filled for inspection.
- `eight_block_walls`: each direction before/after across an eight-block run.
- `nine_phase_contact_2x.png`: all phase combinations for both wall variants, their ends and matching side junctions.
- `previews/layout.json`: exact supplied level grid, crop bounds, height profile and native recipe placements.

The Route 9 screenshot supplies long-wall context; no Route 9 level grid was provided, so this pack does not invent a new Route 9 layout. FireRed's reference is used for the side-wall method only. No reference tile is copied or traced into new art. Native additions are authored directly as indexed arrays; enlarged previews use nearest-neighbour copies.

## Rebuild and validation

Run `source/previews.py`, `source/finish.py`, `source/validate.py`, then `source/package.py` with Python 3, NumPy and Pillow. `source/v01` freezes the approved prior atlas, pieces, metadata and test grids; `source/base` retains the original Route 22 dependency. The brief and reference images are under `source/reference`.

Validation checks the full preserved atlas prefix, raw 4bpp bytes, unchanged PNG/JSON files, palette order, binary alpha, dimensions, exact 8px wall bands, variant joins, square upper ends, rounded base feet, unchanged opposite halves, phase reconstruction, budgets, supplied plan, test grids and protected ground. No ROM or game project was provided, so final emulator integration remains a game-side check. This revision is prepared for design review and has not been uploaded to Drive.

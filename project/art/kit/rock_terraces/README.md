# Kanto Terraces v0.1

Native mountain terraces for Route 22 Rock & Cliff revision 3.2. The approved taller profile uses two-block faces on the upper mountains, with a shallow ledge below. The existing 48x48 nine-phase top, palette, two-block base face and original atlas IDs remain unchanged.

## Height and shape

| Level | Default face height | Artwork |
|---|---|---|
| 1 | 2 blocks | Original base face |
| 2 | 1 block | Existing short terrace |
| 3, 4, 5 | 2 blocks | New taller terrace |

The taller faces grow upward into already-solid plateau cells. Their feet, paths and mountain footprint stay fixed. A full tall face needs two visible rows before the next higher tier; a tightly stacked higher tier can cover part of the face below. The original short profile remains available unchanged. Both profiles are defined in terraces/height_profiles.json.

Straight west/east silhouettes blend into the plateau's dominant stone tone. The outer feet turn inward smoothly; recessed contacts have no hanging dark tails. Inside corners appear only at real offset contacts, avoiding repeated teeth above a straight rim. West faces catch more light than east faces. The taller faces use connected, irregular planes with warm left-facing highlights, a quieter shaded body and a recessed dark foot. Large facets replace the earlier diagonal marks. Three middle assemblies vary their lower rock forms; the third recombines existing tiles at no additional tile cost. The crown keeps the original rim geometry while its shading continues into the new face.

Only the tall face textures change in this revision. The plateau texture, side silhouettes, lower ledges and base cliff remain unchanged. source/texture_revision_reference.json protects their previous appearance.

The Route 3 placement includes the broad upper-tier setbacks proposed in the earlier review. This height revision does not alter that plan. The originally supplied plan is also preserved and previewed. No walkable ground, paths, grass, flowers or props move.

## Tile cost

- **36 new unique 8x8 tiles**, within the 36-tile pack limit.
- Taller columns add **18 tiles** beyond the unchanged 18-tile short-profile set.
- The original one-block step family remains at 12 tiles. The combined short and tall step family uses 30; the approved taller option is an extension to that original sub-budget, reported separately.
- This Route 3 preview uses 33 new tiles.
- Original atlas IDs 0-338 are preserved. The previously reviewed short set at IDs 339-356 is also preserved; taller graphics append after it. The atlas now has 375 allocated tiles.

Counts merge horizontal, vertical and combined flips; rotations remain distinct. Category counts overlap and must not be added. Existing top phases, base faces and transparent tiles are reused at their original IDs. tile_report.json reports each piece, category and the union.

## Pieces and placement

| Folder / piece | Use | Avoid |
|---|---|---|
| step/middle_1, middle_2 | One-block upper faces, default level 2; alternate for restrained variation | Extra south cap above the built-in rim |
| step/outer_W, outer_E | Rounded exposed short face ends | Mirroring west art to make east art |
| step/inner_W, inner_E | Recessed ends beside continuing top | Exposed outside corners |
| tall_step/tall_middle_1, tall_middle_2, tall_middle_3 | Two-block faces, default levels 3-5 | Stretching a short column or drawing outside its level |
| tall_step/tall_outer_W, tall_outer_E | Exposed ends of taller faces | Separate stacked short feet midway down a tall face |
| tall_step/tall_inner_W, tall_inner_E | Recessed ends of taller faces | A lawn bank inside rock |
| side/W_wall, E_wall | Exact 8px directional side bands; opposite half is the correct top phase | Rendering the placeholder half as a hole |
| side/NW_wall, NE_wall | Back corners into the existing north rim | An artificial edge where the map continues |
| side/SW_wall, SE_wall | Last top cell above a front corner | Tapering the shoulder before the face begins |
| corners/outer_W_step_wall, outer_E_step_wall | Aliases of the short exposed ends | Adding a second corner overlay |
| corners/outer_W_wall_side, outer_E_wall_side | Base face corners connecting to the wider side bands | Replacing an ordinary base face middle |
| corners/side_W_step, side_E_step | Continuous return beside an offset short or tall face | A repeated horizontal foot on a vertical return |
| corners/in_SW_step, in_SE_step | Recessed top immediately above an offset face | A normal straight ledge |

All pieces are solid and have over_rows 0. Optional stairs are omitted. Native import PNGs are under terraces/, with 4-bit indexed pixels, the unchanged 16-entry palette and binary alpha at index 0. Exterior alpha reveals lower-tier rock; no grass is baked into these pieces. Side-piece transparent phase placeholders are filled by their recipes.

## Layering rules

1. Use global phase `1 + 3*((y-origin_y)%3) + ((x-origin_x)%3)` on every level. Preview origin is (0,0).
2. A tier mask contains every cell whose level is at least that tier. Render from low to high.
3. The base reserves two bottom rows for the original face and retains its existing south cap. Optional base corner pieces change only their upper outside 8x8 quarter.
4. Upper tiers reserve one or two bottom rows according to the height profile. Do not add an S cap: their own top row carries the rim.
5. Keep the column foot fixed when changing profiles. A no-shelf stack places the next face directly above the lower rim; one-block shelves leave a row of lower plateau between faces.
6. Choose exposed or recessed ends by the neighbouring top/face. A two-block column uses the same end role for both halves. Place recessed caps only above the first row of an offset face.
7. Treat off-map neighbours as continuation of the border level. No false cliff appears against a continuing map edge.
8. Retain lower-tier rock under upper-tier exterior alpha. Each side/contact JSON supplies all nine phase composites with exact tile IDs and flips. The preview raster is a visual proof, not an imported game map.

## Previews

- route3_1x and route3_3x: full route with the taller profile.
- route3_west: columns 0-14, rows 0-9; a 240x160 viewport.
- route3_rest_stop: columns 41-67, rows 0-10. gba_rest_stop and gba_east_return are additional 240x160 crops.
- short_profile_rest_stop: the same proposed plan using the preserved short faces.
- provided_plan_west and provided_plan_rest_stop: original supplied plan with the short profile.
- four_step_test: the original short stack, no shelves on the left and one-block shelves on the right.
- tall_profile_test: the taller stack, with fully exposed faces and both shelf arrangements. gba_tall_no_shelves and gba_tall_one_block_shelves are 240x160 views.
- side_join_closeups_4x: the preserved short side joins. all_pieces_labelled_4x shows every column, and nine_phase_contact_2x checks phase joins.
- layout.json records the supplied/proposed grids, profile, changed cells and every placement's native recipe.

## Source, validation and import

New art is authored directly as native index arrays. No new art is scaled, traced, quantized or dithered. The approved generated height study is visual direction only; none of its raster pixels enter these tiles. Enlarged previews use nearest-neighbour copies only. The supplied map is an exact 2x export: the renderer verifies identical 2x2 groups before recovering its native reference pixels. Every non-cliff pixel is preserved.

source/base contains the unchanged original dependency. source/short_profile_reference.json fingerprints the earlier 357-tile atlas, short PNGs and proposed plan. Validation checks both preserved sets, phase reconstruction, 4-bit encoding, palettes, collision metadata, tile counts, tall face alignment, shelf topology and preview copies.

The atlas is a master catalogue; import only the graphics each map uses. The addition fits the stated free space for Route 3 (about 220), Route 10 (64) and Route 22 (48). Pewter has no free tiles and needs reclamation or sharing before importing new graphics. Do not overwrite existing IDs to make room.

Rebuild in order with Python 3, Pillow and NumPy: source/previews.py, source/finish.py, source/validate.py, source/package.py. No ROM or game project was supplied, so emulator collision and actual map allocation remain integration checks. This package has not been uploaded to Drive in this revision.

# Mansion and Power Plant: exterior scale migration

The owner requested substantially larger buildings. v0.3 deliberately supersedes the original two footprint limits. These assets are ready for design review; the game maps have not been edited. The other 25 buildings, their animations and their gameplay metadata are unchanged from v0.2.

Coordinates below are zero-based `(column,row)`. Local positions are relative to the asset's top-left corner. A block is 16×16 pixels.

| Asset | Old footprint | New footprint | Old local door | New local door | Required walkable block below door |
|---|---|---|---|---|---|
| Pokémon Mansion | 6×5 / 96×80px | 13×9 / 208×144px | (2,4) | (6,8) | (6,9), outside the footprint |
| Power Plant | 7×5 / 112×80px | 15×8 / 240×128px | (3,4) | (7,7) | (7,8), outside the footprint |

Both retain one animated entrance, with three 16×32 frames in a 48×32 strip. The closed frame exactly matches its new building crop. Only the doorway opening changes between frames. Palette RGB values and index order are unchanged. Native windows, masonry and door pixels have not been enlarged; additional repeated modules create the larger structures.

## Placement arithmetic

To preserve an existing world doorway, calculate:

`new_origin = old_origin + old_local_door - new_local_door`

- Mansion: move the top-left origin **4 blocks west and 4 north**. This adds four columns west, three east and four rows north; the south edge remains fixed.
- Power Plant: move the top-left origin **4 blocks west and 3 north**. This adds four columns west, four east and three rows north; the south edge remains fixed.

These offsets are placement options, not tested or approved map edits. `placement_migration.json` records them in machine-readable form.

The supplied original briefs contain historical image-match location hints. They are not authoritative coordinates from the current game project:

| Asset | Historical top-left hint | Historical world door | Candidate origin preserving world door | Consequence |
|---|---|---|---|---|
| Mansion | (4,0) | (6,4) | (0,-4) | Negative row: cannot fit without expanding the map northward or relocating the building and exterior warp. |
| Power Plant | (26,35) | (29,39) | (22,32) | Nonnegative, but terrain, shoreline and neighboring objects still need inspection. |

For example, anchoring Mansion at (0,0) would put its door at (6,8). This is **not** a final placement: it would extend into the original Lab/street area, so Cinnabar needs a local layout revision. Leave the Lab artwork unchanged while rearranging its placement if necessary. The supplied site previews are cropped images, not complete editable maps. The old coastal plots are too tight for these new footprints; shoreline, land, trees and connecting paths need review.

## Integration work after design approval

1. Open the current Cinnabar and Route 10 maps and choose actual placements. Reserve the whole new rectangle; do not crop the artwork into the old footprint. Preserve map joins and unrelated event behavior.
2. Rebuild exterior collision from each new JSON: every footprint block is solid except its declared door. Clear the required approach block below the entrance and connect it to the existing route. Prefer a two-block-wide approach for the follower.
3. Update the exterior warp location if the world doorway moves. Preserve the intended interior destination, unlock conditions and story flags. There is no second entrance at the Plant's sealed loading shutter.
4. Import each regenerated door strip and its new local anchor. Check the closed-frame crop in the placed map and replay all animation frames.
5. Rebuild the building assemblies and map tile allocations. Cinnabar's Lab + Mansion + Gym union is **288/290** building tiles; Power Plant is **148/149**. These counts merge H/V flips and include all door frames. Recheck the **complete 384-tile map bank**, including terrain and other art, in the actual importer.
6. Test exterior reachability, follower clearance, collision, warps and the existing story events in game. None of those game-project tests has been performed in this asset-only revision.

## Art and file checks already completed

The independent validator checks native sizes, 4-bit indexed PNGs, exact 16-entry palettes, binary alpha, transparent index 0, channels divisible by eight, nearest-neighbor 4× copies, solid blocks, closed-frame equality, opening-only animation, flip-merged tile budgets and exact GBA 4bpp reconstruction. It also compares all 27 palettes and confirms the other 25 buildings and animations remain pixel-identical to v0.2.

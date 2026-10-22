# Route 22 Rock & Cliff — revision 3.2

This revision changes only the outer top/face join and top edges touching an inner face return. The palette, full 3×3 surface texture, face height, stairs and rock props remain pixel-identical to 3.1.

## Outer ends

For every phase, place `SW.png` directly above `outer_W_top.png`, followed by `outer_W_bottom.png`. Likewise, place `SE.png` above `outer_E_top.png` and `outer_E_bottom.png`.

The cap and face now share a one-pixel exterior inset at the join, continuing into the same side contour without a lawn notch. The cap changes stay inside its 6×6 corner. The `left` / `right` face aliases are updated too.

## A two-block top strip between terrace faces

Select the texture phase at every map position using the existing global origin. The following names are available in every `cliff_top/phases/1/` through `9/` folder.

| Placement on strip | West side of strip | East side of strip |
|---|---|---|
| Neighbouring terrace face column | `inner_E` to its west | `inner_W` to its east |
| Top beside the face's upper block | `side_W_face_start` | `side_E_face_start` |
| Top beside its lower block / continuing contact | `side_W_face` | `side_E_face` |
| Top immediately above that start | `in_SW_face` | `in_SE_face` |

The corner pieces replace the standard transparent lawn notch above the face start. For a top with other boundaries, copy only the corresponding bottom 8×8 quadrant. Their modified pixels stay inside 6×6. All side pieces change only the outer six pixels and preserve the centre phase elsewhere. W/E lighting is separately drawn.

The contacting three pixels at the bottom of each `inner_W` / `inner_E` column are now opaque, closing the last foot pinhole. All other inner-return pixels and the complete stair connector are unchanged.

## Files and verification

- `cliff_top/face_junctions.json`: all 54 new phase recipes and exact placement rules.
- `previews/junctions_3_2_4x.png`: two-block strip with both side faces and its south end.
- `previews/junctions_comparison_4x.png`: the same joins before and after.
- `previews/junctions_layout.json`: exact block positions, phases and overrides.
- `validation.md` / `validation.json`: 25 passing checks, including preservation against the 3.1 baseline.

The sampled side/head seam regions contain zero transparent gaps, down from 96 in the baseline. All 18 outer cap/face combinations, 162 side-phase pairs and 162 corner/start pairs pass. Import PNGs remain native 4-bit indexed images with the original palette and binary alpha. These are asset/composition checks; no game runtime was supplied.

The full atlas now contains 339 unique 8×8 tiles, up from 253. Load its regenerated tile maps with it; do not reuse old atlas IDs. Use the explicit face-adjacency recipes at these junctions rather than the lawn-only autotile masks.

# Claude handoff — Sunlit Broadleaf v0.4

Status: **v0.4 design approved by Malik on 2026-10-22**. This is the selected Sunlit tree release. Google Drive upload is authorized; game integration and runtime checks remain separate tasks.

1. Read `manifest.json`, `forest/forest.json` and the chosen standalone tree JSON.
2. Treat every tree/forest cell as 32×32 art covering a 2×2 group of 16×16 blocks. Forest cells start on even block columns and rows.
3. Preserve palette index 0 as transparent; never flatten against lawn. Import the one supplied 15-colour palette unchanged.
4. For forest cells, calculate neighbours on the 32px cell grid. Set a bit for each neighbour outside the forest, then apply the documented diagonal normalisation. Choose any crown variant a/b/c and the resulting mask recipe. Import all four quadrants from that same recipe.
5. Mark all four forest quadrants solid. A standalone tree recommends the lower two blocks solid and the upper two canopy; use the engine's existing priority/elevation handling so the player can appear behind foliage correctly.
6. Import the atlas and its supplied maps together. Do not reuse atlas IDs from a different version. There are 128 used 8×8 tiles, 4,096 packed bytes, and one 32-byte palette.
7. Use only `trees/`, `forest/autotiles/` and palette/atlas files for import. Do not import labelled sheets, lawn scenes, `_4x` reviews, source fixtures or validation imagery as game graphics.
8. Compare the imported result to `previews/town_context.png`. Test an inner corner, an outer corner, a 32px-wide opening, a narrow forest strip, and walking in front of/behind a standalone tree. Asset validation passed, but no ROM/runtime test has been performed.

Release filename: Sunlit_Broadleaf_Tree_Pack_v0.4.zip. Destination: the user's Pokemon Assets Drive folder. Malik selected v0.4 over v0.5; use the v0.4 art and atlas recipes in this archive.

## v0.4 compatibility

Palette indices, 32×32 footprints, anchors and placement rules are unchanged from v0.3. The pixel art and atlas have changed; replace graphics and atlas maps together. The new art has rounder crown lobes, stronger branch overlap, brighter rear forest crowns and longer visible trunks. Do not reuse v0.3 atlas IDs.

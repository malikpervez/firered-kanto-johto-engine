# Pallet Town reimagined (proof of concept)

A test of making map art with image generation and putting it in the game with pae.

1. **Concept** (`concept.png`): Pallet Town reimagined as a seaside village (windmill garden, harbor dock,
   Oak's lab with a greenhouse). Generated with Figma's image generator (Gemini 3.1 Flash Image). Concept only:
   a whole town painted like this needs far more unique tiles than a GBA tileset holds.
2. **One landmark as game art** (`windmill_generated.png`): the windmill generated alone, on a flat magenta
   background.
3. **Prepared** (`windmill_48x76.png`): the magenta keyed out, cropped, scaled to 48×76 pixels (3×5 blocks)
   and reduced to 14 colours.
4. **Imported with pae**:

   ```
   pae map import-art PalletTown_Frlg windmill_48x76.png --x 2 --y 13 --solid --bank 7 --new-palette -p engine
   ```

   - It adds 49 tiles, 15 metatiles and palette 7 of `gTileset_PalletTown_Hns`; no metatile used palette 7.
   - The windmill sits at blocks (2–4, 13–17), on the lawn left of the pond, and is solid.
   - Each block keeps the ground it covers.

   Replay test: "pallet windmill".

`before_after.png`: the town before and after (pae map render).

Next steps for a real redesign:
- pick the pieces of the concept to keep (dock, greenhouse, cobblestone paths);
- generate each one alone like the windmill;
- watch the tileset's room: `pae map tiles PalletTown_Frlg`.

Route 1 shares this tileset.

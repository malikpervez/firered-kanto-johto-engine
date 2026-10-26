# Art assets: what there is, where it's used, how to replace it

Every piece of art the rebuilt Kanto maps use: where it came from, which maps use it, and how to swap in a new
version. Anyone making art for the game (a person, or another AI) should start here. **Keep it current:** a pull
request that adds or changes a piece updates this page in the same pull request.

There are two kinds of art:
- **Packs**: native pixel art made outside this repository, reviewed and approved by Malik for the Pokemon Assets
  Google Drive folder, and copied in as a folder (png, json, palette, README). To update one, copy the new version
  over its folder (see *Replacing a piece*).
- **Drawn in code**: art Claude drew in Python while rebuilding a map, or made by recolouring or editing a pack.
  These are stand-ins, and a pack made to replace any of them is welcome. The map's `make_art.py` (or a module next
  to it) **writes their png files again on every build**. So a replacement must also switch off the function that
  draws it (named in the tables below), or the next build overwrites it.

## Packs (made outside, approved)

| Pack | Folder | Version and status | Used in |
|---|---|---|---|
| Sunlit Broadleaf trees | `kit/broadleaf/` | v0.4, approved 2026-10-22 | the forest (`T`) and standalone trees (`R`) on every kit map |
| Sunlit Broadleaf bushes | `kit/broadleaf/bushes/` | v0.2, approved 2026-10-22 | bushes and hedges (`b`) on most maps |
| Sunlit field rocks | `kit/field_rocks/` | v0.1 (its README still says "awaiting approval") | rocks (`o`) |
| Rock & cliff pack | `kit/rock_cliff/` | revision 3.2 (made for Route 22) | cliffs, put together by `kit/cliffs.py`: Route 22, Pewter, Routes 3, 4, 9, 10, 11, 25 |
| Lawn, "Lush Emerald" | `kit/lawn/B_Lush_Emerald/` | option B | the lawn (`.`) everywhere |
| Dressed-stone paving | `kit/paving/` | | paving (`p`): Pewter, Routes 2, 22 |
| Pond water, "Gentle ripples" | `kit/pond/` | option C | ponds (`~`, with lily pads `v` and reeds `r` drawn over it) |
| Sea, "Staggered swells, reworked rocks" | `kit/sea/` | option B | the sea (`s`) and sea rocks (`q`, `Q`): Pallet, Route 25, Route 17 (its inside corners, the pack's `in_*` pieces, in the kit since Route 17) |
| Tall grass | `kit/tall_grass/` | variants B and C (made with another AI from a brief) | tall grass (`g`) |
| Pokémon Center | `kit/buildings/pokemon_center/` | v0.1, approved | every town with a Center: Viridian, Pewter, Route 4, Cerulean, Vermilion, Route 10, Lavender, Celadon, Saffron, Fuchsia |
| Poké Mart | `kit/buildings/poke_mart/` | v0.1, approved | Viridian, Pewter, Cerulean, Vermilion, Lavender, Saffron, Fuchsia |
| Pallet houses (Red's, Blue's) | `pallet-concept/buildings/` | v0.5, approved | Pallet |
| Viridian houses (roofs) | `viridian-concept/buildings/` | v0.1 (roof revision of the Stage 2 houses) | see below: these three houses stand for most of Kanto's buildings |
| Viridian Gym, trainer school | `viridian-concept/buildings/` | Stage 2 | the Gym: Viridian, Cerulean, Vermilion (and recoloured as Pewter's Gym). The school: Viridian, Cerulean, Vermilion, and Saffron's Pokémon Trainer Fan Club |
| Route 2 Stage 2 assets | `route2-concept/buildings/` | v0.3 (the tile-budget export of the approved v0.2) | see below |
| League Front Gate | `route22-concept/buildings/league_front_gate/` | | Route 22 (a storey taller, drawn in code), Pewter's Museum |

The packs reused for buildings they weren't drawn for:

| Pack | Stands for |
|---|---|
| `house_family` | houses in Viridian, Pewter (three, one pack), Cerulean, Vermilion, Lavender; Route 2's trade house; Route 5's Day Care; Celadon's restaurant; Saffron's Copycat's house; Fuchsia's Warden's house |
| `house_gardener` | houses in Viridian, Cerulean, Vermilion, Lavender, Fuchsia; Route 5's Underground Path hut; Fuchsia's Safari Zone office |
| `house_pond_keeper` | houses in Viridian, Vermilion, Lavender; Bill's Sea Cottage (Route 25); the Underground Path huts on Routes 6, 7 and 8; Celadon's Prize Room and its house on Lucky Lane (one pack for both); Saffron's house and Mr. Psychic's house; Route 16's house in the woods; a house in Fuchsia, and (with a back door drawn in) Fuchsia's house with the pond garden |
| `forest_gate_south` | Viridian Forest's south gate (Route 2); Saffron's south, west and east gates on Routes 6, 7 and 8 (KR-40, KR-52; Saffron's own side has its drawn gatehouses); Route 11's gatehouse to Route 12 |
| `forest_gate_north` | Viridian Forest's north gate (Route 2); Saffron's north gate (Route 5) |
| `east_gatehouse` | Route 2's east gatehouse |
| `diglett_cave` | the cave mouths: Diglett's Cave (Routes 2 and 11), Mt. Moon (Route 4), Cerulean Cave (recoloured, below), Rock Tunnel's two mouths (Route 10, in the cliffs' palette) |

Ideas for new packs, from the issues in `../docs/kanto-rebuild.md`: an east-west gatehouse (KR-40, KR-52), a power
plant (KR-47), a prize hall and a restaurant for Celadon (KR-57).

## Drawn in code

| Piece | Where it's drawn | Size (blocks), door | Palette | Used in | Notes |
|---|---|---|---|---|---|
| Cobbles, dirt, stumps, fences, the dock, signs, barrels, crates, the boat, the well, flower beds, lamps | `kit/kit.py` (`cobble`, `dirt`, `stump`, `fence`, `planks`, `sign`, `barrel`, `crate`, `boat`, `well`, `flowers`, `lamp`) | 1×1 each | the kit's: ground (bank 0), wood (2), plants (8) | every kit map (`=` `:` `k` `#` `d` `S` `B` `c` `O` `w` `*` `l`) | |
| Ledges, steps, lily pads, reeds | `kit/fields.py` | 1×1 | ground (bank 0) | `_` `h` `v` `r` | |
| The windmill | `pallet-concept/make_art.py` `windmill()` | 5×6, door (2,5) | the kit's wood (bank 2) | Pallet | |
| Oak's Lab | `pallet-concept/make_art.py` `lab()` | 9×5, door (3,4) | `palette_lab.pal` | Pallet | a house with a metal roof and a greenhouse |
| The rest shelter | `route1-concept/make_art.py` `shelter()` | 3×3 | the route's own | Route 1 | |
| The arch over the road | `route1-concept/make_art.py` `arch()` | 4×2 | the kit's wood (bank 2) | Route 1 | its top row is drawn over the player |
| The League Front Gate, a storey taller | `route22-concept/make_art.py` `two_storeys()` | the pack's, one row taller | the pack's | Route 22 | an edit of the pack's own pixels |
| Pewter's Gym | `pewter-concept/make_art.py` `pewter_gym()` | 7×5, door (3,4) | Viridian's Gym, each colour the League Front Gate's nearest | Pewter | **its door frames are the source of the Power Plant's, the Tower's and Celadon's** (below) |
| Cerulean Cave's mouth | `cerulean-concept/make_art.py` `cave_mouth()` | the pack's (6×5) | the houses' palette, with the mouth's colours added | Cerulean | a recolour of `diglett_cave` |
| Route 2's gatehouse in the family house's palette | `route2-concept/make_art.py` `share_palette()` | the pack's | `house_family`'s | Route 2 | a recolour, to save a palette bank |
| The Power Plant | `route10-concept/make_art.py` `power_plant()` (writes `route10-concept/buildings/power_plant/`) | 7×5, door (3,4) | Pewter Gym's | Route 10 | Pewter's Gym with a blank plaque and a lightning bolt; its door frames' "GYM" painted out (KR-47, KR-49) |
| Pokémon Tower | `lavender-concept/make_art.py` `pokemon_tower()` (writes `lavender-concept/buildings/pokemon_tower/`) | 5×7, door (2,6) | its own (bank 9) | Lavender | three storeys of violet stone with candlelit windows; Pewter Gym's door frames recoloured, the board left blank |
| The Department Store | `celadon-concept/celadon_buildings.py` `department_store()` | 10×7, doors (2,6) and (7,6) | Celadon's buildings palette (`PAL`, bank 9) | Celadon | |
| The Celadon Mansion | `celadon_buildings.py` `mansion()` | 8×8, front door (3,7), back door (3,0) | the same | Celadon | the back door is a doorway (`MB_SOUTH_ARROW_WARP`): no animation, entered walking south |
| The hotel | `celadon_buildings.py` `hotel()` | 6×5, door (2,4) | the same | Celadon | |
| The Game Corner | `celadon_buildings.py` `game_corner()` | 9×5, door (4,4) | the same | Celadon | |
| Erika's Gym | `celadon_buildings.py` `gym()` (folder `celadon_gym`) | 7×5, door (3,4) | the same | Celadon | a glasshouse; keeps the "GYM" board over its door |
| Silph Co. | `saffron-concept/saffron_buildings.py` `silph_co()` | 9×12, door (4,11) | Saffron's buildings palette (`PAL`, bank 9) | Saffron | a tower: a gold crown band with the company's emblem, seven storeys of glass, a glass lobby |
| Sabrina's Gym | `saffron_buildings.py` `gym()` (folder `saffron_gym`) | 7×5, door (3,4) | the same | Saffron | lilac walls, a violet roof with a crystal orb; keeps the "GYM" board |
| The Fighting Dojo | `saffron_buildings.py` `dojo()` (folder `fighting_dojo`) | 7×5, door (3,4) | the same | Saffron | white plaster in a dark wooden frame under a broad slate roof |
| The gatehouse | `saffron_buildings.py` `gate()` (folder `saffron_gate`) | 4×3, a double door at (1,2)-(2,2) | the same | Saffron (its north, west and east gates) | its door frames are drawn here: one wide door, 96×32 |
| The gatehouse's back | `saffron_buildings.py` `gate_back()` (folder `saffron_gate_back`) | 4×3, a doorway at (1,0)-(2,0) | the same | Saffron (its south gate) | the doorway is `MB_SOUTH_ARROW_WARP`: entered walking south, no animation |
| The Magnet Train station | `saffron_buildings.py` `station()` (folder `magnet_train_station`) | 8×4, no door | the same | Saffron | its entrance is shuttered: the attendant outside arranges the journey |
| The Cycling Road gatehouse | `route16-concept/route16_buildings.py` `gate()` (folder `cycling_gate`) | 8×4, doorways at (0,3) and (7,3) | Saffron's buildings palette (bank 9) | Route 16 (twice: its upper and lower halls), Routes 18 and 15 (in bank 7 there) | an east-west gatehouse: the left doorway is `MB_EAST_ARROW_WARP` (entered walking east), the right `MB_WEST_ARROW_WARP`; no door frames. The pack the other east-west gates could use (KR-40, KR-52, KR-60) |
| The cycle track (Cycling Road's surface) | `route17-concept/route17_track.py` `piece()` | 1×1: 16 pieces by neighbours, inside corners, and paint (a lane line `+line`, an arrow downhill `+arrow`, a chequered line `+check`) where the plan has them | its own (`PAL`, bank 7): tarmac, a stone kerb, paint | Route 17 (`t`, `i`, `a`, `x`) | every piece is `MB_CYCLING_ROAD_PULL_DOWN` (the slope carries a rider down); a kerb wherever it meets anything but itself or the kit's cobbles |
| The Safari Zone's gate lodge | `fuchsia-concept/fuchsia_buildings.py` `safari_gate()` | 7×5, door (3,4) | Saffron's buildings palette (bank 9) | Fuchsia | a deep thatched roof (the palette's bronze and gold), a gold-lettered signboard, log walls; Pewter Gym's door frames, the board painted out |
| Koga's Gym | `fuchsia_buildings.py` `gym()` (folder `fuchsia_gym`) | 7×5, door (3,4) | the same | Fuchsia | a ninja house: a violet roof in two tiers, dark timber, paper screens; keeps the "GYM" board |
| The house with the pond garden | `fuchsia_buildings.py` `house_back_door()` | 4×4, front door (1,3), back door (1,0) | Viridian's houses' (bank 7) | Fuchsia | Viridian's `house_pond_keeper` with a dormer door added in its roof's back slope, beside the chimney: the back door (`MB_SOUTH_ARROW_WARP`, entered walking south, no animation); the front door keeps the pack's frames |

How each drawn building is switched off for a replacement:
- Pewter's Gym: remove the `pewter_gym()` call in `pewter-concept/make_art.py`'s `main()`;
- the Power Plant: in `route10-concept/make_art.py`, change `PLANT = power_plant()` to load the folder (as the other
  maps load a pack);
- Pokémon Tower: remove the `pokemon_tower()` call in `lavender-concept/make_art.py`;
- Celadon's buildings: remove the building's function from `ALL` in `celadon_buildings.py`;
- Saffron's buildings: remove the building's function from `ALL` in `saffron_buildings.py`;
- Route 16's gatehouse: remove `gate` from `ALL` in `route16_buildings.py`.

The Power Plant, Pokémon Tower, Celadon's buildings and Saffron's (but its gatehouse) take their door frames from Pewter's Gym's
(`pewter-concept/buildings/pewter_gym/pewter_gym_door.png`), by palette index. Celadon's `PAL` keeps Pewter Gym's
colours at the indices the frames use (1, 2, 4, 9–13). A new Pewter Gym changes all their doors at the next build;
give them door frames of their own first.

## Replacing a piece

A replacement that keeps the piece's size, door blocks and palette bank drops in without touching any map. It needs:
- **the image**: an indexed png of 16 colours, index 0 transparent, its size a whole number of 16-pixel blocks
  (`footprint_blocks` is its size in blocks). For a building, every part of the footprint that isn't the building
  itself is index 0: the map's ground shows there.
- **the door frames** (`<name>_door.png`): 48×32 pixels, three frames of 16×32 side by side (closed, half open,
  open), for the door block and the block above it. The closed frame must match the building's own pixels there.
  A wide door is 96×32 (frames of 32×32).
- **the json** (`<name>.json`, schema 2): `id`, `image`, `image_size_px`, `block_size_px` (16),
  `footprint_blocks` (`width`, `height`), `transparent_index` (0), `door_blocks` (each door's block, from the
  top-left, `[x, y]`), and `door` (its `image`, `sheet_size_px`, `frame_size_px`, `frame_count` 3, `frame_order`).
  The older packs have one `door_block`; the maps read either.
- **the palette**: buildings in one map share palette banks (7 and 9 for buildings; 8 is the kit's plants, 10–12
  are left for seams to old maps). A map's `make_art.py` stops with "its palette isn't the one bank N has" if two
  pieces in one bank disagree. So a new building either uses its bank's palette as it is, or brings a palette for
  every piece in that bank.
- **the tile budget**: a map's own tileset holds at most 384 8×8 tiles (flipped copies count once), and the seams
  to its neighbours need room in the tile slots it leaves free. Draw repeating detail on the 16-pixel grid so tiles
  repeat. Current use, from the built tilesets (seam tiles as `pae seam build` reports them):

| Map | Own tiles (of 384) | Seam tiles | Metatiles |
|---|---|---|---|
| the kit (primary, every map) | 538 (of 640) | | 410 (of 640) |
| Pallet | 308 | 64 | 125 |
| Route 1 | 52 | 134 | 17 |
| Viridian | 230 | 0 | 107 |
| Route 22 | 285 | 0 | 233 |
| Route 2 | 285 | 0 | 162 |
| Viridian Forest | 1 | | 6 |
| Pewter | 341 | 76 | 203 |
| Route 3 | 145 | 94 | 62 |
| Route 4 | 147 | 141 | 77 |
| Cerulean | 255 | 0 | 122 |
| Route 24 | 1 | 0 | 1 |
| Route 25 | 120 | 0 | 36 |
| Route 5 | 200 | 0 | 84 |
| Route 6 | 170 | 24 | 64 |
| Vermilion | 230 | 60 | 110 |
| Route 11 | 238 | 32 | 107 |
| Route 9 | 132 | 97 | 55 |
| Route 10 | 211 | 108 | 121 |
| Lavender | 199 | 74 | 87 |
| Route 8 | 170 | 93 | 64 |
| Route 7 | 170 | 0 | 64 |
| Celadon | 231 | 0 | 280 |
| Saffron | 307 | none (no compiled joins) | 290 |
| Route 16 | 81 | 0 | 48 |
| Route 17 | 37 | 0 | 25 |
| Route 18 | 26 | 30 (for Fuchsia's own pieces) | 32 |
| Fuchsia | 207 | 47 (for old Route 19) | 138 |
| Route 15 | 26 | 39 (for old Route 14) | 32 |

A replacement that changes a building's size or moves its door changes the maps that use it: their plans
(`draw_plan.py`), door adds and warps (`build.sh`). That is a map change, made in its own pull request.

After replacing a piece, from the repository root:
1. `sh project/art/build_all.sh` rebuilds every map (or `sh project/art/<map>-concept/build.sh` for one map). The
   build stops if a palette, a footprint or the tile budget doesn't fit.
2. `cd engine && pae test run`: the replay tests whose screens show the piece will report changes. Look at each
   (`.pae/test-results/<test>.diff.png`), then `pae test accept` the ones that changed as intended.
3. Render the changed maps (`pae map render`) for their `map.png`. Update this page, and open a pull request with
   what was and wasn't tested (AGENTS.md).

Never commit ROMs, saves, emulator states or anything not approved for the repository (AGENTS.md).

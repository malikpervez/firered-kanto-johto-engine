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
  to it) **writes their png files again on every build** (but the one marked "no longer drawn"). So a replacement
  must also switch off the function that draws it (named in the table below), or the next build overwrites it.

## Packs (made outside, approved)

| Pack | Folder | Version and status | Used in |
|---|---|---|---|
| Sunlit Broadleaf trees | `kit/broadleaf/` | v0.4, approved 2026-10-22 | the forest (`T`) and standalone trees (`R`) on every kit map |
| Sunlit Broadleaf bushes | `kit/broadleaf/bushes/` | v0.2, approved 2026-10-22 | bushes and hedges (`b`) on most maps |
| Sunlit field rocks | `kit/field_rocks/` | v0.1 (its README still says "awaiting approval") | rocks (`o`) |
| Rock & cliff pack | `kit/rock_cliff/` | revision 3.2 (made for Route 22) | cliffs, put together by `kit/cliffs.py`: Route 22, Pewter, Routes 3, 4, 9, 10, 11, 25, Cinnabar's volcano, Route 20's Seafoam Islands |
| Lawn, "Lush Emerald" | `kit/lawn/B_Lush_Emerald/` | option B | the lawn (`.`) everywhere |
| Dressed-stone paving | `kit/paving/` | | paving (`p`): Pewter, Routes 2, 22 |
| Pond water, "Gentle ripples" | `kit/pond/` | option C | ponds (`~`, with lily pads `v` and reeds `r` drawn over it) |
| Sea, "Staggered swells, reworked rocks" | `kit/sea/` | option B | the sea (`s`) and sea rocks (`q`, `Q`): Pallet, Route 25, Route 17 (its inside corners, the pack's `in_*` pieces, in the kit since Route 17). The sea is surfable and fishable (the pond's behaviour); the rocks are solid |
| Tall grass | `kit/tall_grass/` | variants B and C (made with another AI from a brief) | tall grass (`g`) |
| Pokémon Center | `kit/buildings/pokemon_center/` | v0.1, approved | every town with a Center: Viridian, Pewter, Route 4, Cerulean, Vermilion, Route 10, Lavender, Celadon, Saffron, Fuchsia |
| Poké Mart | `kit/buildings/poke_mart/` | v0.1, approved | Viridian, Pewter, Cerulean, Vermilion, Lavender, Saffron, Fuchsia |
| Pallet houses (Red's, Blue's) | `pallet-concept/buildings/` | v0.5, approved | Pallet |
| Viridian houses (roofs) | `viridian-concept/buildings/` | v0.1 (roof revision of the Stage 2 houses) | see below: these three houses stand for most of Kanto's buildings |
| Viridian Gym, trainer school | `viridian-concept/buildings/` | Stage 2 | the Gym: Viridian, Cerulean, Vermilion. The school: Viridian, Cerulean, Vermilion |
| Route 2 Stage 2 assets | `route2-concept/buildings/` | v0.3 (the tile-budget export of the approved v0.2) | see below |
| League Front Gate | `route22-concept/buildings/league_front_gate/` | | Pewter's Museum (Route 22 has the remakes' two-storey version, its door art this pack's) |
| Kanto Buildings Remakes | `packs/buildings_v0.3/` (`buildings/<id>/`: png, door frames, json, palette; the pack's README, style guide and import notes beside them) | v0.3, approved 2026-10-27 (v0.2 with the Pokémon Mansion and the Power Plant made larger at Malik's request) | the 27 buildings Claude first drew in code or recoloured: see *The remakes* below |

The packs reused for buildings they weren't drawn for:

| Pack | Stands for |
|---|---|
| `house_family` | houses in Viridian, Pewter (three, one pack), Cerulean, Vermilion, Lavender; Route 2's trade house; Route 5's Day Care; Fuchsia's Warden's house |
| `house_gardener` | houses in Viridian, Cerulean, Vermilion, Lavender, Fuchsia; Route 5's Underground Path hut; Fuchsia's Safari Zone office; Route 12's fishing house |
| `house_pond_keeper` | houses in Viridian, Vermilion, Lavender; Bill's Sea Cottage (Route 25); the Underground Path huts on Routes 6, 7 and 8; Celadon's Prize Room, restaurant and house on Lucky Lane (one pack for all three: KR-57); Saffron's Copycat's house, house, Mr. Psychic's house and Trainer Fan Club (one pack for all four: KR-84); Route 16's house in the woods; a house in Fuchsia (the remakes' `house_pond_garden` is it with a back door, for Fuchsia's house with the pond garden) |
| `forest_gate_south` | Viridian Forest's south gate (Route 2); Saffron's south, west and east gates on Routes 6, 7 and 8 (KR-40, KR-52; Saffron's own side has its drawn gatehouses); Route 11's gatehouse to Route 12 |
| `forest_gate_north` | Viridian Forest's north gate (Route 2); Saffron's north gate (Route 5) |
| `east_gatehouse` | Route 2's east gatehouse |
| `diglett_cave` | the cave mouths: Diglett's Cave (Routes 2 and 11), Mt. Moon (Route 4), Cerulean Cave (recoloured, below), Rock Tunnel's two mouths (Route 10, in the cliffs' palette), the Seafoam Islands' two mouths (Route 20, the same) |

Ideas for new packs, from the issues in `../docs/kanto-rebuild.md`: a prize hall and a restaurant for Celadon (KR-57).
The remakes' east-west gatehouse (`cycling_gate`) could stand for the other east-west gates (KR-40, KR-52, KR-60).

### The remakes (Kanto Buildings Remakes v0.3)

Made by the artist of the packs above from a brief and Claude's stand-ins (the brief and the stand-ins are in the
Drive folder "Kanto Buildings To Remake v1"), in the style of `packs/buildings_v0.3/BUILDING_STYLE_GUIDE.md`. Each
keeps its stand-in's size and doors, except the two marked. The maps load them from `buildings.REMAKES`
(`kit/buildings.py`). The pack's palettes are named groups; a map puts each group in one bank.

| Building (`id`) | Size (blocks), doors | Palette | Used in (bank) | Notes |
|---|---|---|---|---|
| The windmill (`pallet_windmill`) | 5×6, no door | Viridian's houses' | Pallet (10) | scenery |
| The Pokémon Lab (`pokemon_lab`) | 9×5, door (3,4) | the lab's (Pallet's old lab palette, rounded to multiples of 8) | Pallet (7), Cinnabar (10) | Oak's lab and Cinnabar's; its own door frames |
| The rest shelter (`route1_rest_shelter`) | 3×3, no door | Viridian's houses' | Route 1 (7) | |
| The arch over the road (`route1_arch`) | 4×2: the road goes under its middle two columns | Viridian's houses' | Route 1 (7); Pallet shows it across the join in its bank 10 | its top row is drawn over the player |
| The Department Store (`department_store`) | 10×7, doors (2,6) and (7,6) | Celadon's | Celadon (9) | one door strip for both doors |
| The Celadon Mansion (`celadon_mansion`) | 8×8, front door (3,7), back door (3,0) | Celadon's | Celadon (9) | the back door is a doorway (`MB_SOUTH_ARROW_WARP`): no animation, entered walking south |
| The hotel (`celadon_hotel`) | 6×5, door (2,4) | Celadon's | Celadon (9) | |
| The Game Corner (`game_corner`) | 9×5, door (4,4) | Celadon's | Celadon (9) | |
| Erika's Gym (`celadon_gym`) | 7×5, door (3,4) | Celadon's | Celadon (9) | a glasshouse; the "GYM" board over its door |
| Silph Co. (`silph_co`) | 9×12, door (4,11) | Saffron's | Saffron (9) | |
| Sabrina's Gym (`saffron_gym`) | 7×5, door (3,4) | Saffron's | Saffron (9) | |
| The Fighting Dojo (`fighting_dojo`) | 7×5, door (3,4) | Saffron's | Saffron (9) | |
| The gatehouse (`saffron_gate`) | 4×3, a double door at (1,2)-(2,2) | Saffron's | Saffron (9: its north, west and east gates) | one wide door, 96×32 |
| The gatehouse's back (`saffron_gate_back`) | 4×3, a doorway at (1,0)-(2,0) | Saffron's | Saffron (9: its south gate) | entered walking south, no animation |
| The Magnet Train station (`magnet_train_station`) | 8×4, no door | Saffron's | Saffron (9) | its entrance is shuttered: the attendant outside arranges the journey |
| Route 12's north gatehouse (`route12_gate`) | 4×4: a doorway at (1,0)-(2,0), a double door at (1,3)-(2,3) | Saffron's | Route 12 (7); Route 23 (9: the League gate's back, its doorway only) | walked through from north to south |
| The Cycling Road gatehouse (`cycling_gate`) | 8×4, doorways at (0,3) and (7,3) | Saffron's | Route 16 (9, twice), Routes 18 and 15 (7) | an east-west gatehouse: the left doorway `MB_EAST_ARROW_WARP` (entered walking east), the right `MB_WEST_ARROW_WARP`; no door frames |
| The Safari Zone's gate lodge (`safari_gate`) | 7×5, door (3,4) | Saffron's | Fuchsia (9) | |
| Koga's Gym (`fuchsia_gym`) | 7×5, door (3,4) | Saffron's | Fuchsia (9) | |
| The house with the pond garden (`house_pond_garden`) | 4×4, front door (1,3), back door (1,0) | Viridian's houses' | Fuchsia (7) | the pond keeper's house with a dormer doorway in its back slope: the back door is entered walking south, no animation |
| Pokémon Tower (`pokemon_tower`) | 5×7, door (2,6) | Lavender's (the tower's own) | Lavender (9) | |
| The Pokémon League (`pokemon_league`) | 9×12, door (4,11) | the League's | Indigo Plateau (7) | |
| Blaine's Gym (`cinnabar_gym`) | 7×5, door (3,4) | Cinnabar's (volcanic) | Cinnabar (7) | |
| Brock's Gym (`pewter_gym`) | 7×5, door (3,4) | Pewter's stone (the League Front Gate's) | Pewter (7) | |
| The League Front Gate, two storeys (`league_front_gate_tall`) | 15×10, door (7,9) | Pewter's stone | Route 22 (7) | its door art is the League Front Gate pack's |
| The burned Pokémon Mansion (`pokemon_mansion`) | **13×9** (was 6×5), door (6,8) | Cinnabar's (volcanic) | not yet: Cinnabar needs a new layout for it | the stand-in below until then |
| The Power Plant (`power_plant`) | **15×8** (was 7×5), door (7,7) | Pewter's stone | Route 10 (9) | fills its island in the lake; one door: its loading shutter is sealed scenery |

## Drawn in code

| Piece | Where it's drawn | Size (blocks), door | Palette | Used in | Notes |
|---|---|---|---|---|---|
| Cobbles, dirt, stumps, fences, the dock, signs, barrels, crates, the boat, the well, flower beds, lamps | `kit/kit.py` (`cobble`, `dirt`, `stump`, `fence`, `planks`, `sign`, `barrel`, `crate`, `boat`, `well`, `flowers`, `lamp`) | 1×1 each | the kit's: ground (bank 0), wood (2), plants (8) | every kit map (`=` `:` `k` `#` `d` `S` `B` `c` `O` `w` `*` `l`) | |
| Ledges, steps, lily pads, reeds | `kit/fields.py` | 1×1 | ground (bank 0) | `_` `h` `v` `r` | |
| Cerulean Cave's mouth | `cerulean-concept/make_art.py` `cave_mouth()` | the pack's (6×5) | the houses' palette, with the mouth's colours added | Cerulean | a recolour of `diglett_cave` |
| Route 2's gatehouse in the family house's palette | `route2-concept/make_art.py` `share_palette()` | the pack's | `house_family`'s | Route 2 | a recolour, to save a palette bank |
| The burned Pokémon Mansion | `cinnabar-concept/buildings/pokemon_mansion/` (no longer drawn on a build) | 6×5, door (2,4) | its own (bank 9) | Cinnabar | Celadon's old stand-in hotel charred: its colours greyed and darkened, soot streaked up the walls. A stand-in until the remakes' larger Mansion moves in |
| Saffron's city blocks: three offices (tall, mid, narrow) and an arcade, none with a door | `saffron-concept/make_art.py` `city_designs()`, with `kit/buildings.py` `recompose()` and `recolour()` | offices 6×9, 6×6, 4×6; the arcade 4×4 | Silph Co.'s (bank 9, beige) and two recolours of it: sand (10), brick (11) | Saffron (`A` `F` `I` `J` `V` `C` `a`) | Silph Co.'s and the station's own 8×8 cells put back together without the emblem, the signs and the doors, so they cost no tiles; their identical blocks share a metatile (pae's `dedupe`). Saffron also has its own copies of the kit's Center, Mart and lamp on paving (`*_paved`: the kit's tiles, no new ones) |
| The cycle track (Cycling Road's surface) | `route17-concept/route17_track.py` `piece()` | 1×1: 16 pieces by neighbours, inside corners, and paint (a lane line `+line`, an arrow downhill `+arrow`, a chequered line `+check`) where the plan has them | its own (`PAL`, bank 7): tarmac, a stone kerb, paint | Route 17 (`t`, `i`, `a`, `x`) | every piece is `MB_CYCLING_ROAD_PULL_DOWN` (the slope carries a rider down); a kerb wherever it meets anything but itself or the kit's cobbles |

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
| Pallet | 297 | 64 | 125 |
| Route 1 | 45 | 134 | 17 |
| Viridian | 230 | 0 | 107 |
| Route 22 | 337 | 0 | 233 |
| Route 2 | 285 | 0 | 162 |
| Viridian Forest | 1 | | 6 |
| Pewter | 352 | 76 | 203 |
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
| Route 10 | 287 | 108 | 206 |
| Lavender | 215 | 74 | 87 |
| Route 8 | 170 | 93 | 64 |
| Route 7 | 170 | 0 | 64 |
| Celadon | 345 | 0 | 260 |
| Saffron | 355 | none (no compiled joins) | 379 |
| Route 16 | 110 | 0 | 48 |
| Route 17 | 37 | 0 | 25 |
| Route 18 | 55 | 30 (for Fuchsia's own pieces) | 32 |
| Fuchsia | 339 | 47 (for old Route 19) | 138 |
| Route 15 | 55 | 0 | 32 |
| Route 14 | 1 (nothing of its own) | 0 | 0 |
| Route 13 | 1 (nothing of its own) | 0 | 0 |
| Route 12 | 107 | 79 (for Route 11's own pieces) | 32 |
| Route 21 (north and south, one tileset) | 1 (nothing of its own) | 125 (Route 21 South, for Cinnabar's own pieces) | 0 |
| Cinnabar | 371 | 0 | 169 |
| Route 20 | 157 | 0 | 82 |
| Route 19 | 1 (nothing of its own) | 0 | 0 |
| Route 23 | 174 | 149 (for Route 22's gate) | 79 |
| Indigo Plateau | 168 | 29 (for old League West Pass) | 108 |

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

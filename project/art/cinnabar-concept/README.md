# Cinnabar Island after its concept

Kanto's volcanic island town, out in the southern sea. It is rebuilt from the kit (`../kit`). The concept is this
folder's own: `draw_plan.py` draws the block plan (`plan_stage1.txt`) from shapes and says why things are where they
are.

![The map](map.png)

The island is 96×44 blocks, as before. Its joins stay where they were:
- Route 21's sea is above (its columns 0–23, offset 0): its foot is the woods behind the town, and the sea lane down
  the town's west side;
- Route 20's sea is to the right (its rows 0–19, offset 0).

It has two islands:
- **the town island** at the top left: the burned Pokémon Mansion and Blaine's Gym backing onto the woods along the
  north shore, the street between them; the Pokémon Lab, the Pokémon Center and the Mart along the harbour street
  below; the east lane down to the harbour, where the Seagallop comes in; the beach along the south;
- **the volcano island** to the east, across the harbour: the volcano's rock in the middle, narrower at its summit,
  its crater of cooling lava in its top (no way down into it), its slopes of ash with lava rocks and steam vents
  round it with its Pokémon (Magmar and Magby, Magcargo and Slugma, Torkoal, Koffing and Weezing), a hot spring below
  it, steaming, the woods and lawns where the Friends camp (round 46,20, Giratina's rift four blocks west).

The doors the island's scenes walk to stay where they were: the Center's at 14,11 (Bill goes back in through it) and
the Gym's at 20,4 (its lock at 20,5). Bill and the player still walk the harbour street (row 12) and the east lane
(column 21) to the boat, which comes in from the east on rows 8 and 12. The Mansion's, the Lab's and the Mart's doors
moved (6,4; 6,11; 18,11); every warp keeps its number, so the buildings behind them still point at it.

The pieces: the kit's and its Pokémon Center and Mart; the island's own buildings, each in its own palette: Blaine's
Gym and the Pokémon Lab (Oak's, as Pallet has it) from Kanto Buildings Remakes v0.3 (`../packs/buildings_v0.3/`); the burned Mansion
(`buildings/pokemon_mansion`: Celadon's old hotel, greyed, darkened and streaked with soot, until the remakes' larger
Mansion moves in); and the island's own ground, rock and details (below). Until KR-100 the volcano's rock was the
kit's cliffs (`../kit/cliffs.py`) and its paths the kit's dirt.

It was rebuilt with Route 21, in one pull request, so that every join between them is between kit maps. Old
Route 20 still needs a seam (KR-78). The old island's layout was in FireRed's metatile format, so its build sets the
kit's (HnS's, `--version hns`: KR-74).

`make_art.py` checks the island's rules on the map it builds:
- on foot the town is one place, reached from its street; the only walkable block on an edge is the lawn between the
  woods and the Gym, under Route 21's woods;
- by Surf from Route 21's lane, both islands and Route 20's sea are reached; the islands aren't joined on foot;
- every door can be walked into and every sign read; the Center's and the Gym's doors are where the scenes need them;
- the scenes' ground is open and the boat's way is open sea;
- the Friends' camp and Giratina's spot are open ground; the people and Pokémon stand on open ground, Wailmer swims;
- the volcano's crater is solid (its lava), with no way into it.

Build it from the repository root with `sh project/art/cinnabar-concept/build.sh` (or every map with
`sh project/art/build_all.sh`).

Its Town Props (KR-94, `../kit/props.py`): two benches and a bin on the south lawn, looking out to sea.

## Its own look (KR-100)

Kanto Cinnabar Island v0.1 (`../packs/cinnabar_v0.1`, made with another AI from `Cinnabar_Island_v0.1_prompt.md`),
laid by `../kit/cinnabar.py`. The pack came with a placement plan for this map (`previews/placement_plan.json`), and
the map follows it:
- **basalt setts** through the town: both streets and the east lane down to the harbour, the same edge wherever they
  meet the lawn, and straight up to the buildings' fronts (no lawn edge along them). The three signs in the street
  stand on the setts' block under them.
- **volcanic ash** over the volcano island: its paths, under the volcano's rock, and most of its lawn (the pack's
  second round), leaving a one-block lawn shore, the lawn round the woods, the flower beds and the hot spring, and the
  Friends' clearing. Its second fill here and there where only ash is round it.
- **the basalt cliff** for the volcano's rock, block by block as the plan records it (four phases of its top, the
  two-block columnar face along the bottom of each column, its ends and its junctions with the tops, the cap with
  embers along the crater's north side). `cinnabar.lay` checks the plan's cliff covers the map's rock exactly.
- **the crater**: cooling lava in two fills, solid.
- **eight lava rocks**, where the field rocks on the ash were (the plan's seven, and one at 39,26 whose lawn became
  ash in the pack's second round), **four steam vents** on the ash and **the hot spring's steam** on the lawn either
  side of it (the vents and the steam animated, 24 frames an image; all solid, and clear of every walk, person and
  Pokémon).

The setts are in a palette of their own (bank 12); the ash, the cliff, the crater and the details in the pack's
volcano palette (bank 11, the kit rock's before). The island takes 326 of its 384 tiles (89 of them the pack's), 211
metatiles.

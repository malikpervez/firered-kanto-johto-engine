# Cerulean City after its concept

The town by the lake where Nugget Bridge comes down, rebuilt from the kit (`../kit`), the kit's Center and Mart,
Viridian's buildings and Route 2's cave mouth. The concept is this folder's own: `draw_plan.py` draws the block plan
(`plan_stage1.txt`) from shapes and says why things are where they are.

![The map](map.png)

The town is 58×51 blocks, as before, and its four exits stay where its neighbours meet it: Nugget Bridge (Route 24)
the top at columns 41–44, Route 4's road the left edge at rows 17–20, Route 9's the right edge at rows 28–30, Route 5's
the bottom at columns 21–24. It has:
- **the bridge road** down from Nugget Bridge, where Blue waits (his scene walks the same columns as before, and his
  triggers stay across it at row 7);
- **the lake** west of the bridge, and **Cerulean Cave** on its island, reached only by surfing, its guard at the mouth;
- **the badge house** east of the bridge road, with its back door onto a yard you reach only through the house, and
  the berry man's house below it;
- **the robbed house** in the middle of town, with the thieves' hole into its backyard and the Rocket in the
  one-block way out of it, his triggers either side of him; the policeman at its door;
- the Pokémon Center (heal spot 28,29) by the plaza's pool, the Friends' camp (their fourth scene: anchor 34,32), the
  Gym south of the road east, the Mart, the Bike Shop (Viridian's Trainer School) and three small houses, the
  Pokémon shelter's corner, and a garden behind a tree to cut;
- **the neck** on the road south (22–23,45), where the lass and her Slowbro stand until you have the S.S. Ticket
  (`CeruleanCity_EventScript_BlockExits` puts them there); after it they stand south of the Mart.

Every warp keeps its number and the people their order. The Bike Shop's three warps are one door; the hole and the
back door are lawn you step on and walk south from into the house (they aren't drawn yet).

**The streets (KR-93).** The town is paved: the kit's dressed stone in the streets' blocks, every building standing
on it (the Center and the Mart are the town's own copies), lawn only in the gardens, the yards, the backyard, the
shelter's field and the island. West of the road south its slate-blue brick borders the paving; east of it the town is
one grey square from the Center to the Gym. Canals run by the roads south and east, each with a footbridge; a fence
runs along the lake behind the promenade (the island is reached by Surf from the bridge) and round the Center's north
and west sides. Four cottages without doors stand in the west and east. The fountain in the square, the benches, tubs,
bin and bike rack are Kanto Town Props v0.1 (`../packs/town_props_v0.1`, `../kit/props.py`); the fountain's water
animates.

Its tileset's palettes: bank 7 the Gym and the Bike Shop, bank 9 the houses and the cave mouth (drawn in the houses'
palette, the two colours they don't use being the cave's), bank 8 the kit's plants, 10 the brick, 11 and 12 the
cottages; the props are drawn in the kit's water and wood palettes (banks 1 and 2). 320 of its 384 tiles are used.

`make_art.py` checks the town's rules on the map it builds: only the four exits open onto the edges; with the tree
standing, the Rocket and his triggers in his way and the lass and her Slowbro in the neck, the town is everything but
the garden, the backyard, the yard, the island and the road south past the neck; each of those opens only its own way
(the tree, the Rocket, the house, Surf, the S.S. Ticket); every door and sign can be reached.

Build it from the repository root with `sh project/art/cerulean-concept/build.sh` (or every map with
`sh project/art/build_all.sh`).

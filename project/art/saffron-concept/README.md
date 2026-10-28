# Saffron City after its concept

Kanto's golden city of commerce at the region's crossroads, rebuilt from the kit (`../kit`). The concept is this
folder's own: `draw_plan.py` draws the block plan (`plan_stage1.txt`) from shapes and says why things are where they
are.

![The map](map.png)

The city is 60×48 blocks (old Saffron was 66×55). Its joins aren't compiled: the routes around it join its twin,
`SaffronCity_Connection`, still the old layout, and keep clear of it (KR-34). From inside Saffron nothing shows beyond
its edges but its border's forest, so its size is its own and it has no seams. Two avenues cross in its middle, each
ending at a stone gatehouse, the way out to a route:
- **the north, west and east gatehouses** (to Routes 5, 7 and 8) have their double door on their south face, onto the
  avenue. The west and east ones' right door blocks are new warps (15, 16) to the same gatehouse doors;
- **the south gatehouse** (to Route 6) is entered walking south, through a doorway in its roof's back edge.

The city is paved block by block, as FireRed's is, with lamps along the pavements, and between the buildings you can
enter stand offices and arcades without doors (KR-88). The rest of the city:
- **the north-west**: Copycat's house, a house and a brick office on a lane off the avenue. The Fighting Dojo and
  Sabrina's Gym stand side by side on the Gym square, a narrow office beside the Gym. Until Silph Co. is freed,
  Rockets stand at the Gym's door, at Copycat's and at the house's;
- **the north-east**: Silph Co.'s tower, the tallest building in Kanto, on the Silph plaza. Its Rocket guard stands in
  its door until Mr. Fuji is rescued, then sleeps beside it. Next to it is the Magnet Train station, an arcade beside
  it: the train from Goldenrod comes in in front of the station, and its attendant arranges the journey back. Behind
  them, past a row of trees, is a garden with a pond where the Friends camp (scene 10, round 50,8);
- **the south**, along a street parallel to the avenue: the Pokémon Center, the Mart, Mr. Psychic's house and the
  Pokémon Trainer Fan Club, with three arcades between them. Below it, Saffron Park keeps its pond and lawn in the
  south-west, with two shops, a brick office and a narrow one on its east side; the south-east is the city's towers:
  sand and brick offices six to nine blocks tall.

Every warp keeps its number and the people their order. Every other spot fixed to the map moved with it:
- the heal spot (6,31, `src/data/heal_locations.json`; its old-map override dropped);
- the Friends' camp (`src/data/friends_scene_locations.h`);
- the credits' view (38,4, panning down past Silph Co.);
- where the Magnet Train lets you off (49,18, `GoldenrodCity_TrainStation_hns/scripts.inc`);
- where the guard stands until Mr. Fuji is rescued (38,18, the city's map script).

The attendant (the worker, who used to wander) now stands by the station. The people who stood where the new buildings
are stand beside them: the boy and his Pidgeot (51,27 and 52,27), a Pidgey (51,29, another at 26,40), the battle girl
(55,43) and the park's Rocket (7,34, on the lawn north of the pond).

The pieces:
- the kit's ground and plants; its Pokémon Center, Mart and lamp as Saffron's own copies standing on paving (the
  kit's tiles and banks, so no new tiles);
- six buildings from Kanto Buildings Remakes v0.3 (`../packs/buildings_v0.3/`), in one palette (bank 9): Silph Co.,
  Sabrina's Gym, the Fighting Dojo, the gatehouse (front and back) and the Magnet Train station, each with its own
  door frames (the gatehouse's is one wide double door);
- Viridian's pond keeper's house in its palette (bank 7) for Copycat's house, the house, Mr. Psychic's house and the
  Fan Club (KR-84);
- the city's blocks without doors (`make_art.py` `city_designs()`): offices 6×9, 6×6 and 4×6 put together from Silph
  Co.'s own 8×8 cells (its floors and window columns repeat), and a 4×4 arcade from the station's, in Silph's beige
  (bank 9) and two recolours of its palette, sand (bank 10) and brick (bank 11). They cost no tiles; their identical
  blocks share one metatile (pae's `"dedupe"`).

The city takes 355 of its 384 tiles and 379 of its 384 metatiles: a new design would need its own room. More copies of
these designs cost nothing. See `../ASSETS.md` for every pack and how to replace one.

`make_art.py` checks the city's rules on the map it builds:
- nothing walkable on its edges;
- everything walkable is reached from the avenues' crossing;
- every door can be walked into (the south gatehouse's from above), and every sign read;
- the Friends' camp, the train's stop and the walkers' paths are open ground.

Build it from the repository root with `sh project/art/saffron-concept/build.sh` (or every map with
`sh project/art/build_all.sh`).

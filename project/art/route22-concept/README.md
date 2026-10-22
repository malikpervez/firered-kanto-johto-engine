# Route 22 after the concept

The hilly route west of Viridian City to the Pokémon League Front Gate. The plan and the packs were made with
another AI from a brief, in two stages: a concept and block plan, then native pixel packs for what's new: the League
Front Gate, rocky cliffs and a dressed-stone paving for the League approach (`concept_comparison.png` puts the
approved concept beside the packs). This folder builds the route from the kit (`../kit`) and those packs.

![The map](map.png)

The route is 52×28 blocks, as before. The road from Viridian leaves the right edge at rows 6–9 (Viridian's rows
28–31), and Blue meets you on its straight stretch. It has:
- the League Front Gate (15×7 blocks) in the northwest, its roof against the cliff behind it, up a stone forecourt
  and a flight of stairs;
- rocky cliffs and terraces between pine forest walls;
- a dressed-stone approach from the road down to the gate, where it meets the cobblestones through joins;
- tall grass on both sides, a pond with lily pads and reeds, a ledge with steps, round trees and rocks.

## New pieces

- **The dressed-stone paving** (`../kit/paving/`) is in the kit's ground palette (its colours are the kit's), so every
  map can use it: `p` in a grid, with joins to cobblestones and dirt (`paving_to_cobble_N` and the like).
- **The rocky cliffs** (`cliff/`, `C` in the grid) are a 16-piece pack like the water's: the pieces are put together
  for each block by the cliff around it (`../kit/autotile.py`). They're meant for every route, but the kit has no
  palette slot left, so for now they're Route 22's own (bank 9).
- **The League Front Gate** (`buildings/`, bank 7): its top four rows stand against the cliff (cliff under them, `U`
  in the grid, joined to the cliff so it shows no edge there), its front over the lawn (`L`). Its door animates from
  its drawn frames (`pae door add --frames`).
- Stairs more than a row tall: the kit's steps go any way now (drawn by their neighbours east and west).

## Rebuild

From the repository root: `sh project/art/build_all.sh` rebuilds every map made from the kit.
`sh project/art/route22-concept/build.sh` alone runs `make_art.py` (which checks the road to Viridian is open, the
gate's door and the tall grass are reachable, Blue's road is clear and the top rows are only forest and cliff),
`pae tileset new` (the first time), `pae map geometry`, `pae tileset build`, `pae map paint`, `pae map connect`
(Viridian), `pae seam build`, `pae door add` and `pae map place` for the events.

Blue's scenes (`data/maps/Route22_Frlg/scripts.inc`): he appears seven blocks west of you in the row you're in
(`getplayerxy` and `setobjectxyperm`), so one trigger a row (6–9) does for the four-row road. He walks up to you,
battles, and leaves: east toward Viridian the first time, west toward the League the second.

Route 22 isn't joined to Route 23 anymore: that join was only seen across the top (both edges are solid; you go
through the gate), and Route 23's strip needs more palettes than Route 22 has free. Each shows its own border there
until Route 23 is rebuilt (`../WORLD.md`).

## In game

![The gate, up the stairs](in_game_gate.png)
![The stone approach from the road](in_game_approach.png)
![The pond and the tall grass](in_game_pond.png)
![Blue meets you on the road from Viridian](in_game_blue.png)

Replay tests: `viridian west to route 22`, `route 22 looks at viridian`, `route 22 enter the league gate`,
`route 22 blue on row 7`, `route 22 blue on row 9`.

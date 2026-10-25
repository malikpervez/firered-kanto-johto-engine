#!/usr/bin/env python3
"""Viridian Forest after the concept (concept.png, plan_stage1.txt and map_events.json: Viridian Forest Concept
v0.1, made with another AI from a brief, from the kit's art only): a winding forest walk from the south gate to the
north gate, with three bands of tall grass you can't walk round, two trainers on the trail whose lines of sight you
can't walk round, three item branches, a pond with a lawn beside it and a south-east glade.

The forest is 48x60 blocks (it was 74x79). Its exits are three blocks wide in the middle of the top and bottom rows
(columns 22-24): the south one is entered walking south (MB_SOUTH_ARROW_WARP), the north one by walking onto it
(MB_NON_ANIMATED_DOOR), as the old forest's were. Those six blocks are the map's own (its secondary tileset): the
lawn and the dirt path of the kit with the warp behaviours. The kit's forest is drawn in whole 2x2 cells, so the
one-block strip the concept leaves east of each exit (column 25) is bushes here.

Run from the repository root:  python3 project/art/viridianforest-concept/make_art.py
It writes sheets/, palette_7.pal, spec.json, grid.txt, border.txt and legend.json next to itself; build.sh turns
them into the game's tileset and map with pae.
"""
import json
import sys
from collections import deque
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import kit

HERE = Path(__file__).resolve().parent
SECONDARY = "gTileset_ViridianForestConcept"
MAP_W, MAP_H = 48, 60
EXITS = {"north": [(22, 0), (23, 0), (24, 0)], "south": [(22, MAP_H - 1), (23, MAP_H - 1), (24, MAP_H - 1)]}
BUSHES = [(25, 0), (25, 1), (25, MAP_H - 2), (25, MAP_H - 1)]  # the strip beside the exits (see above)
# the exit blocks' letters, by the ground the concept has in the row inside them: lawn or the dirt path
EXIT_LETTERS = {("north", "."): "Y", ("north", ":"): "^", ("south", "."): "y", ("south", ":"): "!"}
EXIT_BEHAVIOR = {"north": "MB_NON_ANIMATED_DOOR", "south": "MB_SOUTH_ARROW_WARP"}
SOLID = set("Tb" "R" "o" "k" "S" "~vr")  # what you can't walk onto (no ledges here)


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 48x60"
    return g


def events() -> dict:
    return json.loads((HERE / "map_events.json").read_text())


def fit(g: list[list[str]], ev: dict) -> list[list[str]]:
    """The plan as the kit builds it: the events' letters (trainers B, people n, item balls i, hidden items z,
    Pokémon m) are the ground the concept has under them; the exits e are the exit pieces; the strip beside the
    exits is bushes."""
    ground = ev["event_ground"]
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] in "Bnizm":
                g[y][x] = ground[f"{x},{y}"]
    for side, blocks in EXITS.items():
        inside = 1 if side == "north" else MAP_H - 2
        for x, y in blocks:
            assert g[y][x] == "e", f"({x},{y}): the plan's exit moved"
            g[y][x] = EXIT_LETTERS[side, g[inside][x]]
    for x, y in BUSHES:
        assert g[y][x] == "T"
        g[y][x] = "b"
    return g


def check(g, ev) -> None:
    """The concept's rules on the map as built: the forest is whole 2x2 cells; nothing but the exits opens onto the
    edges; everything walkable is one area, reached from the south exit with every trainer, person and item ball
    in place; every sign can be read from the block below it and every item ball reached; the three bands of tall
    grass can't be walked round; and the two trainers on the trail can't be walked round either."""
    for cy in range(0, MAP_H, 2):
        for cx in range(0, MAP_W, 2):
            cell = {g[cy + j][cx + i] for i in (0, 1) for j in (0, 1)}
            assert cell == {"T"} or "T" not in cell, f"({cx},{cy}): a forest cell that isn't whole"
    exits = {xy for v in EXITS.values() for xy in v}
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == exits, "only the exits open onto the edges"
    people = {tuple(e["at"]) for k in ("trainers", "people", "items") for e in ev[k]}
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID} - people

    def reach(start, blocked=frozenset()):
        seen, todo = {start}, deque([start])
        while todo:
            x, y = todo.popleft()
            for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
                if n in walk and n not in seen and n not in blocked:
                    seen.add(n)
                    todo.append(n)
        return seen
    south, north = (23, MAP_H - 1), (23, 0)
    everywhere = reach(south)
    assert everywhere == walk, f"blocks you can't reach: {sorted(walk - everywhere)[:8]}"
    assert all((s["at"][0], s["at"][1] + 1) in everywhere for s in ev["signs"]), "a sign can't be read"
    for i in ev["items"]:
        x, y = i["at"]
        assert {(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)} & everywhere, f"{i['id']} can't be reached"
    for x0, y0, w, h in ev["mandatory_grass_rectangles"]:
        band = {(x, y) for x in range(x0, x0 + w) for y in range(y0, y0 + h) if g[y][x] == "g"}
        assert north not in reach(south, band), f"the tall grass at ({x0},{y0}) can be walked round"
    for t in ev["trainers"]:
        if t["role"] == "main trail":
            assert north not in reach(south, {tuple(b) for b in t["sight_blocks"]}), f"{t['id']} can be walked round"


def exit_pieces(g) -> list[tuple[str, str, int | None]]:
    """(letter, piece name, dirt mask) of each exit block as pae map paint draws it: the dirt path's exit blocks
    join the path (its piece by its neighbours, the map's edge counting as path), the lawn's are one piece."""
    out = []
    for side, blocks in EXITS.items():
        for x, y in blocks:
            c = g[y][x]
            if c in "Yy":
                out.append((c, f"exit_{side}_lawn", None))
                continue

            def path(nx, ny):
                return not (0 <= nx < MAP_W and 0 <= ny < MAP_H) or g[ny][nx] in (":", c)
            mask = sum(bit for bit, (dx, dy) in ((1, (0, -1)), (2, (1, 0)), (4, (0, 1)), (8, (-1, 0)))
                       if path(x + dx, y + dy))
            out.append((c, f"exit_{side}#{mask}", mask))
    return out


def main() -> None:
    ev = events()
    g = fit(plan(), ev)
    kit.check_forest(g)
    kit.check_water(g)
    check(g, ev)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    sh = kit.Sheet("forest_exits", kit.PALS["ground"], kit.BANK["ground"], HERE, HERE, cols=6)
    lawn_a = kit.lawn.tiles(kit.LAWN, kit.P0)["lawn_a"]
    pieces = sorted(set(exit_pieces(g)), key=lambda p: p[1])
    for _, name, mask in pieces:
        side = name.split("_")[1].split("#")[0]
        if mask is None:
            sh.add(name, lawn_a, tileset="secondary", behavior=EXIT_BEHAVIOR[side])
        else:
            sh.add(name, kit.dirt(mask), tileset="secondary", ground="grass", behavior=EXIT_BEHAVIOR[side])
    spec_mt += sh.write()
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    kit.write_palette(HERE / "palette_7.pal", kit.PALS["ground"])  # bank 7 isn't used; the plants are bank 8
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": ["palette_7.pal", base["secondary_palettes"][8]]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND)
    for letter, name, mask in pieces:
        legend[letter] = name if mask is None else {"auto": name.split("#")[0], "joins": ":"}
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; exits {[p[1] for p in pieces]}")


if __name__ == "__main__":
    main()

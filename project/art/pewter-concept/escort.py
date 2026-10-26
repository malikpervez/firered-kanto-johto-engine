#!/usr/bin/env python3
"""The walks Pewter's guides lead you on (the Gym guide to the Gym, the Museum guide to the Museum), worked out on the
map as it's built and written into engine/data/maps/PewterCity_Frlg/scripts.inc. Run it after build.sh (it reads the
painted grid and the people's places):  python3 project/art/pewter-concept/escort.py

Each way the scene can start (where you stand when the guide takes you, and where the guide is then) is a start for
the guide and one for you, side by side. The guide walks the shortest way to the block in front of the door (the
fewest turns among them, round everyone standing in town), arriving from the south; you follow in his footsteps one
step behind (your first step is onto his block, as he leaves it). At the door he steps aside and turns to you, and you
arrive in front of the door facing it. Then he walks off (his exit) and is removed.
"""
import heapq
import json
import re
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
sys.path.insert(0, str(HERE))
import make_art  # noqa: E402  (its SOLID: what can't be walked onto)

SCRIPTS = ROOT / "engine/data/maps/PewterCity_Frlg/scripts.inc"
MAP = ROOT / "engine/data/maps/PewterCity_Frlg/map.json"
STEP = {(0, -1): "walk_up", (0, 1): "walk_down", (-1, 0): "walk_left", (1, 0): "walk_right"}
FACE = {(0, -1): "walk_in_place_faster_up", (0, 1): "walk_in_place_faster_down",
        (-1, 0): "walk_in_place_faster_left", (1, 0): "walk_in_place_faster_right"}

# the Gym guide (he stands at 43,24): (his block, yours) when the walk starts, after his first steps to lead you
GYM = {"Top": ((42, 25), (43, 25)), "Mid": ((43, 25), (43, 26)), "Bottom": ((43, 26), (43, 27)),
       "East": ((42, 25), (42, 24)), "West": ((43, 24), (44, 24)), "North": ((43, 24), (43, 25)),
       "Right": ((45, 27), (46, 27))}
# the Museum guide (39,17) walks straight off; you stand where you talked to him
MUSEUM = {"North": ((39, 17), (39, 18)), "South": ((39, 17), (39, 16)), "West": ((39, 17), (40, 17)),
          "East": ((39, 17), (38, 17))}


def walkable():
    g = [list(r) for r in (HERE / "grid.txt").read_text().split("\n")[:make_art.MAP_H]]
    people = {(o["x"], o["y"]) for o in json.loads(MAP.read_text())["object_events"]}
    return {(x, y) for y in range(make_art.MAP_H) for x in range(make_art.MAP_W)
            if g[y][x] not in make_art.SOLID}, people


def path(free, start, goal, avoid_first=None):
    """The shortest walk from ``start`` to ``goal`` with the fewest turns among the shortest (steps as (dx, dy))."""
    todo = [(0, 0, start, None, ())]
    best = {}
    while todo:
        n, turns, at, d, steps = heapq.heappop(todo)
        if at == goal:
            return list(steps)
        if best.get((at, d), (1 << 30,)) <= (n, turns):
            continue
        best[at, d] = (n, turns)
        for dd in STEP:
            nxt = (at[0] + dd[0], at[1] + dd[1])
            if nxt not in free or (not steps and nxt == avoid_first):
                continue
            heapq.heappush(todo, (n + 1, turns + (d is not None and dd != d), nxt, dd, steps + (dd,)))
    raise SystemExit(f"no way from {start} to {goal}")


def walks(free, people, starts, door, aside, face):
    """For each start: (the guide's movement, yours): to the block below ``door``'s front, then up to it."""
    front, below = (door[0], door[1] + 1), (door[0], door[1] + 2)
    out = {}
    for name, (g0, p0) in starts.items():
        ok = (free - people) | {g0, p0}
        steps = path(ok, g0, below, avoid_first=p0) + [(0, -1)]
        lead = (g0[0] - p0[0], g0[1] - p0[1])
        assert lead in STEP, f"{name}: you must start beside the guide"
        assert (front[0] + aside[0], front[1] + aside[1]) in free, f"{name}: no room to step aside at the door"
        guide = [STEP[s] for s in steps] + [STEP[aside], FACE[face]]
        you = [STEP[lead]] + [STEP[s] for s in steps]
        out[name] = guide, you
    return out


def body(moves):
    return "".join(f"\t{m}\n" for m in moves) + "\tstep_end\n"


def replace_label(text, label, moves):
    m = re.search(rf"^{label}::\n(?:\t.*\n)*?\tstep_end\n", text, re.M)
    assert m, f"{label} not in scripts.inc"
    return text[:m.start()] + f"{label}::\n" + body(moves) + text[m.end():]


def drop_macro(text, name):
    return re.sub(rf"^\.macro {name}\n(?:.*\n)*?\.endm\n\n?", "", text, flags=re.M)


def main():
    free, people = walkable()
    text = SCRIPTS.read_text()
    gym = walks(free, people, GYM, make_art.doors_of()["W"], (1, 0), (-1, 0))
    for name, (guide, you) in gym.items():
        text = replace_label(text, f"PewterCity_Movement_GuideWalkToGym{name}", guide)
        text = replace_label(text, f"PewterCity_Movement_PlayerWalkToGym{name}", you)
    museum = walks(free, people, MUSEUM, make_art.doors_of()["U"], (-1, 0), (0, -1))
    for name, (guide, you) in museum.items():
        text = replace_label(text, f"PewterCity_Movement_GuideWalkToMuseum{name}", guide)
        text = replace_label(text, f"PewterCity_Movement_PlayerWalkToMuseum{name}", you + ["delay_8",
                                                                                         "walk_in_place_faster_up"])
    # their exits: from beside the door back along the way they came, until out of sight of it
    gdoor, mdoor = make_art.doors_of()["W"], make_art.doors_of()["U"]
    gym_aside = (gdoor[0] + 1, gdoor[1] + 1)
    text = replace_label(text, "PewterCity_Movement_GymGuideExit",
                         [STEP[s] for s in path(free - people, gym_aside, (21, 23))])
    museum_aside = (mdoor[0] - 1, mdoor[1] + 1)
    text = replace_label(text, "PewterCity_Movement_MuseumGuideExit",
                         [STEP[s] for s in path(free - people, museum_aside, (33, 16))])
    for name in ("walk_to_gym", "walk_to_gym_alt", "walk_to_museum", "walk_to_museum_south"):
        text = drop_macro(text, name)
    SCRIPTS.write_text(text)
    for name, (guide, you) in {**{f"gym {k}": v for k, v in gym.items()},
                               **{f"museum {k}": v for k, v in museum.items()}}.items():
        print(f"{name}: the guide {len(guide)} moves, you {len(you)}")


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""Lavender Town after its concept (draw_plan.py and plan_stage1.txt): the quiet town in a hollow of the hills (see
draw_plan.py). It is 38x32 blocks (old Lavender was 38x31), as wide as before; its joins stay where its neighbours meet
it: Route 10's road the top at columns 12-16 (Route 10's 16-20, offset -4), Route 8's the left edge at rows 9-11 (Route
8's 13-15, offset -4), Route 12's the bottom at columns 13-15 (Route 12's 11-13, offset 2; it was -2, the old town
sitting 4 blocks further east over Route 12).

The pieces: the kit's, the Pokémon Center and the Mart (the kit's), Viridian's three houses in their palette (bank 7),
and Pokémon Tower, drawn here (buildings/pokemon_tower, written by pokemon_tower()) in a palette of its own (bank 9).
Bank 8 is the kit's plants palette; 10-12 stay free for the seams to old Routes 8 and 12.

Run from the repository root:  python3 project/art/lavender-concept/make_art.py
It writes buildings/pokemon_tower/, sheets/, the palettes, spec.json, grid.txt, border.txt, legend.json and doors.json
next to itself; build.sh turns them into the game's tileset and map with pae.
"""
import json
import sys
from collections import deque
from pathlib import Path

import numpy as np
from PIL import Image

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "kit"))
import buildings
import kit

HERE = Path(__file__).resolve().parent
ART = HERE.parent
SECONDARY = "gTileset_LavenderConcept"
MAP_W, MAP_H = 38, 32
HOUSE_BANK, TOWER_BANK = 7, 9
VB = ART / "viridian-concept/buildings"
GYM = ART / "pewter-concept/buildings/pewter_gym"
TOWER = HERE / "buildings/pokemon_tower"
NORTH = [(x, 0) for x in range(12, 17)]
WEST = [(0, y) for y in range(9, 12)]
SOUTH = [(x, MAP_H - 1) for x in range(13, 16)]
CAMP = [(13, 13), (12, 12), (11, 13), (14, 12), (12, 14), (10, 14), (15, 13)]  # the Friends', as before
SOLID = set("T#bRoklSBcw_~vrZLXHUW")
# Pewter's stone palette, index by index, made the tower's: its slate roof a deep violet, its warm stone a lavender
# grey, its gold kept (the windows' candlelight); the Gym's door frames, drawn in the same indices, come out in it too
TOWER_PAL = [(0, 0, 0), (24, 16, 40), (56, 40, 80), (80, 64, 112), (112, 88, 144), (152, 128, 176), (192, 176, 208),
             (96, 88, 112), (136, 128, 152), (176, 168, 192), (208, 200, 224), (232, 224, 240), (136, 104, 56),
             (192, 152, 72), (232, 200, 120), (48, 40, 72)]


def pokemon_tower() -> buildings.Building:
    """Pokémon Tower, 5x7 blocks: a pointed violet roof under a gold finial, three storeys of windows lit by candles
    under slate eaves, a broad base with the door in its middle (Pewter's Gym's door frames, in the tower's colours)."""
    TOWER.mkdir(parents=True, exist_ok=True)
    w, h = 80, 112
    a = np.zeros((h, w), np.uint8)
    a[0:5, 39:41] = 13                                      # the finial
    for r in range(4, 18):                                  # the roof, widening down to its eaves
        hw = min(38, 2 + (r - 4) * 3)
        a[r, 40 - hw:40 + hw] = 3
        a[r, 40 - hw + 1:40 - hw + 3] = 4                   # light on its west slope
        a[r, 40:40 + hw - 1][::4] = 2                       # standing seams
    a[16:18, 2:78] = 2
    for k, top in enumerate((18, 37, 56)):                  # three storeys: an eave, then the wall and its windows
        inset = 8 - k * 2
        a[top:top + 3, inset - 4:w - inset + 4] = 2
        a[top + 1, inset - 4:w - inset + 4] = 3
        a[top + 3:top + 19, inset:w - inset] = 8
        a[top + 3:top + 19, inset:inset + 2] = 9            # the walls' lit west edge,
        a[top + 3:top + 19, w - inset - 2:w - inset] = 7    # and shaded east edge
        for x0 in (inset + 8, 36, w - inset - 16):
            a[top + 6:top + 15, x0:x0 + 8] = 7              # the window's frame,
            a[top + 7:top + 14, x0 + 1:x0 + 7] = 15         # its dark glass,
            a[top + 11:top + 14, x0 + 2:x0 + 6] = 13        # and a candle's glow
            a[top + 12:top + 14, x0 + 3:x0 + 5] = 14
    a[75:80, 0:80] = 2                                      # the base's broad eave
    a[76, 0:80] = 3
    a[80:106, 4:76] = 8                                     # the base
    a[80:106, 4:6] = 9
    a[80:106, 74:76] = 7
    for x0 in (10, 56):                                     # its windows either side of the door
        a[86:98, x0:x0 + 14] = 7
        a[87:97, x0 + 1:x0 + 13] = 15
        a[92:97, x0 + 2:x0 + 12] = 13
        a[94:97, x0 + 4:x0 + 10] = 14
    a[106:112, 2:78] = 7                                    # the plinth
    a[106, 2:78] = 9
    shape = a > 0                                           # a dark outline round it all
    edge = shape & ~(np.pad(shape, 1)[2:, 1:-1] & np.pad(shape, 1)[:-2, 1:-1]
                     & np.pad(shape, 1)[1:-1, 2:] & np.pad(shape, 1)[1:-1, :-2])
    a[edge] = 1
    # the door: Pewter's Gym's three frames, each colour the tower's at the Gym's index
    gym_pal = [tuple(c) for c in np.array(Image.open(GYM / "pewter_gym.png").getpalette()[:48]).reshape(16, 3)]
    to_index = {c: i for i, c in enumerate(gym_pal)}
    frames = np.array(Image.open(GYM / "pewter_gym_door.png").convert("RGBA"))
    letters = frames[2:9] == np.array([*gym_pal[2], 255], np.uint8)  # the Gym board's letters, over the door,
    frames[2:9][letters.all(axis=2)] = [*gym_pal[10], 255]           # painted out: a plain board
    out = frames.copy()
    for y in range(frames.shape[0]):
        for x in range(frames.shape[1]):
            r, g_, b, al = frames[y, x]
            if al:
                out[y, x, :3] = TOWER_PAL[to_index[(r, g_, b)]]
    Image.fromarray(out, "RGBA").save(TOWER / "pokemon_tower_door.png")
    closed = frames[:, 0:16]
    for y in range(32):
        for x in range(16):
            if closed[y, x, 3]:
                a[80 + y, 32 + x] = to_index[tuple(closed[y, x, :3])]
    im = Image.fromarray(a, "P")
    im.putpalette([v for c in TOWER_PAL for v in c] + [0] * (768 - 48))
    im.save(TOWER / "pokemon_tower.png", transparency=0)
    meta = {"schema_version": 2, "id": "pokemon_tower", "type": "building", "image": "pokemon_tower.png",
            "image_size_px": [w, h], "block_size_px": 16, "footprint_blocks": {"width": 5, "height": 7},
            "transparent_index": 0, "door_block": [2, 6],
            "collision_rows": ["#####"] * 6 + ["##D##"],
            "door": {"image": "pokemon_tower_door.png", "sheet_size_px": [48, 32], "frame_size_px": [16, 32],
                     "frame_count": 3, "frame_order": ["closed", "half_open", "open"],
                     "anchor_top_left_px": [32, 80], "anchor_top_left_block": [2, 5],
                     "closed_frame_matches_building_crop": True},
            "name": "pokemon_tower",
            "source": "drawn by lavender-concept/make_art.py; its door is Pewter's Gym's, recoloured"}
    (TOWER / "pokemon_tower.json").write_text(json.dumps(meta, indent=2) + "\n")
    return buildings.load(TOWER)


# the buildings: their letters in the plan, where each comes from and its palette's bank
OWN = {"H": (VB / "house_family", HOUSE_BANK), "U": (VB / "house_pond_keeper", HOUSE_BANK),
       "W": (VB / "house_gardener", HOUSE_BANK)}
SHARED = {"Z": "pokemon_center", "L": "poke_mart"}


def load(letter: str) -> buildings.Building:
    if letter in SHARED:
        return kit.SHARED_BUILDINGS[SHARED[letter]][0]
    if letter == "X":
        return buildings.load(TOWER)
    return buildings.load(OWN[letter][0])


def plan() -> list[list[str]]:
    rows = (HERE / "plan_stage1.txt").read_text().split("\n")[:MAP_H]
    g = [list(r) for r in rows]
    assert len(g) == MAP_H and all(len(r) == MAP_W for r in g), "the plan is 38x32"
    return g


def doors(g) -> dict[str, list[tuple[int, int]]]:
    out = {}
    for letter in list(SHARED) + ["X"] + list(OWN):
        b = load(letter)
        bw, bh = b.idx.shape[1] // 16, b.idx.shape[0] // 16
        cells = {(x, y) for y, r in enumerate(g) for x, c in enumerate(r) if c == letter}
        x0, y0 = min(cells)
        assert cells == {(x0 + i, y0 + j) for i in range(bw) for j in range(bh)}, f"{letter} isn't its footprint"
        out[letter] = [(x0 + b.door[0], y0 + b.door[1])]
    return out


def reachable(g, starts) -> set[tuple[int, int]]:
    seen, todo = set(starts), deque(starts)
    while todo:
        x, y = todo.popleft()
        for n in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if 0 <= n[0] < MAP_W and 0 <= n[1] < MAP_H and n not in seen and g[n[1]][n[0]] not in SOLID:
                seen.add(n)
                todo.append(n)
    return seen


def check(g, d) -> None:
    """The town's rules: only its three roads open onto the edges; everything walkable is reached from Route 10's
    road; every door can be walked into from the block below it, every sign read from it; the Friends' camp is open
    ground."""
    edge = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if x in (0, MAP_W - 1) or y in (0, MAP_H - 1)}
    assert {xy for xy in edge if g[xy[1]][xy[0]] not in SOLID} == set(NORTH + WEST + SOUTH), "only the roads open"
    town = reachable(g, NORTH)
    walk = {(x, y) for y in range(MAP_H) for x in range(MAP_W) if g[y][x] not in SOLID}
    assert walk <= town, f"blocks you can't reach: {sorted(walk - town)[:8]}"
    for letter, ds in d.items():
        for x, y in ds:
            assert (x, y + 1) in town, f"the door of {letter} at ({x},{y}) can't be walked into"
    for y in range(MAP_H):
        for x in range(MAP_W):
            if g[y][x] == "S":
                assert (x, y + 1) in town, f"the sign at ({x},{y}) can't be read"
    assert set(CAMP) <= town, "the Friends' camp must be open ground"


def main() -> None:
    pokemon_tower()
    g = plan()
    d = doors(g)
    kit.check_forest(g)
    kit.check_water(g)
    check(g, d)
    base = kit.primary(HERE)  # the kit: the primary tileset every map shares
    spec_mt = list(base["metatiles"])
    pals = {}
    for letter, (folder, bank) in list(OWN.items()) + [("X", (TOWER, TOWER_BANK))]:
        b = load(letter)
        pals.setdefault(bank, b.palette)
        if pals[bank] != b.palette:
            raise SystemExit(f"{folder.name}: its palette isn't the one bank {bank} has")
        sh = kit.Sheet(b.name, b.palette, bank, HERE, HERE, cols=b.idx.shape[1] // 16)
        sh.add(b.name, b.idx, tileset="secondary", **b.entry())
        spec_mt += sh.write()
    for e in spec_mt:  # sheets put "w"/"h" on everything; drop the 1x1 ones for readability
        if e["w"] == 1 and e["h"] == 1:
            del e["w"], e["h"]
    for bank, pal in pals.items():
        kit.write_palette(HERE / f"palette_{bank}.pal", pal)
    spec = {"version": "hns", "primary": kit.PRIMARY, "secondary": SECONDARY,
            "palettes": {"primary": base["palettes"],
                         "secondary": [f"palette_{HOUSE_BANK}.pal", base["secondary_palettes"][8],
                                       f"palette_{TOWER_BANK}.pal"]},
            "reserve": {"primary": base["reserve"]},
            "animations": base["animations"],
            "field_effects": base["field_effects"],
            "metatiles": spec_mt}
    (HERE / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (HERE / "grid.txt").write_text("".join("".join(r) + "\n" for r in g))
    (HERE / "border.txt").write_text("TT\nTT\n")
    legend = dict(kit.LEGEND, **SHARED, X="pokemon_tower", **{k: load(k).name for k in OWN})
    (HERE / "legend.json").write_text(json.dumps(legend, indent=1) + "\n")
    (HERE / "doors.json").write_text(json.dumps(d, indent=1) + "\n")
    print(f"{len(spec_mt)} metatiles in the spec; grid {MAP_W}x{MAP_H}; doors {d}")


if __name__ == "__main__":
    main()

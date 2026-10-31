"""Settle a map's plan before pae builds it (run after the map's make_art.py): three fixes every kit map needs.

1. The kit's small pieces into the ground they stand in. A sign, a lamp, a boat, a barrel, a rock... has its ground
   baked into its block (the sign and the lamp stand on grass, the boat on the pond). Put one inside another surface
   (a lamp in the paving, a sign on a dirt path, a boat in the sea) and two things go wrong: the piece shows a square of
   its own ground there, and the surface, whose letter doesn't count the piece's as its own, draws its edge round it (a
   lawn rim in the paving, a shore round the boat). So for each such piece standing inside one surface (that surface on
   three quarters of its sides that touch ground, or on two opposite ones; buildings and other pieces beside it don't
   count either way), this makes the piece again in the map's own (secondary) tileset over the block the surface would
   draw there (its edge variant from the same neighbours) and puts it in the surface's group ({"joins": ...}), so the
   surface runs on round it. Pieces already over the right ground only join (no new tiles).
2. The forest on its grid. The kit's forest is drawn in 2x2 cells on the even grid, so a plan whose forest ends on an
   odd row or column shows half trees (crowns cut flat, trunks halved). Each cut cell is made whole: filled with forest
   where the rest of it is plain lawn or flowers, else trimmed back to the lawn beside it, and only where that changes
   nobody's way: no event on it, no walkable place cut off, no new way through.
3. Water up to the docks. A dock or a bridge over the water draws its own outline; the water beside it, whose letter
   isn't the dock's, drew a shore against it (foam, stone, grass), so a bridge looked like an embankment. The water
   next to a dock now takes the piece it would have if the dock were water.

Usage: python3 project/art/kit/settle.py project/art/<map>-concept [GRID ...]   (GRID defaults to grid.txt)
It rewrites the grids, legend.json and spec.json in place, adds sheets/settled_*.png, and prints what it changed."""
import json
import re
import sys
from collections import deque
from pathlib import Path

import numpy as np
from PIL import Image

sys.path.insert(0, str(Path(__file__).parent))
import kit  # noqa: E402

# the kit's small pieces that can stand anywhere; buildings, trees, bushes and flowers are left to each map's plan
PIECES = {"sign", "lamp", "boat", "barrel", "crate", "stump", "field_rock_a", "field_rock_b", "field_rock_c"}
# the surfaces a piece can stand in (not the fence, the forest, ledges, steps or cliff tops, which aren't ground)
GROUNDS = {"pond", "sea", "cobble", "dirt", "dock", "paving", "pavement", "kerb", "brick", "granite", "track",
           "walk_s", "walk_n", "asphalt", "setts", "quay"}
LAWN = ("lawn", "grass", "flowers", "lawn_flowers")
# new legend letters (unused by any plan)
LETTERS = [chr(c) for c in range(0x2C00, 0x2C5F)]
SIDES = ((1, (0, -1)), (2, (1, 0)), (4, (0, 1)), (8, (-1, 0)))
CORNERS = ((1, (1, -1), 1 | 2), (2, (1, 1), 2 | 4), (4, (-1, 1), 4 | 8), (8, (-1, -1), 8 | 1))
ROOT = Path(__file__).resolve().parents[3]


class Plan:
    def __init__(self, here: Path, grid_names: list[str]):
        self.here = here
        self.spec = json.loads((here / "spec.json").read_text())
        self.legend = json.loads((here / "legend.json").read_text())
        self.meta = {e["name"]: e for e in self.spec["metatiles"]}
        self.grids = {n: [list(r) for r in (here / n).read_text().splitlines() if r.strip() and not r.startswith("#")]
                      for n in grid_names}
        used = {c for g in self.grids.values() for row in g for c in row} | set(self.legend)
        self.free = [c for c in LETTERS if c not in used]
        self.maps = self.map_names()

    def map_names(self) -> dict[str, str]:
        """grid file -> map name, from the map's build.sh (its pae map paint lines)."""
        sh = (self.here / "build.sh").read_text()
        var = dict(re.findall(r"^(\w+)=(\w+_Frlg)\s*$", sh, re.M))
        out = {}
        for v, grid in re.findall(r"pae map paint \$?(\w+) \S*/(grid\w*\.txt)", sh):
            out[grid] = var.get(v, v)
        return out

    def item(self, c):
        it = self.legend.get(c)
        return {"name": it} if isinstance(it, str) else dict(it or {})

    def group(self, c):
        it = self.legend.get(c)
        return it.get("joins", c) if isinstance(it, dict) else c

    def piece_name(self, c, x, y):
        it = self.item(c)
        if "pick" in it and it.get("order") != "checker":
            names = it["pick"]
            return names[(x * 7919 + y * 104729 + (x * y) % 13) % len(names)]
        return it.get("name") or it.get("tile")

    def solid(self, c, x, y) -> bool:
        it = self.item(c)
        if "solid" in it:
            return bool(it["solid"])
        name = it.get("auto") and (f"{it['auto']}#15" if f"{it['auto']}#15" in self.meta else it["auto"])
        name = name or self.piece_name(c, x, y)
        m = self.meta.get(name, {})
        elev = it.get("elevation", m.get("elevation"))
        return bool(m.get("solid")) or elev == 1  # water: not on foot

    def lawnish(self, c, x, y) -> bool:
        it = self.item(c)
        if "auto" in it or it.get("solid"):
            return False
        name = self.piece_name(c, x, y) or ""
        m = self.meta.get(name, {})
        return name.startswith(LAWN) and not m.get("solid") and not m.get("ground")

    def write(self):
        (self.here / "spec.json").write_text(json.dumps(self.spec, indent=1) + "\n")
        (self.here / "legend.json").write_text(json.dumps(self.legend, indent=1, ensure_ascii=False) + "\n")
        for gname, g in self.grids.items():
            (self.here / gname).write_text("".join("".join(r) + "\n" for r in g))

    def events(self, gname) -> set[tuple[int, int]]:
        m = self.maps.get(gname)
        f = ROOT / "engine/data/maps" / str(m) / "map.json"
        if not m or not f.exists():
            return set()
        d = json.loads(f.read_text())
        return {(e["x"], e["y"]) for k in ("object_events", "warp_events", "coord_events", "bg_events")
                for e in d.get(k) or []}


def ground_name(p: Plan, g, cells, auto, same):
    """The piece pae map paint would draw for ``auto`` at each of ``cells``, with ``same(x, y)`` its neighbours."""
    out = []
    for cx, cy in cells:
        mask = sum(b for b, (dx, dy) in SIDES if same(cx + dx, cy + dy))
        corners = sum(b for b, (dx, dy), s in CORNERS if mask & s == s and not same(cx + dx, cy + dy))
        out.append(next((n for n in (f"{auto}#{mask}.{corners}" if corners else None, f"{auto}#{mask}",
                                     f"{auto}#15", auto) if n and n in p.meta), None))
    return out


def settle_pieces(p: Plan) -> list[str]:
    made = {}      # (piece, grounds tuple, joins) -> (new name, letter)
    report = []
    for gname, g in p.grids.items():
        h, w = len(g), len(g[0])
        found, done = [], set()
        for y in range(h):
            for x in range(w):
                if (x, y) in done:
                    continue
                it = p.item(g[y][x])
                name = p.piece_name(g[y][x], x, y)
                if "auto" in it or "tile" in it or name not in PIECES or name not in p.meta:
                    continue
                m = p.meta[name]
                cells = [(x + i, y + j) for j in range(m.get("h", 1)) for i in range(m.get("w", 1))]
                done |= set(cells)
                count, ground_sides = {}, 0  # sides on a ground surface; on lawn; buildings and pieces count neither
                for cx, cy in cells:
                    for bit, (dx, dy) in SIDES:
                        xx, yy = cx + dx, cy + dy
                        if (xx, yy) in cells or not (0 <= xx < w and 0 <= yy < h):
                            continue
                        n = g[yy][xx]
                        if p.item(n).get("auto") in GROUNDS:
                            count.setdefault(p.group(n), set()).add((bit, cx, cy))
                            ground_sides += 1
                        elif p.lawnish(n, xx, yy):
                            ground_sides += 1
                if not count:
                    continue
                A = max(count, key=lambda k: len(count[k]))
                bits = {b for b, _, _ in count[A]}
                if not (len(count[A]) * 4 >= ground_sides * 3 or {1, 4} <= bits or {2, 8} <= bits):
                    continue
                found.append((x, y, name, cells, A))
        settled = {c: A for (_, _, _, cells, A) in found for c in cells}
        for x, y, name, cells, A in found:
            m = p.meta[name]
            a_char = next(ch for ch in p.legend if p.group(ch) == A and p.item(ch).get("auto") in GROUNDS)
            auto = p.item(a_char)["auto"]
            docks = {c for c in p.legend if p.item(c).get("auto") == "dock"} if auto in ("pond", "sea") else set()
            grounds = ground_name(p, g, cells, auto, lambda xx, yy: (
                not (0 <= xx < w and 0 <= yy < h) or settled.get((xx, yy)) == A or p.group(g[yy][xx]) == A
                or g[yy][xx] in docks))
            if None in grounds:
                report.append(f"  skip {name} at ({x},{y}): no ground piece for {auto}")
                continue
            key = (name, tuple(grounds), A)
            if key not in made:
                same_ground = all(gn == m.get("ground") for gn in grounds)
                made[key] = (name if same_ground else f"{name}@{'+'.join(grounds)}", p.free.pop(0))
            new, letter = made[key]
            for cx, cy in cells:
                g[cy][cx] = letter
            p.legend[letter] = {"name": new, "joins": A}
            report.append(f"  piece {gname} ({x},{y}) {name} on {m.get('ground')} in '{a_char}' ({auto}) -> "
                          f"{new if new != name else 'joins only'}")
    sheets, entries = {}, []
    for (name, grounds, A), (new, letter) in made.items():
        if new == name:
            continue
        m = p.meta[name]
        bank = m["banks"][0]
        pal_name = next(k for k, v in kit.BANK.items() if v == bank)
        pal = kit.PALS[pal_name]
        src = Image.open(p.here / m["image"]).convert("RGBA")
        px = np.array(src.crop((m["x"], m["y"], m["x"] + 16 * m.get("w", 1), m["y"] + 16 * m.get("h", 1))))
        lut = {tuple(c): i for i, c in enumerate(pal) if i}
        idx = np.zeros(px.shape[:2], np.uint8)
        for (yy, xx), _ in np.ndenumerate(idx):
            r, gg, b, al = (int(v) for v in px[yy, xx])
            if al:
                idx[yy, xx] = lut[(r, gg, b)]
        sh = sheets.setdefault(bank, kit.Sheet(f"settled_{pal_name}", pal, bank, p.here, p.here, cols=8))
        extra = {k: v for k, v in m.items() if k in ("solid", "elevation", "over_rows", "behaviors", "open",
                                                     "row_banks")}
        sh.add(new, idx, tileset="secondary", ground=list(grounds) if len(grounds) > 1 else grounds[0], **extra)
    for sh in sheets.values():
        entries += sh.write()
    for e in entries:
        if e.get("w") == 1 and e.get("h") == 1:
            del e["w"], e["h"]
    p.spec["metatiles"] += entries
    if made:
        report.append(f"  {len(entries)} new pieces; {sum(1 for k, v in made.items() if v[0] == k[0])} kinds only join")
    return report


def components(p: Plan, g, extra_shut=()):
    """Walkable cells (not solid, not water) -> the number of the connected piece they're in."""
    h, w = len(g), len(g[0])
    shut = set(extra_shut)
    ok = {(x, y) for y in range(h) for x in range(w) if not p.solid(g[y][x], x, y) and (x, y) not in shut}
    comp, k = {}, 0
    for c in ok:
        if c in comp:
            continue
        k += 1
        comp[c] = k
        q = deque([c])
        while q:
            x, y = q.popleft()
            for _, (dx, dy) in SIDES:
                n = (x + dx, y + dy)
                if n in ok and n not in comp:
                    comp[n] = k
                    q.append(n)
    return comp


def snap_forest(p: Plan) -> list[str]:
    report = []
    for gname, g in p.grids.items():
        h, w = len(g), len(g[0])
        fchars = [c for c in p.legend if p.item(c).get("auto") == "forest" and "joins" not in p.item(c)]
        if not fchars:
            continue
        F = fchars[0]
        first = p.meta.get("forest#15") or {}
        cw, ch = first.get("w", 1), first.get("h", 1)
        if cw < 2 and ch < 2:
            continue
        events = p.events(gname)
        fixed = left = 0
        for y0 in range(0, h, ch):
            for x0 in range(0, w, cw):
                cells = [(x, y) for y in range(y0, min(h, y0 + ch)) for x in range(x0, min(w, x0 + cw))]
                ins = [c for c in cells if p.group(g[c[1]][c[0]]) == p.group(F)]
                outs = [c for c in cells if c not in ins]
                if not ins or not outs:
                    continue
                before = components(p, g)
                # fill: the rest of the cell is plain lawn, nobody stands there, and no walkable place is cut off
                if all(p.lawnish(g[y][x], x, y) and (x, y) not in events for x, y in outs):
                    after = components(p, g, extra_shut=outs)
                    groups = {}
                    for c, k in after.items():
                        groups.setdefault(before[c], set()).add(k)
                    if all(len(v) == 1 for v in groups.values()):
                        for x, y in outs:
                            g[y][x] = F
                        fixed += 1
                        continue
                # trim: plain forest letters, not on the map's edge, beside one lawn letter, opening no new way through
                keep = {g[y][x] for x, y in outs if p.lawnish(g[y][x], x, y)}
                if (keep and all(g[y][x] == F for x, y in ins)
                        and all(0 < x < w - 1 and 0 < y < h - 1 for x, y in ins)):
                    lawn = sorted(keep)[0]
                    trial = [row[:] for row in g]
                    for x, y in ins:
                        trial[y][x] = lawn
                    after = components(p, trial)
                    merged = {}
                    for c, k in after.items():
                        if c in before:
                            merged.setdefault(k, set()).add(before[c])
                    if all(len(v) == 1 for v in merged.values()):
                        for x, y in ins:
                            g[y][x] = lawn
                        fixed += 1
                        continue
                left += 1
        if fixed or left:
            report.append(f"  forest {gname}: {fixed} cut cells made whole, {left} left (a way or an event there)")
    return report


def water_by_docks(p: Plan) -> list[str]:
    report = []
    made = {}
    for gname, g in p.grids.items():
        h, w = len(g), len(g[0])
        docks = {c for c in p.legend if p.item(c).get("auto") == "dock"}  # the dock letters (not their group: a
        if not docks:                                                        # map may join its dock to a road)
            continue
        n = 0
        for y in range(h):
            for x in range(w):
                it = p.item(g[y][x])
                if it.get("auto") not in ("pond", "sea"):
                    continue
                W_ = p.group(g[y][x])
                near = any(0 <= x + dx < w and 0 <= y + dy < h and g[y + dy][x + dx] in docks
                           for _, (dx, dy) in SIDES)
                if not near:
                    continue
                [name] = ground_name(p, g, [(x, y)], it["auto"], lambda xx, yy: (
                    not (0 <= xx < w and 0 <= yy < h) or p.group(g[yy][xx]) == W_ or g[yy][xx] in docks))
                if not name:
                    continue
                key = (name, W_, it.get("elevation"))
                if key not in made:
                    made[key] = p.free.pop(0)
                    p.legend[made[key]] = {"name": name, "joins": W_, **({"elevation": it["elevation"]}
                                                                         if "elevation" in it else {})}
                g[y][x] = made[key]
                n += 1
        if n:
            report.append(f"  water {gname}: {n} blocks beside a dock run up to it")
    return report


def settle(here: Path, grid_names: list[str]) -> list[str]:
    p = Plan(here, grid_names)
    report = settle_pieces(p) + snap_forest(p) + water_by_docks(p)
    if report:
        p.write()
    return report


if __name__ == "__main__":
    here = Path(sys.argv[1]).resolve()
    names = sys.argv[2:] or ["grid.txt"]
    print(f"settle {here.name}:")
    print("\n".join(settle(here, names)) or "  nothing to settle")

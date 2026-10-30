"""Settle the kit's small pieces into the ground they stand on (run after a map's make_art.py, before pae builds it).

A kit piece (a sign, a lamp, a boat, a barrel, a rock...) has its ground baked into its block: the sign and the lamp
stand on grass, the boat on the pond. Put one inside another surface (a lamp in the paving, a sign on a dirt path, a
boat in the sea) and two things go wrong: the piece shows a square of its own ground there, and the surface, whose
letter doesn't count the piece's as its own, draws its edge round it (a lawn rim in the paving, foam round the boat).

So for each such piece that stands inside one surface (three of its four sides, or two opposite ones, are that
surface's letter, counting the map's edge as the same, as pae map paint does), this makes the piece again in the
map's own (secondary) tileset over the block the surface would draw there (its edge variant from the same
neighbours, so a piece at the surface's edge keeps the edge) and puts it in the surface's group ({"joins": ...}), so
the surface goes on round it unbroken. Pieces already over the right ground only join (no new tiles).

Usage: python3 project/art/kit/settle.py project/art/<map>-concept [GRID ...]   (GRID defaults to grid.txt)
It rewrites the grids, legend.json and spec.json in place, adds sheets/settled_*.png, and prints what it changed."""
import json
import sys
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
# new legend letters (unused by any plan)
LETTERS = [chr(c) for c in range(0x2C00, 0x2C5F)]
SIDES = ((1, (0, -1)), (2, (1, 0)), (4, (0, 1)), (8, (-1, 0)))
CORNERS = ((1, (1, -1), 1 | 2), (2, (1, 1), 2 | 4), (4, (-1, 1), 4 | 8), (8, (-1, -1), 8 | 1))


def settle(here: Path, grid_names: list[str]) -> list[str]:
    spec = json.loads((here / "spec.json").read_text())
    legend = json.loads((here / "legend.json").read_text())
    meta = {e["name"]: e for e in spec["metatiles"]}
    grids = {n: [list(r) for r in (here / n).read_text().splitlines() if r.strip() and not r.startswith("#")]
             for n in grid_names}
    used = {c for g in grids.values() for row in g for c in row} | set(legend)
    free = [c for c in LETTERS if c not in used]

    def item(c):
        it = legend.get(c)
        return {"name": it} if isinstance(it, str) else dict(it or {})

    def group(c):
        it = legend.get(c)
        return it.get("joins", c) if isinstance(it, dict) else c

    made = {}      # (piece, grounds tuple, joins) -> (new name, letter)
    report = []
    for gname, g in grids.items():
        h, w = len(g), len(g[0])
        # pass 1: each small piece standing inside one surface, and that surface's group
        found, done = [], set()
        for y in range(h):
            for x in range(w):
                if (x, y) in done:
                    continue
                it = item(g[y][x])
                name = it.get("name")
                if "pick" in it and it.get("order") != "checker":  # the variant pae map paint picks here
                    names = it["pick"]
                    name = names[(x * 7919 + y * 104729 + (x * y) % 13) % len(names)]
                if "auto" in it or "tile" in it or name not in PIECES or name not in meta:
                    continue
                m = meta[name]
                mw, mh = m.get("w", 1), m.get("h", 1)
                cells = [(x + i, y + j) for j in range(mh) for i in range(mw)]
                done |= set(cells)
                count = {}  # the auto letters on its outside sides (other pieces of its kind count for nothing)
                for cx, cy in cells:
                    for bit, (dx, dy) in SIDES:
                        xx, yy = cx + dx, cy + dy
                        if (xx, yy) in cells or not (0 <= xx < w and 0 <= yy < h):
                            continue
                        n = g[yy][xx]
                        if item(n).get("auto") in GROUNDS:
                            count.setdefault(group(n), set()).add((bit, cx, cy))
                if not count:
                    continue
                A = max(count, key=lambda k: len(count[k]))
                bits = {b for b, _, _ in count[A]}
                outside = sum(1 for cx, cy in cells for b, (dx, dy) in SIDES
                              if (cx + dx, cy + dy) not in cells and 0 <= cx + dx < w and 0 <= cy + dy < h)
                if not (len(count[A]) * 4 >= max(1, outside) * 3 or {1, 4} <= bits or {2, 8} <= bits):
                    continue
                found.append((x, y, name, cells, A))
        # pass 2: their grounds, with every settled piece counted as its surface
        settled = {c: A for (_, _, _, cells, A) in found for c in cells}
        for x, y, name, cells, A in found:
            m = meta[name]
            a_char = next(ch for ch in legend if group(ch) == A and item(ch).get("auto") in GROUNDS)
            auto = item(a_char)["auto"]

            def same(xx, yy):
                return (not (0 <= xx < w and 0 <= yy < h) or settled.get((xx, yy)) == A
                        or group(g[yy][xx]) == A)
            grounds = []
            for cx, cy in cells:
                mask = sum(b for b, (dx, dy) in SIDES if same(cx + dx, cy + dy))
                corners = sum(b for b, (dx, dy), s in CORNERS if mask & s == s and not same(cx + dx, cy + dy))
                gn = next((n for n in (f"{auto}#{mask}.{corners}" if corners else None, f"{auto}#{mask}",
                                       f"{auto}#15", auto) if n and n in meta), None)
                grounds.append(gn)
            if None in grounds:
                report.append(f"  skip {name} at ({x},{y}): no ground piece for {auto}")
                continue
            key = (name, tuple(grounds), A)
            if key not in made:
                same_ground = all(gn == m.get("ground") for gn in grounds) or (
                    isinstance(m.get("ground"), list) and list(grounds) == m["ground"])
                new = name if same_ground else f"{name}@{'+'.join(grounds)}"
                made[key] = (new, free.pop(0))
            new, letter = made[key]
            for cx, cy in cells:
                g[cy][cx] = letter
            legend[letter] = {"name": new, "joins": A}
            report.append(f"  {gname} ({x},{y}) {name} on {m.get('ground')} in '{a_char}' ({auto}) -> "
                          f"{new if new != name else 'joins only'}")
    if not made:
        return report
    # the new pieces: the kit piece's pixels over the new ground, in the map's own tileset
    sheets = {}
    entries = []
    for (name, grounds, A), (new, letter) in made.items():
        if new == name:
            continue
        m = meta[name]
        bank = m["banks"][0]
        pal_name = next(k for k, v in kit.BANK.items() if v == bank)
        pal = kit.PALS[pal_name]
        src = Image.open(here / m["image"]).convert("RGBA")
        px = np.array(src.crop((m["x"], m["y"], m["x"] + 16 * m.get("w", 1), m["y"] + 16 * m.get("h", 1))))
        lut = {tuple(c): i for i, c in enumerate(pal) if i}
        idx = np.zeros(px.shape[:2], np.uint8)
        for (yy, xx), _ in np.ndenumerate(idx):
            r, gg, b, al = (int(v) for v in px[yy, xx])
            if al:
                idx[yy, xx] = lut[(r, gg, b)]
        sh = sheets.setdefault(bank, kit.Sheet(f"settled_{pal_name}", pal, bank, here, here, cols=8))
        extra = {k: v for k, v in m.items() if k in ("solid", "elevation", "over_rows", "behaviors", "open",
                                                     "row_banks")}
        sh.add(new, idx, tileset="secondary", ground=list(grounds) if len(grounds) > 1 else grounds[0], **extra)
    for sh in sheets.values():
        entries += sh.write()
    for e in entries:
        if e.get("w") == 1 and e.get("h") == 1:
            del e["w"], e["h"]
    spec["metatiles"] = [e for e in spec["metatiles"] if not str(e["name"]).startswith(tuple(f"{p}@" for p in PIECES))]
    spec["metatiles"] += entries
    (here / "spec.json").write_text(json.dumps(spec, indent=1) + "\n")
    (here / "legend.json").write_text(json.dumps(legend, indent=1, ensure_ascii=False) + "\n")
    for gname, g in grids.items():
        (here / gname).write_text("".join("".join(r) + "\n" for r in g))
    report.append(f"  {len(entries)} new pieces; {sum(1 for k, v in made.items() if v[0] == k[0])} kinds only join")
    return report


if __name__ == "__main__":
    here = Path(sys.argv[1]).resolve()
    names = sys.argv[2:] or ["grid.txt"]
    print(f"settle {here.name}:")
    print("\n".join(settle(here, names)) or "  nothing to settle")

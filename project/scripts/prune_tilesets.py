#!/usr/bin/env python3
"""Leave the tiles, palettes and metatiles of tilesets no FireRed layout uses out of the FireRed build.

A tileset counts as used when a layout or map header of a FireRed build names it (data/layouts/layouts.inc and
data/maps/*/header.inc of a build tree). For every other tileset, under `#ifdef FIRERED`:

* its `struct Tileset` stays, empty, because native code compares tileset addresses (door animations, field effects);
* its tile, palette, metatile and metatile attribute arrays are not built, unless a kept tileset shares them.

Usage: prune_tilesets.py BUILD_TREE [--keep gTileset_X ...]
"""
import argparse
import re
from pathlib import Path

ENGINE = Path(__file__).resolve().parents[2] / "engine"
STRUCT = re.compile(r"^const struct Tileset (gTileset_\w+) =\n\{\n(.*?)\n\};\n", re.M | re.S)
FIELD = re.compile(r"\.(tiles|palettes|metatiles|metatileAttributes)\s*=\s*(\w+)")
MARK = "prune_tilesets.py"


def used_tilesets(build: Path) -> set[str]:
    used = set(re.findall(r"gTileset_\w+", (build / "data/layouts/layouts.inc").read_text()))
    for f in (build / "data/maps").glob("*/header.inc"):
        used |= set(re.findall(r"gTileset_\w+", f.read_text()))
    return used


def wrap_definitions(path: Path, names: set[str]) -> int:
    """Put `#ifndef FIRERED` around the definitions of these arrays (one statement each, up to its `;`)."""
    text = path.read_text()
    out, i, n = [], 0, 0
    pat = re.compile(r"^(?:const u(?:16|32) (\w+)\[[^\n]*?=[^;]*?;|extern const u(?:16|32) (\w+)\[[^\n]*__attribute__"
                     r"\(\(alias\(\"\w+\"\)\)\);)[^\n]*\n", re.M | re.S)
    for m in pat.finditer(text):
        if (m.group(1) or m.group(2)) not in names:
            continue
        out.append(text[i:m.start()])
        out.append(f"#ifndef FIRERED // {MARK}: no FireRed layout uses this tileset\n{m.group(0)}#endif\n")
        i = m.end()
        n += 1
    out.append(text[i:])
    path.write_text("".join(out))
    return n


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("build", type=Path)
    ap.add_argument("--keep", nargs="*", default=[])
    a = ap.parse_args()
    headers = ENGINE / "src/data/tilesets/headers.h"
    text = headers.read_text()
    if MARK in text:
        raise SystemExit("already pruned; check out the original headers.h first")
    used = used_tilesets(a.build) | set(a.keep)
    structs = {m.group(1): m for m in STRUCT.finditer(text)}
    drop = sorted(t for t in structs if t not in used)
    data_of = {t: dict(FIELD.findall(structs[t].group(2))) for t in structs}
    kept_data = {v for t in structs if t not in drop for v in data_of[t].values()}
    # arrays that are aliases of (or aliased by) kept data stay too
    graphics = (ENGINE / "src/data/tilesets/graphics.h").read_text()
    for alias, target in re.findall(r"(\w+)\[[^\]]*\] __attribute__\(\(alias\(\"(\w+)\"\)\)\)", graphics):
        if alias in kept_data:
            kept_data.add(target)
    drop_data = {v for t in drop for v in data_of[t].values()} - kept_data
    # arrays native code uses directly (the sand pillar borrows the Secret Base palette)
    code = "\n".join(f.read_text(errors="replace") for f in (ENGINE / "src").rglob("*.c"))
    drop_data = {d for d in drop_data if not re.search(rf"\b{d}\b", code)}

    out, i = [], 0
    for t in sorted(drop, key=lambda t: structs[t].start()):
        m = structs[t]
        out.append(text[i:m.start()])
        out.append(f"#ifdef FIRERED // {MARK}: no FireRed layout uses this tileset; native code only compares its address\n"
                   f"const struct Tileset {t} = {{0}};\n#else\n{m.group(0)}#endif\n")
        i = m.end()
    out.append(text[i:])
    headers.write_text("".join(out))
    n = sum(wrap_definitions(ENGINE / f"src/data/tilesets/{f}", drop_data) for f in ("graphics.h", "metatiles.h"))
    print(f"{len(drop)} tilesets emptied for FireRed; {n} of their {len(drop_data)} data arrays left out")


if __name__ == "__main__":
    main()

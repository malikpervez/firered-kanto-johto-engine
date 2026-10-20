#!/usr/bin/env python3
"""Write each map's FireRed version at the top of its map.json (one-time migration).

Maps of the FireRed game kept their FireRed events in a `firered_campaign` section next to the original HnS or
Emerald ones, and mapjson merged it at build time. This merges it once, the same way (its fields replace the top-level
ones), removes the section and marks the map as a FireRed map (`game_version: frlg`), so the top-level events are the
ones the game has. Layout overlays (`firered_campaign` in layouts.json) are merged the same way.

The ROM must stay byte-identical; check before committing.
Usage (repository root): project/scripts/flatten_firered_overlays.py [--layouts]
"""
import argparse
import json
from pathlib import Path

ENGINE = Path(__file__).resolve().parents[2] / "engine"
LAYOUT_GEOMETRY = ("width", "height", "primary_tileset", "secondary_tileset", "border_filepath", "blockdata_filepath",
                   "border_width", "border_height", "layout_version", "blockdata_overrides", "blockdata_composition")


def maps() -> int:
    n = 0
    for f in sorted(ENGINE.glob("data/maps/*/map.json")):
        d = json.loads(f.read_text())
        overlay = d.get("firered_campaign")
        if not isinstance(overlay, dict):
            continue
        out = {k: v for k, v in d.items() if k != "firered_campaign"}
        out.update(overlay)
        out["game_version"] = "frlg"
        f.write_text(json.dumps(out, indent=2, ensure_ascii=False) + "\n")
        n += 1
    return n


def layouts() -> int:
    p = ENGINE / "data/layouts/layouts.json"
    data = json.loads(p.read_text())
    n = 0
    for i, lay in enumerate(data["layouts"]):
        if not lay or "firered_campaign" not in lay:
            continue
        overlay = lay["firered_campaign"]
        out = {k: v for k, v in lay.items() if k != "firered_campaign"}
        if isinstance(overlay, dict):
            assert set(overlay) <= set(LAYOUT_GEOMETRY), lay["id"]
            out.update(overlay)
        if overlay:
            out["game_version"] = "frlg"
        data["layouts"][i] = out
        n += 1
    p.write_text(json.dumps(data, indent=4, ensure_ascii=False) + "\n")
    return n


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--layouts", action="store_true")
    a = ap.parse_args()
    print(f"{maps()} maps flattened" + (f", {layouts()} layouts" if a.layouts else ""))


if __name__ == "__main__":
    main()

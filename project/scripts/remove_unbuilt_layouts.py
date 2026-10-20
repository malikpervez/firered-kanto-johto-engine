#!/usr/bin/env python3
"""Delete the layouts of maps the FireRed game does not have (one-time cleanup, after remove_unbuilt_maps.py).

A layout that is not a FireRed layout (`game_version` other than frlg) was already left out of the build: an empty
slot in the layout table. Its entry in layouts.json becomes {"id", "name", "removed": true}, which keeps the slot (so
other layouts keep their numbers) and its LAYOUT_ constant; entries mapjson skipped anyway (no border file) go. Then
every folder in data/layouts/ that nothing still refers to is deleted.

Usage (repository root): project/scripts/remove_unbuilt_layouts.py [--dry-run]
"""
import argparse
import json
import re
import shutil
from pathlib import Path

ENGINE = Path(__file__).resolve().parents[2] / "engine"
LAYOUTS = ENGINE / "data/layouts"
TEXT = (".s", ".inc", ".c", ".h", ".json", ".mk", ".ld", ".txt", ".py")


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args()
    p = LAYOUTS / "layouts.json"
    data = json.loads(p.read_text())
    out, marked, dropped = [], 0, 0
    for lay in data["layouts"]:
        if lay and not lay.get("removed") and lay.get("game_version") != "frlg":
            if (ENGINE / lay["border_filepath"]).exists():
                out.append({"id": lay["id"], "name": lay["name"], "removed": True})
                marked += 1
            else:
                dropped += 1  # mapjson skipped it already: no slot, no constant
            continue
        out.append(lay)
    data["layouts"] = out
    text = json.dumps(data, indent=4, ensure_ascii=False) + "\n"

    # folders still referred to: by the kept layouts, maps, geometry aliases or anything else in the source
    refs = set(re.findall(r"data/layouts/([^/\"]+)/", text))
    for f in ENGINE.rglob("*"):
        if f.is_file() and f.suffix in TEXT and f != p and "build" not in f.relative_to(ENGINE).parts[:1] \
                and not f.is_relative_to(ENGINE / "tools"):
            refs |= set(re.findall(r"data/layouts/([^/\"\s]+)/", f.read_text(errors="replace")))
    gone = sorted(d.name for d in LAYOUTS.iterdir() if d.is_dir() and d.name not in refs)
    if not a.dry_run:
        p.write_text(text)
        for name in gone:
            shutil.rmtree(LAYOUTS / name)
    print(f"{marked} layouts marked removed, {dropped} skipped entries dropped; {len(gone)} layout folders deleted, "
          f"{sum(1 for d in LAYOUTS.iterdir() if d.is_dir()) - (0 if a.dry_run else 0)} left")


if __name__ == "__main__":
    main()

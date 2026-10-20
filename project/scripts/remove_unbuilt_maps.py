#!/usr/bin/env python3
"""Delete the maps the FireRed game does not have (one-time cleanup).

Every map whose map.json is not a FireRed map (`game_version` other than frlg) was already left out of the build:
mapjson gave it an empty slot. This deletes its folder. Its name stays in map_groups.json, so all other maps keep
their numbers, and data/maps/removed_maps.json keeps its MAP_ constant and the LOCALID_/warp id constants of its
events (C code and data still name some of them).

Refuses if any remaining source still refers to a removed map's folder.
Usage (repository root): project/scripts/remove_unbuilt_maps.py [--dry-run]
"""
import argparse
import json
import re
import shutil
from pathlib import Path

ENGINE = Path(__file__).resolve().parents[2] / "engine"
SCAN = ("data", "src", "include", "asm", "sound", "graphics_file_rules.mk", "map_data_rules.mk", "Makefile",
        "audio_rules.mk", "spritesheet_rules.mk", "ld_script_modern.ld")


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args()
    maps_dir = ENGINE / "data/maps"
    removed = {}
    for f in sorted(maps_dir.glob("*/map.json")):
        d = json.loads(f.read_text())
        if d.get("game_version") != "frlg":
            # the constants mapjson made from its events (C code still names some), numbered as mapjson does
            ids = {o["local_id"]: i + 1 for i, o in enumerate(d.get("object_events") or []) if "local_id" in o}
            ids.update({w["warp_id"]: i for i, w in enumerate(d.get("warp_events") or []) if "warp_id" in w})
            removed[f.parent.name] = {"id": d["id"], **({"event_ids": ids} if ids else {})}
    groups = json.loads((maps_dir / "map_groups.json").read_text())
    listed = {m for g in groups["group_order"] for m in groups[g]}
    assert set(removed) <= listed, sorted(set(removed) - listed)[:10]

    # nothing that stays may point into a removed folder
    pat = re.compile(r"data/maps/(" + "|".join(map(re.escape, removed)) + r")/")
    hits = []
    for name in SCAN:
        p = ENGINE / name
        files = [p] if p.is_file() else [x for x in p.rglob("*") if x.is_file() and x.suffix in
                                         (".s", ".inc", ".c", ".h", ".json", ".mk", ".ld", ".txt")]
        for f in files:
            if f.is_relative_to(maps_dir) and f.parent.name in removed:
                continue
            text = re.sub(r"(@|//).*", "", f.read_text(errors="replace"))  # comments only say where code came from
            for m in pat.finditer(text):
                hits.append(f"{f.relative_to(ENGINE)}: {m.group(0)}")
    if hits:
        raise SystemExit("still referenced:\n" + "\n".join(hits[:40]))
    if not a.dry_run:
        old = maps_dir / "removed_maps.json"
        known = json.loads(old.read_text()) if old.exists() else {}
        known.update(removed)
        old.write_text(json.dumps(dict(sorted(known.items())), indent=2) + "\n")
        for name in removed:
            shutil.rmtree(maps_dir / name)
    print(f"{len(removed)} maps not in the game removed; {len(listed) - len(removed)} kept")


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""Take the HnS Battle Frontier (and Trainer Hill) out of the FireRed Kanto + Johto game.

* Its maps leave the FireRed campaign (their `firered_campaign` is removed), so mapjson leaves their headers, events
  and layouts out of the FireRed build, as it already does for the old HnS Kanto.
* Route 40's gatehouse warps into it are removed (they are Route 40's last warps, so no other warp id moves).
* Its script and text blocks leave data/johto_campaign.s, except blocks that kept scripts still reach.
* The S.S. Aqua no longer offers the Battle Frontier (src/data/script_menu.h for FireRed, and the matching cases).

Usage: prune_frontier.py [--dry-run]
"""
import argparse
import json
import re
from pathlib import Path

ENGINE = Path(__file__).resolve().parents[2] / "engine"
FRONTIER = re.compile(r"^(BattleFrontier|BattlePyramid|BattleTower|BattleDome|BattlePalace|BattleArena|BattleFactory|"
                      r"BattlePike|BattleTent|TrainerHill|ArtisanCave|Gate_Route40_TrainerHill)")
MARKER = re.compile(r"^(?:\.ifdef \w+ ; \.size \w+, \. - \w+ ; \.endif ; )?\.global (\w+)$")
IDENT = re.compile(r"\b[A-Za-z_]\w*\b")


def dump(path: Path, data: dict, indent: int = 2) -> None:
    path.write_text(json.dumps(data, indent=indent, ensure_ascii=False) + "\n")


def maps(dry: bool) -> list[str]:
    names = []
    for f in sorted((ENGINE / "data/maps").glob("*_hns/map.json")):
        d = json.loads(f.read_text())
        if FRONTIER.match(d["name"]) and isinstance(d.get("firered_campaign"), dict):
            names.append(d["name"])
            if not dry:
                del d["firered_campaign"]
                dump(f, d)
    # Route 40's gatehouse warps
    f = ENGINE / "data/maps/Route40_hns/map.json"
    d = json.loads(f.read_text())
    w = d["firered_campaign"]["warp_events"]
    keep = [x for x in w if not x["dest_map"].startswith("MAP_GATE_ROUTE40_TRAINER_HILL")]
    assert w[:len(keep)] == keep, "the gatehouse warps are no longer Route 40's last warps"
    if not dry:
        d["firered_campaign"]["warp_events"] = keep
        dump(f, d)
    return names


def layouts(map_names: list[str], dry: bool) -> int:
    used = {}
    for f in (ENGINE / "data/maps").glob("*/map.json"):
        d = json.loads(f.read_text())
        used.setdefault(d["layout"], set()).add(d["name"])
    p = ENGINE / "data/layouts/layouts.json"
    data = json.loads(p.read_text())
    n = 0
    for lay in data["layouts"]:
        users = used.get(lay.get("id"), set())
        if users and users <= set(map_names) and lay.get("firered_campaign") is True:
            n += 1
            if not dry:
                del lay["firered_campaign"]
    if not dry:
        dump(p, data, indent=4)
    return n


def emitted_layouts() -> set[str]:
    """Layout names mapjson writes for FireRed (frlg layouts and FireRed campaign layouts)."""
    data = json.loads((ENGINE / "data/layouts/layouts.json").read_text())
    return {l["name"] for l in data["layouts"] if l and (l.get("game_version") == "frlg" or l.get("firered_campaign"))}


def aliases(dry: bool) -> int:
    """Geometry aliases whose owner layout is no longer built: the first kept user becomes the owner."""
    p = ENGINE / "data/layouts/firered_geometry_payload_aliases.json"
    plan = json.loads(p.read_text())
    built = emitted_layouts()
    label_layout = lambda lab: re.sub(r"_(Border|Blockdata)$", "", lab)
    by_owner = {}
    for lab, a in plan["aliases"].items():
        by_owner.setdefault(a["owner"], []).append(lab)
    moved = 0
    for owner, labs in by_owner.items():
        if label_layout(owner) in built:
            continue
        kept = [lab for lab in labs if label_layout(lab) in built]
        for lab in labs:
            if lab not in kept:
                del plan["aliases"][lab]
        if not kept:
            continue
        new_owner = kept[0]
        new_path = plan["aliases"][new_owner]["source_filepath"]
        del plan["aliases"][new_owner]
        for lab in kept[1:]:
            plan["aliases"][lab]["owner"] = new_owner
            plan["aliases"][lab]["owner_filepath"] = new_path
        moved += 1
    if not dry:
        dump(p, plan)
    return moved


def campaign(dry: bool) -> tuple[int, int]:
    p = ENGINE / "data/johto_campaign.s"
    lines = p.read_text().split("\n")
    blocks, start, cur = [], 0, None   # (label, first line, end line)
    for i, ln in enumerate(lines):
        m = MARKER.match(ln)
        if m:
            blocks.append((cur, start, i))
            cur, start = m.group(1), i
    blocks.append((cur, start, len(lines)))
    removed_entry = {"OlivinePort_EventScript_ChoseBattleFrontier"}
    drop = {b[0] for b in blocks if b[0] and (FRONTIER.match(b[0]) or b[0] in removed_entry)}
    text_of = {b[0]: "\n".join(lines[b[1]:b[2]]) for b in blocks}
    # keep frontier blocks that kept blocks still reach
    todo = [b[0] for b in blocks if b[0] not in drop]
    seen = set(todo)
    while todo:
        lab = todo.pop()
        body = "\n".join(text_of.get(lab, "").split("\n")[1:]) if lab else "\n".join(lines[blocks[0][1]:blocks[0][2]])
        for tok in set(IDENT.findall(body)):
            if tok in drop and tok not in seen:
                if lab == "OlivinePort_EventScript_Sailor_AfterKanto" and tok in removed_entry:
                    continue
                seen.add(tok)
                todo.append(tok)
    drop -= seen
    out = []
    for lab, a, b in blocks:
        if lab in drop:
            continue
        chunk = lines[a:b]
        if lab == "OlivinePort_EventScript_Sailor_AfterKanto":
            chunk = [ln for ln in chunk if "OlivinePort_EventScript_ChoseBattleFrontier" not in ln]
            chunk = [ln.replace("case 5, OlivinePort_EventScript_Sailor_Refused",
                                "case 4, OlivinePort_EventScript_Sailor_Refused") for ln in chunk]
        out.extend(chunk)
    if not dry:
        p.write_text("\n".join(out))
        # removed labels that native code still names (the Battle Pyramid's input hooks, field specials...)
        code = "\n".join(f.read_text(errors="replace") for f in (ENGINE / "src").rglob("*.c"))
        named = sorted(lab for lab in drop if re.search(rf"\b{lab}\b", code))
        stub = ["@ Generated by project/scripts/prune_frontier.py: Battle Frontier labels native code still names.",
                "@ They do nothing; the FireRed game has no Battle Frontier.", ""]
        for lab in named:
            body = '\t.string "$"' if "_Text_" in lab else "\tstep_end" if "_Movement_" in lab else "\tend"
            stub += [f"{lab}::", body, ""]
        (ENGINE / "data/scripts/frontier_stubs.inc").write_text("\n".join(stub) + "\n")
    return len(drop), len(blocks)


def menu(dry: bool) -> None:
    p = ENGINE / "src/data/script_menu.h"
    t = p.read_text()
    old = "    {gText_FarawayIsland},\n    {gText_BattleFrontier},\n    {gText_Exit},\n};\nstatic const struct MenuAction MultichoiceList_VermilionHarbor[]"
    assert t.count(old) == 1
    new = ("    {gText_FarawayIsland},\n#ifndef FIRERED // the FireRed game has no Battle Frontier\n    {gText_BattleFrontier},\n"
           "#endif\n    {gText_Exit},\n};\nstatic const struct MenuAction MultichoiceList_VermilionHarbor[]")
    if not dry:
        p.write_text(t.replace(old, new))


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args()
    names = maps(a.dry_run)
    n_lay = layouts(names, a.dry_run)
    n_alias = aliases(a.dry_run)
    dropped, total = campaign(a.dry_run)
    menu(a.dry_run)
    print(f"{len(names)} Frontier maps left the FireRed campaign, {n_lay} layouts ({n_alias} shared payloads re-owned); "
          f"{dropped} of {total} campaign script blocks removed")


if __name__ == "__main__":
    main()

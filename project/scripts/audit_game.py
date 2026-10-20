#!/usr/bin/env python3
"""Whole-game audit with pae: map checks, dead triggers and map scripts, flags tested but never set, unreachable
maps, trainers nobody battles, wild tables of removed maps. Static: confirm findings in the game before fixing.
Usage (pae installed): project/scripts/audit_game.py engine audit.json"""
import collections, json, re, sys
from pathlib import Path
from pkmn_asset_editor.decomp import DecompProject

root = Path(sys.argv[1]); out = {}
dp = DecompProject(root); m = dp.maps

# 1. every map: pae's own checks
issues = collections.defaultdict(list)
for name in m.maps:
    data = json.loads((root / "data/maps" / name / "map.json").read_text())
    for lvl, msg in m.validate_map_data(name, data):
        issues[name].append((lvl, msg))
out["map_issues"] = issues

# 2. scripts: every built script file (Kanto/shared via event_scripts.s, Johto via johto_campaign.s)
def includes(f):
    return re.findall(r'^\s*\.include "(data/[^"]+\.inc)"', (root / f).read_text(), re.M)
files = sorted(set(includes("data/event_scripts.s") + includes("data/johto_campaign.s")))
text = {f: (root / f).read_text(errors="replace") for f in files + ["data/event_scripts.s"] if (root / f).exists()}
alltext = "\n".join(re.sub(r"@.*", "", t) for t in text.values())
code = "\n".join(p.read_text(errors="replace") for p in (root / "src").rglob("*.c"))

sets = collections.defaultdict(set)   # var -> values set
for v, val in re.findall(r"^\s*setvar\s+(\w+),\s*(\w+)", alltext, re.M):
    sets[v].add(val)
changed_by_add = set(re.findall(r"^\s*(?:addvar|subvar|copyvar|specialvar|getplayerxy)\s+(\w+)", alltext, re.M))
set_flags = set(re.findall(r"^\s*(?:setflag|clearflag)\s+(\w+)", alltext, re.M))
set_flags |= set(re.findall(r"^\s*setvar\s+\w+,\s*((?:JOHTO_)?FLAG_\w+)", alltext, re.M))  # passed to a special
checked_flags = collections.Counter(re.findall(r"^\s*(?:goto|call)_if_(?:set|unset)\s+(\w+)", alltext, re.M))
trainer_flags = set(re.findall(r"^\s*(?:settrainerflag|cleartrainerflag)\s+(\w+)", alltext, re.M))

def var_dynamic(v):
    return v in changed_by_add or re.search(rf"\b{v}\b", code) or v.replace("JOHTO_", "").startswith(("VAR_TEMP", "VAR_0x8", "VAR_RESULT", "VAR_FACING"))

dead_triggers = []
for name in m.maps:
    d = json.loads((root / "data/maps" / name / "map.json").read_text())
    for c in d.get("coord_events") or []:
        v, val = c.get("var"), str(c.get("var_value"))
        if c.get("type") == "trigger" and v and not var_dynamic(v) and val not in sets.get(v, set()) and not (val == "0"):
            dead_triggers.append(f"{name}: trigger ({c['x']},{c['y']}) waits for {v} == {val}; no script sets that ({sorted(sets.get(v, []))[:6]})")
    for o in d.get("object_events") or []:
        fl = o.get("flag")
        if fl and fl not in ("0", "FLAG_NONE") and fl not in set_flags and not re.search(rf"\b{fl}\b", code) \
                and not fl.startswith(("FLAG_TEMP", "FLAG_HIDE_TRAINER")):
            pass  # an object hidden by a flag nobody changes: it never appears/disappears (often intended); counted below
out["dead_triggers"] = dead_triggers

# map_script_2 (on-frame / warp-into) tables waiting for values nobody sets
dead_frame = []
for f, t in text.items():
    for v, val, lab in re.findall(r"^\s*map_script_2\s+(\w+),\s*(\w+),\s*(\w+)", t, re.M):
        if not var_dynamic(v) and val != "0" and val not in sets.get(v, set()):
            dead_frame.append(f"{f}: {lab} runs when {v} == {val}; no script sets that")
out["dead_map_scripts"] = dead_frame

never_set = sorted((f, n) for f, n in checked_flags.items()
                   if f not in set_flags and f not in trainer_flags and not re.search(rf"\b{f}\b", code)
                   and not f.startswith(("FLAG_TEMP", "FLAG_SYS_", "FLAG_BADGE", "JOHTO_FLAG_BADGE", "FLAG_HIDE_")))
out["flags_checked_never_set"] = never_set

# 3. reachability: warps + connections + script warps from Pallet Town
graph = collections.defaultdict(set)
id_to_name = {v["id"]: k for k, v in m.maps.items()}
for name in m.maps:
    d = json.loads((root / "data/maps" / name / "map.json").read_text())
    for w in d.get("warp_events") or []:
        if w.get("dest_map") in id_to_name: graph[name].add(id_to_name[w["dest_map"]])
    for c in d.get("connections") or []:
        if c.get("map") in id_to_name: graph[name].add(id_to_name[c["map"]])
for f, t in text.items():
    src = Path(f).parent.name if f.startswith("data/maps/") else None
    for dest in re.findall(r"^\s*warp\w*\s+(MAP_\w+)", t, re.M):
        if dest in id_to_name:
            graph[src or "*scripts*"].add(id_to_name[dest])
for dest in re.findall(r"\b(MAP_[A-Z0-9_]+)\b", code):
    if dest in id_to_name: graph["*code*"].add(id_to_name[dest])
seen, todo = set(), ["PalletTown_Frlg", "*scripts*", "*code*"]
while todo:
    n = todo.pop()
    if n in seen: continue
    seen.add(n); todo += list(graph.get(n, ()))
unreach = sorted(n for n in m.maps if n not in seen)
out["unreachable_maps"] = unreach

# 4. trainers never battled
battled = set(re.findall(r"^\s*trainerbattle\w*\s+(?:TRAINER_BATTLE_\w+,\s*)?(TRAINER_\w+)", alltext, re.M))
battled |= set(re.findall(r"\b(TRAINER_\w+)\b", code))
defined = {}
for party in ("src/data/trainers_frlg.party", "src/data/trainers_hns.party"):
    for t in re.findall(r"^===\s+(TRAINER_\w+)\s+===", (root / party).read_text(), re.M):
        defined[t] = party
alias = lambda t: "TRAINER_JOHTO_" + t[8:] if "hns" in defined[t] else t
out["trainers_never_battled"] = sorted(t for t in defined if t not in battled and alias(t) not in battled and t != "TRAINER_NONE")

# 5. wild tables of maps the game doesn't have
removed = json.loads((root / "data/maps/removed_maps.json").read_text())
removed_ids = {v["id"] for v in removed.values()}
w = json.loads((root / "src/data/wild_encounters.json").read_text())
out["wild_tables_of_removed_maps"] = sorted({e.get("map") for g in w["wild_encounter_groups"] for e in g["encounters"] if e.get("map") in removed_ids})

Path(sys.argv[2]).write_text(json.dumps(out, indent=1, default=list))
s = {k: (sum(len(v) for v in out[k].values()) if isinstance(out[k], dict) else len(out[k])) for k in out}
print(s)

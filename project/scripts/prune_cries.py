#!/usr/bin/env python3
"""Leave the cries of Pokémon families the FireRed Kanto + Johto game never shows out of the FireRed build.

A family counts as shown when any member appears in:

* a wild table of a map the FireRed build has (frlg maps and FireRed campaign maps);
* a FireRed trainer party (trainers_frlg.h, trainers_firered_johto.h);
* a script: frlg map scripts and shared scripts by name, data/johto_campaign.s by species number;
* native code or other data by name (in-game trades, roamers, starters, Surf mounts, Easy Chat...);
* project/firered_cries_keep.txt (one family per line, e.g. TEPIG), for Pokémon added to the story later.

Every cry table entry stays, so cry ids do not move. For FireRed, each cry of the other families becomes an alias of
Ditto's cry instead of its own sample (sound/direct_sound_data.inc, `#ifdef FIRERED`; data/sound_data.s goes through the C preprocessor). Other targets are unchanged.

Rerun after adding Pokémon to the game: it first undoes its own earlier changes.
Usage: prune_cries.py BUILD_TREE [--dry-run]
"""
import argparse
import collections
import json
import re
from pathlib import Path

PROJECT = Path(__file__).resolve().parents[1]
ENGINE = PROJECT.parent / "engine"
DATA = ENGINE / "sound/direct_sound_data.inc"
KEEP_FILE = PROJECT / "firered_cries_keep.txt"
SUBSTITUTE = "Cry_Ditto"
MARK = "prune_cries.py"
CRY = re.compile(r"\t\.align 2\n(Cry_\w+)::\n\.if TESTING == FALSE\n\t\.incbin \"[^\"]+\"\n\.endif\n")
WRAPPED = re.compile(rf"#ifdef FIRERED // {MARK}[^\n]*\n\t\.set \w+, \w+\n#else\n(.*?)#endif // {MARK}\n", re.S)
# data that names species without the game showing them
SKIP = ("src/data/pokemon/", "src/data/graphics/", "src/data/pokemon_graphics", "src/data/text/species_names",
        "src/data/pokedex", "src/data/trainers.h", "src/data/trainers_hns.h", "src/data/debug_trainers",
        "src/data/battle_partners", "src/data/battle_frontier", "src/data/wild_encounters.h",
        "include/constants/species.h", "include/config/species_enabled.h")


def species_numbers(build: Path) -> dict[str, int]:
    text = (build / "include/constants/species.h").read_text()
    num = {n: int(v) for n, v in re.findall(r"#define (SPECIES_\w+)\s+(\d+)\b", text)}
    changed = True
    while changed:
        changed = False
        for n, a in re.findall(r"#define (SPECIES_\w+)\s+(SPECIES_\w+)\s*$", text, re.M):
            if a in num and n not in num:
                num[n] = num[a]
                changed = True
    return num


def families_of(build: Path) -> dict[str, str]:
    fam = {}
    for f in (build / "src/data/pokemon/species_info").glob("gen_*_families.h"):
        cur = None
        for ln in f.read_text().split("\n"):
            m = re.match(r"#if P_FAMILY_(\w+)", ln)
            if m:
                cur = m.group(1)
            m = re.match(r"\s*\[(SPECIES_\w+)\]\s*=", ln)
            if m and cur:
                fam[m.group(1)] = cur
    return fam


def shown_species(build: Path) -> set[str]:
    num = species_numbers(build)
    by_number = {}
    for n, v in sorted(num.items(), key=lambda x: len(x[0])):
        by_number.setdefault(v, n)
    names = set()
    built = set()
    for f in (build / "data/maps").glob("*/map.json"):
        d = json.loads(f.read_text())
        if d.get("game_version") == "frlg" or isinstance(d.get("firered_campaign"), dict):
            built.add(d["id"])
            if d.get("game_version") == "frlg" and (f.parent / "scripts.inc").exists():
                names |= set(re.findall(r"SPECIES_\w+", (f.parent / "scripts.inc").read_text(errors="replace")))
    wild = json.loads((build / "src/data/wild_encounters.json").read_text())
    for g in wild["wild_encounter_groups"]:
        if g["label"] == "gWildMonHeaders":
            for e in g["encounters"]:
                if e.get("map") in built:
                    names |= set(re.findall(r"SPECIES_\w+", json.dumps(e)))
    for f in ("trainers_frlg.h", "trainers_firered_johto.h"):
        names |= set(re.findall(r"SPECIES_\w+", (build / "src/data" / f).read_text()))
    for f in list((build / "data/scripts").glob("*.inc")) + [build / "data/event_scripts.s"]:
        names |= set(re.findall(r"SPECIES_\w+", f.read_text(errors="replace")))
    camp = (build / "data/johto_campaign.s").read_text()
    for m in re.finditer(r"^\s*(?:givemon|setwildbattle\w*|giveegg|playmoncry|showmonpic|createmon)\s+(\d+)", camp, re.M):
        if int(m.group(1)) in by_number:
            names.add(by_number[int(m.group(1))])
    for d in ("src", "include"):
        for p in (build / d).rglob("*"):
            if p.suffix in (".c", ".h") and not any(s in str(p.relative_to(build)) for s in SKIP):
                names |= set(re.findall(r"SPECIES_\w+", p.read_text(errors="replace")))
    return {n for n in names if n in num and n != "SPECIES_NONE"}


def restore(text: str) -> str:
    return WRAPPED.sub(lambda m: m.group(1), text)


def prune(text: str, drop: set[str]) -> tuple[str, int]:
    out, n, pos = [], 0, 0
    for m in re.finditer(r"^\.if P_FAMILY_(\w+) == TRUE\n(.*?)^\.endif @ P_FAMILY_\1\n", text, re.M | re.S):
        if m.group(1) not in drop:
            continue
        body_start = m.start(2)
        body = m.group(2)

        def wrap(c):
            nonlocal n
            n += 1
            return (f"#ifdef FIRERED // {MARK}: the FireRed game never shows the {m.group(1).title()} family\n"
                    f"\t.set {c.group(1)}, {SUBSTITUTE}\n#else\n{c.group(0)}#endif // {MARK}\n")
        out.append(text[pos:body_start])
        out.append(CRY.sub(wrap, body))
        pos = m.end(2)
    out.append(text[pos:])
    return "".join(out), n


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("build", type=Path)
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args()
    fam = families_of(a.build)
    shown = {fam[s] for s in shown_species(a.build) if s in fam}
    extra = set()
    if KEEP_FILE.exists():
        extra = {ln.strip().upper() for ln in KEEP_FILE.read_text().split("\n") if ln.strip() and not ln.startswith("#")}
    unknown = extra - set(fam.values())
    if unknown:
        raise SystemExit(f"{KEEP_FILE.name}: not a family: {', '.join(sorted(unknown))}")
    keep = shown | extra | {"DITTO"}
    drop = set(fam.values()) - keep
    text = restore(DATA.read_text())
    new, n = prune(text, drop)
    sizes = collections.Counter()
    for c in CRY.finditer(text):
        b = a.build / re.search(r'"([^"]+)"', c.group(0)).group(1)
        sizes["dropped" if f"\t.set {c.group(1)}, " in new else "kept"] += b.stat().st_size if b.exists() else 0
    if not a.dry_run:
        DATA.write_text(new)
    print(f"{len(keep)} of {len(set(fam.values()))} families shown; {n} cries of {len(drop)} families now alias "
          f"{SUBSTITUTE} for FireRed ({sizes['dropped']:,} bytes of cry samples left out, {sizes['kept']:,} kept)")


if __name__ == "__main__":
    main()

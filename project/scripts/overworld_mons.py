#!/usr/bin/env python3
"""Kanto's overworld Pokémon (the walkers Heart & Soul's maps brought): Kanto's own, and battleable outside towns.

The owner, 6 November 2026: the Pokémon walking around Kanto "are restricted to what should be currently available in
Kanto", and those outside towns "should be slightly stronger compared to those found in that route. If the player
chooses to fight them they should have a higher level and better IVs".

The rules, for every walker on a Kanto map (a `_Frlg` map whose object's graphics are a species):
  * it is a Kanto Pokémon (National Pokédex 1-151);
  * outside towns (route and cave maps) it is one you can find there: a Kanto species in the map's own FireRed wild
    table, its water table for a walker on the water (elevation 1), its land table otherwise (a sea route with no land
    Pokémon: the ones from its water table that walk on land), at night the night table where the map has one, and on
    Route 20 also Seafoam Islands' Seel and Dewgong. Its script is OverworldMon_EventScript_Encounter: the player can
    choose to battle it, a few levels above the map's wild Pokémon with better IVs (src/overworld_mon_encounter.c);
  * in towns and houses it stays as it was (no battle), other than the Kanto species given below for the few that
    weren't Kanto's.

A walker that breaks a rule is given a species that keeps it: each species it had on a map becomes one species (so a
map never needs more sprite colours than before), the one of the map's allowed species with the fewest walkers so far,
the most common first. Every sprite stays the same size (all are 32x32).

Run from the game's root:
    python3 project/scripts/overworld_mons.py          # apply the rules to the maps' events
    python3 project/scripts/overworld_mons.py --check  # list every walker that breaks them (exit 1 if any)
"""
from __future__ import annotations

import argparse
import collections
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
ENGINE = ROOT / "engine"
SCRIPT = "OverworldMon_EventScript_Encounter"
OUTSIDE = {"MAP_TYPE_ROUTE", "MAP_TYPE_UNDERGROUND"}
NIGHT_FLAG = "JOHTO_FLAG_NIGHT_POKEMON"
WALK_ON_LAND = {"PSYDUCK", "GOLDUCK", "KRABBY", "KINGLER", "SLOWPOKE", "SLOWBRO", "SEEL", "DEWGONG", "POLIWAG",
                "POLIWHIRL", "SHELLDER", "STARYU"}
EXTRA = {"MAP_ROUTE20": ["SEEL", "DEWGONG"]}  # the Seafoam Islands stand in Route 20's sea
# Towns and houses: the walkers that weren't Kanto's, with the Kanto Pokémon each becomes (the nearest in kind).
TOWN_SPECIES = {
    ("PalletTown_Frlg", "PINECO"): "METAPOD",           # hanging in the trees at the town's edges
    ("CinnabarIsland_Frlg", "MAGCARGO"): "PONYTA",      # the fire Pokémon round the volcano
    ("CinnabarIsland_Frlg", "SLUGMA"): "VULPIX",
    ("CinnabarIsland_Frlg", "MAGBY"): "GROWLITHE",
    ("CinnabarIsland_Frlg", "TORKOAL"): "RAPIDASH",
    ("CinnabarIsland_Frlg", "MISDREAVUS"): "GASTLY",    # at night, by the burned Mansion
    ("CinnabarIsland_Frlg", "WAILMER"): "TENTACOOL",    # in the sea
    ("LavenderTown_Frlg", "MISDREAVUS"): "GASTLY",      # with the Gastly round the Tower at night
    ("CeladonCity_Condominiums_1F_Frlg", "SKITTY"): "MEOWTH",
    ("SaffronCity_CopycatsHouse_1F_Frlg", "BLISSEY"): "DITTO",
    ("VermilionCity_PokemonFanClub_Frlg", "BAYLEEF"): "CLEFAIRY",
}


def species_numbers() -> dict[str, int]:
    text = (ENGINE / "include/constants/species.h").read_text()
    return {m.group(1): int(m.group(2)) for m in re.finditer(r"#define SPECIES_(\w+)\s+(\d+)\b", text)}


NUM = species_numbers()


def is_kanto(species: str) -> bool:
    return 1 <= NUM.get(species, 0) <= 151


def wild_tables() -> dict:
    """map id -> {"any" | "night": {kind: [species in slot order]}}, FireRed's tables only."""
    data = json.loads((ENGINE / "src/data/wild_encounters.json").read_text())
    out: dict = collections.defaultdict(dict)
    for entry in data["wild_encounter_groups"][0]["encounters"]:
        label = entry["base_label"]
        if "LeafGreen" in label:
            continue
        when = "night" if label.endswith("_Night") else "any"
        for kind in ("land_mons", "water_mons", "fishing_mons", "rock_smash_mons"):
            if kind in entry:
                out[entry["map"]].setdefault(when, {})[kind] = [m["species"][len("SPECIES_"):]
                                                               for m in entry[kind]["mons"]]
    return out


TABLES = wild_tables()


def allowed(map_id: str, on_water: bool, night: bool) -> list[str]:
    """The species a walker outside towns may be: Kanto's own that you can find on its map, the most common first."""
    tabs = TABLES.get(map_id, {})

    def kinds(when: str, names: tuple[str, ...]) -> list[str]:
        return [s for name in names for s in tabs.get(when, {}).get(name, [])]

    def pick(names: tuple[str, ...]) -> list[str]:
        return (kinds("night", names) if night else []) or kinds("any", names)

    if on_water:
        found = pick(("water_mons", "fishing_mons"))
    else:
        found = pick(("land_mons", "rock_smash_mons"))
        if not found:
            found = [s for s in pick(("water_mons", "fishing_mons")) if s in WALK_ON_LAND]
    found += EXTRA.get(map_id, [])
    return [s for s in dict.fromkeys(found) if is_kanto(s)]


GRAPHICS = re.compile(r"(OBJ_EVENT_GFX_MON_BASE|OBJ_EVENT_MON)\s*\+\s*SPECIES_([A-Z0-9_]+?)((?:\s*\+\s*OBJ_EVENT_MON_\w+)*)")


def walkers(data: dict):
    for i, obj in enumerate(data.get("object_events", [])):
        m = GRAPHICS.fullmatch(str(obj.get("graphics_id", "")))
        if m:
            yield i, obj, m.group(2)


def rules(data: dict, i: int, obj: dict, species: str) -> list[str]:
    """What this walker breaks (empty: nothing)."""
    out = []
    if not is_kanto(species):
        out.append(f"{species} isn't a Kanto Pokémon")
    if data.get("map_type") in OUTSIDE:
        ok = allowed(data["id"], obj.get("elevation") == 1, obj.get("flag") == NIGHT_FLAG)
        if not ok:
            out.append("its map has no Kanto wild Pokémon for it to be")
        elif species not in ok:
            out.append(f"{species} isn't found on {data['id']} ({', '.join(ok)})")
        if obj.get("script") != SCRIPT:
            out.append(f"its script is {obj.get('script')}, not {SCRIPT}")
    return out


def apply(data: dict) -> list[str]:
    changes = []
    name = data["name"]
    count = collections.Counter(s for _, _, s in walkers(data))
    chosen: dict = {}
    for i, obj, species in list(walkers(data)):
        new = species
        if data.get("map_type") in OUTSIDE:
            on_water, night = obj.get("elevation") == 1, obj.get("flag") == NIGHT_FLAG
            ok = allowed(data["id"], on_water, night)
            if ok and species not in ok:
                key = (species, on_water, night)
                if key not in chosen:
                    chosen[key] = min(ok, key=lambda s: (count[s], ok.index(s)))
                new = chosen[key]
            if obj.get("script") != SCRIPT:
                changes.append(f"{name} #{i + 1} {species}: script {obj.get('script')} -> {SCRIPT}")
                obj["script"] = SCRIPT
        elif not is_kanto(species):
            new = TOWN_SPECIES.get((name, species), species)
        if new != species:
            count[species] -= 1
            count[new] += 1
            m = GRAPHICS.fullmatch(obj["graphics_id"])  # keeps a shiny walker shiny
            obj["graphics_id"] = f"{m.group(1)}+SPECIES_{new}{m.group(3)}"
            changes.append(f"{name} #{i + 1} at ({obj['x']},{obj['y']}): {species} -> {new}")
    return changes


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--check", action="store_true", help="list the walkers that break the rules; change nothing")
    args = ap.parse_args()
    broken = 0
    for path in sorted((ENGINE / "data/maps").glob("*_Frlg/map.json")):
        text = path.read_text()
        data = json.loads(text)
        if not any(True for _ in walkers(data)):
            continue
        if args.check:
            for i, obj, species in walkers(data):
                for why in rules(data, i, obj, species):
                    print(f"{data['name']} #{i + 1} at ({obj['x']},{obj['y']}): {why}")
                    broken += 1
            continue
        for line in apply(data):
            print(line)
        new = json.dumps(data, indent=2) + "\n"
        if new != text:
            path.write_text(new)
    if args.check:
        print(f"{broken} broken" if broken else "every Kanto walker keeps the rules")
    return 1 if broken else 0


if __name__ == "__main__":
    sys.exit(main())

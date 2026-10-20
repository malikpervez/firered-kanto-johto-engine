#!/usr/bin/env python3
"""Add the bounded FireRed night-bird overlay to an isolated source JSON.

The supplied baseline must be the frozen candidate05 encounter input. Existing
FireRed daytime entries, all other targets and all encounter levels/rates stay
unchanged. The source generator already understands FireRed and _Night labels.
This recipe neither builds a ROM nor modifies a save or the system clock.
"""

import argparse
import copy
import hashlib
import json
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
BASELINE_SHA256 = "b3b610ee92b6e4ed4e5f0599b9fce780aff77de09840e2167397196394226fa6"
EXPECTED_MAPS = (
    "MAP_ROUTE1", "MAP_ROUTE2", "MAP_ROUTE5", "MAP_ROUTE13",
    "MAP_ROUTE14", "MAP_ROUTE15", "MAP_ROUTE25",
)
POLICY = (
    ("SPECIES_PIDGEY", "SPECIES_HOOTHOOT", 1),
    ("SPECIES_PIDGEOTTO", "SPECIES_NOCTOWL", 20),
)


def digest(data):
    return hashlib.sha256(data).hexdigest()


def make_overlay(baseline):
    result = copy.deepcopy(baseline)
    rows = result["wild_encounter_groups"][0]["encounters"]
    by_label = {row["base_label"]: row for row in rows}
    additions, changes = [], []
    for row in list(rows):
        if not row["base_label"].endswith("_FireRed"):
            continue
        native_map = row["map"]
        if native_map not in EXPECTED_MAPS or "land_mons" not in row:
            continue
        hns_map = native_map + "_HNS"
        days = [x for x in rows if x["map"] == hns_map and x["base_label"].endswith("_hns_Day")]
        nights = [x for x in rows if x["map"] == hns_map and x["base_label"].endswith("_hns_Night")]
        if len(days) != 1 or len(nights) != 1:
            raise ValueError("Exact matching HnS Day/Night providers required: " + native_map)
        day, night = days[0], nights[0]
        day_species = {x["species"] for x in day["land_mons"]["mons"]}
        night_species = {x["species"] for x in night["land_mons"]["mons"]}
        overlay = {
            "map": native_map,
            "base_label": row["base_label"] + "_Night",
            "land_mons": copy.deepcopy(row["land_mons"]),
        }
        if overlay["base_label"] in by_label:
            raise ValueError("Baseline already contains planned overlay")
        slot_changes = []
        if len(overlay["land_mons"]["mons"]) != 12:
            raise ValueError("Original twelve-slot native land table required")
        for slot, mon in enumerate(overlay["land_mons"]["mons"]):
            for original, nocturnal, minimum in POLICY:
                if (mon["species"] == original and original in day_species
                        and nocturnal in night_species and mon["min_level"] >= minimum):
                    mon["species"] = nocturnal
                    slot_changes.append({"slot": slot, "before": original, "after": nocturnal,
                                         "min_level": mon["min_level"], "max_level": mon["max_level"]})
                    break
        if not slot_changes:
            raise ValueError("Planned overlay lacks a grounded substitution: " + native_map)
        additions.append(overlay)
        changes.append({"map": native_map, "native_day_label": row["base_label"],
                        "night_label": overlay["base_label"], "encounter_rate": row["land_mons"]["encounter_rate"],
                        "HnS_day_provider": day["base_label"], "HnS_night_provider": night["base_label"],
                        "slots": slot_changes})
    if sorted(x["map"] for x in additions) != sorted(EXPECTED_MAPS):
        raise ValueError("Actual seven-map overlay differs from reviewed scope")
    rows.extend(additions)
    return result, changes


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--baseline-json", type=Path, required=True)
    parser.add_argument("--source-json", type=Path, required=True)
    parser.add_argument("--report", type=Path, required=True)
    parser.add_argument("--apply", action="store_true", help="Write only the explicitly selected isolated source JSON")
    args = parser.parse_args()
    baseline_path, source_path, report_path = [p.resolve() for p in (args.baseline_json, args.source_json, args.report)]
    if not source_path.is_relative_to(ROOT / "_local/worktrees") or source_path.parts[-3:] != ("src", "data", "wild_encounters.json"):
        raise ValueError("An isolated B-owned encounter source under _local/worktrees is required")
    if not report_path.is_relative_to(ROOT / "_local/evidence") or report_path.exists():
        raise ValueError("A new ignored private evidence report is required")
    baseline_bytes = baseline_path.read_bytes()
    if digest(baseline_bytes) != BASELINE_SHA256:
        raise ValueError("Baseline differs from exact frozen candidate05 input")
    baseline = json.loads(baseline_bytes)
    updated, changes = make_overlay(baseline)
    before = source_path.read_bytes()
    source = json.loads(before)
    if source == updated:
        status = "ALREADY APPLIED; source unchanged"
    elif source == baseline:
        status = "APPLIED" if args.apply else "PREPARED; source unchanged"
        if args.apply:
            source_path.write_text(json.dumps(updated, indent=2, ensure_ascii=False) + "\n")
    else:
        raise ValueError("Source has unrelated encounter changes; refusing to replace them")
    report = {
        "status": status, "baseline": {"path": str(baseline_path), "sha256": digest(baseline_bytes)},
        "source": str(source_path), "before_sha256": digest(before), "after_sha256": digest(source_path.read_bytes()),
        "recipe_sha256": digest(Path(__file__).read_bytes()), "changes": changes,
        "original_rows_semantic_equal_and_order_preserved": True,
        "new_rows_land_only": True, "original_native_levels_rates_and_other_slots_preserved": True,
        "species_enable_flags_save_layout_clock_changes": "NONE",
        "estimated_ROM_payload_bytes": len(changes) * (12 * 4 + 8),
        "ROM_estimate_qualification": "Seven original-size land arrays plus Info structs; existing header slots reused. Actual link delta is not measured here.",
        "build_and_gameplay": "NOT RUN by this recipe",
    }
    report_path.parent.mkdir(parents=True, exist_ok=True)
    report_path.write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps({"status": status, "maps": len(changes), "slot_changes": sum(len(x["slots"]) for x in changes),
                      "report": str(report_path), "report_sha256": digest(report_path.read_bytes())}))


if __name__ == "__main__":
    main()

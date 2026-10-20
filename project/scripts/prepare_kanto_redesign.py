#!/usr/bin/env python3
"""Apply explicit local Kanto geometry plans without copying donor story state.

Plans and source/assets stay in ignored _local paths. The default is a dry run.
Native map/layout identities, event order, scripts, flags and warp destinations
are preserved. Only reviewed coordinates and native FireRed-only geometry
overlays are permitted; this tool does not qualify gameplay or convert saves.
"""
import argparse
import copy
import datetime
import hashlib
import json
from pathlib import Path
import re
import subprocess


ROOT = Path(__file__).resolve().parents[1]
PIN = "167aa6d537b109bb229c231ddce4616974c4da71"
LAYOUT_FIELDS = {
    "width", "height", "primary_tileset", "secondary_tileset", "border_filepath",
    "blockdata_filepath", "border_width", "border_height", "layout_version",
}
EVENT_FIELDS = {"x", "y", "elevation"}
INHERITED_BG_PROVIDERS = {
    "EventScript_Questionnaire",
    "EventScript_AdvertisingPoster",
    "EventScript_NeatlyLinedUpTools",
    "EventScript_RegionMap",
}


def digest(data):
    return hashlib.sha256(data).hexdigest()


def private(value, parent):
    path = Path(value).resolve()
    if not path.is_relative_to(parent.resolve()):
        raise ValueError("Path is outside its B-owned private scope: " + str(path))
    return path


def name(value):
    if not re.fullmatch(r"[A-Za-z0-9_]+", value):
        raise ValueError("Invalid map name: " + value)
    return value


def encoded(value):
    return (json.dumps(value, indent=2) + "\n").encode()


def effective_map(value):
    result = copy.deepcopy(value)
    overlay = result.get("firered_campaign", {})
    if not isinstance(overlay, dict):
        raise ValueError("Expected an explicit map overlay object")
    result.update(overlay)
    return result


def geometry(layout):
    result = copy.deepcopy(layout)
    if isinstance(result.get("firered_campaign"), dict):
        result.update(result["firered_campaign"])
    return result


def validate_events(value, layout):
    width, height = layout["width"], layout["height"]
    for category in ("object_events", "warp_events", "coord_events", "bg_events"):
        for index, event in enumerate(value.get(category, [])):
            x, y = event["x"], event["y"]
            if not isinstance(x, int) or not isinstance(y, int):
                raise ValueError("Noninteger event coordinate")
            if not (0 <= x < width and 0 <= y < height):
                raise ValueError(f"Out-of-bounds {category}[{index}] at {x},{y}")


def prepare(args):
    source = private(args.source, ROOT / "_local/worktrees")
    plan_path = private(args.plan, ROOT / "_local")
    output = private(args.out, ROOT / "_local/evidence")
    if output.exists():
        raise ValueError("Use a fresh evidence directory")
    checked = subprocess.run(
        ["/usr/bin/git", "--no-optional-locks", "-C", str(source), "rev-parse", "HEAD"],
        capture_output=True, text=True, check=False,
    )
    if checked.returncode or checked.stdout.strip() != PIN:
        raise ValueError("Source is not pinned to the approved commit")
    plan_raw = plan_path.read_bytes()
    plan = json.loads(plan_raw)
    if plan.get("schema") != "kanto-redesign-plan-1" or not plan.get("maps"):
        raise ValueError("Expected a nonempty versioned explicit geometry plan")
    layouts_path = source / "data/layouts/layouts.json"
    layouts_raw = layouts_path.read_bytes()
    if digest(layouts_raw) != plan["expected_layout_registry_sha256"]:
        raise ValueError("The layout registry changed after planning")
    layouts = json.loads(layouts_raw)
    by_id = {row["id"]: row for row in layouts["layouts"] if row}
    if len(by_id) != len([row for row in layouts["layouts"] if row]):
        raise ValueError("Duplicate layout identity")
    originals = {layouts_path: layouts_raw}
    changed = {}
    records = []
    touched_layouts = set()
    seen_maps = set()
    for entry in plan["maps"]:
        native_name = name(entry["native_map"])
        donor_name = name(entry["donor_map"])
        if native_name in seen_maps:
            raise ValueError("Duplicate map plan")
        seen_maps.add(native_name)
        native_path = source / "data/maps" / native_name / "map.json"
        donor_path = source / "data/maps" / donor_name / "map.json"
        native_raw, donor_raw = native_path.read_bytes(), donor_path.read_bytes()
        if digest(native_raw) != entry["expected_native_sha256"]:
            raise ValueError("Native map changed: " + native_name)
        if digest(donor_raw) != entry["expected_donor_sha256"]:
            raise ValueError("Donor map changed: " + donor_name)
        native, donor = json.loads(native_raw), json.loads(donor_raw)
        if native.get("game_version") != "frlg" or native.get("region") != "REGION_KANTO":
            raise ValueError("Only an explicit native Kanto map may be redesigned")
        before = effective_map(native)
        target = copy.deepcopy(before)
        target_layout = by_id[before["layout"]]
        donor_layout = geometry(by_id[donor["layout"]])
        asset_records = []
        for key in ("border_filepath", "blockdata_filepath"):
            asset = private(source / donor_layout[key], source / "data/layouts")
            raw = asset.read_bytes()
            if digest(raw) != entry["expected_donor_assets"][key]:
                raise ValueError("Donor layout asset changed")
            asset_records.append({"path": str(asset), "sha256": digest(raw), "bytes": len(raw)})
        block = source / donor_layout["blockdata_filepath"]
        if block.stat().st_size != 2 * donor_layout["width"] * donor_layout["height"]:
            raise ValueError("Blockmap dimensions do not match its byte count")
        mode = entry.get("geometry_mode", "donor")
        if mode not in ("donor", "native", "map"):
            raise ValueError("Unknown geometry mode")
        effective_geometry = geometry(target_layout)
        if mode in ("donor", "map"):
            selected_geometry = {
                key: donor_layout[key] for key in sorted(LAYOUT_FIELDS) if key in donor_layout
            }
            selected_geometry["layout_version"] = donor_layout.get("layout_version", "hns")
            if mode == "map":
                # Keep global shared layouts and every unrelated consumer intact.
                target["firered_geometry"] = selected_geometry
                effective_geometry = {**target_layout, **selected_geometry}
            else:
                if target_layout["id"] in touched_layouts:
                    raise ValueError("Shared native layout needs a single explicit plan")
                touched_layouts.add(target_layout["id"])
                target_layout["firered_campaign"] = selected_geometry
                effective_geometry = geometry(target_layout)
        for category, edits in entry.get("event_positions", {}).items():
            if category not in ("object_events", "warp_events", "coord_events", "bg_events"):
                raise ValueError("Unsupported event category")
            used = set()
            for edit in edits:
                index = edit["index"]
                if not isinstance(index, int) or not 0 <= index < len(target[category]) or index in used:
                    raise ValueError("Invalid or duplicate event index")
                used.add(index)
                positions = edit["position"]
                if not positions or not set(positions) <= EVENT_FIELDS:
                    raise ValueError("A position plan cannot change script, flag, reward or warp destination")
                if any(not isinstance(v, int) for v in positions.values()):
                    raise ValueError("Event positions must be integers")
                target[category][index].update(positions)
        added_ambient = []
        for index in entry.get("ambient_indices", []):
            if not isinstance(index, int) or not 0 <= index < len(donor.get("object_events", [])):
                raise ValueError("Invalid ambient donor index")
            actor = copy.deepcopy(donor["object_events"][index])
            gfx = actor.get("graphics_id", "")
            if not ("OBJ_EVENT_GFX_MON_BASE" in gfx or "OBJ_EVENT_MON+SPECIES_" in gfx):
                raise ValueError("The ambient importer accepts existing species graphics only")
            if actor.get("script") != "NULL" or str(actor.get("flag")) != "0" \
             or actor.get("trainer_type") != "TRAINER_TYPE_NONE" or "local_id" in actor:
                raise ValueError("Only source-proven NULL/flag0 ambient actors are currently supported")
            if index in added_ambient:
                raise ValueError("Duplicate ambient actor index")
            actor["type"] = "object"
            target["object_events"].append(actor)
            added_ambient.append(index)
        if len(target.get("object_events", [])) > 64:
            raise ValueError("The existing current-map template capacity would be exceeded")
        added_interactions = []
        for event in entry.get("inherited_bg_events", []):
            # Explicit bindings restore existing native metatile interactions;
            # they cannot introduce a new script, reward or persistent field.
            if set(event) != {"type", "x", "y", "elevation", "player_facing_dir", "script"} \
             or event["type"] != "sign" or event["elevation"] != 0 \
             or event["player_facing_dir"] != "BG_EVENT_PLAYER_FACING_ANY" \
             or event["script"] not in INHERITED_BG_PROVIDERS:
                raise ValueError("Unsupported inherited native interaction")
            if any((old["x"], old["y"]) == (event["x"], event["y"])
                   for old in target.get("bg_events", [])):
                raise ValueError("Inherited interaction duplicates an existing background event")
            target.setdefault("bg_events", []).append(copy.deepcopy(event))
            added_interactions.append(event)
        validate_events(target, effective_geometry)
        overlay = copy.deepcopy(native.get("firered_campaign", {}))
        if mode == "map":
            overlay["firered_geometry"] = target["firered_geometry"]
        for category in ("object_events", "warp_events", "coord_events", "bg_events"):
            if target.get(category) != before.get(category):
                overlay[category] = target[category]
            for old_event, new_event in zip(before.get(category, []), target.get(category, [])):
                if {k:v for k,v in old_event.items() if k not in EVENT_FIELDS} != {
                    k:v for k,v in new_event.items() if k not in EVENT_FIELDS
                }:
                    raise ValueError("Noncoordinate event semantics changed")
        if overlay:
            native["firered_campaign"] = overlay
        originals[native_path] = native_raw
        changed[native_path] = encoded(native)
        records.append({
            "native_map": native_name, "donor_map": donor_name,
            "map_identity": before["id"], "layout_identity": before["layout"],
            "native_event_counts": {k:len(before.get(k,[])) for k in
                                    ("object_events", "warp_events", "coord_events", "bg_events")},
            "result_event_counts": {k:len(target.get(k,[])) for k in
                                    ("object_events", "warp_events", "coord_events", "bg_events")},
            "added_NULL_flag0_ambient_donor_indices": added_ambient,
            "geometry_mode": mode,
            "inherited_native_interactions": added_interactions,
            "donor_assets_read_only": asset_records, "event_positions": entry.get("event_positions", {}),
            "scripts_flags_rewards_warp_destinations_connections_preserved": True,
            "notes": entry.get("notes", []),
        })
    changed[layouts_path] = encoded(layouts)
    # Validate the entire plan before creating evidence or changing source.
    for path, raw in originals.items():
        if path.read_bytes() != raw:
            raise ValueError("Source changed during planning")
    output.mkdir(parents=True)
    for path, raw in originals.items():
        before_path = output / "before" / path.relative_to(source)
        before_path.parent.mkdir(parents=True, exist_ok=True)
        with before_path.open("xb") as stream:
            stream.write(raw)
    written = []
    for path, raw in changed.items():
        row = {"path": str(path.relative_to(source)), "before_sha256": digest(originals[path]),
               "after_sha256": digest(raw), "different": raw != originals[path]}
        if args.apply and row["different"]:
            if path.read_bytes() != originals[path]:
                raise ValueError("Source changed immediately before write")
            with path.open("wb") as stream:
                stream.write(raw)
            if path.read_bytes() != raw:
                raise ValueError("Source write mismatch")
        written.append(row)
    receipt = {
        "created_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(),
        "status": "APPLIED explicit FireRed-only geometry plan" if args.apply else "DRY RUN; source unchanged",
        "source": str(source), "upstream_pin": PIN, "plan": str(plan_path),
        "plan_sha256": digest(plan_raw), "script_sha256": digest(Path(__file__).read_bytes()),
        "records": records, "source_changes": written,
        "originals_preserved": "Each input is frozen in this invocation's before/ directory",
        "assets": "Read-only references to existing pinned donor assets; no asset bytes copied/edited",
        "save_and_runtime": "No save or emulator operations. Build, rendering and gameplay NOT RUN by this tool.",
    }
    with (output / "receipt.json").open("x") as stream:
        json.dump(receipt, stream, indent=2)
        stream.write("\n")
    print(json.dumps({"status":receipt["status"], "maps":len(records),
                      "receipt":str(output / "receipt.json")}, indent=2))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", required=True)
    parser.add_argument("--plan", required=True)
    parser.add_argument("--out", required=True)
    parser.add_argument("--apply", action="store_true")
    prepare(parser.parse_args())


if __name__ == "__main__":
    main()

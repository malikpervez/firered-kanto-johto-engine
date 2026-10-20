#!/usr/bin/env python3
"""Create an isolated B-owned diagnostic save, never a natural-play milestone.

Presets change location only, or explicitly stage the eight native Kanto badge
bits and native game-clear bit. Johto state is never created or edited. Late
quests still need an appropriate separately reviewed story checkpoint.
"""
from __future__ import annotations

import argparse
import datetime
import json
from pathlib import Path
import re
import shlex
import struct
import subprocess

import firered_save_codec as codec

ROOT = Path(__file__).resolve().parents[1]
PRESETS = ("location-only", "pre-champion", "post-kanto-champion")


def require(condition, message):
    if not condition:
        raise ValueError(message)


def reference(path):
    path = Path(path).resolve()
    data = path.read_bytes()
    return {"path": str(path), "bytes": len(data), "sha256": codec.sha256(data)}


def command(argv, directory, label, evidence):
    result = subprocess.run(argv, cwd=directory, capture_output=True)
    (evidence / (label + ".stdout")).write_bytes(result.stdout)
    (evidence / (label + ".stderr")).write_bytes(result.stderr)
    record = {"argv": list(map(str, argv)), "cwd": str(directory), "exit_code": result.returncode}
    with (evidence / "commands.jsonl").open("a") as handle:
        handle.write(json.dumps(record) + "\n")
    require(result.returncode == 0, f"{label} failed: see {evidence}")
    return record


def validate_build(manifest):
    require(manifest["target"] == "firered" and manifest["build_exit_code"] == 0
            and manifest["status"].startswith("PASS"), "Require successful FireRed compilation")
    if manifest["wrapper_exit_code"] == 0:
        return {"build_exit_code": 0, "wrapper_exit_code": 0}
    require(manifest.get("qualification_exit_code") == 0, "Wrapper failure needs separate bound qualification")
    for key in ("original_build_manifest", "qualification_evidence"):
        record = manifest[key]
        require(reference(record["path"]) == record, f"{key} binding changed")
    original = json.loads(Path(manifest["original_build_manifest"]["path"]).read_text())
    proof = json.loads(Path(manifest["qualification_evidence"]["path"]).read_text())
    require(original["build_exit_code"] == 0 and original["wrapper_exit_code"] == manifest["wrapper_exit_code"] != 0
            and original["status"].startswith("FAIL"), "Original failure must remain recorded")
    require(all(original[k] == manifest[k] for k in ("build_cwd", "source_commit", "effective_configuration", "complete_source_freeze")), "Qualified build identity differs")
    require(proof["original_build_manifest"] == manifest["original_build_manifest"] and proof["status"].startswith("PASS")
            and proof["every_other_object_byte_identical"] is True
            and proof["all_other_compiled_C_objects_byte_equal_parent"] is True
            and len(proof["actual_file_offsets_old_new"]) == 1
            and all(row["equal"] for row in proof["generated_headers_exact_private_prediction"]), "Bound one-byte qualification is incomplete")
    return {"build_exit_code": 0, "wrapper_exit_code": manifest["wrapper_exit_code"],
            "qualification_exit_code": 0, "original_build_manifest": manifest["original_build_manifest"],
            "qualification_evidence": manifest["qualification_evidence"]}


def measure(manifest, map_name, evidence):
    """Measure the real ARM/APCS ABI and selected map ID, then read ROM layout."""
    tree = Path(manifest["build_cwd"]).resolve()
    freeze = manifest["complete_source_freeze"]
    require(reference(freeze["path"])["sha256"] == freeze["sha256"], "Source freeze binding changed")
    for row in freeze["source_files"]:
        path = tree / row["path"]
        require(not path.exists() if row["status"] == "deleted" else
                reference(path)["sha256"] == row["sha256"], f"Frozen source changed: {row['path']}")
    toolbin = Path(manifest["toolchain"]) / "bin"
    cc, objcopy, nm = [toolbin / ("arm-none-eabi-" + name) for name in ("gcc", "objcopy", "nm")]
    fields = {
        "save1_size": "sizeof(struct SaveBlock1)",
        "save2_size": "sizeof(struct SaveBlock2)",
        "storage_size": "sizeof(struct PokemonStorage)",
        "save3_size": "sizeof(struct SaveBlock3)",
        "continue_warp": "__builtin_offsetof(struct SaveBlock1, continueGameWarp)",
        "continue_flags": "__builtin_offsetof(struct SaveBlock2, specialSaveWarpFlags)",
        "continue_mask": "CONTINUE_GAME_WARP",
        "native_flags": "__builtin_offsetof(struct SaveBlock1, flags)",
        "native_flags_size": "sizeof(((struct SaveBlock1 *)0)->flags)",
        "warp_group": "__builtin_offsetof(struct WarpData, mapGroup)",
        "warp_num": "__builtin_offsetof(struct WarpData, mapNum)",
        "warp_id": "__builtin_offsetof(struct WarpData, warpId)",
        "warp_x": "__builtin_offsetof(struct WarpData, x)",
        "warp_y": "__builtin_offsetof(struct WarpData, y)",
        "map_id": map_name,
        "game_clear": "FLAG_SYS_GAME_CLEAR",
        **{f"badge{i}": f"FLAG_BADGE{i:02}_GET" for i in range(1, 9)},
        "header_layout": "__builtin_offsetof(struct MapHeader, mapLayout)",
        "layout_width": "__builtin_offsetof(struct MapLayout, width)",
        "layout_height": "__builtin_offsetof(struct MapLayout, height)",
        "layout_map": "__builtin_offsetof(struct MapLayout, map)",
    }
    source = evidence / "arm-checkpoint-fields.c"
    source.write_text('#include "global.h"\n#include "save_location.h"\n#include "pokemon_storage_system.h"\n#include "constants/maps.h"\n'
                      '#include "constants/flags.h"\n'
                      'const unsigned int checkpoint_fields[] __attribute__((section(".checkpoint_probe"),used)) = {\n'
                      + ",\n".join(fields.values()) + "\n};\n")
    config = manifest["effective_configuration"]
    flags = shlex.split(config["CFLAGS"]) + shlex.split(config["CPPFLAGS"])
    require("-mabi=apcs-gnu" in flags and "-DFIRERED" in flags, "Require actual FireRed ARM/APCS configuration")
    obj, binary = evidence / "arm-checkpoint-fields.o", evidence / "arm-checkpoint-fields.bin"
    calls = [command([str(cc), *flags, "-c", str(source), "-o", str(obj)], tree, "arm-probe", evidence)]
    calls.append(command([str(objcopy), "-O", "binary", "--only-section=.checkpoint_probe", str(obj), str(binary)], tree, "extract-probe", evidence))
    raw_fields = binary.read_bytes()
    require(len(raw_fields) == 4 * len(fields), "Unexpected ARM probe section length")
    values = dict(zip(fields, struct.unpack("<" + "I" * len(fields), raw_fields)))
    require([values[k] for k in ("save1_size", "save2_size", "storage_size", "save3_size")] == [15868, 3892, 34144, 1332], "Save ABI differs from strict codec")
    arts = {a["kind"]: a for a in manifest["artifacts"]}
    for kind in ("ROM", "ELF"):
        require(reference(arts[kind]["path"])["sha256"] == arts[kind]["sha256"], f"{kind} binding changed")
    calls.append(command([str(nm), arts["ELF"]["path"]], tree, "elf-symbols", evidence))
    matches = re.findall(r"^([0-9a-fA-F]+)\s+\w\s+gMapGroups$", (evidence / "elf-symbols.stdout").read_text(), re.M)
    require(len(matches) == 1, "ELF lacks unambiguous gMapGroups")
    rom = Path(arts["ROM"]["path"]).read_bytes()

    def u32(address):
        offset = address - 0x08000000
        require(0 <= offset <= len(rom) - 4, "ROM pointer out of bounds")
        return struct.unpack_from("<I", rom, offset)[0]

    group, num = values["map_id"] >> 8, values["map_id"] & 255
    require(group < 128 and num < 128, "Map ID exceeds native signed WarpData")
    header = u32(u32(int(matches[0], 16) + 4 * group) + 4 * num)
    layout = u32(header + values["header_layout"])
    width, height = u32(layout + values["layout_width"]), u32(layout + values["layout_height"])
    require(0 < width <= 1024 and 0 < height <= 1024, "Invalid actual ROM layout")
    return values, {"constant": map_name, "group": group, "num": num,
                    "header": hex(header), "layout": hex(layout), "width": width, "height": height,
                    "blockdata": u32(layout + values["layout_map"])}, rom, calls


def stage(raw, base, fields, point, preset):
    save1, save2, ext = bytearray(base.save1), bytearray(base.save2), bytearray(base.extension)
    masks1, masks2 = {}, {}
    at = fields["continue_warp"]
    for key, fmt, value in [("warp_group", "b", point["group"]), ("warp_num", "b", point["num"]),
                            ("warp_id", "b", -1), ("warp_x", "h", point["x"]), ("warp_y", "h", point["y"])]:
        offset = at + fields[key]
        struct.pack_into("<" + fmt, save1, offset, value)
        masks1.update({offset + i: 255 for i in range(struct.calcsize(fmt))})
    offset, mask = fields["continue_flags"], fields["continue_mask"]
    save2[offset] |= mask
    masks2[offset] = mask
    if preset != "location-only":
        for flag, enabled in ([(fields["game_clear"], preset == "post-kanto-champion")]
                              + [(fields[f"badge{i}"], True) for i in range(1, 9)]):
            require(flag // 8 < fields["native_flags_size"], "Native flag outside measured capacity")
            offset, mask = fields["native_flags"] + flag // 8, 1 << (flag % 8)
            save1[offset] = save1[offset] | mask if enabled else save1[offset] & ~mask
            masks1[offset] = masks1.get(offset, 0) | mask
    payloads = list(base.payloads)
    payloads[0] = bytes(save2)
    cursor = 0
    for logical in range(1, 5):
        length = len(payloads[logical])
        payloads[logical] = bytes(save1[cursor:cursor + length])
        cursor += length
    payloads = tuple(payloads)
    ext[84:116] = codec.main_digest(bytes(ext), payloads)
    struct.pack_into("<I", ext, 80, codec.extension_crc(bytes(ext)))
    codec.validate_extension(bytes(ext), base.counter, payloads)
    chunks = bytearray(b"".join(s[3968:4084] for s in base.sectors))
    chunks[:codec.EXTENSION_SIZE] = ext
    output, allowed = bytearray(raw), {}

    def allow(logical, local, mask=255):
        position = (base.index * 14 + (logical + base.rotation) % 14) * 4096 + local
        allowed[position] = allowed.get(position, 0) | mask

    for offset, mask in masks2.items():
        allow(0, offset, mask)
    for offset, mask in masks1.items():
        remaining = offset
        for logical in range(1, 5):
            if remaining < len(payloads[logical]):
                allow(logical, remaining, mask)
                break
            remaining -= len(payloads[logical])
        else:
            raise ValueError("Save1 allowlist offset outside payload")
    for offset in range(80, 116):
        allow(offset // 116, 3968 + offset % 116)
    for logical, payload in enumerate(payloads):
        sector = bytearray(base.sectors[logical])
        sector[:len(payload)] = payload
        sector[3968:4084] = chunks[logical * 116:(logical + 1) * 116]
        struct.pack_into("<H", sector, 4086, codec.native_checksum(payload))
        if payload != base.payloads[logical]:
            allow(logical, 4086)
            allow(logical, 4087)
        start = (base.index * 14 + (logical + base.rotation) % 14) * 4096
        output[start:start + 4096] = sector
    output = bytes(output)
    changes = []
    for i, (before, after) in enumerate(zip(raw, output)):
        if before != after:
            require(not ((before ^ after) & ~allowed.get(i, 0)), f"Unlisted physical change at {i}")
            changes.append({"offset": i, "before": before, "after": after, "mask": allowed[i]})
    selected, outcome, banks = codec.select_bank(output)
    require(outcome == "loaded" and [b.status for b in banks] == ["valid", "valid"], "Require two strict valid output banks")
    require((selected.index, selected.counter, selected.rotation) == (base.index, base.counter, base.rotation), "Bank identity changed")
    require(selected.save1 == save1 and selected.save2 == save2 and selected.extension == ext, "Reparse differs from intended bytes")
    require(selected.storage == base.storage and selected.extension[:80] == base.extension[:80]
            and selected.extension[116:] == base.extension[116:], "Protected PC/regional/header bytes changed")
    return output, changes


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", required=True, type=Path)
    parser.add_argument("--source-sha256", required=True)
    parser.add_argument("--build-manifest", required=True, type=Path)
    parser.add_argument("--map", required=True, dest="map_name")
    parser.add_argument("--x", required=True, type=int)
    parser.add_argument("--y", required=True, type=int)
    parser.add_argument("--preset", choices=PRESETS, default="location-only")
    parser.add_argument("--out", required=True, type=Path, help="New private directory; never reused")
    parser.add_argument("--write", action="store_true", help="Emit checkpoint.sav after all byte checks; default is plan only")
    args = parser.parse_args()
    source, out = args.source.resolve(), args.out.resolve()
    require(source.is_relative_to(ROOT / "_local/saves/firered"), "Only explicitly selected B-owned FireRed test saves")
    require(out.is_relative_to(ROOT / "_local") and not out.exists(), "Require a new ignored local output directory")
    require(re.fullmatch(r"MAP_[A-Z0-9_]+", args.map_name), "Map must be a constant, not C source")
    original = source.read_bytes()
    require(codec.sha256(original) == args.source_sha256, "Source SHA binding mismatch")
    base, outcome, banks = codec.select_bank(original)
    require(outcome == "loaded" and [b.status for b in banks] == ["valid", "valid"], "Require two strict valid native6 banks")
    manifest = json.loads(args.build_manifest.read_text())
    build_acceptance = validate_build(manifest)
    out.mkdir(parents=True)
    fields, point, rom, calls = measure(manifest, args.map_name, out)
    require(0 <= args.x < point["width"] and 0 <= args.y < point["height"], "Coordinate outside actual ROM layout")
    offset = point["blockdata"] - 0x08000000 + 2 * (args.y * point["width"] + args.x)
    require(0 <= offset <= len(rom) - 2, "Blockdata outside actual ROM")
    word = struct.unpack_from("<H", rom, offset)[0]
    require((word >> 10) & 3 == 0, "Selected actual ROM tile has collision")
    point.update(x=args.x, y=args.y, source_word=word,
                 geometry_limit="Actual layout bounds and collision checked; terrain, actors, scripts and quest suitability require the focused review.")
    output, changes = stage(original, base, fields, point, args.preset)
    require(source.read_bytes() == original, "Original changed during preparation")
    report = {
        "status": "STAGED NOT NATURAL; native execution NOT RUN" if args.write else "PLAN ONLY; save not emitted; native execution NOT RUN",
        "recorded_utc": datetime.datetime.now(datetime.timezone.utc).isoformat(), "preset": args.preset,
        "source": reference(source), "build_manifest": reference(args.build_manifest),
        "build_acceptance": build_acceptance,
        "build_artifacts": manifest["artifacts"], "generator": reference(__file__),
        "source_freeze": {key: manifest["complete_source_freeze"][key] for key in ("path", "sha256")},
        "codec": reference(ROOT / "scripts/firered_save_codec.py"), "ARM_fields": fields, "probe_commands": calls,
        "destination": point, "selected_bank": base.index, "generation": base.counter, "rotation": base.rotation,
        "output_sha256": codec.sha256(output), "output_bytes": len(output), "physical_byte_changes": changes,
        "preservation": "All physical differences checked against exact masks: Continue request/bit, explicitly listed native badge/clear bits, affected checksums and existing FRJS digest/CRC only. Identity, party, PC, items, money, Dex, rival, all Johto state, reserve, backup bank, special sectors and trailer preserved.",
        "cache_policy": "Retain source current map/cache/actors/templates. Native Continue consumes the request; normal warp loader reconstructs destination layout/cache/actors/templates and clears map temporaries before input.",
        "limits": "Staging is no evidence of natural gym/League completion. No Johto grants or quest states are invented. Merely placing a trainer at a late map does not establish that its story is ready.",
    }
    if args.write:
        with (out / "checkpoint.sav").open("xb") as handle:
            require(handle.write(output) == len(output), "Incomplete save write")
        require((out / "checkpoint.sav").read_bytes() == output, "Save readback mismatch")
    with (out / "manifest.json").open("x") as handle:
        handle.write(json.dumps(report, indent=2) + "\n")
    require(source.read_bytes() == original, "Original changed during output write")
    print(json.dumps({"status": report["status"], "out": str(out), "sha256": report["output_sha256"]}))


if __name__ == "__main__":
    main()

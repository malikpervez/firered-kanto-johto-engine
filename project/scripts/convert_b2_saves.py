#!/usr/bin/env python3
"""Convert the three approved immutable B2 fixtures into new local files only."""

from __future__ import annotations

import argparse
import json
import os
import stat
from datetime import datetime, timezone
from pathlib import Path

from firered_save_codec import ALLOWED_INPUTS, SaveValidationError, convert_allowed_fixture, sha256


ROOT = Path(__file__).resolve().parents[1]
INPUT_DIR = ROOT / "_local/saves/firered/b2-native-01"
DEFAULT_OUTPUT_DIR = ROOT / "_local/saves/firered/save-foundation-converted-01"
APPROVED_PROPOSAL = ROOT / "_local/evidence/save-foundation-01/approved-proposal.md"
APPROVED_SHA = "37c8886e78e1ad5f4c83d613ccae4825a2c26a2adbab6ad395aca93f90cd77f7"
FIXTURES = ("kanto-before-travel", "johto-cycle-01", "kanto-cycle-02")


def convert_file(source: Path, destination: Path) -> dict:
    if source.resolve() == destination.resolve():
        raise SaveValidationError("same-file", "conversion must write a separate file")
    before = source.read_bytes()
    before_stat = source.stat()
    if stat.S_IMODE(before_stat.st_mode) != 0o444:
        raise SaveValidationError("mutable-source", "approved source fixture must remain mode0444")
    output, report = convert_allowed_fixture(before)
    destination.parent.mkdir(parents=True, exist_ok=True)
    if destination.exists():
        if destination.read_bytes() != output:
            raise SaveValidationError("output-exists", "refusing to overwrite a different existing output")
        disposition = "existing identical output retained"
    else:
        with destination.open("xb") as handle:
            handle.write(output)
            handle.flush()
            os.fsync(handle.fileno())
        destination.chmod(0o444)
        disposition = "new copy written and made0444"
    after = source.read_bytes()
    after_stat = source.stat()
    if before != after or stat.S_IMODE(after_stat.st_mode) != 0o444:
        raise SaveValidationError("source-modified", "original bytes/mode changed during conversion")
    if destination.read_bytes() != output:
        raise SaveValidationError("output-verification", "written output differs from qualified encoding")
    report.update({
        "input_path": str(source.resolve()), "output_path": str(destination.resolve()),
        "input_mode": "0444", "output_mode": f"{stat.S_IMODE(destination.stat().st_mode):04o}",
        "input_hash_unchanged": sha256(before) == sha256(after),
        "disposition": disposition,
    })
    return report


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output-dir", type=Path, default=DEFAULT_OUTPUT_DIR)
    parser.add_argument("--manifest", type=Path, required=True)
    args = parser.parse_args()
    if sha256(APPROVED_PROPOSAL.read_bytes()) != APPROVED_SHA:
        parser.error("immutable approved proposal fingerprint mismatch")
    if args.manifest.exists():
        parser.error("manifest exists; choose a new evidence filename rather than overwrite")
    try:
        reports = [convert_file(INPUT_DIR / f"{name}.sav", args.output_dir / f"{name}-frjs1.sav")
                   for name in FIXTURES]
    except (SaveValidationError, OSError) as error:
        parser.error(str(error))
    manifest = {
        "run": "save-foundation-01 exact B2 offline copy conversion",
        "completed_utc": datetime.now(timezone.utc).isoformat(),
        "scope": "Only three immutable approved fixture hashes; no runtime/gameplay qualification",
        "approved_proposal_sha256": APPROVED_SHA,
        "source_pin": "167aa6d537b109bb229c231ddce4616974c4da71",
        "base_patch_sha256": "4260edec61faf85a04e62744f9d5424dbc25cfa37d3bacda54e65d4df69684d1",
        "base_rom_sha256": "8980ba9dced4586dda2450ea102789a4ac8bf4da731f3a8c07db18a0a41ab9f2",
        "native_layout": {"save1": 15868, "save2": 3892, "storage": 34144,
                          "old_save3": 52, "new_save3": 1332},
        "format": {"native_version": 6, "schema": 1, "content": 1, "layout": 1},
        "input_allowlist": ALLOWED_INPUTS,
        "tool_sha256": {name: sha256((ROOT / "scripts" / name).read_bytes())
                        for name in ("firered_save_codec.py", "convert_b2_saves.py")},
        "result": "PASS — EXECUTED offline conversion and byte-preservation checks",
        "engine_native_load": "NOT RUN",
        "engine_fault_recovery": "NOT RUN",
        "fixtures": reports,
    }
    args.manifest.parent.mkdir(parents=True, exist_ok=True)
    with args.manifest.open("x", encoding="utf-8") as handle:
        json.dump(manifest, handle, indent=2)
        handle.write("\n")
    print(json.dumps({"result": manifest["result"], "manifest": str(args.manifest.resolve()),
                      "outputs": [report["output_path"] for report in reports]}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

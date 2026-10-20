#!/usr/bin/env python3
"""Finite host-codec checks; explicitly separate from compiled-engine tests."""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
import zlib
from datetime import datetime, timezone
from pathlib import Path

import firered_save_codec as codec
from convert_b2_saves import DEFAULT_OUTPUT_DIR, FIXTURES, INPUT_DIR, convert_file


ROOT = Path(__file__).resolve().parents[1]
CHECKS: list[dict] = []


def check(name: str, condition: bool, detail=None) -> None:
    CHECKS.append({"check": name, "result": "PASS" if condition else "FAIL", "detail": detail})
    if not condition:
        raise AssertionError(name)


def rejected(name: str, data: bytes, code: str | None = None) -> None:
    try:
        codec.select_bank(data)
    except codec.SaveValidationError as error:
        check(name, code is None or error.code == code, str(error))
    else:
        check(name, False, "malformed input accepted")


def replace_sector(data: bytes, bank: codec.Bank, logical_id: int,
                   transform) -> bytes:
    offset = (bank.index * 14 + (logical_id + bank.rotation) % 14) * 4096
    changed = bytearray(data)
    sector = bytearray(changed[offset:offset + 4096])
    transform(sector)
    changed[offset:offset + 4096] = sector
    return bytes(changed)


def replace_extension(data: bytes, bank: codec.Bank, mutate) -> bytes:
    held = bytearray(bank.extension)
    mutate(held)
    held[80:84] = b"\0" * 4
    struct.pack_into("<I", held, 80, zlib.crc32(held) & 0xFFFFFFFF)
    changed = bytearray(data)
    padded = held + b"\0" * (1624 - len(held))
    for logical_id in range(14):
        offset = (bank.index * 14 + (logical_id + bank.rotation) % 14) * 4096 + 3968
        changed[offset:offset + 116] = padded[116 * logical_id:116 * (logical_id + 1)]
    return bytes(changed)


def pair_image(payloads, prefix, first: int, second: int, rotation: int) -> bytes:
    flash = bytearray(b"\xff" * 131072)
    for generation in (first, second):
        encoded = codec.encode_bank(payloads, prefix, generation, rotation)
        offset = (generation & 1) * 14 * 4096
        flash[offset:offset + len(encoded)] = encoded
    return bytes(flash)


def independently_check_conversion(source: bytes, converted: bytes) -> dict:
    """No codec parser/encoder/checksum calls: raw framing and protected bytes."""
    physical_map = {}
    # New output has one complete bank. Locate all committed physical sectors.
    for physical in range(28):
        sector = converted[4096 * physical:4096 * (physical + 1)]
        logical_id, checksum, signature, counter = struct.unpack_from("<HHII", sector, 4084)
        if signature == 0x08012025:
            if logical_id >= 14 or logical_id in physical_map:
                raise AssertionError("independent physical ID validation")
            physical_map[logical_id] = (physical, sector, checksum, counter)
    if set(physical_map) != set(range(14)):
        raise AssertionError("independent complete one-bank output")
    bank_index = physical_map[0][0] // 14
    counter = physical_map[0][3]
    used = [3892, 3968, 3968, 3968, 3964] + [3968] * 8 + [2400]
    payloads = [physical_map[logical_id][1][:used[logical_id]] for logical_id in range(14)]
    extension = b"".join(physical_map[i][1][3968:4084] for i in range(14))[:1332]
    source_map = {}
    for physical in range(bank_index * 14, bank_index * 14 + 14):
        sector = source[4096 * physical:4096 * (physical + 1)]
        source_map[struct.unpack_from("<H", sector, 4084)[0]] = sector
    for logical_id in range(14):
        physical, sector, checksum, generation = physical_map[logical_id]
        expected = bytearray(source_map[logical_id][:used[logical_id]])
        if logical_id == 1:
            expected[0:2] = b"\x06\x00"
        if payloads[logical_id] != bytes(expected) or generation != counter:
            raise AssertionError(f"independent protected payload {logical_id}")
        total = 0
        for byte_offset in range(0, used[logical_id], 4):
            total = (total + int.from_bytes(sector[byte_offset:byte_offset + 4], "little")) & 0xFFFFFFFF
        expected_sum = ((total >> 16) + (total & 65535)) & 65535
        if checksum != expected_sum:
            raise AssertionError(f"independent native checksum {logical_id}")
    frame = b"FRJSMAIN" + extension[52:80]
    for logical_id in list(range(1, 14)) + [0]:
        frame += logical_id.to_bytes(2, "little") + used[logical_id].to_bytes(2, "little") + payloads[logical_id]
    if len(frame) != 53996 or hashlib.sha256(frame).digest() != extension[84:116]:
        raise AssertionError("independent SHA/framing")
    crc_input = extension[:80] + b"\0" * 4 + extension[84:]
    if zlib.crc32(crc_input) & 0xFFFFFFFF != int.from_bytes(extension[80:84], "little"):
        raise AssertionError("independent extension CRC")
    if extension[:52] != source_map[0][3968:4020]:
        raise AssertionError("independent legacy prefix preservation")
    if source[28 * 4096:] != converted[28 * 4096:]:
        raise AssertionError("independent special sector/trailer preservation")
    return {"header_hex": extension[52:116].hex(), "framing_bytes": len(frame),
            "main_sha256": hashlib.sha256(frame).hexdigest(),
            "crc32": f"{zlib.crc32(crc_input) & 0xFFFFFFFF:08x}",
            "all_used_payloads_preserved_except_native_version": True,
            "prefix_special_sectors_trailer_preserved": True}


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--report", type=Path, required=True)
    args = parser.parse_args()
    if args.report.exists():
        parser.error("report exists; preserve it and select a new output path")
    check("CRC32 ISO-HDLC standard vector", zlib.crc32(b"123456789") == 0xCBF43926)
    check("SHA256 empty standard vector", hashlib.sha256(b"").hexdigest() ==
          "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855")
    check("SHA256 abc standard vector", hashlib.sha256(b"abc").hexdigest() ==
          "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad")
    vectors = {}
    for fixture in FIXTURES:
        source_path = INPUT_DIR / f"{fixture}.sav"
        output_path = DEFAULT_OUTPUT_DIR / f"{fixture}-frjs1.sav"
        source, output = source_path.read_bytes(), output_path.read_bytes()
        repeated, _ = codec.convert_allowed_fixture(source)
        check(f"{fixture}: repeat in-memory conversion identical", repeated == output)
        before_hash = codec.sha256(source)
        report = convert_file(source_path, output_path)
        check(f"{fixture}: repeat file conversion retains identical output", report["disposition"] ==
              "existing identical output retained")
        check(f"{fixture}: original bytes and0444 unchanged", source_path.read_bytes() == source
              and (source_path.stat().st_mode & 0o777) == 0o444)
        vectors[fixture] = independently_check_conversion(source, output)
        check(f"{fixture}: independent raw-byte/hash/checksum verification", True, vectors[fixture])
        try:
            codec.convert_allowed_fixture(output)
        except codec.SaveValidationError as error:
            check(f"{fixture}: format6 conversion input rejected", error.code == "input-not-approved")
        else:
            check(f"{fixture}: format6 conversion input rejected", False)
        altered = source[:-1] + bytes([source[-1] ^ 1])
        try:
            codec.convert_allowed_fixture(altered)
        except codec.SaveValidationError as error:
            check(f"{fixture}: unapproved hash rejected", error.code == "input-not-approved")
        else:
            check(f"{fixture}: unapproved hash rejected", False)
    data = (DEFAULT_OUTPUT_DIR / "kanto-cycle-02-frjs1.sav").read_bytes()
    bank, _, _ = codec.select_bank(data)
    check("decode/re-encode roundtrip", codec.encode_bank(bank.payloads, bank.extension[:52],
          bank.counter, bank.rotation, bank.sectors) == data[bank.index * 14 * 4096:(bank.index + 1) * 14 * 4096])
    rejected("out-of-range ID blocked", replace_sector(data, bank, 0,
             lambda sector: struct.pack_into("<H", sector, 4084, 65535)), "unrecoverable")
    rejected("duplicate ID blocked", replace_sector(data, bank, 13,
             lambda sector: struct.pack_into("<H", sector, 4084, 1)), "unrecoverable")
    rejected("mixed counters blocked", replace_sector(data, bank, 2,
             lambda sector: struct.pack_into("<I", sector, 4092, bank.counter + 2)), "unrecoverable")
    rejected("uncommitted signature blocked", replace_sector(data, bank, 0,
             lambda sector: sector.__setitem__(4088, 255)), "unrecoverable")
    rejected("native checksum corruption blocked", replace_sector(data, bank, 3,
             lambda sector: sector.__setitem__(100, sector[100] ^ 1)), "unrecoverable")
    rejected("prefix integrity corruption blocked", replace_sector(data, bank, 0,
             lambda sector: sector.__setitem__(3968, sector[3968] ^ 1)), "unrecoverable")
    rejected("extension boundary integrity corruption blocked", replace_sector(data, bank, 11,
             lambda sector: sector.__setitem__(3968 + 55, sector[3968 + 55] ^ 1)), "unrecoverable")
    rejected("unsupported total length blocked", replace_extension(data, bank,
             lambda ext: struct.pack_into("<H", ext, 60, 65535)), "unrecoverable")
    rejected("unknown content blocked", replace_extension(data, bank,
             lambda ext: struct.pack_into("<I", ext, 68, 2)), "unsupported")
    rejected("main digest mismatch blocked even with validCRC", replace_extension(data, bank,
             lambda ext: ext.__setitem__(84, ext[84] ^ 1)), "unrecoverable")
    pair = pair_image(bank.payloads, bank.extension[:52], 1, 2, bank.rotation)
    newest, status, _ = codec.select_bank(pair)
    check("adjacent generation selects successor", newest.counter == 2 and status == "loaded")
    torn = replace_sector(pair, newest, 0, lambda sector: sector.__setitem__(4088, 255))
    previous, status, _ = codec.select_bank(torn)
    check("torn header falls back to previous whole bank", previous.counter == 1 and status == "recovered")
    wrap = pair_image(bank.payloads, bank.extension[:52], 0xFFFFFFFF, 0, bank.rotation)
    newest, status, _ = codec.select_bank(wrap)
    check("u32 generation wrap selects zero", newest.counter == 0 and status == "loaded")
    rejected("non-adjacent bank fork blocked", pair_image(bank.payloads, bank.extension[:52], 1, 4,
             bank.rotation), "generation-fork")
    moved = bytearray(b"\xff" * 131072)
    only = codec.encode_bank(bank.payloads, bank.extension[:52], 1, bank.rotation)
    moved[:len(only)] = only
    rejected("wrong physical parity blocked", bytes(moved), "unrecoverable")
    wrong_rotation = bytearray(data)
    physical_start = bank.index * 14 * 4096
    left, right = wrong_rotation[physical_start:physical_start + 4096], \
        wrong_rotation[physical_start + 4096:physical_start + 8192]
    wrong_rotation[physical_start:physical_start + 4096] = right
    wrong_rotation[physical_start + 4096:physical_start + 8192] = left
    rejected("inconsistent sector rotation blocked", bytes(wrong_rotation), "unrecoverable")
    rejected("short image blocked", data[:131071], "image-length")
    rejected("unapproved trailer length blocked", data + b"x", "image-length")
    rejected("erased fresh image classified empty", b"\xff" * 131072, "empty")
    result = {
        "completed_utc": datetime.now(timezone.utc).isoformat(),
        "result": "PASS — EXECUTED host converter/codec qualification",
        "checks": CHECKS, "check_count": len(CHECKS), "independent_fixture_vectors": vectors,
        "tool_sha256": {name: codec.sha256((ROOT / "scripts" / name).read_bytes()) for name in
                        ("firered_save_codec.py", "convert_b2_saves.py", "qualify_firered_save_codec.py")},
        "engine_native_load": "NOT RUN", "actual_engine_flash_fault_recovery": "NOT RUN",
        "limits": "Mutations exist only in disposable host-memory copies; these checks do not qualify C engine or gameplay.",
    }
    args.report.parent.mkdir(parents=True, exist_ok=True)
    with args.report.open("x", encoding="utf-8") as handle:
        json.dump(result, handle, indent=2)
        handle.write("\n")
    print(json.dumps({"result": result["result"], "checks": len(CHECKS),
                      "report": str(args.report.resolve())}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

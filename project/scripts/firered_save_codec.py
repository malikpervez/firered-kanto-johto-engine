#!/usr/bin/env python3
"""Strict local codec for the approved FireRed FRJS1 development save format.

This is an independent host implementation/reference, not proof of engine or
emulator behavior. No arbitrary native-v5 save is accepted for conversion.
"""

from __future__ import annotations

import hashlib
import struct
import zlib
from dataclasses import dataclass
from pathlib import Path

FLASH_SIZE = 128 * 1024
SECTOR_SIZE = 4096
PAYLOAD_CAPACITY = 3968
EXTENSION_CHUNK_SIZE = 116
SECTORS_PER_BANK = 14
EXTENSION_SIZE = 1332
EXTENSION_CAPACITY = EXTENSION_CHUNK_SIZE * SECTORS_PER_BANK
LEGACY_PREFIX_SIZE = 52
NATIVE_MAGIC = 0xE8F828BC
SECTOR_SIGNATURE = 0x08012025
FRJS_SCHEMA = 1
CONTENT_ID = 1
B3_CONTENT_ID = 2
CAMPAIGN_CONTENT_ID = 3
CAMPAIGN_SEEDED_FLAG = 4
LAYOUT_ID = 1
PAYLOAD_LENGTHS = (3892, 3968, 3968, 3968, 3964,
                   3968, 3968, 3968, 3968, 3968, 3968, 3968, 3968, 2400)
DIGEST_ORDER = tuple(range(1, 14)) + (0,)
HEADER = struct.Struct("<4sHHHHIIIHH")
ALLOWED_INPUTS = {
    "6fac3f465bfc8fea83dfee6a5fdd73002c879286d35069ac4c4e5de547a6c074":
        "kanto-before-travel",
    "ba7aefef473f237f7eff6d220920348c16c09861b1b1fe74faa0e9d2f43edccd":
        "johto-cycle-01",
    "7ba5fda5ca885fdc87f208a8dd0b48a60fcbc4471640003dbfb06c83cf4dd10e":
        "kanto-cycle-02",
}


class SaveValidationError(ValueError):
    def __init__(self, code: str, detail: str):
        self.code = code
        super().__init__(f"{code}: {detail}")


@dataclass(frozen=True)
class Bank:
    index: int
    counter: int
    rotation: int
    payloads: tuple[bytes, ...]
    extension: bytes
    sectors: tuple[bytes, ...]  # logical ID order

    @property
    def save1(self) -> bytes:
        return b"".join(self.payloads[1:5])

    @property
    def save2(self) -> bytes:
        return self.payloads[0]

    @property
    def storage(self) -> bytes:
        return b"".join(self.payloads[5:])


@dataclass(frozen=True)
class BankResult:
    index: int
    status: str
    bank: Bank | None = None
    error: str | None = None


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def native_checksum(payload: bytes) -> int:
    if len(payload) % 4:
        raise SaveValidationError("length", "native payload must be u32 aligned")
    total = sum(value[0] for value in struct.iter_unpack("<I", payload)) & 0xFFFFFFFF
    return ((total & 0xFFFF) + (total >> 16)) & 0xFFFF


def extension_crc(extension: bytes) -> int:
    if len(extension) != EXTENSION_SIZE:
        raise SaveValidationError("length", "FRJS extension must be exactly 1332 bytes")
    held = bytearray(extension)
    held[80:84] = b"\0" * 4
    return zlib.crc32(held) & 0xFFFFFFFF


def main_digest(extension: bytes, payloads: tuple[bytes, ...]) -> bytes:
    if len(extension) != EXTENSION_SIZE or len(payloads) != 14:
        raise SaveValidationError("length", "digest requires one extension and fourteen payloads")
    digest = hashlib.sha256()
    digest.update(b"FRJSMAIN")
    digest.update(extension[52:80])
    for logical_id in DIGEST_ORDER:
        payload = payloads[logical_id]
        if len(payload) != PAYLOAD_LENGTHS[logical_id]:
            raise SaveValidationError("length", f"wrong used length for logical ID {logical_id}")
        digest.update(struct.pack("<HH", logical_id, len(payload)))
        digest.update(payload)
    return digest.digest()


def foundation_extension(prefix: bytes, counter: int,
                         payloads: tuple[bytes, ...]) -> bytes:
    if len(prefix) != LEGACY_PREFIX_SIZE or not 0 <= counter <= 0xFFFFFFFF:
        raise SaveValidationError("length", "invalid legacy prefix or generation")
    extension = bytearray(EXTENSION_SIZE)
    extension[:52] = prefix
    HEADER.pack_into(extension, 52, b"FRJS", 1, 64, EXTENSION_SIZE, 0,
                     counter, CONTENT_ID, LAYOUT_ID, 2, 0)
    struct.pack_into("<HH", extension, 116, 1, 1)
    struct.pack_into("<HH", extension, 148, 2, 1)
    extension[84:116] = main_digest(bytes(extension), payloads)
    struct.pack_into("<I", extension, 80, extension_crc(bytes(extension)))
    return bytes(extension)


def validate_extension(extension: bytes, counter: int,
                       payloads: tuple[bytes, ...]) -> None:
    if len(extension) != EXTENSION_SIZE:
        raise SaveValidationError("length", "incorrect serialized extension length")
    magic, schema, header_len, total_len, flags, generation, content, layout, count, reserved = \
        HEADER.unpack_from(extension, 52)
    if magic != b"FRJS":
        raise SaveValidationError("extension-magic", "native6 bank lacks FRJS identity")
    if schema != 1 or content not in (CONTENT_ID, B3_CONTENT_ID, CAMPAIGN_CONTENT_ID) or layout != LAYOUT_ID:
        raise SaveValidationError("unsupported", "extension schema/content/layout is not registered")
    if header_len != 64 or total_len != EXTENSION_SIZE:
        raise SaveValidationError("length", "unsupported declared header/extension length")
    if (flags and (content != CAMPAIGN_CONTENT_ID or flags != CAMPAIGN_SEEDED_FLAG)) or reserved or count != 2:
        raise SaveValidationError("unsupported", "format flags/reserved/count not recognized")
    if generation != counter:
        raise SaveValidationError("generation", "extension generation differs from bank counter")
    if struct.unpack_from("<I", extension, 80)[0] != extension_crc(extension):
        raise SaveValidationError("extension-crc", "FRJS CRC mismatch")
    if extension[84:116] != main_digest(extension, payloads):
        raise SaveValidationError("main-digest", "FRJS main-bank binding mismatch")
    if extension[116:120] != struct.pack("<HH", 1, 1):
        raise SaveValidationError("regional-schema", "wrong Kanto metadata identity/schema")
    if extension[148:152] != struct.pack("<HH", 2, 1):
        raise SaveValidationError("regional-schema", "wrong Johto identity/schema")
    validate_regional_state(extension, content)


def validate_regional_state(extension: bytes, content: int) -> None:
    """Validate the exact registered content1/2/3 regional byte meanings.

    Conversion still emits content1 and retains its exact three-input policy.
    Content3 uses allocated event/travel bytes for the campaign, savings and
    two Johto dogs, preserving the prototype slots and the zero stored reserve.
    """
    if content not in (CONTENT_ID, B3_CONTENT_ID, CAMPAIGN_CONTENT_ID):
        raise SaveValidationError("unsupported", "regional content is not registered")
    flags = struct.unpack_from("<H", extension, 62)[0]
    if flags and (content != CAMPAIGN_CONTENT_ID or flags != CAMPAIGN_SEEDED_FLAG):
        raise SaveValidationError("unsupported", "regional header flags are not registered")
    if any(extension[120:148]):
        raise SaveValidationError("regional-state", "native Kanto metadata must remain zero")
    initialized = struct.unpack_from("<I", extension, 152)[0]
    if content == CONTENT_ID or initialized == 0:
        if flags or any(extension[152:]):
            raise SaveValidationError("regional-state", "uninitialized records must be zero")
        return
    if initialized != 1:
        raise SaveValidationError("regional-state", "unregistered Johto metadata")
    revision = 2 if content == CAMPAIGN_CONTENT_ID else 1
    if struct.unpack_from("<III", extension, 168) != (revision, revision, revision):
        raise SaveValidationError("regional-state", "unregistered Johto mapping revisions")
    quest = struct.unpack_from("<H", extension, 564)[0]
    if not flags:
        if any(extension[156:168]):
            raise SaveValidationError("regional-state", "unseeded metadata must stay blank")
        if quest not in (1, 2, 3) or extension[180] != (1 << quest) - 1:
            raise SaveValidationError("regional-state", "contradictory Johto quest milestones")
        if any(extension[181:564]) or any(extension[566:]):
            raise SaveValidationError("regional-state", "unregistered Johto state or nonzero reserve")
        return

    if quest not in (0, 1, 2, 3) or extension[180] & 7 != (1 << quest) - 1:
        raise SaveValidationError("regional-state", "contradictory Johto quest milestones")
    if extension[372] & 0xF8 or any(extension[373:376]) or any(extension[432:436]):
        raise SaveValidationError("regional-state", "unregistered event-tail bytes")
    if any(extension[560:564]) or any(extension[1068:1076]) or any(extension[1076:]):
        raise SaveValidationError("regional-state", "unregistered trainer/travel bits or nonzero reserve")
    if extension[157] > 2:
        raise SaveValidationError("regional-state", "unregistered regional starter state")
    badges = sum(((extension[180 + (index >> 3)] >> (index & 7)) & 1) << bit
                 for bit, index in enumerate(range(1283, 1291)))
    if extension[156] != badges:
        raise SaveValidationError("regional-state", "Johto badge mask differs from its event flags")
    for row in range(40):
        start = 864 + row * 3
        readiness = sum(((extension[436 + ((start + bit) >> 3)] >> ((start + bit) & 7)) & 1) << bit
                        for bit in range(3))
        if readiness > 5:
            raise SaveValidationError("regional-state", "unregistered Johto rematch readiness")
    money, gifts, saving, initialized = struct.unpack_from("<IHBB", extension, 1044)
    if money > 999999 or gifts & ~0x3FF or saving > 1 or initialized != 1:
        raise SaveValidationError("regional-state", "unregistered Johto mother savings state")
    for offset in (376, 404):
        dog = extension[offset:offset + 28]
        species = struct.unpack_from("<H", dog, 8)[0]
        if species == 0:
            if any(dog):
                raise SaveValidationError("regional-state", "empty Johto dog record must be zero")
        elif (species not in (243, 244) or not 1 <= dog[12] <= 100
              or dog[19] > 1 or dog[21] > 1 or dog[22] != 0 or any(dog[23:])):
            raise SaveValidationError("regional-state", "unregistered Johto dog state")


def split_image(data: bytes) -> tuple[bytes, bytes]:
    if len(data) not in (FLASH_SIZE, FLASH_SIZE + 16):
        raise SaveValidationError("image-length", "accept only 128-KiB flash with optional opaque 16-byte trailer")
    return data[:FLASH_SIZE], data[FLASH_SIZE:]


def parse_bank(data: bytes, index: int, native_version: int = 6) -> BankResult:
    if index not in (0, 1) or native_version not in (5, 6):
        raise ValueError("bank index or native version outside explicit codec scope")
    flash, _ = split_image(data)
    start = index * SECTORS_PER_BANK * SECTOR_SIZE
    raw = flash[start:start + SECTORS_PER_BANK * SECTOR_SIZE]
    if raw == b"\xff" * len(raw):
        return BankResult(index, "empty")
    try:
        sectors: list[bytes | None] = [None] * 14
        positions = [-1] * 14
        counter = None
        for physical in range(14):
            sector = raw[physical * SECTOR_SIZE:(physical + 1) * SECTOR_SIZE]
            logical_id, checksum, signature, generation = struct.unpack_from("<HHII", sector, 4084)
            if logical_id >= 14:
                raise SaveValidationError("sector-id", f"out-of-range ID {logical_id}")
            if sectors[logical_id] is not None:
                raise SaveValidationError("duplicate-id", f"logical ID {logical_id} repeated")
            if signature != SECTOR_SIGNATURE:
                raise SaveValidationError("signature", f"logical ID {logical_id} not committed")
            if checksum != native_checksum(sector[:PAYLOAD_LENGTHS[logical_id]]):
                raise SaveValidationError("payload-checksum", f"logical ID {logical_id} checksum mismatch")
            if counter is not None and counter != generation:
                raise SaveValidationError("mixed-generation", "sector counters are inconsistent")
            counter = generation
            sectors[logical_id] = sector
            positions[logical_id] = physical
        if any(sector is None for sector in sectors) or counter is None:
            raise SaveValidationError("missing-id", "bank does not contain every logical ID")
        if counter % 2 != index:
            raise SaveValidationError("bank-parity", "counter is in the wrong physical bank")
        rotation = positions[0]
        if any(positions[logical_id] != (logical_id + rotation) % 14 for logical_id in range(14)):
            raise SaveValidationError("rotation", "logical IDs violate the bank rotation")
        logical_sectors = tuple(sector for sector in sectors if sector is not None)
        payloads = tuple(sector[:PAYLOAD_LENGTHS[i]] for i, sector in enumerate(logical_sectors))
        save1 = b"".join(payloads[1:5])
        version = struct.unpack_from("<H", save1, 0)[0]
        if version != native_version:
            raise SaveValidationError("unsupported", f"native version {version} is not {native_version}")
        if struct.unpack_from("<I", save1, 4320)[0] != NATIVE_MAGIC:
            raise SaveValidationError("native-magic", "native save magic mismatch")
        chunks = b"".join(sector[3968:4084] for sector in logical_sectors)
        extension = chunks[:52 if native_version == 5 else EXTENSION_SIZE]
        if native_version == 6:
            validate_extension(extension, counter, payloads)
        return BankResult(index, "valid", Bank(index, counter, rotation, payloads, extension, logical_sectors))
    except SaveValidationError as error:
        return BankResult(index, "unsupported" if error.code == "unsupported" else "corrupt", error=str(error))


def select_bank(data: bytes, native_version: int = 6) -> tuple[Bank, str, tuple[BankResult, ...]]:
    results = tuple(parse_bank(data, i, native_version) for i in (0, 1))
    valid = [result.bank for result in results if result.bank is not None]
    if any(result.status == "unsupported" for result in results):
        raise SaveValidationError("unsupported", "an occupied bank has an unrecognized format; refusing downgrade")
    if not valid:
        code = "empty" if all(result.status == "empty" for result in results) else "unrecoverable"
        raise SaveValidationError(code, "; ".join(result.error or result.status for result in results))
    if len(valid) == 1:
        return valid[0], "loaded" if all(result.status in ("valid", "empty") for result in results) else "recovered", results
    first, second = valid
    if (first.counter + 1) & 0xFFFFFFFF == second.counter:
        return second, "loaded", results
    if (second.counter + 1) & 0xFFFFFFFF == first.counter:
        return first, "loaded", results
    raise SaveValidationError("generation-fork", "two valid banks have non-adjacent generations")


def encode_bank(payloads: tuple[bytes, ...], prefix: bytes,
                counter: int, rotation: int, source_sectors: tuple[bytes, ...] | None = None) -> bytes:
    """Encode one complete FRJS bank; callers select its physical parity bank."""
    if not 0 <= rotation < 14:
        raise SaveValidationError("rotation", "rotation outside 0..13")
    extension = foundation_extension(prefix, counter, payloads)
    chunks = extension.ljust(EXTENSION_CAPACITY, b"\0")
    bank = bytearray(14 * SECTOR_SIZE)
    for logical_id in range(14):
        sector = bytearray(source_sectors[logical_id] if source_sectors else b"\0" * SECTOR_SIZE)
        payload = payloads[logical_id]
        sector[:len(payload)] = payload
        sector[3968:4084] = chunks[logical_id * 116:(logical_id + 1) * 116]
        struct.pack_into("<HHII", sector, 4084, logical_id, native_checksum(payload), SECTOR_SIGNATURE, counter)
        physical = (logical_id + rotation) % 14
        bank[physical * SECTOR_SIZE:(physical + 1) * SECTOR_SIZE] = sector
    return bytes(bank)


def convert_allowed_fixture(data: bytes) -> tuple[bytes, dict]:
    """Copy conversion of exactly three approved B2 hashes, with no file writes."""
    source_hash = sha256(data)
    if source_hash not in ALLOWED_INPUTS:
        raise SaveValidationError("input-not-approved", "input SHA-256 is outside the three-fixture allowlist")
    source, outcome, results = select_bank(data, 5)
    payloads = list(source.payloads)
    first = bytearray(payloads[1])
    struct.pack_into("<H", first, 0, 6)
    payloads[1] = bytes(first)
    payloads = tuple(payloads)
    encoded = encode_bank(payloads, source.extension, source.counter, source.rotation, source.sectors)
    flash, trailer = split_image(data)
    output = bytearray(b"\xff" * FLASH_SIZE)
    offset = source.index * 14 * SECTOR_SIZE
    output[offset:offset + len(encoded)] = encoded
    output[28 * SECTOR_SIZE:] = flash[28 * SECTOR_SIZE:]
    output = bytes(output) + trailer
    target, target_outcome, target_results = select_bank(output, 6)
    expected_save1 = bytearray(source.save1)
    struct.pack_into("<H", expected_save1, 0, 6)
    preservation = {
        "save1_only_native_version_changed": target.save1 == bytes(expected_save1),
        "save2_all_bytes_identical": target.save2 == source.save2,
        "pc_storage_all_bytes_identical": target.storage == source.storage,
        "legacy_prefix_all_52_bytes_identical": target.extension[:52] == source.extension,
        "original_counter_rotation_and_bank_retained":
            (target.counter, target.rotation, target.index) == (source.counter, source.rotation, source.index),
        "alternate_bank_erased": target_results[1 - target.index].status == "empty",
        "special_sectors_identical": output[28 * SECTOR_SIZE:FLASH_SIZE] == flash[28 * SECTOR_SIZE:],
        "opaque_trailer_identical": output[FLASH_SIZE:] == trailer,
        "johto_uninitialized_and_reserve_zero": not any(target.extension[152:]),
    }
    if not all(preservation.values()):
        raise SaveValidationError("preservation", "copy conversion violated a protected domain")
    return output, {
        "fixture": ALLOWED_INPUTS[source_hash], "input_sha256": source_hash,
        "output_sha256": sha256(output), "bytes": len(output),
        "source_outcome": outcome, "source_bank_results": [result.status for result in results],
        "target_outcome": target_outcome, "target_bank": target.index,
        "counter": target.counter, "rotation": target.rotation,
        "preservation": preservation,
        "main_sha256": target.extension[84:116].hex(),
        "extension_crc32": f"{struct.unpack_from('<I', target.extension, 80)[0]:08x}",
        "native_gameplay_load": "NOT RUN",
        "occupied_pc_legacy_migration": "NOT RUN — approved fixtures have empty PC",
    }


def load_image(path: Path) -> bytes:
    return path.read_bytes()

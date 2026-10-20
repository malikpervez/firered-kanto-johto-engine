#!/usr/bin/env python3
"""Give the numbers in the Johto scripts their names back (one-time migration, after johto_to_source.py).

For each line with a numeric operand, the same line in the original HnS source (git BASE, by label and command) says
which constant it was: `setflag FLAG_VISITED_KANTO` there, `setflag 10495` here. The number is replaced by
<name> when the FireRed build gives it exactly that value (shared, not remapped), otherwise by JOHTO_<name> (the
Johto copy, see include/constants/johto_ids.h) when that has the value. Values are checked by
assembling the candidates with the build's own preprocessor and assembler, so a name is only used when the game
would assemble the same number. Numbers without such a name stay numbers.

The ROM must stay byte-identical; check before committing.
Usage (repository root): project/scripts/johto_name_operands.py BUILD_TREE [--base 2579f99b]
"""
import argparse
import collections
import json
import re
import struct
import subprocess
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
ENGINE = ROOT / "engine"
UNIT = ENGINE / "data/johto_campaign.s"
LABEL = re.compile(r"^([A-Za-z_]\w*)::?\s*$")
NUM = re.compile(r"^-?(?:0x[0-9A-Fa-f]+|\d+)$")
IDENT = re.compile(r"^[A-Za-z_]\w*$")
CMD = re.compile(r"^(\s+)([A-Za-z_][\w.]*)(\s+)(.*?)(\s*(?:@.*)?)$")


def split_args(s: str) -> list[str]:
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
            continue
        depth += ch == "("
        depth -= ch == ")"
        cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def blocks(text: str) -> dict[str, list[str]]:
    out, cur = {}, None
    for ln in text.split("\n"):
        m = LABEL.match(ln)
        if m:
            cur = m.group(1)
            out[cur] = []
        elif cur:
            out[cur].append(ln.split("@")[0].rstrip())
    return out


def commands(lines: list[str]) -> list[tuple[str, list[str]]]:
    out = []
    for ln in lines:
        m = CMD.match(ln) if ln.strip() else None
        if m and not m.group(2).startswith("."):
            out.append((m.group(2), split_args(m.group(4))))
        elif m:
            out.append((m.group(2), split_args(m.group(4))))
    return out


def values(build: Path, names: set[str]) -> dict[str, int]:
    """The value each name assembles to in the FireRed build's script context (names that are not constants are
    left out)."""
    es = (ENGINE / "data/event_scripts.s").read_text()
    header = es[:es.index('\t.include "constants/constants.inc"\n') + len('\t.include "constants/constants.inc"\n')]
    names = sorted(names)
    pp, cs = str(build / "tools/preproc/preproc"), str(build / "charmap.txt")
    while True:
        lines = header.split("\n") + ["\t.section .rodata", "Values:"]
        first = len(lines) + 1  # line number of the first name
        lines += [f"\t.4byte {n}" for n in names]
        with tempfile.TemporaryDirectory() as d:
            src, obj = Path(d) / "v.s", Path(d) / "v.o"
            src.write_text("\n".join(lines) + "\n")
            cmd = (f"{pp} -s {src} {cs} | arm-none-eabi-cpp -iquote include -Wno-trigraphs -DMODERN=1 -DTESTING=0 "
                   f"-DFIRERED -std=gnu17 -I include - | {pp} -ie {src} {cs} | arm-none-eabi-as -mcpu=arm7tdmi "
                   f"-march=armv4t -meabi=5 --defsym MODERN=1 --defsym FIRERED=1 -o {obj}")
            r = subprocess.run(cmd, shell=True, cwd=build, capture_output=True, text=True)
            bad_lines = {int(x) for x in re.findall(r"v\.s:(\d+): Error", r.stderr)}
            if r.returncode and bad_lines:
                # names the assembler cannot evaluate (C-only expressions): leave them out and try again
                drop = {names[n - first] for n in bad_lines if 0 <= n - first < len(names)}
                if not drop:
                    raise SystemExit("assembling the candidate names failed:\n" + r.stderr[-3000:])
                names = [n for n in names if n not in drop]
                continue
            if r.returncode:
                raise SystemExit("assembling the candidate names failed:\n" + r.stderr[-3000:])
            relocs = subprocess.run(["arm-none-eabi-objdump", "-r", "-j", ".rodata", str(obj)], capture_output=True,
                                    text=True).stdout
            bad = {int(m.group(1), 16) // 4 for m in re.finditer(r"^([0-9a-f]{8}) ", relocs, re.M)}
            raw = subprocess.run(["arm-none-eabi-objcopy", "-O", "binary", "-j", ".rodata", str(obj), "/dev/stdout"],
                                 capture_output=True).stdout
            break
    vals = struct.unpack(f"<{len(names)}i", raw[:4 * len(names)])
    return {n: v for i, (n, v) in enumerate(zip(names, vals)) if i not in bad}


def number(s: str) -> int:
    return int(s, 0)


# kinds of operand, in the order their names are preferred (the Johto copy first: these are Johto scripts)
FAMILY_PREFIXES = {"localid": "LOCALID_", "johto_flag": "JOHTO_FLAG_", "flag": "FLAG_", "johto_var": "JOHTO_VAR_", "var": "VAR_",
                   "johto_trainer": "TRAINER_JOHTO_", "trainer": "TRAINER_", "se": "SE_", "mus": "MUS_",
                   "species": "SPECIES_", "item": "ITEM_"}
PARAM_KINDS = {"flag": ["johto_flag", "flag"], "var": ["johto_var", "var"], "destination": ["johto_var", "var"],
               "source": ["johto_var", "var"], "trainer": ["johto_trainer", "trainer"], "species": ["species"],
               "item": ["item"]}
VAR_FIRST = re.compile(r"^(goto|call)_if_(eq|ne|lt|ge|le|gt)$|^(setvar|addvar|subvar|copyvar|specialvar|map_script_2)$")


def family_names() -> dict[str, list[str]]:
    text = "\n".join(p.read_text(errors="replace") for p in (ENGINE / "include/constants").glob("*.h"))
    names = set(re.findall(r"^#define\s+([A-Z_][A-Z0-9_]*)\b", text, re.M))
    opponents = "\n".join(p.read_text(errors="replace") for p in (ENGINE / "include/constants").glob("*.h")
                          if p.name.startswith("opponents") or p.name == "johto_trainers.h")
    trainers = set(re.findall(r"^#define\s+(TRAINER_[A-Z0-9_]*)\b", opponents, re.M))
    out = {}
    for fam, pre in FAMILY_PREFIXES.items():
        others = [p for p in FAMILY_PREFIXES.values() if p != pre and p.startswith(pre)]
        pool = trainers if "trainer" in fam else names
        out[fam] = sorted(n for n in pool if n.startswith(pre) and not any(n.startswith(o) for o in others)
                          and not n.endswith(("_START", "_END", "_COUNT", "_FIRST", "_LAST", "_BASE", "_MASK")))
    return out


def map_local_ids(build: Path) -> dict[str, list[str]]:
    """Map folder -> the LOCALID_ names mapjson generates for its object events (include/constants/map_event_ids.h
    of the build, one `// MAP_X` section per map)."""
    ids = {}
    for f in (ENGINE / "data/maps").glob("*/map.json"):
        ids[json.loads(f.read_text())["id"]] = f.parent.name
    out, cur = collections.defaultdict(list), None
    for ln in (build / "include/constants/map_event_ids.h").read_text().split("\n"):
        m = re.match(r"^// (MAP_\w+)", ln)
        if m:
            cur = ids.get(m.group(1))
        m = re.match(r"^#define (LOCALID_\w+)", ln)
        if m and cur:
            out[cur].append(m.group(1))
    return out


def macro_params() -> dict[str, list[str]]:
    out = {}
    for m in re.finditer(r"^\s*\.macro\s+(\w+)\s*(.*)$", (ENGINE / "asm/macros/event.inc").read_text(), re.M):
        out[m.group(1)] = [re.split(r"[:=]", p.strip())[0] for p in m.group(2).split(",") if p.strip()]
    return out


def kinds(cmd: str, k: int, params: dict[str, list[str]]) -> list[str]:
    if k == 0 and VAR_FIRST.match(cmd):
        return ["johto_var", "var"]
    if cmd == "copyvar" or cmd == "getplayerxy":
        return ["johto_var", "var"]
    if cmd in ("playse", "waitse"):
        return ["se"]
    if cmd in ("playbgm", "playfanfare", "savebgm", "fadenewbgm"):
        return ["mus"]
    p = params.get(cmd, [])
    if cmd == "waitmovement":
        return []  # `waitmovement 0` (the last applymovement) is how every script writes it
    if k < len(p) and p[k] in ("localId", "id") and cmd not in ("dynmultipush",):
        return ["localid_map", "localid", "johto_var", "var"]
    return PARAM_KINDS.get(p[k], []) if k < len(p) else []


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("build", type=Path)
    ap.add_argument("--base", default="2579f99b147c72b2e72e10c193752c8b53aae017")
    a = ap.parse_args()
    files = re.findall(r'^\t\.include "(data/[^"]+)"$', UNIT.read_text(), re.M)
    files = [f for f in files if f.startswith(("data/maps/", "data/scripts/johto/"))]

    # 1. align with the original HnS source and collect candidate names
    plans = []  # (file, line index, arg index, number, [candidate names])
    originals = {}
    for f in files:
        text = (ENGINE / f).read_text()
        src = re.match(r"@ Johto \(([^)]+)\)", text)
        if not src or src.group(1) == "generator":
            continue
        if src.group(1) not in originals:
            r = subprocess.run(["git", "show", f"{a.base}:engine/{src.group(1)}"], cwd=ROOT, capture_output=True)
            originals[src.group(1)] = blocks(r.stdout.decode(errors="replace")) if r.returncode == 0 else {}
        orig = originals[src.group(1)]
        lines = text.split("\n")
        cur = None
        used = collections.defaultdict(set)
        for i, ln in enumerate(lines):
            m = LABEL.match(ln)
            if m:
                cur = m.group(1)
                continue
            m = CMD.match(ln) if cur else None
            if not m or m.group(2).startswith("."):
                continue
            args = split_args(m.group(4))
            numeric = [k for k, x in enumerate(args) if NUM.match(x)]
            if not numeric:
                continue
            key = cur[2:] if cur.startswith("J_") and cur[2:] in orig else cur
            best, best_score = None, -1
            for j, (c, oargs) in enumerate(commands(orig.get(key, []))):
                if c != m.group(2) or len(oargs) != len(args) or j in used[key]:
                    continue
                score = sum(1 for x, y in zip(args, oargs) if x == y or x == "J_" + y)
                if score > best_score:
                    best, best_score = (j, oargs), score
            if best is None:
                continue
            used[key].add(best[0])
            for k in numeric:
                o = best[1][k]
                if IDENT.match(o):
                    # the shared FireRed name first; then the Johto copy (johto_ids.h, johto_trainers.h)
                    johto = f"TRAINER_JOHTO_{o[8:]}" if o.startswith("TRAINER_") else f"JOHTO_{o}"
                    plans.append((f, i, k, number(args[k]), [o, johto]))
                elif re.search(r"[A-Za-z_]", o) and not re.search(r"[\"']", o):
                    plans.append((f, i, k, number(args[k]), [o]))  # an expression, e.g. METATILE_X | MAPGRID_Y

    # 2. check the candidates' values in the FireRed build
    families = family_names()
    vals = values(a.build, {n for p in plans for n in p[4]} | {n for ns in families.values() for n in ns})

    # 3. names from the original source
    edits = collections.defaultdict(dict)
    named = 0
    for f, i, k, v, cands in plans:
        for n in cands:
            if vals.get(n) == v:
                edits[f].setdefault(i, {})[k] = n
                named += 1
                break

    # 4. lines the original source does not have (added by the generator, or not matched): name by the command's
    # parameter, only when exactly one name of that kind has the value
    by_value = {fam: collections.defaultdict(list) for fam in families}
    for fam, ns in families.items():
        for n in ns:
            if n in vals:
                by_value[fam][vals[n]].append(n)
    params = macro_params()
    # the name the original source uses most for a value, when several names share it
    usage = collections.Counter(n for e in edits.values() for d in e.values() for n in d.values())
    local_ids = map_local_ids(a.build)
    vals_local = values(a.build, {n for ns in local_ids.values() for n in ns})
    typed = 0
    for f in files:
        mf = re.match(r"data/maps/([^/]+)/scripts\.inc$", f)
        by_value["localid_map"] = collections.defaultdict(list)
        for n in local_ids.get(mf.group(1) if mf else "", []):
            if n in vals_local:
                by_value["localid_map"][vals_local[n]].append(n)
        for i, ln in enumerate((ENGINE / f).read_text().split("\n")):
            m = CMD.match(ln)
            if not m or m.group(2).startswith("."):
                continue
            for k, x in enumerate(split_args(m.group(4))):
                if not NUM.match(x) or k in edits[f].get(i, {}):
                    continue
                for fam in kinds(m.group(2), k, params):
                    hit = by_value[fam].get(number(x), [])
                    if len(hit) > 1:
                        top = sorted(hit, key=lambda n: -usage[n])
                        if usage[top[0]] > usage[top[1]]:
                            hit = top[:1]
                    if len(hit) == 1:
                        edits[f].setdefault(i, {})[k] = hit[0]
                        typed += 1
                        break
                    if hit:
                        break
    total = 0
    for f in files:
        lines = (ENGINE / f).read_text().split("\n")
        for i, ln in enumerate(lines):
            m = CMD.match(ln)
            if m and not m.group(2).startswith(".") and any(NUM.match(x) for x in split_args(m.group(4))):
                total += sum(1 for x in split_args(m.group(4)) if NUM.match(x))
            if i in edits.get(f, {}):
                args = split_args(m.group(4))
                for k, n in edits[f][i].items():
                    args[k] = n
                lines[i] = f"{m.group(1)}{m.group(2)}{m.group(3)}{', '.join(args)}{m.group(5)}"
        (ENGINE / f).write_text("\n".join(lines))
    print(f"{total} numeric operands: {named} named from the original source, {typed} by their parameter "
          f"({len(vals)} names checked)")


if __name__ == "__main__":
    main()

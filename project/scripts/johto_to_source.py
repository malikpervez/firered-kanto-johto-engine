#!/usr/bin/env python3
"""Turn the generated data/johto_campaign.s back into ordinary script source (one-time migration).

data/johto_campaign.s was written by prepare_johto_campaign.py from the pinned HnS sources: preprocessed, with the
HnS constants and macros inlined, texts encoded to bytes and every operand a number. Its generator inputs are not in
this repository, so it could only be edited by hand. This writes it back as source:

* each block goes back to the file its label came from: the Johto map's own data/maps/<Map>_hns/scripts.inc, or
  data/scripts/johto/<file>.inc for the Johto copies of shared scripts (labels with a J_ prefix) and for scripts of
  maps that are not in the game;
* the inlined HnS constants and macros are replaced by the FireRed build's own (as data/event_scripts.s includes);
* texts are .string lines again (any byte the charmap cannot name stays as {0xNN});
* numbers become names where the command's parameter says what they are (see NAMING), and only when exactly one
  name of that kind has the value.

The result must build a byte-identical ROM; check that before committing. Run from the repository root:
    project/scripts/johto_to_source.py BUILD_TREE
BUILD_TREE is a tree where `make firered` has run (for the generated constants and tools/preproc/preproc).
"""
import argparse
import collections
import json
import re
import subprocess
import tempfile
from pathlib import Path

ENGINE = Path(__file__).resolve().parents[2] / "engine"
CAMPAIGN = "data/johto_campaign.s"
BODY = ".section script_data"
SECTION = '.section script_data, "aw", %progbits'
MARK = re.compile(r"^\.ifdef (\w+) ; \.size \1, \. - \1 ; \.endif ; ?(?:\.global (\w+)|(\w+):)?\s*$")
LABEL_DEF = re.compile(r"^([A-Za-z_]\w*)::?", re.M)
HEADER_END = '\t.include "constants/constants.inc"\n'


def blocks_of(lines: list[str]) -> list[dict]:
    """Split the body into labelled blocks. A block starts at a marker line; `.global X` markers are followed by the
    `X:` line itself."""
    out, cur = [], None
    for ln in lines:
        m = MARK.match(ln)
        if m:
            if cur:
                out.append(cur)
            glob, local = m.group(2), m.group(3)
            cur = {"label": glob or local, "global": bool(glob), "lines": []}
            continue
        if cur is None:
            cur = {"label": None, "global": False, "lines": []}
        if cur["global"] and not cur["lines"] and ln == f"{cur['label']}:":
            continue
        cur["lines"].append(ln)
    if cur:
        out.append(cur)
    return out


# ---------------------------------------------------------------- where each block came from
def label_files(engine: Path) -> dict[str, set[str]]:
    where = collections.defaultdict(set)
    files = list(engine.glob("data/maps/*/scripts.inc")) + list(engine.glob("data/scripts/**/*.inc")) + \
        list(engine.glob("data/text/*.inc")) + [engine / "data/event_scripts.s"]
    for f in files:
        rel = str(f.relative_to(engine))
        if rel.startswith("data/scripts/johto/") or rel in ("data/scripts/hoenn_kept.inc", "data/scripts/hoenn_stubs.inc",
                                                            "data/scripts/frontier_stubs.inc"):
            continue
        for lab in LABEL_DEF.findall(f.read_text(errors="replace")):
            where[lab].add(rel)
    return where


def owners(blocks: list[dict], where: dict[str, set[str]]) -> list[str]:
    raw = []
    for b in blocks:
        lab = b["label"] or ""
        key = lab[2:] if lab.startswith("J_") and lab[2:] in where else lab
        raw.append(sorted(where.get(key, ())))
    own = [c[0] if len(c) == 1 else None for c in raw]
    for _ in range(3):  # ambiguous labels go with their neighbours, then with the HnS file
        for i, c in enumerate(raw):
            if len(c) > 1:
                near = [own[j] for j in (i - 1, i + 1) if 0 <= j < len(own) and own[j] in c]
                hns = [x for x in c if "_hns" in x]
                own[i] = near[0] if near else hns[0] if len(hns) == 1 else c[0]
    prev = None
    for i, o in enumerate(own):  # labels the generator added belong to the file around them
        own[i] = o or prev
        prev = own[i]
    return own


def destination(src: str, campaign_maps: set[str], used: collections.Counter) -> str:
    m = re.match(r"data/maps/([^/]+)/scripts\.inc$", src)
    if m and m.group(1) in campaign_maps:
        base = f"data/maps/{m.group(1)}/scripts"
    elif m:
        base = f"data/scripts/johto/{m.group(1)}"
    else:
        base = "data/scripts/johto/" + Path(src).stem
    used[base] += 1
    return f"{base}.inc" if used[base] == 1 else f"{base}_{used[base]}.inc"


# ---------------------------------------------------------------- texts
class Charmap:
    def __init__(self, path: Path):
        chars, named = {}, {}
        for ln in path.read_text().split("\n"):
            ln = ln.split("@")[0].strip()
            m = re.match(r"^'(\\.|[^'\\]|\\')'\s*=\s*([0-9A-F]{2}(?: [0-9A-F]{2})*)$", ln)
            if m:
                c = "'" if m.group(1) == "\\'" else m.group(1)
                chars.setdefault(bytes.fromhex(m.group(2)), []).append(c)
                continue
            m = re.match(r"^([A-Z_][A-Z_0-9]*)\s*=\s*([0-9A-F]{2}(?: [0-9A-F]{2})*)$", ln)
            if m:
                named.setdefault(bytes.fromhex(m.group(2)), []).append(m.group(1))
        self.single = {}
        for b, cs in chars.items():
            if len(b) == 1:
                ok = [c for c in cs if c not in ('{', '}', '"')]
                if ok:
                    self.single[b[0]] = min(ok, key=lambda c: (not (c.isascii() and c.isprintable()), cs.index(c)))
        # only real text codes: they start with a control byte ({PLAYER}, {COLOR ...}, button icons). Sound, music
        # and phoneme names (SE_/MUS_/PH_) only exist as arguments of play codes and must never stand for letters.
        codes = {}
        for b, ns in named.items():
            ok = [n for n in ns if not n.startswith(("SE_", "MUS_", "PH_"))]
            if len(b) > 1 and b[0] in (0xF8, 0xF9, 0xFC, 0xFD) and ok:
                codes[b] = ok[0]
        self.multi = sorted(codes.items(), key=lambda x: -len(x[0]))
        self.colors = {b[0]: n[0] for b, n in named.items() if len(b) == 1}

    def decode(self, data: bytes) -> str:
        out, i = [], 0
        while i < len(data):
            for b, name in self.multi:
                if data.startswith(b, i):
                    i += len(b)
                    if name in ("COLOR", "HIGHLIGHT", "SHADOW") and i < len(data) and data[i] in self.colors:
                        out.append("{%s %s}" % (name, self.colors[data[i]]))
                        i += 1
                    else:
                        out.append("{%s}" % name)
                    break
            else:
                c = data[i]
                if c == 0xFF:
                    out.append("$")
                elif c in self.single:
                    out.append(self.single[c])
                else:
                    out.append("{0x%02X}" % c)
                i += 1
        return "".join(out)


def byte_lines(lines: list[str]) -> list[bytes] | None:
    """The bytes of each `.byte` line, if the block is only `.byte` lines (plus blank ones)."""
    out = []
    for ln in lines:
        s = ln.strip()
        if not s:
            continue
        if not s.startswith(".byte "):
            return None
        try:
            out.append(bytes(int(x, 0) for x in s[6:].split(",")))
        except ValueError:
            return None
    return out or None


def encode_all(build: Path, texts: dict[int, list[str]]) -> dict[int, bytes]:
    """Encode the decoded texts with the build's own preproc, to check each one round-trips."""
    texts = dict(texts)
    while True:
        src, owner = [], {}
        for k, lines in texts.items():
            src.append(f"T{k}:")
            for t in lines:
                src.append(f'\t.string "{t}"')
                owner[len(src)] = k
        with tempfile.TemporaryDirectory() as d:
            p = Path(d) / "t.s"
            p.write_text("\n".join(src) + "\n")
            r = subprocess.run([str(build / "tools/preproc/preproc"), "-s", str(p), str(build / "charmap.txt")],
                               capture_output=True, text=True)
        m = re.search(r":(\d+): error", r.stderr)
        if r.returncode == 0 or not m:
            break
        del texts[owner[int(m.group(1))]]  # this one stays as bytes
    got, cur = {}, None
    for ln in r.stdout.split("\n"):
        m = re.match(r"^T(\d+):$", ln)
        if m:
            cur = int(m.group(1))
            got[cur] = b""
        elif cur is not None and ln.strip().startswith(".byte"):
            got[cur] += bytes(int(x, 0) for x in ln.strip()[6:].split(","))
    return got


# ---------------------------------------------------------------- main
def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("build", type=Path)
    ap.add_argument("--report", type=Path)
    a = ap.parse_args()
    text = (ENGINE / CAMPAIGN).read_text()
    if BODY not in text:
        raise SystemExit("data/johto_campaign.s is not the generated file (already converted?)")
    lines = text.split("\n")
    start = next(i for i, ln in enumerate(lines) if ln.strip().startswith(BODY))
    body = lines[start + 1:]
    while body and body[-1].strip() in ("", "#endif"):
        body.pop()
    blocks = blocks_of(body)
    if blocks and blocks[-1]["label"] is None:  # the closing `.size` marker line
        blocks.pop()

    # texts
    cm = Charmap(a.build / "charmap.txt")
    cand = {}
    for i, b in enumerate(blocks):
        bl = byte_lines(b["lines"])
        if bl and bl[-1].endswith(b"\xff"):
            cand[i] = (bl, [cm.decode(x) for x in bl])
    enc = encode_all(a.build, {i: t for i, (_, t) in cand.items()})
    n_text = n_raw = 0
    for i, (bl, t) in cand.items():
        if enc.get(i) == b"".join(bl):
            blocks[i]["lines"] = [f'\t.string "{x}"' for x in t] + [""]
            n_text += 1
        else:
            n_raw += 1

    # files
    where = label_files(ENGINE)
    own = owners(blocks, where)
    campaign_maps = set()
    for f in ENGINE.glob("data/maps/*/map.json"):
        d = json.loads(f.read_text())
        if isinstance(d.get("firered_campaign"), dict) and d.get("game_version") == "hns":
            campaign_maps.add(f.parent.name)
    runs = []
    for b, o in zip(blocks, own):
        if runs and runs[-1][0] == o:
            runs[-1][1].append(b)
        else:
            runs.append([o, [b]])
    used = collections.Counter()
    files = []
    for src, bl in runs:
        dest = destination(src or "data/event_scripts.s", campaign_maps, used)
        out = [f"@ Johto ({src or 'generator'}), as built into the FireRed game.", ""]
        for b in bl:
            if b["label"]:
                out.append(f"{b['label']}::" if b["global"] else f"{b['label']}:")
            body_lines = list(b["lines"])
            while body_lines and not body_lines[-1].strip():
                body_lines.pop()
            out += [("\t" + ln.strip()) if ln.strip() and not ln.startswith("\t") else ln for ln in body_lines]
            out.append("")
        files.append((dest, out))

    # write
    for f in (ENGINE / "data/scripts/johto").glob("*.inc") if (ENGINE / "data/scripts/johto").exists() else ():
        f.unlink()
    for dest, out in files:
        p = ENGINE / dest
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text("\n".join(out) + "\n")
    es = (ENGINE / "data/event_scripts.s").read_text()
    header = es[:es.index(HEADER_END) + len(HEADER_END)]
    unit = ["#ifdef FIRERED", "@ Johto scripts of the FireRed game. Same constants and macros as data/event_scripts.s;",
            "@ the files are listed in the order they are built.", header.rstrip("\n"), "", "\t" + SECTION, ""]
    unit += [f'\t.include "{dest}"' for dest, _ in files]
    unit += ["", "#endif", ""]
    (ENGINE / CAMPAIGN).write_text("\n".join(unit))
    print(f"{len(blocks)} blocks in {len(files)} files ({len(runs)} runs); {n_text} texts decoded, {n_raw} kept as bytes")
    if a.report:
        a.report.write_text(json.dumps({"files": [d for d, _ in files]}, indent=1))


if __name__ == "__main__":
    main()

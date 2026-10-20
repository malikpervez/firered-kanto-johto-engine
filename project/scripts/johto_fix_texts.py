#!/usr/bin/env python3
"""Re-decode the Johto texts written by an early johto_to_source.py (one-time repair).

Its decoder used sound and music names ({SE_M_REVERSAL}...) for ordinary letters, so most Johto texts were
unreadable in the source (the bytes, and so the game, were right). This turns every .string line of the Johto script
files into text again with the fixed decoder, and only keeps a new line when it encodes to exactly the same bytes.
Usage (repository root): project/scripts/johto_fix_texts.py BUILD_TREE
"""
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
import johto_to_source as j  # noqa: E402

STRING = re.compile(r'^(\s*\.string\s+")(.*)("\s*)$')


def main() -> None:
    build = Path(sys.argv[1])
    files = re.findall(r'^\t\.include "(data/[^"]+)"$', (j.ENGINE / j.CAMPAIGN).read_text(), re.M)
    lines = {}
    for f in files:
        for ln in (j.ENGINE / f).read_text().split("\n"):
            m = STRING.match(ln)
            if m:
                lines.setdefault(m.group(2), None)
    texts = list(lines)
    old = j.encode_all(build, {i: [t] for i, t in enumerate(texts)})
    cm = j.Charmap(build / "charmap.txt")
    new = {i: cm.decode(old[i]) for i in old}
    check = j.encode_all(build, {i: [s] for i, s in new.items()})
    fixed = {texts[i]: new[i] for i in new if check.get(i) == old[i] and new[i] != texts[i]}
    kept = sum(1 for i in old if check.get(i) != old[i])
    n = 0
    for f in files:
        p = j.ENGINE / f
        out = []
        for ln in p.read_text().split("\n"):
            m = STRING.match(ln)
            if m and m.group(2) in fixed:
                ln = m.group(1) + fixed[m.group(2)] + m.group(3)
                n += 1
            out.append(ln)
        p.write_text("\n".join(out))
    print(f"{len(texts)} different text lines; {len(fixed)} re-decoded ({n} lines in the files); "
          f"{kept} left as they were (would not re-encode the same)")


if __name__ == "__main__":
    main()

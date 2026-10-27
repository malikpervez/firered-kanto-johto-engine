#!/usr/bin/env python3
"""Find the waits a story check boulder step needs (story_check.pushes): where a wandering Pokémon is in the way.

Plays the plan from a checkpoint one move at a time and checks where the player stands; after a push, a probe step
into the block the boulder left proves it moved. A move that fails gets a wait before it, 15 frames longer each
try (a push that failed shows as the walk after it failing, so the wait goes before the push). A Pokémon that stays
put while you wait (shut in a corner by you and the boulder) is still there however long you wait, as the game plays
the same way each time: after 300 frames the search starts again with a longer wait before the first move, which
moves everything it does relative to you. The wandering Pokémon move the same way each time from the same
checkpoint, so the waits hold until a step before this one changes: then find them again.

Usage (from the repository root, pae installed):
  project/scripts/strength_waits.py CHECKPOINT X,Y "D! D L ..." [--state S]... [--var VAR=VALUE] [--pre INPUTS]
  X,Y: where the player stands when the plan starts (after --pre, inputs played first). Give the step's checkpoint
  before it (its walk's end) and the states its play has (the Repel, REPEL in story_check.py). --var checks the
  switch's variable at the end. Prints the waits, {move number: frames}, for the step's pushes(plan, waits).
  options: -p PROJECT (default engine), --waits '{k: f}' (start from these), --skip N (trust the first N moves)
"""
import argparse
import ast
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from story_check import pushes  # noqa: E402

D = {"U": (0, -1), "D": (0, 1), "L": (-1, 0), "R": (1, 0)}
KEY = {"U": "UP", "D": "DOWN", "L": "LEFT", "R": "RIGHT"}


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("checkpoint")
    ap.add_argument("start")
    ap.add_argument("plan")
    ap.add_argument("-p", "--project", default="engine")
    ap.add_argument("--state", action="append", default=[])
    ap.add_argument("--var")
    ap.add_argument("--pre", default="")
    ap.add_argument("--waits", default="{}")
    ap.add_argument("--skip", type=int, default=0)
    a = ap.parse_args()
    project = Path(a.project)
    shot = project / ".pae" / "story-check" / "strength-waits.png"
    shot.parent.mkdir(parents=True, exist_ok=True)
    plan, waits = a.plan.split(), ast.literal_eval(a.waits)

    def play(inputs, show=None):
        cmd = ["pae", "play", "-p", str(project), "--no-build", "--from", a.checkpoint, "--inputs",
               (a.pre + ", " if a.pre else "") + inputs + ", wait 30", "-o", str(shot)]
        for s in a.state:
            cmd += ["--state", s]
        cmd += ["--show-var", show] if show else []
        out = subprocess.run(cmd, capture_output=True, text=True).stdout
        m = re.search(r"'x': (\d+), 'y': (\d+)", out)
        v = re.search(r"var \S+ = (\d+)", out)
        return (int(m[1]), int(m[2])) if m else None, (int(v[1]) if v else None)

    pos, expect = tuple(int(v) for v in a.start.split(",")), []
    for mv in plan:
        if not mv.endswith("!"):
            pos = (pos[0] + D[mv[0]][0], pos[1] + D[mv[0]][1])
        expect.append(pos)
    k = a.skip
    while k < len(plan):
        inputs = pushes(" ".join(plan[:k + 1]), waits)
        if plan[k].endswith("!"):
            dx, dy = D[plan[k][0]]
            want = (expect[k][0] + dx, expect[k][1] + dy)
            got, _ = play(inputs + f", {KEY[plan[k][0]]}*12, wait 20")
        else:
            want = expect[k]
            got, _ = play(inputs)
        if got == want:
            print(f"ok   {k} {plan[k]} {got}", flush=True)
            k += 1
            continue
        j = k - 1 if (k and plan[k - 1] == plan[k][0] + "!" and not plan[k].endswith("!")) else k
        waits[j] = waits.get(j, 0) + 15
        if j and waits[j] > 300:
            waits = {0: waits.get(0, 0) + 30}
            if waits[0] > 3000:
                sys.exit(f"gave up at move {k}")
            print(f"miss {k} {plan[k]}: still in the way; start again, waiting {waits[0]} first", flush=True)
            k = 0
            continue
        if waits[j] > 3000:
            sys.exit(f"gave up at move {k}")
        print(f"miss {k} {plan[k]}: at {got}, not {want}; wait {waits[j]} before move {j}", flush=True)
        k = j
    if a.var:
        name, value = a.var.split("=")
        got, v = play(pushes(a.plan, waits) + ", wait 60", show=name)
        print(f"end  {got} {name} = {v}", "(right)" if v == int(value) else f"(wrong: want {value})")
    print(waits)


if __name__ == "__main__":
    main()

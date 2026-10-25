#!/usr/bin/env python3
"""The story sanity check (project/docs/story-sanity-check.md): plays the game from a new game through the maps
rebuilt so far, step by step, with pae, and checks where each step ends and the story state it leaves.

Each step starts from the checkpoint the step before it saved (`story-NN-name`, in <project>/.pae/checkpoints, never
committed). A run can resume at any step whose previous checkpoint is there; without it, run from the top (the
game is deterministic: the same inputs make the same checkpoints). Screenshots of every play go to
<project>/.pae/story-check/. Every play has a Repel on (VAR_REPEL_STEP_COUNT) so wild battles don't break the
walks; it doesn't change the story.

Usage (pae with --show-flag, from the repository root):
  project/scripts/story_check.py                 build, then every step
  project/scripts/story_check.py --list          the steps
  project/scripts/story_check.py --from dex      resume at step 'dex'
  project/scripts/story_check.py --to oak        stop after step 'oak'
  options: -p PROJECT (default engine), --no-build (use the ROM as built)
"""
import argparse
import ast
import subprocess
import sys
import time
from pathlib import Path

REPEL = "VAR_REPEL_STEP_COUNT=250"
DIRS = {"up": "UP", "down": "DOWN", "left": "LEFT", "right": "RIGHT"}


def hold(n):
    """Frames to hold a direction to walk n blocks: a step takes 16 frames and, once started, finishes when the key
    is let go, so letting go 12 frames into the last step walks exactly n blocks, whether or not the game drops a
    frame now and then or stands still for a few at a crossing. (Holding 16 * n + 2 only worked while every step took
    17 frames.) A walk that comes up short is planned again from where it stopped."""
    return 16 * (n - 1) + 12


def A(n, wait=60):
    return "".join(f"A*4, wait {wait}, " for _ in range(n))


def B(n, wait=90):
    return "".join(f"B*4, wait {wait}, " for _ in range(n))


# Each step: what it checks; where it starts (a new game's map/x/y/state, or the checkpoint of the step named in
# "after", by default the one before); "walk" to a block on the current map (planned with pae map path, re-planned
# if someone was in the way; "via" blocks on the way first, e.g. round a trainer's line of sight), then "inputs";
# extra "state" (e.g. a team); what it must end with.
STEPS = [
    dict(name="oak", what="A new game: out of the house; Oak stops you at the north exit and walks you to his lab",
         map="PalletTown_PlayersHouse_1F_Frlg", xy=(9, 8), state=["CLEAR_TEAM"],
         inputs="wait 20, DOWN*20, wait 120, DOWN*16, wait 8, RIGHT*96, wait 8, UP*112, wait 8, RIGHT*16, wait 8, "
                "UP*16, wait 400, " + A(6) + "wait 900, " + A(12) + "wait 200",
         expect=dict(map="PalletTown_ProfessorOaksLab_Frlg", xy=(6, 4),
                     vars={"VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB": 2})),
    dict(name="pikachu", what="Pikachu joins you; Blue takes his starter",
         inputs="wait 30, RIGHT*16, wait 20, RIGHT*4, wait 20, A*4, wait 120, A*4, wait 120, A*4, wait 150, "
                "A*4, wait 150, " + B(12, 100) + "wait 200",
         expect=dict(map="PalletTown_ProfessorOaksLab_Frlg", xy=(7, 4), flags={"FLAG_SYS_POKEMON_GET": True},
                     vars={"VAR_STARTER_MON": 0})),
    dict(name="lab-battle", what="Blue's first battle, with Oak's lessons (the tutorial battle); Blue leaves",
         inputs="wait 30, DOWN*72, wait 200, " + A(160) + "wait 600",
         expect=dict(map="PalletTown_ProfessorOaksLab_Frlg", xy=(7, 8), flags={"FLAG_BEAT_RIVAL_IN_OAKS_LAB": True},
                     vars={"VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB": 4})),
    dict(name="leave-lab", what="Out of the lab (the middle of its mat)", walk=(6, 12),
         inputs="wait 10, DOWN*30, wait 200", expect=dict(map="PalletTown_Frlg", xy=(21, 16))),
    dict(name="route1", what="The sign lady's trainer tips at the route entrance; Route 1's opening scene",
         walk=(15, 6), inputs="UP*64, wait 100, " + B(6) + "wait 60, UP*64, wait 200, " + B(4) + "wait 700, "
                              + B(5) + "wait 300",
         expect=dict(map="Route1_Frlg", xy=(25, 39),
                     flags={"FLAG_OPENED_START_MENU": True, "FLAG_RB_OPENING_SEEN": True},
                     vars={"VAR_MAP_SCENE_PALLET_TOWN_SIGN_LADY": 1})),
    dict(name="potion", what="Route 1's Mart clerk gives a Potion", walk=(23, 21),
         inputs="UP*4, wait 20, A*4, wait 80, " + B(8) + "wait 60",
         expect=dict(map="Route1_Frlg", xy=(23, 21), flags={"FLAG_GOT_POTION_ON_ROUTE_1": True})),
    dict(name="viridian", what="North into Viridian", walk=(23, 0), inputs="UP*12, wait 150",
         expect=dict(map="ViridianCity_Frlg", xy=(25, 51))),
    dict(name="parcel", what="Viridian's Poke Mart: the clerk gives Oak's Parcel", walk=(31, 28),
         inputs="UP*20, wait 250, " + B(10) + "wait 200",
         expect=dict(map="ViridianCity_Mart_Frlg", xy=(4, 3),
                     vars={"VAR_MAP_SCENE_VIRIDIAN_CITY_MART": 1, "VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB": 5})),
    dict(name="leave-mart", what="Out of the Mart", inputs="wait 30, DOWN*80, wait 30, DOWN*20, wait 200",
         expect=dict(map="ViridianCity_Frlg", xy=(31, 28))),
    dict(name="south-route1", what="South into Route 1", walk=(25, 51), inputs="DOWN*12, wait 150",
         expect=dict(map="Route1_Frlg", xy=(23, 0))),
    dict(name="south-pallet", what="Down Route 1 (over its ledges) into Pallet", walk=(25, 39),
         inputs="DOWN*12, wait 150", expect=dict(map="PalletTown_Frlg")),  # a block or two in: the walk carries on
    dict(name="into-lab", what="Into Oak's lab", walk=(21, 16), inputs="UP*20, wait 250",
         expect=dict(map="PalletTown_ProfessorOaksLab_Frlg", xy=(6, 12))),
    dict(name="dex", what="The parcel to Oak: the Pokedex; Blue leaves", walk=(6, 4),
         inputs="UP*4, wait 20, A*4, wait 90, " + B(55) + "wait 600",
         expect=dict(map="PalletTown_ProfessorOaksLab_Frlg", xy=(6, 4), flags={"FLAG_SYS_POKEDEX_GET": True},
                     vars={"VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB": 6, "VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN": 1,
                           "VAR_MAP_SCENE_ROUTE22": 1, "VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE": 1,
                           "VAR_MAP_SCENE_VIRIDIAN_CITY_MART": 2})),
    dict(name="leave-lab-2", what="Out of the lab", walk=(6, 12), inputs="wait 10, DOWN*30, wait 200",
         expect=dict(map="PalletTown_Frlg", xy=(21, 16))),
    dict(name="rivals-house", what="Into Blue's house", walk=(18, 8), inputs="UP*20, wait 250",
         expect=dict(map="PalletTown_RivalsHouse_Frlg", xy=(4, 8))),
    dict(name="town-map", what="Daisy gives the Town Map",
         inputs="wait 30, UP*60, wait 30, RIGHT*4, wait 20, A*4, wait 90, " + B(12) + "wait 200",
         expect=dict(map="PalletTown_RivalsHouse_Frlg", xy=(4, 4), vars={"VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE": 2})),
    dict(name="leave-rivals-house", what="Out of Blue's house", inputs="wait 30, DOWN*66, wait 20, DOWN*20, wait 200",
         expect=dict(map="PalletTown_Frlg", xy=(18, 8))),
    dict(name="north-route1", what="North into Route 1", walk=(15, 0), inputs="UP*12, wait 150",
         expect=dict(map="Route1_Frlg", xy=(25, 39))),
    dict(name="north-viridian", what="Up Route 1 into Viridian", walk=(23, 0), inputs="UP*12, wait 150",
         expect=dict(map="ViridianCity_Frlg", xy=(25, 51))),
    dict(name="old-man", what="The old man's catching demonstration (the second tutorial battle)",
         walk=(25, 16), inputs="wait 20, UP*16, wait 8, UP*16, wait 8, UP*16, wait 200, " + B(60) + "wait 600",
         expect=dict(map="ViridianCity_Frlg", xy=(25, 13), vars={"VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN": 2})),
    dict(name="route2", what="The road north is open: into Route 2", walk=(25, 0), inputs="UP*12, wait 200",
         expect=dict(map="Route2_Frlg", xy=(9, 79))),
    dict(name="back-viridian", what="Back into Viridian", inputs="wait 30, DOWN*28, wait 200",
         expect=dict(map="ViridianCity_Frlg", xy=(25, 0))),
    dict(name="center", what="Into Viridian's Pokemon Center", walk=(20, 28), inputs="UP*20, wait 250",
         expect=dict(map="ViridianCity_PokemonCenter_1F_Frlg", xy=(7, 8))),
    dict(name="heal", what="The nurse heals the team (the Center becomes where you wake after a blackout)",
         inputs="wait 30, UP*50, wait 20, UP*4, wait 20, A*4, wait 100, A*4, wait 100, A*4, wait 400, " + B(6)
                + "wait 100",
         expect=dict(map="ViridianCity_PokemonCenter_1F_Frlg", xy=(7, 4))),
    dict(name="leave-center", what="Out of the Center", inputs="wait 30, DOWN*66, wait 20, DOWN*20, wait 250",
         expect=dict(map="ViridianCity_Frlg", xy=(20, 28))),
    dict(name="route22", what="West into Route 22", walk=(0, 29), inputs="LEFT*12, wait 200",
         expect=dict(map="Route22_Frlg", xy=(51, 7))),
    dict(name="blue-lose", what="Blue meets you on the road and wins: you wake in Viridian's Center",
         inputs="wait 30, path 51,7 40,7, wait 300, " + A(120) + "wait 600",
         expect=dict(map="ViridianCity_PokemonCenter_1F_Frlg", xy=(7, 4), vars={"VAR_MAP_SCENE_ROUTE22": 1})),
    dict(name="blue-win", what="The same with a stronger Pikachu: Blue loses and leaves east", after="route22",
         state=["CLEAR_TEAM", "SPECIES_PIKACHU lv40 MOVE_THUNDERBOLT"],
         inputs="wait 30, path 51,7 40,7, wait 300, " + A(60) + "wait 600",
         expect=dict(map="Route22_Frlg", xy=(44, 7), vars={"VAR_MAP_SCENE_ROUTE22": 2})),
    dict(name="league-gate", what="Up the stairs in the cliff, across the forecourt, into the League Front Gate",
         walk=(16, 18), inputs="wait 20, UP*72, wait 10, LEFT*60, wait 8, UP*16, wait 8, UP*16, wait 300, " + B(6)
                               + "wait 100",
         expect=dict(map="Route22_NorthEntrance_Frlg", xy=(7, 10))),
    dict(name="leave-league-gate", what="Back out of the League Front Gate", inputs="wait 30, DOWN*20, wait 250",
         expect=dict(map="Route22_Frlg", xy=(12, 14))),
    dict(name="east-viridian", what="Down the stairs and east along the road into Viridian", walk=(51, 7),
         inputs="RIGHT*12, wait 200", expect=dict(map="ViridianCity_Frlg", xy=(0, 29))),
    dict(name="north-route2", what="North out of Viridian into Route 2", walk=(25, 0), inputs="UP*12, wait 200",
         expect=dict(map="Route2_Frlg", xy=(9, 79))),
    dict(name="forest-gate", what="Up Route 2's south meadow into Viridian Forest's south gate (its double door)",
         walk=(8, 52), inputs="UP*20, wait 300", expect=dict(map="Route2_ViridianForest_SouthEntrance_Frlg",
                                                             xy=(7, 9))),
    dict(name="forest", what="Through the gatehouse into Viridian Forest", walk=(7, 2), inputs="UP*20, wait 300",
         expect=dict(map="ViridianForest_Frlg", xy=(39, 72))),
    dict(name="forest-stairs", what="Up the forest, round its trainers' lines of sight, and west down its sideways "
                                    "stairs (they move you diagonally: off the planned walk)",
         via=[(39, 60), (41, 60), (41, 59), (46, 59), (46, 46), (48, 46), (48, 44), (47, 44), (47, 30), (48, 30),
              (48, 24), (47, 24), (47, 15)],
         walk=(39, 15), inputs="LEFT*16, wait 8, LEFT*16, wait 40", expect=dict(map="ViridianForest_Frlg",
                                                                                 xy=(37, 16))),
    dict(name="forest-north", what="On through the forest, round Sammy's line of sight, to its north gate",
         via=[(30, 16), (30, 23), (28, 23), (28, 25), (21, 25), (21, 23), (18, 23), (18, 14), (17, 14), (17, 11),
              (16, 11)],
         walk=(15, 10), inputs="UP*20, wait 300", expect=dict(map="Route2_ViridianForest_NorthEntrance_Frlg",
                                                              xy=(7, 9))),
    dict(name="route2-north", what="Out of the forest's north gate onto Route 2 (its doorway, walking north)",
         walk=(7, 2), inputs="UP*20, wait 300", expect=dict(map="Route2_Frlg", xy=(7, 20))),
    dict(name="pewter", what="Up Route 2's north meadow into Pewter City", walk=(9, 0), inputs="UP*12, wait 200",
         expect=dict(map="PewterCity_Frlg", xy=(23, 43))),
]


class Runner:
    def __init__(self, project: Path):
        self.project = project
        self.out = project / ".pae" / "story-check"
        self.out.mkdir(parents=True, exist_ok=True)

    def pae(self, *args):
        r = subprocess.run(["pae", *args, "-p", str(self.project)], capture_output=True, text=True)
        return r.returncode, r.stdout + r.stderr

    def path(self, map_, a, b):
        """pae map path's walk as inputs: each straight run held for its steps (see hold())."""
        code, out = self.pae("map", "path", map_, f"{a[0]},{a[1]}", f"{b[0]},{b[1]}")
        steps = [line.split("_")[1] for line in out.splitlines() if line.startswith("walk_")]
        if code or (not steps and tuple(a) != tuple(b)):
            raise RuntimeError(f"no walk on {map_} from {a} to {b}: {out.strip().splitlines()[-1]}")
        runs = []
        for s in steps:
            if runs and runs[-1][0] == s:
                runs[-1][1] += 1
            else:
                runs.append([s, 1])
        return ", ".join(f"{DIRS[d]}*{hold(n)}, wait 6" for d, n in runs)

    def inputs(self, text, map_):
        """'path X,Y X,Y' in a step's inputs becomes the planned walk on ``map_``."""
        parts = []
        for part in text.split(", "):
            if part.startswith("path "):
                a, b = (tuple(int(v) for v in p.split(",")) for p in part.split()[1:])
                part = self.path(map_, a, b)
            parts.append(part)
        return ", ".join(parts)

    def play(self, shot, cp=None, map_=None, xy=None, state=(), inputs="wait 5", save=None, flags=(), vars_=()):
        args = ["play"] + ([map_] if map_ else []) + (["--from", cp] if cp else [])
        if xy:
            args += ["--x", str(xy[0]), "--y", str(xy[1])]
        for s in [REPEL, *state]:
            args += ["--state", s]
        for f in flags:
            args += ["--show-flag", f]
        for v in vars_:
            args += ["--show-var", v]
        args += ["--no-build", "--inputs", inputs, "-o", str(self.out / f"{shot}.png")]
        args += ["--save-as", save] if save else []
        code, out = self.pae(*args)
        line = next((ln for ln in out.splitlines() if ln.startswith("wrote ") and "({" in ln), None)
        if code or line is None:
            raise RuntimeError(out.strip().splitlines()[-1] if out.strip() else f"pae exit {code}")
        d = ast.literal_eval(line[line.index("({") + 1:-1])
        got = {"map": d["map"], "xy": (d["x"], d["y"])}
        for ln in out.splitlines():
            if ln.startswith(("flag ", "var ")):
                kind, name, _, value = ln.split(" ", 3)
                got[name] = value == "True" if kind == "flag" else int(value)
        return got

    def walk(self, shot, cp, save, target, state, tries=6):
        """From ``cp`` to ``target`` on its map, re-planned from wherever the player stopped (people walk about:
        each try waits a little longer first). Stops early if the walk crossed onto another map."""
        here = self.play(f"{shot}-at", cp=cp)
        start_map, cur = here["map"], cp
        for k in range(tries + 1):
            if here["map"] != start_map or here["xy"] == tuple(target):
                return here, cur
            if k == tries:
                raise RuntimeError(f"couldn't walk to {target}: stuck at {here['map']} {here['xy']}")
            walk = self.path(here["map"], here["xy"], target)
            here = self.play(f"{shot}-walk{k}", cp=cur, inputs=f"wait {20 + 70 * k}, {walk}, wait 20", save=save,
                             state=state)
            cur = save

    def run_step(self, i, step, prev_cp):
        cp = f"story-{i:02d}-{step['name']}"
        state = step.get("state", [])
        if "map" in step:  # a new game
            here = self.play(cp, map_=step["map"], xy=step["xy"], state=state,
                             inputs=self.inputs(step["inputs"], step["map"]), save=cp)
        else:
            if "walk" in step:
                src = prev_cp
                for j, via in enumerate(step.get("via", [])):
                    _, src = self.walk(f"{cp}-via{j}", src, cp, via, state)
                here, src = self.walk(cp, src, cp, step["walk"], state)
            else:
                here, src = self.play(f"{cp}-from", cp=prev_cp), prev_cp
            self.play(cp, cp=src, state=state, inputs=self.inputs(step["inputs"], here["map"]), save=cp)
        e = step["expect"]
        got = self.play(f"{cp}-check", cp=cp, flags=list(e.get("flags", {})), vars_=list(e.get("vars", {})))
        want = {"map": e["map"], **({"xy": tuple(e["xy"])} if "xy" in e else {}), **e.get("flags", {}),
                **e.get("vars", {})}
        wrong = {k: (got.get(k), v) for k, v in want.items() if got.get(k) != v}
        return cp, got, wrong


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("-p", "--project", default="engine")
    ap.add_argument("--from", dest="start", help="resume at this step (needs the step before it's checkpoint)")
    ap.add_argument("--to", dest="stop", help="stop after this step")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--no-build", action="store_true")
    a = ap.parse_args()
    names = [s["name"] for s in STEPS]
    if a.list:
        for i, s in enumerate(STEPS, 1):
            print(f"{i:2d} {s['name']:<20} {s['what']}")
        return 0
    for n in (a.start, a.stop):
        if n and n not in names:
            sys.exit(f"no step '{n}' (see --list)")
    project = Path(a.project).resolve()
    run = Runner(project)
    if not a.no_build:
        r = subprocess.run(["make", "-j4"], cwd=project, capture_output=True, text=True)
        if r.returncode:
            sys.exit("make failed:\n" + "\n".join(r.stdout.splitlines()[-20:] + r.stderr.splitlines()[-20:]))
    first = names.index(a.start) if a.start else 0
    last = names.index(a.stop) if a.stop else len(STEPS) - 1
    cps = {}  # step name -> its checkpoint
    for i, s in enumerate(STEPS[:first], 1):
        cps[s["name"]] = f"story-{i:02d}-{s['name']}"
    failed, t0 = False, time.monotonic()
    for i in range(first, last + 1):
        step = STEPS[i]
        before = step.get("after") or (STEPS[i - 1]["name"] if i else None)
        prev = cps.get(before)
        if before and prev is None or (prev and not (project / ".pae" / "checkpoints" / f"{prev}.sav").exists()):
            sys.exit(f"step '{step['name']}' starts from '{before}', which has no checkpoint: run from an earlier step")
        try:
            cp, got, wrong = run.run_step(i + 1, step, prev)
        except RuntimeError as e:
            print(f"FAIL {i + 1:2d} {step['name']}: {e}", flush=True)
            failed = True
            break
        cps[step["name"]] = cp
        shown = ", ".join(f"{k}={v}" for k, v in got.items() if k not in ("map", "xy"))
        if wrong:
            problems = ", ".join(f"{k} is {g}, not {w}" for k, (g, w) in wrong.items())
            print(f"FAIL {i + 1:2d} {step['name']}: {problems}", flush=True)
            failed = True
            break
        print(f"ok   {i + 1:2d} {step['name']:<20} {got['map']} {got['xy']}  {shown}".rstrip(), flush=True)
    print(f"{time.monotonic() - t0:.0f} s; screenshots: {run.out}")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())

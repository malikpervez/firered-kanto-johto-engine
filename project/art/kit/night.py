"""Every kit map at night (KR-102): the colours that glow after dark, the tiles drawn with a lit copy of their
palette, and the glows round lamps and lanterns. One table for all of them, so a new building or lamp is lit where
its map is listed here (AGENTS.md, "Night").

The game darkens towns, cities and routes after dark and lights the colours a palette's .pla lists: they go halfway
to the game's warm light (or the bank's own, kept in its colour 0) instead. A colour can glow only if nothing else
in its bank uses it (`pae map colours MAP --bank B -o PNG` shows where each is). The kit's (kit.py LIGHTS: the
Center's and Mart's glass and the MART letters, the street lamp's glass) glow on every map; a map's own buildings
are listed below, from the survey of every map in November 2026: window and door glass (most of the packs' houses
keep theirs in 14 and 15), lit signs and lanterns, Cinnabar's lava. Left dark on purpose: the burned Pokémon Mansion
and the derelict Power Plant.

Where glass shares its colours with a roof (Pallet's houses: the blue house's roof is the glass's blue), the glass's
tiles are drawn with a copy of the palette in a free bank (`pae map rebank`, after the build), and only the copy
glows: by day nothing changes.

Each map's build.sh runs it twice:
  python3 project/art/kit/night.py spec project/art/<map>-concept     after make_art.py: the spec's "lights"
  python3 ../project/art/kit/night.py map ../project/art/<map>-concept MAP     (in engine/) after its events: the
                                                                      copies' tiles, then the glows
"""
import json
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import kit  # noqa: E402

LAMP = (8, 14)  # the kit street lamp's glass (bank 8, the plants): a glow on every block that shows it


def _rect(x0: int, y0: int, x1: int, y1: int) -> list[tuple[int, int]]:
    return [(x, y) for y in range(y0, y1 + 1) for x in range(x0, x1 + 1)]


# by art folder: "lights" bank -> colours (or {"colours", "light"}); "copies" bank -> the bank whose palette it
# copies (the spec writes it from the same file); "rebank" the tiles moved onto a copy (pae map rebank: from, to,
# the blocks that show a colour or the blocks listed, only tiles showing these colours); "twins" bank -> {free
# colour: the colour it copies} and "recolour" the blocks whose pixels of a colour go onto its unlit twin (pae map
# recolour: a glass roof in the windows' glass colour); "glows" lanterns and wall lamps (x, y), besides the street
# lamps, which are found by their glass
MAPS = {
    "pallet-concept": {
        "lights": {7: [9, 10, 11],  # Oak's lab: its windows, glass door and the greenhouse
                   9: [13],  # the houses' glints on glass (their door blocks keep theirs here)
                   10: [14, 15],  # the windmill's window
                   11: [10, 12, 13]},  # the houses' window glass, on the copy of their palette
        "copies": {11: 9},
        "rebank": [{"from": 9, "to": 11, "on": (9, 13), "colours": [10, 12, 13], "except": [11]}]},  # 11: roof
    "viridian-concept": {"lights": {7: [14, 15], 9: [14, 15]}},
    "pewter-concept": {"lights": {7: [15], 10: [14, 15], 11: [14, 15], 12: [14, 15]}},
    "cerulean-concept": {"lights": {7: [14, 15], 9: [14, 15], 11: [14, 15], 12: [14, 15]}},
    "vermilion-concept": {"lights": {7: [14, 15], 9: [14, 15]}},
    "celadon-concept": {"lights": {7: [14, 15],
                                   9: [7, 8, 14]},  # the city's window and door glass, the marquee bulbs
                        # Erika's glasshouse roof is in the same glass colours: its blocks on a copy, unlit
                        "copies": {11: 9},
                        "rebank": [{"from": 9, "to": 11, "colours": [7, 8], "blocks": _rect(8, 30, 16, 32)}],
                        "glows": [(34, 18), (36, 18)]},  # the Hotel's door lanterns
    "saffron-concept": {"lights": {7: [14, 15],
                                   9: [7],  # Silph Co.'s, the Gym's and the gates' window glass (its dark pane)
                                   10: [7, 8], 11: [7, 8]},  # the offices' windows
                        # the station's and the arcades' glass roofs are in the windows' glass colours and the
                        # city has no bank to spare: their dark glass goes onto colour 13, the same blue, unlit
                        # (13 is the bank's one free colour, so the pale glass, 8, stays unlit everywhere)
                        "twins": {9: {13: 7}},
                        "recolour": [{"bank": 9, "colour": 7, "to": 13,
                                      "blocks": _rect(46, 14, 57, 15) + _rect(23, 27, 26, 28) + _rect(41, 27, 44, 28)
                                      + _rect(46, 27, 49, 28) + _rect(13, 34, 16, 35) + _rect(18, 34, 21, 35)
                                      + _rect(28, 45, 31, 45)}],
                        "glows": [(16, 17), (18, 17)]},  # the Gym's door lamps
    "fuchsia-concept": {"lights": {7: [14, 15], 9: [7, 8]},
                        "glows": [(22, 6), (24, 6), (4, 31), (6, 31), (38, 30)]},  # lodge, Gym, pond house lanterns
    "cinnabar-concept": {"lights": {7: [6, 15],  # Blaine's Gym's windows
                                    10: [9, 10, 11],  # the Lab's glass and its greenhouse
                                    11: {"colours": [8, 9, 10], "light": [248, 112, 40]}},  # the lava, the vents
                         "glows": [(19, 4), (21, 4)]},  # the Gym's entrance lamps
    "indigo-concept": {"lights": {7: [8]}, "glows": [(10, 11), (12, 11)]},  # the League's door glass, its lamps
    "lavender-concept": {},  # its own make_art.py LIGHTS and GLOWS (glows.txt)
    "route2-concept": {"lights": {7: [14], 9: [14, 15]}},
    "route5-concept": {"lights": {7: [14], 9: [14, 15]}},
    "route6-concept": {"lights": {7: [14], 9: [14, 15]}},
    "route7-concept": {"lights": {7: [14], 9: [14, 15]}},
    "route8-concept": {"lights": {7: [14], 9: [14, 15]}},
    "route11-concept": {"lights": {9: [14]}},
    "route12-concept": {"lights": {7: [7, 8], 9: [14, 15]}},
    "route15-concept": {"lights": {7: [8]}},
    "route16-concept": {"lights": {7: [14, 15], 9: [8]}},
    "route18-concept": {"lights": {7: [8]}},
    "route22-concept": {"lights": {7: [6, 15]}},
    "route23-concept": {"lights": {9: [7, 8]}},
    "route25-concept": {"lights": {9: [14, 15]}},
}


def spec(folder: Path) -> None:
    """The map's spec.json gets its "lights" (the kit's, its own make_art.py's, this table's) and its copies."""
    folder = Path(folder)
    entry = MAPS.get(folder.name, {})
    path = folder / "spec.json"
    sp = json.loads(path.read_text())
    lights = {str(b): cols for b, cols in kit.LIGHTS.items()}
    lights.update(sp.get("lights", {}))
    lights.update({str(b): cols for b, cols in entry.get("lights", {}).items()})
    npp = 7  # HnS layouts: banks 0-6 the primary's, 7-12 the secondary's
    sec = sp["palettes"]["secondary"]
    for bank, src in entry.get("copies", {}).items():
        while len(sec) <= bank - npp:
            sec.append(sec[src - npp])
        sec[bank - npp] = sec[src - npp]
    for bank, twins in entry.get("twins", {}).items():  # into the bank's own palette file, which make_art writes
        f = folder / sec[bank - npp]
        cols = _read_jasc(f)
        for free, src in twins.items():
            cols[free] = cols[src]
        kit.write_palette(f, cols)
    sp["lights"] = lights
    path.write_text(json.dumps(sp, indent=1) + "\n")


def _read_jasc(path: Path) -> list[tuple[int, int, int]]:
    rows = path.read_text().split()[3:]
    return [tuple(int(v) for v in rows[i:i + 3]) for i in range(0, len(rows), 3)]


def glows(folder: Path, name: str, pae_args: list[str]) -> list[str]:
    """The pae map lights command for the map: its street lamps (by their glass), its lanterns, make_art's
    glows.txt."""
    folder = Path(folder)
    entry = MAPS.get(folder.name, {})
    spots = [f"{x},{y}" for x, y in entry.get("glows", [])]
    f = folder / "glows.txt"
    if f.exists():
        spots += f.read_text().split()
    return ["pae", "map", "lights", name, *spots, "--on", f"{LAMP[0]}:{LAMP[1]}", *pae_args]


def on_map(folder: Path, name: str, pae_args: list[str]) -> None:
    """After the map's build (in engine/): the copies' tiles, then the glows."""
    folder = Path(folder)
    for r in MAPS.get(folder.name, {}).get("rebank", []):
        cmd = ["pae", "map", "rebank", name, *[f"{x},{y}" for x, y in r.get("blocks", [])],
               "--from", str(r["from"]), "--to", str(r["to"]), "--colours", ",".join(map(str, r["colours"])),
               "--except-colours", ",".join(map(str, r.get("except", []))), *pae_args]
        if "on" in r:
            cmd[4:4] = ["--on", f"{r['on'][0]}:{r['on'][1]}"]
        subprocess.run(cmd, check=True)
    for r in MAPS.get(folder.name, {}).get("recolour", []):
        subprocess.run(["pae", "map", "recolour", name, *[f"{x},{y}" for x, y in r["blocks"]], "--bank",
                        str(r["bank"]), "--colour", str(r["colour"]), "--to", str(r["to"]), *pae_args], check=True)
    subprocess.run(glows(folder, name, pae_args), check=True)


if __name__ == "__main__":
    if len(sys.argv) >= 3 and sys.argv[1] == "spec":
        spec(Path(sys.argv[2]))
    elif len(sys.argv) >= 4 and sys.argv[1] == "map":
        on_map(Path(sys.argv[2]), sys.argv[3], sys.argv[4:] or ["-p", "."])
    else:
        sys.exit(__doc__)

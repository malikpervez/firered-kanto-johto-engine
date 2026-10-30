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
TEAM = "SPECIES_ALAKAZAM lv100 MOVE_PSYCHIC MOVE_SURF MOVE_CUT MOVE_STRENGTH"
FRESH = ["CLEAR_TEAM", TEAM]  # the same team again, healed and its moves' PP back, before a battle
DIRS = {"up": "UP", "down": "DOWN", "left": "LEFT", "right": "RIGHT"}


def hold(n):
    """Frames to hold a direction to walk n blocks: a step takes 16 frames and, once started, finishes when the key
    is let go, so letting go 12 frames into the last step walks exactly n blocks, whether or not the game drops a
    frame now and then or stands still for a few at a crossing. (Holding 16 * n + 2 only worked while every step took
    17 frames.) A walk that comes up short is planned again from where it stopped."""
    return 16 * (n - 1) + 12


def surf_hold(n):
    """The same for surfing, facing the way already: 8 frames a block, each starting as the last ends. (Facing
    another way, a press first turns you, for 8 frames; a walk that starts so comes up a block short and is planned
    again from there.)"""
    return 8 * n - 4


def bike_hold(n):
    """The same on the Bicycle: 6 frames a block, the first press already moving you whichever way you faced."""
    return 6 * n - 2


def A(n, wait=60):
    return "".join(f"A*4, wait {wait}, " for _ in range(n))


def B(n, wait=90):
    return "".join(f"B*4, wait {wait}, " for _ in range(n))


def pushes(plan, waits=None):
    """A Strength boulder plan as inputs: moves like "D! D L", one block each, "!" a push. A push moves only the
    boulder: you stay where you are. Before the first push: face the boulder and use Strength (on until the map
    loads again). ``waits`` {move number: frames} waits first for a wandering mon to get out of the way (its spot
    stays the same each run from the same checkpoint)."""
    out, first = [], True
    for k, mv in enumerate(plan.split()):
        dn = {"U": "UP", "D": "DOWN", "L": "LEFT", "R": "RIGHT"}[mv[0]]
        w = (waits or {}).get(k)
        pre = f"wait {w}, " if w else ""
        if mv.endswith("!") and first:
            pre += f"wait 20, {dn}*2, wait 20, " + A(5) + B(4)
            first = False
        out.append(f"{pre}{dn}*12, wait {40 if mv.endswith('!') else 6}")
    return ", ".join(out)


# Victory Road's Strength boulders, planned (each push moves the boulder a block; you stay put), with the waits a
# wandering mon made needed: {move number: frames}
VR1F = ("D! D L D R! R R! R R! R R! R R! D R R U! U U! U L U R! R R! R R! R R! R R! R R! R R! D R R U! U U! L L U U R R! "
        "U R R D!", {0: 1065})
VR2F = ("R D D D D R D D R R R D! D R D L! L L! U L L D! D R D L! L L!", {})
VR2F_2 = (" ".join(["L!", "L"] * 18 + ["L!"]), {0: 60, 22: 105, 24: 195})
VR3F = ("L U U U U L U! U U! U R U L! L L! L L! L L! L L! L L! L L! L L! L L! L L! L L! L L! L L! L L! L L! "
        "L L! L L! L L! L L! L L! L L! U L L D! D R D L! L L! L L! L L! L L! L U L D! D D! D D! D L D R!", {34: 75, 36: 45, 38: 75})


def quiz(yes):
    """Blaine's quiz machines, faced from below: the rules (five pages), the question, the answer (A for yes, B for
    no), then "correct" (two pages)."""
    return "UP*4, wait 20, A*4, wait 60, " + B(5, 120) + f"wait 120, {'A' if yes else 'B'}*4, wait 400, " + B(2, 120)


# Each step: what it checks; where it starts (a new game's map/x/y/state, or the checkpoint of the step named in
# "after", by default the one before); "walk" to a block on the current map (planned with pae map path, re-planned
# if someone was in the way; "via" blocks on the way first, e.g. round a trainer's line of sight; on water with
# "surf", riding with "bike"), then "inputs";
# extra "state" (e.g. a team; "repel": False for none at all, not even the Repel: setting state loads the map
# again, which gets you off the Bicycle); what it must end with.
STEPS = [
    dict(name="oak", what="A new game: out of the house; Oak stops you at the north exit and walks you to his lab "
         "(up beside the road, then onto it below the fingerpost)",
         map="PalletTown_PlayersHouse_1F_Frlg", xy=(9, 8), state=["CLEAR_TEAM"],
         inputs="wait 20, DOWN*20, wait 120, DOWN*16, wait 8, RIGHT*96, wait 8, UP*80, wait 8, RIGHT*16, wait 8, "
                "UP*48, wait 400, " + A(6) + "wait 900, " + A(12) + "wait 200",
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
    dict(name="route1", what="The sign lady's trainer tips at the route entrance, then into Route 1 (Ho-Oh waits for the Pokédex)",
         walk=(15, 6), inputs="UP*64, wait 100, " + B(6) + "wait 60, UP*64, wait 300",
         expect=dict(map="Route1_Frlg", xy=(25, 38),
                     flags={"FLAG_OPENED_START_MENU": True, "FLAG_RB_OPENING_SEEN": False},
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
    dict(name="north-route1", what="North into Route 1: Ho-Oh flies over, then the stranger and the Pokédex with no entry",
         walk=(15, 0), inputs="UP*12, wait 150, " + A(2) + "wait 1000, " + A(40) + "wait 400",
         expect=dict(map="Route1_Frlg", xy=(25, 39), flags={"FLAG_RB_OPENING_SEEN": True, "FLAG_MW01_SEEN": True})),
    dict(name="north-viridian", what="Up Route 1 into Viridian: Giratina drops the Friends on the road", walk=(23, 0),
         inputs="UP*12, wait 30, " + A(110) + "wait 500",
         expect=dict(map="ViridianCity_Frlg", xy=(25, 48), flags={"FLAG_FRIENDS_ARRIVED_IN_VIRIDIAN": True})),
    dict(name="old-man", what="The old man's catching demonstration (the second tutorial battle)",
         walk=(25, 16), inputs="wait 20, UP*16, wait 8, UP*16, wait 8, UP*16, wait 200, " + B(60) + "wait 600",
         expect=dict(map="ViridianCity_Frlg", xy=(25, 13), vars={"VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN": 2})),
    dict(name="route2", what="The road north is open: into Route 2", walk=(25, 0), inputs="UP*12, wait 200",
         expect=dict(map="Route2_Frlg", xy=(9, 79))),
    dict(name="back-viridian", what="Back into Viridian", inputs="wait 30, DOWN*12, wait 200",
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
    dict(name="forest", what="Through the gatehouse into Viridian Forest (its south exit)", walk=(7, 2),
         inputs="UP*20, wait 300", expect=dict(map="ViridianForest_Frlg", xy=(23, 59))),
    dict(name="forest-rick", what="Up the trail and west: Rick sees you across it and battles (you can't walk round "
                                  "him)",
         via=[(23, 50)], walk=(21, 50), inputs=f"LEFT*{hold(1)}, wait 200, " + A(40) + B(6) + "wait 300",
         expect=dict(map="ViridianForest_Frlg", xy=(20, 50))),
    dict(name="forest-doug", what="West through the tall grass, north, east, then north: Doug sees you across the "
                                  "trail and battles",
         via=[(10, 50), (10, 38), (31, 38)], walk=(31, 30),
         inputs=f"UP*{hold(1)}, wait 200, " + A(50) + B(6) + "wait 300",
         expect=dict(map="ViridianForest_Frlg", xy=(31, 29))),
    dict(name="forest-north", what="On north through the last tall grass to the forest's north exit and its gate",
         via=[(32, 22), (18, 22), (18, 10), (23, 10)], walk=(23, 1), inputs="UP*20, wait 300",
         expect=dict(map="Route2_ViridianForest_NorthEntrance_Frlg", xy=(7, 9))),
    dict(name="route2-north", what="Out of the forest's north gate onto Route 2 (its doorway, walking north)",
         walk=(7, 2), inputs="UP*20, wait 300", expect=dict(map="Route2_Frlg", xy=(7, 20))),
    dict(name="pewter", what="Up Route 2's north meadow into Pewter City", walk=(9, 0), inputs="UP*12, wait 200",
         expect=dict(map="PewterCity_Frlg", xy=(23, 43))),
    dict(name="pewter-guide", what="Up Pewter's main street and east along the road out: the Gym guide stops you and "
                                   "walks you to the Gym",
         walk=(40, 26), inputs="RIGHT*60, wait 60, " + A(3) + "wait 900, " + A(3) + "wait 400",
         expect=dict(map="PewterCity_Frlg", xy=(9, 21))),
    dict(name="pewter-gym", what="Into Pewter's Gym (a Wartortle now, for its rock types)",
         state=["CLEAR_TEAM", "SPECIES_WARTORTLE lv40 MOVE_WATER_GUN"], inputs="UP*20, wait 300",
         expect=dict(map="PewterCity_Gym_Frlg", xy=(6, 14))),
    dict(name="gym-liam", what="Up the Gym: the camper Liam sees you across it and battles", walk=(6, 9),
         inputs="UP*" + str(hold(1)) + ", wait 200, " + A(50) + B(6) + "wait 200",
         expect=dict(map="PewterCity_Gym_Frlg", xy=(6, 8))),
    dict(name="brock", what="On up to Brock and beat him: the Boulder Badge", walk=(6, 6),
         inputs="UP*4, wait 20, " + A(80) + B(8) + "wait 200",
         expect=dict(map="PewterCity_Gym_Frlg", xy=(6, 6), flags={"FLAG_BADGE01_GET": True},
                     vars={"VAR_MAP_SCENE_PEWTER_CITY": 1})),
    dict(name="leave-gym", what="Back out of Pewter's Gym", walk=(6, 13), inputs="DOWN*20, wait 300",
         expect=dict(map="PewterCity_Frlg", xy=(9, 21))),
    dict(name="running-shoes", what="East along the road out: Oak's aide stops you and gives you the Running Shoes",
         walk=(44, 26), inputs="RIGHT*60, wait 200, " + A(22, 70) + "wait 300",
         expect=dict(map="PewterCity_Frlg", xy=(47, 26), flags={"FLAG_SYS_B_DASH": True},
                     vars={"VAR_MAP_SCENE_PEWTER_CITY": 2})),
    dict(name="route3", what="On east out of Pewter onto Route 3", walk=(51, 25), inputs="RIGHT*12, wait 200",
         expect=dict(map="Route3_Frlg", xy=(0, 10))),
    dict(name="route3-north", what="Across Route 3 (through the bottom of the tall grass, below the trainers' lines of "
                                   "sight) and up the pass onto Route 4",
         via=[(14, 15), (43, 15), (50, 13), (71, 12)], walk=(71, 0), inputs="UP*12, wait 200",
         expect=dict(map="Route4_Frlg", xy=(11, 19))),
    dict(name="mt-moon", what="Up Route 4's road past the Pokémon Center into Mt. Moon's near mouth", walk=(19, 15),
         inputs="UP*20, wait 300", expect=dict(map="MtMoon_1F_Frlg", xy=(18, 37))),
    dict(name="mt-moon-1f", what="Across Mt. Moon's first floor, round its trainers' lines of sight and its other "
                                  "ladders, to the ladder down in its north-west",
         via=[(18, 25), (26, 25), (26, 15), (35, 15), (35, 9), (18, 9), (18, 18), (11, 18), (11, 6)], walk=(6, 6),
         inputs="LEFT*20, wait 300", expect=dict(map="MtMoon_B1F_Frlg", xy=(3, 3))),
    dict(name="mt-moon-b1f", what="Along the first basement's passage to the ladder down to the second",
         via=[(3, 17)], walk=(22, 17), inputs="DOWN*20, wait 300", expect=dict(map="MtMoon_B2F_Frlg", xy=(25, 21))),
    dict(name="mt-moon-grunt4", what="Into the second basement: the Rocket who looks about the east passage is in the "
                                     "way; step beside him and battle",
         via=[(25, 17), (31, 17), (31, 20)], walk=(36, 20),
         inputs=f"DOWN*{hold(1)}, wait 60, RIGHT*4, wait 20, " + A(40) + B(6) + "wait 300",
         expect=dict(map="MtMoon_B2F_Frlg", xy=(36, 21))),
    dict(name="mt-moon-grunt1", what="Round the rest of the basement to the Rocket in the way north; step into his line "
                                     "of sight and beat him",
         via=[(36, 20), (39, 20), (39, 17), (43, 17), (43, 28), (39, 28), (39, 38), (12, 38)],
         walk=(12, 23), inputs=f"UP*{hold(1)}, wait 200, " + A(40) + B(6) + "wait 300",
         expect=dict(map="MtMoon_B2F_Frlg", xy=(12, 22))),
    dict(name="mt-moon-miguel", what="On north to the fossils: Miguel stops you and battles", via=[(14, 22)],
         walk=(14, 12), inputs=f"UP*{hold(1)}, wait 200, " + A(90) + B(8) + "wait 300",
         expect=dict(map="MtMoon_B2F_Frlg", xy=(14, 11), vars={"VAR_MAP_SCENE_MT_MOON_B2F": 1})),
    dict(name="mt-moon-fossil", what="Take the Helix Fossil; Miguel takes the Dome Fossil (and steps out of the way)",
         walk=(14, 8), inputs="UP*4, wait 30, " + A(10, 90) + "wait 300",
         expect=dict(map="MtMoon_B2F_Frlg", xy=(14, 8), flags={"FLAG_GOT_HELIX_FOSSIL": True})),
    dict(name="mt-moon-b2f", what="North past the fossils and round to the ladder up", via=[(14, 6), (4, 6), (4, 11)],
         walk=(5, 11), inputs="UP*20, wait 300", expect=dict(map="MtMoon_B1F_Frlg", xy=(39, 4))),
    dict(name="mt-moon-out", what="Up the ladder's passage and out of Mt. Moon's far mouth onto Route 4's high shelf",
         walk=(44, 4), inputs="RIGHT*20, wait 400", expect=dict(map="Route4_Frlg", xy=(36, 7))),
    dict(name="route4-ledge", what="East along the shelf and down its ledge to the road (one way)", walk=(50, 8),
         inputs=f"DOWN*{hold(2)}, wait 120", expect=dict(map="Route4_Frlg", xy=(50, 10))),
    dict(name="cerulean", what="East along Route 4's road into Cerulean City", walk=(107, 11),
         inputs="RIGHT*20, wait 200", expect=dict(map="CeruleanCity_Frlg", xy=(0, 18))),
    dict(name="cerulean-rival", what="Round the square (the fence along the Center's north side and the policeman in the "
                                     "robbed house's door close the street past it) and up the bridge road: Blue comes "
                                     "down off Nugget Bridge and battles",
         via=[(30, 30), (40, 28), (41, 24)], walk=(42, 8),
         inputs=f"UP*{hold(1)}, wait 300, " + A(110) + B(10) + "wait 300",
         expect=dict(map="CeruleanCity_Frlg", xy=(42, 7), vars={"VAR_MAP_SCENE_CERULEAN_CITY_RIVAL": 1})),
    dict(name="cerulean-center", what="Into Cerulean's Pokemon Center", walk=(28, 29), inputs="UP*20, wait 250",
         expect=dict(map="CeruleanCity_PokemonCenter_1F_Frlg", xy=(7, 8))),
    dict(name="cerulean-heal", what="The nurse heals the team (Cerulean's Center becomes where you wake after a blackout)",
         inputs="wait 30, UP*50, wait 20, UP*4, wait 20, A*4, wait 100, A*4, wait 100, A*4, wait 400, " + B(6)
                + "wait 100",
         expect=dict(map="CeruleanCity_PokemonCenter_1F_Frlg", xy=(7, 4))),
    dict(name="cerulean-leave-center", what="Out of the Center", inputs="wait 30, DOWN*66, wait 20, DOWN*20, wait 250",
         expect=dict(map="CeruleanCity_Frlg", xy=(28, 29))),
    dict(name="nugget-bridge", what="Up the bridge road onto Nugget Bridge (Route 24)", walk=(42, 0),
         inputs=f"UP*{hold(1)}, wait 200", expect=dict(map="Route24_Frlg", xy=(17, 21))),
    dict(name="bridge-cale", what="Up the bridge: Cale sees you across it and battles", walk=(17, 20),
         inputs=f"UP*{hold(1)}, wait 200, " + A(80) + B(8) + "wait 300", expect=dict(map="Route24_Frlg", xy=(17, 19))),
    dict(name="bridge-ali", what="Up the bridge: Ali sees you across it and battles", walk=(17, 18),
         inputs=f"UP*{hold(1)}, wait 200, " + A(80) + B(8) + "wait 300", expect=dict(map="Route24_Frlg", xy=(17, 17))),
    dict(name="bridge-timmy", what="Up the bridge: Timmy sees you across it and battles", walk=(17, 16),
         inputs=f"UP*{hold(1)}, wait 200, " + A(80) + B(8) + "wait 300", expect=dict(map="Route24_Frlg", xy=(17, 15))),
    dict(name="bridge-reli", what="Up the bridge: Reli sees you across it and battles", walk=(17, 14),
         inputs=f"UP*{hold(1)}, wait 200, " + A(80) + B(8) + "wait 300", expect=dict(map="Route24_Frlg", xy=(17, 13))),
    dict(name="bridge-ethan", what="Up the bridge: Ethan sees you across it and battles", walk=(17, 12),
         inputs=f"UP*{hold(1)}, wait 200, " + A(80) + B(8) + "wait 300", expect=dict(map="Route24_Frlg", xy=(17, 11))),
    dict(name="bridge-rocket",
         what="At the bridge's north end the Rocket steps over, gives you the Nugget and battles (Wartortle evolves)",
         walk=(17, 9), inputs=f"UP*{hold(1)}, wait 300, " + A(80) + "wait 900, " + A(30) + "wait 300",
         expect=dict(map="Route24_Frlg", xy=(17, 8), vars={"VAR_MAP_SCENE_ROUTE24": 1})),
    dict(name="route25", what="Off the bridge's north end onto Route 25", walk=(17, 0), inputs=f"UP*{hold(1)}, wait 200",
         expect=dict(map="Route25_Frlg", xy=(17, 23))),
    dict(name="route25-joey", what="Up off the bridge and east along the cape road into the first neck: Joey sees you; "
         "beat him", via=[(17, 9)], walk=(27, 9), inputs=f"RIGHT*{hold(1)}, wait 200, " + A(80) + B(8) + "wait 300",
         expect=dict(map="Route25_Frlg", xy=(28, 9))),
    dict(name="route25-wayne", what="On past the couple and Nob (round the north of their sight) into the second neck: "
         "Wayne sees you; beat him", via=[(40, 9), (40, 7), (46, 7)], walk=(46, 9),
         inputs=f"RIGHT*{hold(1)}, wait 200, " + A(80) + B(8) + "wait 300", expect=dict(map="Route25_Frlg", xy=(47, 9))),
    dict(name="sea-cottage", what="Along the headland and up the path into Bill's Sea Cottage", via=[(51, 9)],
         walk=(51, 8), inputs=f"UP*{hold(1)}, wait 250", expect=dict(map="Route25_SeaCottage_Frlg", xy=(7, 9))),
    # one step: that Bill is in his teleporter is a temporary flag, which a checkpoint (the map loaded again) forgets
    dict(name="bill", what="Talk to the Clefairy (Bill): help him, and he goes into his teleporter; run the cell "
         "separator on his PC, and he comes out of the other", walk=(10, 7),
         inputs="UP*4, wait 30, " + A(12) + f"wait 300, LEFT*{hold(6)}, wait 20, UP*{hold(1)}, wait 20, " + A(4)
         + "wait 1200",
         expect=dict(map="Route25_SeaCottage_Frlg", xy=(4, 6), flags={"FLAG_HELPED_BILL_IN_SEA_COTTAGE": True})),
    dict(name="ss-ticket", what="Talk to Bill (back where he stands, 7,5): he gives you the S.S. Ticket", walk=(7, 6),
         inputs="UP*4, wait 30, " + A(12) + "wait 200",
         expect=dict(map="Route25_SeaCottage_Frlg", xy=(7, 6), flags={"FLAG_GOT_SS_TICKET": True})),
    dict(name="leave-cottage", what="Out of the cottage onto the headland", walk=(7, 8),
         inputs=f"DOWN*{hold(1)}, wait 20, DOWN*20, wait 250",
         expect=dict(map="Route25_Frlg", xy=(51, 8))),
    dict(name="back-to-bridge", what="Back west along the cape road, round the north of Nob's and Flint's sight and "
         "through Joey's neck (not down the ledges), onto the bridge",
         via=[(51, 9), (45, 9), (45, 7), (40, 7), (40, 9), (27, 9), (17, 9)], walk=(17, 23),
         inputs=f"DOWN*{hold(1)}, wait 200",
         expect=dict(map="Route24_Frlg", xy=(17, 0))),
    dict(name="back-over-bridge", what="Back over Nugget Bridge (its trainers beaten, the Rocket gone) into Cerulean",
         walk=(17, 21), inputs=f"DOWN*{hold(1)}, wait 200", expect=dict(map="CeruleanCity_Frlg", xy=(42, 0))),
    dict(name="route5", what="Through Cerulean and south through the neck (the lass and her Slowbro gone with the "
         "S.S. Ticket) onto Route 5", walk=(22, 50), inputs=f"DOWN*{hold(1)}, wait 200",
         expect=dict(map="Route5_Frlg", xy=(30, 0))),
    dict(name="underground-path", what="Down Route 5's road and into the Underground Path's hut", walk=(35, 25),
         inputs=f"UP*{hold(1)}, wait 250", expect=dict(map="UndergroundPath_NorthEntrance_Frlg", xy=(13, 12))),
    dict(name="tunnel", what="Down the hut's stairs into the Underground Path (stand on them and walk east)",
         walk=(12, 9), inputs=f"UP*{hold(1)}, wait 20, RIGHT*20, wait 250", expect=dict(map="UndergroundPath_NorthSouthTunnel_Frlg", xy=(3, 4))),
    dict(name="tunnel-south", what="Along the tunnel under Saffron and up the stairs at its south end (east off them)",
         walk=(2, 37), inputs=f"DOWN*{hold(1)}, wait 20, RIGHT*20, wait 250", expect=dict(map="UndergroundPath_SouthEntrance_Frlg", xy=(14, 8))),
    dict(name="route6", what="Out of the south hut onto Route 6", walk=(13, 11),
         inputs=f"DOWN*{hold(1)}, wait 20, DOWN*20, wait 250", expect=dict(map="Route6_Frlg", xy=(46, 12))),
    dict(name="vermilion", what="Down Route 6's road (in no trainer's sight) to Vermilion's stairs", walk=(41, 31),
         inputs=f"DOWN*{hold(1)}, wait 200", expect=dict(map="VermilionCity_Frlg", xy=(33, 0))),
    dict(name="vermilion-center", what="Down the road into Vermilion's Pokémon Center", walk=(28, 7),
         inputs=f"UP*{hold(1)}, wait 250", expect=dict(map="VermilionCity_PokemonCenter_1F_Frlg", xy=(7, 8))),
    dict(name="vermilion-heal", what="The nurse heals the team (Vermilion's Center becomes where you wake after a "
         "blackout)", inputs="wait 30, UP*50, wait 20, UP*4, wait 20, A*4, wait 100, A*4, wait 100, A*4, wait 400, "
         + B(6) + "wait 100", expect=dict(map="VermilionCity_PokemonCenter_1F_Frlg", xy=(7, 4))),
    dict(name="vermilion-leave-center", what="Back out to the plaza",
         inputs="wait 30, DOWN*66, wait 20, DOWN*20, wait 250", expect=dict(map="VermilionCity_Frlg", xy=(28, 7))),
    dict(name="route11", what="East along Vermilion's main street onto Route 11", walk=(59, 12),
         inputs=f"RIGHT*{hold(1)}, wait 200", expect=dict(map="Route11_Frlg", xy=(0, 15))),
    dict(name="route11-gatehouse", what="Along Route 11's road (in no trainer's sight) into the gatehouse before "
         "Route 12", walk=(53, 16), inputs=f"UP*{hold(1)}, wait 250",
         expect=dict(map="Route11_EastEntrance_1F_Frlg", xy=(1, 6))),
    dict(name="route11-leave-gatehouse", what="Back out of the gatehouse by its west door (stand on it and walk "
         "west); Snorlax sleeps on Route 12's road", inputs="wait 30, LEFT*20, wait 250",
         expect=dict(map="Route11_Frlg", xy=(53, 16))),
    dict(name="back-to-vermilion", what="Back west along the road into Vermilion", walk=(0, 15),
         inputs=f"LEFT*{hold(1)}, wait 200", expect=dict(map="VermilionCity_Frlg", xy=(59, 12))),
    dict(name="ss-anne", what="Down the pier: the ferry sailor checks the S.S. Ticket, and onto the S.S. Anne's "
         "gangway", walk=(37, 39), inputs=f"DOWN*{hold(1)}, wait 30, " + A(6) + f"DOWN*{hold(1)}, wait 250",
         expect=dict(map="SSAnne_Exterior_Frlg", xy=(32, 5))),
    dict(name="ss-anne-board", what="Down the gangway into the ship's first-floor corridor (its end is an arrow: press down on it)", walk=(32, 13),
         inputs=f"DOWN*{hold(1)}, wait 20, DOWN*20, wait 250", expect=dict(map="SSAnne_1F_Corridor_Frlg", xy=(19, 2))),
    dict(name="ss-anne-2f", what="West along the corridor (round the worker, off the row of cabin doors) and up the "
         "stairs at its end to the second floor (walk west onto them)", via=[(19, 9), (13, 9), (13, 8)], walk=(4, 8),
         inputs=f"LEFT*{hold(1)}, wait 20, LEFT*20, wait 250", expect=dict(map="SSAnne_2F_Corridor_Frlg", xy=(2, 2))),
    dict(name="ss-anne-rival", what="Down past the sailor, east along the corridor (off the stairs to 3F and the cabin "
         "doors) and up towards the captain's door: Blue comes out and battles", via=[(4, 11), (4, 13), (31, 13)],
         walk=(31, 7), inputs=f"UP*{hold(1)}, wait 300, " + A(110) + B(10) + "wait 300",
         expect=dict(map="SSAnne_2F_Corridor_Frlg", xy=(31, 6), vars={"VAR_MAP_SCENE_S_S_ANNE_2F_CORRIDOR": 1})),
    dict(name="captains-office", what="Up the stairs to the captain's office (stand at their foot and walk east)",
         walk=(30, 3), inputs=f"UP*{hold(1)}, wait 20, RIGHT*20, wait 250",
         expect=dict(map="SSAnne_CaptainsOffice_Frlg", xy=(3, 7))),
    dict(name="hm01", what="Talk to the seasick captain: rub his back, and he gives you HM01 (Cut)", walk=(5, 5),
         inputs="UP*4, wait 20, " + A(30, 90) + B(6) + "wait 200",
         expect=dict(map="SSAnne_CaptainsOffice_Frlg", xy=(5, 5), flags={"FLAG_GOT_HM01": True},
                     vars={"VAR_MAP_SCENE_VERMILION_CITY": 1})),
    dict(name="leave-office", what="Back down the office's stairs (walk west onto them)", walk=(4, 7),
         inputs=f"LEFT*{hold(1)}, wait 20, LEFT*20, wait 250", expect=dict(map="SSAnne_2F_Corridor_Frlg", xy=(30, 2))),
    dict(name="ss-anne-down", what="Back west along the second floor (off the cabin doors and the stairs to 3F) and "
         "down the stairs to the first (up the passage's east side, away from the sailor; walk east off their head)", via=[(31, 13), (4, 13), (4, 4)], walk=(2, 3),
         inputs=f"UP*{hold(1)}, wait 20, RIGHT*20, wait 250", expect=dict(map="SSAnne_1F_Corridor_Frlg", xy=(3, 8))),
    dict(name="leave-ss-anne", what="East along the corridor (round the worker and the sailor) and out of the ship: it "
         "sails, and you walk up the gangway onto Vermilion's pier", via=[(13, 8), (13, 9), (19, 9)], walk=(19, 2),
         inputs=f"UP*{hold(1)}, wait 20, UP*20, wait 3000",
         expect=dict(map="VermilionCity_Frlg", xy=(38, 38), vars={"VAR_MAP_SCENE_VERMILION_CITY": 3})),
    dict(name="back-to-route6", what="Up the pier and the road through Vermilion (up the plaza's middle, between the "
         "Center's and the Mart's doors) onto Route 6", via=[(38, 23), (33, 12)], walk=(33, 0),
         inputs=f"UP*{hold(1)}, wait 200", expect=dict(map="Route6_Frlg", xy=(41, 31))),
    dict(name="route6-hut", what="Up Route 6's road (in no trainer's sight) into the Underground Path's hut",
         walk=(46, 12), inputs=f"UP*{hold(1)}, wait 250", expect=dict(map="UndergroundPath_SouthEntrance_Frlg", xy=(13, 12))),
    dict(name="tunnel-back", what="Down the hut's stairs (stand on them and walk west) into the tunnel", walk=(14, 9),
         inputs=f"UP*{hold(1)}, wait 20, LEFT*20, wait 250", expect=dict(map="UndergroundPath_NorthSouthTunnel_Frlg", xy=(2, 38))),
    dict(name="tunnel-north", what="Back along the tunnel and up its north stairs (west off them)", walk=(3, 5),
         inputs=f"UP*{hold(1)}, wait 20, LEFT*20, wait 250", expect=dict(map="UndergroundPath_NorthEntrance_Frlg", xy=(12, 8))),
    dict(name="route5-back", what="Out of the north hut onto Route 5", walk=(13, 11),
         inputs=f"DOWN*{hold(1)}, wait 20, DOWN*20, wait 250", expect=dict(map="Route5_Frlg", xy=(35, 25))),
    dict(name="cerulean-back", what="Up Route 5's road and through the neck into Cerulean", walk=(30, 0),
         inputs=f"UP*{hold(1)}, wait 200", expect=dict(map="CeruleanCity_Frlg", xy=(22, 50))),
    dict(name="cerulean-gym", what="Through Cerulean and into Misty's Gym", walk=(47, 37), inputs=f"UP*{hold(1)}, wait 300",
         expect=dict(map="CeruleanCity_Gym_Frlg", xy=(7, 18))),
    dict(name="gym-diana", what="Round the Gym guy, past the swimmer Luis's one block of sight and round the pool's "
         "west walkway to the east one; west towards Misty into the picnicker Diana's line: she battles",
         via=[(6, 18), (6, 15), (7, 14), (7, 13), (5, 13), (5, 10), (10, 10), (10, 8)], walk=(9, 7),
         inputs=f"LEFT*{hold(1)}, wait 300, " + A(80) + B(8) + "wait 300",
         expect=dict(map="CeruleanCity_Gym_Frlg", xy=(8, 7))),
    dict(name="misty", what="Face Misty and beat her: the Cascade Badge (Cut can be used outside battle)",
         inputs="UP*4, wait 20, " + A(160) + B(12) + "wait 300",
         expect=dict(map="CeruleanCity_Gym_Frlg", xy=(8, 7), flags={"FLAG_BADGE02_GET": True})),
    dict(name="leave-cerulean-gym", what="Back out of the Gym the way you came (its mat: press down on it)", via=[(10, 8), (10, 10), (5, 10),
         (5, 13), (7, 13), (7, 14), (6, 15), (6, 17)], walk=(7, 17), inputs=f"DOWN*{hold(1)}, wait 20, DOWN*20, wait 300",
         expect=dict(map="CeruleanCity_Frlg", xy=(47, 37))),
    dict(name="route9", what="East out of Cerulean onto Route 9", walk=(57, 29), inputs=f"RIGHT*{hold(1)}, wait 200",
         expect=dict(map="Route9_Frlg", xy=(0, 9))),
    dict(name="route9-alicia", what="Cut the tree in the neck and on along the gorge into the picnicker Alicia's line: "
         "she battles (in one step: a checkpoint's reload would bring the tree back). The team is set here: one Kingler "
         "at level 65 that knows Surf and Cut (the captain's HM01 isn't taught in the steps; the Blastoise's Water Gun "
         "had run down). One Pokémon, so no battle asks whether to change Pokémon, strong enough to knock out what it "
         "meets before a Slowpoke can Disable its Surf",
         state=["CLEAR_TEAM", "SPECIES_KINGLER lv65 MOVE_SURF MOVE_CUT"], walk=(8, 9),
         inputs="RIGHT*4, wait 30, " + A(4, 130) + "wait 300, " + f"RIGHT*{hold(5)}, wait 300, " + A(160) + B(12)
                + "wait 300", expect=dict(map="Route9_Frlg", xy=(13, 9))),
    dict(name="route9-chris", what="On along the gorge into the camper Chris's line: he battles", walk=(18, 9),
         inputs=f"RIGHT*{hold(1)}, wait 300, " + A(160) + B(12) + "wait 300", expect=dict(map="Route9_Frlg", xy=(19, 9))),
    dict(name="route10", what="Along Route 9's road round the outcrop (in no other trainer's sight) onto Route 10",
         walk=(59, 18), inputs=f"RIGHT*{hold(1)}, wait 200", expect=dict(map="Route10_Frlg", xy=(0, 18))),
    dict(name="route10-center", what="Up to Route 10's Pokémon Center", walk=(14, 16), inputs=f"UP*{hold(1)}, wait 250",
         expect=dict(map="Route10_PokemonCenter_1F_Frlg", xy=(7, 8))),
    dict(name="route10-heal", what="The nurse heals the team (Route 10's Center becomes where you wake after a "
         "blackout)", inputs="wait 30, UP*50, wait 20, UP*4, wait 20, A*4, wait 100, A*4, wait 100, A*4, wait 400, "
         + B(6) + "wait 100", expect=dict(map="Route10_PokemonCenter_1F_Frlg", xy=(7, 4))),
    dict(name="route10-leave-center", what="Back out to the clearing",
         inputs="wait 30, DOWN*66, wait 20, DOWN*20, wait 250", expect=dict(map="Route10_Frlg", xy=(14, 16))),
    dict(name="rock-tunnel", what="Into Rock Tunnel's north mouth", walk=(8, 9), inputs=f"UP*{hold(1)}, wait 250",
         expect=dict(map="RockTunnel_1F_Frlg", xy=(17, 2))),
    dict(name="rt-ashton", what="Into Rock Tunnel's dark first floor (no Flash): the hiker Ashton's line can't be gone "
         "round on the way to the ladder down; he battles", via=[(17, 8), (24, 8)], walk=(24, 9),
         inputs=f"DOWN*{hold(1)}, wait 300, " + A(160) + B(12) + "wait 300",
         expect=dict(map="RockTunnel_1F_Frlg", xy=(24, 10))),
    dict(name="rt-b1f", what="On east along the floor's south passage and up to the ladder down to B1F",
         via=[(24, 12), (45, 12)], walk=(45, 3), inputs=f"UP*{hold(1)}, wait 20, UP*20, wait 300",
         expect=dict(map="RockTunnel_B1F_Frlg", xy=(38, 38))),
    dict(name="rt-winston", what="Down B1F's east side and west along its bottom passage: the hiker Winston's line "
         "crosses it; he battles", via=[(37, 37), (37, 46)], walk=(30, 46),
         inputs=f"LEFT*{hold(1)}, wait 300, " + A(160) + B(12) + "wait 300", expect=dict(map="RockTunnel_B1F_Frlg", xy=(29, 46))),
    dict(name="rt-martha", what="On west and up the passage north: the picnicker Martha battles", via=[(17, 46)],
         walk=(17, 44), inputs=f"UP*{hold(1)}, wait 300, " + A(160) + B(12) + "wait 300",
         expect=dict(map="RockTunnel_B1F_Frlg", xy=(17, 43))),
    dict(name="rt-allen", what="North and east round the middle of B1F to the hall below the ladder: the hiker "
         "Allen battles", via=[(17, 41), (29, 41), (29, 31), (38, 31)], walk=(38, 24),
         inputs=f"LEFT*{hold(2)}, wait 300, " + A(160) + B(12) + "wait 300", expect=dict(map="RockTunnel_B1F_Frlg", xy=(36, 24))),
    dict(name="rt-1f-west", what="Up the ladder to the first floor's west side (the Kingler is given again here, its "
         "Surf full: the tunnel has no Center, and one Surf's 15 PP don't last its trainers)",
         state=["CLEAR_TEAM", "SPECIES_KINGLER lv65 MOVE_SURF MOVE_CUT"], via=[(33, 24)], walk=(33, 14),
         inputs=f"UP*{hold(1)}, wait 20, UP*20, wait 300", expect=dict(map="RockTunnel_1F_Frlg", xy=(4, 2))),
    dict(name="rt-lenny", what="Down the floor's west side into the PokéManiac Lenny's line: he battles",
         via=[(4, 9)], walk=(6, 9), inputs=f"RIGHT*{hold(1)}, wait 300, " + A(160) + B(12) + "wait 300",
         expect=dict(map="RockTunnel_1F_Frlg", xy=(7, 9))),
    dict(name="rt-b1f-west", what="East and south to the ladder down to B1F's west part",
         via=[(10, 9), (10, 16), (20, 16)], walk=(20, 14), inputs=f"UP*{hold(1)}, wait 20, UP*20, wait 300",
         expect=dict(map="RockTunnel_B1F_Frlg", xy=(27, 22))),
    dict(name="rt-sofia", what="West along B1F's middle into the picnicker Sofia's line: she battles",
         via=[(19, 23), (19, 26)], walk=(12, 26), inputs=f"LEFT*{hold(1)}, wait 300, " + A(160) + B(12) + "wait 300",
         expect=dict(map="RockTunnel_B1F_Frlg", xy=(11, 26))),
    dict(name="rt-dudley", what="On west into the hiker Dudley's line: he battles", via=[(8, 26), (8, 25)],
         walk=(6, 25), inputs=f"LEFT*{hold(1)}, wait 300, " + A(160) + B(12) + "wait 300",
         expect=dict(map="RockTunnel_B1F_Frlg", xy=(5, 25))),
    dict(name="rt-cooper", what="North up the west passage to the PokéManiac Cooper, who looks about: face him and "
         "battle (he may see you first)", via=[(3, 25)], walk=(3, 17),
         inputs=f"UP*{hold(1)}, wait 300, LEFT*4, wait 20, " + A(160) + B(12) + "wait 300",
         expect=dict(map="RockTunnel_B1F_Frlg", xy=(3, 16))),
    dict(name="rt-1f-east", what="On up to the ladder to the first floor's east part (the Kingler given again, its "
         "Surf full)", state=["CLEAR_TEAM", "SPECIES_KINGLER lv65 MOVE_SURF MOVE_CUT"], walk=(2, 14),
         inputs=f"UP*{hold(1)}, wait 20, UP*20, wait 300", expect=dict(map="RockTunnel_1F_Frlg", xy=(45, 21))),
    dict(name="rt-dana", what="Down and round the floor's east part and west along its south passage: the "
         "picnicker Dana's line crosses it; she battles",
         via=[(39, 22), (39, 26), (44, 26), (44, 30), (42, 30), (42, 32), (31, 32), (31, 31)], walk=(27, 31),
         inputs=f"LEFT*{hold(1)}, wait 300, " + A(160) + B(12) + "wait 300", expect=dict(map="RockTunnel_1F_Frlg", xy=(26, 31))),
    dict(name="rt-out", what="On west and down out of Rock Tunnel's south mouth onto Route 10", via=[(18, 31)],
         walk=(18, 36), inputs=f"DOWN*{hold(1)}, wait 20, DOWN*20, wait 300",
         expect=dict(map="Route10_Frlg", xy=(10, 46))),
    dict(name="lavender", what="Down Route 10's valley road (in no trainer's sight) into Lavender", walk=(18, 59),
         inputs=f"DOWN*{hold(1)}, wait 200", expect=dict(map="LavenderTown_Frlg", xy=(14, 0))),
    dict(name="lavender-center", what="Down the north road into Lavender's Pokémon Center", walk=(7, 7),
         inputs=f"UP*{hold(1)}, wait 250", expect=dict(map="LavenderTown_PokemonCenter_1F_Frlg", xy=(7, 8))),
    dict(name="lavender-heal", what="The nurse heals the team (Lavender's Center becomes where you wake after a "
         "blackout)", inputs="wait 30, UP*50, wait 20, UP*4, wait 20, A*4, wait 100, A*4, wait 100, A*4, wait 400, "
         + B(6) + "wait 100", expect=dict(map="LavenderTown_PokemonCenter_1F_Frlg", xy=(7, 4))),
    dict(name="lavender-leave-center", what="Back out to the street",
         inputs="wait 30, DOWN*66, wait 20, DOWN*20, wait 250", expect=dict(map="LavenderTown_Frlg", xy=(7, 7))),
    dict(name="route8", what="West along Lavender's street onto Route 8 (Saffron's gates are shut: the way on is "
         "Route 8's underground path to Celadon)", walk=(0, 10), inputs=f"LEFT*{hold(1)}, wait 200",
         expect=dict(map="Route8_Frlg", xy=(59, 14))),
    dict(name="route8-underground", what="West along Route 8's road (in no trainer's sight) into the Underground "
         "Path's hut", walk=(18, 13), inputs=f"UP*{hold(1)}, wait 250",
         expect=dict(map="UndergroundPath_EastEntrance_Frlg", xy=(13, 12))),
    dict(name="ew-tunnel", what="Down the hut's stairs into the Underground Path west (stand on them and walk west)",
         walk=(14, 9), inputs=f"UP*{hold(1)}, wait 20, LEFT*20, wait 250",
         expect=dict(map="UndergroundPath_EastWestTunnel_Frlg", xy=(76, 4))),
    dict(name="ew-tunnel-west", what="Along the tunnel under Saffron and up the stairs at its west end (west off them)",
         walk=(3, 5), inputs=f"UP*{hold(1)}, wait 20, LEFT*20, wait 250",
         expect=dict(map="UndergroundPath_WestEntrance_Frlg", xy=(12, 8))),
    dict(name="route7", what="Out of the west hut onto Route 7", walk=(13, 11),
         inputs=f"DOWN*{hold(1)}, wait 20, DOWN*20, wait 250", expect=dict(map="Route7_Frlg", xy=(9, 10))),
    dict(name="celadon", what="West along Route 7's road into Celadon", walk=(0, 11), inputs=f"LEFT*{hold(1)}, wait 200",
         expect=dict(map="CeladonCity_Frlg", xy=(59, 21))),
    dict(name="celadon-center", what="West along the boulevard into Celadon's Pokémon Center", walk=(49, 19),
         inputs=f"UP*{hold(1)}, wait 250", expect=dict(map="CeladonCity_PokemonCenter_1F_Frlg", xy=(7, 8))),
    dict(name="celadon-heal", what="The nurse heals the team (Celadon's Center becomes where you wake after a "
         "blackout)", inputs="wait 30, UP*50, wait 20, UP*4, wait 20, A*4, wait 100, A*4, wait 100, A*4, wait 400, "
         + B(6) + "wait 100", expect=dict(map="CeladonCity_PokemonCenter_1F_Frlg", xy=(7, 4))),
    dict(name="celadon-leave-center", what="Back out to the boulevard",
         inputs="wait 30, DOWN*66, wait 20, DOWN*20, wait 250", expect=dict(map="CeladonCity_Frlg", xy=(49, 19))),
    # Past Celadon (the rest of Kanto's story, added once every Kanto town and route was rebuilt). From here the
    # team is one Pokémon at level 100 that knows Psychic and the field moves the story needs (Surf, Cut, Strength):
    # the story check is about the maps and the scenes, not the battles, and one Pokémon never asks to switch
    dict(name="celadon-gym-tree", what="Cut the tree in the hedge round Erika's garden and walk through to the Gym's "
         "door. The team is set here: one Alakazam at level 100 that knows Psychic, Surf, Cut and Strength", state=["CLEAR_TEAM", TEAM], walk=(12, 24),
         inputs="DOWN*4, wait 30, " + A(4, 130) + "wait 300, path 12,24 12,35, " + f"UP*{hold(1)}, wait 300",
         expect=dict(map="CeladonCity_Gym_Frlg", xy=(6, 18))),
    dict(name="erika", what="Cut the middle tree of the Gym's hedge and walk up the middle of the garden (in nobody's "
         "line of sight) to Erika; face her and beat her: the Rainbow Badge", walk=(6, 15),
         inputs="UP*4, wait 30, " + A(4, 130) + "wait 300, path 6,15 6,5, UP*4, wait 20, " + A(160) + B(12) + "wait 300",
         expect=dict(map="CeladonCity_Gym_Frlg", xy=(6, 5), flags={"FLAG_BADGE04_GET": True})),
    dict(name="leave-celadon-gym", what="Back down the garden, cut the tree again (it grew back) and out of the Gym",
         walk=(6, 13), inputs="DOWN*4, wait 30, " + A(4, 130) + "wait 300, path 6,13 6,18, DOWN*20, wait 300",
         expect=dict(map="CeladonCity_Frlg", xy=(12, 35))),
    dict(name="celadon-garden-out", what="Out of Erika's garden: cut the tree in the hedge again (it grew back) and "
         "walk through", walk=(12, 26), inputs="UP*4, wait 30, " + A(4, 130) + f"wait 300, UP*{hold(2)}, wait 30",
         expect=dict(map="CeladonCity_Frlg", xy=(12, 24))),
    dict(name="game-corner", what="Across Celadon (round the old man by the hedge) into the Game Corner",
         via=[(12, 22)], walk=(28, 30), inputs=f"UP*{hold(1)}, wait 300",
         expect=dict(map="CeladonCity_GameCorner_Frlg")),
    dict(name="game-corner-grunt", state=FRESH, what="Up to the Rocket grunt standing at the poster at the back; talk to him and "
         "beat him (he runs off)", via=[(9, 11), (9, 4)], walk=(11, 3), inputs="UP*4, wait 20, " + A(60) + B(8) + "wait 300",
         expect=dict(map="CeladonCity_GameCorner_Frlg", xy=(11, 3))),
    dict(name="rocket-hideout", what="Press the switch behind the poster (stairs open in the corner) and take them "
         "down into the Rocket Hideout", inputs=f"UP*{hold(1)}, wait 20, UP*4, wait 20, " + A(4) + B(2) +
         "path 11,2 14,2, " + f"RIGHT*{hold(1)}, wait 20, RIGHT*30, wait 300",
         expect=dict(map="RocketHideout_B1F_Frlg", flags={"FLAG_OPENED_ROCKET_HIDEOUT": True})),
    # The Hideout's floors below are FireRed's own. Walks over its spin tiles (you slide until a stop tile or
    # something solid) were planned on the tiles, off every trainer's line of sight, one key at a time
    dict(name="hideout-b2f", what="Along B1F's top corridor and down its stairs to B2F", walk=(16, 2),
         inputs="RIGHT*12, wait 20, RIGHT*30, wait 300", expect=dict(map="RocketHideout_B2F_Frlg", xy=(28, 2))),
    dict(name="hideout-b3f", what="Round B2F's east rooms (out of the grunt's sight) and down the stairs to B3F",
         inputs="DOWN*60, wait 6, LEFT*44, wait 6, UP*12, wait 6, LEFT*28, wait 6, UP*12, wait 6, LEFT*28, wait 6, "
         "UP*28, wait 20, RIGHT*30, wait 300", expect=dict(map="RocketHideout_B3F_Frlg", xy=(18, 2))),
    dict(name="hideout-b4f", what="Across B3F's spin tiles (three slides) and down the stairs to B4F",
         inputs="DOWN*28, wait 6, LEFT*92, wait 6, DOWN*44, wait 6, LEFT*92, wait 6, DOWN*12, wait 6, LEFT*12, wait 6, "
         "DOWN*12, wait 6, LEFT*12, wait 76, DOWN*12, wait 6, DOWN*12, wait 100, LEFT*28, wait 6, DOWN*44, wait 6, "
         "LEFT*44, wait 6, DOWN*28, wait 6, RIGHT*12, wait 6, RIGHT*12, wait 148, LEFT*28, wait 6, DOWN*76, wait 6, "
         "RIGHT*76, wait 6, UP*76, wait 6, RIGHT*76, wait 6, UP*28, wait 20, LEFT*30, wait 300",
         expect=dict(map="RocketHideout_B4F_Frlg", xy=(11, 15))),
    dict(name="hideout-lift-key-grunt", state=FRESH, what="Up B4F's west rooms to the grunt by the Lift Key; talk to him from the side "
         "and beat him (he drops the key)", walk=(5, 2), inputs="LEFT*4, wait 20, " + A(60) + B(8) + "wait 300",
         expect=dict(map="RocketHideout_B4F_Frlg", xy=(5, 2))),
    dict(name="hideout-lift-key", what="Round him and pick up the Lift Key", inputs="DOWN*12, wait 30, LEFT*12, wait 30, LEFT*12, wait 30, UP*4, wait 20, " + A(4) + B(2),
         expect=dict(map="RocketHideout_B4F_Frlg", xy=(3, 3), flags={"FLAG_CAN_USE_ROCKET_HIDEOUT_LIFT": True})),
    dict(name="hideout-back-b3f", what="Back down the rooms and up the stairs to B3F",
         inputs="RIGHT*28, wait 6, DOWN*60, wait 6, RIGHT*60, wait 6, DOWN*124, wait 6, RIGHT*28, wait 20, RIGHT*30, wait 300",
         expect=dict(map="RocketHideout_B3F_Frlg")),
    dict(name="hideout-back-b2f", what="Back across B3F (two slides) and up its stairs to B2F",
         inputs="DOWN*28, wait 6, LEFT*44, wait 6, UP*60, wait 6, LEFT*28, wait 6, UP*12, wait 6, UP*12, wait 64, "
         "LEFT*12, wait 6, UP*28, wait 6, LEFT*12, wait 76, RIGHT*60, wait 6, UP*108, wait 6, RIGHT*92, wait 20, "
         "RIGHT*30, wait 300", expect=dict(map="RocketHideout_B2F_Frlg", xy=(21, 2))),
    dict(name="hideout-moon-stone", what="Slide along B2F's top row (out of the grunt's sight) to its west end and pick "
         "up the Moon Stone that blocks the way down",
         inputs="DOWN*12, wait 6, LEFT*28, wait 6, DOWN*28, wait 6, LEFT*28, wait 6, DOWN*12, wait 6, LEFT*12, wait 256, "
         "RIGHT*12, wait 30, DOWN*3, wait 20, " + A(3) + B(2),
         expect=dict(map="RocketHideout_B2F_Frlg", xy=(2, 4))),
    dict(name="hideout-elevator", what="Down through B2F's spin maze (five slides) to the lift and into it",
         inputs="DOWN*60, wait 6, RIGHT*12, wait 6, DOWN*12, wait 6, RIGHT*12, wait 124, RIGHT*12, wait 6, RIGHT*12, "
         "wait 124, LEFT*12, wait 6, LEFT*12, wait 100, RIGHT*44, wait 6, DOWN*28, wait 6, LEFT*12, wait 124, RIGHT*12, "
         "wait 6, DOWN*12, wait 100, RIGHT*28, wait 6, UP*44, wait 6, RIGHT*204, wait 6, UP*12, wait 300",
         expect=dict(map="RocketHideout_Elevator_Frlg")),
    dict(name="hideout-lift-b4f", what="Up to the lift's panel, choose B4F (the Lift Key works it) and walk out "
         "(the mat's east half)",
         inputs="UP*12, wait 30, LEFT*12, wait 30, LEFT*12, wait 30, UP*12, wait 30, A*4, wait 90, DOWN*4, wait 30, "
         "A*4, wait 400, RIGHT*12, wait 30, RIGHT*12, wait 30, DOWN*12, wait 30, DOWN*12, wait 30, DOWN*30, wait 300",
         expect=dict(map="RocketHideout_B4F_Frlg")),
    dict(name="hideout-door-grunt-west", state=FRESH, what="Talk to the west grunt guarding Giovanni's door and beat him",
         walk=(16, 15), inputs="UP*4, wait 20, " + A(60) + B(8) + "wait 300",
         expect=dict(map="RocketHideout_B4F_Frlg", xy=(16, 15))),
    dict(name="hideout-door-grunt-east", state=FRESH, what="Then the east one: with both beaten the barrier between them goes",
         walk=(19, 15), inputs="UP*4, wait 20, " + A(60) + B(8) + "wait 300",
         expect=dict(map="RocketHideout_B4F_Frlg", xy=(19, 15))),
    dict(name="giovanni-hideout", state=FRESH, what="Through the open door up to Giovanni; face him and beat him (he leaves the "
         "Silph Scope behind)", via=[(18, 12)], walk=(19, 5), inputs="UP*4, wait 20, " + A(100) + B(12) + "wait 300",
         expect=dict(map="RocketHideout_B4F_Frlg", xy=(19, 5), flags={"FLAG_HIDE_CELADON_ROCKETS": True})),
    dict(name="silph-scope", what="Pick up the Silph Scope beside where he stood", inputs="RIGHT*4, wait 20, " + A(4) + B(2),
         expect=dict(map="RocketHideout_B4F_Frlg", xy=(19, 5), flags={"FLAG_HIDE_SILPH_SCOPE": True})),
    dict(name="hideout-lift-up", what="Back down to the lift and up to B1F", walk=(20, 24),
         inputs=f"UP*{hold(1)}, wait 300, UP*12, wait 30, LEFT*12, wait 30, LEFT*12, wait 30, UP*12, wait 30, A*4, wait 90, "
         "UP*4, wait 30, UP*4, wait 30, A*4, wait 400, RIGHT*12, wait 30, RIGHT*12, wait 30, DOWN*12, wait 30, "
         "DOWN*12, wait 30, DOWN*30, wait 300", expect=dict(map="RocketHideout_B1F_Frlg")),
    dict(name="hideout-b1f-grunt-lift", state=FRESH, what="West from the lift into the line of the grunt who watches "
         "it: he battles", walk=(22, 26), inputs=f"LEFT*{hold(1)}, wait 200, " + A(60) + B(8) + "wait 300",
         expect=dict(map="RocketHideout_B1F_Frlg", xy=(21, 26))),
    dict(name="hideout-b1f-grunt-east", state=FRESH, what="Up the corridor to the east room and into the line of the "
         "grunt at its door: he battles", walk=(22, 13), inputs=f"UP*{hold(1)}, wait 200, " + A(60) + B(8) + "wait 300",
         expect=dict(map="RocketHideout_B1F_Frlg", xy=(22, 12))),
    dict(name="hideout-out", what="Up through the middle room and the stairs back up into the Game Corner",
         walk=(13, 2), inputs="LEFT*12, wait 20, LEFT*30, wait 300", expect=dict(map="CeladonCity_GameCorner_Frlg")),
    dict(name="game-corner-out", what="Down past the slot machines and out to Celadon", via=[(13, 4), (14, 5), (14, 11)],
         walk=(9, 13), inputs="DOWN*20, wait 300", expect=dict(map="CeladonCity_Frlg", xy=(28, 30))),
    dict(name="celadon-mansion", what="Into Celadon Mansion", walk=(25, 19), inputs=f"UP*{hold(1)}, wait 250",
         expect=dict(map="CeladonCity_Condominiums_1F_Frlg")),
    dict(name="tea", what="Up to the old woman with the Meowth: she gives you Tea (Saffron's thirsty guards will let "
         "you by for it)", walk=(2, 8), inputs="DOWN*4, wait 20, " + A(10) + B(4),
         expect=dict(map="CeladonCity_Condominiums_1F_Frlg", flags={"FLAG_GOT_TEA": True})),
    dict(name="celadon-mansion-out", what="Back out to the boulevard", walk=(12, 17),
         inputs=f"DOWN*{hold(1)}, wait 20, DOWN*20, wait 250", expect=dict(map="CeladonCity_Frlg")),
    dict(name="route7-back", what="East along the boulevard onto Route 7", walk=(59, 21), inputs=f"RIGHT*{hold(1)}, wait 200",
         expect=dict(map="Route7_Frlg")),
    dict(name="route7-hut", what="Into the Underground Path's west hut", walk=(9, 10), inputs=f"UP*{hold(1)}, wait 250",
         expect=dict(map="UndergroundPath_WestEntrance_Frlg")),
    dict(name="ew-tunnel-back", what="Down the hut's stairs into the tunnel", walk=(12, 9),
         inputs=f"UP*{hold(1)}, wait 20, RIGHT*20, wait 250", expect=dict(map="UndergroundPath_EastWestTunnel_Frlg")),
    dict(name="ew-tunnel-east", what="Along the tunnel to its east stairs and up into the east hut", walk=(76, 5),
         inputs=f"UP*{hold(1)}, wait 20, RIGHT*20, wait 250", expect=dict(map="UndergroundPath_EastEntrance_Frlg")),
    dict(name="route8-back", what="Out of the east hut onto Route 8", walk=(13, 11),
         inputs=f"DOWN*{hold(1)}, wait 20, DOWN*20, wait 250", expect=dict(map="Route8_Frlg", xy=(18, 13))),
    dict(name="lavender-back", what="East along Route 8's road into Lavender", walk=(59, 14),
         inputs=f"RIGHT*{hold(1)}, wait 200", expect=dict(map="LavenderTown_Frlg", xy=(0, 10))),
    dict(name="pokemon-tower", what="Across Lavender into the Pokémon Tower", walk=(29, 9), inputs=f"UP*{hold(1)}, wait 250",
         expect=dict(map="PokemonTower_1F_Frlg")),
    dict(name="tower-2f", what="Up the hall to the stairs and up to 2F", walk=(17, 9),
         inputs=f"RIGHT*{hold(1)}, wait 20, RIGHT*30, wait 300", expect=dict(map="PokemonTower_2F_Frlg", xy=(18, 10))),
    dict(name="tower-rival", state=FRESH, what="Up 2F's east side and west under the rival: he turns, battles, and "
         "leaves", walk=(17, 6), inputs=f"LEFT*{hold(1)}, wait 200, " + A(160) + B(12) + "wait 400",
         expect=dict(map="PokemonTower_2F_Frlg", xy=(16, 6), vars={"VAR_MAP_SCENE_POKEMON_TOWER_2F": 1})),
    dict(name="tower-3f", what="West along 2F's north hall and down to the stairs up to 3F",
         inputs="LEFT*156, wait 6, DOWN*28, wait 6, LEFT*28, wait 6, DOWN*12, wait 20, DOWN*12, wait 20, LEFT*30, wait 300",
         expect=dict(map="PokemonTower_3F_Frlg", xy=(4, 10))),
    dict(name="tower-4f", what="Round 3F's west room, up its middle and east along the north hall (in no channeler's "
         "sight) to the stairs up to 4F",
         inputs="DOWN*60, wait 6, RIGHT*44, wait 6, UP*108, wait 6, RIGHT*172, wait 6, DOWN*28, wait 20, DOWN*12, wait 20, "
         "RIGHT*30, wait 300", expect=dict(map="PokemonTower_4F_Frlg", xy=(18, 10))),
    dict(name="tower-5f", what="Through 4F's rooms (in no channeler's sight) to the stairs up to 5F",
         inputs="DOWN*12, wait 6, LEFT*28, wait 6, UP*60, wait 6, LEFT*12, wait 6, UP*12, wait 6, LEFT*60, wait 6, "
         "UP*44, wait 6, LEFT*28, wait 6, DOWN*92, wait 6, LEFT*44, wait 6, DOWN*12, wait 6, LEFT*12, wait 20, LEFT*12, "
         "wait 20, LEFT*30, wait 300", expect=dict(map="PokemonTower_5F_Frlg", xy=(4, 10))),
    dict(name="tower-ruth", state=FRESH, what="Up 5F's west side and east along its north hall into the channeler Ruth's "
         "line (every way east crosses it): she battles", inputs=f"UP*60, wait 6, RIGHT*92, wait 20, RIGHT*{hold(1)}, "
         "wait 200, " + A(60) + B(8) + "wait 300", expect=dict(map="PokemonTower_5F_Frlg", xy=(11, 6))),
    dict(name="tower-purified", what="Down into the middle room's purified zone: the team is healed",
         walk=(13, 9), inputs=f"LEFT*{hold(1)}, wait 150, " + B(3),
         expect=dict(map="PokemonTower_5F_Frlg", xy=(12, 9))),
    dict(name="tower-karina", state=FRESH, what="West out of the zone and down into the channeler Karina's line (the way "
         "to the east stairs runs past her): she battles", walk=(8, 11),
         inputs=f"DOWN*{hold(1)}, wait 200, " + A(60) + B(8) + "wait 300", expect=dict(map="PokemonTower_5F_Frlg", xy=(8, 12))),
    dict(name="tower-6f", what="East along 5F's south rooms (in no channeler's sight) to the stairs up to 6F",
         inputs="DOWN*12, wait 6, RIGHT*76, wait 6, UP*12, wait 6, RIGHT*28, wait 6, UP*12, wait 6, RIGHT*44, wait 6, "
         "UP*12, wait 20, RIGHT*30, wait 300", expect=dict(map="PokemonTower_6F_Frlg", xy=(18, 10))),
    dict(name="tower-jennifer", state=FRESH, what="Up 6F's east side into the channeler Jennifer's line (the way west "
         "crosses it): she battles", inputs=f"UP*28, wait 6, LEFT*28, wait 6, UP*12, wait 20, UP*{hold(1)}, wait 200, "
         + A(60) + B(8) + "wait 300", expect=dict(map="PokemonTower_6F_Frlg", xy=(16, 6))),
    dict(name="tower-emilia", state=FRESH, what="Round the north hall and down the middle room into the channeler "
         "Emilia's line (the way on to the west rooms crosses it): she battles",
         inputs=f"UP*28, wait 6, LEFT*60, wait 6, DOWN*44, wait 6, LEFT*28, wait 20, LEFT*{hold(1)}, wait 200, "
         + A(60) + B(8) + "wait 300", expect=dict(map="PokemonTower_6F_Frlg", xy=(9, 7))),
    dict(name="marowak-ghost", state=FRESH, what="Round the west rooms to the stairs up; the ghost blocks them: with the "
         "Silph Scope it's Cubone's mother, Marowak; beat it and its spirit is calmed",
         inputs=f"DOWN*12, wait 6, LEFT*44, wait 6, DOWN*60, wait 6, RIGHT*76, wait 6, DOWN*28, wait 20, DOWN*{hold(1)}, "
         "wait 200, " + A(60) + B(10) + "wait 300",
         expect=dict(map="PokemonTower_6F_Frlg", xy=(11, 15), vars={"VAR_MAP_SCENE_POKEMON_TOWER_6F": 1})),
    dict(name="tower-7f", what="Up the stairs to the top floor", inputs="DOWN*12, wait 30, LEFT*30, wait 300",
         expect=dict(map="PokemonTower_7F_Frlg", xy=(11, 16))),
    dict(name="tower-grunt1", state=FRESH, what="Up the hall into the first Rocket's line: he battles, then runs off",
         inputs=f"UP*{hold(5)}, wait 20, UP*{hold(1)}, wait 200, " + A(60) + B(8) + "wait 400",
         expect=dict(map="PokemonTower_7F_Frlg", xy=(11, 10))),
    dict(name="tower-grunt2", state=FRESH, what="On up into the second one's: he battles, then runs off",
         inputs=f"UP*{hold(1)}, wait 20, UP*{hold(1)}, wait 200, " + A(60) + B(8) + "wait 400",
         expect=dict(map="PokemonTower_7F_Frlg", xy=(11, 8))),
    dict(name="tower-grunt3", state=FRESH, what="And the third one's: he battles, then runs off",
         inputs=f"UP*{hold(1)}, wait 20, UP*{hold(1)}, wait 200, " + A(60) + B(8) + "wait 400",
         expect=dict(map="PokemonTower_7F_Frlg", xy=(11, 6))),
    dict(name="mr-fuji", what="Up to Mr. Fuji: he thanks you and goes home, and you with him",
         inputs=f"UP*{hold(1)}, wait 20, UP*4, wait 20, " + A(12) + "wait 400",
         expect=dict(map="LavenderTown_VolunteerPokemonHouse_Frlg", flags={"FLAG_RESCUED_MR_FUJI": True})),
    dict(name="poke-flute", what="Up to Mr. Fuji in his house: he gives you the Poké Flute", walk=(3, 4),
         inputs="UP*4, wait 20, " + A(10) + B(4),
         expect=dict(map="LavenderTown_VolunteerPokemonHouse_Frlg", flags={"FLAG_GOT_POKE_FLUTE": True})),
    # Snorlax, Routes 12 to 15 and Fuchsia
    dict(name="fuji-house-out", what="Out of Mr. Fuji's house", walk=(4, 6), inputs=f"DOWN*{hold(1)}, wait 20, DOWN*20, wait 250",
         expect=dict(map="LavenderTown_Frlg")),
    dict(name="route12", what="Down Lavender's south road onto Route 12", walk=(13, 31), inputs=f"DOWN*{hold(1)}, wait 200",
         expect=dict(map="Route12_Frlg")),
    dict(name="route12-gate", what="Down Route 12's lane into its gatehouse", walk=(11, 9),
         inputs=f"DOWN*{hold(1)}, wait 20, DOWN*20, wait 250",
         expect=dict(map="Route12_NorthEntrance_1F_Frlg", xy=(5, 2))),
    dict(name="route12-bridge", what="Through the gatehouse and out of its south door onto the bridge", walk=(5, 10),
         inputs=f"DOWN*{hold(1)}, wait 20, DOWN*20, wait 250", expect=dict(map="Route12_Frlg", xy=(11, 14))),
    dict(name="snorlax", state=FRESH, what="Down the Silence Bridge (its middle lane, past the fishers' lines) to the "
         "sleeping Snorlax; play the Poké Flute: it wakes and battles, and is gone", via=[(13, 15), (13, 39)],
         walk=(17, 47), inputs="DOWN*4, wait 20, " + A(80) + B(10) + "wait 300",
         expect=dict(map="Route12_Frlg", xy=(17, 47), flags={"FLAG_WOKE_UP_ROUTE_12_SNORLAX": True})),
    # Routes 12 to 15 are long and full of trainers: their walks were planned on the maps off every trainer's line of
    # sight (and off anywhere a wandering one can stand and see), hopping the ledges, one key at a time
    dict(name="route13", what="On down Route 12 (past where Snorlax slept, by the fishing house) onto Route 13",
         inputs="DOWN*316, wait 6, RIGHT*60, wait 6, DOWN*92, wait 6, RIGHT*44, wait 6, DOWN*92, wait 20, "
         "DOWN*30, wait 200", expect=dict(map="Route13_Frlg", xy=(89, 1))),
    dict(name="route14", what="Down Route 13's coast road and west along it (round the birdkeepers and the beauties) "
         "onto Route 14",
         inputs="DOWN*268, wait 6, LEFT*140, wait 6, DOWN*12, wait 6, LEFT*76, wait 6, DOWN*12, wait 6, LEFT*188, "
         "wait 6, DOWN*76, wait 6, LEFT*636, wait 6, DOWN*92, wait 6, LEFT*12, wait 20, DOWN*30, wait 200",
         expect=dict(map="Route14_Frlg", xy=(18, 1))),
    dict(name="route14-tree", what="Down Route 14 to the tree across its east lane; cut it and walk through",
         via=[(18, 9), (5, 9), (5, 12), (19, 12)], walk=(19, 15),
         inputs="DOWN*4, wait 30, " + A(4, 130) + f"wait 300, DOWN*{hold(2)}, wait 30",
         expect=dict(map="Route14_Frlg", xy=(19, 17))),
    dict(name="route14-ledge", what="On down the lane and west to the long ledge; hop it",
         via=[(19, 19), (18, 19), (18, 23), (11, 23)], walk=(11, 32), inputs=f"DOWN*{hold(1)}, wait 60",
         expect=dict(map="Route14_Frlg", xy=(11, 34))),
    dict(name="route15", what="Down Route 14's south fields and west onto Route 15",
         via=[(11, 40), (10, 40), (10, 41), (9, 41), (9, 51)], walk=(0, 51), inputs="LEFT*30, wait 200",
         expect=dict(map="Route15_Frlg", xy=(78, 15))),
    dict(name="route15-gate", what="West along Route 15 (round the bikers' and beauties' lines) into its west "
         "gatehouse (along the south lane: the road's Volbeat and Illumise patrol it, and its Hoppip wander anywhere)",
         via=[(78, 17), (21, 17), (21, 8), (19, 8), (19, 5)], walk=(17, 5), inputs=f"LEFT*{hold(1)}, wait 20, LEFT*20, wait 250",
         expect=dict(map="Route15_WestEntrance_1F_Frlg")),
    dict(name="route15-gate-out", what="Through the gatehouse and out of its west door", walk=(2, 6),
         inputs=f"LEFT*{hold(1)}, wait 20, LEFT*20, wait 250", expect=dict(map="Route15_Frlg", xy=(9, 5))),
    dict(name="fuchsia", what="West along the lane into Fuchsia", walk=(0, 5), inputs="LEFT*30, wait 200",
         expect=dict(map="FuchsiaCity_Frlg", xy=(46, 21))),
    dict(name="fuchsia-gym", what="Across Fuchsia into Koga's Gym", walk=(5, 32), inputs=f"UP*{hold(1)}, wait 250",
         expect=dict(map="FuchsiaCity_Gym_Frlg")),
    dict(name="koga", state=FRESH, what="Up the middle of the Gym (between the two jugglers' lines, along the invisible "
         "walls) into Koga's room; face him and beat him: the Soul Badge (Surf can be used outside battle)",
         via=[(8, 16)], walk=(7, 14), inputs="UP*4, wait 20, " + A(120) + B(12) + "wait 300",
         expect=dict(map="FuchsiaCity_Gym_Frlg", xy=(7, 14), flags={"FLAG_BADGE05_GET": True})),
    dict(name="leave-fuchsia-gym", what="Back down and out of the Gym", via=[(8, 16)], walk=(7, 21),
         inputs="DOWN*20, wait 300", expect=dict(map="FuchsiaCity_Frlg", xy=(5, 32))),
    # The Safari Zone (FireRed's own areas): Centre, then East, North and West in turn (the Centre's west half and the
    # North are only reached that way round). A checkpoint's reload ends Safari mode, as loading a save does (the game
    # clears it then), so past the gate these steps check the paths, not the 600-step ticket: the walk is about 270
    # steps, inside one
    dict(name="safari-entrance", what="Up Fuchsia's west lane (a tree to cut closes the middle one) and into the "
         "Safari Zone's gate", via=[(10, 32), (10, 20)], walk=(23, 7),
         inputs=f"UP*{hold(1)}, wait 250", expect=dict(map="FuchsiaCity_SafariZone_Entrance_Frlg")),
    dict(name="safari-zone", what="Up to the counter: pay ₽500 for 30 Safari Balls and go in",
         walk=(4, 4), inputs=f"UP*{hold(1)}, wait 60, " + A(10) + "wait 300",
         expect=dict(map="SafariZone_Center_Frlg", xy=(26, 30))),
    dict(name="safari-east", what="Up the Centre's east side and out of its east gate into the East area",
         via=[(26, 21), (32, 21), (32, 19), (34, 19), (34, 16)], walk=(42, 16), inputs="RIGHT*30, wait 250",
         expect=dict(map="SafariZone_East_Frlg", xy=(8, 27))),
    dict(name="safari-north", what="Round the East area's meadows and out of its north-west gate into the North area",
         via=[(14, 27), (14, 28), (33, 28), (33, 26), (36, 26), (36, 24), (30, 24), (30, 26), (24, 26), (24, 11),
              (31, 11), (31, 13), (35, 13), (35, 7), (27, 7), (27, 8), (21, 8), (21, 10)], walk=(9, 10),
         inputs="LEFT*30, wait 250", expect=dict(map="SafariZone_North_Frlg")),
    dict(name="safari-west", what="Across the North area (round its ponds) and down its south-west gate into the West "
         "area", walk=(11, 33), inputs="DOWN*30, wait 250", expect=dict(map="SafariZone_West_Frlg")),
    dict(name="gold-teeth", what="Down the West area to the item by the rocks: the Warden's Gold Teeth", walk=(28, 15),
         inputs="UP*4, wait 20, " + A(4) + B(2),
         expect=dict(map="SafariZone_West_Frlg", xy=(28, 15), flags={"FLAG_HIDE_SAFARI_ZONE_WEST_GOLD_TEETH": True})),
    dict(name="secret-house", what="West to the secret house in the corner", walk=(12, 8), inputs=f"UP*{hold(1)}, wait 250",
         expect=dict(map="SafariZone_SecretHouse_Frlg")),
    dict(name="hm03", what="Up to the man inside: for reaching it, HM03 (Surf)", walk=(6, 6),
         inputs="UP*4, wait 20, " + A(16) + B(4), expect=dict(map="SafariZone_SecretHouse_Frlg", flags={"FLAG_GOT_HM03": True})),
    dict(name="secret-house-out", what="Out of the secret house", walk=(4, 8), inputs="DOWN*20, wait 250",
         expect=dict(map="SafariZone_West_Frlg")),
    dict(name="safari-back-north", what="Back up the West area and out of its north gate into the North area",
         via=[(12, 10), (19, 10), (19, 7), (29, 7), (29, 6)], walk=(31, 6), inputs="UP*30, wait 250",
         expect=dict(map="SafariZone_North_Frlg")),
    dict(name="safari-back-east", what="Across the North area to its east gate and into the East area",
         via=[(11, 16), (12, 16), (12, 7), (34, 7), (34, 12), (24, 12), (24, 20), (22, 20), (22, 28), (24, 28), (24, 23),
              (30, 23), (30, 32)], walk=(47, 32), inputs="RIGHT*30, wait 250", expect=dict(map="SafariZone_East_Frlg")),
    dict(name="safari-back-centre", what="Round the East area to its south-west gate and back into the Centre",
         via=[(9, 9), (18, 9), (18, 7), (29, 7), (29, 8), (35, 8), (35, 13), (32, 13), (32, 11), (25, 11), (25, 22),
              (24, 22), (24, 26), (29, 26), (29, 24), (36, 24), (36, 28), (17, 28), (17, 27)], walk=(9, 27),
         inputs="LEFT*30, wait 250", expect=dict(map="SafariZone_Center_Frlg")),
    dict(name="safari-out", what="Down the Centre and out to the gate", via=[(42, 29)], walk=(26, 29),
         inputs="DOWN*30, wait 250", expect=dict(map="FuchsiaCity_SafariZone_Entrance_Frlg")),
    dict(name="safari-gate-out", what="Down past the counter and out to Fuchsia (a reload in the Zone ended Safari "
         "mode, so the counter thinks you're coming in and asks again: no thanks)",
         inputs="DOWN*12, wait 60, " + A(3, 120) + "DOWN*4, wait 30, A*4, wait 120, " + A(2, 120) + "wait 60, "
         "DOWN*12, wait 30, DOWN*12, wait 30, DOWN*12, wait 30, DOWN*30, wait 250",
         expect=dict(map="FuchsiaCity_Frlg", xy=(23, 7))),
    dict(name="wardens-house", what="Down Fuchsia's west lane and along the south road into the Warden's house",
         via=[(10, 20), (10, 32)], walk=(31, 32), inputs=f"UP*{hold(1)}, wait 250",
         expect=dict(map="FuchsiaCity_WardensHouse_Frlg")),
    dict(name="hm04", what="Give the Warden his Gold Teeth: he can talk again, and gives HM04 (Strength)", walk=(3, 6),
         inputs="UP*4, wait 20, " + A(20) + B(4), expect=dict(map="FuchsiaCity_WardensHouse_Frlg", flags={"FLAG_GOT_HM04": True})),
    dict(name="wardens-house-out", what="Out of the Warden's house", walk=(6, 8), inputs=f"DOWN*{hold(1)}, wait 20, DOWN*20, wait 250",
         expect=dict(map="FuchsiaCity_Frlg", xy=(31, 32))),
    # Saffron: back north the long way (Routes 15 to 12 and Lavender; Cycling Road needs a bike) to Route 8's gate,
    # whose guard lets you by for the Tea
    dict(name="fuchsia-east", what="Up Fuchsia's east lane onto Route 15", via=[(40, 32), (40, 28), (41, 28), (41, 20)],
         walk=(47, 20), inputs="RIGHT*30, wait 200", expect=dict(map="Route15_Frlg")),
    dict(name="route15-gate-east", what="Into Route 15's west gatehouse", walk=(8, 5), inputs=f"RIGHT*{hold(1)}, wait 20, "
         "RIGHT*20, wait 250", expect=dict(map="Route15_WestEntrance_1F_Frlg")),
    dict(name="route15-east", what="Through it and out of its east door", walk=(10, 6),
         inputs=f"RIGHT*{hold(1)}, wait 20, RIGHT*20, wait 250", expect=dict(map="Route15_Frlg")),
    dict(name="route14-back", what="East along Route 15's south lane (off the road the Volbeat and Illumise patrol) "
         "onto Route 14", via=[(19, 5), (19, 8), (21, 8), (21, 17), (78, 17)], walk=(79, 15), inputs="RIGHT*30, wait 200",
         expect=dict(map="Route14_Frlg")),
    dict(name="route14-tree-back", what="Up Route 14's fields (round the ledges) to the tree on the east lane; cut it "
         "and walk through", via=[(1, 50), (2, 50), (2, 32), (4, 32), (4, 29), (7, 29), (7, 20), (18, 20), (18, 18),
         (19, 18)], walk=(19, 17), inputs="UP*4, wait 30, " + A(4, 130) + f"wait 300, UP*{hold(2)}, wait 30",
         expect=dict(map="Route14_Frlg", xy=(19, 15))),
    dict(name="route13-back", what="On up Route 14 onto Route 13", via=[(19, 11), (5, 11), (5, 9), (16, 9), (16, 0)],
         walk=(18, 0), inputs="UP*30, wait 200", expect=dict(map="Route13_Frlg")),
    dict(name="route12-back", what="East along Route 13 (off every trainer's line) and up onto Route 12",
         via=[(22, 21), (31, 21), (31, 20), (32, 20), (32, 19), (63, 19), (63, 16), (68, 16), (68, 14), (86, 14), (86, 0)],
         walk=(89, 0), inputs="UP*30, wait 200", expect=dict(map="Route12_Frlg")),
    dict(name="route12-snorlax-spot", state=FRESH, what="Up Route 12 to where Snorlax slept, through it and west "
         "along the bank (the rocker Luca walks round there and may see you: then he battles)",
         via=[(24, 64), (18, 64), (18, 50)], walk=(17, 49),
         inputs=f"UP*{hold(2)}, wait 30, LEFT*{hold(5)}, wait 60, " + A(40) + B(8) + "wait 100",
         expect=dict(map="Route12_Frlg")),
    dict(name="route12-north", what="Up the Silence Bridge (its middle lane) to the gatehouse",
         via=[(12, 44), (13, 40), (13, 14)], walk=(12, 14), inputs="UP*30, wait 250",
         expect=dict(map="Route12_NorthEntrance_1F_Frlg")),
    dict(name="route12-gate-back", what="Through the gatehouse and out of its north door", walk=(5, 2),
         inputs=f"UP*{hold(1)}, wait 20, UP*20, wait 250", expect=dict(map="Route12_Frlg")),
    dict(name="lavender-again", what="Up the lane into Lavender", walk=(13, 0), inputs="UP*30, wait 200",
         expect=dict(map="LavenderTown_Frlg")),
    dict(name="route8-again", what="West along Lavender's street onto Route 8", via=[(13, 10)], walk=(0, 10),
         inputs="LEFT*30, wait 200", expect=dict(map="Route8_Frlg")),
    dict(name="route8-gate", what="West along Route 8 to Saffron's east gate", walk=(11, 13), inputs=f"UP*{hold(1)}, wait 250",
         expect=dict(map="Route8_WestEntrance_Frlg")),
    dict(name="saffron-guard", what="Past the guard: he's thirsty; give him the Tea and he lets you by",
         inputs=f"LEFT*{hold(5)}, wait 100, " + A(12) + B(4) + "wait 100",
         expect=dict(map="Route8_WestEntrance_Frlg", vars={"VAR_MAP_SCENE_ROUTE5_ROUTE6_ROUTE7_ROUTE8_GATES": 1})),
    dict(name="saffron", what="On through the gate into Saffron (its exit mat's lower half)", walk=(2, 5), inputs=f"LEFT*{hold(1)}, wait 20, LEFT*20, wait 250",
         expect=dict(map="SaffronCity_Frlg", xy=(56, 22))),
    # Silph Co. (FireRed's own floors): up the stairs to 5F for the Card Key, its doors, the pads up to 7F (the rival)
    # and 11F (Giovanni)
    dict(name="silph-co", what="Across Saffron (the Rocket at Silph's door is asleep now Mr. Fuji is safe) into Silph Co.",
         walk=(38, 18), inputs=f"UP*{hold(1)}, wait 250", expect=dict(map="SilphCo_1F_Frlg")),
    dict(name="silph-2f", what="Up the hall to the stairs and up to 2F", walk=(31, 3),
         inputs=f"UP*{hold(1)}, wait 20, RIGHT*30, wait 300", expect=dict(map="SilphCo_2F_Frlg", xy=(30, 2))),
    dict(name="silph-3f", what="Along to the next stairs and up to 3F", walk=(28, 3),
         inputs=f"UP*{hold(1)}, wait 20, LEFT*30, wait 300", expect=dict(map="SilphCo_3F_Frlg", xy=(28, 2))),
    dict(name="silph-4f", what="And up to 4F", walk=(30, 3),
         inputs=f"UP*{hold(1)}, wait 20, RIGHT*30, wait 300", expect=dict(map="SilphCo_4F_Frlg", xy=(30, 2))),
    dict(name="silph-5f", what="And up to 5F", walk=(28, 3),
         inputs=f"UP*{hold(1)}, wait 20, LEFT*30, wait 300", expect=dict(map="SilphCo_5F_Frlg", xy=(28, 2))),
    dict(name="silph-beau", state=FRESH, what="West along 5F's north hall past the scientist Beau, who walks about "
         "there (a door shuts the middle way and a Rocket the east one): if he sees you he battles",
         walk=(14, 4), inputs=f"LEFT*{hold(5)}, wait 60, DOWN*{hold(4)}, wait 60, " + A(120) + B(8) + "wait 100",
         expect=dict(map="SilphCo_5F_Frlg")),
    dict(name="silph-9f-pad", what="Down the west rooms to the pad by the bottom hall's door: it takes you up to 9F "
         "(a walk must never end on a pad: its checkpoint is saved before the pad takes you)", walk=(10, 19),
         inputs=f"DOWN*{hold(1)}, wait 200", expect=dict(map="SilphCo_9F_Frlg", xy=(22, 18))),
    dict(name="silph-5f-grunt", state=FRESH, what="Off the pad and back on: it brings you down into 5F's bottom hall; "
         "step on into the Rocket's line by its door: he battles",
         inputs=f"LEFT*{hold(1)}, wait 30, RIGHT*{hold(1)}, wait 200, DOWN*{hold(1)}, wait 200, " + A(60) + B(8) + "wait 300",
         expect=dict(map="SilphCo_5F_Frlg", xy=(10, 21))),
    dict(name="card-key", what="East along the bottom hall to the Card Key", inputs=f"RIGHT*{hold(11)}, wait 30, RIGHT*4, "
         "wait 20, " + A(4) + B(2),
         expect=dict(map="SilphCo_5F_Frlg", xy=(21, 21), flags={"FLAG_HIDE_SILPH_CO_5F_CARD_KEY": True})),
    dict(name="silph-back-9f", what="Back along the hall and up the pad to 9F", walk=(10, 21),
         inputs=f"UP*{hold(1)}, wait 200", expect=dict(map="SilphCo_9F_Frlg", xy=(22, 18))),
    dict(name="silph-9f-door4", what="Up to 9F's first locked door; the Card Key opens it", via=[(20, 18), (20, 14)],
         walk=(21, 14), inputs="UP*4, wait 20, " + A(3) + B(2),
         expect=dict(map="SilphCo_9F_Frlg", flags={"FLAG_SILPH_9F_DOOR_4": True})),
    dict(name="silph-9f-door3", what="Through it and up to the next; the Card Key opens it too", walk=(21, 8),
         inputs="UP*4, wait 20, " + A(3) + B(2), expect=dict(map="SilphCo_9F_Frlg", flags={"FLAG_SILPH_9F_DOOR_3": True})),
    dict(name="silph-9f-grunt", state=FRESH, what="Round the north hall and down the west corridor into a Rocket's line: "
         "he battles", via=[(21, 5), (15, 5)], walk=(15, 14), inputs=f"DOWN*{hold(1)}, wait 200, " + A(60) + B(8) + "wait 300",
         expect=dict(map="SilphCo_9F_Frlg", xy=(15, 15))),
    dict(name="silph-9f-door2", what="The door to the west rooms: the Card Key opens it", via=[(14, 15)], walk=(14, 16),
         inputs="LEFT*4, wait 20, " + A(3) + B(2), expect=dict(map="SilphCo_9F_Frlg", flags={"FLAG_SILPH_9F_DOOR_2": True})),
    dict(name="silph-9f-door1", what="Through the west rooms to the last door: the Card Key opens it", via=[(6, 16), (6, 10)],
         walk=(4, 10), inputs="LEFT*4, wait 20, " + A(3) + B(2), expect=dict(map="SilphCo_9F_Frlg", flags={"FLAG_SILPH_9F_DOOR_1": True})),
    dict(name="silph-9f-grunt2", state=FRESH, what="Through it into the line of the Rocket guarding the pad: he battles",
         inputs=f"LEFT*{hold(3)}, wait 200, " + A(60) + B(8) + "wait 300", expect=dict(map="SilphCo_9F_Frlg")),
    dict(name="silph-3f-pad", what="Up the west side to the pad in the corner: it takes you down to 3F", via=[(0, 10), (0, 4)],
         walk=(8, 4), inputs=f"RIGHT*{hold(1)}, wait 200", expect=dict(map="SilphCo_3F_Frlg", xy=(2, 14))),
    dict(name="silph-3f-door", what="East to 3F's locked door; the Card Key opens it", via=[(8, 14)], walk=(8, 13),
         inputs="RIGHT*4, wait 20, " + A(3) + B(2), expect=dict(map="SilphCo_3F_Frlg", flags={"FLAG_SILPH_3F_DOOR_1": True})),
    dict(name="silph-7f", what="Through it to the pad in the middle room: it takes you up to 7F", walk=(13, 13),
         inputs=f"DOWN*{hold(1)}, wait 200", expect=dict(map="SilphCo_7F_Frlg", xy=(5, 4))),
    dict(name="silph-rival", state=FRESH, what="West off the pad: the rival is waiting there; he battles, then leaves",
         inputs=f"LEFT*{hold(3)}, wait 200, " + A(160) + B(12) + "wait 300",
         expect=dict(map="SilphCo_7F_Frlg", xy=(2, 4), vars={"VAR_MAP_SCENE_SILPH_CO_7F": 1})),
    dict(name="silph-11f", what="Round to the other pad: it takes you up to 11F", via=[(1, 5), (1, 7)], walk=(5, 7),
         inputs=f"DOWN*{hold(1)}, wait 200", expect=dict(map="SilphCo_11F_Frlg", xy=(2, 5))),
    dict(name="silph-11f-grunt", state=FRESH, what="Down 11F's west side and east into the line of the Rocket at its "
         "foot: he battles", via=[(2, 13), (1, 13)], walk=(1, 18), inputs=f"RIGHT*{hold(1)}, wait 200, " + A(60) + B(8) +
         "wait 300", expect=dict(map="SilphCo_11F_Frlg", xy=(2, 18))),
    dict(name="silph-11f-door", what="East to the locked door below the boardroom; the Card Key opens it", walk=(5, 18),
         inputs="UP*4, wait 20, " + A(3) + B(2), expect=dict(map="SilphCo_11F_Frlg", flags={"FLAG_SILPH_11F_DOOR": True})),
    dict(name="giovanni-silph", state=FRESH, what="Up through it to Giovanni, who stops you: he battles, and Team "
         "Rocket leaves Silph Co.", inputs=f"UP*{hold(3)}, wait 200, " + A(140) + B(12) + "wait 400",
         expect=dict(map="SilphCo_11F_Frlg", xy=(5, 15), flags={"FLAG_HIDE_SAFFRON_ROCKETS": True},
                     vars={"VAR_MAP_SCENE_SILPH_CO_11F": 1})),
    dict(name="silph-back-7f", what="Back up the west side to the pad: down to 7F (the boardroom side of 11F has no other "
         "way out)", via=[(2, 13)], walk=(2, 6), inputs=f"UP*{hold(1)}, wait 200", expect=dict(map="SilphCo_7F_Frlg", xy=(5, 8))),
    dict(name="silph-back-3f", what="Over to the other pad: down to 3F", walk=(5, 5), inputs=f"UP*{hold(1)}, wait 200",
         expect=dict(map="SilphCo_3F_Frlg", xy=(13, 14))),
    dict(name="silph-3f-door2", what="East to 3F's other locked door; the Card Key opens it", walk=(19, 12),
         inputs="RIGHT*4, wait 20, " + A(3) + B(2), expect=dict(map="SilphCo_3F_Frlg", flags={"FLAG_SILPH_3F_DOOR_2": True})),
    dict(name="silph-3f-grunt", state=FRESH, what="Through it and up the corridor into the line of the Rocket across it: "
         "he battles", walk=(22, 10), inputs=f"UP*{hold(1)}, wait 200, " + A(60) + B(8) + "wait 300",
         expect=dict(map="SilphCo_3F_Frlg", xy=(22, 9))),
    dict(name="silph-down-2f", what="Up to the north hall and down the stairs to 2F", walk=(28, 3),
         inputs=f"UP*{hold(1)}, wait 20, LEFT*30, wait 300", expect=dict(map="SilphCo_2F_Frlg")),
    dict(name="silph-down-1f", what="Down again to the lobby", walk=(30, 3),
         inputs=f"UP*{hold(1)}, wait 20, RIGHT*30, wait 300", expect=dict(map="SilphCo_1F_Frlg")),
    dict(name="silph-out", what="Out of Silph Co. into Saffron, free of Rockets now", walk=(8, 19),
         inputs=f"DOWN*{hold(2)}, wait 300", expect=dict(map="SaffronCity_Frlg")),
    dict(name="saffron-gym", what="Across Saffron to Sabrina's Gym", walk=(17, 18), inputs=f"UP*{hold(1)}, wait 300",
         expect=dict(map="SaffronCity_Gym_Frlg", xy=(14, 23))),
    dict(name="gym-pad-se", what="The Gym is nine rooms joined by teleport pads. The entrance room's pad goes to the "
         "south-east room", walk=(18, 21), inputs=f"UP*{hold(1)}, wait 200",
         expect=dict(map="SaffronCity_Gym_Frlg", xy=(28, 23))),
    dict(name="gym-pad-ne", what="Under the psychic's line to the room's west pad: to the north-east room",
         via=[(27, 22), (21, 22)], walk=(21, 20), inputs=f"LEFT*{hold(1)}, wait 200",
         expect=dict(map="SaffronCity_Gym_Frlg", xy=(28, 4))),
    dict(name="gym-pad-nw", what="Under that room's psychic to its south-west pad: to the north-west room",
         via=[(28, 6)], walk=(20, 6), inputs=f"DOWN*{hold(1)}, wait 200",
         expect=dict(map="SaffronCity_Gym_Frlg", xy=(0, 4))),
    dict(name="gym-pad-centre", what="Down the west wall to that room's south-west pad: into Sabrina's room",
         walk=(0, 6), inputs=f"DOWN*{hold(1)}, wait 200", expect=dict(map="SaffronCity_Gym_Frlg", xy=(18, 15))),
    dict(name="sabrina", state=FRESH, what="Face Sabrina and beat her: the Marsh Badge and TM04",
         via=[(17, 14), (14, 14)], walk=(14, 12), inputs="UP*4, wait 20, " + A(120) + B(16) + "wait 300",
         expect=dict(map="SaffronCity_Gym_Frlg", xy=(14, 12),
                     flags={"FLAG_BADGE06_GET": True, "FLAG_GOT_TM04_FROM_SABRINA": True})),
    dict(name="gym-back-nw", what="The pads back out: Sabrina's room's pad to the north-west room", walk=(18, 14),
         inputs=f"DOWN*{hold(1)}, wait 200", expect=dict(map="SaffronCity_Gym_Frlg", xy=(0, 7))),
    dict(name="gym-back-ne", what="Its north-west pad: to the north-east room", walk=(0, 5),
         inputs=f"UP*{hold(1)}, wait 200", expect=dict(map="SaffronCity_Gym_Frlg", xy=(20, 7))),
    dict(name="gym-back-se", what="Along under the psychic to the north-east pad: to the south-east room",
         via=[(20, 6), (28, 6)], walk=(28, 5), inputs=f"UP*{hold(1)}, wait 200",
         expect=dict(map="SaffronCity_Gym_Frlg", xy=(20, 20))),
    dict(name="gym-back-entrance", what="Under the psychic to the south-east pad: back to the entrance",
         via=[(21, 22)], walk=(28, 22), inputs=f"DOWN*{hold(1)}, wait 200",
         expect=dict(map="SaffronCity_Gym_Frlg", xy=(18, 20))),
    dict(name="leave-saffron-gym", what="Out of the Gym", via=[(18, 21)], walk=(14, 22),
         inputs=f"DOWN*{hold(2)}, wait 300", expect=dict(map="SaffronCity_Frlg", xy=(17, 18))),
    # Cinnabar next. Without Fly the way there is the sea: down to Fuchsia by Routes 6, 11 and 12, then Surf
    dict(name="saffron-south", what="Down Saffron to its south gate (its guard drank the Tea too)",
         via=[(17, 38), (27, 38), (27, 44)], walk=(29, 44), inputs=f"DOWN*{hold(2)}, wait 250",
         expect=dict(map="Route6_NorthEntrance_Frlg")),
    dict(name="route6-again", what="Through the gate and out onto Route 6", walk=(4, 8),
         inputs=f"DOWN*{hold(2)}, wait 250",
         expect=dict(map="Route6_Frlg")),
    dict(name="vermilion-again", what="Down Route 6 into Vermilion", walk=(40, 31), inputs="DOWN*30, wait 200",
         expect=dict(map="VermilionCity_Frlg")),
    # Routes 16-18 (Cycling Road) need the Bicycle: the Bike Voucher from the Fan Club's chairman here, the bike
    # from Cerulean's Bike Shop
    dict(name="fan-club", what="Up Vermilion's street into the Pokémon Fan Club", via=[(32, 10)], walk=(16, 10),
         inputs=f"UP*{hold(1)}, wait 250", expect=dict(map="VermilionCity_PokemonFanClub_Frlg")),
    dict(name="bike-voucher", what="Round the table to the chairman; yes, you'd like to hear about his Pokémon: the "
         "Bike Voucher (he's talked to from his side: his chair is at another height from the floor behind him, so from "
         "above he doesn't answer)", via=[(3, 9), (3, 4)], walk=(4, 4),
         inputs="RIGHT*4, wait 20, " + A(16) + B(10),
         expect=dict(map="VermilionCity_PokemonFanClub_Frlg", flags={"FLAG_GOT_BIKE_VOUCHER": True})),
    dict(name="leave-fan-club", what="Back out of the Fan Club", via=[(3, 4), (3, 9)], walk=(5, 9),
         inputs=f"DOWN*{hold(2)}, wait 250", expect=dict(map="VermilionCity_Frlg", xy=(16, 10))),
    # Lt. Surge's Gym is behind a tree to cut, and Cut works outside battle from Misty's badge on: the walk past
    # Vermilion after the S.S. Anne came before that, so his badge is won here, on the way back through
    dict(name="vermilion-tree", what="Across Vermilion to the tree in front of the Gym's yard; cut it and walk through "
         "(in one step: a checkpoint's reload brings a cut tree back)",
         walk=(15, 14), inputs="DOWN*4, wait 30, " + A(4, 130) + f"wait 300, DOWN*{hold(2)}, wait 30",
         expect=dict(map="VermilionCity_Frlg", xy=(15, 16))),
    dict(name="vermilion-gym", what="Through the yard into Lt. Surge's Gym", via=[(14, 16), (14, 21)],
         walk=(10, 21), inputs=f"UP*{hold(1)}, wait 250", expect=dict(map="VermilionCity_Gym_Frlg")),
    # The switches are under two trash cans the game picks at random as the Gym loads (the second next to the first).
    # The check's play is the same every time, so they are too: loaded from the step before's checkpoint with this
    # step's state (the Repel and the team: setting state loads the map again) they are cans 6 and 1 (pae play --from
    # it with those --state and --show-var VAR_TEMP_0 --show-var VAR_TEMP_1). A walk would save a checkpoint and load
    # it again, picking others, so the step walks in its inputs, and both switches are in its one play (the first is
    # forgotten when the map loads). If a change before here moves them, read them again
    dict(name="surge-switches", state=FRESH, what="Along the bottom and up the west wall to trash can 6: the first "
         "switch. Up into Baily's line (he battles) to can 1: the second; the electric locks open",
         inputs=f"UP*{hold(4)}, wait 6, LEFT*{hold(5)}, wait 6, UP*{hold(2)}, wait 6, RIGHT*{hold(1)}, wait 20, "
         "UP*4, wait 20, A*4, wait 60, " + B(4) + f"LEFT*{hold(1)}, wait 6, UP*{hold(2)}, wait 120, " + A(40) + B(8) +
         f"wait 200, UP*{hold(1)}, wait 30, RIGHT*4, wait 20, A*4, wait 60, " + B(5),
         expect=dict(map="VermilionCity_Gym_Frlg", xy=(0, 10),
                     flags={"FLAG_FOUND_BOTH_VERMILION_GYM_SWITCHES": True})),
    dict(name="lt-surge", state=FRESH, what="Along the top row into Tucker's line (he battles) and up through the "
         "opened beams to Lt. Surge; beat him: the Thunder Badge",
         inputs=f"UP*{hold(1)}, wait 6, RIGHT*{hold(3)}, wait 6, UP*{hold(1)}, wait 6, RIGHT*{hold(1)}, wait 120, " +
         A(40) + B(8) + f"wait 200, UP*{hold(5)}, wait 6, RIGHT*{hold(1)}, wait 20, UP*4, wait 20, " + A(120) +
         B(16) + "wait 300", expect=dict(map="VermilionCity_Gym_Frlg", xy=(5, 3), flags={"FLAG_BADGE03_GET": True})),
    dict(name="leave-vermilion-gym", what="Back down through the beams and the west aisle and out of the Gym",
         inputs=f"LEFT*{hold(1)}, wait 6, DOWN*{hold(12)}, wait 6, RIGHT*{hold(1)}, wait 6, DOWN*{hold(3)}, wait 20, "
         f"DOWN*{hold(2)}, wait 250", expect=dict(map="VermilionCity_Frlg", xy=(10, 21))),
    dict(name="vermilion-tree-out", what="Round the yard to the tree (grown back); cut it and walk out",
         via=[(14, 21), (14, 16)], walk=(15, 16), inputs="UP*4, wait 30, " + A(4, 130) + f"wait 300, UP*{hold(2)}, wait 30",
         expect=dict(map="VermilionCity_Frlg", xy=(15, 14))),
    dict(name="route6-north", what="Up Vermilion's plaza onto Route 6", via=[(33, 12)], walk=(33, 0),
         inputs=f"UP*{hold(1)}, wait 200", expect=dict(map="Route6_Frlg", xy=(41, 31))),
    dict(name="route6-hut-again", what="Up Route 6's road into the Underground Path's hut", walk=(46, 12),
         inputs=f"UP*{hold(1)}, wait 250", expect=dict(map="UndergroundPath_SouthEntrance_Frlg", xy=(13, 12))),
    dict(name="tunnel-again", what="Down the hut's stairs into the tunnel", walk=(14, 9),
         inputs=f"UP*{hold(1)}, wait 20, LEFT*20, wait 250",
         expect=dict(map="UndergroundPath_NorthSouthTunnel_Frlg", xy=(2, 38))),
    dict(name="tunnel-north-again", what="Along the tunnel and up its north stairs", walk=(3, 5),
         inputs=f"UP*{hold(1)}, wait 20, LEFT*20, wait 250", expect=dict(map="UndergroundPath_NorthEntrance_Frlg", xy=(12, 8))),
    dict(name="route5-again", what="Out of the north hut onto Route 5", walk=(13, 11),
         inputs=f"DOWN*{hold(1)}, wait 20, DOWN*20, wait 250", expect=dict(map="Route5_Frlg", xy=(35, 25))),
    dict(name="cerulean-again", what="Up Route 5's road and through the neck into Cerulean", walk=(30, 0),
         inputs=f"UP*{hold(1)}, wait 200", expect=dict(map="CeruleanCity_Frlg", xy=(22, 50))),
    dict(name="bike-shop", what="Into the Bike Shop", walk=(10, 42), inputs=f"UP*{hold(1)}, wait 250",
         expect=dict(map="CeruleanCity_BikeShop_Frlg")),
    dict(name="bicycle", what="Up to the counter: the clerk takes the Bike Voucher for a Bicycle", walk=(7, 3),
         inputs="RIGHT*4, wait 20, " + A(10) + B(8),
         expect=dict(map="CeruleanCity_BikeShop_Frlg", flags={"FLAG_GOT_BICYCLE": True})),
    dict(name="leave-bike-shop", what="Back out of the Bike Shop (round the woman)", via=[(7, 7)], walk=(5, 7), inputs=f"DOWN*{hold(2)}, wait 250",
         expect=dict(map="CeruleanCity_Frlg")),
    dict(name="route5-south", what="Back down through Cerulean's neck onto Route 5", walk=(22, 50),
         inputs="DOWN*30, wait 200", expect=dict(map="Route5_Frlg")),
    dict(name="saffron-north-gate", what="Down Route 5's road into Saffron's north gate", via=[(30, 27), (26, 27), (26, 29)],
         walk=(24, 29), inputs=f"DOWN*{hold(2)}, wait 250", expect=dict(map="Route5_SouthEntrance_Frlg")),
    dict(name="saffron-from-north", what="Through the gate into Saffron (its mat's east half: backlog #6)", walk=(4, 8), inputs=f"DOWN*{hold(2)}, wait 250",
         expect=dict(map="SaffronCity_Frlg")),
    dict(name="saffron-west-gate", what="Down Saffron's avenue and up into its west gate (its doors face south)", via=[(29, 21)], walk=(2, 22),
         inputs=f"UP*{hold(2)}, wait 250", expect=dict(map="Route7_EastEntrance_Frlg")),
    dict(name="route7-west", what="Through the gate onto Route 7", walk=(2, 5), inputs=f"LEFT*{hold(2)}, wait 250",
         expect=dict(map="Route7_Frlg")),
    dict(name="celadon-west", what="West along Route 7 into Celadon", walk=(0, 10), inputs="LEFT*30, wait 200",
         expect=dict(map="CeladonCity_Frlg")),
    dict(name="route16", what="West along Celadon's boulevard onto Route 16", via=[(39, 20), (39, 21)], walk=(0, 21),
         inputs="LEFT*30, wait 200", expect=dict(map="Route16_Frlg")),
    dict(name="route16-snorlax", state=FRESH, what="West to the sleeping Snorlax in the gap; play the Poké Flute: it "
         "wakes and battles, and is gone", via=[(55, 24)], walk=(45, 24), inputs="LEFT*4, wait 20, " + A(80) + B(10) +
         "wait 300", expect=dict(map="Route16_Frlg", xy=(45, 24), flags={"FLAG_HIDE_ROUTE_16_SNORLAX": True})),
    # Cycling Road is by bike only. Getting on is the bag's Key Items (one pocket left of Items), the Bike two up
    # from the top (the last item: the list wraps round), Use. Riding goes 6 frames a block ("bike" walks)
    dict(name="cycling-road", what="Get on the Bicycle, ride west through the Cycling Road gatehouse's lower hall (the "
         "guard lets bikes by) and out of its west door onto Cycling Road (in one step: indoors, a checkpoint's reload "
         "puts you back on foot)",
         inputs="wait 20, START*4, wait 60, DOWN*4, wait 20, DOWN*4, wait 20, A*4, wait 120, LEFT*4, wait 60, "
         "UP*4, wait 30, UP*4, wait 30, A*4, wait 60, A*4, wait 200, LEFT*90, wait 300, LEFT*60, wait 300, LEFT*20, "
         "wait 300", expect=dict(map="Route16_Frlg", xy=(28, 24), vars={"VAR_MAP_SCENE_ROUTE16": 1})),
    dict(name="route17", what="Down Route 16's west side between the bikers' lines onto Route 17", bike=True,
         via=[(27, 24), (27, 27), (17, 27), (17, 28), (16, 28), (16, 43)], walk=(14, 43), inputs="DOWN*10, wait 200",
         expect=dict(map="Route17_Frlg")),
    dict(name="route18", what="Down the whole of Cycling Road onto Route 18: its slope carries you down; Jamal sees "
         "you on the way and battles (only A while you ride: a key held when a battle starts moves its menu)",
         repel=False, inputs="wait 30, DOWN*120, wait 30, " + A(80) + B(10) + "wait 600, DOWN*200, wait 250",
         expect=dict(map="Route18_Frlg")),
    dict(name="route18-gate", what="Ride up the shore and east along Route 18's road into its gatehouse, through it "
         "and out of its east door, and on into Fuchsia", repel=False,
         inputs=f"UP*{bike_hold(6)}, wait 20, RIGHT*{bike_hold(33)}, wait 30, RIGHT*20, wait 300, RIGHT*80, wait 300, "
         "RIGHT*20, wait 300, RIGHT*100, wait 250", expect=dict(map="FuchsiaCity_Frlg")),
    dict(name="route19", what="Down through Fuchsia's west walks and south road onto Route 19",
         via=[(6, 23), (7, 23), (7, 25), (8, 25), (8, 26), (9, 26), (9, 29), (10, 29), (10, 33), (19, 33), (19, 39)],
         walk=(24, 39), inputs="DOWN*30, wait 200",
         expect=dict(map="Route19_Frlg", xy=(12, 1))),
    dict(name="route19-surf", what="Down between the swimmers' lines to the beach; Surf from it (the Soul Badge lets "
         "Surf be used outside battle)", via=[(12, 9), (11, 9)], walk=(11, 15), inputs="DOWN*4, wait 30, " + A(3, 80) +
         "wait 200", expect=dict(map="Route19_Frlg", xy=(11, 16))),
    dict(name="route20", what="Surf south-west round the swimmers' lines onto Route 20", surf=True,
         via=[(11, 17), (8, 17), (8, 25), (4, 25), (4, 36), (3, 36), (3, 45)], walk=(0, 45), inputs="LEFT*30, wait 200",
         expect=dict(map="Route20_Frlg")),
    dict(name="cinnabar",
         what="West along Route 20, over the top of the Seafoam Islands, to Cinnabar Island", surf=True,
         via=[(117, 2), (72, 2), (72, 1), (49, 1), (49, 2)], walk=(0, 2), inputs="LEFT*2, wait 12, LEFT*12, wait 200",
         expect=dict(map="CinnabarIsland_Frlg")),
    dict(name="cinnabar-shore", what="Round the north of the island's east half to the town's shore, and ashore",
         surf=True, via=[(94, 5), (39, 5), (39, 6)], walk=(23, 6), inputs="LEFT*2, wait 12, LEFT*4, wait 100",
         expect=dict(map="CinnabarIsland_Frlg", xy=(22, 6))),
    dict(name="mansion", what="Along the top street into the Pokémon Mansion (the Gym next door is locked)",
         via=[(21, 6), (21, 5)], walk=(6, 5), inputs=f"UP*{hold(1)}, wait 250",
         expect=dict(map="PokemonMansion_1F_Frlg")),
    # The Mansion: its statues work one switch for all four floors, which opens one set of barriers and shuts
    # another. The walks were planned on the floors in both states, off every line of sight but Lewis's on B1F. pae
    # map path plans on a floor as it was built, so a walk through a barrier the switch opened is held in the inputs
    dict(name="mansion-2f", what="Up the hall to the stairs and up to 2F", via=[(8, 13)], walk=(9, 13),
         inputs="RIGHT*12, wait 30, RIGHT*30, wait 250", expect=dict(map="PokemonMansion_2F_Frlg", xy=(6, 14))),
    dict(name="mansion-3f", what="Round 2F's halls (off Arnie's line) to the north stairs and up to 3F",
         via=[(6, 17), (13, 17), (13, 13), (14, 13), (14, 12), (15, 12), (15, 6), (11, 6), (11, 5), (9, 5)],
         walk=(9, 4),
         inputs="UP*12, wait 30, RIGHT*30, wait 250", expect=dict(map="PokemonMansion_3F_Frlg", xy=(8, 3))),
    dict(name="mansion-3f-statue", what="Down to the statue in 3F's west room; press its secret switch: the barriers "
         "change on every floor", via=[(8, 6)], walk=(12, 6), inputs="UP*4, wait 20, " + A(3) + B(2),
         expect=dict(map="PokemonMansion_3F_Frlg", flags={"FLAG_POKEMON_MANSION_SWITCH_STATE": True})),
    dict(name="mansion-hole", what="Through the opened way east and down through the hole in the floor to 1F",
         via=[(12, 7), (15, 7), (15, 9)], walk=(17, 9),
         inputs=f"DOWN*{hold(5)}, wait 6, RIGHT*{hold(1)}, wait 6, DOWN*{hold(4)}, wait 250",
         expect=dict(map="PokemonMansion_1F_Frlg")),
    dict(name="mansion-b1f", what="Round 1F's south rooms to the stairs down to the basement",
         via=[(19, 23), (17, 23), (17, 29), (25, 29)], walk=(25, 28), inputs="UP*12, wait 30, LEFT*30, wait 250",
         expect=dict(map="PokemonMansion_B1F_Frlg", xy=(34, 29))),
    dict(name="mansion-lewis", state=FRESH, what="Up B1F's east side and west along the north hall, then down through "
         "the way the switch opened, where the burglar Lewis wanders: if he sees you he battles",
         via=[(32, 29), (32, 22), (29, 22), (29, 20)], walk=(22, 20),
         inputs=f"DOWN*{hold(6)}, wait 100, " + A(120) + B(12) + "wait 200", expect=dict(map="PokemonMansion_B1F_Frlg")),
    dict(name="mansion-b1f-statue", what="Round the table to the statue below it; press its switch: back as it was",
         via=[(23, 26)], walk=(23, 30), inputs=f"RIGHT*{hold(1)}, wait 20, UP*4, wait 20, " + A(3) + B(2),
         expect=dict(map="PokemonMansion_B1F_Frlg", xy=(24, 30), flags={"FLAG_POKEMON_MANSION_SWITCH_STATE": False})),
    dict(name="mansion-b1f-statue2", what="West, up the west hall, east along the middle and up the east side to the "
         "statue in the north-east room; press its switch again",
         via=[(23, 30), (23, 29), (19, 29), (19, 28), (15, 28), (15, 20), (27, 20), (27, 22), (33, 22), (33, 6)],
         walk=(27, 6), inputs="UP*4, wait 20, " + A(3) + B(2),
         expect=dict(map="PokemonMansion_B1F_Frlg", xy=(27, 6), flags={"FLAG_POKEMON_MANSION_SWITCH_STATE": True})),
    dict(name="secret-key", what="Back along the middle hall and through the opened way into the west room: the "
         "Secret Key", via=[(30, 6), (30, 10)], walk=(13, 10),
         inputs=f"LEFT*{hold(2)}, wait 6, UP*{hold(4)}, wait 6, LEFT*{hold(6)}, wait 20, DOWN*4, wait 20, " + A(2) +
         B(2),
         expect=dict(map="PokemonMansion_B1F_Frlg", xy=(5, 6),
         flags={"FLAG_HIDE_POKEMON_MANSION_B1F_SECRET_KEY": True})),
    dict(name="mansion-west-out", what="Out of the west room the way you came",
         inputs=f"RIGHT*{hold(3)}, wait 6, DOWN*{hold(4)}, wait 6, RIGHT*{hold(5)}, wait 30",
         expect=dict(map="PokemonMansion_B1F_Frlg", xy=(13, 10))),
    dict(name="mansion-out-statue", what="Back to the north-east statue; press the switch", via=[(30, 10), (30, 6)],
         walk=(27, 6), inputs="UP*4, wait 20, " + A(3) + B(2),
         expect=dict(map="PokemonMansion_B1F_Frlg", flags={"FLAG_POKEMON_MANSION_SWITCH_STATE": False})),
    dict(name="mansion-out-statue2", what="Down the east side (beside Ivan's line) and round to the statue below the "
         "table; press it again", via=[(30, 6), (30, 13), (31, 13), (31, 18), (33, 18), (33, 22), (29, 22), (29, 20),
         (15, 20), (15, 30)], walk=(24, 30), inputs="UP*4, wait 20, " + A(3) + B(2),
         expect=dict(map="PokemonMansion_B1F_Frlg", xy=(24, 30), flags={"FLAG_POKEMON_MANSION_SWITCH_STATE": True})),
    dict(name="mansion-out-lewis", state=FRESH, what="Up past the table and through the opened way, where Lewis "
         "wanders: if he sees you he battles", via=[(23, 30)], walk=(23, 24),
         inputs=f"LEFT*{hold(1)}, wait 6, UP*{hold(4)}, wait 100, " + A(120) + B(12) + "wait 200",
         expect=dict(map="PokemonMansion_B1F_Frlg")),
    dict(name="mansion-up", what="East along the north hall and down to the stairs; up to 1F", via=[(27, 20), (27, 29)],
         walk=(33, 29), inputs="RIGHT*12, wait 30, RIGHT*30, wait 250", expect=dict(map="PokemonMansion_1F_Frlg")),
    dict(name="mansion-out",
         what="Through 1F's east rooms (the switch has their barriers open) and out of the back door",
         inputs=f"RIGHT*{hold(2)}, wait 6, UP*{hold(4)}, wait 6, RIGHT*{hold(5)}, wait 6, DOWN*{hold(9)}, wait 6, "
         f"RIGHT*{hold(2)}, wait 20, DOWN*{hold(2)}, wait 250", expect=dict(map="CinnabarIsland_Frlg")),
    dict(name="cinnabar-gym", what="Along to the Gym: the Secret Key opens its door", walk=(20, 5),
         inputs=f"UP*{hold(1)}, wait 250", expect=dict(map="CinnabarIsland_Gym_Frlg")),
    # Blaine's Gym: each room's quiz machine opens the door to the next for a right answer (a wrong one brings out the
    # room's trainer). pae map path plans with the doors shut, so each walk stays in its room and the doors are walked
    # through in the inputs
    dict(name="gym-quiz1", what="Up into the east room to its quiz machine: Caterpie evolves into Metapod? Yes",
         via=[(26, 12)], walk=(22, 12), inputs=f"UP*{hold(1)}, wait 20, " + quiz(True),
         expect=dict(map="CinnabarIsland_Gym_Frlg", xy=(22, 11), flags={"FLAG_CINNABAR_GYM_QUIZ_1": True})),
    dict(name="gym-door1", what="Round Quinn and up through the opened door into the north-east room",
         inputs=f"DOWN*{hold(1)}, wait 6, RIGHT*{hold(4)}, wait 6, UP*{hold(5)}, wait 30",
         expect=dict(map="CinnabarIsland_Gym_Frlg", xy=(26, 7))),
    dict(name="gym-quiz2",
         what="Along the room's north side to its machine: there are nine certified League Badges? No",
         via=[(26, 3)], walk=(15, 3), inputs=quiz(False),
         expect=dict(map="CinnabarIsland_Gym_Frlg", xy=(15, 3), flags={"FLAG_CINNABAR_GYM_QUIZ_2": True})),
    dict(name="gym-door2", what="Down past Avery and through the door into the middle room",
         inputs=f"DOWN*{hold(4)}, wait 6, RIGHT*{hold(2)}, wait 6, DOWN*{hold(4)}, wait 30",
         expect=dict(map="CinnabarIsland_Gym_Frlg", xy=(17, 11))),
    dict(name="gym-quiz3", what="Round Ramon to the room's machine: Poliwag evolves three times? No",
         via=[(17, 12), (13, 12)], walk=(13, 11), inputs=quiz(False),
         expect=dict(map="CinnabarIsland_Gym_Frlg", xy=(13, 11), flags={"FLAG_CINNABAR_GYM_QUIZ_3": True})),
    dict(name="gym-door3", what="Through the door south into the south room",
         inputs=f"DOWN*{hold(3)}, wait 6, RIGHT*{hold(4)}, wait 6, DOWN*{hold(4)}, wait 30",
         expect=dict(map="CinnabarIsland_Gym_Frlg", xy=(17, 18))),
    dict(name="gym-quiz4", what="Round Derek to the machine: are electric moves effective against ground types? No",
         via=[(17, 19), (14, 19)], walk=(14, 18), inputs=quiz(False),
         expect=dict(map="CinnabarIsland_Gym_Frlg", xy=(14, 18), flags={"FLAG_CINNABAR_GYM_QUIZ_4": True})),
    dict(name="gym-door4", what="Through the door west into the south-west room",
         inputs=f"DOWN*{hold(4)}, wait 6, LEFT*{hold(4)}, wait 30",
         expect=dict(map="CinnabarIsland_Gym_Frlg", xy=(10, 22))),
    dict(name="gym-quiz5", what="Round Dusty to the machine: Pokémon of the same kind and level are not identical? Yes",
         via=[(3, 22), (3, 20)], walk=(2, 19), inputs=quiz(True),
         expect=dict(map="CinnabarIsland_Gym_Frlg", xy=(2, 19), flags={"FLAG_CINNABAR_GYM_QUIZ_5": True})),
    dict(name="gym-door5", what="Below Dusty and up through the door into the west room",
         inputs=f"DOWN*{hold(1)}, wait 6, RIGHT*{hold(3)}, wait 6, UP*{hold(5)}, wait 30",
         expect=dict(map="CinnabarIsland_Gym_Frlg", xy=(5, 15))),
    dict(name="gym-quiz6", what="Up the room's west side to the machine: TM28 contains Tombstony? No",
         via=[(2, 14)], walk=(2, 11), inputs=quiz(False),
         expect=dict(map="CinnabarIsland_Gym_Frlg", xy=(2, 11), flags={"FLAG_CINNABAR_GYM_QUIZ_6": True})),
    dict(name="gym-door6", what="Below Zac and up through the last door into Blaine's room",
         inputs=f"DOWN*{hold(1)}, wait 6, RIGHT*{hold(3)}, wait 6, UP*{hold(5)}, wait 30",
         expect=dict(map="CinnabarIsland_Gym_Frlg", xy=(5, 7))),
    dict(name="blaine", state=FRESH, what="Up to Blaine; beat him: the Volcano Badge and TM38", walk=(5, 5),
         inputs="UP*4, wait 20, " + A(120) + B(16) + "wait 300",
         expect=dict(map="CinnabarIsland_Gym_Frlg", xy=(5, 5),
         flags={"FLAG_BADGE07_GET": True, "FLAG_GOT_TM38_FROM_BLAINE": True})),
    dict(name="gym-out", what="Back out through the opened doors: down the west side and east along the south rooms, "
         "then up the middle (past Derek and Ramon) into the north room",
         inputs=f"DOWN*{hold(17)}, wait 6, RIGHT*{hold(12)}, wait 6, UP*{hold(15)}, wait 30",
         expect=dict(map="CinnabarIsland_Gym_Frlg", xy=(17, 7))),
    dict(name="gym-out2", what="Round Avery and Erik and down the east side through the first door to the entrance",
         inputs=f"RIGHT*{hold(1)}, wait 6, UP*{hold(4)}, wait 6, RIGHT*{hold(8)}, wait 6, DOWN*{hold(19)}, wait 30",
         expect=dict(map="CinnabarIsland_Gym_Frlg", xy=(26, 22))),
    dict(name="bill-cinnabar",
         what="Out of the Gym: Bill is waiting and asks you to come to One Island with him. Say no (the "
         "Sevii Islands aren't part of this check): he waits in the Pokémon Center",
         inputs=f"LEFT*{hold(1)}, wait 20, DOWN*{hold(2)}, wait 400, " + B(6, 120) + "wait 120, B*4, wait 200, " +
         B(5, 120) + "wait 300",
         expect=dict(map="CinnabarIsland_Frlg", vars={"VAR_MAP_SCENE_CINNABAR_ISLAND": 2})),
    # The last badge is Viridian's: north by Route 21 to Pallet
    dict(name="cinnabar-surf", what="West along the top street to the shore; Surf", walk=(3, 5),
         inputs="LEFT*4, wait 30, " + A(3, 80) + "wait 200", expect=dict(map="CinnabarIsland_Frlg", xy=(2, 5))),
    dict(name="route21-south", what="North up the island's west side onto Route 21", surf=True, walk=(2, 0),
         inputs="UP*2, wait 12, UP*12, wait 200", expect=dict(map="Route21_South_Frlg")),
    dict(name="route21-north", what="Straight up the west side of Route 21 (off the swimmers' lines)", surf=True,
         walk=(2, 0), inputs="UP*2, wait 12, UP*12, wait 200", expect=dict(map="Route21_North_Frlg")),
    dict(name="pallet-again", what="On up, then east into the channel between the fields and up it into Pallet Town",
         surf=True, via=[(2, 16), (7, 16), (7, 0)], walk=(8, 0), inputs="UP*2, wait 12, UP*12, wait 200",
         expect=dict(map="PalletTown_Frlg")),
    dict(name="pallet-shore", what="Up Pallet's pond and ashore by the lab", surf=True, walk=(16, 20),
         inputs="LEFT*2, wait 12, LEFT*4, wait 100", expect=dict(map="PalletTown_Frlg", xy=(15, 20))),
    dict(name="route1-again", what="Up through Pallet onto Route 1", via=[(15, 0)], walk=(14, 0), inputs="UP*30, wait 200",
         expect=dict(map="Route1_Frlg")),
    dict(name="viridian-again", what="Up Route 1 into Viridian", walk=(23, 0), inputs="UP*12, wait 200",
         expect=dict(map="ViridianCity_Frlg")),
    dict(name="viridian-gym", what="Across Viridian to the Gym: with seven badges its door is open now (the walk stops a "
         "block short: the block before the door runs the locked-door scene, which a checkpoint would cut off)",
         walk=(44, 22), inputs=f"UP*{hold(2)}, wait 250", expect=dict(map="ViridianCity_Gym_Frlg", vars={"VAR_MAP_SCENE_VIRIDIAN_CITY_GYM_DOOR": 1})),
    # Giovanni's Gym: spin tiles, planned on the tiles (scratchpad spin.py) like the Rocket Hideout's. Giovanni's
    # corner opens only past Warren's and Takashi's lines, so both battle
    dict(name="viridian-gym-warren", state=FRESH, what="Across the spin tiles to the north-east and up into Warren's "
         "line: he battles",
         inputs="UP*2, wait 10, UP*108, wait 10, LEFT*2, wait 10, LEFT*12, wait 52, LEFT*2, wait 10, LEFT*28, "
         "wait 10, UP*2, wait 10, UP*28, wait 10, LEFT*2, wait 10, LEFT*12, wait 10, UP*2, wait 10, UP*44, "
         "wait 10, RIGHT*2, wait 10, RIGHT*28, wait 10, UP*2, wait 10, UP*28, wait 10, wait 20, UP*12, "
         "wait 120, " + A(120) + B(12) + "wait 200",
         expect=dict(map="ViridianCity_Gym_Frlg", xy=(15, 7))),
    dict(name="viridian-gym-takashi", state=FRESH, what="Round Warren and west along the hall into Takashi's line: he "
         "battles", inputs="UP*2, wait 10, UP*12, wait 10, LEFT*2, wait 10, LEFT*44, wait 10, DOWN*2, wait 10, DOWN*12, "
         "wait 10, LEFT*2, wait 10, LEFT*28, wait 10, UP*2, wait 10, UP*12, wait 10, wait 20, UP*12, "
         "wait 120, " + A(120) + B(12) + "wait 200",
         expect=dict(map="ViridianCity_Gym_Frlg", xy=(10, 5))),
    dict(name="giovanni", state=FRESH, what="Round to Giovanni in the north-west room; beat him: the Earth Badge, and "
         "Team Rocket is finished", inputs="UP*2, wait 10, UP*28, wait 10, LEFT*2, wait 10, LEFT*44, wait 10, DOWN*2, wait 10, DOWN*44, "
         "wait 10, LEFT*2, wait 10, LEFT*60, wait 10, UP*2, wait 10, UP*44, wait 10, LEFT*2, wait 10, "
         "LEFT*12, wait 10, wait 20, UP*4, wait 20, " + A(120) + B(16) + "wait 300",
         expect=dict(map="ViridianCity_Gym_Frlg", xy=(2, 3), flags={"FLAG_BADGE08_GET": True},
                     vars={"VAR_MAP_SCENE_ROUTE22": 3})),
    dict(name="leave-viridian-gym", what="Back across the spin tiles and out of the Gym (no tap to turn first: a "
         "checkpoint's reload leaves you facing down already, and a tap that way is a step)",
         inputs="DOWN*44, wait 10, RIGHT*2, wait 10, RIGHT*76, wait 10, UP*2, wait 10, UP*44, "
         "wait 10, RIGHT*2, wait 10, RIGHT*44, wait 10, RIGHT*2, wait 10, RIGHT*12, wait 124, RIGHT*2, "
         "wait 10, RIGHT*12, wait 184, DOWN*2, wait 10, DOWN*108, wait 10, LEFT*2, wait 10, LEFT*12, "
         "wait 10, wait 20, DOWN*28, wait 300", expect=dict(map="ViridianCity_Frlg", xy=(44, 21))),
    # The road to the League
    dict(name="route22-again", what="West along Viridian's street onto Route 22", via=[(44, 29)], walk=(0, 29),
         inputs="LEFT*12, wait 200", expect=dict(map="Route22_Frlg", xy=(51, 7))),
    dict(name="route22-rival", state=FRESH, what="West along the road: the rival comes after you for one last battle "
         "before the League", walk=(45, 7), inputs=f"LEFT*{hold(1)}, wait 200, " + A(120) + B(16) + "wait 400",
         expect=dict(map="Route22_Frlg", vars={"VAR_MAP_SCENE_ROUTE22": 4})),
    dict(name="league-gate-again", what="Round Route 22's ponds to the League Front Gate", via=[(45, 9), (37, 9), (37, 18),
         (17, 18), (17, 14)], walk=(12, 14), inputs=f"UP*{hold(2)}, wait 300", expect=dict(map="Route22_NorthEntrance_Frlg")),
    dict(name="boulder-badge-gate", what="Up the gatehouse: the guard checks the Boulder Badge; on out of its north door "
         "onto Route 23", walk=(7, 3), inputs=f"UP*{hold(1)}, wait 200, " + B(4) + f"wait 60, UP*{hold(2)}, wait 300",
         expect=dict(map="Route23_Frlg", vars={"VAR_MAP_SCENE_ROUTE23": 1})),
    # Route 23's badge gates: each guard stops you on the row before him (a walk ends a block short: the trigger row
    # runs his scene, which a checkpoint would cut off)
    dict(name="cascade-badge-gate", what="Up the road to the Cascade Badge's gate: the guard checks it and lets you by",
         walk=(9, 142), inputs=f"UP*{hold(1)}, wait 200, " + B(4) + "wait 60",
         expect=dict(map="Route23_Frlg", vars={"VAR_MAP_SCENE_ROUTE23": 2})),
    dict(name="thunder-badge-gate", what="Up the road to the Thunder Badge's gate: the guard checks it and lets you by",
         walk=(9, 124), inputs=f"UP*{hold(1)}, wait 200, " + B(4) + "wait 60",
         expect=dict(map="Route23_Frlg", vars={"VAR_MAP_SCENE_ROUTE23": 3})),
    dict(name="rainbow-badge-gate", what="Up the road to the Rainbow Badge's gate: the guard checks it and lets you by",
         walk=(9, 106), inputs=f"UP*{hold(1)}, wait 200, " + B(4) + "wait 60",
         expect=dict(map="Route23_Frlg", vars={"VAR_MAP_SCENE_ROUTE23": 4})),
    dict(name="soul-badge-gate", what="Up the road to the Soul Badge's gate: the guard checks it and lets you by",
         walk=(9, 88), inputs=f"UP*{hold(1)}, wait 200, " + B(4) + "wait 60",
         expect=dict(map="Route23_Frlg", vars={"VAR_MAP_SCENE_ROUTE23": 5})),
    dict(name="route23-lake", what="Up to the lake's shore; Surf", walk=(9, 80),
         inputs="UP*4, wait 30, " + A(3, 80) + "wait 200", expect=dict(map="Route23_Frlg", xy=(9, 79))),
    dict(name="route23-lake-north", what="Across the lake and ashore", surf=True, walk=(9, 66),
         inputs="UP*2, wait 12, UP*4, wait 100", expect=dict(map="Route23_Frlg", xy=(9, 65))),
    dict(name="marsh-badge-gate", what="Up the road to the Marsh Badge's gate: the guard checks it and lets you by",
         walk=(9, 60), inputs=f"UP*{hold(1)}, wait 200, " + B(4) + "wait 60",
         expect=dict(map="Route23_Frlg", vars={"VAR_MAP_SCENE_ROUTE23": 6})),
    dict(name="volcano-badge-gate", what="Up the road to the Volcano Badge's gate: the guard checks it and lets you by",
         walk=(9, 50), inputs=f"UP*{hold(1)}, wait 200, " + B(4) + "wait 60",
         expect=dict(map="Route23_Frlg", vars={"VAR_MAP_SCENE_ROUTE23": 7})),
    dict(name="earth-badge-gate", what="Up the road to the Earth Badge's gate: the guard checks it and lets you by",
         walk=(5, 40), inputs=f"UP*{hold(1)}, wait 200, " + B(4) + "wait 60",
         expect=dict(map="Route23_Frlg", vars={"VAR_MAP_SCENE_ROUTE23": 8})),
    dict(name="victory-road", what="Into the yard under the cliff and into Victory Road", walk=(6, 30),
         inputs=f"UP*{hold(1)}, wait 300", expect=dict(map="VictoryRoad_1F_Frlg")),
    dict(name="vr1f-boulder", what="Victory Road 1F: round the first boulder to stand above it", via=[(6, 18)],
         walk=(7, 17),
         inputs="wait 5", expect=dict(map="VictoryRoad_1F_Frlg", xy=(7, 17))),
    dict(name="vr1f-switch", what="Strength: the boulder down, along and up onto the floor switch; the rock barrier "
         "opens", inputs=pushes(*VR1F) + ", wait 120",
         expect=dict(map="VictoryRoad_1F_Frlg", vars={"VAR_MAP_SCENE_VICTORY_ROAD_1F": 100})),
    dict(name="vr2f", what="Round the boulder (back where it started: the switch stays down) and through the opened "
         "barrier, under Naomi's and Rolando's lines and up the ladder",
         via=[(6, 18), (6, 17), (7, 16), (13, 14), (15, 11), (15, 5), (13, 8), (5, 10), (4, 7)],
         walk=(4, 2), inputs=f"LEFT*{hold(1)}, wait 200, DOWN*{hold(1)}, wait 20",
         expect=dict(map="VictoryRoad_2F_Frlg", xy=(1, 10))),
    dict(name="vr2f-switch", what="2F: Strength, the boulder down onto the west floor switch; its barrier opens",
         inputs=pushes(*VR2F) + ", wait 120",
         expect=dict(map="VictoryRoad_2F_Frlg", vars={"VAR_MAP_SCENE_VICTORY_ROAD_2F_BOULDER1": 100})),
    dict(name="vr3f", what="Round the boulder (back where it started) through the barrier, east across 2F under Daisuke "
         "and behind Nelson, and up the ladder to 3F", via=[(4, 13), (9, 13), (9, 10), (21, 10), (21, 17), (31, 20), (40, 19),
         (34, 14)], walk=(34, 10),
         inputs=f"UP*{hold(1)}, wait 200, DOWN*{hold(1)}, wait 20", expect=dict(map="VictoryRoad_3F_Frlg", xy=(34, 10))),
    dict(name="vr3f-switch", what="3F: Strength, the north boulder up, west along the top and down onto the floor "
         "switch; the barrier on the west side opens", inputs=pushes(*VR3F) + ", wait 120",
         expect=dict(map="VictoryRoad_3F_Frlg", vars={"VAR_MAP_SCENE_VICTORY_ROAD_3F": 100})),
    dict(name="vr3f-hole", what="Round the top and the west side through the opened barrier, east along the south "
         "(under Colby's and Caroline's lines) to the boulder by the hole; Strength, and it falls in, to 2F",
         via=[(10, 4), (10, 2), (23, 2), (23, 3), (29, 3), (29, 8), (25, 8), (25, 6), (16, 6), (16, 12), (4, 11),
              (4, 15), (17, 15), (17, 19), (21, 19)], walk=(32, 18), inputs=pushes("R!") + ", wait 120",
         expect=dict(map="VictoryRoad_3F_Frlg", flags={"FLAG_HIDE_VICTORY_ROAD_2F_BOULDER": False,
                                                       "FLAG_HIDE_VICTORY_ROAD_3F_BOULDER": True})),
    dict(name="vr2f-switch2", what="Down the hole after it, then Strength and the boulder 19 blocks west onto the "
         "second switch; the barrier by the east ladder opens",
         inputs=f"RIGHT*{hold(2)}, wait 200, " + pushes(*VR2F_2) + ", wait 120",
         expect=dict(map="VictoryRoad_2F_Frlg", vars={"VAR_MAP_SCENE_VICTORY_ROAD_2F_BOULDER2": 100})),
    dict(name="vr3f-east", what="Round the wandering Pokémon and the boulder (back by the hole's foot), through the "
         "second barrier behind Nelson and up the east ladder to 3F",
         via=[(18, 19), (18, 20), (24, 20), (24, 19), (31, 19), (31, 17)], walk=(35, 17),
         inputs=f"RIGHT*{hold(1)}, wait 200, UP*{hold(1)}, wait 20", expect=dict(map="VictoryRoad_3F_Frlg", xy=(39, 16))),
    dict(name="vr2f-east", what="Across 3F's east side under Tyra's line and down the ladder to 2F's far side",
         via=[(39, 15), (37, 15), (37, 14), (36, 14), (36, 11)], walk=(37, 11),
         inputs=f"UP*{hold(1)}, wait 200, DOWN*{hold(1)}, wait 20", expect=dict(map="VictoryRoad_2F_Frlg", xy=(38, 10))),
    dict(name="victory-road-out", what="Out of Victory Road onto Route 23's top yard", via=[(38, 11)], walk=(48, 11),
         inputs=f"DOWN*{hold(1)}, wait 20, DOWN*20, wait 300", expect=dict(map="Route23_Frlg")),
    dict(name="indigo-plateau", what="Up Route 23's last stretch to the Indigo Plateau", walk=(11, 0),
         inputs=f"UP*{hold(2)}, wait 60", expect=dict(map="IndigoPlateau_Exterior_Frlg")),
    dict(name="indigo-center", what="Into the Indigo Plateau's Pokémon Center (the League's doors: the end of the "
         "check)", walk=(11, 12), inputs=f"UP*{hold(1)}, wait 300",
         expect=dict(map="IndigoPlateau_PokemonCenter_1F_Frlg")),
]


class Runner:
    def __init__(self, project: Path):
        self.project = project
        self.out = project / ".pae" / "story-check"
        self.out.mkdir(parents=True, exist_ok=True)

    def pae(self, *args):
        r = subprocess.run(["pae", *args, "-p", str(self.project)], capture_output=True, text=True)
        return r.returncode, r.stdout + r.stderr

    def path(self, map_, a, b, surf=False, bike=False):
        """pae map path's walk as inputs: each straight run held for its steps (see hold()); on water with ``surf``,
        riding with ``bike``."""
        code, out = self.pae("map", "path", map_, f"{a[0]},{a[1]}", f"{b[0]},{b[1]}", *(["--surf"] if surf else []))
        steps = [line.split("_")[1] for line in out.splitlines() if line.startswith("walk_")]
        if code or (not steps and tuple(a) != tuple(b)):
            raise RuntimeError(f"no walk on {map_} from {a} to {b}: {out.strip().splitlines()[-1]}")
        runs = []
        for s in steps:
            if runs and runs[-1][0] == s:
                runs[-1][1] += 1
            else:
                runs.append([s, 1])
        if surf:  # each turn is its own tap first: on water a press toward a new way only turns you (a play starts
            # facing down, as a loaded game does)
            taps = ["" if k == 0 and d == "down" else f"{DIRS[d]}*2, wait 12, " for k, (d, _) in enumerate(runs)]
            return ", ".join(f"{t}{DIRS[d]}*{surf_hold(n)}, wait 6" for t, (d, n) in zip(taps, runs))
        if bike:
            return ", ".join(f"{DIRS[d]}*{bike_hold(n)}, wait 6" for d, n in runs)
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

    def play(self, shot, cp=None, map_=None, xy=None, state=(), inputs="wait 5", save=None, flags=(), vars_=(),
             repel=True):
        args = ["play"] + ([map_] if map_ else []) + (["--from", cp] if cp else [])
        if xy:
            args += ["--x", str(xy[0]), "--y", str(xy[1])]
        for s in ([REPEL] if repel else []) + list(state):
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

    def walk(self, shot, cp, save, target, state, tries=6, surf=False, bike=False):
        """From ``cp`` to ``target`` on its map, re-planned from wherever the player stopped (people walk about:
        each try waits a little longer first). Stops early if the walk crossed onto another map."""
        here = self.play(f"{shot}-at", cp=cp)
        start_map, cur = here["map"], cp
        for k in range(tries + 1):
            if here["map"] != start_map or here["xy"] == tuple(target):
                return here, cur
            if k == tries:
                raise RuntimeError(f"couldn't walk to {target}: stuck at {here['map']} {here['xy']}")
            walk = self.path(here["map"], here["xy"], target, surf, bike)
            inputs = f"wait {20 + 70 * k}, {walk}, wait 20"
            try:
                here = self.play(f"{shot}-walk{k}", cp=cur, inputs=inputs, save=save, state=state)
            except RuntimeError as e:
                if "only be saved" not in str(e):
                    raise
                # a trainer who wanders saw the walk and battles (the game can't be saved mid-battle): play the
                # same walk on through the battle, then plan again from wherever it left you
                here = self.play(f"{shot}-walk{k}-battle", cp=cur, inputs=inputs + ", " + A(120) + B(12) + "wait 100",
                                 save=save, state=state)
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
                    _, src = self.walk(f"{cp}-via{j}", src, cp, via, state, surf=step.get("surf", False),
                                       bike=step.get("bike", False))
                here, src = self.walk(cp, src, cp, step["walk"], state, surf=step.get("surf", False),
                                      bike=step.get("bike", False))
            else:
                here, src = self.play(f"{cp}-from", cp=prev_cp), prev_cp
            self.play(cp, cp=src, state=state, inputs=self.inputs(step["inputs"], here["map"]), save=cp,
                      repel=step.get("repel", True))
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
    twice = sorted({n for n in names if names.count(n) > 1})
    if twice:  # --from and the checkpoints go by name
        sys.exit(f"steps with the same name: {', '.join(twice)}")
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

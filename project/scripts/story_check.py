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
    dict(name="route1", what="The sign lady's trainer tips at the route entrance, then into Route 1 (Ho-Oh waits for the Pokédex)",
         walk=(15, 6), inputs="UP*64, wait 100, " + B(6) + "wait 60, UP*64, wait 300",
         expect=dict(map="Route1_Frlg", xy=(25, 39),
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
         walk=(15, 0), inputs="UP*12, wait 150, " + A(2) + "wait 1000, " + A(30) + "wait 400",
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
    dict(name="cerulean-rival", what="Along the street past the robbed house (its policeman in the door) and up the bridge "
                                     "road: Blue comes down off Nugget Bridge and battles",
         via=[(30, 24), (41, 24)], walk=(42, 8),
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

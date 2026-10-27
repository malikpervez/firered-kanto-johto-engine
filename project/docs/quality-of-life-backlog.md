# Quality-of-life backlog

Small things found while play-testing that don't stop the story. They are kept here to fix later, each in its own
pull request. Add new ones as they turn up and take them off when they are fixed (the pull request says which).
Gaps in pae are not kept here: they are fixed in pae straight away.

## Small fixes

| # | Where | What happens | Found | Idea |
|---|---|---|---|---|
| 1 | Pallet Town, the fat man (`LOCALID_PALLET_FAT_MAN`, (18,17)) | He wanders 6 blocks across and 2 down (`MOVEMENT_TYPE_WANDER_AROUND`), which takes in the path to Oak's lab door. He can stand in the way, and the player has to wait or walk around him. | Story check, 2026-10-22: the walk to the lab door needed several tries. | Make his wander area smaller or move it off the path, or have him stand still or look around. |
| 2 | Oak's lab, the exit mat (5–7,12) | All three mat blocks warp out, but only the middle one (metatile 0x291) has the "step down to leave" behaviour (`MB_SOUTH_ARROW_WARP`). The left and right ones (0x290, 0x292) are plain floor, so pressing down on them does nothing. The interior hasn't changed since the 37C import. | Story check, 2026-10-22: pressing down at (7,12) didn't leave; (6,12) did. | Give 0x290 and 0x292 the same behaviour in `gTileset_Lab_Frlg`. Sinjoh Ruins' house uses that tileset too, so look at it after. |
| 3 | The out-of-memory crash screen (`AssertfCrashScreen`, `src/assertf.c`) | When the heap runs out, the screen that should say so needs memory itself. It fails again and again until the game restarts, so the player sees a sudden reset with no message. | Tracing the tutorial-battle resets (PR #21). | Draw the crash screen without the heap, or keep memory aside for it. |
| 4 | Kanto's ambient Pokémon with `MOVEMENT_TYPE_WANDER_AROUND` and movement range 0: 64 of them on 27 maps (Route 15's six Hoppip, Cinnabar's six, Cerulean Cave's eleven, Route 20's four, Route 3's four, Victory Road's six…) | Range 0 means no limit, so they wander anywhere on the map. On Route 15 a Hoppip stood in the road and the walk west couldn't get by; any of them can do that on a narrow way. | Story check, 2026-10-27 (Route 15). Again in Victory Road 1F: the Golem placed at (17,16) wanders in the pocket by the floor switch (20,16), which the boulder has to be pushed round, so it stands in the way of the last pushes; a push into it just doesn't happen. The check waits for it (the waits the step needs depend on the checkpoint). | Give each a small range (1–2 blocks) round where it's placed, as Route 15's Volbeat and Illumise have. |
| 5 | Celadon City, warps 10–12 | Three warps on the same block (25,11), all to the Mansion's back door (1F warp 5): only the first is ever used. | Story check, 2026-10-27 | Keep one. |
| 6 | The Rocket Hideout's and Silph Co.'s lifts, the Game Corner's exit, Saffron's four gatehouses (FireRed's own interiors) | As in Oak's lab (#2), only one block of each exit mat leaves when you press toward the door on it: the lifts' (2,5), not (1,5); the Game Corner's (9,13), not (10,13) or (11,13); in the gatehouses one block of each two-block mat (Route 8's west gate leaves from (1,5), not (1,4); Route 7's from (1,5) and (11,5), not (1,6) and (11,6); Routes 5's and 6's from (4,9), not (3,9) or (5,9)). | Story check, 2026-10-27 | Give the other blocks `MB_SOUTH_ARROW_WARP` too. |
| 7 | Cerulean City, warps 5, 11 and 14 | Three warps on the same block (10,41), all to the Bike Shop's door (its warp 1): only the first is ever used. Like #5. | Story check, 2026-10-27 | Keep one. |

## Planned later (bigger than a fix)

These come from the map work so far. They go with the map edits they belong to, not as fixes on their own.

* **Pallet's sea to Cinnabar**: the sea becomes surfable when it leads to Cinnabar (the old Route 21). See
  `project/art/WORLD.md`, "Planned".
* **Route 22 to Route 23**: join them again when Route 23 is rebuilt (`project/art/WORLD.md`).
* **The tree to cut**: the kit's tree has one frame, and the game cuts it in four. It needs cutting frames, and
  until then Viridian and Route 2 use FireRed's tree (`project/art/viridian-concept/README.md`).
* **Tall grass mix**: kinds B and C now alternate block by block. The other option is whole patches of one kind
  next to patches of the other.
* **Rock and cliff pack into the kit**: move Route 22's rock and cliff tiles into the shared kit so every route can
  use them. This needs a free palette slot in the kit first.

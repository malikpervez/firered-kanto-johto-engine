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
| 4 | Viridian City, the Friends' camp (`src/data/friends_scene_locations.h`) | The camp's first local id is 12, but Brian is local id 11 (an object before the Friends went since the 37C snapshot), so the scene would look for the seven one id off. Route 2 had the same, fixed with its rebuild. Their scene needs that story's state, so it wasn't played. | Rebuilding Route 2, 2026-10-23. | Set it to 11, then play a Friends scene there. |

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
